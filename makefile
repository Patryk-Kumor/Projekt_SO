main: main.cpp 
	g++ -o main main.cpp -Wall -Werror -pthread

run: main
	./main 5 5 15 4 1 0 50 75 200 0 23
