main: main.cpp 
	g++ -o main main.cpp -Wall -Werror -pthread

run: main
	./main 5 6 15 4 1 2 50 75 120 0 30
