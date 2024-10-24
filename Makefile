all: matrix

matrix: jim-haslett-csc6220-hw4.c
	gcc -fopenmp -o jim-haslett-csc6220-hw4 jim-haslett-csc6220-hw4.c

clean:
	rm jim-haslett-csc6220-hw4 result.txt times.tsv

lint:
	cpplint jim-haslett-csc6220-hw4.c

run:
	./jim-haslett-csc6220-hw4
