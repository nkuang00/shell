all: exec_cmd.o parse_args.o main.o
	gcc -o program exec_cmd.o parse_args.o main.o

main.o: main.c parse_args.h exec_cmd.h
	gcc -c main.c

parse_args.o: parse_args.c parse_args.h exec_cmd.h
	gcc -c parse_args.c

exec_cmd.o: exec_cmd.c exec_cmd.h
	gcc -c exec_cmd.c

run:
	./program

clean:
	rm *.o
	rm *~
