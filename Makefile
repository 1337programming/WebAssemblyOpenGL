CC = emcc
SRCS = main.c

FILES = $(addprefix src/c/, $(SRCS)) # Add 'src/' to each source
OBJS = $(FILES:.c=.o) # Modify file extensions of FILES
EOPT = USE_WEBGL2=1 FULL_ES3=1 USE_GLFW=3  # Emscripten specific options
EOPTS = $(addprefix -s $(EMPTY), $(EOPT))	# Add '-s ' to each option

# Builds necessary files
build: $(OBJS)
		mkdir build
		$(CC) $(FILES) -O3 $(EOPTS) -o build/module.js -s WASM=1 -Wall -s MODULARIZE=1
		$(CC) src/c/counter.c -O3 $(EOPTS) -s SIDE_MODULE=1 -s WASM=1 -o build/counter.wasm
		emcc src/c/engine.c -O3 -o build/engine.js -s WASM=1 -Wall -s MODULARIZE=1

# O3 is is a optimization setting
# WASM=1 means set web assembly to ture
# SIDE_MODULE=1 will only produce a wasm file, you have to build out your own integration
# MODULARIZE provides a ASM JS module we can interact with our client code, so we don't need to build any integration code from scratch

# Test run
test:
		emcc src/c/main.c -O3 $(EOPTS) -o build/index.html -s WASM=1

# Removes object files, but leaves build for serving
dist: build
		rm $(OBJS)

# Cleans up object files and build directory
clean:
		rm -rf build
		rm $(OBJS)
