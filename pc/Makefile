GXX_LINUX=g++
GXX_WIN32=x86_64-w64-mingw32-g++

all: clean main

clean:
	rm -f *.o main main.exe

main:
ifeq ($(OS),Windows_NT)
	$(GXX_WIN32) -o main.exe main.cpp -L . -l ftd2xx -I . -I ../include -static -l ws2_32 -D_WIN32_WINNT=0x0601
else
	$(GXX_LINUX) -o main main.cpp -L . -l ftd2xx -I . -I ../include
endif
