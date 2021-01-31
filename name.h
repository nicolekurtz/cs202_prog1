// Nicole Kurtz
#include "product.h"

//This file manages name and facility objects.
// Name is the base class to a the derived object, facility
// Every Facility has an array object which manages a list of categorized products
// Every facility has a BST to manage the priority replenishment of products
// The full list of facilities is kept in a LLL in the list class
// The list class has a node that points to a facility object

//const variable
const int selection_size = 25;


// this class manages an array of products
class array
{
	public:
		array(); //default constructor
		array(const array *& array_tocopy); // copy constructor
		~array(); //deconstructor
		bool ship_customer(char * provided, char * my_transportation); // remove quantity from product
		int add_product(product & my_product, char *& facility_name); // add product to array
		int add_product(product & product_toadd); // add product to array
		bool replenish_table(char * product_tofind); // replenish highest priority product with quantity
		bool find_product(char * provided_product, int priority); // find product in product array
		product *& return_product(char * provided_product); // returns a product back to calling routine
		bool display(); // display the products in array
		bool product_path(char * provided_product); // display path of product

	protected:
		pnode ** my_selection; // array of pointers
		int index; // track index

	private:
		void to_copy(pnode ** head, pnode ** copy_to); // copy contents of existing array
		void delete_array(pnode *& head, int & i); // recursive call to delete array
		void delete_array_lll(pnode *& head); // recursive call to delete LLL of array index
		bool replenish_table(pnode *& head, char * provided_product, int & i); // replenish quantity or product with highest priority
		bool replenish_table_lll(pnode *& head, char * provided_product); // replenish quantity of product with highest priority - LLL
		int add_product(pnode *& head, pnode *& temp, int & i); // add product to array
		product *& return_product(pnode *& head, char * provided_product, int & i); // return product copy from array
		product *& return_product_LLL(pnode *& head, char * provided_product); // search for product in LLL
		bool find_product(pnode * head, char * provided_product, int & i); // find product in product array
		bool find_product_LLL(pnode * head, char * provided_product); // search for product in LLL
		bool ship_customer(pnode *& head, char * provided, int & i, char * my_transportation); // remove quantity from product
		bool ship_customer_LLL(pnode *& head, char * provided, char * my_transportation); // check to see if product is in LLL, if so remove quantity
		void display_LLL(pnode *& head); // display items of LLL
		void display(pnode *& head, int & result, int & i); // display the products in array
		bool product_path(pnode * head, char * provided_product, int & i); // recursive function to display product path
		bool product_path_LLL(pnode * head, char * provided_product); // recursive function to display LLL of array index
};

// This class manages a binary search tree organized by priority
class table
{
	public:
		table(); //default constructor
		table(const table & to_copy); // copy constructor
		~table(); //deconstructor
		int display(); // display contents of BST
		bool priority_replenish(); // replenish products of highest priority
		bool add_product(product * my_product, int priority); // add products to replenish on BST
		bool repelenish_table(char *& product_tofind); // replenish top priority product
		bool get_top_priority(char *& product_tofind); // wrapper function to get the to priority node and delete

	protected:
		bnode * root;

	private:
		void copy_table(bnode * root, bnode * to_copy); // copy first arguments data into second argument
		bool delete_node(bnode *& root, char *& product_tofind); // delete nodes
		bool get_top_priority(bnode *& root, char *& product_tofind); // get the top priority node and delete
		void delete_table(bnode *& root); // delete contents of table
		int display(bnode * root); // recursive call to display replenish list
		bool add_product(bnode *& root, bnode * new_prod, int priority); // recursive call to add product to table

};

// The class manages te creation of a facility: name, type and location.
// This class will be in charge of changing and displaying the facilities
// information. It is the parent to the facility class. 
class name
{
	public:
		name(); // default constructor
		name(char * name_toadd, char * type_toadd, char * location_toadd); // add constructor with args
		name(const name * source); // copy constructor
		name(const name & source); // copy constructor
		~name(); // deconstructor
		int display(); // display facility name informatoin
		bool change_name(); // change name of facility
		bool change_location(); // change location of facility
		bool change_type(); // change type of facility: national or local

	protected:
		char * facility_name; // name of facility
		char * facility_type; // facility type: National or Local
		char * facility_location; // Facility location

	private:

};

// The class manages the shipping, discontinuation, addition, and display of products at facilities. 
// Additionally, each facility includes an array of categorized products which represent the 
// facilities inventory. Each facility will be saved in an array of all_facilities. Facility
// 'is a' name class (inheritance). It 'has a' product, transportation, and table class. 
class facility: public name
{
	public:
		facility(); // default constructor
		facility(const facility * copy); // copy constructor
		facility(const facility & copy); // copy constructor
		facility(char * f_name, char * type, char * location); // add constructor
		~facility(); // deconstructor
		bool find_name(char * provided_facility); // compare name
		bool display_list(); // display product list
		bool display_path(char * provided_path); // function to call display product path
		bool ship_customer(char * provided, char * my_transportation); // ship to a customer (remove quantity)
		bool product_found(); // display facilities that have product
		bool add_product(product & found_product); // add product to facility
		bool add_table(char * provided_product, int priority); // add product to replenishment table
		bool replenish_table(); // replenish priority table

	protected:
		product a_product; // product object
		array * product_array; // array of products organized by category
		table * priority_table; // bst for replenishing products

	private:

};

//This class manages a pointer to a facility
// It is used by the list class which handles a list of facilities
class node
{
	public:
		node(); // default constructor
		node(const node *& to_copy); // copy constructor
		~node(); // deconstructor
		node*& go_forward(); // move forward in list
		void set_next(node *& connection); // connect nodes in list
		bool display(); // display content of node
		bool display_list(); // display list of facilities
		bool display_path(char * provided_product); // display product path
		bool ship_customer(char * provided_product, char * my_transportation); // ship item to customer, reduce quantity of product at facility
		bool find_name(char * provided_facility); // check to see if facility name exists in node
		bool add_product(product & my_product); // function to add product to facility
		bool add_table(char * provided_product, int priority); // add product to priority table
		bool replenish_table(); // replenish highest priority product in BST
		facility * get_facility(); // return copied facility object to list class
		node(facility & to_add); // set nodes facility object
	protected:
		node * next; // pointer to the next node
		facility * a_facility; // facility object

	private:
};

//This class manages a linear linked list of FACILITIES
class list
{
	public:
		list(); // default constructor
		list(const list & to_copy); // copy constructor 
		~list(); // deconstructor
		int add_facility(facility & facility_toadd); // add facility to facility list
		bool find_facility(char * provided_facility); // find facility in faciliyt list
		bool display_list(char * provided_facility); // display facility list
		bool add_product(product & product_toadd, char * provided_facility); // add product to facility
		bool ship_customer(char * provided_facility, char * provided_product, char * my_transportation); // reduce quantity of product
		int display(); // display all info in the list of movemenet
		bool display_path(char * provided_facility, char * provided_product); // recursive call to display path
		bool add_table(char * facility_toget, char * product_toget, int priority); // add product to repenishment table
		bool replenish_table(char * facility_toget); // replenish highest priority product

	protected:
		node * head; // head of LLL of facilities

	private:
		void copy_list(node * head, node * to_copy); // copy list
		void delete_list(node *& head); // delete all items in a list
		int display(node * head); // recursive call to display
		bool replenish_table(node *& head, char * provided_facility); // recursive call to replenish table based on priority
		bool ship_customer(node * head, char * provided_facility, char * provided_product, char * my_transportation); // recursive to ship to cusomter
		bool find_facility(node * head, char * provided_facility); // recurive function to find facility
		bool display_path(node * head, char * provided_facility, char * provided_product); // recursive call to display path
		bool add_product(node * head, char * facility, product & product_toget); // recursive call to add product to facility
		bool add_table(node * head, char * facility_toget, char * product_toget, int priority); // recursive call to add product to table
		bool display_list(node * head, char * provided_facility); // recursive call to display items of faciilty list

};
