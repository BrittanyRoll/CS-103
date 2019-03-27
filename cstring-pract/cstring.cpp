#include <iostream>
 #include <cstring>
using namespace std;

int main()
{
char mystring[80] = "ComputerScience";
char yourstring[80];
char* astring;

//yourstring = mystring; //can't do this, think of array names as constant pointer to beginning of array
strncpy(astring, mystring, 80);

astring = mystring; 
strncpy(yourstring, mystring, 80); // make a copy?
cout << astring << endl;
cout << yourstring << endl;

mystring[0] = '*'; // which one actually made a copy?
cout << astring << endl;
cout << yourstring << endl;

    return 0;
 }

//for some reason when I run gdb I get:
//[Inferior 1 (process 17777) exited normally]
