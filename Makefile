CC=g++
CFLAGS=-Wall -Werror -std=c++11 -O3

all:
	$(CC) $(CFLAGS) RoutingPerformance.cpp -o RoutingPerformance
