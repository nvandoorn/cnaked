# cnaked

A snake that's so close to the metal that some say 6 CVEs have been opened since reading this.

## Status

Lots of headers, some tests, some coupling, not much implemented.

### To Be Implemented

1. (hash) Thread safe hash table
1. (graph) Threaded graph BFS
1. (server) HTTP server/routing
1. (parser) Fast "JSON" parser (it could potentially use magic indices and be super dumb but super fast)
1. (core) Generate graph based on `POST` request
1. (core) Tree shaking as the graph is being built (i.e don't add naive moves)
1. (core) Define thread communication (in particular, how does it pass back it's result?)

## Naming

C doesn't have namespaces so we have to get oddly specific about this.

### Rules

1. Use an include guard with a name obscure enough that it's probably OK
2. Libraries should use prefixed names following this style for all expose in header files: `<libname>-<routineName>`
3. Local routines/functions should use camel case
4. Any `struct`s or `enum`s used like types should end with `_t`

## Building

Building the main app: `make main`

Building and running the tests: `make test`

Kent Beck in my ear mode: `./naive-watch.sh`

## Testing

Write small unit tests with the routines in `test-lib.h` and use better languages for integration/e2e tests.

So far this is a little Node/TypeScript code for this, but it doesn't do anything yet.
