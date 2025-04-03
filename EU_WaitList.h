#pragma once
#include "LinkedQueue.h"
template <typename T>
class EU_WaitList : public LinkedQueue <T>
{
protected:
	int TreatmentLatency;
public:
	EU_WaitList() {}
	~EU_WaitList() {}
	bool enqueue(const T& newEntry)
	{
		bool r = LinkedQueue <T>::enqueue(newEntry);
		if(r)
			TreatmentLatency = TreatmentLatency + T->GetCurrTreatment()->GetDuration(); 
		return r;
	}

	bool dequeue(T& frntEntry)
	{
		bool r = LinkedQueue <T>::dequeue(frntEntry);
		if(r)
			TreatmentLatency = TreatmentLatency - T->GetCurrTreatment()->GetDuration(); 
		return r;
	}

	bool InsertSorted(const T& newEntry, int SortingValue)
	{
		bool r;
		Node<T*> newnodePtr = new Node<T>(newEntry);
		Node<T*> curr;
		Node<T*> currnext;




		if (isEmpty())
		{
			frontPtr = newnodePtr;
			backPtr =  newnodePtr;
			r = true;
		}
		else if (SortingValue < frontPtr->getItem()->GetPT())
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
			
		}
		if (r)
			TreatmentLatency = TreatmentLatency + T->GetCurrTreatment()->GetDuration;
		return true;

	}

	int GetTreatmentLatency()
	{
		return TreatmentLatency;
	}
};

