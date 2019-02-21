#ifndef CNAKE_SERVER_H
#define CNAKE_SERVER_H

struct server_Ctx_t {
  int port;
};

struct server_Req_t {
  char *body;
  int status;
};

struct server_Res_t {
  int (*write)(char *resBody, int status);
};

typedef void (*server_Callback_t)(struct server_Req_t *req,
                                  struct server_Res_t *res, void *ctx);

/**
 * Start the HTTP server
 *
 * Return a non-zero value on error,
 * error codes to come
 */
int server_start(struct server_Ctx_t *ctx);

/*
 * void myFunction(ServerRequest_t* req, ServerResponse_t* res) {
 *   res->write("nice work", HTTP_OK);
 * }
 * int res = server_attachRouteHandler("/move", myFunction)
 */
int server_attachRouteHandler(char *route, server_Callback_t handler,
                              void *ctx);

#endif
