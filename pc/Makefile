SRCDIR = src
SHARED = ../shared
CONNECTOR = banjo_tooie_connector
ifeq ($(OS),Windows_NT)
	CXX=x86_64-w64-mingw32-g++
	TARGET=$(CONNECTOR).exe
	CXXFLAGS = -D_WIN32_WINNT=0x0601
	LDFLAGS = -static
	LDFLAGS+= -l ws2_32
	LDFLAGS+= -l wsock32
else
	CXX=g++
	TARGET=$(CONNECTOR)
endif
CXXFLAGS+= -I src -I include -I ../shared/include
CXXFLAGS+= -std=c++20 -g
LDFLAGS += -L lib/vcp-driver/amd64 -L lib/vcp-driver/i386
LDFLAGS += -l ftd2xx

SOURCE = $(shell find $(SRCDIR)/ -type f -name '*.cpp')
OBJS = $(shell find $(SRCDIR)/ -type f -name '*.o')
DEPS = $(shell find $(SRCDIR)/ -type f -name '*.d')
CLEANUP = $(OBJS) $(DEPS)

$(TARGET): $(patsubst %.cpp,%.o,$(SOURCE))
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS)

include $(DEPS)

%.o: %.cpp
	$(CXX) -o $@ -c $< $(CXXFLAGS) -MMD

.PHONY: clean
clean:
	$(RM) $(CLEANUP)
