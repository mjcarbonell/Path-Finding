CC = clang 
CFLAGS = -Wall -Wextra -Werror -Wpedantic -g

all: tsp 

tsp: tsp.o graph.o stack.o path.o
	$(CC) -o tsp tsp.o graph.o stack.o path.o -lm

graph.o: graph.c
	$(CC) $(CFLAGS) -c graph.c
stack.o: stack.c
	$(CC) $(CFLAGS) -c stack.c
path.o: path.c
	$(CC) $(CFLAGS) -c path.c
tsp.o: tsp.c
	$(CC) $(CFLAGS) -c tsp.c
clean:
	rm -f tsp tsp.o graph.o stack.o path.o 

scan-build: clean
	scan-build make   
	
format: 
	clang-format -i -style=file tsp.c graph.c stack.c path.c vertices.h tsp.h 
