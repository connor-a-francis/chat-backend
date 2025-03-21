# chat-backend

## Dependencies:

- C++ compiler
- CMake
- `libsqlite3-dev`

## First build commands

- `git submodule update --init --recursive` </br>
This pulls down submodules in the `external` directory that we need to build the server </br>
- `mkdir build && cd build && cmake .. && make` </br>
This generates our MakeFile and builds against it, giving us a single binary to run! </br>
Subsequent runs can just use `make` while in the build directory.

## Running the tests:
- `make && ctest`
