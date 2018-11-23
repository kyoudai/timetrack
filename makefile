app = timetrack

ifdef OS
	RM = del /Q
	CP = copy
	OUT = .\$(app).exe
	DEST = $(SYSTEMROOT) # todo: fix
else
	CP = cp
	RM = rm -f
	OUT = ./$(app)
	DEST = /usr/local/bin
endif

CXX = g++
CXXFLAGS = -std=c++11 -static-libgcc -static-libstdc++ -pedantic-errors
HEADERS = $(wildcard ./*.h)
SRC = $(wildcard ./*.cpp)
OBJ = $(SRC:.cpp=.o)

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
	$(CP) $(OUT) $(DEST)

.PHONY: clean
