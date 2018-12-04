app = timetrack

cat = $(if $(filter $(OS),Windows_NT),type,cat)
version = $(shell $(cat) VERSION)

CXX = g++
EXTRAFLAGS = -DVERSION="\"$(version)\""
HEADERS = $(wildcard ./*.h)
OBJ = $(SRC:.cpp=.o)
SRC = $(wildcard ./*.cpp)

ifdef OS
	CP = copy
	CXXFLAGS = -std=c++11 -static-libgcc -static-libstdc++ -pedantic-errors $(EXTRAFLAGS)
	DEST = $(shell echo %SYSTEMROOT%)
	OUT = .\$(app).exe
	RM = del /Q
else
	CP = cp
	CXXFLAGS = -std=c++11 -pedantic-errors $(EXTRAFLAGS)
	DEST = /usr/local/bin
	OUT = ./$(app)
	RM = rm -f
endif

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
