// Nicole Kurtz
// The purpose of this code is to implement the client program functions

using namespace std;
#include <iostream>
#include "name.h"

// prototypes
void create_product(list & facility_list); // create product object
void strategy(char strategy_toadd[]); // select distribution strategy
void create_transportation(); // create transportation object
void create_name(list & facility_list); // create name object
void facility_type_selection(char facility_type[]); // select facility type for name object
void display_facility_products(list & facility_list); // add product to facility
void menu(list & facility_list, int & response); // menu 
void ship_customer(list & facility_list); // ship product from facility to customer (reduce quantity)
void display_product_path(list & facility_list); // display products path in system
void add_product_table(list & facility_list); // add product to to facilities replenishment table
void replenish_table(list & facility_list); // replenish highest priority product

int main()
{
	// objects
	list facility_list; // list of facilities
	int response; // response from user
		
	do{
		menu(facility_list, response);
	}while(response != 8);

	return 0;
}

// menu to select function
void menu(list & facility_list, int & response)
{

	cout << endl << "------MENU------";
	cout << endl << "1 - Create Facility";
	cout << endl << "2 - Stock Facility with New Product";
	cout << endl << "3 - Display Facility Products";
	cout << endl << "4 - Ship product to Customer";
	cout << endl << "5 - Display Product Path";
	cout << endl << "6 - Add Product to Replenishment Table";
	cout << endl << "7 - Replenish Top Priority Product for Facility (+100 QTY)";
	cout << endl << "8 - End Program";
	cout << endl << "-----------------";

	cout << endl << endl << "Type the number of the menu item: ";
	cin >> response;
	cin.ignore(100, '\n');

	switch(
		response)
	{
		case 1:
			create_name(facility_list);
			break;
		case 2: 
			create_product(facility_list);
			break;
		case 3:
			display_facility_products(facility_list);
			break;
		case 4:
			ship_customer(facility_list);
			break;
		case 5:
			display_product_path(facility_list);
			break;
		case 6:
			add_product_table(facility_list);
			break;

		case 7:
			replenish_table(facility_list);
			break;
			
		case 8: 
			cout << endl << "Thanks for using the Distribution program" << endl << endl;
			break;
	}
}

// Replenish highest priority product
void replenish_table(list & facility_list)
{
	char facility_toget[100];
	bool check = true;
	
	// check that facility exists
	do {
	cout << endl << "What facility would you like to add to replenishment priority list: ";
	cin.get(facility_toget, 100, '\n');
	cin.ignore(100, '\n');
		if(!(facility_list.find_facility(facility_toget)))
		{
			cout << endl << "The facility does not exist, please retype your facility" << endl;
			check = false;
		}
		else
			check = true;
	}while(check == false);

	if(!(facility_list.replenish_table(facility_toget)))
		cout << endl << "Unsuccessful! Check that products have been added to replenishment table" << endl;
	else
		cout << endl << "Top Priority Product Replenished by 100 QTY! Display Facility Products to see increase." << endl;
}

// add product to replenishment table of the facility
void add_product_table(list & facility_list)
{
	char facility_toget[100];
	char product_toget[100];
	int priority;
	bool check = true;
	
	// check that facility exists
	do {
	cout << endl << "What facility would you like to add to replenishment priority list: ";
	cin.get(facility_toget, 100, '\n');
	cin.ignore(100, '\n');
		if(!(facility_list.find_facility(facility_toget)))
		{
			cout << endl << "The facility does not exist, please retype your facility" << endl;
			check = false;
		}
		else
			check = true;
	}while(check == false);
	
	// product to add to replenishment table
	cout << endl << "What product would you like to add to replenishment table of " << facility_toget << ": ";
	cin.get(product_toget, 100, '\n');
	cin.ignore(100, '\n');
	
	// priority level for replenishing product
	cout << endl << "What is the priority level for " << product_toget << " to be replenished (1 = highest, 5 = lowest):";
	cin >> priority;
	cin.ignore(100, '\n');
	
	// function call to add product to replenishment table
	if(!facility_list.add_table(facility_toget, product_toget, priority))
		cout << endl << "Product could not be added to replenishment list. Check that product has been added to facility." << endl;
}

// display the product path - facility location and transportation
void display_product_path(list & facility_list)
{
	char facility_toget[100];
	char product_toget[100];
	bool check = true;

	cout << endl << "What product would you like to display the path for: ";
	cin.get(product_toget, 100, '\n');
	cin.ignore(100, '\n');
	
	// check to make sure facility exists
	do {
	cout << "What was the last facility the product was located: ";
	cin.get(facility_toget, 100, '\n');
	cin.ignore(100, '\n');
		if(!(facility_list.find_facility(facility_toget)))
		{
			cout << endl << "The facility does not exist, please retype your facility" << endl;
			check = false;
		}
		else
			check = true;
	}while(check == false);
	
	// check that product was found and path displayed
	if(!facility_list.display_path(facility_toget, product_toget))
		cout << endl << "Product not found!" << endl;

}

// ship product to customer
// reduce quantity of product in facility
void ship_customer(list & facility_list)
{
	char facility_toget[100];
	char product_toget[100];
	bool check = true;
	
	cout << "What product would you like to ship to a customer: ";
	cin.get(product_toget, 100, '\n');
	cin.ignore(100, '\n');
	
	// check that facility exists 
	do {
	cout << "What facility would you like to ship the product from: ";
	cin.get(facility_toget, 100, '\n');
	cin.ignore(100, '\n');
		if(!(facility_list.find_facility(facility_toget)))
		{
			cout << "The facility does not exist, please retype your facility" << endl;
			check = false;
		}
		else
			check = true;
	}while(check == false);

	// variables
	int response;
	char t_type[100];
	
	// select delivery method
	cout << endl <<  "Delivery Type Options:" << endl;
	cout << "1 - Truck" << endl;
	cout << "2 - Airplane" << endl;
	cout << "3 - Boat" << endl;

	cout << endl << "Type Number of New Delivery Type: ";

	do{
		cin >> response;
		cin.ignore(100, '\n');
		if(response > 3)
			cout << "Please type a number between 1-3" << endl;
	}while(response > 3 || response < 0);

	
	// copies transportation type to type variable
	switch(response)
	{
		case 1:
			strcpy(t_type, "truck");
			break;
		case 2:
			strcpy(t_type, "airplane");
			break;
		case 3:
			strcpy(t_type, "boat");
			break;
	}
	
	// display message if successfully shipped or not
	if(facility_list.ship_customer(facility_toget, product_toget, t_type))
		cout << endl << "Product delivered to customer" << endl;
	else
		cout << endl << "Product was unable to be delivered. Check that facility contains product." << endl;

}

// Display products in a facility
void display_facility_products(list & facility_list)
{
	char facility_toget[100];
	bool check = true;
	
	// find facility to add product to
	do {
	cout << "What facility would you like to display product list: ";
	cin.get(facility_toget, 100, '\n');
	cin.ignore(100, '\n');
		if(!(facility_list.find_facility(facility_toget)))
		{
			cout << "The facility does not exist, please retype your facility" << endl;
			check = false;
		}
		else
			check = true;
	}while(check == false);
	
	// If there's no products, display message
	if(!facility_list.display_list(facility_toget))
		cout << endl << "No products to display" << endl;

}

// create transportation object
void create_transportation()
{
	// variables
	int response;
	char type[100];
	int time;

	cout << endl <<  "Delivery Type Options:" << endl;
	cout << "1 - Truck" << endl;
	cout << "2 - Airplane" << endl;
	cout << "3 - Boat" << endl;

	cout << endl << "Type Number of New Delivery Type: ";

	do{
		cin >> response;
		cin.ignore(100, '\n');
		if(response > 3)
			cout << "Please type a number between 1-3" << endl;
	}while(response > 3 || response < 0);

	
	// copies transportation type to type variable
	switch(response)
	{
		case 1:
			strcpy(type, "truck");
			break;
		case 2:
			strcpy(type, "airplane");
			break;
		case 3:
			strcpy(type, "boat");
			break;
	}
	
	// create transportation object
	transportation my_transportation(type, time);

	// display transportation information
	my_transportation.display();


}

// create product object
void create_product(list & facility_list)
{
	// variables
	char name_toadd[100];
	char strategy_toadd[100];
	char category_toadd[100];
	int quantity_toadd;
	float price_toadd;

	char facility_toget[100];
	bool check = true;
	
	// find facility to add product to
	do {
	cout << "What facility would you like to add a product to: ";
	cin.get(facility_toget, 100, '\n');
	cin.ignore(100, '\n');
		if(!(facility_list.find_facility(facility_toget)))
		{
			cout << "The facility does not exist, please retype your facility" << endl;
			check = false;
		}
		else
			check = true;
	}while(check == false);


	cout << "--Create Product--" << endl;
	
	// user input
	cout << "Name: ";
	cin.get(name_toadd, 100, '\n');
	cin.ignore(100, '\n');

	cout << "Price: ";
	cin >> price_toadd;
	cin.ignore(100, '\n');

	cout << "Category: ";
	cin.get(category_toadd, 100, '\n');
	cin.ignore(100, '\n');

	cout << "Quantity: ";
	cin >> quantity_toadd;
	cin.ignore(100, '\n');
	
	// function to copy product strategy to variable
	strategy(strategy_toadd);

	// create product object
	product my_product(name_toadd, strategy_toadd, category_toadd, quantity_toadd, price_toadd); 

	// add product to facility list
	facility_list.add_product(my_product, facility_toget);

}

// strategy selection function -- copies info to variable
void strategy(char strategy_toadd[])
{
	int response;
	cout << endl <<  "Distribution Strategy Options:" << endl;
	cout << "1 - 1-Day Shipping" << endl;
	cout << "2 - 2-Day Shipping" << endl;
	cout << "3 - Standard Shipping (5 Day)" << endl;

	cout << endl << "Type Number of Strategy: ";
	do{
		cin >> response;
		cin.ignore(100, '\n');
		if(response > 3)
			cout << "Please type a number between 1-3";
	}while(response > 3 || response < 0);
	
	// copies information to variable
	switch(response)
	{
		case 1:
			strcpy(strategy_toadd, "1-day");
			break;
		case 2:
			strcpy(strategy_toadd, "2-day");
			break;
		case 3:
			strcpy(strategy_toadd, "standard");
			break;
	}
			
}

// Create name object
void create_name(list & my_list)
{
	char facility_name[100];
	char type[100];
	char location[100];

	cout << endl << "Please type the facility name: ";
	cin.get(facility_name, 100, '\n');
	cin.ignore(100, '\n');

	cout << endl << "Please type the location of the facility: ";
	cin.get(location, 100, '\n');
	cin.ignore(100, '\n');
	
	// function to copy facility type to name object
	facility_type_selection(type);
	
	// create name object
	facility my_name(facility_name, type, location);
	
	// display name object
	my_name.display();

	// add to facility list
	my_list.add_facility(my_name);


}

// function to copy facility type info to variable
void facility_type_selection(char facility_type[])
{
	int response;
	cout << endl <<  "Facility Type Options:" << endl;
	cout << "1 - National" << endl;
	cout << "2 - Local" << endl;

	cout << endl << "Type Number of the Facility Type: ";
	do{
		cin >> response;
		cin.ignore(100, '\n');
		if(response > 3)
			cout << "Please type a number between 1-3";
	}while(response > 3 || response < 0);
	
	// copies info to variable
	switch(response)
	{
		case 1:
			strcpy(facility_type, "National");
			break;
		case 2:
			strcpy(facility_type, "Local");
			break;
	}
}
