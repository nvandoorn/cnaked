# cnaked

A snake that's so close to the metal that some say 6 CVEs have been opened since reading this.

## Status

Lots of headers, some tests, some coupling, not much implemented.

### Journal

#### 2am Saturday Feb 23

Ahhh yes, that part of the project where you see the promise but also the headaches. The parser is going OK assuming I can get cJSON to compile properly (dick around with cmake). After that I should implement the HTTP layer. Those should both be relatively straight forward to implement. After that I need to figure out why the hash table isnt so thread safe despite using a mutex to lock it. Finally, figure out how implement a threaded BFS.

Assuming I can figure out and test all of the "internals" listed above, that still leaves the actual algorithm that pieces all of these things together. I think it should go like this.

1. Transform the HTTP request into a complete `struct GameState_t` (core -> http -> parser -> core)
1. Build the graph of all moves reachable from the current state. (core -> graph -> hash).
1. Recurse on this graph as deeply as possible using a breadth first search (as implemented by the graph module). This traversal should be threaded if possible, and each thread should stop recursing if the path is deemed undesirable.
1. All paths that are desirable recurse infinitely, stopping only for a timeout.
1. These paths should be tracked somehow to avoid running a path finder after the fact.

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
