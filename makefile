#Makefile for ZEngine

include $(CURDIR)/config
#defines the user shouldn't change#
INCLUDES = -I$(CURDIR)/include $(SDL_INC_PATH) $(GL_INC_PATH)
LIBRARIES = -L$(CURDIR)/lib $(SDL_LIB_PATH) $(GL_LIB_PATH)
CFLAGS = $(EXTRA_OPTIONS) $(WARN_LEVEL) $(INCLUDES) $(LIBRARIES)
LIB_OUT = $(CURDIR)/lib/libZEngineS.a
ALL_TESTS = ZFontTest ZMouseTest ZMusicTest ZSoundTest ZTimerTest ZImageTest ZRectTest ZParticleTest

%.o: $(CURDIR)/src/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

%.o: $(CURDIR)/src/external/%.cpp
	$(CC) $(CFLAGS) -c $< -o $@

SOURCES = $(wildcard $(CURDIR)/src/external/*.cpp) \
	  $(wildcard $(CURDIR)/src/*.cpp)

#SOURCES with path stripped and .cpp changed to .o
OBJECTS = $(notdir $(SOURCES:.cpp=.o))

#build targets#

all: $(LIB_OUT) tests
tests: $(ALL_TESTS)

$(LIB_OUT): $(OBJECTS)
	@echo Building $(BUILD_NAME)...
	$(AR) $(LIB_OUT) $(OBJECTS)
	@echo Built $(BUILD_NAME).

$(ALL_TESTS) : $(LIB_OUT)
	@echo Building $@...
	$(CC) $(CFLAGS) $(CURDIR)/test/$@.cpp -o $(CURDIR)/test/bin/$@ $(LIBS)
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

