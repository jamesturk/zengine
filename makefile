#Makefile for ZEngine

#defines the user shouldn't change#
include ./config
CFLAGS = -O2 $(WARN_LEVEL) -I./include $(SDL_INC_PATH) $(GL_INC_PATH) -L./lib $(SDL_LIB_PATH) $(GL_LIB_PATH)
LIB_OUT = ./lib/libZEngineS.a
ALL_TESTS = ZFontTest ZMouseTest ZMusicTest ZSoundTest ZTimerTest ZImageTest ZRectTest ZParticleTest

SOURCES = ./src/external/SDLGL_Util.cpp ./src/VersionInfo.cpp ./src/ZE_Utility.cpp \
	./src/ZE_ZClient.cpp ./src/ZE_ZConfigFile.cpp ./src/ZE_ZEngine.cpp  \
	./src/ZE_ZError.cpp ./src/ZE_ZFont.cpp ./src/ZE_ZImage.cpp ./src/ZE_ZMusic.cpp \
	./src/ZE_ZRandGen.cpp ./src/ZE_ZRect.cpp ./src/ZE_ZServer.cpp ./src/ZE_ZSound.cpp \
	./src/ZE_ZTimer.cpp ./src/external/physfsrwops.cpp
	
OBJECTS = SDLGL_Util.o VersionInfo.o ZE_Utility.o ZE_ZClient.o ZE_ZConfigFile.o \
	ZE_ZEngine.o ZE_ZError.o ZE_ZFont.o ZE_ZImage.o ZE_ZMusic.o ZE_ZRandGen.o ZE_ZRect.o \
	ZE_ZServer.o ZE_ZSound.o ZE_ZTimer.o physfsrwops.o

#build targets#

$(LIB_OUT): $(SOURCES)
	@echo Building $(BUILD_NAME)...
	$(CC) $(CFLAGS) -c $(SOURCES)
	$(AR) $(LIB_OUT) $(OBJECTS)
	@echo Built $(BUILD_NAME).

./test/bin/ZFontTest$(EXE) : $(LIB_OUT) ./test/ZFontTest.cpp
	@echo Building ZFontTest...
	$(CC) $(CFLAGS) ./test/ZFontTest.cpp -o ./test/bin/ZFontTest$(EXE) $(LIBS)
	@echo ZFontTest compiled.

./test/bin/ZMouseTest$(EXE) : $(LIB_OUT) ./test/ZMouseTest.cpp
	@echo Building ZMouseTest...
	$(CC) $(CFLAGS) ./test/ZMouseTest.cpp -o ./test/bin/ZMouseTest$(EXE) $(LIBS)
	@echo ZMouseTest compiled.

./test/bin/ZMusicTest$(EXE) : $(LIB_OUT) ./test/ZMusicTest.cpp
	@echo Building ZMusicTest...
	$(CC) $(CFLAGS) ./test/ZMusicTest.cpp -o ./test/bin/ZMusicTest$(EXE) $(LIBS)
	@echo ZMusicTest compiled.

./test/bin/ZSoundTest$(EXE) : $(LIB_OUT) ./test/ZSoundTest.cpp
	@echo Building ZSoundTest...
	$(CC) $(CFLAGS) ./test/ZSoundTest.cpp -o ./test/bin/ZSoundTest$(EXE) $(LIBS)
	@echo ZSoundTest compiled.

./test/bin/ZTimerTest$(EXE) : $(LIB_OUT) ./test/ZTimerTest.cpp
	@echo Building ZTimerTest...
	$(CC) $(CFLAGS) ./test/ZTimerTest.cpp -o ./test/bin/ZTimerTest$(EXE) $(LIBS)
	@echo ZTimerTest compiled.

./test/bin/ZImageTest$(EXE) : $(LIB_OUT) ./test/ZImageTest.cpp
	@echo Building ZImageTest...
	$(CC) $(CFLAGS) ./test/ZImageTest.cpp -o ./test/bin/ZImageTest$(EXE) $(LIBS)
	@echo ZImageTest compiled.

./test/bin/ZRectTest$(EXE) : $(LIB_OUT) ./test/ZRectTest.cpp
	@echo Building ZRectTest...
	$(CC) $(CFLAGS) ./test/ZRectTest.cpp -o ./test/bin/ZRectTest$(EXE) $(LIBS)
	@echo ZRectTest compiled.

./test/bin/ZParticleTest$(EXE) : $(LIB_OUT) ./test/ZParticleTest.cpp
	@echo Building ZParticleTest...
	$(CC) $(CFLAGS) ./test/ZParticleTest.cpp -o ./test/bin/ZParticleTest$(EXE) $(LIBS)
	@echo ZParticleTest compiled.

.PHONY: $(ALL_TESTS) tests all install clean veryclean

ZFontTest: ./test/bin/ZFontTest$(EXE)
ZMouseTest: ./test/bin/ZMouseTest$(EXE)
ZMusicTest: ./test/bin/ZMusicTest$(EXE)
ZSoundTest: ./test/bin/ZSoundTest$(EXE)
ZTimerTest: ./test/bin/ZTimerTest$(EXE)
ZImageTest: ./test/bin/ZImageTest$(EXE)
ZRectTest: ./test/bin/ZRectTest$(EXE)
ZParticleTest: ./test/bin/ZParticleTest$(EXE)

tests: $(ALL_TESTS)
all: $(LIB_OUT) $(ALL_TESTS)

install: $(LIB_OUT)
	mkdir -p $(INSTALL_INC)
	mkdir -p $(INSTALL_LIB)
	mkdir -p $(INSTALL_DOC)
	cp -r ./include/* $(INSTALL_INC)
	cp $(LIB_OUT) $(INSTALL_LIB)
	cp -r ./doc/html/* $(INSTALL_DOC)

clean:
	rm -f *.o
	@echo All object files removed.

veryclean:
	rm -f *.o
	rm -f ./test/bin/*.exe
	rm -f $(LIB_OUT)
	@echo All output files removed.
