/* 
queue.cpp

Author: Brittany Rollins

Short description of this file: 
functions that update the queue
*/

#include "queue.h"

// constructor. maxlen must be as large as the total number
// of Locations that will ever be entered into this Queue.
// this is complete, you don't need to change it.
Queue::Queue(int maxlen) {
   contents = new Location[maxlen];
   head = 0;
   tail = 0;
}

// destructor. releases resources. C++ will call it automatically.
// this is complete, you don't need to change it.
Queue::~Queue() {
   delete[] contents;
}

/* queue class has a large dynamically allocated array
create an array of type dstored in queue,
head points to front
tail points to next empty spot (after last spot being used)
head and tail start

*/

// insert a new Location at the end/back of our list   
void Queue::push(Location loc) { //copy location into where tail points to,
   // FILL THIS IN
   contents[tail] = loc;
   tail++; //increase tracker for push calls
}

// return and "remove" the oldest Location not already extracted
Location Queue::pop() { //returns location item, copy item to what head points to, then move head pointer one location
   // FILL THIS IN
   Location locat = contents[head];
   //contents[head] = 0; //remove location
   head++;
   return locat;
}

// is this Queue empty? (did we extract everything added?)
// this is complete, you don't need to change it.
bool Queue::is_empty() {
    bool empt = false;
    if (head == tail) { //if no more
        empt = true;
    }
   return empt;
}

