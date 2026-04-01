all: run-tests build

run-tests: avl-tree.o test-lab4.o
	gcc avl-tree.o test-lab4.o -o test-lab4.exe
	@echo "running tests..."
	./test-lab4.exe

build: avl-tree.o lab4.o
	gcc avl-tree.o lab4.o -o lab4.exe
	@echo "lab4 builded"

avl-tree.o: avl-tree.c lab4.h
	gcc -c avl-tree.c

lab4.o: lab4.c lab4.h
	gcc -c lab4.c

clean:
	rm -rf *.exe *.o
	@echo "cleaned"
