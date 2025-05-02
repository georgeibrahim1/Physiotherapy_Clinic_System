
#include "EU_WaitList.h"

EU_WaitList::EU_WaitList()
{
	TreatmentLatency = 0;
}
EU_WaitList::~EU_WaitList() {}
bool EU_WaitList::enqueue(Patient*& newEntry)
{
	bool r = LinkedQueue <Patient*>::enqueue(newEntry);
	if (r)
	{
		Treatment* curr;
		newEntry->Peek_ReqTreatment(curr);
		TreatmentLatency = TreatmentLatency + curr->GetDuration();
	}
	return r;
}

bool EU_WaitList::dequeue(Patient*& frntEntry)
{
	bool r = LinkedQueue <Patient*>::dequeue(frntEntry);
	if (r)
	{
		Treatment* curr;
		frntEntry->Peek_ReqTreatment(curr);
		TreatmentLatency = TreatmentLatency - curr->GetDuration();
	}
	return r;
}

bool EU_WaitList::peek(Patient*& frntEntry) const
{
	bool r = LinkedQueue<Patient*>::peek(frntEntry);
	return r;
}

bool EU_WaitList::InsertSorted(Patient*& newEntry, int SortingValue)
{
	bool r = false;

	Node<Patient*>* newnodePtr = new Node<Patient*>(newEntry);
	Node<Patient*>* curr;
	Node<Patient*>* currnext;



	if (isEmpty())
	{
		frontPtr = newnodePtr;
		backPtr = newnodePtr;
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
		newEntry->Peek_ReqTreatment(curr);
		TreatmentLatency = TreatmentLatency + curr->GetDuration();
		count++;
	}
	return r;

}

int EU_WaitList::GetTreatmentLatency()
{
	return TreatmentLatency;
}

