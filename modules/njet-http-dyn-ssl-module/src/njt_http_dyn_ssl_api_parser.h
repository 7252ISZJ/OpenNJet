

/* This file was generated by JSON Schema to C.
 * Any changes made to it will be lost on regeneration. 

 * Copyright (C) 2021-2023  TMLake(Beijing) Technology Co., Ltd.
 */

#ifndef PARSER_SSL_API_H
#define PARSER_SSL_API_H
#include <stdint.h>
#include <stdbool.h>
#include "njt_core.h"
#include "js2c_njet_builtins.h"
/* ===================== Generated type declarations ===================== */
typedef njt_str_t dyn_ssl_api_listens_item_t;

typedef njt_array_t  dyn_ssl_api_listens_t;
typedef njt_str_t dyn_ssl_api_serverNames_item_t;

typedef njt_array_t  dyn_ssl_api_serverNames_t;
typedef enum dyn_ssl_api_type_t_e{
    DYN_SSL_API_TYPE_ADD,
    DYN_SSL_API_TYPE_DEL
} dyn_ssl_api_type_t;

typedef enum dyn_ssl_api_cert_info_cert_type_t_e{
    DYN_SSL_API_CERT_INFO_CERT_TYPE_REGULAR,
    DYN_SSL_API_CERT_INFO_CERT_TYPE_NTLS
} dyn_ssl_api_cert_info_cert_type_t;

typedef njt_str_t dyn_ssl_api_cert_info_certificate_t;

typedef njt_str_t dyn_ssl_api_cert_info_certificateKey_t;

typedef njt_str_t dyn_ssl_api_cert_info_certificateEnc_t;

typedef njt_str_t dyn_ssl_api_cert_info_certificateKeyEnc_t;

typedef struct dyn_ssl_api_cert_info_t_s {
    dyn_ssl_api_cert_info_cert_type_t cert_type;
    dyn_ssl_api_cert_info_certificate_t certificate;
    dyn_ssl_api_cert_info_certificateKey_t certificateKey;
    dyn_ssl_api_cert_info_certificateEnc_t certificateEnc;
    dyn_ssl_api_cert_info_certificateKeyEnc_t certificateKeyEnc;
    unsigned int is_cert_type_set:1;
    unsigned int is_certificate_set:1;
    unsigned int is_certificateKey_set:1;
    unsigned int is_certificateEnc_set:1;
    unsigned int is_certificateKeyEnc_set:1;
} dyn_ssl_api_cert_info_t;

typedef struct dyn_ssl_api_t_s {
    dyn_ssl_api_listens_t *listens;
    dyn_ssl_api_serverNames_t *serverNames;
    dyn_ssl_api_type_t type;
    dyn_ssl_api_cert_info_t *cert_info;
    unsigned int is_listens_set:1;
    unsigned int is_serverNames_set:1;
    unsigned int is_type_set:1;
    unsigned int is_cert_info_set:1;
} dyn_ssl_api_t;

dyn_ssl_api_listens_item_t* get_dyn_ssl_api_listens_item(dyn_ssl_api_listens_t *out, size_t idx);
dyn_ssl_api_serverNames_item_t* get_dyn_ssl_api_serverNames_item(dyn_ssl_api_serverNames_t *out, size_t idx);
dyn_ssl_api_cert_info_cert_type_t get_dyn_ssl_api_cert_info_cert_type(dyn_ssl_api_cert_info_t *out);
dyn_ssl_api_cert_info_certificate_t* get_dyn_ssl_api_cert_info_certificate(dyn_ssl_api_cert_info_t *out);
dyn_ssl_api_cert_info_certificateKey_t* get_dyn_ssl_api_cert_info_certificateKey(dyn_ssl_api_cert_info_t *out);
dyn_ssl_api_cert_info_certificateEnc_t* get_dyn_ssl_api_cert_info_certificateEnc(dyn_ssl_api_cert_info_t *out);
dyn_ssl_api_cert_info_certificateKeyEnc_t* get_dyn_ssl_api_cert_info_certificateKeyEnc(dyn_ssl_api_cert_info_t *out);
// CHECK ARRAY not exceeding bounds before calling this func
dyn_ssl_api_listens_t* get_dyn_ssl_api_listens(dyn_ssl_api_t *out);
// CHECK ARRAY not exceeding bounds before calling this func
dyn_ssl_api_serverNames_t* get_dyn_ssl_api_serverNames(dyn_ssl_api_t *out);
dyn_ssl_api_type_t get_dyn_ssl_api_type(dyn_ssl_api_t *out);
dyn_ssl_api_cert_info_t* get_dyn_ssl_api_cert_info(dyn_ssl_api_t *out);
int add_item_dyn_ssl_api_listens(dyn_ssl_api_listens_t *src, dyn_ssl_api_listens_item_t* items);
dyn_ssl_api_listens_t* create_dyn_ssl_api_listens(njt_pool_t *pool, size_t nelts);
void set_dyn_ssl_api_listens(dyn_ssl_api_t* obj, dyn_ssl_api_listens_t* field);
int add_item_dyn_ssl_api_serverNames(dyn_ssl_api_serverNames_t *src, dyn_ssl_api_serverNames_item_t* items);
dyn_ssl_api_serverNames_t* create_dyn_ssl_api_serverNames(njt_pool_t *pool, size_t nelts);
void set_dyn_ssl_api_serverNames(dyn_ssl_api_t* obj, dyn_ssl_api_serverNames_t* field);
void set_dyn_ssl_api_type(dyn_ssl_api_t* obj, dyn_ssl_api_type_t field);
void set_dyn_ssl_api_cert_info_cert_type(dyn_ssl_api_cert_info_t* obj, dyn_ssl_api_cert_info_cert_type_t field);
void set_dyn_ssl_api_cert_info_certificate(dyn_ssl_api_cert_info_t* obj, dyn_ssl_api_cert_info_certificate_t* field);
void set_dyn_ssl_api_cert_info_certificateKey(dyn_ssl_api_cert_info_t* obj, dyn_ssl_api_cert_info_certificateKey_t* field);
void set_dyn_ssl_api_cert_info_certificateEnc(dyn_ssl_api_cert_info_t* obj, dyn_ssl_api_cert_info_certificateEnc_t* field);
void set_dyn_ssl_api_cert_info_certificateKeyEnc(dyn_ssl_api_cert_info_t* obj, dyn_ssl_api_cert_info_certificateKeyEnc_t* field);
dyn_ssl_api_cert_info_t* create_dyn_ssl_api_cert_info(njt_pool_t *pool);
void set_dyn_ssl_api_cert_info(dyn_ssl_api_t* obj, dyn_ssl_api_cert_info_t* field);
dyn_ssl_api_t* create_dyn_ssl_api(njt_pool_t *pool);
dyn_ssl_api_t* json_parse_dyn_ssl_api(njt_pool_t *pool, const njt_str_t *json_string, js2c_parse_error_t *err_ret);
njt_str_t* to_json_dyn_ssl_api(njt_pool_t *pool, dyn_ssl_api_t *out, njt_int_t flags);
#endif /* PARSER_SSL_API_H */