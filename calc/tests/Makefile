objects = lex.o test_lex.o test_parser.o test.o parser.o

all: $(objects)
	cc -o test $(objects) && rm $(objects)

test.o: test.h

test_lex.o: test_lex.h

test_parser.o: test_parser.h

parser.o: ../src/parser.h ../src/lex.h
	cc -c ../src/parser.c ../src/lex.c

lex.o: ../src/lex.h ../src/token.h
	cc -c ../src/lex.c

clean:
	rm $(objects)