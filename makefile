main: main.cpp 
	g++ -o main main.cpp -Wall -Werror -pthread

run: main
	./main 1 2 3 4 5 6 7 8 9 10 11
