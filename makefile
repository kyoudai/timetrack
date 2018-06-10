app = timetrack

ifdef SYSTEMROOT
	RM = del /Q
else
	RM = rm -f
endif

CXX = g++
CXXFLAGS = -std=c++11 -static-libgcc -static-libstdc++ -pedantic-errors
HEADERS = $(wildcard ./*.h)
SRC = $(wildcard ./*.cpp)
OBJ = $(SRC:.cpp=.o)
DEST = /usr/local/bin
OUT = ./$(app)

all: $(OUT)

# main target
$(OUT): $(OBJ)
		$(CXX) $(CXXFLAGS) -o $@ $^

# how to compile objects
./%.o: ./%.cpp ./%.h
		$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	$(RM) $(OUT) *.o *.exe

install:
	cp $(OUT) $(DEST)

.PHONY: clean
