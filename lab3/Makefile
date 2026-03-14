all: run-tests build

run-tests: lab3.h stack.o tree.o deykstra.o convert.o test_lab3.o
	gcc stack.o tree.o deykstra.o convert.o test_lab3.o -o test_lab3.exe
	@echo "Running tests"
	./test_lab3.exe

build: lab3.h get_string.o stack.o tree.o deykstra.o convert.o lab3.o
	gcc get_string.o stack.o tree.o deykstra.o convert.o lab3.o -o lab3.exe
	@echo "lab3 builded"

get_string.o: lab3.h get_string.c
	gcc -c get_string.c

stack.o: lab3.h stack.c
	gcc -c stack.c

tree.o: lab3.h tree.c
	gcc -c tree.c

deykstra.o: lab3.h deykstra.c
	gcc -c deykstra.c

convert.o: lab3.h convert.c
	gcc -c convert.c

lab3.o: lab3.h lab3.c
	gcc -c lab3.c

clean:
	rm -rf *.o *.exe
	@echo "cleaned"
