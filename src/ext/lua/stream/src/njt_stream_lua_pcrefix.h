
/*
 * !!! DO NOT EDIT DIRECTLY !!!
 * This file was automatically generated from the following template:
 *
 * src/subsys/njt_subsys_lua_pcrefix.h.tt2
 */


/*
 * Copyright (C) Xiaozhe Wang (chaoslawful)
 * Copyright (C) Yichun Zhang (agentzh)
 * Copyright (C) TMLake, Inc.
 */


#ifndef _NJT_STREAM_LUA_PCREFIX_H_INCLUDED_
#define _NJT_STREAM_LUA_PCREFIX_H_INCLUDED_


#include "njt_stream_lua_common.h"


#if (NJT_PCRE)
njt_pool_t *njt_stream_lua_pcre_malloc_init(njt_pool_t *pool);
void njt_stream_lua_pcre_malloc_done(njt_pool_t *old_pool);
#endif


#endif /* _NJT_STREAM_LUA_PCREFIX_H_INCLUDED_ */

/* vi:set ft=c ts=4 sw=4 et fdm=marker: */