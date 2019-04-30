// Program 3:	Messages.h
// Name: 		Tyler Robins
// Class: 		COMP 2710 Section 1
// Date:		10/29/2017
// Email:		tjr0023@auburn.edu
//
// Description: This program is a header file for the Messages class. It contains a structure for what the Message class will contain.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

class Messages
{

public:
   void broadcast(string);
   void unicast(string);
   void multicast(string);
   void banner(string);
   void addGroup(string);
   void timestamp(string);
   string enterMessage();
   bool joinedGroup(string, string);
   bool isUser(string);
   bool isGroup(string);
};