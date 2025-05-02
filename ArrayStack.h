//	This is an updated version of code originally
//  created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT stack: Array-based implementation.
 @file ArrayStack.h */

#ifndef ARRAY_STACK_
#define ARRAY_STACK_

#include "StackADT.h"
#include <iostream>
using namespace std;
//#include "Patient.h"

//Unless spesificed by the stack user, the default size is 100
template<typename T>
class ArrayStack : public StackADT<T>
{
	enum { MAX_SIZE = 100 };
protected:

	T items[MAX_SIZE];		// Array of stack items
	int top;                   // Index to top of stack
	                           // count = top + 1  ya george
	
public:

	ArrayStack()
	{
		top = -1;
	}  // end default constructor

	bool isEmpty() const
	{
		return top == -1;	
	}  // end isEmpty

	bool push(const T& newEntry)
	{
		if( top == MAX_SIZE-1 ) return false;	//Stack is FULL

		top++;
		items[top] = newEntry;   
		return true;
	}  // end push

	bool pop(T& TopEntry)
	{
		if (isEmpty()) return false;
		
		TopEntry = items[top];


		//delete* (items[top]); // deleting patients
		//delete items[top]; // deleting patient pointers


		top--;
		return true;
	}  // end pop
	
	bool peek(T& TopEntry) const
	{
		if (isEmpty()) return false;
		
		TopEntry = items[top];		 
		return true;
	}  // end peek

	int getCount()
	{
		return top + 1;
	}

	void Print();

	~ArrayStack();
}; // end ArrayStack



template<typename T>
void ArrayStack<T>::Print()
{
	if (isEmpty()) return;

	for (int i = top; i >= 0; i--)  // LIFO order: from top to bottom
	{
		if (items[i])
		{
			items[i]->Print();
			if (i > 0) cout << ", ";
		}
	}

	cout << "\n";
}

//template<>
//ArrayStack<Patient*> :: ~ArrayStack()
//{
//	Patient* temp;
//	while (pop(temp));
//}  // destructor to delete patient pointers and patients

template<typename T>
ArrayStack<T>::~ArrayStack()
{
	T temp;
	while (pop(temp));
}



#endif
