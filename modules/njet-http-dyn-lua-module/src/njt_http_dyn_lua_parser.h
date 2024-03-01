

/* This file was generated by JSON Schema to C.
 * Any changes made to it will be lost on regeneration. 

 * Copyright (C) 2021-2023  TMLake(Beijing) Technology Co., Ltd.
 */

#ifndef PARSER_DYN_LUA_H
#define PARSER_DYN_LUA_H
#include <stdint.h>
#include <stdbool.h>
#include "njt_core.h"
#include "js2c_njet_builtins.h"
/* ===================== Generated type declarations ===================== */
typedef struct dynhttplua_locationDef_t_s dynhttplua_locationDef_t; //forward decl for public definition
typedef njt_str_t dynhttplua_locationDef_location_t;

typedef njt_str_t dynhttplua_locationDef_lua_content_by_t;

typedef njt_str_t dynhttplua_locationDef_lua_access_by_t;

typedef njt_str_t dynhttplua_locationDef_lua_log_by_t;

typedef struct dynhttplua_locationDef_lua_t_s {
    dynhttplua_locationDef_lua_content_by_t content_by;
    dynhttplua_locationDef_lua_access_by_t access_by;
    dynhttplua_locationDef_lua_log_by_t log_by;
    unsigned int is_content_by_set:1;
    unsigned int is_access_by_set:1;
    unsigned int is_log_by_set:1;
} dynhttplua_locationDef_lua_t;

typedef dynhttplua_locationDef_t dynhttplua_locationDef_locations_item_t; //ref def
typedef njt_array_t  dynhttplua_locationDef_locations_t;
typedef struct dynhttplua_locationDef_t_s {
    dynhttplua_locationDef_location_t location;
    dynhttplua_locationDef_lua_t *lua;
    dynhttplua_locationDef_locations_t *locations;
    unsigned int is_location_set:1;
    unsigned int is_lua_set:1;
    unsigned int is_locations_set:1;
} dynhttplua_locationDef_t;

dynhttplua_locationDef_lua_content_by_t* get_dynhttplua_locationDef_lua_content_by(dynhttplua_locationDef_lua_t *out);
dynhttplua_locationDef_lua_access_by_t* get_dynhttplua_locationDef_lua_access_by(dynhttplua_locationDef_lua_t *out);
dynhttplua_locationDef_lua_log_by_t* get_dynhttplua_locationDef_lua_log_by(dynhttplua_locationDef_lua_t *out);
dynhttplua_locationDef_locations_item_t* get_dynhttplua_locationDef_locations_item(dynhttplua_locationDef_locations_t *out, size_t idx);
dynhttplua_locationDef_location_t* get_dynhttplua_locationDef_location(dynhttplua_locationDef_t *out);
dynhttplua_locationDef_lua_t* get_dynhttplua_locationDef_lua(dynhttplua_locationDef_t *out);
// CHECK ARRAY not exceeding bounds before calling this func
dynhttplua_locationDef_locations_t* get_dynhttplua_locationDef_locations(dynhttplua_locationDef_t *out);
void set_dynhttplua_locationDef_location(dynhttplua_locationDef_t* obj, dynhttplua_locationDef_location_t* field);
void set_dynhttplua_locationDef_lua_content_by(dynhttplua_locationDef_lua_t* obj, dynhttplua_locationDef_lua_content_by_t* field);
void set_dynhttplua_locationDef_lua_access_by(dynhttplua_locationDef_lua_t* obj, dynhttplua_locationDef_lua_access_by_t* field);
void set_dynhttplua_locationDef_lua_log_by(dynhttplua_locationDef_lua_t* obj, dynhttplua_locationDef_lua_log_by_t* field);
dynhttplua_locationDef_lua_t* create_dynhttplua_locationDef_lua(njt_pool_t *pool);
void set_dynhttplua_locationDef_lua(dynhttplua_locationDef_t* obj, dynhttplua_locationDef_lua_t* field);
int add_item_dynhttplua_locationDef_locations(dynhttplua_locationDef_locations_t *src, dynhttplua_locationDef_locations_item_t* items);
dynhttplua_locationDef_locations_t* create_dynhttplua_locationDef_locations(njt_pool_t *pool, size_t nelts);
void set_dynhttplua_locationDef_locations(dynhttplua_locationDef_t* obj, dynhttplua_locationDef_locations_t* field);
dynhttplua_locationDef_t* create_dynhttplua_locationDef(njt_pool_t *pool);
typedef njt_str_t dynhttplua_servers_item_listens_item_t;

typedef njt_array_t  dynhttplua_servers_item_listens_t;
typedef njt_str_t dynhttplua_servers_item_serverNames_item_t;

typedef njt_array_t  dynhttplua_servers_item_serverNames_t;
typedef dynhttplua_locationDef_t dynhttplua_servers_item_locations_item_t; //ref def
typedef njt_array_t  dynhttplua_servers_item_locations_t;
typedef struct dynhttplua_servers_item_t_s {
    dynhttplua_servers_item_listens_t *listens;
    dynhttplua_servers_item_serverNames_t *serverNames;
    dynhttplua_servers_item_locations_t *locations;
    unsigned int is_listens_set:1;
    unsigned int is_serverNames_set:1;
    unsigned int is_locations_set:1;
} dynhttplua_servers_item_t;

typedef njt_array_t  dynhttplua_servers_t;
typedef struct dynhttplua_t_s {
    dynhttplua_servers_t *servers;
    unsigned int is_servers_set:1;
} dynhttplua_t;

dynhttplua_servers_item_listens_item_t* get_dynhttplua_servers_item_listens_item(dynhttplua_servers_item_listens_t *out, size_t idx);
dynhttplua_servers_item_serverNames_item_t* get_dynhttplua_servers_item_serverNames_item(dynhttplua_servers_item_serverNames_t *out, size_t idx);
dynhttplua_servers_item_locations_item_t* get_dynhttplua_servers_item_locations_item(dynhttplua_servers_item_locations_t *out, size_t idx);
// CHECK ARRAY not exceeding bounds before calling this func
dynhttplua_servers_item_listens_t* get_dynhttplua_servers_item_listens(dynhttplua_servers_item_t *out);
// CHECK ARRAY not exceeding bounds before calling this func
dynhttplua_servers_item_serverNames_t* get_dynhttplua_servers_item_serverNames(dynhttplua_servers_item_t *out);
// CHECK ARRAY not exceeding bounds before calling this func
dynhttplua_servers_item_locations_t* get_dynhttplua_servers_item_locations(dynhttplua_servers_item_t *out);
dynhttplua_servers_item_t* get_dynhttplua_servers_item(dynhttplua_servers_t *out, size_t idx);
// CHECK ARRAY not exceeding bounds before calling this func
dynhttplua_servers_t* get_dynhttplua_servers(dynhttplua_t *out);
int add_item_dynhttplua_servers_item_listens(dynhttplua_servers_item_listens_t *src, dynhttplua_servers_item_listens_item_t* items);
dynhttplua_servers_item_listens_t* create_dynhttplua_servers_item_listens(njt_pool_t *pool, size_t nelts);
void set_dynhttplua_servers_item_listens(dynhttplua_servers_item_t* obj, dynhttplua_servers_item_listens_t* field);
int add_item_dynhttplua_servers_item_serverNames(dynhttplua_servers_item_serverNames_t *src, dynhttplua_servers_item_serverNames_item_t* items);
dynhttplua_servers_item_serverNames_t* create_dynhttplua_servers_item_serverNames(njt_pool_t *pool, size_t nelts);
void set_dynhttplua_servers_item_serverNames(dynhttplua_servers_item_t* obj, dynhttplua_servers_item_serverNames_t* field);
int add_item_dynhttplua_servers_item_locations(dynhttplua_servers_item_locations_t *src, dynhttplua_servers_item_locations_item_t* items);
dynhttplua_servers_item_locations_t* create_dynhttplua_servers_item_locations(njt_pool_t *pool, size_t nelts);
void set_dynhttplua_servers_item_locations(dynhttplua_servers_item_t* obj, dynhttplua_servers_item_locations_t* field);
dynhttplua_servers_item_t* create_dynhttplua_servers_item(njt_pool_t *pool);
int add_item_dynhttplua_servers(dynhttplua_servers_t *src, dynhttplua_servers_item_t* items);
dynhttplua_servers_t* create_dynhttplua_servers(njt_pool_t *pool, size_t nelts);
void set_dynhttplua_servers(dynhttplua_t* obj, dynhttplua_servers_t* field);
dynhttplua_t* create_dynhttplua(njt_pool_t *pool);
dynhttplua_t* json_parse_dynhttplua(njt_pool_t *pool, const njt_str_t *json_string, js2c_parse_error_t *err_ret);
njt_str_t* to_json_dynhttplua(njt_pool_t *pool, dynhttplua_t *out, njt_int_t flags);
#endif /* PARSER_DYN_LUA_H */