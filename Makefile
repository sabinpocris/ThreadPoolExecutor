build:
	gcc main.c LinkedList.c IO.c Queue.c Stack.c SystemConfiguration.c ThreadPoolExecutor.c Task.c -o tema2 -g -std=c99

clean:
	rm tema2