#SRC =
OBJ = $(SRC:.cpp=.o)
INCL = -I./src/
CFLAGS = -std=c++11 -Wunused-function -O3

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
