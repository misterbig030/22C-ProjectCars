#include<iostream>
//#include<cstdlib>
#include"car.h"

//using namespace std;

template <typename T>
class node
{
protected:
	T* data;
	node* nextptr;
public:
	node(node* ptr);
	node(T d, node* ptr);
	node* get_next() const;
	T& get_data() const;
	void set_next(node* ptr);
	void set_data(T t);
	void remove_data();
	~node();
};
/*
This is the default constructor for a node. Initializes data to nullptr
Pre : ptr ?pointer to the next node in the sequence

Post : data - initializes data to nullptr, sets the next pointer to the parameter received
*/
template <typename T>
node<T>::node(node* ptr) : data(nullptr), nextptr(ptr)
{
}

/*
This is another constructor for a node. Initializes data to whatever is passed to it
Pre : ptr ?pointer to the next node in the sequence
d - an object of any type
Post : data, nextptr
*/
template <typename T>
node<T>::node(T d, node* ptr) : data(new T(d)), nextptr(ptr)
{
}

/*
Returns the address of the next node in sequence
Pre :
Post :

Return: nextptr
*/
template <typename T>
node<T>* node<T>::get_next() const
{
	return nextptr;
}

/*
Returns the data held in the node
Pre :
Post :

Return: *data
*/
template <typename T>
T& node<T>::get_data() const
{

	return *data;
}

/*
Sets the next pointer to an address passed to the function
Pre : ptr - address of next node
Post : nextptr
Return:
*/
template <typename T>
void node<T>::set_next(node* ptr)
{
	nextptr = ptr;
}

/*
Sets the data held in the node to the object passed to the function
Pre : t - input data
Post : data
Return:
*/
template <typename T>
void node<T>::set_data(T t)
{
	remove_data();
	data = new T(t);
}

/*
Removes data held in node
Pre :
Post : data - set to null
Return:
*/
template <typename T>
void node<T>::remove_data()
{
	if (data)
	{
		delete data;
	}
}

/*
Destroy the node. Release memory
Pre :
Post :
Return:
*/
template <typename T>
node<T>::~node()
{
	//remove_data();
	nextptr = nullptr;
}

/*
A special type of node - headnode.
Will be the first node of a list, queue, stack, etc.
*/
template <typename T>
class headnode : public node<T>
{
protected:
	node<T>* rearptr;
	unsigned count;
public:
	headnode(unsigned c, node<T>* hptr, node<T>* rptr);
	node<T>* get_rearptr();
	unsigned get_count() const;
	void incrementCount();
	void decrementCount();
	void setRearptr(node<T>* p);
	void reset_count();
};

/*
A constructor to initialize data members of headnode
Pre : c- number of nodes in data structure
hptr- address of first node following the headnode
rptr- address of last node in the data structure
Post :
Return:
*/
template <typename T>
headnode<T>::headnode(unsigned c, node<T>* hptr, node<T>* rptr) : count(c), node<T>(hptr), rearptr(rptr)
{
}

/*
Return the address of the last node in data structure
Pre :
Post :
Return: rearptr - address of the last node in data structure
*/
template <typename T>
node<T>* headnode<T>::get_rearptr()
{
	return rearptr;
}

/*
Return number of nodes in data structure
Pre :
Post :
Return: count - number of nodes in data structure
*/
template <typename T>
unsigned headnode<T>::get_count() const
{
	return count;
}

/*
Increment the number of nodes
Pre:
Post: count
Return:
*/
template <typename T>
void headnode<T>::incrementCount()
{
	count++;
}

/*
Decrement the number of nodes
Pre:
Post: count
Return:
*/
template <typename T>
void headnode<T>::decrementCount()
{
	count--;
}

/*
Set the address of the last node in data structure to the address passed
Pre: p - input address
Post: rearptr
Return:
*/
template <typename T>
void headnode<T>::setRearptr(node<T>* p)
{
	rearptr = p;
}

/*
Reset the count (number of nodes in data structure is 0)
Pre:
Post: count
Return:
*/
template <typename T>
void headnode<T>::reset_count()
{
	count = 0;
}

template <typename T>
class List
{
protected:
	headnode<T> H;
	unsigned comprsnCount;
	unsigned insertCount;
public:
	List();
	headnode<T>& get_headnode();
	unsigned get_count() const;
	void printCount(std::ostream& fout) const;
	void emptyList();
	bool findByHP(unsigned t) const;
	T* findByModel(std::string t) const;
	bool isEmpty() const;
	void insert(T* t);
	bool remove(std::string t, std::ostream& fout = cout);
	std::ostream& print(std::ostream& fout = cout) const;
	unsigned getCmCount() const;
	unsigned getInsertCount() const;
	void clearCount();
	~List();
};

/*
Default constructor for a linked list. Initializes members to 0/null
Pre:
Post:
Return:
*/
template <typename T>
List<T>::List() : H(0, nullptr, nullptr), comprsnCount(0), insertCount(0)
{
}

/*
Return headnode
Pre:
Post:
Return: H - headnode of list
*/
template <typename T>
headnode<T>& List<T>::get_headnode()
{
	return H;
}

/*
Inserts a specified value to a specified position in the list
Pre: p - position to insert object in
t - data to be inserted
Post:
Return:
*/
template<typename T>
void List<T>::insert(T* t)
{
	node<T>* temp1 = H.get_next();
	node<T>* temp2 = nullptr;

	if (temp1 == nullptr)
	{
		H.set_next(new node<T>((*t), temp1));
		H.incrementCount();
		//if (temp1 == nullptr)
		H.setRearptr(H.get_next());
		insertCount++;
		return;
	}


	if (t->getHp() <= temp1->get_data().getHp())
	{
		comprsnCount++;
		H.set_next(new node<T>((*t), temp1));
		H.incrementCount();
		insertCount++;
		return;
	}

	while (t->getHp() > temp1->get_data().getHp())
	{
		comprsnCount++;
		temp2 = temp1;
		temp1 = temp1->get_next();
		if (temp1 == nullptr)
		{
			temp2->set_next(new node<T>(*t, nullptr));
			H.incrementCount();
			H.setRearptr(temp2->get_next());
			insertCount++;
			return;
		}
	}

	comprsnCount++;
	temp2->set_next(new node<T>((*t), temp1));
	H.incrementCount();

	if (temp1 == nullptr)
		H.setRearptr(temp2->get_next());

	insertCount++;
}

/*
Remove a node holding the specified value from the list if it exists.
Pre: t - value to be removed
fout - stream to print appropriate message to
Post:
Return: true/false depending on if the operation is successful
*/
template<typename T>
bool List<T>::remove(std::string t, std::ostream& fout)
{
	node<T>* temp1 = H.get_next();
	node<T>* temp2 = 0;

	if (H.get_next() == nullptr)
	{
		fout << "List is empty" << endl << endl;
		return false;
	}

	if (t == temp1->get_data().getModel())
	{
		H.set_next(temp1->get_next());
		if (temp1->get_next() == nullptr)
			H.setRearptr(nullptr);
		H.decrementCount();
		delete temp1;
		return true;
	}

	while (temp1 != nullptr)
	{
		if (temp1->get_data().getModel() == t)
		{
			H.decrementCount();
			temp2->set_next(temp1->get_next());
			if (temp1->get_next() == nullptr)
				H.setRearptr(temp2);
			delete temp1;
			return true;
		}
		temp2 = temp1;
		temp1 = temp1->get_next();
	}

	fout << "Value not found" << endl << endl;
	return false;
}

template <typename T>
unsigned List<T>::getCmCount() const
{
	return comprsnCount;
}

template <typename T>
unsigned List<T>::getInsertCount() const
{
	return insertCount;
}

template <typename T>
void List<T>::clearCount()
{
	comprsnCount = 0;
	insertCount = 0;
}

/*
Return number of nodes in linked list
Pre:
Post:
Return: count - number of nodes in linked list
*/
template <typename T>
unsigned List<T>::get_count() const
{
	return H.get_count();
}

/*
Print the number of nodes in the list to a specified stream
Pre: fout - specified stream
Post:
Return:
*/
template <typename T>
void List<T>::printCount(std::ostream& fout) const
{
	fout << "The list has " << get_count() << " objects" << endl << endl;
}

/*
Clear contents of list. Release memory
Pre:
Post:
Return:
*/
template <typename T>
void List<T>::emptyList()
{
	node<T>* temp = H.get_next();
	while (temp != nullptr)
	{
		H.set_next(temp->get_next());
		delete temp;
		temp = H.get_next();
	}
	H.reset_count();
}

/*
Find a specified object in the list
Pre: t - object to be searched for
Post:
Return: true/false depending on if the operation is successful
*/
template <typename T>
bool List<T>::findByHP(unsigned t) const
{
	node<T>* temp = H.get_next();
	while (temp != nullptr)
	{
		if (t <= temp->get_data().getHp())
		{
			while (temp != nullptr)
			{
				cout << temp->get_data() << endl;
				temp = temp->get_next();
			}
			cout << endl;
			return true;
		}
		temp = temp->get_next();
	}
	return false;
}

/*
Find a specified object in the list
Pre: t - object to be searched for
Post:
Return: true/false depending on if the operation is successful
*/
template <typename T>
T* List<T>::findByModel(std::string t) const
{
	node<T>* temp1 = H.get_next();
	while (temp1 != nullptr)
	{
		if (t == temp1->get_data().getModel())
			return &(temp1->get_data());
		temp1 = temp1->get_next();
	}
	return nullptr;
}

/*
Print all objects held in the nodes in a list
Pre: fout - stream to print to
Post:
Return:
*/
template <typename T>
std::ostream& List<T>::print(std::ostream& fout) const
{
	node<T>* temp = H.get_next();
	while (temp != nullptr)
	{
		fout << temp->get_data() << endl;
		temp = temp->get_next();
	}
	fout << endl;
	return fout;
}

/*
Check if list is empty
Pre:
Post:
Return: true/false depending on if the operation is successful
*/
template <typename T>
bool List<T>::isEmpty() const
{
	if (H.get_next() == nullptr)
		return true;
	else
		return false;
}

/*
Clear contents of list. Release memory
Pre:
Post:
Return:
*/
template <typename T>
List<T>::~List()
{
	emptyList();
}