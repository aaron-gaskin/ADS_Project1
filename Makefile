OBJS = fibonacci_heap.cpp node.cpp main.cpp

hashtagcounter: $(OBJS)
	g++ -Wall -o hashtagcounter fibonacci_heap.cpp node.cpp main.cpp