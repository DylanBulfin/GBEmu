PROJECT=emulator.out
SOURCES=src/main.c src/cpu/load.c src/cpu/util.c src/cpu/disassembler.c src/cpu/arrays.c src/cpu/arithmetic.c src/cpu/rotations_extensions.c src/cpu/control_flow.c src/cpu/misc.c src/timing/clock.c src/timing/display.c src/interrupts/interrupts.c src/cpu/memory.c src/startup.c src/cpu/cpu.c src/graphics/graphics.c src/graphics/background.c src/timing/waiting.c src/input/input.c src/timing/timer.c src/graphics/sprites.c src/cartridge/cartridge.c src/graphics/window.c src/sound/sound.c src/settings.c
LIBRARY=nope
INCPATHS=
LIBPATHS=
CFLAGS=-c -Wall -O3 -g
CC=gcc

ifdef OS
RM = del /Q
LDFLAGS=-lmingw32 -lSDL2main -lSDL2 -lm
PAPATH=libportaudio.dll.a
else
RM = rm -f
LDFLAGS=-lSDL2main -lSDL2 -lm -lpthread -lasound
PAPATH=libportaudio.a
endif


# ------------ MAGIC BEGINS HERE -------------

# Automatic generation of some important lists
OBJECTS=$(SOURCES:.c=.o)
INCFLAGS=$(foreach TMP,$(INCPATHS),-I$(TMP))
LIBFLAGS=$(foreach TMP,$(LIBPATHS),-L$(TMP))

# Set up the output file names for the different output types
ifeq "$(LIBRARY)" "shared"
    BINARY=lib$(PROJECT).so
    LDFLAGS += -shared
else ifeq "$(LIBRARY)" "static"
    BINARY=lib$(PROJECT).a
else
    BINARY=$(PROJECT)
endif

all: $(SOURCES) $(BINARY)

$(BINARY): $(OBJECTS)
    # Link the object files, or archive into a static library
    ifeq "$(LIBRARY)" "static"
        ar rcs $(BINARY) $(OBJECTS)
    else
	$(CC) $(LIBFLAGS) $(OBJECTS) $(LDFLAGS) $(PAPATH) -o $@
    endif

.c.o:
	$(CC) $(INCFLAGS) $(CFLAGS) -fPIC $< -o $@

distclean: clean
	$(RM) $(BINARY)

clean:
    ifdef OS
	$(RM) $(subst /,\,$(OBJECTS))
    else
	$(RM) $(OBJECTS)
    endif
