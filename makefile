#Makefile for ZEngine
#Created and maintained by James Turk
#Incremental build optimizations submitted by Atani

include $(CURDIR)/config
#defines the user shouldn't change#
INCLUDES = -I$(CURDIR)/include $(SDL_INC_PATH) $(GL_INC_PATH)
LIBRARIES = -L$(CURDIR)/lib $(SDL_LIB_PATH) $(GL_LIB_PATH)
CPPFLAGS = $(EXTRA_OPTIONS) $(WARN_LEVEL) $(INCLUDES) $(LIBRARIES)
CFLAGS = -w
LIB_OUT = $(CURDIR)/lib/libZEngineS.a
ALL_TESTS = ZFontTest ZMouseTest ZMusicTest ZSoundTest ZTimerTest ZImageTest ZRectTest ZParticleTest

%.o: $(CURDIR)/src/%.cpp
	$(CPPC) $(CPPFLAGS) -c $< -o $@

%.o: $(CURDIR)/src/external/%.cpp
	$(CPPC) $(CPPFLAGS) -c $< -o $@

%.o: $(CURDIR)/zlib/%.c
	$(CC) $(CFLAGS) -c $< -o $@

CPP_SOURCES = $(wildcard $(CURDIR)/src/external/*.cpp) \
	  $(wildcard $(CURDIR)/src/*.cpp) 
C_SOURCES = $(wildcard $(CURDIR)/zlib/*.c)

#sources with path stripped and .cpp changed to .o
OBJECTS = $(notdir $(CPP_SOURCES:.cpp=.o)) $(notdir $(C_SOURCES:.c=.o))

#build targets#

all: $(LIB_OUT) tests
tests: $(ALL_TESTS)

$(LIB_OUT): $(OBJECTS)
	@echo Building $(BUILD_NAME)...
	$(AR) $(LIB_OUT) $(OBJECTS)
	@echo Built $(BUILD_NAME).

$(ALL_TESTS) : $(LIB_OUT)
	@echo Building $@...
	$(CPPC) $(CPPFLAGS) $(CURDIR)/test/$@.cpp -o $(CURDIR)/test/bin/$@ $(LIBS)
	@echo $@ compiled.

.PHONY: $(ALL_TESTS) install clean veryclean

install: $(LIB_OUT)
	mkdir -p $(INSTALL_INC)
	mkdir -p $(INSTALL_LIB)
	mkdir -p $(INSTALL_DOC)
	cp -r $(CURDIR)/include/* $(INSTALL_INC)
	cp $(LIB_OUT) $(INSTALL_LIB)
	cp -r $(CURDIR)/doc/html/* $(INSTALL_DOC)

clean:
	rm -f $(OBJECTS)
	@echo All object files removed.

veryclean:
	rm -f $(OBJECTS)
	rm -f $(CURDIR)/test/bin/Z* 
	rm -f $(LIB_OUT)
	@echo All output files removed.

