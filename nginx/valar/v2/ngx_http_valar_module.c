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


ngx_module_t ngx_http_valar_module = {
        NGX_MODULE_V1,
	&ngx_http_valar_module_ctx, 
	ngx_http_valar_command,      
	NGX_HTTP_MODULE,	
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NGX_MODULE_V1_PADDING	
};

ngx_int_t ngx_http_valar_handler(ngx_http_request_t *r) {
	
	ngx_log_error(NGX_LOG_ERR, r->connection->log, 0, "valar module have been called!");
	if ((r->method & (NGX_HTTP_GET | NGX_HTTP_POST)) == 0) {
		return NGX_HTTP_NOT_ALLOWED;
	}
	ngx_int_t rc = ngx_http_discard_request_body(r);
	if (rc != NGX_OK) {
		return rc;
	}

	ngx_str_t type = ngx_string("text/plain");
	ngx_str_t response = ngx_string("this is valar module, what I want to say is: hello world!");
	r->headers_out.status = NGX_HTTP_OK;
	r->headers_out.content_type = type;
	r->headers_out.content_length_n = response.len;

	rc = ngx_http_send_header(r);
	if (rc == NGX_ERROR || rc > NGX_OK || r->header_only) {
		return rc;
	}

	ngx_buf_t *b;
	b = ngx_create_temp_buf(r->pool, response.len);
	if (b == NULL) {
		return NGX_HTTP_INTERNAL_SERVER_ERROR;
	}
	ngx_memcpy(b->pos, response.data, response.len);
	b->last = b->pos + response.len;
	// this is the last buffer
	b->last_buf = 1;

	ngx_chain_t out;
	out.buf = b;
	out.next = NULL;	
	return ngx_http_output_filter( r, &out);
}


static char* ngx_http_valar_init(ngx_conf_t *conf, ngx_command_t *cmd, void *cf) {

	ngx_http_core_loc_conf_t *clcf;
	clcf = ngx_http_conf_get_module_loc_conf(conf, ngx_http_core_module);
	if (clcf == NULL) {
		return NGX_CONF_ERROR;
	}
	clcf->handler = ngx_http_valar_handler;
	return NGX_CONF_OK;
}




