#ifndef CNAKE_SERVER_H
#define CNAKE_SERVER_H

struct ServerContext_t {
  int port;
};

struct ServerRequest_t {
  char* body;
  int status;
};

struct ServerResponse_t {
  int (*write)(char* resBody, int status);
};

typedef void (*ServerCallBack_t)(struct ServerRequest_t *req,
                                 struct ServerResponse_t *res);

/**
 * Start the HTTP server
 *
 * Return a non-zero value on error,
 * error codes to come
 */
int server_start(ServerContext_t *ctx);

/*
 * void myFunction(ServerRequest_t* req, ServerResponse_t* res) {
 *   res->write("nice work", HTTP_OK);
 * }
 * int res = server_attachRouteHandler("/move", myFunction)
 */
int server_attachRouteHandler(char *route, ServerCallBack_t handler);

#endif
