/*****************************************
** File:    LL.cpp
** Project: CMSC 202 Project 5, Spring 2023
** Author:  Jervon Drakes
** Date:    5/02/23
** Section: 44
** E-mail:  jdrakes1@umbc.edu
**
** This file contains the LL.cpp file for Project 5.
** This program executes the functions of LL.cpp to
** implement proj5.cpp.
**
**
**
***********************************************/

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//DO NOT ADD ANY CONSTANTS OR FUNCTIONS TO ANY CLASS

// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node {
public:
  Node( const T& data ); //Node Constructor - Assume each quan
  pair<T,int>& GetData(); //Node Data Getter
  void SetData( const pair<T,int>& ); //Node Data Setter
  Node<T>* GetNext(); //Node m_next getter
  void SetNext( Node<T>* next ); //Node m_next setter
private:
  pair <T,int> m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
  m_data = make_pair(data,1);
  m_next = nullptr;
}

template <class T>
pair<T,int>& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const pair<T,int>& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

//Templated Linked List class
template <class T>
class LL {
 public:
  // Name: LL() (Linked List) - Default Constructor
  // Desc: Used to build a new linked list
  // Preconditions: None
  // Postconditions: Creates a new linked list where m_head points to nullptr
  LL();
  // Name: ~LL() - Destructor
  // Desc: Used to destruct a LL
  // Preconditions: There is an existing LL with at least one node
  // Postconditions: A LL is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~LL();
  // Name: LL (Copy Constructor)
  // Desc: Creates a copy of existing LL
  //       Requires a LL - REQUIRED to be implemented even if not used
  // Preconditions: Source LL exists
  // Postconditions: Copy of source LL
  LL(const LL&);
  // Name: operator= (Overloaded Assignment Operator)
  // Desc: Makes two LL of the same type have identical number of nodes and values
  // Preconditions: Requires two linked lists of the same templated type
  //                REQUIRED to be implemented even if not used
  // Postconditions: Two idenetical LL
  LL<T>& operator= (const LL&);
  // Name: Find
  // Desc: Iterates through LL and returns node if data found
  // Preconditions: LL Populated
  // Postconditions: Returns nullptr if not found OR Node pointer if found
  Node<T>* Find(const T& data);
  // Name: Insert
  // Desc: Either inserts a node to the linked list OR increments frequency of first
  //       Takes in data. If "first" (of pair) NOT in list, adds node
  //       If "first" (of pair) is already in list, increments quantity
  //       Inserts "first" in order with no duplicates
  // Preconditions: Requires a LL.
  // Postconditions: Node inserted in LL based on first value (or quantity incremented)
  void Insert(const T&);
  // Name: RemoveAt
  // Desc: Removes a node at a particular position based on data passed (matches first)
  // Preconditions: LL with at least one node. 
  // Postconditions: Removes first node with passed value (in first)
  void RemoveAt(const T&);
  // Name: Display
  // Desc: Display all nodes in linked list
  // Preconditions: Outputs the LL
  // Postconditions: Displays the pair in each node of LL 
  void Display();
  // Name: GetSize
  // Desc: Returns the size of the LL
  // Preconditions: Requires a LL
  // Postconditions: Returns m_size
  int GetSize();
  // Name: operator<< (Overloaded << operator)
  // Desc: Returns the ostream of the data in each node
  // Preconditions: Requires a LL
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const LL<U>&);
  // Name: Overloaded [] operator
  // Desc: When passed an integer, returns the data at that location
  // Precondition: Existing LL
  // Postcondition: Returns pair from LL using []
  pair<T,int>& operator[] (int x);//Overloaded [] operator to pull data from LL
private:
  Node <T> *m_head; //Node pointer for the head
  int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement LL here


// LL() (Linked List) - Default Constructor
// Used to build a new linked list
template <class T>
LL<T>::LL() {
  
  m_head = nullptr; // m_head points to nullptr 
  m_size = 0; 

}


//~LL() - Destructor
//Used to destruct a LL
template <class T>
LL<T>::~LL() {

  Node<T>* curr = m_head; // a new templated node is created and points to m_head

  // conditionnal to determine that the curr node is not nullptr
  while(curr != nullptr){
    
    Node<T>* temp = curr; // a new templated node called temp is created and points to the curr node
    
    curr = curr->GetNext(); // other nodes are accessed within the linked list

    // the temp node is deleted to prevent any possible meory leaks
    delete temp;
    
  }
  m_head = nullptr;
  m_size = 0;

}



// LL (Copy Constructor)
// Creates a copy of existing LL. Requires a LL - REQUIRED to be implemented even if not used
template <class T>
LL<T>::LL(const LL& other){

  m_size = 0;
  m_head = nullptr;
  Node<T>* curr = other.m_head; // creates a new templated node called curr which points to the m_head of the other linked list

  
  // determines if curr is nullptr
  while(curr != nullptr){

    // loops through curr  
    for(int i = 0; i < curr->GetData().second; i++){
      
      // inserts the templated data  
	Insert(curr->GetData().first);      
    }
    curr = curr->GetNext(); // access the other nodes 
  }
}


// operator= (Overloaded Assignment Operator)
// Makes two LL of the same type have identical number of nodes and values
template <class T>
LL<T>& LL<T>::operator=(const LL& other){

  // conditional which determines if the this pointer is not the other linked list
  if(this != &other){
    
    Node<T>* temp = m_head; // creates a new templated node called temp which points to m_head

    // conditional executed once m_head is not nullptr
    while(m_head != nullptr){

      
      m_head = m_head->GetNext(); // access other nodes within the linked list

      delete temp; // deallocates the memory for temp to prevent memory leaks
      
      temp = m_head; // points temp to m_head
    }
    m_head = nullptr;
    
    m_size = 0;

    
    Node<T>* curr = other.m_head; // creates another templated node which points to the m_head of the other linked list

    // conditional executed once 
    while(curr != nullptr){

      // loops through the templated curr node
    for(int i = 0; i < curr->GetData().second; i++){

      // inserts templated data into the linked list
      Insert(curr->GetData().first); 
    }

    curr = curr->GetNext();

    }
    
  }
  return *this;
}  


// Find
// Iterates through LL and returns node if data found
template <class T>
Node<T>* LL<T>::Find(const T& data){

  Node<T>* curr = m_head; // creates a templated node called curr and points it to m_head

  // conditional executed once curr is not nullptr
  while(curr !=  nullptr){

    // dtermined is the first value of the templated data is data
    if(curr->GetData().first == data){

      return curr;
    }
    
    curr = curr->GetNext(); // access the other nodes
  }
  
  return nullptr;
}


//Insert
// Either inserts a node to the linked list OR increments frequency of first. Takes in data. If "first" (of pair) NOT in list, adds node. If "first" (of pair is already in list, increments quantity. Inserts "first" in order with no      duplicates
template <class T>
void LL<T>::Insert(const T& myData){

  Node<T>* temp = Find(myData); // creates a templated node called temp which calls the find function
   
  // conditional to determine if the templated data is foudn within the linked list
  if(temp){
    
    // the frequency of the data is increased if condition is met
    temp->SetData(make_pair(temp->GetData().first, temp->GetData().second + 1));
    return;
  }

  
  Node<T>* newNode = new Node<T>(myData); // a templated node called newNode is created

  // determines if m_head is nullptr
  if(m_head == nullptr){
    
    m_head = newNode; // m_head points to newNode if condition is met
	 
  }else{

    Node<T>* curr = m_head; // templated node called curr points to m_head 
    Node<T>* prev = nullptr; // templated node called prev points to nullptr


    // determines whether the data within curr is less than myData and whether the next node points to nullptr
    while(curr->GetData().first < myData  && curr->GetNext() != nullptr){
      
      prev = curr; 
      
      curr = curr->GetNext();
    }

    // determines if the node is accessed next points to nullptr
    if(curr->GetNext() == nullptr){

       // sets the current node as the newNode
      curr->SetNext(newNode); 

    }else{

      // sets newNode to the current node
      newNode->SetNext(curr);

      // determines if prev points to nullptr
      if(prev == nullptr){

	// sets the new node as m_head
	newNode->SetNext(m_head);
	
	m_head = newNode; // points m_head to the newNode
      
   
      }else{
          
	newNode->SetNext(curr);
	
	prev->SetNext(newNode);

      }
      
    }
    
  }
  
  m_size++;
  
  
}

// RemoveAt
// Removes a node at a particular position based on data passed (matches first)
template<class T>
void LL<T>::RemoveAt(const T& otherData){
  
  Node<T>* curr = m_head; // templated node called curr created which points to m_head
  Node<T>* prev = nullptr; // templated node called prev created which points to nullptr

  // determines if m_head points to nullptr
  if(m_head == nullptr){
    
    return;
  }

  // determines if the data found within the linked list points to nullptr
  if(Find(otherData) == nullptr){

    return;
  }

  // determines if the first value of the pair is otherDat
  if(curr->GetData().first == otherData){

    // determines if prev is nullptr
    if(prev == nullptr){
      
      m_head = curr->GetNext(); // assigns m_head as the next node within curr
      
      delete curr; 
      
      m_size--;
      
    }
    
  }else{

    // determines if the size of the linked list is greater than 1
    if(m_size > 1){
      
      curr = m_head; // points curr to the m_head
      
      prev = curr; // points the prev node to curr

      // condtional to determine whether curr does not point to nullptr
      while(curr != nullptr){
	
	prev = curr; // points the curr node to curr
	
	curr = curr->GetNext(); // curr is assigned the next node 

	// determines if the first value in the pair is otherData
	if(curr->GetData().first == otherData){

	  // sets prev to next node in curr
	  prev->SetNext(curr->GetNext()); 

	  // deallocates the curr node which prevents memory leak
	  delete curr;
	  
	  m_size--;
	  
	  return;
	}
      }
    }
  }  
}
  
// Display
// Display all nodes in linked list
template<class T>
void LL<T>::Display(){

  Node<T>* curr = m_head; // creates a templated node called curr

  // conditional determines whether curr is not nullptr
  while(curr != nullptr){

    // displays the contents of each node
    cout << curr->GetData().first << ":" << curr->GetData().second << endl;
    
    curr = curr->GetNext(); // accesses the next node
  }

  cout << "END" <<  endl;
}



//GetSize
//Returns the size of the LL
template<class T>
int LL<T>::GetSize(){
  return m_size;
}


//operator<< (Overloaded << operator)
//Returns the ostream of the data in each node
template <class U>
ostream& operator<<(ostream& output, const LL<U>&source){

   
  Node<U>* curr = source.m_head; // creates a templated node called curr which points to the m_head of source 

  // determines whether curr is not nullptr
  while(curr != nullptr){

    // the contents of the nodes are placed into output 
    output << curr->GetData().first << ":" << curr->GetData().second << endl;
    
    curr = curr->GetNext(); // accesses the next noe
  }
  
  return output;
}

  
// Overloaded [] operator
// When passed an integer, returns the data at that location
template <class T>
pair<T,int>&LL<T>::operator[](int x){

  
  Node<T>* curr = m_head; // creates a templated node which points to m_head

  // loops through curr
  for(int i = 0; i < x; i++){
    
    curr = curr->GetNext(); // accesses each node once after the other

  }
  // returns the templated data of each node
  return curr->GetData(); 
}
