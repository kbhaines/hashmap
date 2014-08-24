CC=gcc -g

LIBS=-lcheck -lm -lpthread -lrt
%.o=%.c %.h

main: main.c vin.o hashmap.o csv.o

test: vin.check vin.o
	checkmk vin.check > test_vin.c
	gcc -o test-vin test_vin.c vin.o hashmap.o csv.o $(LIBS)

testhash: hashmap.o hashmap.h testhash.c

hashmap.o: hashmap.c hashmap.h
