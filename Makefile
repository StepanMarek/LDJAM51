ASSETS=res
SOURCE=src/main.c src/game.c src/animation.c src/collisions.c src/boundedCamera.c
HEADERS=src/game.h src/animation.h src/collisions.h src/boundedCamera.h
LIBS=src/libraylib.a
EMCC_FLAGS=-s USE_GLFW=3

RAYLIB_LOCATION=raylib/src
RAYLIB_SOURCE=rcore.c rshapes.c rtextures.c rtext.c utils.c raudio.c
RAYLIB_OBJECTS=rcore.o rshapes.o rtextures.o rtext.o utils.o raudio.o
LOCATED_RAYLIB_OBJECTS=$(addprefix $(RAYLIB_LOCATION)/, $(RAYLIB_OBJECTS))

all: main.js

run: all
	./server.sh

main.js: $(SOURCE) $(LIBS) $(ASSETS)/* $(HEADERS)
	emcc -I$(RAYLIB_LOCATION) $(EMCC_FLAGS) $(LIBS) $(SOURCE) -o $@ --preload-file $(ASSETS)

src/libraylib.a: $(LOCATED_RAYLIB_OBJECTS)
	emar rcs $@ $^

$(RAYLIB_LOCATION)/%.o: $(RAYLIB_LOCATION)/%.c
	emcc -c -o $@ -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 $<
