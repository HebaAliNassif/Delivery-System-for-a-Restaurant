#include"Generic_DS\Node.h"
#include <cassert>
#ifndef _LINKED_LIST
#define _LINKED_LIST

template < typename T>
class LinkedList
{
private:
	Node<T>*headPtr;
   int itemCount;         
   
   Node<T>* getNodeAt(int position) const;
   Node<T>* insertNode(int newPosition, Node<T>* newNodePtr, Node<T>* subChainPtr);

public:
   LinkedList();
   LinkedList(const LinkedList<T>& aList);
   virtual ~LinkedList();
   void InsertBeg(T item);
   	void DeleteLast(T& item );
	bool getlastevent(T& item);
   bool isEmpty() const;

   bool insert(int newPosition, const T& newEntry);
   int getLength() const;
   bool remove(int position);
  void toArray(T*& Rhs) const;
   T getEntry(int position) const;
   void setEntry(int position, const T& newEntry);
   int getSize();
}; // end LinkedList
#endif 

////////////////////////////////////////////////////////

template < typename T>
T LinkedList<T>::getEntry(int position) const
{
	bool ableToGet = (position >= 1) && (position <= itemCount);
	if (ableToGet)
	{
		Node<T>* nodePtr = getNodeAt(position);
		return nodePtr->getItem();
	}
	//return NULL;

}

 ////////////////////////////////////////////////////////

template < typename T>
LinkedList<T>::LinkedList():headPtr(nullptr),itemCount(0)
{
}  // end default constructor

////////////////////////////////////////////////////////

template < typename T>
bool LinkedList<T>::remove(int position)
{
	bool ableToRemove = (position >= 1) && (position <= itemCount);
	if (ableToRemove)
	{
		Node<T>* curPtr = nullptr;
		if (position == 1)
		{
			// Remove the first node in the chain
			curPtr = headPtr; // Save pointer to node
			headPtr = headPtr->getNext();
		}
		else
		{
			// Find node that is before the one to delete
			Node<T>* prevPtr = getNodeAt(position - 1);

			// Point to node to delete
			curPtr = prevPtr->getNext();

			// Disconnect indicated node from chain by connecting the
			// prior node with the one after
			prevPtr->setNext(curPtr->getNext());
		}  // end if

		// Return node to system
		curPtr->setNext(nullptr);
		delete curPtr;
		curPtr = nullptr;

		itemCount--;  // Decrease count of entries
	}  // end if

	return ableToRemove;

}

  ////////////////////////////////////////////////////////

template < typename T>
LinkedList<T>::~LinkedList()
{
   //clear();
}  // end destructor

////////////////////////////////////////////////////////

template < typename T>
bool LinkedList<T>::isEmpty() const
{
   return itemCount == 0;
}  // end isEmpty

////////////////////////////////////////////////////////

template < typename T>
int LinkedList<T>::getLength() const
{
   return itemCount;
}  // end getLength

////////////////////////////////////////////////////////

template < typename T>
void LinkedList<T>::InsertBeg(T item)
{
	insert(1,item);
	/*Node<T> *newNodePtr = new Node<T>(item);
	headPtr = insertNode(1, newNodePtr, headPtr);*/
}

////////////////////////////////////////////////////////

template < typename T>
void LinkedList<T>::DeleteLast(T& item)
{
	if(headPtr==NULL)
	{
		return;
	}
	if(itemCount==1)
	{
		item= headPtr->getItem();
		headPtr=NULL;
	}
	else
	{
	  Node<T>* curPtr= getNodeAt(itemCount);
	  item=curPtr->getItem();
	  Node<T>* ptr = getNodeAt(itemCount-1);
	  ptr->setNext(NULL);
	}  
      itemCount--;  // Decrease count of entries
}

////////////////////////////////////////////////////////
template < typename T>
bool LinkedList<T>::getlastevent(T& item)
{
	Node<T>* curPtr= getNodeAt(itemCount);
	item=curPtr->getItem();
	return true;
}

////////////////////////////////////////////////////////

template < typename T>
Node<T>* LinkedList<T>::getNodeAt(int position) const
{
	   assert( (position >= 1) && (position <= itemCount) );
   // Count from the beginning of the chain
   Node<T>* curPtr = headPtr;
   for (int skip = 1; skip < position; skip++)
      curPtr = curPtr->getNext();
      
   return curPtr;
}  // end getNodeAt

////////////////////////////////////////////////////////

// RECURSIVE
template < typename T>
Node<T>* LinkedList<T>::insertNode(int position, Node<T>* newNodePtr,Node<T>* subChainPtr)
{
   if (position == 1)
   {
      // Insert new node at beginning of subchain
      newNodePtr->setNext(subChainPtr);
      subChainPtr = newNodePtr;
      itemCount++;  // Increase count of entries
   }
   else
   {
      Node<T>* afterPtr = insertNode(position - 1, newNodePtr, subChainPtr->getNext());
      subChainPtr->setNext(afterPtr);
   }  // end if
   
   return subChainPtr;

}  // end insertNode

template<typename T>
bool LinkedList<T>::insert(int newPosition, const T& newEntry)
{
   bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1);
   if (ableToInsert)
   {
      // Create a new node containing the new entry
      Node<T>* newNodePtr = new Node<T>(newEntry);
      headPtr = insertNode(newPosition, newNodePtr, headPtr);
   }  // end if
   
   return ableToInsert;
}  // end insert
template <typename T>
void LinkedList<T>::toArray(T*& Rhs) const
{
	Rhs=new T [itemCount];
	Node<T>* curPtr = headPtr;
	int counter = 0;
	while ((curPtr != nullptr) && (counter < itemCount))
	{
		Rhs[counter] = curPtr->getItem();
		curPtr = curPtr->getNext();
		counter++;
	} // end while
	//return QueueContents;
} // end toArray
template < typename T>
 int LinkedList<T>::getSize()
 {
	 return itemCount;
 }