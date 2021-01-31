// Nicole Kurtz
#include "product.h"
using namespace std;

/*
		char * name; // name of product
		char * strategy; // strategy of product
		char * category; // category of product
		float price; // price of product
		int quantity;  // quantity of product
*/


//  This file manages the implemention of a product object
// The nodes that point to a product object: pnode: node for LLL
// bnode: node for BST. and a LLL object for tracking a product as it 
// moves through the system

//////* TRACK FUNCTION *//////
// this is a LLL that tracks the movement of a product
// through the system

// default constructor
track::track(): head(NULL)
{
}

// copy constructor
track::track(const track & track_tocopy)
{
	if(track_tocopy.head)
		copy_tnodes(head, track_tocopy.head);
}

// recursively copies first arguments data to second
// arguments data
void track::copy_tnodes(tnode * head, tnode * to_copy)
{
	if(!head) return;

	to_copy = new tnode(*head);

	copy_tnodes(head->go_forward(), to_copy->go_forward());
}

// deconstructor
track::~track()
{
	if(head)
		delete_nodes(head);
}

// recursively deletes nodes
void track::delete_nodes(tnode *& head)
{
	if(!head)
		return;
	
	tnode * temp = head->go_forward();
	delete head;
	head = temp;

	return delete_nodes(head);
}
	
// add node to LLL of product ptah
bool track::add_node(char * facility_name, int & time)
{
	tnode * temp = new tnode(facility_name, time);

	if(!temp)
		return false;

	if(!head)
		head = temp;
	else
	{
		temp->set_next(head);
		head = temp;
	}
	head->display();
		
	return true;
}

// display product path
bool track::display()
{
	if(!head)
		return false;

	cout << endl << "----Product Path----" <<endl;

	return display(head);
}

// recursive call to display product path
bool track::display(tnode * head)
{
	if(!head)
		return true;

	head->display();
	
	display(head->go_forward());

	return true;
}


///* PRODUCT FUNCTIONS *////

// This is a product object that contains a products:
// name, strategy, category, quantity and price
// The product function contains a LLL (called track)
// which tracks the products movement through the system

// default constructor
product::product()
{
	//product_path = new list;
	name = strategy = category = NULL;
	quantity = 0;
	price = 0;

	// create LLL of product path
	p_path = new track;

}

// add constructor
product::product(char * name_add, char * strategy_add, char * category_add, int quantity_add, float price_add): name(NULL), strategy(NULL), category(NULL), quantity(0), price(0)
{
	if(name)
		delete [] name;
	if(strategy)
		delete [] strategy;
	if(category)
		delete [] category;

	name = new char[strlen(name_add) + 1];
	strcpy(name, name_add);

	strategy = new char[strlen(strategy_add) + 1];
	strcpy(strategy, strategy_add);

	category = new char[strlen(category_add) + 1];
	strcpy(category, category_add);

	quantity = quantity_add;
	price = price_add;

	// create LLL of product path
	p_path = new track;
}

// copy constuctor
product::product(const product & product_toadd): name(NULL), strategy(NULL), category(NULL), quantity(0), price(0.0)
{
	if(!product_toadd.name || !product_toadd.strategy || !product_toadd.category)
		return;

	// delete if dynamic memory already exists
	if(name)
		delete [] name;
	if(strategy)
		delete [] strategy;
	if(category)
		delete [] category;

	name = new char[strlen(product_toadd.name) + 1];
	strcpy(name, product_toadd.name);

	strategy = new char[strlen(product_toadd.strategy) + 1];
	strcpy(strategy, product_toadd.strategy);

	category = new char[strlen(product_toadd.category) + 1];
	strcpy(category, product_toadd.category);

	quantity = product_toadd.quantity;
	price = product_toadd.price;
	
	// create LLL of product path
	p_path = new track;
}

// copy constructor
product::product(const product * product_toadd): name(NULL), strategy(NULL), category(NULL), quantity(0), price(0.0)
{
	// delete if dynamic memory already exists
	if(name)
		delete [] name;
	if(strategy)
		delete [] strategy;
	if(category)
		delete [] category;

	name = new char[strlen(product_toadd->name) + 1];
	strcpy(name, product_toadd->name);

	strategy = new char[strlen(product_toadd->strategy) + 1];
	strcpy(strategy, product_toadd->strategy);

	category = new char[strlen(product_toadd->category) + 1];
	strcpy(category, product_toadd->category);

	quantity = product_toadd->quantity;
	price = product_toadd->price;
	
	// create LLL of product path
	p_path = new track;
}

// deconstructor
product::~product()
{
	if(p_path)
		delete p_path;

	if(name)
		delete [] name;
	if(strategy)
		delete [] strategy;
	if(category)
		delete [] category;
	quantity = 0;
	price = 0;
}

// compares argument category to current category
bool product::category_compare(product *& to_compare)
{
	if(strcmp(category, to_compare->category) == 0)
		return true;
	return false;
}

// compares argument category to current category
bool product::category_compare(product & to_compare)
{
	if(strcmp(category, to_compare.category))
		return true;
	return false;
}

// get the name of the facility
bool product::get_name(char *& name_toget)
{
	if(!name_toget)
		return false;

	name_toget = new char[strlen(name) + 1];
	strcpy(name_toget, name);

	return true;
}

// display product path
bool product::product_path()
{
	if(p_path->display())
		return true;
	return false;
}

// ship a product to a customer
bool product::ship_customer(char * my_transportation)
{

	if(quantity > 0)
	{
		// reduce quantity by one
		--quantity;

		// travel time based on strategy
		int time = get_strategy_time();

		// add node to product path
		p_path->add_node(my_transportation, time);
		return true;
	}
	
	// quantity is zero, can't reduce
	else
		return false;
}

// calls function to add product path to LLL of product path
bool product::track_facility(char * facility_name)
{
	int time = 0;
	if(p_path->add_node(facility_name, time))
		return true;
	return false;
}

// returns number of days the product strategy will take to reach destination
int product::get_strategy_time()
{
	if(strcmp(strategy, "1-day") == 0)
		return 1;

	if(strcmp(strategy, "2-day") == 0)
		return 2;

	if(strcmp(strategy, "standard") == 0)
		return 5;
	return 0;
}

// replenish quantity of product
bool product::replenish()
{
	quantity += 100;
	return true;
}

// display prouct info
bool product::display()
{
	if(!name || !category)
		return false;

	cout << endl << "Name: " << name << endl;
	cout << "Category: " << category << endl;
	cout << "Price: " << price << endl;
	cout << "Quantity: " << quantity << endl;
	cout << "Strategy: " << strategy << endl << endl;

	return true;
}

// compare names
bool product::find_name(char * provided_product)
{
	if(strcmp(name, provided_product) == 0)
	{
		return true;
	}
	return false;
}


//////*  Product Node for BST *//////////

// This is a node that points to a product
// It is use for a Binary Search Tree

// default constructor
bnode::bnode(): left(NULL), right(NULL), priority(0)
{
}

// add constructor
bnode::bnode(const product * my_product, int priority_toadd): left(NULL), right(NULL), priority(0)
{
	a_product = new product(my_product);
	priority = priority_toadd;
}

// copy constructor
bnode::bnode(const bnode & node): left(NULL), right(NULL), priority(0)
{
	a_product = new product(node.a_product);
}

// deconstructor
bnode::~bnode()
{
	left = right = NULL;

	priority = 0;
	
	// delete dynamic memory if exists
	if(a_product)
		delete a_product;
}

// replace current node with to_add
bool bnode::add(const bnode * to_add)
{
	delete a_product;

	a_product = new product(to_add->a_product);

	if(!a_product)
		return false;
	return true;

}

// fill passed pointer with name 
bool bnode::get_name(char *& name_toget)
{
	if(a_product->get_name(name_toget))
		return true;
	return false;
}

// move to the left node
bnode *& bnode::go_left()
{
	return left;
}

// move to the right node
bnode *& bnode::go_right()
{
	return right;
}

// set left node to connection
void bnode::set_left(bnode *& connection)
{
	left = connection;
}

// set right node to connection
void bnode::set_right(bnode *& connection)
{
	right = connection;
}

// display contents of node
bool bnode::display()
{
	if(a_product->display())
		return true;
	return false;
}

// compared priority to passed priority
bool bnode::compare_prio(int priority_tocompare)
{
	if(priority >= priority_tocompare)
		return true;
	return false;
}


//////* Product Node for LLL *//////////

// This is a node that points to a product
// This is used by a Linear Linked list

// constructor
pnode::pnode(): next(NULL)
{
}

// deconstructor
pnode::~pnode()
{
	next = NULL;

	if(a_product) 
		delete a_product;
}

// returns next node to calling routine
pnode*& pnode::go_forward()
{
	return next;
}

// copy constructor
pnode::pnode(const product & add_product)
{
	a_product = new product(add_product);
	next = NULL;
}

// copy constructor
pnode::pnode(const pnode * to_copy)
{
	if(a_product)
		delete a_product;

	a_product = new product(to_copy->a_product);

}

// sets the next node to argument node
void pnode::set_next(pnode *& connection)
{
	next = connection;
}

// return product
product *& pnode::get_product()
{
	return a_product;
}

// find out if product exists 
bool pnode::find_name(char * provided_product)
{
	if(a_product->find_name(provided_product))
		return true;
	return false;
}

// replenish quantity of product
bool pnode::replenish()
{
	a_product->replenish();
	return true;
}

// display content of pnode
void pnode::display()
{
	a_product->display();
}

// call product function compare categories
bool pnode::category_match(pnode *& product_tocompare)
{
	if(a_product->category_compare(product_tocompare->a_product))
		return true;
	return false;
}

// call product function to compare categories
int pnode::category_match(product & product_tocompare)
{
	if(a_product->category_compare(product_tocompare))
		return 1;
	return 0;
}

// ship product to customer
bool pnode::ship_customer(char * my_transportation)
{
	if(a_product->ship_customer(my_transportation))
		return true;
	return false;
}

// add facility name to Product LLL (track)
bool pnode::track_facility(char * facility)
{
	if(a_product->track_facility(facility))
		return true;
	return false;
}

// display products path in the system
bool pnode::product_path()
{
	if(a_product->product_path())
		return true;
	return false;
}
