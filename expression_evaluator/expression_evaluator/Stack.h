/**
@author Peter Sands
Email: w1541805@apps.losrios.edu

@file Stack.h
@brief A stack style container class, which represents last-in first-out access
	This stack is based on the functionality of the list container.
	Items inserted into this stack will be inserted at the end of the backing list and removed from the end of the list to achieve last-in first-out access.

@see List.h

*/

#ifndef PSANDS_CISP430_Stack_H
#define PSANDS_CISP430_Stack_H

/**
@brief namespace for assignment 2
*/
namespace psands_cisp430_a2
{
	/// @tparam TDataType is the type of data this node stores.
	template <class TDataType>
	class Stack
	{
	private:
		List<TDataType> * _list; ///< backing list to represent this stack

	public:
		/**
			default constructor will initialize this stack to the default state
		*/
		Stack();
		/**
			copy constructor will initialize this stack to the state of the parameter stack
			@param stack the stack to copy the values from
		*/
		Stack(const Stack<TDataType> & stack);
		/**
			destructor will free dynamically allocated memory
		*/
		~Stack();

		/**
			less than operator is required to allow for assignment 2 containers to contain stacks
			@param stack the stack to compare this stack to
			@return true if this stack is less than the param stack
		*/
		bool operator <(Stack<TDataType> & stack) const;

		/**
			equals operator is required to allow for assignment 2 containers to contain stacks
			@param stack the stack to copy into this stack
		*/
		void operator =(const Stack & stack);

		/**
			peek will return the next item to retrieve from the stack without removing it from the backing list
			@return the next item to retrieve from the stack without removing it from the backing list
		*/
		TDataType peek();
		/**
			pop will return the next item to retrieve from the stack and will remove it from the backing list
			@return the next item to retrieve from the stack
		*/
		TDataType pop();
		/**
			push will add the data element to the stack
			@param data the element to add to the stack
			@return true if the add action was successful
		*/
		bool push(TDataType data);

		/**
			return true if the stack is empty
		*/
		bool isEmpty();
		/**
			return true if the stack is full
		*/
		bool isFull();

		/**
			will serialize this stack to disk using filename as the location to store it
			@param filename the file to store this stack
		*/
		void serialize(char * filename);
		/**
			will deserialize the stack from disk to this stack from the file represented by filename
			@param filename the file to restore from
		*/
		void deserialize(char * filename);

	};

	/**
		\code{.unparsed}
			set the backing list to its initial state, do not use a sorted list
		\endcode
	*/
	template<class TDataType>
	inline Stack<TDataType>::Stack()
	{
		_list = new List<TDataType>();
	}

	/**
	\code{.unparsed}
		set the backing list to the values contained in the parameter stack's list
	\endcode
	*/
	template<class TDataType>
	inline Stack<TDataType>::Stack(const Stack<TDataType>& stack)
	{
		this->_list = new List<TDataType>(*stack._list);
	}

	/**
	\code{.unparsed}
		free memory allocated by this stack's list
	\endcode
	*/
	template<class TDataType>
	inline Stack<TDataType>::~Stack()
	{
		delete this->_list;
	}

	/**
	\code{.unparsed}
		compare this list to the parameter stack's list by way of the count of the lists
	\endcode
	*/
	template<class TDataType>
	inline bool Stack<TDataType>::operator<(Stack<TDataType>& stack) const
	{
		return this->_list->getCount() < stack._list->getCount();
	}

	/**
	\code{.unparsed}
		set this stack's list equal to that of the parameter stack's list
	\endcode
	*/
	template<class TDataType>
	inline void Stack<TDataType>::operator=(const Stack & stack)
	{
		*this->_list = *stack._list;
	}

	/**
	\code{.unparsed}
		retrieve the last item from this stack's list
		return that retrieved item
	\endcode
	*/
	template<class TDataType>
	inline TDataType Stack<TDataType>::peek()
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
		retrieve the last item from this stack's list
		remove that item from this stack's list
		return the retrieved item
	\endcode
	*/
	template<class TDataType>
	inline TDataType Stack<TDataType>::pop()
	{
		TDataType element = this->peek();

		this->_list->remove();

		return element;
	}

	/**
	\code{.unparsed}
		add a new item to this stack's list (the end of the list)
	\endcode
	*/
	template<class TDataType>
	inline bool Stack<TDataType>::push(TDataType data)
	{
		return this->_list->add(data);
	}

	/**
	\code{.unparsed}
		return the result of this stack's list empty method
	\endcode
	*/
	template<class TDataType>
	inline bool Stack<TDataType>::isEmpty()
	{
		return this->_list->isEmpty();
	}

	/**
	\code{.unparsed}
		return the result of this stack's full method
	\endcode
	*/
	template<class TDataType>
	inline bool Stack<TDataType>::isFull()
	{
		return this->_list->isFull();
	}

	/**
	\code{.unparsed}
		use this stack's list serialize method
	\endcode
	*/
	template<class TDataType>
	inline void Stack<TDataType>::serialize(char * filename)
	{
		this->_list->serialize(filename);
	}

	/**
	\code{.unparsed}
		use this stack's list deserialize method
	\endcode
	*/
	template<class TDataType>
	inline void Stack<TDataType>::deserialize(char * filename)
	{
		this->_list->deserialize(filename);
	}
	
}

#endif // PSANDS_CISP430_STACK_H