all : jc

jc: jc.o token.o
	gcc -g -Wall -std=c11 -o jc jc.o token.o

jc.o: jc.c token.h
	gcc -g -Wall -std=c11 -c jc.c

token.o: token.c token.h
	gcc -g -Wall -std=c11 -c token.c

print_asm.o: print_asm.c print_asm.h token.h
	gcc -g -Wall -std=c11 -c print_asm.c

clean:
	rm -f *.o *~ jc
