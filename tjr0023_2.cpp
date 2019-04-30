// Program 0:	tjr0023_2
// Name: 		Tyler Robins
// Class: 		COMP 2710 Section 1
// Date:		10/29/2017
// Email:		tjr0023@auburn.edu
//
// Description: This program allows the a user to do multiple functions such as creating a new user; posting
//				a message to everyone, a specific group, or a specific user; displaying a user's wall or
//				home page; creating a new group; joining a group; or simply quitting the program.
//				The program is capable of being run in multiple sessions or multiple tux copmuters
//				while retaining all info from previous sessions.
//
// How to:      To compile the program, type the following two lines in the terminal:
//				make
//				To execute the program, type the following two lines in the terminal:
//				./lab2

#include <iostream>
#include "Menu.h"

int main()
{
	Menu menu;
	menu.options();
	return 0;
}