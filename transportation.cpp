// Nicole Kurtz
#include "transportation.h"
#include <iostream> 
#include <cstring>
using namespace std;


/*
		char * type; // type of transportation (ex: truck, plane, etc)
		int time; // time it takes to deliver item
*/

// This file manages the functions related to the transportatoin class. 
// It includes the transportation object and a tnode (node pointing to a transportation object)

//////* TRANSPORTATION FUNCTIONS *///////

// This is a transportatoin object
// this manages the movement/location of a product
// through the system. It includes a type and time. 

// default constructor
transportation::transportation(): type(NULL), time(0)
{
}

// add constructor with arguments
transportation::transportation(char * type_toadd, int & time_toadd): time(time_toadd), type(NULL)
{
	type = new char[strlen(type_toadd) + 1];
	strcpy(type, type_toadd);

	time = time_toadd;
}

// copy constructor
transportation::transportation(const transportation & my_transportation)
{
	type = new char[strlen(my_transportation.type) + 1];
	strcpy(type, my_transportation.type);

	time = my_transportation.time;
}

// deconstructor
transportation::~transportation()
{
	if(type)
		delete [] type;
	time = 0;
}

// display transportation info
bool transportation::display()
{
	// transportation incorrectly made, nothing to display, return
	if(!type)
	{
		return false;
	}
	
	// this is a facility, display as such:
	if(time == 0)
	{
		cout << endl << "Facility Name: " << type << endl;
		cout << "No time data associated with a facility" << endl;
		return true;
	}
	
	// this is a transportation, display as such:
	if(time != 0)
	{
		cout << endl << "Transportation Type: " << type << endl;
		cout << "Est. Travel Time: " << time << endl;
		return true;
	}

	return false;
}

// change transportation type
bool transportation::change_type()
{
	int response;
	char temp[100];
	cout << endl <<  "Delivery Type Options:" << endl;
	cout << "1 - Truck" << endl;
	cout << "2 - Airplane" << endl;
	cout << "3 - Boat" << endl;

	// user input
	cout << endl << "Type Number of New Delivery Type: ";
	cin >> response;
	cin.ignore(100, '\n');
	
	// copy user information to temp variable
	switch(response)
	{
		case 1:
			strcpy(temp, "truck");
			break;
		case 2:
			strcpy(temp, "airplane");
			break;
		case 3:
			strcpy(temp, "boat");
			break;
	}
	
	// delete type dynamic memory
	delete [] type;

	// copy temp info to type variable
	type = new char[strlen(temp) + 1];
	strcpy(type, temp);

	return true;

}

// change time
bool transportation::change_time()
{
	// take in user input
	cout << endl << "What is the new time of " << type << ":";
	cin >> time;

	return true;
}


//////* TNODE FUNCTION *//////

// This is a node that points to a transportation object
// It is used by a LLL, called track, which tracks the movement of
// a product through the system

// constructor
tnode::tnode(): next(NULL)
{
}

tnode::tnode(const tnode & to_add): next(NULL)
{
	transport = new transportation(*to_add.transport);
}

// copy constructor
tnode::tnode(char *& facility, int & time)
{
	transport = new transportation(facility, time);
	next = NULL;
}

// deconstructor
tnode::~tnode()
{
	next = NULL;

	if(transport) 
		delete transport;
}

// returns next node to calling routine
tnode*& tnode::go_forward()
{
	return next;
}

// sets the next node to argument node
void tnode::set_next(tnode *& connection)
{
	next = connection;
}

// return transportation object
transportation * tnode::get_tran()
{
	return transport;
}

// display content of pnode
void tnode::display()
{
	transport->display();

}
