GXX_LINUX=g++
GXX_WIN32=x86_64-w64-mingw32-g++
ARCH=$(shell getconf LONG_BIT)

all: clean main

clean:
	rm -f *.o main main.exe

main:
ifeq ($(OS),Windows_NT)
    ifeq ($(PROCESSOR_ARCHITECTURE),AMD64)
	    $(GXX_WIN32)  -g -o main.exe main.cpp -L ../lib/vcp-driver/amd64 -I ../include -static -l ftd2xx -l ws2_32 -D_WIN32_WINNT=0x0601
    else
	    $(GXX_WIN32) -g -o main.exe main.cpp -L ../lib/vcp-driver/i386 -I ../include -static -l ftd2xx -l ws2_32 -D_WIN32_WINNT=0x0601
    endif
else
	$(GXX_LINUX) -o main main.cpp -L . -l ftd2xx -I . -I ../include
endif