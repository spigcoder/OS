.PHONY:all
all:libdy.so libmath.a

libdy.so:print.o
	gcc -shared -o $@ $<

libmath.a:math.o
	ar -rc $@ $<

print.o:print.h print.c
	gcc -fPIC -c print.c
math.o:math.c

.PHONY:clean open
clean:
	rm -rf lib *.o
open:
	mkdir -p lib/include
	mkdir -p lib/mylib
	mv *.so lib/mylib
	mv *.a lib/mylib
	mv .h lib/include

