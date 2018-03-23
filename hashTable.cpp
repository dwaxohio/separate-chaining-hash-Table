/*
 *hashTable.cpp
 *Course:  Data Structure and Algorithm Analysis
 *Created on : Jan 31, 2018
 *
 * The program contains three classes: Node, LinkedList and HashTable classes.
 * HashTable is implemented to simulate a separate chaining hash table by utilizing LinkedList class, which utilizes Node class.
 * The HashTable class has an array of LinkedLists which takes the size of the table as the vector size.
 * The HashTable mainly utilizes insertion, deletion, search of the record in the LinkedList.
 * Hash function is used to create a index of hash table based on the string type key.
 * The LinkedList class implements a singly linked list, which mainly utilize insertion, deletion and search of the node by key of the Node.
 * The Node class has a string type key and long long type value along with Node pointer to the next node.
 *
 * The main function reads in a file with various information to input in hash table.
 * First, it reads in the size of hash table, number of command lines.
 * The size of the hash table will not be larger than 16381, and will always be prime.
 * the load factor will not exceed 10.
 * Then, there are four different command characters: I (insert record), D (delete record), S (search record) and P (print record).
 * I is followed by a string type key and a long long type value to insert if the key doesn't exist
 * D is followed by a string type key to delete if the key exists
 * S is followed by a string type key to search and print the key and value if exist.
 *
 */


#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>

//the element part of the Linked List.
class Node
{
private:
	// the linkage in the singly linked list
	Node* next;
	//the key of the element
	std::string key;
	// the data stored
	long long value;
public:
	//constructor
	Node(std::string ky, long long val, Node* nxt);
	//Update the next Node
	void setNext(Node *nxt);
	//retrieve and return next Node
	Node* getNext();
	//return the key stored in the node as a const
	const std::string& getKey() const;
	//return the value stored in the node as a const
	const long long getValue() const;
};

//singly linked list
class LinkedList
{
private:
	//pointer for first node in the linked list
	Node* head;
public:
	//constructor
	LinkedList();
	//destructor
	virtual ~LinkedList();
	//insert at head, or do nothing as well as returning false if key is already present.
	bool insert(std::string key, long long value);
	//if matched key is found, delete the node and return true.
	//otherwise, do nothing and return false.
	bool deleteNode(std::string key);
	//return result of the search. Return true if found, otherwise false.
	bool find(std::string key);
	//return the value for matching key. Return -1 if the key is not found
	long long findValue(std::string key);
	//return true if the LinkedList is empty
	bool empty() const;
	//delete the first node in the list.
	void deleteFrontNode();
	//return the size of the Linked List: number of nodes in the linked list.
	int size();
	//debug tool that prints the linked list with information of nodes
	void debug(std::ostream &out);
};

//separate chaining hash table with singly linked list
class HashTable{
private:
	//pointer for declaring an array
	LinkedList * hashLinkedList;
	//size of the hash table
	unsigned int hashTableSize;
public:
	//constructor
	HashTable(int size);
	//destructor
	virtual ~HashTable();
	//attempt to insert a record.
	//Return false if the key is already present in the table.
	//Otherwise insert and return true.
	bool insert(std::string key, long long val);
	//attempt to delete a record, Return false if the key isn't present in the table.
	bool deleteRecord(std::string key);
	//attempt to find a record. Return the value or -1 if the key is not found.
	long long search(std::string key);
	//empty the hash table.
	void clearTable();
	//returns the number of records in the table
	int size();
	//the function to create a index in the hash table for the key based on its key character and length
	static int hash(std::string key, unsigned int tableSize);
	//debug tool that prints the linked list with information of nodes.
	//it calls the Linked List of debug
	void debug(std::ostream &out);

};





//main driver. First, size of table and number of command lines are inputted.
//Then take stream of command inputs with character command I, D or S
//Then appropriate key and value to be inserted in hash table.
int main()
{
	unsigned int sizeOfTable; //size of Table; it must be prime number.
	unsigned int numberOfLines; //number of command lines input after size of Table.
	unsigned int lineCount = 1; //to give correct number of new line.
	char command; // a character of command: I, D or S.
	std::string key; //string type key as part of the node in the linked list of hash table.
	long long value; //long long type value as part of the node in the linked list of hash table.


//	std::ifstream inputFile;
//	inputFile.open("p1d1in.txt");
//	std::ofstream outputFile;
//	outputFile.open("p1d1out.txt");

//	if (inputFile.is_open())
//	{
		std::cin >> sizeOfTable;
		std::cin >> numberOfLines;

		HashTable hashRecord(sizeOfTable); //creation of hashTable with the size as a parameter.

		for (unsigned int i = 0; i < numberOfLines; i++)
		{
			std::cin >> command;

			//insert a record with key and value
			//if duplicate exist, print key already exists; otherwise, key inserted.
			if (command == 'I')
			{
				std::cin >> key;
				std::cin >> value;
				if (hashRecord.insert(key, value))
					std::cout << "Key " << key << " inserted";
				else
					std::cout << "Key " << key << " already exists";

			}
			//delete record with key
			//if duplicate exist, print Key doesn't exist; otherwise, key deleted.
			else if (command == 'D')
			{
				std::cin >> key;
				if (hashRecord.deleteRecord(key))
					std::cout << "Key " << key << " deleted";
				else
					std::cout << "Key " << key << " doesn't exist";
			}
			//Search for key
			//If key found, print key found, record = value; otherwise, key doesn't exist
			else if (command == 'S')
			{
				std::cin >> key;
				if (hashRecord.search(key) != -1)
					std::cout << "Key " << key << " found, record = " << hashRecord.search(key);
				else
					std::cout << "Key " << key << " doesn't exist";
			}
			//Print number of records in the table
			else if (command == 'P')
			{
				std::cout << "Number of records in table = " << hashRecord.size();
			}

			if (lineCount < numberOfLines) //to give correct number of new lines.
			{
				std::cout << std::endl;
				lineCount++;
			}
		}
//		hashRecord.debug(std::cout);
//	}
//	else
//		std::cout << "can't open the file. The program will be terminated." << std::endl;

//	inputFile.close();
//	outputFile.close();
}


//constructor
Node::Node(std::string ky, long long val, Node* nxt)
{
	next = nxt;
	key = ky;
	value = val;
}

//Update the next Node
void Node::setNext(Node *nxt)
{
	next = nxt;
}

//return next Node
Node* Node::getNext()
{
	return next;
}

//return the key stored in the node as a const
const std::string& Node::getKey() const
{
	return key;
}

//return the value stored in the node as a const
const long long Node::getValue() const
{
	return value;
}




//constructor
LinkedList::LinkedList()
{
	head = nullptr;
}

//destructor
LinkedList::~LinkedList()
{
	while (!empty())
		deleteFrontNode();
}

//insert at head, or do nothing as well as returning false if key is already present.
bool LinkedList::insert(std::string key, long long value)
{
	if (!(find(key))) //case : key is not found in the LinkedList
	{
		Node *newNode;
		newNode = new Node(key, value, nullptr);
		if (empty()) //if the list is empty, newNode is the only node to be added
			head = newNode;
		else //if the list is not empty, add a node to the front of the list
		{
			newNode->setNext(head);
			head = newNode;
		}
		return true;
	}
	else
		return false;
}


//if matched key is found, delete the node and return true.
//otherwise, do nothing and return false.
bool LinkedList::deleteNode(std::string key)
{
	Node *traverseNode; //a node to traverse through the list to search the match
	Node *trailNode; //a node before the traverseNode
	traverseNode = head;
	bool found = false;
	while (traverseNode != nullptr && !found)
	{
		if (traverseNode->getKey() == key) //found the matching key
		{
			if (head->getKey() == key) //case 1. first node is the matching node
				deleteFrontNode();
			else //case 2. any nodes other than first node are the matching node
			{
				trailNode->setNext(traverseNode->getNext());
				delete traverseNode;
			}
			found = true;
		}
		else // not found the matching key. traverse the list.
		{
			trailNode = traverseNode;
			traverseNode = traverseNode->getNext();
		}
	}
	return found;
}


//return result of the search. Return true if found, otherwise false.
bool LinkedList::find(std::string key)
{
	Node *traverseNode; //pointer to traverse the list
	traverseNode = head;
	bool found = false;
	while (traverseNode != nullptr && !found) //traverse the list until reach the end or found the matching key
	{
		if (traverseNode->getKey() == key) //found the matching key
			found = true;
		else //not found the matching key; move to the next node
			traverseNode = traverseNode->getNext();
	}
	return found;
}

//return the value for matching key. Return -1 if the key is not found
long long LinkedList::findValue(std::string key)
{
	Node *traverseNode;
	traverseNode = head;
	while (traverseNode != nullptr)
	{
		if (traverseNode->getKey() == key)
			return traverseNode->getValue();
		else
			traverseNode = traverseNode->getNext();
	}
	return -1; //no match found
}

//return true if the linkedlist is empty
bool LinkedList::empty() const
{
	if (head == nullptr)
		return true;
	else
		return false;
}

//delete the first node in the list.
void LinkedList::deleteFrontNode()
{
	if (!empty())
	{
		Node *tempNode; //temporary node to hold the node for deletion
		tempNode = head;
		head = head->getNext(); //head move to the next node
		delete tempNode;
	}
}

//return the size of the Linked List: number of nodes in the linked list.
int LinkedList::size()
{
	int size = 0;
	Node *traverseNode;
	traverseNode = head;
	while (traverseNode != nullptr)
	{
		size++;
		traverseNode = traverseNode->getNext();
	}
	return size;
}

//debug tool that prints the linked list with information of nodes
void LinkedList::debug(std::ostream &out)
{
	const unsigned int ADDRWIDTH = 10;
	int sizeTemp = size();
	out << "START DEBUG" << std::endl;
	out << "first  =" << std::setw(ADDRWIDTH) << head;
	out << ", # nodes=" << sizeTemp << std::endl;
	unsigned int count = 0;

	for (auto current=head; current!= nullptr; current=current->getNext())
	{
		out << "node " << std::setw(2) << count;
		out << "=" << std::setw(ADDRWIDTH) << current;
		out << ", next=" << std::setw(ADDRWIDTH)
			<< current->getNext();
		out << ", key=" << current->getKey();
		out << ", value=" << current->getValue() << std::endl;

		count++;
	}
	out << "END DEBUG" << std::endl;
	out << std::endl;
}


//constructor
HashTable::HashTable(int size)
{
	hashLinkedList = new LinkedList [size];
	hashTableSize = size;
}

//destructor
HashTable::~HashTable()
{
	clearTable();
	delete [] hashLinkedList;
}

//attempt to insert a record.
//Return false if the key is already present in the table.
//Otherwise insert and return true.
bool HashTable::insert(std::string key, long long val)
{
	int index = hash(key, hashTableSize);
	if (hashLinkedList[index].find(key)) //check if the key is already present in the table.
		return false;
	else
	{
		hashLinkedList[index].insert(key, val);
		return true;
	}
}

//attempt to find and delete a record.
//Return false if the key isn't present in the table.
bool HashTable::deleteRecord(std::string key)
{
	int index = hash(key, hashTableSize);
	if (hashLinkedList[index].deleteNode(key))
		return true;
	else
		return false;
}

//attempt to find a record.
//Return the value or -1 if the key is not found.
long long HashTable::search(std::string key)
{
	int index = hash(key, hashTableSize);
	if (hashLinkedList[index].find(key))
		return hashLinkedList[index].findValue(key);
	else
		return -1;
}

//empty the hash table.
void HashTable::clearTable()
{
	for (unsigned int i = 0; i < hashTableSize; i++)
		hashLinkedList[i].~LinkedList(); //call destructor for LinkedList in each index of hash Table
}

//return the number of records in the table
int HashTable::size()
{
	int size;
	for (unsigned int i = 0; i < hashTableSize; i++)
		size += hashLinkedList[i].size();
	return size;
}

/*the function to create a index in the hash table for the key based on its key character and length
 *string (key) is used to find its hash index location
 *tableSize is used to mod hash index value to fit inside the hash table
 *return the hash index
 */
int HashTable::hash(std::string key, unsigned int tableSize)
{
	long long modValue = pow(2,32);
	long long hashIndex = key.at(0);
	for (unsigned int i = 1; i < key.length(); i++)
	{
		hashIndex = hashIndex * 31 + key.at(i);
		hashIndex %= modValue;
	}
	hashIndex %= modValue;
	hashIndex %= tableSize;
	return hashIndex;
}

//debug tool that prints the linked list with information of nodes.
//it calls the Linked List of debug
void HashTable::debug(std::ostream &out)
{
	for (unsigned int i = 0; i < hashTableSize; i++)
	{
		hashLinkedList[i].debug(out);
	}
}



