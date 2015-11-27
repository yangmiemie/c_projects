objects = lex.o calc.o parser.o

all: $(objects)
	cc -o calc $(objects) && rm $(objects)

calc.o: calc.c

parser.o: parser.h lex.h

lex.o: token.h

clean:
	rm $(objects)