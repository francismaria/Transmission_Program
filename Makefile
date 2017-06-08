make:
	gcc -Wall -o receiver receiver.c -lrt -lpthread
	gcc -Wall -o sender	sender.c -lrt -lpthread