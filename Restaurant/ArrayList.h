#ifndef _ARRAY_LIST
#define _ARRAY_LIST

template<class ItemType>
class ArrayList 
{
private:
	static const int DEFAULT_CAPACITY = 25;
	ItemType items[DEFAULT_CAPACITY];      
   int itemCount;                        
   int maxItems;                        
   
public:
   ArrayList();
   bool isEmpty() const;
   int getLength() const;
   bool insert(int newPosition, const ItemType& newEntry);
   bool remove(int position);
   void clear();
   ItemType getEntry(int position) const;
   void setEntry(int position, const ItemType& newEntry); 
                            
}; 

#endif 

////////////////////////////////////////////////////////

template<class ItemType>
ArrayList<ItemType>::ArrayList() : itemCount(0),maxItems(DEFAULT_CAPACITY)
{
}  // end default constructor

////////////////////////////////////////////////////////

template<class ItemType>
bool ArrayList<ItemType>::isEmpty() const
{
   return itemCount == 0;
}  // end isEmpty

////////////////////////////////////////////////////////

template<class ItemType>
int ArrayList<ItemType>::getLength() const
{
   return itemCount;
}  // end getLength

////////////////////////////////////////////////////////

template<class ItemType>
bool ArrayList<ItemType>::insert(int newPosition, const ItemType& newEntry)
{
   bool ableToInsert = (newPosition >= 1) && (newPosition <= itemCount + 1) &&             
                       (itemCount < maxItems);
   if (ableToInsert)
   {
	  //
      // Make room for new entry by shifting all entries at
      // positions >= newPosition toward the end of the array
      // (no shift if newPosition == itemCount + 1)
      for (int pos = itemCount; pos >= newPosition; pos--)
         items[pos] = items[pos - 1];
         
      // Insert new entry
      items[newPosition - 1] = newEntry;
      itemCount++;  // Increase count of entries
   }  // end if
   
   return ableToInsert;
}  // end insert

////////////////////////////////////////////////////////

template<class ItemType>
bool ArrayList<ItemType>::remove(int position)
{
  
      // Remove entry by shifting all entries after the one at
      // position toward the beginning of the array
      // (no shift if position == itemCount)
      for (int fromIndex = position, toIndex = fromIndex - 1; fromIndex < itemCount;
 fromIndex++, toIndex++)
         items[toIndex] = items[fromIndex];
         
      itemCount--;  // Decrease count of entries

   
   return true;
}  // end remove

////////////////////////////////////////////////////////

template<class ItemType>
void ArrayList<ItemType>::clear()
{
   itemCount = 0;
}  // end clear

////////////////////////////////////////////////////////

template<class ItemType>
ItemType ArrayList<ItemType>::getEntry(int position) const
{
   // Enforce precondition
   bool ableToGet = (position >= 1) && (position <= itemCount);
   if (ableToGet)
      return items[position - 1];
   else
   {
      string message = "getEntry() called with an empty list or "; 
      message  = message + "invalid position.";
      throw(PrecondViolatedExcep(message)); 
   }  // end if
}  // end getEntry

////////////////////////////////////////////////////////

template<class ItemType>
void ArrayList<ItemType>::setEntry(int position, const ItemType& newEntry)
{
   // Enforce precondition
   bool ableToSet = (position >= 1) && (position <= itemCount);
   if (ableToSet)
      items[position - 1] = newEntry;
   else
   {
      string message = "setEntry() called with an empty list or "; 
      message  = message + "invalid position.";
      throw(PrecondViolatedExcep(message)); 
   }  // end if
}  // end setEntry

//  End of implementation file.

