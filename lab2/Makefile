all: run-tests build

build: lab2.o sort-lab2.o table.o
	gcc lab2.o sort-lab2.o table.o -o lab2.exe
	@echo "lab2 builded"

run-tests: test-lab2.o sort-lab2.o table.o
	gcc test-lab2.o sort-lab2.o table.o -o test-lab2.exe
	@echo "running tests"
	./test-lab2.exe

lab2.o: lab2.h lab2.c
	gcc -c lab2.c

sort-lab2.o: lab2.h sort-lab2.c
	gcc -c sort-lab2.c

table-io.o: lab2.h table.c
	gcc -c table.c

test-lab2.o: lab2.h test-lab2.c
	gcc -c test-lab2.c

clean:
	rm -f *.o *.exe
	@echo "cleaned"
