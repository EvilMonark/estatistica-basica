all: clean build run

clean:
	@rm -rf main.o main *.txt

build:
	@g++ main.cc -o main

run:
	@./main