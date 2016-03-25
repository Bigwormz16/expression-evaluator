/**
	@author Peter Sands
	Email: w1541805@apps.losrios.edu

	@file List.h
	@brief A two-way list container class.
		A two-way list container class, supporting initialization to a default state, 
	adding and inserting elements into the list, removing elements from the list, 
	searching for elements within the list, sorting the list, and getting an iterator to easily traverse the list

	@see LinkedListNode.h
	@see ListIterator.h

*/

#ifndef PSANDS_CISP430_LIST_H
#define PSANDS_CISP430_LIST_H

#include <new>
#include "LinkedListNode.h"
#include "ListIterator.h"

/**
	@brief namespace for assignment 2
*/
namespace psands_cisp430_a2
{
	/// @tparam TDataType is the type of data this node stores.
	template <class TDataType>
	class List
	{
	private:
		LinkedListNode<TDataType> * _head; ///< head node to traverse the list front-to-back
		LinkedListNode<TDataType> * _tail; ///< tail node to traverse the list back-to-front
		int _count; ///< tracks the count of the list
		bool _isSorted; ///< indicates that the list is ina  sorted state
		bool _isFull; ///< indicates that the list is full and no more add/insert can take place

		/**
			retrieves the node at a specified position within the list
			@param position of the node to retrieve
			@returns the node at the specified position or null if the position is out of bounds of the list
		*/
		LinkedListNode<TDataType> * getNodeAt(unsigned int position);

		/**
			determines whether or not the specified position is within a given bound
			@param position the position to test
			@param startBound the starting boundary that position may be equal to or greater than
			@param endBound the end boundary that position may be equal to or less than
			@returns true if the position is within the bounds of the list
		*/
		bool isInbounds(unsigned int position, int startBound, int endBound);

	public:
		/**
			default constructor initializes the list to the default state: head and tail are null and count is 0
		*/
		List();

		/**
			parameterized constructor initializes the list to a sorted or unsorted state
			@param isSorted flag to indicate whether or not the list is to be sorted
		*/
		List(bool isSorted);
		/**
			copy constructor copies the values from another list into this list
			@param list the list to copy into this list
		*/
		List(const List<TDataType> & list);
		/**
			destructor goes through the list and deletes each node in turn
		*/
		~List();

		/**
			overloading less than comparison operator allows a list to contain a list.
			unsure what a lesser list would be, going to use count to compare the two lists.
			@param list the list to compare this list against with the less than operator
		*/
		bool operator <(List<TDataType> &list) const;

		/**
			overloading equals operator is necessary to support the structure of a list of lists.  
			@param list the list to set this list equal to
		*/
		void operator =(const List & list);

		/**
			returns true when the list is empty and false otherwise
			@returns true when the list is empty and false otherwise
		*/
		bool isEmpty() const;

		/**
			returns true when the list is full and false otherwise
			@returns true when the list is full and false otherwise
		*/
		bool isFull() const;
		
		/**
			returns true when the list is sorted and false otherwise
			@returns true when the list is sorted and false otherwise
		*/
		bool isSorted() const;

		/**
			returns the number of elements contained within the list
			@returns the number of elements contained within the list
		*/
		unsigned int getCount() const;

		/**
			retrieves the data element at a specified position within the list
			@param position of the data element to retrieve
			@returns the data element at the specified position or a default value
		*/
		TDataType getElementAt(unsigned int position);

		/**
			@brief initializes the list to the default state: head and tail are null and count is 0
			This implementation is also responsible for cleaning up after the original list elements
		*/
		void init();

		/**
			adds an element to the end of the list
			@param data the element to add to the list
			@returns true when the add action was successful
		*/
		bool add(TDataType data);
		/**
			@brief inserts an element to a specified position within the list
			an unsuccessful insert can be caused when the position is out of bounds of the list
			@param data the element to insert into the list
			@param position the location within the list to insert the element to
			@returns true when the insert action was successful
		*/
		bool insert(TDataType data, int position = -1);

		/**
			@brief appends the contents of the parameter list to this list
			the net result should be that this list contains its original contents and the contents of the parameter list
			@param list the list to add to this list
			@returns true when all additions to this list have been successful
		*/
		bool addRange(const List<TDataType> & list);

		/**
			@brief removes an element from the end of the list
			an unsuccessful removal can occur when the list is already empty
			@returns true when the removal action was successful
		*/
		bool remove();
		/**
			@brief removes the first element matching the parameter after the specified location in the list
			an unsuccessful removal can occur when the element is not found or the position is out of bounds of the list
			@param data the element to find and remove from the list
			@param position the position to start the removal search from
			@returns true when the removal action was successful
		*/
		bool remove(TDataType data, unsigned int position = 0);

		/**
			removes all elements from the list
			@returns true if a removal action has taken place, false if there was nothing to remove
		*/
		bool removeAll();

		/**
			searches the list for the specified element and indicates whether or not that element is contained in the list
			@param data the element to search the list for
			@returns true when the element exists within the list
		*/
		bool contains(TDataType data);
		/**
			searches the list for the specified element after a specified position and indicates the location of that element within the list
			@param data the element to search the list for
			@param position the position to start the search from
			@return the location of the element within the list or -1 if the position is out of bounds of the list or the element was not found
		*/
		int indexOf(TDataType data, unsigned int position = 0);

		/**
			sorts the list in ascending order
		*/
		void sort();
		/**
			sorts the list in descending order
		*/
		void sortDescending();

		/**
			returns an iterator that allows for easy traversal of the list
			@param isForward true when the iterator is to traverse the list front to back, false if it is back to front
			@returns an iterator that allows for easy traversal of the list
		*/
		ListIterator<TDataType> * getIterator(bool isForward = true) const;

		/**
			serializes the list to a file
			@param fileName the name of the file to save the file to
		*/
		void serialize(char * fileName);

		/**
			deserializes the list from a file
			@param fileName the name of the file to read the list from
		*/
		void deserialize(char * fileName);

	}; // end of class List
	
	/**
		\code{.unparsed}
			test to see if the position is within the bounds of the list
				return null if that position is not in bounds
						
			if position is in the first half of the list, then
				from the head, iterate until the position is reached
				return the node at that position
			otherwise,
				from the tail, iterate backwards until the position is reached
				return the node at that position

		\endcode
	*/
	template<class TDataType>
	inline LinkedListNode<TDataType>* List<TDataType>::getNodeAt(unsigned int position)
	{
		if (false == this->isInbounds(position, 0, this->_count - 1))
		{
			return nullptr;
		}

		LinkedListNode<TDataType> * node = nullptr;

		if (position <= (this->_count / 2))
		{
			node = this->_head;
			for (unsigned int i = 0; i < position; i++)
			{
				node = node->getNext();
			}
		}
		else
		{
			node = this->_tail;
			for(unsigned int i = this->_count - 1; position < i; i--)
			{
				node = node->getPrevious();
			}
		}

		

		return node;
	}
	
	/**
		\code{.unparsed}
			test to see if position is less than or equal to startBound
			test to see if position is greater than or equal to endBound
			return true if the position is within the bounds and false otherwise
		\endcode
	*/
	template<class TDataType>
	inline bool List<TDataType>::isInbounds(unsigned int position, int startBound, int endBound)
	{
		return startBound <= position && position <= endBound;
	}

	/**
		\code{.unparsed}
			initialize the list to the default state
		\endcode
	*/
	template<class TDataType>
	inline List<TDataType>::List()
	{
		this->_head = nullptr;
		this->_tail = nullptr;
		this->_count = 0;
		this->_isFull = false;
		this->_isSorted = false;

		this->init();
	}

	/**
		\code{.unparsed}
			initialize the list to the default state
			set the list to be ordered or unordered based on the input parameter
		\endcode
	*/
	template<class TDataType>
	inline List<TDataType>::List(bool isSorted) : List()
	{
		this->_isSorted = isSorted;
	}

	/**
		\code{.unparsed}
			copy the contents of one list into this list
		\endcode
	*/
	template<class TDataType>
	inline List<TDataType>::List(const List<TDataType>& list) : List()
	{	
		this->addRange(list);
	}

	/**
		\code{.unparsed}
			remove all nodes from the list and clean up the memory allocation
		\endcode
	*/
	template<class TDataType>
	inline List<TDataType>::~List()
	{
		this->removeAll();
	}

	/**
		\code{.unparsed}
			return true if this list count is less than parameter list count
		\endcode
	*/
	template<class TDataType>
	inline bool List<TDataType>::operator<(List<TDataType>& list) const
	{
		return this->getCount() < list.getCount();
	}

	/**
		\code{.unparsed}
			remove all items from this list
			add all items from list to this list
		\endcode
	*/
	template<class TDataType>
	inline void List<TDataType>::operator=(const List & list)
	{
		this->removeAll();
		this->addRange(list);
	}

	/**
		\code{.unparsed}
			determine if the list is empty
			return true if the list is empty
		\endcode
	*/
	template<class TDataType>
	inline bool List<TDataType>::isEmpty() const
	{
		return 0 == this->_count;
	}

	/**
		\code{.unparsed}
			determine if the list is full
			return true if the list is full
		\endcode
	*/
	template<class TDataType>
	inline bool List<TDataType>::isFull() const
	{
		return this->_isFull;
	}
	
	/**
		\code{.unparsed}
			determine if the list is sorted
			return true if the list is sorted
		\endcode
	*/
	template<class TDataType>
	inline bool List<TDataType>::isSorted() const
	{
		return this->_isSorted;
	}

	/**
		\code{.unparsed}
			determine the count of the list
			return the count of the list
		\endcode
	*/
	template<class TDataType>
	inline unsigned int List<TDataType>::getCount() const
	{
		return this->_count;
	}

	/**
		\code{.unparsed}
			using getNodeAt,
				locate the node at the given position
				return the data element contained within that node
		\endcode
	*/
	template<class TDataType>
	inline TDataType List<TDataType>::getElementAt(unsigned int position)
	{
		return this->getNodeAt(position)->getData();
	}

	/**
		\code{.unparsed}
			remove all nodes from the list and clean up the memory allocation
			initialize the list to the default state
		\endcode
	*/
	template<class TDataType>
	inline void List<TDataType>::init()
	{
		this->removeAll();

		this->_head = nullptr;
		this->_tail = nullptr;
		this->_count = 0;
	}

	/**
		\code{.unparsed}
			if the list is sorted, then
				use a non sorted insert
			otherwise,
				insert into the list at the end of the list
			return result of insert
		\endcode
	*/
	template<class TDataType>
	inline bool List<TDataType>::add(TDataType data)
	{
		if (this->_isSorted)
		{
			return this->insert(data, -1);
		}
		else
		{
			return this->insert(data, this->_count);
		}
	}
	
	/**
		\code{.unparsed}
			if the list is full, then
				fail the insert

			if position is non-negative and the list is sorted, then
				fail the insert

			if position is negative and the list is not sorted, then
				fail the insert
				
			if the position to insert is out of bounds, then
				fail the insert
			
			create a new list node
			
			if the creation of a new list node failed, then
				flag the list as full
				fail the insert

			if head and tail is null, then
				set head to node "new"
				set tail to node "new"
				increase list count
				return success
				
			if 

			retrieve node "enode" existing node to replace
				if list is sorted, then
					"enode" is the first node that has a value greater than or equal to "new" node
				otherwise,
					"enode" is the node located at "position"

			if node "enode" is null, then
				set node "tail" next to node "new"
				set node "new" previous to node "tail"
				set tail to node "new"
			otherwise, if node "enode" previous is null, then
				set node "position" previous to node "new"
				set node "new" next to node "position"
				set head to node "new"
			otherwise,
				set node "new" previous to node "enode-1"
				set node "new" next to node "enode"
				set node "enode-1" next to node "new"
				set node "enode" previous to node "new"

			increase list count
			return success

		\endcode
	*/
	template<class TDataType>
	inline bool List<TDataType>::insert(TDataType data, int position)
	{		
		if(true == this->_isFull)
		{
			return false;
		}

		if (true == this->_isSorted && 0 <= position) // can not positionally insert on a sorted list
		{
			return false;
		}

		if (false == this->_isSorted && false == this->isInbounds(position, 0, this->_count)) // can not insert without a position on a non-sorted list
		{
			return false;
		}

		LinkedListNode<TDataType> * newNode = new(std::nothrow) LinkedListNode<TDataType>(data);
		
		if(!newNode)
		{
			this->_isFull = true;
			return false;
		}

		if (nullptr == this->_head && nullptr == this->_tail)
		{
			this->_head = this->_tail = newNode;
			this->_count++;
			return true;
		}

		LinkedListNode<TDataType> * existingNode = nullptr;

		if (false == this->_isSorted) // positionally insert a non-sorted list
		{
			existingNode = this->getNodeAt(position); 
		}
		else // locate the sorted location for a sorted list
		{
			existingNode = this->_head;
			while (nullptr != existingNode && existingNode->getData() < newNode->getData())
			{
				existingNode = existingNode->getNext();
			}
		}

		if (nullptr == existingNode) // this is true if trying to insert a new tail
		{
			newNode->setPrevious(this->_tail);
			this->_tail->setNext(newNode);
			this->_tail = newNode;
		}
		else if (nullptr == existingNode->getPrevious()) // this is true if trying to insert a new head
		{
			existingNode->setPrevious(newNode);
			newNode->setNext(existingNode);
			this->_head = newNode;
		}
		else // otherwise, inserting a middle node
		{
			newNode->setPrevious(existingNode->getPrevious());
			newNode->setNext(existingNode);
			existingNode->getPrevious()->setNext(newNode);
			existingNode->setPrevious(newNode);
		}

		this->_count++;

		return true;
	}
	/**
		for each item contained in parameter list
			add that item to the end of this list
	*/
	template<class TDataType>
	inline bool List<TDataType>::addRange(const List<TDataType>& list)
	{
		bool isSuccessful = true;

		ListIterator<TDataType> * iterator = list.getIterator();

		while (iterator->next() && false == this->_isFull)
		{
			if (!this->add(iterator->getData()))
			{
				isSuccessful = false;
			}
		}

		delete iterator;

		return isSuccessful;
	}

	/**
		\code{.unparsed}
			if tail is not null, then
				if node "tail-1" is not null, then
					set node "tail-1" next to null
				delete node "tail"
				set node "tail-1" to the new tail
				decrease list count
				return success
			return failure, no tail to remove
		\endcode
	*/
	template<class TDataType>
	inline bool List<TDataType>::remove()
	{		
		if (nullptr != this->_tail)
		{
			LinkedListNode<TDataType> * tail = this->_tail;
			LinkedListNode<TDataType> * newTail = this->_tail->getPrevious();

			if (this->_head == this->_tail)
			{
				this->_head = this->_tail = nullptr;
			}
			else
			{
				newTail->setNext(nullptr);
				this->_tail = newTail;
			}
			delete tail;
			this->_count--;
			return true;
		}
		return false;
	}

	/**
		\code{.unparsed}
			if given position is outside of the bounds of the list, then
				return failure status
			retrieve the first node that has data matching the data input parameter,
				that is also located after position in the list
			if no node is found to match these parameters, then
				return failure status
			otherwise
				remove this node from the list
					if the node to remove is the head of the list, then
						if a node exists after the head, then
							update the next node's previous pointer to null
						update the head to the value of the next node
					if the node to remove is the tail of the list, then
						if a node exists before the tail, then
							update the previous node's next pointer to null
						update the tail to the value of the previous node
					if this is a middle node
						then update the previous and next node to point to each other (bypassing this node)
			deallocate this node
			reduce the list count
			return a successful status					
		\endcode
	*/
	template<class TDataType>
	inline bool List<TDataType>::remove(TDataType data, unsigned int position)
	{
		if (false == this->isInbounds(position, 0, this->_count - 1))
		{
			return false;
		}

		LinkedListNode<TDataType> * node = this->_head;

		unsigned int i = 0;
		bool isDataFound = false;
		while (nullptr != node && false == isDataFound)
		{
			if (position <= i && node->getData() == data)
			{
				isDataFound = true;
			}
			else
			{
				node = node->getNext();
				i++;
			}
		}

		if (nullptr == node)
		{
			return false;
		}
		
		LinkedListNode<TDataType> * previousNode = node->getPrevious();
		LinkedListNode<TDataType> * nextNode = node->getNext();

		if (nullptr == previousNode) // must be head if there is nothing in previous
		{
			if(nullptr != nextNode)
			{
				nextNode->setPrevious(nullptr);
			}
			
			this->_head = nextNode;
		}
		if (nullptr == nextNode) // must be tail if there is nothing in next
		{
			if(nullptr != previousNode)
			{
				previousNode->setNext(nullptr);
			}
			
			this->_tail = previousNode;
		}
		if(nullptr != previousNode && nullptr != nextNode) // must be a middle node if there is something behind and in front
		{
			previousNode->setNext(nextNode);
			nextNode->setPrevious(previousNode);
		}
		delete node;
		this->_count--;
		return true;
	}

	/**
		\code{.unparsed}
			starting at the head of the list,
				for each node encountered,
					store the value of the next node
					delete the current node
				update the head and tail to null
				reset the count to 0
		\endcode
	*/
	template<class TDataType>
	inline bool List<TDataType>::removeAll()
	{		
		LinkedListNode<TDataType> * node = this->_head;

		while (nullptr != node)
		{
			LinkedListNode<TDataType> * tmp = node;
			node = node->getNext();

			delete tmp;
		}

		this->_head = this->_tail = nullptr;
		this->_count = 0;

		return true;
	}

	/**
		\code{.unparsed}
			using indexOf,
				if indexOf returns -1,
					return failure status
				return successful status
		\endcode
	*/
	template<class TDataType>
	inline bool List<TDataType>::contains(TDataType data)
	{
		return -1 != this->indexOf(data);
	}

	/**
		\code{.unparsed}
			if the position parameter is outside of the bounds of the list, then
				return failure status
			otherwise,
				starting at the head of the list, begin looking for data
					if current node data is equal to data parameter, then
						if the current node is at position or greater in the list, then
							node is found,
							return the found location
						keep looking until we are at position or greater in the list
					keep looking until data matches current node data
				data was not found,
					return failure status
		\endcode
	*/
	template<class TDataType>
	inline int List<TDataType>::indexOf(TDataType data, unsigned int position)
	{
		if (false == this->isInbounds(position, 0, this->_count - 1))
		{
			return -1;
		}

		LinkedListNode<TDataType> * node = this->_head;

		unsigned int i = 0;
		while (nullptr != node)
		{
			if(data == node->getData())
			{
				if(position <= i)
				{
					return i;
				}
			}
			
			node = node->getNext();
			i++;
		}

		return -1;
	}

	/**
		\code{.unparsed}
			create a new, sorted list
			for each item in this list, add it to the sorted list
			empty out this list
			update the attributes of this list to those of the sorted list
		\endcode
	*/
	template<class TDataType>
	inline void List<TDataType>::sort()
	{
		List<TDataType> * newList = new List<TDataType>(true);

		LinkedListNode<TDataType> * node = this->_head;

		while (nullptr != node)
		{
			newList->add(node->getData());
			node = node->getNext();
		}

		this->removeAll();

		this->_head = newList->_head;
		this->_tail = newList->_tail;
		this->_count = newList->_count;
		this->_isFull = newList->_isFull;
		this->_isSorted = newList->_isSorted;
	}

	/**
		\code{.unparsed}
			sort the list
			for each item in the list,
				swap the previous and next pointers
			swap the head and the tail
		\endcode
	*/
	template<class TDataType>
	inline void List<TDataType>::sortDescending()
	{
		this->sort();

		LinkedListNode<TDataType> * node = this->_head;

		while (nullptr != node)
		{
			LinkedListNode<TDataType> * tmpNode = node;
			node = node->getNext();
			
			LinkedListNode<TDataType> * tmpPrev = tmpNode->getPrevious();
			tmpNode->setPrevious(tmpNode->getNext());
			tmpNode->setNext(tmpPrev);
		}

		LinkedListNode<TDataType> * tmpHead = this->_head;

		this->_head = this->_tail;
		this->_tail = tmpHead;

	}

	/**
		\code{.unparsed}
			if list is from beginning to end, then
				return an iterator that travels the list beginning to end
			otherwise
				return an iterator that travels the list end to beginning
		\endcode
	*/
	template<class TDataType>
	inline ListIterator<TDataType>* List<TDataType>::getIterator(bool isForward) const
	{
		if (true == isForward)
		{
			return new ListIterator<TDataType>(this->_head, true);
		}
		return new ListIterator<TDataType>(this->_tail, false);
	}

	/**
		\code{.unparsed}
			open the file "filename"
				starting at the head of the list,
				write each data element to the file
			save and close the file "filename"
		\endcode
	*/
	template<class TDataType>
	inline void List<TDataType>::serialize(char * fileName)
	{
	}

	/**
		\code{.unparsed}
			open the file "filename"
				for each data element in the file,
				add the element to the list
			close the file "filename"
		\endcode
	*/
	template<class TDataType>
	inline void List<TDataType>::deserialize(char * fileName)
	{
	}
	
}

#endif  // PSANDS_CISP430_LIST_H