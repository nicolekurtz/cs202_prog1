// Nicole Kurtz
#include "name.h"
using namespace std;

/*
name variables:
		char * facility_name; // name of facility
		char * facility_type; // facility type: National or Local
		char * facility_location; // Facility location

facility variables:


*/

// This file manages the implementation of a name base class and facility derived class
// and a array, table, node and list
// Every Facility has an array object which manages a list of categorized products
// Every facility has a BST to manage the priority replenishment of products
// The full list of facilities is kept in a LLL in the list class
// The list class has a node that points to a facility object


///////* NAME FUNCTIONS *///////

// This is a base class that manages the name, type and location dynamic member

// Default constructor
name::name():facility_name(NULL), facility_type(NULL), facility_location(NULL)
{
}

// Constructor with arguments -- dynamic memory
name::name(char * name_toadd, char * type_toadd, char * location_toadd): facility_name(NULL), facility_type(NULL), facility_location(NULL)
{
	if(!name_toadd || !type_toadd || !location_toadd)
		return;

	facility_name = new char[strlen(name_toadd) + 1];
	strcpy(facility_name, name_toadd);

	facility_type = new char[strlen(type_toadd) + 1];
	strcpy(facility_type, type_toadd);

	facility_location = new char[strlen(location_toadd) + 1];
	strcpy(facility_location, location_toadd);

}

// copy constructor
name::name(const name & source): facility_name(NULL), facility_type(NULL), facility_location(NULL) {
	if(!source.facility_name || !source.facility_type || !source.facility_location)
		return;

	facility_name = new char[strlen(source.facility_name) + 1];
	strcpy(facility_name, source.facility_name);

	facility_type = new char[strlen(source.facility_type) + 1];
	strcpy(facility_type, source.facility_type);

	facility_location = new char[strlen(source.facility_location) + 1];
	strcpy(facility_location, source.facility_location);
}

// copy constructor
name::name(const name * source): facility_name(NULL), facility_type(NULL), facility_location(NULL) {
	if(!source->facility_name || !source->facility_type || !source->facility_location)
		return;

	facility_name = new char[strlen(source->facility_name) + 1];
	strcpy(facility_name, source->facility_name);

	facility_type = new char[strlen(source->facility_type) + 1];
	strcpy(facility_type, source->facility_type);

	facility_location = new char[strlen(source->facility_location) + 1];
	strcpy(facility_location, source->facility_location);
}


// Deconstructor
name::~name()
{
	// set variables to NULL
	if(facility_name)
		delete [] facility_name;
	if(facility_type)
		delete [] facility_type;
	if(facility_location)
		delete [] facility_location;
	
	facility_name = facility_type = facility_location = NULL;
}

// display name info
int name::display()
{
	// if there's no information return false
	if(!facility_name || !facility_type || !facility_location)
		return 0;

	cout << endl << "Facility Name: " << facility_name << endl;
	cout << "Facility Type: " << facility_type << endl;
	cout << "Facility Location: " << facility_location << endl;

	return 1;
}

// change name of name object
bool name::change_name()
{ 
	// if there's already information, delete it
	if(facility_name)
		delete [] facility_name;
	
	char temp[100];
	cout << endl << "Type the new name of your facility: ";
	cin.get(temp, 100, '\n');
	cin.ignore(100, '\n');

	facility_name = new char[strlen(temp) + 1];
	strcpy(facility_name, temp);
	
	return true;
}

// change location of name object
bool name::change_location()
{
	// if theres' no information, delete it
	if(facility_location)
		delete [] facility_location;
	
	char temp[100];
	cout << endl << "Type the new location of your facility: ";
	cin.get(temp, 100, '\n');
	cin.ignore(100, '\n');
	
	facility_location = new char[strlen(temp) + 1];
	strcpy(facility_location, temp);

	return true;
}

// change type of name
bool name::change_type()
{
	int response;
	char temp[100];
	cout << endl <<  "Facility Type Options:" << endl;
	cout << "1 - National" << endl;
	cout << "2 - Local" << endl;
	
	// user input
	cout << endl << "Type Number of " << facility_name << "'s New Facility Type: ";
	cin >> response;
	cin.ignore(100, '\n');
	
	// copy selection to variable
	switch(response)
	{
		case 1:
			strcpy(temp, "National");
			break;
		case 2:
			strcpy(temp, "Local");
			break;
	}
	
	// delete current information in variable
	delete [] facility_type;
	
	// copy information to variable
	facility_type = new char[strlen(temp) + 1];
	strcpy(facility_type, temp);

	return true;
}


///////* FACILITY FUNCTIONS *//////////

// The facility class manages the operations of a facility
// Every facility has an array of products
// and a BST of product replenishment

// default constructor
facility::facility()
{
	product_array = new array;
	priority_table = new table;
}

// copy constructor
facility::facility(const facility * copy): name(copy)
{
	product_array = new array;
	priority_table = new table;
}

// copy constructor
facility::facility(const facility & copy): name(copy)
{
	product_array = new array;
	priority_table = new table;
}

// add constructor
facility::facility(char * f_name, char * type, char * location): name(f_name, type, location)
{ 
	product_array = new array;
	priority_table = new table;
}

// deconstructor
facility::~facility()
{ 
	if(product_array)
		delete product_array;

	if(priority_table)
		delete priority_table;
}

// display product array list
bool facility::display_list()
{
	if(product_array->display())
		return true;
	return false;
}

// find compare facility and character array
bool facility::find_name(char * facility_tofind)
{
	if(strcmp(facility_name, facility_tofind) == 0)
		return true;
	return false;
}

// display path of product call
bool facility::display_path(char * provided_path)
{
	if(product_array->product_path(provided_path))
		return true;
	return false;
}

// add product to facility categorized produc list
bool facility::add_product(product & found_product)
{
	if(product_array->add_product(found_product, facility_name))
	{
		cout << endl << "---" << facility_name << "'s List of Products---" << endl;
		product_array->display();
		return true;
	}
	else
		return false;
}

// ship from facility to customer
bool facility::ship_customer(char * provided, char * my_transportation)
{
	if(product_array->ship_customer(provided, my_transportation))
		return true;
	return false;
}

// add product to replenishment table
bool facility::add_table(char * provided_product, int priority)
{
	// If product is found in facility array
	if(product_array->find_product(provided_product, priority))
	{
		//create new product based on product found
		product * copied_product = new product(product_array->return_product(provided_product));

		//add product to repleishment table
		priority_table->add_product(copied_product, priority);

		// display table
		if(priority_table)
		{
			cout << endl << "---Priority Table---" << endl;
			priority_table->display();
		}

		// delete dynamic memory
		delete copied_product;

		return true;
	}
	return false;
}

// remove highest priority from table
// increase quantity by 10
bool facility::replenish_table()
{
	char * product_tofind;

	if(priority_table->repelenish_table(product_tofind))
	{
		if(product_array->replenish_table(product_tofind))
		{
			if(product_tofind)
				delete [] product_tofind;
			return true;
		}
	}
	return false;
}

//////* ARRAY FUNCTIONS *//////

// This class manages an array of products organized by category
// It is used by teh facility class

// constructor
array::array()
{
	my_selection = new pnode *[selection_size];
	index = 0;

	for(int i=0; i < selection_size; ++i)
	{
		my_selection[i] = NULL;
	}
}

// copy constructor 
array::array(const array *& array_tocopy)
{
	my_selection = new pnode *[selection_size];

	if(array_tocopy->my_selection)
		to_copy(array_tocopy->my_selection, my_selection);

}

// copy product array 
void array::to_copy(pnode ** head, pnode ** copy_to)
{
	if(!*(head)) return;

	if(*(head))
	{
		pnode * temp = new pnode(*(head));
		*(copy_to) = temp;
	}

	return to_copy(++head, ++copy_to);
}

// deconstructor
array::~array()
{
	if(my_selection)
	{
		int i = 0;
		delete_array(my_selection[0], i);
	}
	delete [] my_selection;
}

// recursive call to delete array
void array::delete_array(pnode *& head, int & i)
{
	if(!head)
		return;

	if(head->go_forward())
	{
		delete_array_lll(head->go_forward());
	}

	delete head;
	head = NULL;

	++i;

	return delete_array(my_selection[i], i);
}

// recursive call to delete lll of array
void array::delete_array_lll(pnode *& head)
{
	if(!head) return;

	delete_array_lll(head->go_forward());

	delete head;
	head = NULL;
}

// increase top priority quantity
bool array::replenish_table(char * product_tofind)
{
	if(my_selection)
	{
		int i = 0;
		if(replenish_table(my_selection[0], product_tofind, i))
		{
			return true;
		}
	}
	return false;
}

// replenish quantity of product by 10
// this function finds location of product
bool array::replenish_table(pnode *& head, char * provided_product, int & i)
{	
	// make sure we don't go outside of array size	
	if(i == selection_size)
		return false;

	if(!head)
		return false;
	
	// if match found
	if(head->find_name(provided_product))
	{
		head->replenish();
		return true;
	}

	// if there's a LLL in index, check LLL
	if(head->go_forward())
	{
		if(replenish_table_lll(head->go_forward(), provided_product))
		{
			head->replenish();
			return true;
		}

	}
	
	// increase index
	++i;

	return replenish_table(my_selection[i], provided_product, i);
}

// replenish quantity of product by 10
// this function finds location of product in LLL
bool array::replenish_table_lll(pnode *& head, char * provided_product)
{
	if(!head)
		return false;

	// if match found
	if(head->find_name(provided_product))
	{
		head->replenish();
		return true;
	}
	
	return replenish_table_lll(head->go_forward(), provided_product);
}

// wrapper function to find product in product array 
bool array::find_product(char * provided_product, int priority)
{
	if(my_selection)
	{
		int i = 0;
		if(find_product(my_selection[0], provided_product, i))
		{
			return true;
		}
	}
	return false;
}

// recursive call to find product in product array
bool array::find_product(pnode * head, char * provided_product, int & i)
{
	// make sure we don't go outside of array size	
	if(i == selection_size)
		return false;

	if(!head)
		return false;
	
	// if match found
	if(head->find_name(provided_product))
	{
		return true;
	}

	// if there's a LLL in index, check LLL
	if(head->go_forward())
	{
		if(find_product_LLL(head->go_forward(), provided_product))
			return true;

	}
	
	// increase index
	++i;

	return find_product(my_selection[i], provided_product, i);
}

// find product in the LLL of index
bool array::find_product_LLL(pnode * head, char * provided_product)
{
	if(!head)
		return false;

	// if match found
	if(head->find_name(provided_product))
	{
		return true;
	}
	
	return find_product_LLL(head->go_forward(), provided_product);
}

// wrapper function return product to calling routing (this is for replenishment table)
product *& array::return_product(char * provided_product)
{
	int i = 0;

	return return_product(my_selection[0], provided_product, i);
}

// recursive call to return product to calling routine of LLL of array (this is for replenishment table
product *& array::return_product_LLL(pnode *& head, char * provided_product)
{
	// if product is found, return product
	if(head->find_name(provided_product))
		return head->get_product();

	return return_product_LLL(head->go_forward(), provided_product);
}


// recursive call to return product to calling routine of array (this is for replenishment table
product *& array::return_product(pnode *& head, char * provided_product, int & i)
{
	// if match found, return product
	if(head->find_name(provided_product))
	{
		return head->get_product();
	}
	
	// if tehre's a LLL of index
	if(head->go_forward())
	{
		// if match found in LLL, return product
		if(find_product_LLL(head->go_forward(), provided_product))
			return return_product_LLL(head->go_forward(), provided_product);

	}

	// increase index
	++i;

	return return_product(my_selection[i], provided_product, i);
}

// add product to array
int array::add_product(product & my_product, char *& facility_name)
{
	// add product to node
	pnode * temp = new pnode(my_product);

	temp->track_facility(facility_name);
	
	// if nothings in temp, return false
	if(!temp)
		return 0;
	
	// if array is empty, add temp to first index
	if(!my_selection[0])
	{
		my_selection[0] = temp;
		++index;
		return 1;
	}

	int i = 0;
	
	// call recursive function to add product to matching array or first empty index
	return add_product(my_selection[0], temp, i);
}

// recursive function to add product to array index
int array::add_product(pnode *& head, pnode *& temp, int & i)
{
	// make sure we dont go outside of array size
	if(i == selection_size)
		return false;

	// if the index is empty, add temp to it
	if(!head)
	{
		++index;
		head = temp;
		return 1;
	}
	
	// if current node and temp match
	// add temp to LLL  index
	if(head->category_match(temp))
	{
		temp->set_next(head);
		head = temp;
		return 1;
	}

	// track index
	++i;

	return add_product(my_selection[i], temp, i);
}

// wrapper function to call function to display product path
bool array::product_path(char * provided_product)
{
	int i=0;
	return product_path(my_selection[0], provided_product, i);
}

// recursive function to call function to display product path
bool array::product_path(pnode * head, char * provided_product, int & i)
{
	if(i == selection_size)
		return false;
	if(!head)
	{
		return false;
	}
	
	if(head->find_name(provided_product))
	{
		head->product_path();
		return true;
	}

	if(head->go_forward())
		if(product_path_LLL(head->go_forward(), provided_product))
			return true;

	// track index
	++i;

	return product_path(my_selection[i], provided_product, i);
}

// display product path of LLL of index
bool array::product_path_LLL(pnode * head, char * provided_product)
{
	if(!head)
		return 0;
	
	// if match, display product path
	if(head->find_name(provided_product))
	{
		head->product_path();
		return true;
	}

	return product_path_LLL(head->go_forward(), provided_product);
}

// wrapper function to ship to customer
// reduce quantity of product
bool array::ship_customer(char * provided, char * my_transportation)
{
	int i = 0;
	return ship_customer(my_selection[0], provided, i, my_transportation);
}

// recursive function to ship to customer
// reduce quantity of product
bool array::ship_customer(pnode *& head, char * provided, int & i, char * my_transportation)
{
	if(i == selection_size)
		return false;
	if(!head)
	{
		return false;
	}
	
	if(head->find_name(provided))
	{
		head->ship_customer(my_transportation);
		return true;
	}

	if(head->go_forward())
		if(ship_customer_LLL(head->go_forward(), provided, my_transportation))
			return true;

	// track index
	++i;

	return ship_customer(my_selection[i], provided, i, my_transportation);
}

// look for matching provided character in array, remove quantity if found
bool array::ship_customer_LLL(pnode *& head, char * provided, char * my_transportation)
{
	if(!head)
		return 0;
	
	// compare name
	if(head->find_name(provided))
	{
		head->ship_customer(my_transportation);
		return true;
	}

	return ship_customer_LLL(head->go_forward(), provided, my_transportation);
}


// display content of array
bool array::display()
{
	int result = 0;
	int i = 0;

	// if array exits, call recurse function to display contents
	if(my_selection)
	{
		if(!my_selection[0])
			return false;
		display(my_selection[0], result, i);
		return true;
	}
	return false;
}

// recursive function to display content of array
void array::display(pnode *& head, int & result, int & i)
{
	// track to make sure array doesn't go outside of array indices
	++result;
	if(result > index)
		return;
	
	// if array index is empty, nothing more to display
	if(!head)
	{
		return;
	}
	
	// call display function
	head->display();
	
	// if there's item in the LLL of the index, call and display
	if(head->go_forward())
		display_LLL(head->go_forward());
	
	//track index
	++i;

	return display(my_selection[i], result, i);
}

// recursive function to display LLL of index
void array::display_LLL(pnode *& head)
{
	if(!head)
		return;
	
	// display contents of index
	head->display();

	return display_LLL(head->go_forward());
}
			

/////* TABLE FUNCTIONS */////

// This class manages a Binary Search tree
// organized by priority level

// default constructor
table::table(): root(NULL)
{
}

// copy constructor
table::table(const table & to_copy)
{
	if(root)
		copy_table(root, to_copy.root);
}

// copy roots data to to_copies BST
void table::copy_table(bnode * root, bnode * to_copy)
{
	if(!root)
		return;
	
	to_copy = new bnode(*root);

	copy_table(root->go_left(), to_copy->go_left());
	copy_table(root->go_right(), to_copy->go_right());
}

// deconstructor
table::~table()
{
	if(root)
		delete_table(root);
}

// delete table
void table::delete_table(bnode *& root)
{
	if(!root)
		return;

	delete_table(root->go_left());

	delete_table(root->go_right());

	delete root;
}

// display products in priority table
int table::display()
{
	if(!root)
		return 0;
	if(display(root) == 0)
		return false;
	return true;
}

// recursive display of products in priotity table
int table::display(bnode * root)
{
	int result = 0;

	if(!root)
		return 0;
	
	root->display();

	result = display(root->go_left()) + 1;

	result += display(root->go_right()) + 1;

	return result;
}


// add products to replenish table
bool table::add_product(product * my_product, int priority)
{
	bnode * new_prod = new bnode(my_product, priority);
	
	if(!root)
	{
		root = new_prod;
		return true;
	}

	return add_product(root, new_prod, priority);
}

// add product to replenish table
bool table::add_product(bnode *& root, bnode * new_prod, int priority)
{
	if(!root)
	{
		root = new_prod;
		return true;
	}
	
	//if root is greater or equal to priority, go left
	if(root->compare_prio(priority))
		add_product(root->go_left(), new_prod, priority);

	//otherwise, root is smaller than priority, go right
	else
		add_product(root->go_right(), new_prod, priority);

	return false;
}

// replenish top priority product
bool table::repelenish_table(char *& product_tofind)
{
	if(get_top_priority(product_tofind))
		return true;
	return false;
}

// fill pointer with top priority product
bool table::get_top_priority(char *& product_tofind)
{
	if(!root)
		return false;
	
	return get_top_priority(root, product_tofind);
}

// recursive function to fill pointer with top priority product
bool table::get_top_priority(bnode *& root, char *& product_tofind)
{
	if(!root->go_left())
	{
		delete_node(root, product_tofind);
		return true;
	}


	return get_top_priority(root->go_left(), product_tofind);
}

// function to remove node based on children
bool table::delete_node(bnode *& root, char *& product_tofind)
{
	bnode * hold = NULL;

	// empty tree
	if(!root)
		return false;

	// no children
	if(!root->go_right() && !root->go_left())
	{
		root->get_name(product_tofind);
		delete root;
		root = NULL;
		return true;
	}
	
	// only left child - left child becomes root
	if(!root->go_right() && root->go_left())
	{
		root->get_name(product_tofind);
		hold = root->go_left();
		delete root;
		root = hold;
		return true;
	}

	// only right child - right child becomes root
	if(!root->go_left() && root->go_right())
	{
		root->get_name(product_tofind);
		hold = root->go_right();
		delete root;
		root = hold;
		return true;
	}

	//two chlildren
	if(root->go_right() && root->go_left())
	{
		root->get_name(product_tofind);
		hold = root->go_right();
		bnode * child = NULL;

		// if there's no child to the right child of root
		if(!hold->go_left())
		{
			hold = root->go_right();
			child = hold->go_right();

			// add right child to root - NEED TO ADD THIS
			if(!(root->add(hold)))
				return false;

			root->go_right() = child;
			delete hold;
			hold = NULL;
			
			return true;
		}

		else
		{
			bnode * parent = NULL;

			while(hold->go_right())
			{
				hold->go_right();
			}

			child = hold->go_right();

			// add the smallest value object to the root
			//ADD THIS
			if(!(root->add(hold)))
				return false;

			delete hold;
			hold = NULL;

			parent->set_left(child);

			return true;
		}
	}
	return false;
}



////////* NODE FUNCTIONS *//////////

// This class manages a node which points to a facility
// it is used by the list class to keep track of facilities

// default constructor
node::node(): next(NULL)
{
}

// copy constructor 
node::node(const node *& to_copy)
{
	a_facility = new facility(to_copy->a_facility);
}

// deconstructor
node::~node()
{
	next = NULL;

	if(a_facility) 
		delete a_facility;
}

// returns next node to calling routine
node*& node::go_forward()
{
	return next;
}

// sets the next node to argument node
void node::set_next(node *& connection)
{
	next = connection;
}

// node facility copy constructor
node::node(facility & add_facility)
{
	a_facility = new facility(add_facility);
}

// call facility display function
bool node::display()
{
	if(!a_facility)
		return false;
	a_facility->display();
	return true;
}

//check to see if passed facility name exists in node
bool node::find_name(char * provided_facility)
{
	if(a_facility->find_name(provided_facility))
	{
		return true;
	}
	return false;
}

// add product to facility product array
bool node::add_product(product & my_product)
{
	if(a_facility->add_product(my_product))
		return true;
	return false;
}

// display list of facilities
bool node::display_list()
{
	if(a_facility->display_list())
		return true;
	return false;
}

// return facility object
facility * node::get_facility()
{	
	return a_facility;
}

// ship product to customer
bool node::ship_customer(char * provided_product, char * transportation_toadd)
{
	if(a_facility->ship_customer(provided_product, transportation_toadd))
		return true;
	return false;
}

// display product path
bool node::display_path(char * provided_product)
{
	if(a_facility->display_path(provided_product))
		return true;
	return false;
}

// add product to priority table
bool node::add_table(char * provided_product, int priority)
{
	if(a_facility->add_table(provided_product, priority))
		return true;
	return false;
}

// replenish product of highest priority in replenishment BST
bool node::replenish_table()
{
	if(a_facility->replenish_table())
		return true;
	return false;
}

//////////////* LIST FUNCTION *//////////////

// This class manages a linear linked list of facilities
// it has a node which points to a facility

// constructor
list::list(): head(NULL)
{
}

// copy constructor
list::list(const list & to_copy)
{
	if(to_copy.head)
		copy_list(head, to_copy.head);
}

// copy list 
void list::copy_list(node * head, node * to_copy)
{
	if(!head) return;
	
	to_copy = new node(*head);

	copy_list(head->go_forward(), to_copy->go_forward());
}


// Add facility to list 
int list::add_facility(facility & add_facility)
{
	// copy constructor to node
	node * temp = new node(add_facility);
	
	// if there's no head, the new node is head
	if(!head)
	{
		head = temp;
		return 1;
	}
	
	// if there is head, make the temp head and connect
	else
	{
		temp->set_next(head);
		head = temp;
		return 1;
	}
	return 0;
}

// deconstructor
list::~list()
{
	if(head)
		delete_list(head);
}

// display product path wrapper function
bool list::display_path(char * provided_facility, char * provided_product)
{
	return display_path(head, provided_facility, provided_product);
}

//display product path
bool list::display_path(node * head, char * provided_facility, char * provided_product)
{

	if(!head)
		return false;

	// call node function to check if facility exists
	if(head->find_name(provided_facility))
	{
		head->display_path(provided_product);
		return true;
	}
	
	// otherwise, call function agian and move down list
	return display_path(head->go_forward(), provided_facility, provided_product);
}

// Add product to replenishment table
bool list::add_table(char * facility_toget, char * product_toget, int priority)
{
	return add_table(head, facility_toget, product_toget, priority);
}

// add product to replenishment table
bool list::add_table(node * head, char * provided_facility, char * provided_product, int priority)
{
	// if there's no head, we no there's no facility to match
	if(!head)
		return false;

	// call node function to check if facility exists
	if(head->find_name(provided_facility))
	{
		if(head->add_table(provided_product, priority))
			return true;
		return false;
	}
	
	// otherwise, call function agian and move down list
	return add_table(head->go_forward(), provided_facility, provided_product, priority);
}

// wrapper function to ship product to customer
bool list::ship_customer(char * provided_facility, char * provided_product, char * transportation_toadd)
{
	return ship_customer(head, provided_facility, provided_product, transportation_toadd);
}

// recursive function to ship product to customer
bool list::ship_customer(node * head, char * provided_facility, char * provided_product, char * transportation_toadd)
{
	// if there's no head, we no there's no facility to match
	if(!head)
		return false;

	// call node function to check if facility exists
	if(head->find_name(provided_facility))
	{
		head->ship_customer(provided_product, transportation_toadd);
		return true;
	}
	
	// otherwise, call function agian and move down list
	return ship_customer(head->go_forward(), provided_facility, provided_product, transportation_toadd);
}

// check to see if facility exists wrapper function
bool list::find_facility(char * provided_facility)
{
	// call recursive function to find facility
	if(find_facility(head, provided_facility))
		return true;
	return false;
}

// recurse function to find facility in list
bool list::find_facility(node * head, char * provided_facility)
{
	// if there's no head, we no there's no facility to match
	if(!head)
		return false;
	// call node function to check if facility exists
	if(head->find_name(provided_facility))
	{
		facility copied_facility(head->get_facility());
		return true;
	}
	
	// otherwise, call function agian and move down list
	return find_facility(head->go_forward(), provided_facility);
}

// wrapper function to add product to product array
bool list::add_product(product & product_toadd, char * provided_facility)
{
	if(add_product(head, provided_facility, product_toadd))
		return true;
	return false;
}

// add product to product array
bool list::add_product(node * head, char * provided_facility, product & product_toadd)
{
	if(!head)
		return false;
	
	// if match found
	if(head->find_name(provided_facility))
	{
		head->add_product(product_toadd);
		return true;

	}
	return add_product(head->go_forward(), provided_facility, product_toadd);
}

// delete all items in a linear linked list
void list::delete_list(node *& head)
{
	// if there's no head, return
	if(!head)
		return;
	
	// otherwise go to end of list
	delete_list(head->go_forward());
	
	// delete all nodes 
	delete head;
	head = NULL;
}

//display facility list wrapper function
bool list::display_list(char * facility_toget)
{
	// call recursive function to find facility
	if(display_list(head, facility_toget))
		return true;
	return false;
}

// recurse function to display facility in list
bool list::display_list(node * head, char * provided_facility)
{
	// if there's no head, we no there's no facility to match
	if(!head)
		return false;
	// call node function to check if facility exists
	if(head->find_name(provided_facility))
	{
		if(head->display_list())
			return true;
		return false;
	}
	
	// otherwise, call function agian and move down list
	return find_facility(head->go_forward(), provided_facility);
}

// wrapped function to call recursive display function
int list::display()
{
	if(display(head))
		return true;
	return false;
}

// recursive call to display
int list::display(node * head)
{
	if(!head)
		return 0;
	
	// call nodes display function
	head->display();

	return display(head->go_forward()) + 1;
}

// replenish product in facility with highest priority
bool list::replenish_table(char * facility_toget)
{
	return replenish_table(head, facility_toget);
}

// recursive callt o replenish product in facility with highest priority
bool list::replenish_table(node *& head, char * provided_facility)
{
	// if there's no head, we no there's no facility to match
	if(!head)
		return false;

	// call node function to check if facility exists
	if(head->find_name(provided_facility))
	{
		if(head->replenish_table())
			return true;
		return false;
	}
	
	// otherwise, call function agian and move down list
	return replenish_table(head->go_forward(), provided_facility);
}
