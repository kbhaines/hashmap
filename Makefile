CC=gcc -g

LIBS=-lcheck -lm -lpthread -lrt
%.o=%.c %.h

main: main.c vin.o hashmap.o csv.o

run: main
	head -n 1000000 jlrdat/vehicle-data|/usr/bin/time -v ./main

test: vin.check vin.o
	checkmk vin.check > test_vin.c
	gcc -o test-vin test_vin.c vin.o hashmap.o csv.o $(LIBS)

testhash: hashmap.o hashmap.h testhash.c

clean:
	rm *.o
