// Nicole Kurtz

// This file includes the objects related to transportation.
// It includes a transportation object and a tnode which is
// a node that points to a transportation object

//This class manages the creation, display, and return of transportation information
class transportation
{
	public:
		transportation(); // default constructor
		transportation(char * type_toadd, int & time_toadd); // add constructor
		transportation(const transportation & transport_toadd); // copy constructor
		~transportation(); // deconstructor
		bool display(); // display info of transporation class
		bool change_type(); // change type of transportation
		bool change_time(); // change time of transportation

	protected:
		char * type; // type of transportation (ex: truck, plane, etc)
		int time; // time it takes to deliver item
	private:

};

// This class maanges a pointer to a transportation object and a node pointer.
class tnode
{
	public:
		tnode(); // default constructor
		tnode(const tnode & to_add); // copy constructor
		tnode(const transportation & add_trans, int & time); // copy constructor
		tnode(char * facility_name); // add consturctor
		tnode(char *&, int &); // add constructor
		~tnode(); // deconstructor
		tnode *& go_forward(); // move right
		void set_next(tnode *& connection); // set the next value of the node
		transportation * get_tran(); // return transportation object
		void display(); // display tnode

	protected:
		transportation * transport; // transportation object
		tnode * next; // right pointer to a tnode

	private:

};
