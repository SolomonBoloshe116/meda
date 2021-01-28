DIR = lexer_and_parser/
CC  = clang
CFLAGS = -Weverything
OBJECTS = meda_parser.o main.o meda_lexer.o assignment_table.o

all: program clean

program: $(OBJECTS)
	$(CC) -g -o $@ $^ -lfl

main.o: main.c
	$(CC) -g -c $<

assignment_table.o: table/assignment_table.c
	$(CC) $(CFLAGS) -g -c $<

meda_parser.o: meda_parser.c
	$(CC) -g -c $<

meda_lexer.o: meda_lexer.c
	$(CC) -g -c $<

meda_parser.c: $(DIR)parser.c
	bison -d -o $@ $^

meda_lexer.c: $(DIR)lexer.c
	flex -o $@ $^

clean:
	rm -rf *.o
	rm -rf meda_lexer.c
	rm -rf meda_parser.c
	rm -rf meda_parser.h
	# clear

run:
	./program $<

