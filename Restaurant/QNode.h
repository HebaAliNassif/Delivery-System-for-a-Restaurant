#ifndef __QNODE_H_
#define __QNODE_H_
template<typename T, class P>
class QNode
{
private :
	T item; // A data item
	QNode<T,P>* next; // Pointer to next node
	P priority;
public :
	QNode();
	QNode( const T & r_Item,const P&);	//passing by const ref.
	QNode( const T & r_Item,const P& pr,  QNode<T,P>* nextNodePtr);
	void setItem( const T & r_Item);
	void setNext(QNode<T,P>* nextNodePtr);
	T getItem() const ;
	QNode<T,P>* getNext() const ;
	P getPriority();
	void setPriority(P item);
}; // end Node

////////////////////////////////////////////////////////

template<typename T, class P>
QNode<T,P>::QNode() 
{
	next = nullptr;
} 

////////////////////////////////////////////////////////

template<typename T, class P>
QNode<T,P>::QNode( const T& r_Item,const P& pr)
{
	item = r_Item;
	priority=pr;
	next = nullptr;
} 

////////////////////////////////////////////////////////

template<typename T, class P>
QNode<T,P>::QNode( const T& r_Item,const P& pr, QNode<T,P>* nextNodePtr)
{
	item = r_Item;
	priority=pr;
	next = nextNodePtr;
}

////////////////////////////////////////////////////////

template<typename T, class P>
void QNode<T,P>::setItem( const T& r_Item)
{
	item = r_Item;
} 

////////////////////////////////////////////////////////

template<typename T, class P>
void QNode<T,P>::setNext(QNode<T,P>* nextNodePtr)
{
	next = nextNodePtr;
} 

////////////////////////////////////////////////////////

template<typename T, class P>
T QNode<T,P>::getItem() const
{
	return item;
} 

////////////////////////////////////////////////////////

template<typename T, class P>
QNode<T,P>* QNode<T,P>::getNext() const
{
	return next;
}

////////////////////////////////////////////////////////

template<typename T, class P>
P QNode<T,P>::getPriority()
{
	return priority;
}

////////////////////////////////////////////////////////

template<typename T, class P>
void QNode<T,P>::setPriority(P item)
{
	priority=item;
}
#endif