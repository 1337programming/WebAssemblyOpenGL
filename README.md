# WebAssembly & OpenGL (WIP)

This is a boilerplate example of how to port over a typical OpenGL project with Emscripten to produce a .wasm file for browsers.

# Compilation and Serving

- Follow the steps [here](http://webassembly.org/getting-started/developers-guide/) to get ready to comile WebAssembly
- Git Clone
- `cd` to the root of the newly cloned directory
- Use the makefile to either build, clean up, or make a distribution version (build directory only) of the repo
    - Build: `make`
    - Clean: `make clean`
    - Build, but remove objects leaving the `build` dir: `make dist`
- `npm run start` to serve demo
