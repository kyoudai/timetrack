app = timetrack

ifdef OS
	CP = copy
	CXXFLAGS = -std=c++11 -static-libgcc -static-libstdc++ -pedantic-errors
	DEST = $(shell echo %SYSTEMROOT%)
	OUT = .\$(app).exe
	RM = del /Q
else
	CP = cp
	CXXFLAGS = -std=c++11 -pedantic-errors
	DEST = /usr/local/bin
	OUT = ./$(app)
	RM = rm -f
endif

CXX = g++
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
	@echo installing to $(DEST)
	$(CP) $(OUT) $(DEST)

.PHONY: clean
