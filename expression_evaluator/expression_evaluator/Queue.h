/**
@author Peter Sands
Email: w1541805@apps.losrios.edu

@file Queue.h
@brief A queue container class, which represents first-in first-out access
	This queue is based on the functionality of the list container class.
	Items will be inserted at the front of the list and removed from the end of it, which is how we model the first-in first-out access.

@see List.h

*/

#ifndef PSANDS_CISP430_QUEUE_H
#define PSANDS_CISP430_QUEUE_H

#include "List.h"

/**
@brief namespace for assignment 2
*/
namespace psands_cisp430_a2
{
	/// @tparam TDataType is the type of data this node stores.
	template <class TDataType>
	class Queue
	{
	private:
		List<TDataType> * _list; ///< where we represent the queue structure

	public:
		/**
			default constructor initializes the queue to the default state
		*/
		Queue();
		/**
			copy constructor will copy the contents of one queue into this queue.
			@param queue the queue to copy into this queue
		*/
		Queue(const Queue<TDataType> & queue);
		/**
			destructor frees dynamically allocated memory
		*/
		~Queue();

		/**
			less than operator is a required implementation to allow the ability to store queues in these assignment 2 container classes
			@param queue the queue to compare this queue against
			@returns true if this queue is less than the parameter queue
		*/
		bool operator <(Queue<TDataType> & queue) const;

		/**
			equals operator is a required implementation to allow the ability to store queues in these assignment 2 container classes (for purposes of setting data elements in nodes)
			@param queue the queue to set this queue equal to
		*/
		void operator =(const Queue & queue);

		/**
			returns the element at the front of the queue without removing it from the queue
			@return the element at the front of the queue without removing it from the queue
		*/
		TDataType peek();
		/**
			returns the element at the front of the queue and removes it from the queue
			@return the element at the front of the queue and removes it from the queue
		*/
		TDataType dequeue();
		/**
			adds the data parameter to the end of the queue
			@param data the data to add to the end of the queue
			@return true if the add action was successful
		*/
		bool enqueue(TDataType data);

		/**
			returns true if there are no elements in the queue
			@return true if there are no elements in the queue
		*/
		bool isEmpty();
		/**
			returns true if there was a failure to add a new element to the queue
			@return true if there was a failure to add a new element to the queue
		*/
		bool isFull();

		/**
			saves the queue to disk using the parameter filename as the file to store it in
			@param filename the file to store the queue in
		*/
		void serialize(char * filename);
		/**
			loads a queue from disk to memory using the parameter filename as the file to retrieve it from
			@param filename the file to restore the queue from
		*/
		void deserialize(char * filename);

	};

	/**
		\code{.unparsed}
			Initialize the list to the default state
			Do not use a sorted list
		\endcode
	*/
	template<class TDataType>
	inline Queue<TDataType>::Queue()
	{
		_list = new List<TDataType>();
	}

	/**
		\code{.unparsed}
			Copy the contents of the other queue's list into our list
		\endcode
	*/
	template<class TDataType>
	inline Queue<TDataType>::Queue(const Queue<TDataType> & queue)
	{
		this->_list = new List<TDataType>(*queue._list);
	}

	/**
		\code{.unparsed}
			delete our dynamically allocated list
		\endcode
	*/
	template<class TDataType>
	inline Queue<TDataType>::~Queue()
	{
		delete this->_list;
	}

	/**
		\code{.unparsed}
			use the count member data to determine if this queue's list is less than other queue's list
		\endcode
	*/
	template<class TDataType>
	inline bool Queue<TDataType>::operator<(Queue<TDataType>& queue) const
	{
		return this->_list->getCount() < queue._list->getCount();
	}

	/**
		\code{.unparsed}
			Set this queue's list equal to the other queue's list
		\endcode
	*/
	template<class TDataType>
	inline void Queue<TDataType>::operator=(const Queue & queue)
	{
		*this->_list = *queue._list;
	}

	/**
		\code{.unparsed}
			determine the position of the last element in this queue's list
			return that element without modifying list
			if there are no elements in this queue's list then return a default element
		\endcode
	*/
	template<class TDataType>
	inline TDataType Queue<TDataType>::peek()
	{
		unsigned int listCount = this->_list->getCount();

		if (0 == listCount)
		{
			return TDataType(); // or throw error?
		}

		return this->_list->getElementAt(listCount - 1);
	}

	/**
		\code{.unparsed}
			return the element returned by the peek action
			remove that element from the list
		\endcode
	*/
	template<class TDataType>
	inline TDataType Queue<TDataType>::dequeue()
	{
		TDataType element = this->peek();

		this->_list->remove();

		return element;
	}

	/**
		\code{.unparsed}
			insert the data parameter to the beginning of the list
		\endcode
	*/
	template<class TDataType>
	inline bool Queue<TDataType>::enqueue(TDataType data)
	{
		return this->_list->insert(data, 0);
	}

	/**
		\code{.unparsed}
			return list isEmpty result
		\endcode
	*/
	template<class TDataType>
	inline bool Queue<TDataType>::isEmpty()
	{
		return this->_list->isEmpty();
	}

	/**
		\code{.unparsed}
			return list isFull result
		\endcode
	*/
	template<class TDataType>
	inline bool Queue<TDataType>::isFull()
	{
		return this->_list->isFull();
	}

	/**
		\code{.unparsed}
			Without any members of our own, other than the list, serialize the list
		\endcode
	*/
	template<class TDataType>
	inline void Queue<TDataType>::serialize(char * filename)
	{
		this->_list->serialize(filename);
	}

	/**
		\code{.unparsed}
			Without any members of our own, other than the list, deserialize the list
		\endcode
	*/
	template<class TDataType>
	inline void Queue<TDataType>::deserialize(char * filename)
	{
		this->_list->deserialize(filename);
	}

}

#endif // PSANDS_CISP430_QUEUE_H