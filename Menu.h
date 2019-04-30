// Program 1:	Menu.h
// Name: 		Tyler Robins
// Class: 		COMP 2710 Section 1
// Date:		10/29/2017
// Email:		tjr0023@auburn.edu
//
// Description: This program is a header file for the Menu class. It contains a structure for what the Menu class will contain.

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include "Messages.h"
#include "Groups.h"
#include "Users.h"
using namespace std;

class Menu
{

public:
   string username;
   void options();
   void displayHome();
   void displayWall();
   void banner(string);
   void switcheroo(string, bool&);
   map<int, string> extractMsg();
   int getTime();
};
   