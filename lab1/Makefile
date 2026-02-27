all: build-tests build



build-tests: tree-lab1.o test-lab1.o
	g++ test-lab1.o tree-lab1.o -o test-lab1.exe
	@echo "lab1 tests builded"

build: tree-lab1.o lab1.o
	g++ lab1.o tree-lab1.o -o lab1.exe
	@echo "lab1 builded"

tree-lab1.o: tree-lab1.c lab1.h
	g++ -c tree-lab1.c

lab1.o: lab1.c lab1.h
	g++ -c lab1.c

test-lab1.o: test-lab1.c lab1.h
	g++ -c test-lab1.c



clean:
	rm -f *.o *.exe
	@echo "cleaned"
