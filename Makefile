ASSETS=res
SOURCE=src/main.c
LIBS=src/libraylib.a
EMCC_FLAGS=-s USE_GLFW=3

RAYLIB_LOCATION=raylib/src
RAYLIB_SOURCE=rcore.c rshapes.c rtextures.c rtext.c utils.c raudio.c
RAYLIB_OBJECTS=rcore.o rshapes.o rtextures.o rtext.o utils.o raudio.o
LOCATED_RAYLIB_OBJECTS=$(addprefix $(RAYLIB_LOCATION)/, $(RAYLIB_OBJECTS))

src/libraylib.a: $(LOCATED_RAYLIB_OBJECTS)
	cd $(RAYLIB_LOCATION) && emar rcs $@ $(RAYLIB_OBJECTS) && cp libraylib.a ../../src

$(LOCATED_RAYLIB_OBJECTS): $(RAYLIB_SOURCE)
       cd $(RAYLIB_LOCATION) && emcc -Os -Wall -DPLATFORM_WEB -DGRAPHICS_API_OPENGL_ES2 $@

main.js: $(SOURCE) $(LIBS) $(ASSETS)/*
	emcc -I$(RAYLIB_LOCATION) $(EMCC_FLAGS) $(LIBS) $(SOURCE) -o $@ --preload-file $(ASSETS)
