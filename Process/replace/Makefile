.PHONY: all
all:demo test

test:test.cpp
	g++ -o $@ $<

demo: test.c
	gcc -o $@ $<

.PHONY: clean
clean:
	rm -f demo test
