#Makefile for ZEngine

ZE = .
include $(ZE)/config

LIB_OUT = $(ZE)/lib/libZEngineS.a

LIB_SOURCES = $(SRC)/external/SDLGL_Util.cpp $(SRC)/VersionInfo.cpp $(SRC)/ZE_Utility.cpp \
	$(SRC)/ZE_ZClient.cpp $(SRC)/ZE_ZConfigFile.cpp $(SRC)/ZE_ZEngine.cpp  \
	$(SRC)/ZE_ZError.cpp $(SRC)/ZE_ZFont.cpp $(SRC)/ZE_ZImage.cpp $(SRC)/ZE_ZMusic.cpp \
	$(SRC)/ZE_ZRandGen.cpp $(SRC)/ZE_ZRect.cpp $(SRC)/ZE_ZServer.cpp $(SRC)/ZE_ZSound.cpp \
	$(SRC)/ZE_ZTimer.cpp $(SRC)/external/physfsrwops.cpp
	
LIB_OBJECTS = SDLGL_Util.o VersionInfo.o ZE_Utility.o ZE_ZClient.o ZE_ZConfigFile.o \
	ZE_ZEngine.o ZE_ZError.o ZE_ZFont.o ZE_ZImage.o ZE_ZMusic.o ZE_ZRandGen.o ZE_ZRect.o \
	ZE_ZServer.o ZE_ZSound.o ZE_ZTimer.o physfsrwops.o

#build targets#

libZEngineS.a: $(SOURCES)
	$(CC) $(CFLAGS) -c $(LIB_SOURCES)
	$(AR) $(LIB_OUT) $(LIB_OBJECTS)

tests: $(TEST)/ZFontTest.cpp $(TEST)/ZMouseTest.cpp $(TEST)/ZMusicTest.cpp $(TEST)/ZSoundTest.cpp \
	   $(TEST)/ZTimerTest.cpp $(TEST)/ZImageTest.cpp $(TEST)/ZRectTest.cpp $(TEST)/ZParticleTest.cpp
	$(CC) $(CFLAGS) -L$(ZE)/lib $(TEST)/ZFontTest.cpp -o $(TEST)/bin/ZFontTest  $(LIBS)
	$(CC) $(CFLAGS) -L$(ZE)/lib $(TEST)/ZMouseTest.cpp -o $(TEST)/bin/ZMouseTest $(LIBS)
	$(CC) $(CFLAGS) -L$(ZE)/lib $(TEST)/ZMusicTest.cpp -o $(TEST)/bin/ZMusicTest $(LIBS)
	$(CC) $(CFLAGS) -L$(ZE)/lib $(TEST)/ZSoundTest.cpp -o $(TEST)/bin/ZSoundTest $(LIBS)
	$(CC) $(CFLAGS) -L$(ZE)/lib $(TEST)/ZTimerTest.cpp -o $(TEST)/bin/ZTimerTest $(LIBS)
	$(CC) $(CFLAGS) -L$(ZE)/lib $(TEST)/ZImageTest.cpp -o $(TEST)/bin/ZImageTest $(LIBS) 
	$(CC) $(CFLAGS) -L$(ZE)/lib $(TEST)/ZRectTest.cpp -o $(TEST)/bin/ZRectTest $(LIBS)
	$(CC) $(CFLAGS) -L$(ZE)/lib $(TEST)/ZParticleTest.cpp -o $(TEST)/bin/ZParticleTest $(LIBS)

install: $(LIB_OUT)
	mkdir -p $(INSTALL_ROOT)
	mkdir -p $(INSTALL_INC)
	mkdir -p $(INSTALL_LIB)
	mkdir -p $(INSTALL_DOC)
	cp -r $(ZE)/include/* $(INSTALL_INC)
	cp $(LIB_OUT) $(INSTALL_LIB)
	cp -r $(ZE)/doc/html/* $(INSTALL_DOC)
	

.PHONY: clean veryclean

clean:
	rm -f *.o

veryclean:
	rm -f *.o
	rm -f $(TEST)/bin/*.exe
	rm -f $(LIB_OUT)