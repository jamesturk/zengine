#Makefile for ZEngine

ZE = .
include $(ZE)/config

LIB_OUT=$(ZE)/lib/libZEngineS.a

libZEngineS.a: $(SRC)/ZE_ZTimer.cpp $(SRC)/ZE_ZImage.cpp $(SRC)/ZE_ZFont.cpp $(SRC)/ZE_ZMusic.cpp $(SRC)/ZE_ZConfigFile.cpp $(SRC)/ZE_ZSound.cpp $(SRC)/ZE_ZMusic.cpp $(SRC)/ZE_ZRect.cpp  $(SRC)/ZE_Error.cpp $(SRC)/ZE_ZEngine.cpp $(SRC)/external/SDLGL_Util.cpp
	$(CC) $(CFLAGS) -c $(SRC)/ZE_ZTimer.cpp $(SRC)/ZE_ZImage.cpp $(SRC)/ZE_ZFont.cpp $(SRC)/ZE_ZMusic.cpp $(SRC)/ZE_ZConfigFile.cpp $(SRC)/ZE_ZSound.cpp $(SRC)/ZE_ZMusic.cpp $(SRC)/ZE_ZRect.cpp $(SRC)/ZE_Error.cpp $(SRC)/ZE_ZEngine.cpp $(SRC)/external/SDLGL_Util.cpp
	$(AR) $(LIB_OUT) ZE_ZTimer.o ZE_ZImage.o ZE_ZFont.o ZE_ZMusic.o ZE_ZConfigFile.o ZE_ZSound.o ZE_ZMusic.o ZE_Error.o ZE_ZRect.o ZE_ZEngine.o SDLGL_Util.o

tests: $(TEST)/ZFontTest.cpp $(TEST)/ZMouseTest.cpp $(TEST)/ZMusicTest.cpp $(TEST)/ZSoundTest.cpp $(TEST)/ZTimerTest.cpp $(TEST)/ZImageTest.cpp $(TEST)/ZRectTest.cpp
	$(CC) $(CFLAGS) -L$(ZE)/lib $(TEST)/ZFontTest.cpp -o $(TEST)/bin/ZFontTest  $(LIBS)
	$(CC) $(CFLAGS) -L$(ZE)/lib $(TEST)/ZMouseTest.cpp -o $(TEST)/bin/ZMouseTest $(LIBS)
	$(CC) $(CFLAGS) -L$(ZE)/lib $(TEST)/ZMusicTest.cpp -o $(TEST)/bin/ZMusicTest $(LIBS)
	$(CC) $(CFLAGS) -L$(ZE)/lib $(TEST)/ZSoundTest.cpp -o $(TEST)/bin/ZSoundTest $(LIBS)
	$(CC) $(CFLAGS) -L$(ZE)/lib $(TEST)/ZTimerTest.cpp -o $(TEST)/bin/ZTimerTest $(LIBS)
	$(CC) $(CFLAGS) -L$(ZE)/lib $(TEST)/ZImageTest.cpp -o $(TEST)/bin/ZImageTest $(LIBS) 
	$(CC) $(CFLAGS) -L$(ZE)/lib $(TEST)/ZRectTest.cpp -o $(TEST)/bin/ZRectTest $(LIBS)

install: $(LIB_OUT)
	mkdir -p $(INSTALL_ROOT)
	mkdir -p $(INSTALL_INC)
	mkdir -p $(INSTALL_LIB)
	mkdir -p $(INSTALL_DOC)
	cp -r $(ZE)/include/* $(INSTALL_INC)
	cp $(LIB_OUT) $(INSTALL_LIB)
	cp -r $(ZE)/doc/html/* $(INSTALL_DOC)
	

.PHONY: clean

clean:
	rm *.o



