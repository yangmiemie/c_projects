objects = lex.o test_lex.o test.o

all: $(objects)
	cc -o test $(objects) && rm $(objects)

test.o: test.h

test_lex.o: test_lex.h

lex.o: ../src/lex.h ../src/token.h
	cc -c ../src/lex.c

clean:
	rm $(objects)