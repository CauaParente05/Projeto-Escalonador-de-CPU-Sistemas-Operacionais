all: rate edf

rate: objects/main.o objects/tasks.o
	gcc objects/main.o objects/tasks.o -o rate -Wall -Wextra -g

edf: objects/edf.o objects/tasks.o
	gcc objects/edf.o objects/tasks.o -o edf -Wall -Wextra -g

objects/main.o: source/main.c source/tasks.h
	gcc -c source/main.c -o objects/main.o -Wall -Wextra -g

objects/edf.o: source/edf.c source/tasks.h
	gcc -c source/edf.c -o objects/edf.o -Wall -Wextra -g

objects/tasks.o: source/tasks.c source/tasks.h
	gcc -c source/tasks.c -o objects/tasks.o -Wall -Wextra -g

clean:
	rm -f objects/*.o rate edf *.out

.PHONY: clean all