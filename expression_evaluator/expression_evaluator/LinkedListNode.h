/**
	@author Peter Sands
	Email: w1541805@apps.losrios.edu

	@file LinkedListNode.h
	@brief A two direction node for the purposes of being used in a linked-list
*/

#ifndef PSANDS_CISP430_LINKEDLISTNODE_H
#define PSANDS_CISP430_LINKEDLISTNODE_H

/**
@brief namespace for assignment 2
*/
namespace psands_cisp430_a2
{

	/// @tparam TDataType is the type of data this node stores.
	template <class TDataType>
	class LinkedListNode
	{
	private:
		TDataType _data; ///< this node's data
		LinkedListNode * _next; ///< this node's next node
		LinkedListNode * _previous; ///< this node's previous node

	public:
		/// default constructor
		LinkedListNode();
		/// parameterized constructor - to initialize this node's data
		LinkedListNode(TDataType data);
		/// copy constructor - to initialize data and update next and previous node addresses
		LinkedListNode(const LinkedListNode<TDataType> & linkedListNode);

		/**
		accessor to retrieve this node's data
		\return data stored in this node
		*/
		TDataType getData() const;
		/**
		accessor to retrieve this node's next node
		\return address of next node
		*/
		LinkedListNode<TDataType> * getNext() const;
		/**
		accessor to retrieve this node's previous node
		\return address of previous node
		*/
		LinkedListNode<TDataType> * getPrevious() const;

		/**
		mutator to update this node's data
		\param data this node's data is updated with this parameter
		*/
		void setData(TDataType data);
		/**
		mutator to update this node's next node address
		\param next this node's next node address is updated with this parameter
		*/
		void setNext(LinkedListNode<TDataType> * next);
		/**
		mutator to update this node's previous node address
		\param previous this node's previous node address is updated with this parameter
		*/
		void setPrevious(LinkedListNode<TDataType> * previous);
		/**
		mutator to update this node's next and previous node addresses
		\param next this node's next node address is updated with this parameter
		\param previous this node's previous node address is updated with this parameter
		*/
		void setNodes(LinkedListNode<TDataType> * next, LinkedListNode<TDataType> * previous);

	};  // end of class LinkedListNode

	template<class TDataType>
	inline LinkedListNode<TDataType>::LinkedListNode()
	{
		this->_next = nullptr;
		this->_previous = nullptr;
	}

	template<class TDataType>
	inline LinkedListNode<TDataType>::LinkedListNode(TDataType data) : LinkedListNode()
	{
		this->setData(data);
	}

	template<class TDataType>
	inline LinkedListNode<TDataType>::LinkedListNode(const LinkedListNode<TDataType> & linkedListNode)
	{
		this->setData(data);
		this->setNodes(linkedListNode.getNext(), linkedListNode.getPrevious());
	}

	template<class TDataType>
	inline TDataType LinkedListNode<TDataType>::getData() const
	{
		return this->_data;
	}

	template<class TDataType>
	inline LinkedListNode<TDataType> * LinkedListNode<TDataType>::getNext() const
	{
		return this->_next;
	}

	template<class TDataType>
	inline LinkedListNode<TDataType> * LinkedListNode<TDataType>::getPrevious() const
	{
		return this->_previous;
	}

	template<class TDataType>
	inline void LinkedListNode<TDataType>::setData(TDataType data)
	{
		this->_data = data;
	}

	template<class TDataType>
	inline void LinkedListNode<TDataType>::setNext(LinkedListNode<TDataType> * next)
	{
		this->_next = next;
	}

	template<class TDataType>
	inline void LinkedListNode<TDataType>::setPrevious(LinkedListNode<TDataType> * previous)
	{
		this->_previous = previous;
	}

	template<class TDataType>
	inline void LinkedListNode<TDataType>::setNodes(LinkedListNode<TDataType> * next, LinkedListNode<TDataType> * previous)
	{
		this->setNext(next);
		this->setPrevious(previous);
	}

}

#endif  // PSANDS_CISP430_LINKEDLISTNODE_H
