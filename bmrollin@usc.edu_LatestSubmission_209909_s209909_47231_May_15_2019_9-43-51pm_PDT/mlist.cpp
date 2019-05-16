#include <iostream>
#include "mlist.h"
using namespace std;
//------------------------------------------------------------------------------
//IMPORTANT: You are not allowed to remove or add any parameters to any functions.
//NOTE: There can only be at most 2 loops in this file
//------------------------------------------------------------------------------

//Constructor, construct an empty doubly linked list.
MList::MList(){ //need to fix constructor? test 0 not passinng
    //implement a node struct????
    ntop = NULL;
    nbottom = NULL;

}

//Destructor, properly clears and deallocates everything of current list.
//simply call the clear function if you have already implemented that.
MList::~MList(){
    clear();
}

//Note: RECURSION --- This function should be implemented using recursion.
//this function properly clears and deallocates everything of current list.
//there should be no loop in this function
void MList::clear(){
    if(!isEmpty()) {
        //need more?
        pop_top();
        clear();
    }
}

/*
    //a pointer that points to the first node (top)
	Node* ntop;
	//a pointer that points to the last node (bottom)
	Node* nbottom;
*/

//returns a boolean true if the list is empty, false if otherwise.
bool MList::isEmpty(){
    return (ntop == NULL && nbottom == NULL);
}

/*
	Add or insert a new node with d_item as its data at the top of the list.
	You need to dynamically allocate memory for the new node.
*/
void MList::push_top(Data* d_item){
    if(isEmpty()) {
        Node* n = new Node;
        n->nodeData = d_item;
        ntop = n;
        nbottom = n;
        n->next = NULL;
        n->prev = NULL;
       } else {
        Node* n = new Node;
        n->nodeData = d_item;
        ntop->prev = n;
        n->next = ntop;
        n->prev = NULL;
        ntop = n;
        }

}

/*
	Add or insert a new node with d_item as its data at the bottom of the list.
	You need to dynamically allocate memory for the new node.
*/
void MList::push_bottom(Data* d_item){
    if(isEmpty()) {
        Node* n = new Node;
        n->nodeData = d_item;
        ntop = n;
        nbottom = n;
        n->next = NULL;
        n->prev = NULL;
    } else {
        Node* n = new Node;
        n->nodeData = d_item;
        nbottom->next = n;
        n->prev = nbottom;
        nbottom = n;
        n->next = NULL;
    }
    
    
}

/*
	Delete or remove the top node of the list.
	Once pop, you need to properly deallocate the memory for the node (not the data).
	If your list is currently empty, you don't have to do anything.
*/
void MList::pop_top(){
    if(!isEmpty()) {
          if (ntop == nbottom) { //one thing in list
              Node* t = ntop;
              ntop = NULL;
              nbottom = NULL;
              delete t;
          
          } else {
              Node* t = ntop;
              ntop = ntop->next;
              ntop->prev = NULL;
              delete t;
              
          }
      }
  
}

/*
	Delete or remove the bottom node of the list.
	Once pop, you need to properly deallocate the memory for the node (not the data).
	If your list is currently empty, you don't have to do anything.
*/
void MList::pop_bottom(){
    if(!isEmpty()) {
          if (ntop == nbottom) {
              Node* t = nbottom;
              ntop = NULL;
              nbottom = NULL;
              delete t;
              
          } else {
              Node* t = nbottom;
              nbottom = nbottom->prev;
              nbottom->next = NULL;
              delete t;
              
          }
      }   
    
}

/*
	Note: RECURSION --- This function should be implemented using recursion.
	Search a node in the list that has data with the same name as the parameter.
	If one is found, return the pointer to the node.
	If one is not found, return NULL.
*/
Node* MList::search(Node* start, string name){ //wrong output
    if (isEmpty()) { //if list is empty
        return NULL;
    } else if (start->nodeData->name == name) {//name of data in node has same name as parameter
        return start;
    } else if (start->next) {
        return search((start->next), name);
    } else { //not in list 
        return NULL;
    }
    
    
    /*
    if (start == NULL) { //if at end of list or if list is empty
        return NULL;
    } 
    else if (start->nodeData->name == name) {//name of data in node has same name as parameter
        return start;
    } else {
        search((start->next), name);
    }
    */
}


//Swapping node a with node b.
//what if next to each other?
/* Node struct has:
    Node* prev;
	Node* next;
	Data* nodeData;
    */
void MList::swapNode(Node* a, Node*b){ //core dump
    Node* saveB;
    Node* saveA;
    //same node
    if (a == b) { //do nothing?
    }
    //a right before b
    else if (a->next == b) {
        removeNode(a);
        insertAfter(a, b);  
    }
    //b right before a
    else if (b->next == a) {
        removeNode(b);
        insertAfter(b,a);
    }
    //a & b in middle not next to each other
    else {
        saveA = a->prev;
        saveB = b->prev;
        
        removeNode(a);
        removeNode(b);
        insertAfter(a, saveB);
        insertAfter(b, saveA);
    }
}

/*
	This function PERMANENTLY deletes a node from the list given a pointer to that node.
	You can assume that the node exists in the list - no need to search for the node.
*/
void MList::deleteNode(Node* a){ //works
   //if at start
   if(a->prev != NULL && a->next != NULL) { //somewhere in the middle
       a->prev->next = a->next; //node before a has next point to node after a
       a->next->prev = a->prev; //node after a has pointer to node before a
       
       delete a;
   } else if (a->prev != NULL && a->next == NULL) { //if a is last
       nbottom = nbottom->prev;
       
       a->prev->next = NULL;
       delete a;
   } else if (a->prev == NULL && a->next != NULL) {//if a is first
       ntop = ntop->next;
       
       a->next->prev = NULL;
       delete a;
   } else { //if only thing in list
       ntop = NULL;
       nbottom = NULL;
       delete a;
   }
}

/*
	Unlike the delete function above, this function does NOT permanently delete the node.
	What you need to do at the last step is to set the node's prev and next pointers to NULL.
	Again, you can assume that the node exists in the list - no need to search for the node.
	Note: this function will be useful
        when we want to insert the given node later at another position after you remove it from the list.
*/
void MList::removeNode(Node* a){ //works
    if(a->prev != NULL && a->next != NULL) { //somewhere in the middle
       a->prev->next = a->next; //node before a has next point to node after a
       a->next->prev = a->prev; //node after a has pointer to node before a
       
       a->next = NULL;
       a->prev = NULL;
   } else if (a->prev != NULL && a->next == NULL) { //if a is last
       nbottom = nbottom->prev;
       
       a->prev->next = NULL;
       //a->next = NULL;
       a->prev = NULL;
   } else if (a->prev == NULL && a->next != NULL) {//if a is first
       ntop = ntop->next;
       
       a->next->prev = NULL;
       a->next = NULL;
       //a->prev = NULL;
   } else { //if only thing in list
       ntop = NULL;
       nbottom = NULL;
       //a->next = NULL;
       //a->prev = NULL;
   }
}

/*
	Insert node a after node b.
	Note: b can be NULL, Q: what does that mean?
    otherwise, you can assume that b exists in the list.
*/
void MList::insertAfter(Node *a, Node* b){
    //if b is a the end
    if (isEmpty()) { //put into list, is this right
        ntop = a; 
        nbottom = a;
        a->next = NULL;
        a->prev = NULL;
    } else if (b == NULL) { //insert at front, is this right
        a->next = ntop;
        ntop->prev = a;
        a->prev = NULL;
        ntop = a;
    } else if (b->next == NULL) { //at end
        b->next = a;
        a->prev = b;
        a->next = NULL;
        nbottom = a;
    }   else { //b is in beginning or mid
        a->next = b->next;
        b->next->prev = a; //what is after b points to a
        b->next = a;
        a->prev = b;
    
    }
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Implement a SELECTION SORT algorithm using recursion.
	The function takes in a start node.
	Things to keep in mind:
		1). sort should NOT be run if the list is empty.
		2). if mode = true, sort by name in alphabetical order
			(i.e., A-Za-z) based on ASCII number if mode = true
        3). if mode = false, sort by size in ascending order (low->high)
	You can search any online resources available to you (i.e. search 'selection sort')
	to understand the basic idea behind the selection sort algorithm.
    Note: 
        1). there can only be at most one loop in this function
        2). this function is private
            see sortByNameSelection and sortBySizeSelection for the calls to this function
            
            compare start with everything else after
            if a is smalllest swap a with a
*/
void MList::sortSelection(Node* start, bool mode){
    if(!isEmpty() && ntop != nbottom) {
       Node* temp = start->next;
       Node* min = start;
       
       while (temp != NULL) {
           if (mode == false) { //sort alphahbetically
                if (min->nodeData->size > temp->nodeData->size) {
                    min = temp;
                }
                temp = temp->next; 
           }
           else /*if (mode == true)*/ { //sort by size
               //changing modes causes seg. fault
               if (min->nodeData->name > temp->nodeData->name) {
                    min = temp;
                }
                temp = temp->next;
                 
           }
       }
        
       swapNode(min, start);
        
       if (start != nbottom) {
           sortSelection(min->next, mode);
       }
  
    }
}


/*
 Note: RECURSION --- This function should be implemented using recursion.
	Implement an INSERTION SORT algorithm using recursion.
	The function takes in a start node.
	Things to keep in mind:
		1). sort should NOT be run if the list is empty.
		2). we are trying to sort by name in alphabetical order
			(i.e., A-Za-z) based on ASCII number.
	You can search any online resources available to you (i.e. search 'insertion sort')
	to understand the basic idea behind the insertion sort algorithm.
	The gif from the wikipedia page of this algorithm is the easiest to understand in my opinion
	Link: https://en.wikipedia.org/wiki/Insertion_sort
    Note: 
        1). there can only be at most one loop in this function
        2). this function is private, see sortByNameInsertion for the call to this function
*/
void MList::sortInsertion(Node* start){ //works
    if(!isEmpty() && nbottom != ntop) {
        Node* prior = start->prev; 
        Node* comp = start;
        Node* save = start->next;
        
        while (prior != NULL) { //while prev node exists
            if (comp->nodeData->name > prior->nodeData->name) { //compare start to prev node
               break; 
            } else { //look at prior's prior node
               prior = prior->prev;
            }
        }
        
         removeNode(start);
         insertAfter(start, prior); //put start where it belongs in first half of list
    
         if (save != NULL) {
             sortInsertion(save); //sort using next item in list after where start was
         }  
        
    }  
}


/*
	Note: RECURSION --- This function should be implemented using recursion.
	Traverse and print our list from node n to the top.
	we will seperate each node printed by the passed-in delimiter.
	If a node you encounter is a folder type, do

		cout<<....name.....<<delim;

	If a node you encounter is a file type, doz

		cout<<....name.....<<"("<<..size..<<")"<<delim;

	Note: please do NOT include <<endl; (aka newline)
	Example output (assume that the delimiter is a single space):
    
		folder1 file1(0) folder2 file2(0)

    There should be no loop in this function
	See printBtT function for the call to this function.
    This function is private
*/
void MList::traverseToTop(Node* n, string delim){
    if (!isEmpty()) {
    if (n->nodeData->isFolder == false) { //what to do?
        cout << n->nodeData->name << "(" << n->nodeData->size << ")" << delim;
    } else {
        cout << n->nodeData->name << delim;
    }

    if (n->prev != NULL) {
        traverseToTop(n->prev, delim);
    }
    }
    
    
    
    
    

}

/*
	Note: RECURSION --- This function should be implemented using recursion.
	Traverse and print our list from node n to the bottom.
	we will seperate each node printed by the passed-in delimiter.
	If a node you encounter is a folder type, do

		cout<<....name.....<<delim;

	If a node you encounter is a file type, do

		cout<<....name.....<<"("<<..size..<<")"<<delim;

	Note: please do NOT include <<endl; (aka newline)
	Example output (assume that the delimiter is a single space):
    
		folder1 file1(0) folder2 file2(0)

    There should be no loop in this function
	See printTtB function for the call to this function.
    This function is private
*/
void MList::traverseToBottom(Node* n,string delim){
    if (!isEmpty()) {
    if (n->nodeData->isFolder == false) { //what to do?
        cout << n->nodeData->name << "(" << n->nodeData->size << ")" << delim;
    } else {
        cout << n->nodeData->name << delim;
    }

    if (n->next != NULL) {
        traverseToBottom(n->next, delim);
    }
    }
    
    
}

//------------------------------------------------------------------------------
//FUNCTIONS BELOW ARE COMPLETE, PLEASE DON'T CHANGE ANYTHING HERE
//------------------------------------------------------------------------------

//getting the pointer to the top node.
Node* MList::top(){
	return ntop;
}

//getting the pointer to the bottom node.
Node* MList::bottom(){
	return nbottom;
}

//call traverseToBottom to print all item in the list from bottom node to top node
//the list of items is separated by a given delimiter
void MList::printBtT(string delim){
	//create a temp pointer to hold bottom
	Node* tmp = nbottom;
	traverseToTop(tmp,delim);
}

//call traverseToBottom to print all item in the list from top node to bottom node
//the list of items is separated by a given delimiter
void MList::printTtB(string delim){
	Node* tmp = ntop;
	traverseToBottom(tmp,delim);
}

//call sortSelection function, mode = true = sort by name
//public member
void MList::sortByNameSelection(){
    bool mode = true;
    Node *tmp = ntop;
    sortSelection(tmp,mode);
}

//call sortSelection function, mode = false = sort by size
//public member
void MList::sortBySizeSelection(){
    bool mode = false;
    Node *tmp = ntop;
    sortSelection(tmp,mode);
}

//call sortInsertion function
//public member
void MList::sortByNameInsertion(){
    Node *tmp = ntop;
    sortInsertion(tmp);
}