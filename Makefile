route: route.o
	gcc -o route route.o
route.o: route.c
	gcc -c route.c
clear:
	rm route.exe *.o