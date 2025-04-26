#pragma once
#include "LinkedQueue.h"
class EU_WaitList : public LinkedQueue <Patient*>
{
protected:
	int TreatmentLatency;
public:
	EU_WaitList() 
	{
		TreatmentLatency = 0;
	}
	~EU_WaitList() {}
	bool enqueue(Patient*& newEntry)
	{
		bool r = LinkedQueue <Patient*>::enqueue(newEntry);
		if (r)
		{
			Treatment* curr;
			newEntry->Get_reqtreatmentlist().peek(curr);
			TreatmentLatency = TreatmentLatency + curr->GetDuration();
		}
		return r;
	}

	bool dequeue(Patient*& frntEntry)
	{
		bool r = LinkedQueue <Patient*>::dequeue(frntEntry);
		if (r)
		{
			Treatment* curr;
			frntEntry->Get_reqtreatmentlist().peek(curr);
			TreatmentLatency = TreatmentLatency - curr->GetDuration();
		}
		return r;
	}

	bool InsertSorted(Patient*& newEntry, int SortingValue)
	{
		bool r = false;

		Node<Patient*>* newnodePtr = new Node<Patient*>(newEntry);
		Node<Patient*>* curr;
		Node<Patient*>* currnext;



		if (isEmpty())
		{
			frontPtr = newnodePtr;
			backPtr =  newnodePtr;
			r = true;
		}
		else if (SortingValue < frontPtr->getItem()->getPT())
		{
			newnodePtr->setNext(frontPtr);
			frontPtr = newnodePtr;
			r = true;
		}
		else
		{
			curr = frontPtr;
			currnext = frontPtr->getNext(); // we can use one pointer instead of two
			while (currnext && SortingValue >= currnext->getItem()->getPT())
			{
				curr = currnext;
				currnext = currnext->getNext();
			}
			newnodePtr->setNext(currnext);
			curr->setNext(newnodePtr);
			if (currnext == nullptr)
				backPtr = newnodePtr;
			r = true;
			
		}
		if (r)
		{
			Treatment* curr;
			newEntry->Get_reqtreatmentlist().peek(curr);
			TreatmentLatency = TreatmentLatency + curr->GetDuration();
			count++;
		}
		return r;

	}

	int GetTreatmentLatency()
	{
		return TreatmentLatency;
	}
};

