CC=g++
CFLAGS=-O2 -W -Wall -I"/usr/include/SDL" -I"/home/James/ZEngine-dev/include" -L"/usr/lib/SDL" -L"/home/James/ZEngine-dev/lib"
LIBS=-lZEngineS -lSDL_mixer -lSDL_image -lSDL_ttf -lSDLmain -lSDL

ZEngineS.a: src/ZE_ZTimer.cpp src/ZE_ZImage.cpp src/ZE_ZFont.cpp src/ZE_ZMusic.cpp src/ZE_ZConfigFile.cpp src/ZE_ZSound.cpp src/ZE_ZMusic.cpp src/ZE_ZRect.cpp  src/ZE_Error.cpp src/ZE_ZEngine.cpp
	$(CC) $(CFLAGS) -c src/ZE_ZTimer.cpp src/ZE_ZImage.cpp src/ZE_ZFont.cpp src/ZE_ZMusic.cpp src/ZE_ZConfigFile.cpp src/ZE_ZSound.cpp src/ZE_ZMusic.cpp src/ZE_ZRect.cpp src/ZE_Error.cpp src/ZE_ZEngine.cpp
	ar rcs lib/libZEngineS.a ZE_ZTimer.o ZE_ZImage.o ZE_ZFont.o ZE_ZMusic.o ZE_ZConfigFile.o ZE_ZSound.o ZE_ZMusic.o ZE_Error.o ZE_ZRect.o ZE_ZEngine.o

tests: test/ZFontTest.cpp test/ZMouseTest.cpp test/ZMusicTest.cpp test/ZSoundTest.cpp test/ZTimerTest.cpp test/ZImageTest.cpp test/ZRectTest.cpp
	$(CC) $(CFLAGS) test/ZFontTest.cpp -o test/bin/ZFontTest  $(LIBS)
	$(CC) $(CFLAGS) test/ZMouseTest.cpp -o test/bin/ZMouseTest $(LIBS)
	$(CC) $(CFLAGS) test/ZMusicTest.cpp -o test/bin/ZMusicTest $(LIBS)
	$(CC) $(CFLAGS) test/ZSoundTest.cpp -o test/bin/ZSoundTest $(LIBS)
	$(CC) $(CFLAGS) test/ZTimerTest.cpp -o test/bin/ZTimerTest $(LIBS)
	$(CC) $(CFLAGS) test/ZImageTest.cpp -o test/bin/ZImageTest $(LIBS) 
	$(CC) $(CFLAGS) test/ZRectTest.cpp -o test/bin/ZRectTest $(LIBS)

.PHONY: clean

clean:
	rm *.o

