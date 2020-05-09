#ifndef __QUEUE_H_
#define __QUEUE_H_
#include "Node.h"
template <typename T>
class Queue
{
private :
	
	Node<T>* backPtr;
	Node<T>* frontPtr;
	int itemCount;
public :
	Queue();	
	bool isEmpty() const ;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
	int getSize() const;
	 void  toArray(T*& Rhs) const;
	~Queue();
};

/////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
Queue<T>::Queue()
{
	itemCount=0;
	backPtr=nullptr;
	frontPtr=nullptr;

}
/////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool Queue<T>::isEmpty() const
{
	if(frontPtr==nullptr)
		return true;
	else
		return false;
}

/////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool Queue<T>::enqueue( const T& newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);
	// Insert the new node
	if (isEmpty())
		frontPtr = newNodePtr; // The queue is empty
	else
		backPtr->setNext(newNodePtr); // The queue was not empty
	backPtr = newNodePtr; // New node is at back
	itemCount++;
	return true ;
} // end enqueue


/////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool Queue<T>:: dequeue(T& frntEntry)  
{
	if(isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr ;	
		
	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;
	itemCount--;

	return true;

}

/////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
bool Queue<T>:: peekFront(T& frntEntry) const 
{
	if(isEmpty())
		return false;

	frntEntry=frontPtr->getItem();
	return true;

}

///////////////////////////////////////////////////////////////////////////////////

template <typename T>
void Queue<T>::toArray(T*& Rhs) const
{
	//T* QueueContents = new T [itemCount]; 
	Rhs=new T [itemCount];
	Node<T>* curPtr = frontPtr;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		//QueueContents[counter] = curPtr->getItem();
		Rhs[counter] = curPtr->getItem();
		curPtr = curPtr->getNext();
		counter++;
	} // end while
	//return QueueContents;
} // end toArray
template <typename T>
int Queue<T>::getSize() const
{
	return itemCount;
}

///////////////////////////////////////////////////////////////////////////////////

template <typename T>
Queue<T>::~Queue()
{
}
#endif