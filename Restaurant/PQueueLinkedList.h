#include"QNode.h"
#include<iostream>
using namespace std;
#ifndef __PQueueLinkedList_H_
#define __PQueueLinkedList_H_
template<typename T, class P>
class PQueueLinkedList
{
private:
	QNode<T,P> *front;
	QNode<T,P> *back;
	int itemCount;
public:
	PQueueLinkedList()
	{
		front = NULL;
		back = NULL;
		itemCount=0;
	}
	//~PQueueLinkedList(){destroyList();}
	bool isEmpty() const;
	void enqueue(const T& newEntry,P priority);
    bool dequeue( T& Entry);
	void destroyList();
	bool peekFront(T& frntEntry) const;
	void toArray(T*& Rhs) const;
	int getSize() const;
};
#endif

////////////////////////////////////////////////////////

template<typename T, class P>
bool PQueueLinkedList<T,P>::isEmpty() const
{
	if(front==nullptr)
		return true;
	else
		return false;
}

////////////////////////////////////////////////////////

template<typename T, class P>
void PQueueLinkedList<T,P>::enqueue(const T& newEntry,P priority)
{
	itemCount++;
	QNode<T,P> *n=new QNode<T,P>(newEntry,priority);

	if(front == NULL)//queue has one node.
	{
		front = n;
		back = n;
		back->setNext(NULL);
		front->setNext(NULL);
	}
	else//queue has more than one node.
	{
		QNode<T,P>* temp = front;
		QNode<T,P>* prevtemp=front;
		if( n->getPriority() > temp->getPriority())//New node id's is greater than all others.
		{
			n->setNext(front);
			front = n;

		}
		else
		{
			//Search for the position for the new node.
			while( n->getPriority() <= temp->getPriority())
			{
				if(temp->getNext()== NULL)
					break;
				prevtemp=temp;
				temp = temp->getNext();
			}
			//New node id's smallest than all others
			if(temp->getNext()== NULL && n->getPriority() <= temp->getPriority())
			{
				back->setNext(n);
				back = n;
				back->setNext(NULL);
			}
			else//New node id's is in the medium range.
			{
				n->setNext(temp);
				prevtemp->setNext(n);
			}
		}
	}
}

////////////////////////////////////////////////////////

template<typename T, class P>
bool PQueueLinkedList<T,P>::dequeue( T& Entry)
{
	if(isEmpty())
		return false;

	QNode<T,P>* nodeToDeletePtr = front;
	Entry = front->getItem();
	front = front->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == back)	 // Special case: one node in queue
		back = nullptr ;	

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;
	itemCount--;

	return true;
	
}

////////////////////////////////////////////////////////

template<typename T, class P>
void PQueueLinkedList<T,P>::destroyList()
{
   while(front != NULL)
   {
       QNode<T,P>  *temp = front;
       front = front->getNext();
       delete temp;
   }
  
}

////////////////////////////////////////////////////////

template<typename T, class P>
bool PQueueLinkedList<T,P>:: peekFront(T& frntEntry) const 
{
	if(isEmpty())
		return false;

	frntEntry= front->getItem();
	return true;

}

////////////////////////////////////////////////////////

template<typename T, class P>
void PQueueLinkedList<T,P>::toArray(T*& Rhs) const
{
	Rhs=new T [itemCount];
	QNode<T,P>* curPtr = front;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		Rhs[counter] = curPtr->getItem();
		curPtr = curPtr->getNext();
		counter++;
	}
	
}

////////////////////////////////////////////////////////

template<typename T, class P>
int PQueueLinkedList<T,P>::getSize() const
{
	return itemCount;
}
