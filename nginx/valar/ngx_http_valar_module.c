/*
 * Copyright (C) Bo Cai
 * Copyright (C) Fugle, Inc.
 */


#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_http.h>

static char* ngx_http_valar_init(ngx_conf_t *conf, ngx_command_t *cmd , void *cf);


static ngx_command_t ngx_http_valar_command[] = {
    { ngx_string("valar"),
      NGX_HTTP_MAIN_CONF|NGX_HTTP_SRV_CONF|NGX_HTTP_LOC_CONF|NGX_CONF_NOARGS,
      ngx_http_valar_init,
      NGX_HTTP_LOC_CONF_OFFSET,
      0,
      NULL },
      
      ngx_null_command
};

// 模块上下文
static ngx_http_module_t ngx_http_valar_module_ctx = {
        NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL
};

// 模块入口
ngx_module_t ngx_http_valar_module = {
    NGX_MODULE_V1, // 前置填充
	&ngx_http_valar_module_ctx,     /* 模块的上下文 */
	ngx_http_valar_command,         /* 模块的指令   */
	NGX_HTTP_MODULE,				/* 指定模块类型 */
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NGX_MODULE_V1_PADDING	
};

ngx_int_t ngx_http_valar_handler(ngx_http_request_t *request) {
	ngx_log_error(NGX_LOG_ERR,request->connection->log, 0, "valar module have been called!");
	return NGX_HTTP_NOT_ALLOWED;
}


// 将模块挂载到http content parse阶段
static char* ngx_http_valar_init(ngx_conf_t *conf, ngx_command_t *cmd, void *cf) {
	ngx_http_core_loc_conf_t *clcf;
	
	clcf = ngx_http_conf_get_module_loc_conf(conf, ngx_http_core_module);
	if ( clcf == NULL ) {
	    return NGX_CONF_ERROR;
	}
		
	return NGX_CONF_OK;
}




