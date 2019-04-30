// Program 5:	Users.h
// Name: 		Tyler Robins
// Class: 		COMP 2710 Section 1
// Date:		10/29/2017
// Email:		tjr0023@auburn.edu
//
// Description: This program is a header file for the Users class. It contains a structure for what the Users class will contain.

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Users
{
public:
    bool isUser(string);
	bool isGroup(string);
	void joinGroup(string);	
	void banner(string);
};