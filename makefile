all : jc

jc: jc.o token.o print_asm.o deque.o
	gcc -g -Wall -std=c11 -o jc jc.o token.o print_asm.o deque.o

jc.o: jc.c token.h deque.h
	gcc -g -Wall -std=c11 -c jc.c

print_asm.o: print_asm.c print_asm.h token.h deque.h
	gcc -g -Wall -std=c11 -c print_asm.c

token.o: token.c token.h
	gcc -g -Wall -std=c11 -c token.c

deque.o: deque.c deque.h
	gcc -g -Wall -std=c11 -c deque.c

clean:
	rm -f *.o *~ jc
