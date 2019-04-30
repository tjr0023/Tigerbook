// Program 2:	Menu.cpp
// Name: 		Tyler Robins
// Class: 		COMP 2710 Section 1
// Date:		10/29/2017
// Email:		tjr0023@auburn.edu
//
// Description: This is the Menu class. It runs the program by a loop in the options method which keeps 
//				repeating the "switcheroo" method until the user decides to quit the program. It also
//				includes the methods for displaying a user's wall and home page's, displayWall()
//				and displayHome(). The last three methods are used exclusively within the 
//				displayWall() and displayHome() but are separate methods to make the code
//				more reusable and easier to read.

#include "Menu.h"

//	The options methods prompts the user for their username. If they have not logged in before, it adds them to
//	the "all_users" text file. If they have logged in before, it will set the current username allowing
//	the user to access their previous information. It has a loop to keep asking the user what they
//	want to do until they decide to quit the function.
void Menu::options()
{
	
	string dummy;
	string names;
	string bannerMsg;
	string filename;
	bool done = false;
	bool taken = false;
	ifstream infile, readFile;
	ofstream outfile;
	string input;
	
	cout << "===========================================================" << endl;
	cout << "|               			MediCode			           |" << endl;
	cout << "===========================================================" << endl << endl;
	cout << "Please enter user name: ";
	cin >> username;
	getline(cin, dummy);
	filename = "all_users";
	ifstream my_file(filename.c_str());
	if (my_file.good())
	{
	    my_file.close();
		infile.open(filename.c_str());
		
		while (infile >> names)
		{
			if (names == username)
				taken = true;
		}
		
		if (!taken)
		{
			outfile.open("all_users", ios::app);
			outfile << username << endl;
			outfile.flush();
			outfile.close();
			
			filename = username;
			outfile.open(filename.c_str());
			outfile.flush();
			outfile.close();
		}
		
	}
	
	else
	{
		outfile.open(filename.c_str());
		outfile << username << endl;
		outfile.flush();
		outfile.close();
		
		filename = username;
		outfile.open(filename.c_str());
		outfile.flush();
		outfile.close();
	}
	
	bannerMsg = "Welcome to MediCode, " + username;
	banner(bannerMsg);
	
	while (!done)
	{
		cout << "Broadcast (b), Multicast (m), Unicast (u), Wall (w), Home (h), " << endl;
		cout << "Create new group (g), Join a group (j), Quit (q)\n" << endl;
		cout << "Choose an option: ";
		cin >> input;
		getline(cin, dummy);
		switcheroo(input, done);
	}
}

//	The switcheroo method takes the input from the user and executes the respective function.
void Menu::switcheroo(string input, bool& done)
	{
		char choice = 'z';
		string validResponse = "nNbBmMuUwWhHgGjJsSqQ";
		Messages msg;
		Users usr;
		Groups grp;
		
		if (input.size() == 1 && validResponse.find(input) != string::npos)
		{
			choice = input.at(0);
		}
		switch (choice)
		{		
			case 'b':
			case 'B':
				msg.broadcast(username);
				break;
				
			case 'm':
			case 'M':
				msg.multicast(username);
				break;
				
			case 'u':
			case 'U':
				msg.unicast(username);
				break;
			
			case 'w':
			case 'W':
				displayWall();
				break;
			
			case 'h':
			case 'H':
				displayHome();
				break;
			
			case 'g':
			case 'G':
				grp.createGroup();
				break;
			
			case 'j':
			case 'J':
				usr.joinGroup(username);
				break;
			
			case 'q':
			case 'Q':
				done = true;
				banner("Thank you for using the Distributed TigerBook System");
				break;
			
			default:
			cout << "\nPlease enter a valid response.\n\n";
	     }
	}	

//	The displayWall method will list all messages to user has sent in broadcast, unicast, and multicast.
//	First, it will display the latest two messages. If the user asks for more messages, it will
//	display all remaining messages the user has sent.
void Menu::displayWall()
{
	int time = getTime();	// Retrives the latest timestamp indicating the latest method.
	int loc = 0;
	int loc2 = 0;
	bool more = false;
	string bannerMsg = username + "'s Wall Page";
	map<int, string> msgMap = extractMsg();
	string tempGs;
	string groups;
	string groupname;
	string usr;
	string message;
	string dummy;
	string result1 = "";
	string result2 = "";
	string tempString;
	string allMsgs = "";
	ifstream infile;
	ofstream outfile;
	
	//	Extracts messages from the message_buffer file and places them in a map.
	msgMap = extractMsg();
	
	//	Loops through the map of messages and stores messages the current user sent.
	if (time > 0)
	{
		for (int i = 1; i <= time; i++)
		{
			if (msgMap.find(i) != msgMap.end())
			{
				tempString = msgMap.at(i);
				loc = tempString.find("<!", 0) + 2;
				loc2 = tempString.find(":", loc);
				usr = tempString.substr(loc, loc2 - loc);
				if (username == usr)
				{
					allMsgs = tempString + allMsgs;
				}
			}
			loc = 0;
			loc2 = 0;
		}
		
		//	Retrieves the latest two messages the user sent.
		for (int i = 0; i < 2; i++)
		{
			//find username
			loc = allMsgs.find("<!", loc);
			if (loc == string::npos)
			{
				//break if no more messages
				break; 
			}			   
			loc += 2;
			loc2 = allMsgs.find(":", loc);
			usr = allMsgs.substr(loc, loc2 - loc);
			
			// Find groupname in message buffer
			loc = loc2 + 1;
			loc2 = allMsgs.find("!>", loc);
			groupname = allMsgs.substr(loc, loc2 - loc);
			// Output 
			result1 += usr + " (" + groupname + ") >";
			
			// Find message and output
			loc = loc2 + 2;
			loc2 = allMsgs.find("<!", loc);
			if (loc2 == string::npos)
			{
				message = allMsgs.substr(loc, allMsgs.size() - 1);
			}
			else
			{
				message = allMsgs.substr(loc, loc2 - loc);
				if (i == 1)
				{
					more = true;
				}
					
			}
			result1 += "\n" + message + "\n\n";
		}
		
	}
	
	banner(bannerMsg);
	cout << result1;
	
	//	Prompts the user for more messages and displays the rest if they say yes.
	if (more == true)
	{
		string yesOrNo;
		bool over = false;
		while (!over)
		{
		cout << "More messages> (yes/no): ";
		cin >> yesOrNo;
		getline(cin, dummy);
		cout << endl;
		if (yesOrNo == "yes")
		{
			over = true;
			while (loc != string::npos)
			{
				//find username
				loc = allMsgs.find("<!", loc);
				if (loc == string::npos)
				{
					//break if no more messages
					break; 
				}			   
				loc += 2;
				loc2 = allMsgs.find(":", loc);
				usr = allMsgs.substr(loc, loc2 - loc);
				
				// Find groupname in message buffer
				loc = loc2 + 1;
				loc2 = allMsgs.find("!>", loc);
				groupname = allMsgs.substr(loc, loc2 - loc);
				
				// Output 
				result2 += usr + " (" + groupname + ") >";
				// Find message and output
				loc = loc2 + 2;
				loc2 = allMsgs.find("<!", loc);
				if (loc2 == string::npos)
				{
					message = allMsgs.substr(loc, allMsgs.size() - 1);
				}
				else
				{
					message = allMsgs.substr(loc, loc2 - loc);
				}
				
				result2 += "\n" + message + "\n\n";
				
			}
			cout << result2;
			break;
		}
		
		if (yesOrNo == "no")
		{
			over = true;
			break;
		}
		else 
			cout << "\nPlease enter a valid response.\n";	\
		}
		
	}
	
}

//	The displayWall method will list all messages in groups the user is a part of as well 
//	as messages unicast to the user. First, it will display the latest two messages. If 
//	the user asks for more messages, it will display all remaining messages.
void Menu::displayHome()
{
	int time = getTime(); // Retrives the latest timestamp indicating the latest method.
	int loc = 0;
	int loc2 = 0;
	bool more = false;
	string bannerMsg = username + "'s Home Page";
	map<int, string> msgMap = extractMsg();
	string tempGs;
	string groups;
	string groupname;
	string usr;
	string message;
	string dummy;
	string result1 = "";
	string result2 = "";
	string tempString;
	string allMsgs = "";
	ifstream infile;
	ofstream outfile;
	
	// Creates a string of all the groups the user is a part of.
	string filename = username;
	ifstream my_file(filename.c_str());
	if (my_file.good())
	{
		my_file.close();
		infile.open(filename.c_str());
	   while (infile >> tempGs)
	   {
		   groups = tempGs + " " + groups;
	   }
		infile.close();
	}
	
	// Add #All and username to string of groups.
	groups = "#All " + username + " " + groups;
	
	// Extracts messages from the message_buffer file and places them in a map.
	msgMap = extractMsg();
	
	//	Loops through the map of messages and stores messages in all groups the user is a part of.
	if (time > 0)
	{
		for (int i = 1; i <= time; i++)
		{
			if (msgMap.find(i) != msgMap.end())
			{
				tempString = msgMap.at(i);
				loc = tempString.find(":", 0) + 1;
				loc2 = tempString.find("!>", loc);
				groupname = tempString.substr(loc, loc2 - loc);
				if (groups.find(groupname) != string::npos)
				{
					allMsgs = tempString + allMsgs;
				}
			}
			loc = 0;
			loc2 = 0;
		}
		
		// Retrieves the latest two messages.
		for (int i = 0; i < 2; i++)
		{
			//find username
			loc = allMsgs.find("<!", loc);
			if (loc == string::npos)
			{
				//break if no more messages
				break; 
			}			   
			loc += 2;
			loc2 = allMsgs.find(":", loc);
			usr = allMsgs.substr(loc, loc2 - loc);
			
			// Find groupname in message buffer
			loc = loc2 + 1;
			loc2 = allMsgs.find("!>", loc);
			groupname = allMsgs.substr(loc, loc2 - loc);
			// Output 
			result1 += usr + " (" + groupname + ") >";
			
			// Find message and output
			loc = loc2 + 2;
			loc2 = allMsgs.find("<!", loc);
			if (loc2 == string::npos)
			{
				message = allMsgs.substr(loc, allMsgs.size() - 1);
			}
			else
			{
				message = allMsgs.substr(loc, loc2 - loc);
				if (i == 1)
				{
					more = true;
				}
					
			}
			result1 += "\n" + message + "\n\n";
		}
		
	}
	
	banner(bannerMsg);
	cout << result1;
	
	// Prompts the user for more messages and displays the rest if they say yes.
	if (more == true)
	{
		string yesOrNo;
		bool over = false;
		while (!over)
		{
		cout << "More messages> (yes/no): ";
		cin >> yesOrNo;
		getline(cin, dummy);
		cout << endl;
		if (yesOrNo == "yes")
		{
			over = true;
			while (loc != string::npos)
			{
				//find username
				loc = allMsgs.find("<!", loc);
				if (loc == string::npos)
				{
					//break if no more messages
					break; 
				}			   
				loc += 2;
				loc2 = allMsgs.find(":", loc);
				usr = allMsgs.substr(loc, loc2 - loc);
				
				// Find groupname in message buffer
				loc = loc2 + 1;
				loc2 = allMsgs.find("!>", loc);
				groupname = allMsgs.substr(loc, loc2 - loc);
				
				// Output 
				result2 += usr + " (" + groupname + ") >";
				// Find message and output
				loc = loc2 + 2;
				loc2 = allMsgs.find("<!", loc);
				if (loc2 == string::npos)
				{
					message = allMsgs.substr(loc, allMsgs.size() - 1);
				}
				else
				{
					message = allMsgs.substr(loc, loc2 - loc);
				}
				
				result2 += "\n" + message + "\n\n";
				
			}
			cout << result2;
			break;
		}
		
		if (yesOrNo == "no")
		{
			over = true;
			break;
		}
		else 
			cout << "\nPlease enter a valid response.\n";	\
		}
		
	}
	
	
}

//	The getTime method retrieves the lastest timestamp from the time file.
//	This is in sorting through the message_buffer to know when to stop.
int Menu::getTime()
{
	int time = 0;
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
		infile.close();
	}
	return time;
}

//	The extractMsg method converts all messages into a map with the int timestamp 
//	and the message string.
map<int, string> Menu::extractMsg()
{
	map<int, string> maps;
	string message_buffer = "";
	string filename = "msg_buffer";
	string tempTime;
	string tempMsg;
	int time;	
	int loc = 0;
	int loc2 = 0;
	ifstream my_file(filename.c_str());
	if (my_file.good())
	{
	    my_file.close();
		ifstream in(filename.c_str(), ios::in | ios::binary);
		if (in)
		{
			ostringstream contents;
			contents << in.rdbuf();
			in.close();
			message_buffer = contents.str();
		}
	}	
	
	while (loc != string::npos && message_buffer.size() > 0)
	{
		loc = message_buffer.find("{!", loc);
		if (loc == string::npos)
		{
			break;
		}
		loc += 2;
		loc2 = message_buffer.find("!}", loc);
		tempTime = message_buffer.substr(loc, loc2 - loc);
		loc = loc2 + 2;
		loc2 = message_buffer.find("{!", loc);
		if (loc2 == string::npos)
		{
			tempMsg = message_buffer.substr(loc, message_buffer.size() - 1);
		}
		else
		{
			tempMsg = message_buffer.substr(loc, loc2 - loc);
		}
		stringstream ss(tempTime);
		ss >> time;
		maps[time] = tempMsg;
	}
	return maps;
		
}
		
//	The banner function takes in a string and centers it within the specified banner output.
//	This method is in multiple classes to allow classes to handle all output internally.
void Menu::banner(string message)
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