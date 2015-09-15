#SRC =
OBJ = $(SRC:.cpp=.o)
INCL = -I./src/
CFLAGS = -std=c++11 -Wunused-function -O3
TINCL = -I./tests/ -I./include/
TSRC = tests/matrix.cpp \
		tests/test.cpp


all: SICS

#$(OBJ): %.o : %.h

#.cpp.o:
#src/%.o: src/%.cpp
#	g++ $(CFLAGS) -Wall -c -I./src/ -o $@ $<

#SICS: $(OBJ)
#	g++ -Wall $(CFLAGS) -I./src/ $^ src/main.cpp -o $@
SICS:
	g++ -Wall $(CFLAGS) -I./src/ $^ src/main.cpp -o $@

#debug:
#	g++ $(CFLAGS) -ggdb -I./src/ -o SICS_dbg $(SRC) src/main.cpp

test:
	g++ $(TINCL) -o $@1  $(TSRC)
	./test1

clean:
	rm test1 SICS $(OBJ)

ciconf:
	gcc --version
	g++ --version
	alias
	export CXX="g++-4.8" CC="gcc-4.8"
	alias gcc='gcc-4.8'
	alias cc='gcc-4.8'
	alias g++='g++-4.8'
	alias c++='c++-4.8'
	gcc --version
	g++ --version
