// Program 4:	Messages.cpp
// Name: 		Tyler Robins
// Class: 		COMP 2710 Section 1
// Date:		10/29/2017
// Email:		tjr0023@auburn.edu
//
// Description: This is the Messages class. It allows the user to broadcast, unicast, and multicast. It timestamps and 
//				saves all messages through the timestamp method. Timestamp was initially supposed to be its own class,
//				but because of how small it is I decided to simply include it in the Messages Class. 
#include "Messages.h"

// The broadcast method allows the user to send messages to all users.
void Messages::broadcast(string username)
{
	string bannerMsg;
	string msg = enterMessage();
	string grpname = "#All";
	
	if(!isGroup(grpname))
		addGroup(grpname);
	
	msg = "<!" + username + ":" + grpname + "!>" + msg;
	timestamp(msg);
	bannerMsg = username + " has broadcasted a message";
	banner(bannerMsg);

}

// The unicast method allows the user to send messages to a specific user.
// It prompts the user for a valid user to send the message to.
void Messages::unicast(string username)
{
	string dummy;
	string recipient;
	string msg;
	string bannerMsg;
	string grpname;
	bool done = false;
	while (!done)
	{
		cout << endl << "Enter the recipient user name: ";
		cin >> recipient;
		getline(cin, dummy);
		if (isUser(recipient)) 
		{
			done = true;
			msg = enterMessage();
			grpname = "_" + recipient;
			msg = "<!" + username + ":" + recipient + "!>" + msg;
			if(!isGroup(grpname))
				addGroup(grpname);
			timestamp(msg);
			bannerMsg = username + " has unicasted a message to " + recipient;
			banner(bannerMsg);
			
		}
		
		else
		{
			cout << endl << "Please enter a valid recipient name." << endl;
		}
	}
	
}

// The multicast method allows the user to send messages to a specific group.
// It prompts the user for a group they have previously joined.
void Messages::multicast(string username)
{
	string dummy;
	string grpname;
	string msg;
	string bannerMsg;
	bool done = false;
	while (!done)
	{
		cout << endl << "Enter the group name: ";
		cin >> grpname;
		getline(cin, dummy);
		if (joinedGroup(grpname, username)) 
		{
			done = true;
			msg = enterMessage();
			msg = "<!" + username + ":" + grpname + "!>" + msg;
			timestamp(msg);
			bannerMsg = username + " has multicasted a message to " + grpname;
			banner(bannerMsg);
			
		}
		
		else
		{
			cout << endl << "Please enter a group you have previously joined." << endl;
		}
	}
}

// The enterMessage method is used by all three message options. It simply prompts the 
// user for the message they want to enter.
string Messages::enterMessage()
{
	string message;
	string tempmessage;
	string buffer;
	int msgnum = 0;
	bool msgCheck = false;
	
	   cout << "\nEnter message: ";
	   while (msgCheck == false)
	   {
		   getline(cin, tempmessage);
		   // Special spacing and resetting variable for first line of input
		   if (msgnum == 0)
		   {
			   message = tempmessage;
			   msgnum++;
		   }
		   
		   // Storing rest of message
		   else if (tempmessage.find("^!") == string::npos) 
		   {
			   message = message + "\n" + tempmessage;
		   }
		   
		   // End of loop
		   else 
		   {
			   msgCheck = true;  
			   msgnum = 0;		     
		   }			  
	   }
	    
	   return message;
}

// The joinedGroup method is used by the multicast method to check
// whether the user has joined the group they are messaging. It was
// originally intended to be part of the Group class, but I 
// decided to handle everything within this class.
bool Messages::joinedGroup(string grpname, string username)
{
	bool taken = false;
	string filename;
	string grps;
	ifstream infile;
	ofstream outfile;
	
	filename = username;
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

// The isUser method is used by the unicast method to check
// if the recipient the user is trying to message exists. It
// was originally intended to be in the Users class.
bool Messages::isUser(string name)
{
	bool taken = false;
	string filename;
	string users;
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
			if (users == name)
			{
				taken = true;
			}
		}
	}
	
	return taken;
}

// The isGroup method is used by both the broadcast and unicast methods. Rather than
// checking for actual groups, it is simply making sure #All and the recipient of 
// a unicast are included in the all_groups file.
bool Messages::isGroup(string name)
{
	bool taken = false;
	string filename;
	string users;
	ifstream infile;
	ofstream outfile;
	
	filename = "all_groups";
	ifstream my_file(filename.c_str());
	
	if (my_file.good())
	{
		my_file.close();
		infile.open(filename.c_str());
		while (infile >> users) 
		{
			if (users == name)
			{
				taken = true;
			}
		}
	}
	
	return taken;
}

// The addGroup method is used by both the broadcast and unicast methods. Rather than
// creating actual groups, it is simply adds either #All or the recipient of 
// a unicast to the all_groups file.
void Messages::addGroup(string grpname)
{
	ifstream infile;
	ofstream outfile;
	string filename = "all_groups";
	ifstream my_file(filename.c_str());
	if (my_file.good())
	{
		my_file.close();
		outfile.open(filename.c_str(), ios::app);
		outfile << grpname + " ";
		outfile.flush();
		outfile.close();
	}
	else
	{
		my_file.close();
		outfile.open(filename.c_str());
		outfile << grpname + " ";
		outfile.flush();
		outfile.close();
	}
}

// The timestamp method increments the int value in the time file, attaches the new timestamp
// to the message passed into it, and saves it in the message_buffer file. It will create
// either the time file or the message_buffer file if they have not already been created.
void Messages::timestamp(string message)
{
	int time = 1;
	ifstream infile;
	ofstream outfile;
	stringstream intToString;
	string filename;
	string stamp;
	
	filename = "time";
	ifstream my_file(filename.c_str());
	if (my_file.good())
	{
		my_file.close();
		infile.open(filename.c_str());
		infile >> time;
		time++;
		infile.close();
	}
	
	outfile.open(filename.c_str());
	outfile << time;
	outfile.close();
	
	intToString << time;
	intToString >> stamp;
	
	message = "{!" + stamp + "!}" + message;
	
	filename = "msg_buffer";
	ifstream my_file2(filename.c_str());
	if (my_file.good())
	{
		my_file.close();
		outfile.open(filename.c_str(), ios::app);
		outfile << message;
		outfile.flush();
		outfile.close();
	}
	else
	{
		my_file.close();
		outfile.open(filename.c_str());
		outfile << message;
		outfile.flush();
		outfile.close();
	}
}

//	The banner function takes in a string and centers it within the specified banner output.
//	This method is in multiple classes to allow classes to handle all output internally.	
void Messages::banner(string message)
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