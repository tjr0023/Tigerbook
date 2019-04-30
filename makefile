lab2: tjr0023_2.o Menu.o Messages.o Users.o Groups.o 
	g++ -o lab2 tjr0023_2.o Menu.o Messages.o Users.o Groups.o 
	
tjr0023_2.o: tjr0023_2.cpp Menu.h
	g++ -c tjr0023_2.cpp
	
Menu.o: Menu.cpp Menu.h
	g++ -c Menu.cpp
	
Messages.o: Messages.cpp Messages.h
	g++ -c Messages.cpp
	
Users.o: Users.cpp Users.h
	g++ -c Users.cpp
	
Groups.o: Groups.cpp Groups.h
	g++ -c Groups.cpp
