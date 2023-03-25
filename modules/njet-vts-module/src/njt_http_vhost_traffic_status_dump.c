
/*
 * Copyright (C) YoungJoo Kim (vozlt)
 * Copyright (C) TMLake, Inc.
 */


#include "njt_http_vhost_traffic_status_module.h"
#include "njt_http_vhost_traffic_status_dump.h"


static u_char  NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_DATA_PAD[] = { 0x53, 0x54, 0x56 };


static ssize_t njt_http_vhost_traffic_status_dump_header_read(njt_file_t *file,
    njt_http_vhost_traffic_status_dump_header_t *file_header);
static ssize_t njt_http_vhost_traffic_status_dump_header_write(njt_event_t *ev,
    njt_file_t *file);
static void njt_http_vhost_traffic_status_dump_node_write(njt_event_t *ev,
    njt_file_t *file, njt_rbtree_node_t *node);
static njt_int_t njt_http_vhost_traffic_status_dump_update_valid(njt_event_t *ev);
static njt_int_t njt_http_vhost_traffic_status_dump_restore_add_node(njt_event_t *ev,
     njt_http_vhost_traffic_status_node_t *ovtsn, njt_str_t *key);


void
njt_http_vhost_traffic_status_file_lock(njt_file_t *file)
{
    njt_err_t  err = njt_lock_fd(file->fd);

    if (err == 0) {
        return;
    }

    njt_log_error(NJT_LOG_ALERT, file->log, err,
                  njt_lock_fd_n " \"%s\" failed", file->name.data);
}


void
njt_http_vhost_traffic_status_file_unlock(njt_file_t *file)
{
    njt_err_t  err = njt_unlock_fd(file->fd);

    if (err == 0) {
        return;
    }

    njt_log_error(NJT_LOG_ALERT, file->log, err,
                  njt_unlock_fd_n " \"%s\" failed", file->name.data);
}


void
njt_http_vhost_traffic_status_file_close(njt_file_t *file)
{
    if (njt_close_file(file->fd) == NJT_FILE_ERROR) {
        njt_log_error(NJT_LOG_ALERT, file->log, njt_errno,
                      njt_close_file_n " \"%s\" failed", file->name.data);
    }
}


static ssize_t
njt_http_vhost_traffic_status_dump_header_read(njt_file_t *file,
    njt_http_vhost_traffic_status_dump_header_t *file_header)
{
    ssize_t  n;

    njt_memzero(file_header, sizeof(njt_http_vhost_traffic_status_dump_header_t));

    n = njt_read_file(file, (u_char *) file_header,
                      sizeof(njt_http_vhost_traffic_status_dump_header_t), 0);

    return n;
}


static ssize_t
njt_http_vhost_traffic_status_dump_header_write(njt_event_t *ev, njt_file_t *file)
{
    size_t                                        len;
    ssize_t                                       n;
    u_char                                       *p;
    njt_http_vhost_traffic_status_ctx_t          *ctx;
    njt_http_vhost_traffic_status_dump_header_t   file_header;

    ctx = ev->data;

    njt_memzero(&file_header, sizeof(njt_http_vhost_traffic_status_dump_header_t));

    len = (ctx->shm_name.len >= NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_HEADER_NAME_SIZE)
          ? NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_HEADER_NAME_SIZE - 1
          : ctx->shm_name.len;

    p = file_header.name;
    p = njt_cpymem(p, ctx->shm_name.data, len);
    file_header.time = njt_http_vhost_traffic_status_current_msec();
    file_header.version = njet_version;

    n = njt_write_fd(file->fd, &file_header, sizeof(njt_http_vhost_traffic_status_dump_header_t));

    return n;
}


static void
njt_http_vhost_traffic_status_dump_node_write(njt_event_t *ev, njt_file_t *file,
    njt_rbtree_node_t *node)
{
    njt_http_vhost_traffic_status_ctx_t   *ctx;
    njt_http_vhost_traffic_status_node_t  *volatile vtsn;

    ctx = ev->data;

    if (node != ctx->rbtree->sentinel) {
        vtsn = (njt_http_vhost_traffic_status_node_t *) &node->color;

        (void) njt_write_fd(file->fd, vtsn, sizeof(njt_http_vhost_traffic_status_node_t));
        (void) njt_write_fd(file->fd, vtsn->data, vtsn->len);
        (void) njt_write_fd(file->fd, NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_DATA_PAD,
                            sizeof(NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_DATA_PAD));

        njt_http_vhost_traffic_status_dump_node_write(ev, file, node->left);
        njt_http_vhost_traffic_status_dump_node_write(ev, file, node->right);
    }
}


static njt_int_t
njt_http_vhost_traffic_status_dump_update_valid(njt_event_t *ev)
{
    size_t                                        len;
    ssize_t                                       n;
    njt_fd_t                                      fd;
    njt_int_t                                     rc;
    njt_msec_t                                    current_msec;
    njt_file_t                                    file;
    njt_http_vhost_traffic_status_ctx_t          *ctx;
    njt_http_vhost_traffic_status_dump_header_t   file_header;

    ctx = ev->data;

    fd = njt_open_file(ctx->dump_file.data, NJT_FILE_RDONLY, NJT_FILE_OPEN, 0);
    if (fd == NJT_INVALID_FILE) {
        njt_log_debug1(NJT_LOG_DEBUG_HTTP, ev->log, njt_errno,
                       njt_open_file_n " \"%s\" failed", ctx->dump_file.data);
        return NJT_OK;
    }

    file.fd = fd;
    file.name = ctx->dump_file;
    file.log = ev->log;

    n = njt_http_vhost_traffic_status_dump_header_read(&file, &file_header);

    njt_http_vhost_traffic_status_file_close(&file);

    if (n != sizeof(njt_http_vhost_traffic_status_dump_header_t)) {
        njt_log_debug1(NJT_LOG_DEBUG_HTTP, ev->log, 0,
                      "dump_update_valid::dump_header_read() size:%z failed", n);
        return NJT_OK;
    }

    len = (ctx->shm_name.len >= NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_HEADER_NAME_SIZE)
          ? NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_HEADER_NAME_SIZE - 1
          : ctx->shm_name.len;

    if (njt_strncmp(ctx->shm_name.data, file_header.name, len) != 0) {
        njt_log_debug2(NJT_LOG_DEBUG_HTTP, ev->log, 0,
                      "dump_update_valid::dump_header_read() name[%z]:\"%s\" failed",
                      len, file_header.name);
        return NJT_OK;
    }

    current_msec = njt_http_vhost_traffic_status_current_msec();

    rc = ((current_msec - file_header.time) > ctx->dump_period) ? NJT_OK : NJT_ERROR;

    return rc;
}


njt_int_t
njt_http_vhost_traffic_status_dump_execute(njt_event_t *ev)
{
    u_char                               *name;
    ssize_t                               n;
    njt_fd_t                              fd;
    njt_file_t                            file;
    njt_http_vhost_traffic_status_ctx_t  *ctx;

    ctx = ev->data;

    name = ctx->dump_file.data;

    fd = njt_open_file(name, NJT_FILE_RDWR, NJT_FILE_TRUNCATE, NJT_FILE_DEFAULT_ACCESS);

    if (fd == NJT_INVALID_FILE) {
        njt_log_error(NJT_LOG_ALERT, ev->log, njt_errno,
                      njt_open_file_n " \"%s\" failed", name);
        return NJT_ERROR;
    }

    file.fd = fd;
    file.name = ctx->dump_file;
    file.log = ev->log;

    njt_http_vhost_traffic_status_file_lock(&file);

    n = njt_http_vhost_traffic_status_dump_header_write(ev, &file);
    if (n != sizeof(njt_http_vhost_traffic_status_dump_header_t)) {
        njt_log_error(NJT_LOG_ALERT, ev->log, 0,
                      "dump_execute::dump_header_write() failed");

        njt_http_vhost_traffic_status_file_unlock(&file);
        njt_http_vhost_traffic_status_file_close(&file);

        return NJT_ERROR;
    }

    njt_http_vhost_traffic_status_dump_node_write(ev, &file, ctx->rbtree->root);

    njt_http_vhost_traffic_status_file_unlock(&file);
    njt_http_vhost_traffic_status_file_close(&file);

    return NJT_OK;
}


void
njt_http_vhost_traffic_status_dump_handler(njt_event_t *ev)
{
    njt_int_t  rc;

    if (njt_exiting) {
        return;
    }

    rc = njt_http_vhost_traffic_status_dump_update_valid(ev);
    if (rc != NJT_OK) {
        goto invalid;
    }

    rc = njt_http_vhost_traffic_status_dump_execute(ev);
    if (rc != NJT_OK) {
        njt_log_error(NJT_LOG_ALERT, ev->log, 0,
                      "dump_handler::dump_header_execute() failed");
    }

invalid:

    njt_add_timer(ev, 1000);
}


static njt_int_t
njt_http_vhost_traffic_status_dump_restore_add_node(njt_event_t *ev,
     njt_http_vhost_traffic_status_node_t *ovtsn, njt_str_t *key)
{
    size_t                                 size;
    uint32_t                               hash;
    njt_slab_pool_t                       *shpool;
    njt_rbtree_node_t                     *node;
    njt_http_vhost_traffic_status_ctx_t   *ctx;
    njt_http_vhost_traffic_status_node_t  *vtsn;

    ctx = ev->data;

    if (key->len == 0) {
        return NJT_ERROR;
    }

    shpool = (njt_slab_pool_t *) ctx->shm_zone->shm.addr;

    njt_shmtx_lock(&shpool->mutex);

    /* find node */
    hash = njt_crc32_short(key->data, key->len);

    node = njt_http_vhost_traffic_status_node_lookup(ctx->rbtree, key, hash);

    /* copy node */
    if (node == NULL) {
        size = offsetof(njt_rbtree_node_t, color)
               + offsetof(njt_http_vhost_traffic_status_node_t, data)
               + key->len;

        node = njt_slab_alloc_locked(shpool, size);
        if (node == NULL) {
            njt_log_error(NJT_LOG_ALERT, ev->log, 0,
                          "dump_restore_add_node::njt_slab_alloc_locked() failed");

            njt_shmtx_unlock(&shpool->mutex);
            return NJT_ERROR;
        }

        vtsn = (njt_http_vhost_traffic_status_node_t *) &node->color;

        node->key = hash;

        *vtsn = *ovtsn;

        njt_memcpy(vtsn->data, key->data, key->len);

        njt_rbtree_insert(ctx->rbtree, node);
    }

    njt_shmtx_unlock(&shpool->mutex);

    return NJT_OK;
}


void
njt_http_vhost_traffic_status_dump_restore(njt_event_t *ev)
{
    off_t                                         offset;
    size_t                                        len;
    ssize_t                                       n;
    u_char                                       *buf, *pad;
    njt_fd_t                                      fd;
    njt_str_t                                     key;
    njt_int_t                                     rc;
    njt_file_t                                    file;
    njt_http_vhost_traffic_status_ctx_t          *ctx;
    njt_http_vhost_traffic_status_node_t          vtsn;
    njt_http_vhost_traffic_status_dump_header_t   file_header;

    ctx = ev->data;

    fd = njt_open_file(ctx->dump_file.data, NJT_FILE_RDONLY, NJT_FILE_OPEN, 0);
    if (fd == NJT_INVALID_FILE) {
        njt_log_debug1(NJT_LOG_DEBUG_HTTP, ev->log, njt_errno,
                       njt_open_file_n " \"%s\" failed", ctx->dump_file.data);
        return;
    }

    file.fd = fd;
    file.name = ctx->dump_file;
    file.log = ev->log;

    n = njt_http_vhost_traffic_status_dump_header_read(&file, &file_header);

    if (n != sizeof(njt_http_vhost_traffic_status_dump_header_t)) {
        njt_log_debug1(NJT_LOG_DEBUG_HTTP, ev->log, 0,
                      "dump_restore::dump_header_read() size:%z failed", n);
        njt_http_vhost_traffic_status_file_close(&file);
        return;
    }

    len = (ctx->shm_name.len >= NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_HEADER_NAME_SIZE)
          ? NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_HEADER_NAME_SIZE - 1
          : ctx->shm_name.len;

    if (njt_strncmp(ctx->shm_name.data, file_header.name, len) != 0) {
        njt_log_debug2(NJT_LOG_DEBUG_HTTP, ev->log, 0,
                      "dump_restore::dump_header_read() name[%z]:\"%s\" failed",
                      len, file_header.name);
        njt_http_vhost_traffic_status_file_close(&file);
        return;
    }

    buf = njt_pcalloc(njt_cycle->pool, NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_DATA_BUF_SIZE);
    pad = njt_pcalloc(njt_cycle->pool, sizeof(NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_DATA_PAD));
    if (buf == NULL || pad == NULL) {
        njt_log_error(NJT_LOG_ALERT, ev->log, 0,
                      "dump_restore::njt_pcalloc() failed");
        njt_http_vhost_traffic_status_file_close(&file);
        return;
    }

    offset = n;

    for ( ;; ) {
        njt_memzero(buf, NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_DATA_BUF_SIZE);

        /* read: node */
        n = njt_read_file(&file, (u_char *) &vtsn,
                          sizeof(njt_http_vhost_traffic_status_node_t), offset);

        if (n == NJT_ERROR || n == 0
            || n != sizeof(njt_http_vhost_traffic_status_node_t)) {
            njt_log_debug1(NJT_LOG_DEBUG_HTTP, ev->log, 0,
                          "dump_restore::njt_read_file() node size:%z failed", n);
            break;
        }

        if (vtsn.len > NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_DATA_BUF_SIZE) {
            offset += vtsn.len + sizeof(NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_DATA_PAD);
            continue;
        }

        /* read: data */
        offset += n;
        n = njt_read_file(&file, buf, vtsn.len, offset);
        if (n != vtsn.len) {
            njt_log_debug2(NJT_LOG_DEBUG_HTTP, ev->log, 0,
                          "dump_restore::njt_read_file() read:%z, data:%z failed",
                          n, vtsn.len);
            break;
        }

        /* read: pad */
        offset += n;
        n = njt_read_file(&file, pad,
                          sizeof(NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_DATA_PAD),
                          offset);
        if (n == NJT_ERROR || n == 0
            || n != sizeof(NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_DATA_PAD))
        {
            njt_log_debug1(NJT_LOG_DEBUG_HTTP, ev->log, 0,
                          "dump_restore::njt_read_file() pad size:%z failed", n);
            break;
        }

        if (njt_memcmp(NJT_HTTP_VHOST_TRAFFIC_STATUS_DUMP_DATA_PAD, pad, n) != 0) {
            njt_log_debug0(NJT_LOG_DEBUG_HTTP, ev->log, 0,
                           "dump_restore::njt_read_file() pad does not match");
            break;
        }

        /* push: node */
        key.len = vtsn.len;
        key.data = buf;

        rc = njt_http_vhost_traffic_status_dump_restore_add_node(ev, &vtsn, &key);
        if (rc != NJT_OK) {
            njt_log_debug0(NJT_LOG_DEBUG_HTTP, ev->log, 0,
                           "dump_restore::dump_restore_add_node() failed");
            break;
        }

        offset += n;
    }

    njt_http_vhost_traffic_status_file_close(&file);
}

/* vi:set ft=c ts=4 sw=4 et fdm=marker: */