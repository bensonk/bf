all: interp

test: all
	./interp hello.bf
	@echo

clean:
	rm -rf interp *.o
