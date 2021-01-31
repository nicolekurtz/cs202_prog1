// Nicole Kurtz
#include <iostream>
#include <cctype>
#include <cstring>
#include "transportation.h"

// This manages the product class which contains a name, strategy, category
// quantity and price. Every product has a track, a lll of the movement of a product
// Every track has a tnode which points to a transportation object
// There is also a pnode which is used by a LLL to point to a product
// There is also a bnode which is used by a BST to point to a product


// this is a linear linked list that tracks the path of a product 
class track
{
	public:
		track(); // default constructor
		track(const track & track_tocopy); // copy constructor
		void copy_tnodes(tnode * head, tnode * to_copy); // recursively copies nodes
		~track(); // deconstructor
		bool add_trans(transportation & add_tran, int & time); // add transportation object
		bool add_node(char * facility, int & time); // add node to LLL
		bool display(); // display product path

	protected:
		tnode * head; //transportation pointer to ehad

	private:
		void delete_nodes(tnode *& head); // delete nodes in list
		bool display(tnode * head); // display product list
};

// This class manages the creatoin, display and editing of a product. It 'has a' list class. 
class product
{
	public:
		product(); // default constructor
		~product(); // deconstructor
		product(char * name_add, char * strategy_add, char * category_add, int quantity_add, float price_add); // add constructor
		product(const product & product_toadd); // copy constructor
		product(const product * product_toadd); // copy constructor
		bool find_name(char * provided_product); // see if name matches
		bool ship_customer(char * my_transportation); // reduce quantity of product by one
		bool get_name(char *& name_toget); // get the name of the facility
		bool replenish(); // replenish quantity by 100
		bool display(); // display info about a product
		int get_strategy_time(); // returns amount of days the product takes to travel
		bool product_path(); // display product path
		bool category_compare(product & product_tocompare); //compare category of passed product and current 
		bool category_compare(product *& product_tocompare); // compare categories of products
		bool track_facility(char * facility_name); // add facility to product track list

	protected:
		char * name; // name of product
		char * strategy; // strategy of product
		char * category; // category of product
		float price; // price of product
		int quantity;  // quantity of product
		track * p_path; // pointer to a lll of products path

	private:
};

// this class manages a pointer to a product object for a LLL
class pnode
{
	public:
		pnode(); // default constructor
		~pnode(); // deconstructor
		pnode(const product & to_add); // set nodes facility object
		pnode(const pnode * to_copy); // copy constructor
		pnode*& go_forward(); // move forward in list
		product *& get_product(); // return copied facility object to list class
		bool add_product(char * facility_toget, char * product_toget); // add product to facility
		bool find_name(char * name); // find name that matches product
		bool product_path(); // display product path
		int category_match(product & to_compare); // compare categories 
		bool category_match(pnode *& product_tocompare); // compare categories of nodes
		void set_next(pnode *& connection); // connect nodes in list
		bool replenish(); // replenish products quantity
		void display(); // display content of node
		bool ship_customer(char * my_transportation); // ship a product to a customer, reduce quantity
		bool track_facility(char * facility); // add facility name to LLL of product
	protected:
		product * a_product;
		pnode * next;
	private:
};

// this class manages a pointer to a product object for a BST
class bnode
{
	public:
		bnode(); // default constructor
		bnode(const product * my_product, int priority); // add constructor
		bnode(const bnode & node); // copy constructor
		~bnode(); // deconstructor
		bool add(const bnode * to_add); // replace contents of node with new node
		bnode *& go_left(); // moves left on the BST
		bnode *& go_right(); // moves right on BST
		bool get_name(char *& name_toget); // get the name of the product
		void set_left(bnode *& connection); // connect node to left
		void set_right(bnode *& connection); // connect node to right
		bool display(); // display product info of node
		bool compare_prio(int priority); // compare priority to current root
	
	protected:
		product * a_product;
		bnode * left;
		bnode * right;
		int priority;
	
	private:
};

