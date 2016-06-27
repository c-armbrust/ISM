ismclient: PruTask.o
	g++  main.cpp PruTask.o -std=c++14 -o ismclient -lpthread -lprussdrv
PruTask.o:
	g++ -c PruTask.cpp -std=c++14 -o PruTask.o
	
clean: 
	rm ismclient PruTask.o
