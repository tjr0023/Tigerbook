// Program 8:	Groups.h
// Name: 		Tyler Robins
// Class: 		COMP 2710 Section 1
// Date:		10/29/2017
// Email:		tjr0023@auburn.edu
//
// Description: This is the Groups class. It allows the user to create a new group via the createGroup function.

#include "Groups.h"

// The createGroup function creates a new group and stores it to the all_groups file as long as the group
// name is unique.
void Groups::createGroup()
{
	string grpname;
	string grps;
	string dummy;
	string bannerMsg;
	string filename;
	bool created = false;
	bool taken = false;
	ifstream infile;
	ofstream outfile;
	
	while (!created)
	{
		taken = false;
		cout << endl << "Please enter the group name: ";
		cin >> grpname;
		getline(cin, dummy);
		
		// If all_users is already created, check whether group name is taken and
		// add group if not.
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
					cout << endl << "Sorry, this group name is already taken." << endl << endl;
				}
			}
			
			if (!taken) 
			{
				infile.close();
				outfile.open(filename.c_str(), ios::app);
				outfile << grpname + " ";
				outfile.flush();
				outfile.close();
				created = true;
			}
		}
		
		// If the all_groups file has not been created, create it and add the group.
		else
		{
			outfile.open(filename.c_str());
			outfile << grpname + " ";
			outfile.flush();
			outfile.close();
			created = true;
		}
	}
	
	bannerMsg = "New group " + grpname + " created";
	banner(bannerMsg);
	
}

//	The banner function takes in a string and centers it within the specified banner output.
//	This method is in multiple classes to allow classes to handle all output internally.
void Groups::banner(string message)
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
			
			
		