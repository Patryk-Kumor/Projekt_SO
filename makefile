main: main.cpp 
	g++ -o main main.cpp -Wall -Werror -pthread

run: main
	./main 5 5 5 4 1 4 20 8 8 0 23
