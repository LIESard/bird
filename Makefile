CC=g++
INCDIR=include
SRCDIR=src
FLAGS=-Wall -Werror -std=c++14 -c -g
LIBS=-lglfw -lGLEW -lGL
INC=-I$(INCDIR)
SRC=$(wildcard $(SRCDIR)/*.cpp)
OBJS=$(notdir $(SRC:.cpp=.o))
OUT=bird

all: $(OUT)

$(OUT): $(OBJS)
	$(CC) $(OBJS) -o $(OUT) $(LIBS)

%.o: $(SRCDIR)/%.cpp
	$(CC) $(FLAGS) $(INC) $<

debug:
	rm -f *.trace
	gdb ./$(OUT)
	apitrace trace ./$(OUT)
	qapitrace $(OUT).trace

clean:
	rm -f $(OUT) $(OBJS) *.trace
