DIR = lexer_and_parser/
CC  = clang
CFLAGS = -Weverything
OBJECTS = meda_parser.o main.o meda_lexer.o literal.o variable.o

all: program clean

program: $(OBJECTS)
	$(CC) -g -o $@ $^ -lfl -ly

main.o: main.c
	$(CC) -g -c $(CFLAGS) $<

variable.o: table/variable.c
	$(CC) -g $(CFLAGS) -c $<

literal.o: table/literal.c
	$(CC) -g $(CFLAGS) -c $<

meda_parser.o: meda_parser.c
	$(CC) -g -c $<

meda_lexer.o: meda_lexer.c
	$(CC) -g -c $<

meda_parser.c: $(DIR)parser.c
	bison -d -o $@ $<

meda_lexer.c: $(DIR)lexer.c
	flex -o $@ $<

clean:
	rm -rf *.o
	rm -rf meda_lexer.c
	rm -rf meda_parser.c
	rm -rf meda_parser.h

run:
	./program

run_sc:
	./program hello.meda
