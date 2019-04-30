// Program 6:	Users.cpp
// Name: 		Tyler Robins
// Class: 		COMP 2710 Section 1
// Date:		10/29/2017
// Email:		tjr0023@auburn.edu
//
// Description: This is the Users class. It contains methods to check for users and groups: isUser and isGroup.
//				It also allows the user to join a group.

#include "Users.h"

// The isUser method checks whether a user is stored in the all_users file.
// This method is now only used in the messages class for unicast, but
// I am leaving it here for future implementations.
bool Users::isUser(string username)
{
	bool taken;
	string users;
	string filename;
	ifstream infile;
	ofstream outfile;
	
	filename = "all_users";
	ifstream my_file(filename.c_str());
	
	if (my_file.good())
	{
		my_file.close();
		infile.open(filename.c_str());
		while (infile >> users) 
		{
			if (users == username)
			{
				taken = true;
			}
		}
	}
	
	return taken;
}

// The joinGroup method allows the user to join a pre existing group.
// It uses the isGroup method to check whether the group is valid, 
// and it also checks whether the user has already joined the group.
void Users::joinGroup(string username)
{
	bool isG = false;
	bool joined = false;
	bool prevJoined = false;
	string bannerMsg;
	string grpname;
	string dummy;
	string filename;
	ifstream infile;
	ofstream outfile;
	
	while (!joined)
	{
		prevJoined = false;
		cout << endl << "Please enter the group name: ";
		cin >> grpname;
		getline(cin, dummy);
		
		isG = isGroup(grpname);
		if (isG)
		{
			string joinedGs;
			filename = username;
			ifstream my_file(filename.c_str());
			if (my_file.good())
			{
				my_file.close();
				infile.open(filename.c_str());
				while (infile >> joinedGs)
				{
					if (joinedGs == grpname)
					{
						cout << endl << "You're already in this group! Please choose another." << endl;
						prevJoined = true;
						break;
					}
					
				}
				
				if (!prevJoined)
				{
					joined = true;
					infile.close();
					outfile.open(filename.c_str(), ios::app);
					outfile << grpname << " ";
					outfile.flush();
					outfile.close();
				}	
			}
			
			else
			{
				joined = true;
				outfile.open(filename.c_str());
				outfile << grpname << " ";
				outfile.flush();
				outfile.close();
			}
		}
		else
			cout << endl << "Please enter a valid group name" << endl;
	}
	
	if (joined)
	{
		bannerMsg = username + " has joined group " + grpname;
		banner(bannerMsg);
	}
}

// The isGroup method simply checks whether a group has been created.
// Originally intended to be part of the Group class. 
bool Users::isGroup(string grpname)
{
	bool taken = false;
	string filename;
	string grps;
	ifstream infile;
	ofstream outfile;
	
	filename = "all_groups";
	ifstream my_file(filename.c_str());
	
	if (my_file.good())
	{
		my_file.close();
		infile.open(filename.c_str());
		while (infile >> grps) 
		{
			if (grps == grpname)
			{
				taken = true;
			}
		}
	}
	
	return taken;
}	

//	The banner function takes in a string and centers it within the specified banner output.
//	This method is in multiple classes to allow classes to handle all output internally.
void Users::banner(string message)
{
	string bars(59, '=');
	int numSpaces = 0;
	string vbar = "|";
	
	numSpaces = bars.size() - message.size() - 2*vbar.size();
	string spaces(numSpaces/2, ' ');
	message = vbar + spaces + message + spaces;
	if (numSpaces%2 != 0)
		message += " ";
	message += vbar;
	
	cout << endl;
	cout << bars;
	cout << endl << message;
	cout << endl << bars << endl << endl;
}
	