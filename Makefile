all:
	./main
main: main.cpp
	g++ main.cpp -o main -pthread
cleanup:
	rm -rf ./main