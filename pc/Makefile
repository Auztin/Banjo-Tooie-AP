ifeq ($(OS),Windows_NT)
	CXX=x86_64-w64-mingw32-g++
	TARGET=main.exe
	CXXFLAGS = -D_WIN32_WINNT=0x0601
	LDFLAGS = -static
	LDFLAGS+= -l ws2_32
	LDFLAGS+= -l wsock32
else
	CXX=g++
	TARGET=main
endif
CXXFLAGS+= -I src -I include -I ../include
CXXFLAGS+= -std=c++20 -g
LDFLAGS += -L lib/vcp-driver/amd64 -L lib/vcp-driver/i386
LDFLAGS += -l ftd2xx
OBJS = $(patsubst %.cpp,%.o,$(shell find src/ -type f -name '*.cpp'))

all: clean .WAIT main

%.o: %.cpp
	$(CXX) -c $< -o $@ $(CXXFLAGS)

main: $(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -f $(TARGET) $(OBJS)
