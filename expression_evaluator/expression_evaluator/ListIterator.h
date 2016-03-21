/**
	@author Peter Sands
	Email: w1541805@apps.losrios.edu

	@file ListIterator.h
	@brief An iterator that can be used to traverse a list

	@see List.h
	@see LinkedListNode.h
*/

#ifndef PSANDS_CISP430_ListIterator_H
#define PSANDS_CISP430_ListIterator_H

/**
@brief namespace for assignment 2
*/
namespace psands_cisp430_a2
{

	/// @tparam TDataType is the type of data this node stores.
	template <class TDataType>
	class ListIterator
	{
	private:
		LinkedListNode<TDataType> * _current; ///< stores the current position of the iterator
		bool _hasStarted; ///< stores whether or not iteration hsa begun
		bool _isHeadToTail; ///< stores whether or not we are traversing the list front to back or back to front

	public:
		/**
			default constructor initializes the iterator to the default state
		*/
		ListIterator<TDataType>();
		/**
			parameterized constructor is used to initialize the current node and whether or not we are traversing forward or backward
			@param node the node we will set our current node to
			@param isHeadToTail determines the direction the iterator will go
		*/
		ListIterator<TDataType>(LinkedListNode<TDataType> * node, bool isHeadoTail = true);
		/**
			copy constructor will be where we copy our values from
			@param listIterator will copy our values from this list iterator
		*/
		ListIterator<TDataType>(const ListIterator<TDataType> & listIterator);

		/**
			returns true if there is another element to iterate to
			@return true if there is another element to iterate to
		*/
		bool hasNext() const;
		/**
			iterates to the next element and returns true if there is another element to iterate to after the iteration has occurred
			@return true if there is another element to iterate to
		*/
		bool next();

		/**
			get the data value at the current iterator position
			@return the data value at the current iterator position
		*/
		TDataType getData();

	};  // end of class Iterator

	/**
		\code{.unparsed}
			sets the list iterator to the default state
		\endcode
	*/
	template<class TDataType>
	inline ListIterator<TDataType>::ListIterator()
	{
		this->_current = nullptr;
		this->_isHeadToTail = true;
		this->_hasStarted = false;
	}

	/**
	\code{.unparsed}
		set the current position to that of the parameter node
		set the direction by the parameter isHeadToTail
		set the starting condition to has not started
	\endcode
	*/
	template<class TDataType>
	inline ListIterator<TDataType>::ListIterator(LinkedListNode<TDataType>* node, bool isHeadToTail = true)
	{
		this->_current = node;
		this->_isHeadToTail = isHeadToTail;
		this->_hasStarted = false;
	}

	/**
	\code{.unparsed}
		copy the private member data from the parameter listIterator
	\endcode
	*/
	template<class TDataType>
	inline ListIterator<TDataType>::ListIterator(const ListIterator<TDataType> & listIterator)
	{
		this->_current = ListIterator._current;
		this->_isHeadToTail = ListIterator._isHeadToTail;
		this->_hasStarted = ListIterator._hasStarted;
	}


	/**
	\code{.unparsed}
		if the current node is null, then
			return false
		otherwise, if the direction is forward, then
			check if the next node is null
			return true if is null
		otherwise, if the direction is backward, then
			check if the previous node is null
			return true if it is null
	\endcode
	*/
	template<class TDataType>
	inline bool ListIterator<TDataType>::hasNext() const
	{
		if (nullptr == this->_current)
		{
			return false;
		}

		if (true == this->_isHeadToTail)
		{
			return nullptr != this->_current->getNext();
		}
		else
		{
			return nullptr != this->_current->getPrevious();
		}

	}

	/**
	\code{.unparsed}
		use the method hasNext to determine if there is a next element,
		if the list has not "started", then start the list [this allows (while itr->next()) { next->getData() } style, without skipping the first element]
		otherwise, if there is a next element then retrieve that element,
			check if direction is forward, return next node if it is
			check if direction is backward, return previous node if it is
	\endcode
	*/
	template<class TDataType>
	inline bool ListIterator<TDataType>::next()
	{
		bool isNext = this->hasNext();

		if (false == this->_hasStarted)
		{
			this->_hasStarted = true;
		}
		else if(true == isNext)
		{
			if (true == this->_isHeadToTail)
			{
				this->_current = this->_current->getNext();
			}
			else
			{
				this->_current = this->_current->getPrevious();
			}
		}

		return isNext;
	}

	/**
		if the iterator has not started, but we are calling get data, then
			start the iterator
		check if we are on a null pointer,
			throw exception if we are trying to retrieve data from a null
		otherwise,
			return the data from the current node
	*/
	template<class TDataType>
	inline TDataType ListIterator<TDataType>::getData()
	{
		if (false == this->_hasStarted)
		{
			this->_hasStarted = true;
		}

		if (nullptr == this->_current)
		{
			throw "something is wrong here...";
		}

		return this->_current->getData();
	}

}

#endif  // PSANDS_CISP430_ListIterator_H
