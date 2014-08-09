jlr: jlr.c hashmap.o hashmap.h csv.o csv.h

testhash: hashmap.o hashmap.h testhash.c

hashmap.o: hashmap.c hashmap.h
