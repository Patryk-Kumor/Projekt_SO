main: main.cpp 
	g++ -o main main.cpp -Wall -Werror -pthread

run: main
	./main 20 20 20 5 5 0 1000 1000 1000 1000 1000
