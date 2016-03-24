//Peter Sands
//CISP 430 - Wed 6:30
//Spring 2016
//Assign 1

#include "Slot.h"
#include <fstream>

#ifndef PSANDS_CISP430_BUCKET_H
#define PSANDS_CISP430_BUCKET_H

namespace psands_cisp430
{
	template <class TKey, class TData>
	class Bucket
	{
	public:
		Bucket();
		Bucket(unsigned int maxSlots);
		Bucket(int overflowIdx, unsigned int count, unsigned int maxSlots);
		Bucket(Slot<TKey, TData>* slots[], int overflowIdx, unsigned int count, unsigned int maxSlots);
		Bucket(const Bucket &bucket);
		~Bucket();

		// ACCESSORS
		TKey getKey(int slotIdx) const;
		TData getData(int slotIdx) const;
		int getChainLength() const;
		int getOverflowIdx() const;
		int getSlotNumberByKey(TKey key) const;

		// MUTATORS	
		void setKey(TKey key, int slotIdx);
		void setData(TData data, int slotIdx);
		void set(TKey key, TData data, int slotIdx);
		void set(Slot<TKey, TData>* slot, int slotIdx);
		void setOverflowIdx(int overflowIdx);

		// HASHING
		void insert(TKey key, TData data);
		bool hasMatch(TKey key) const;
		bool hasFreeSlot() const;
		bool hasAvailableOverflow() const;

		// IMPORT / EXPORT
		void serialize(std::ofstream &file) const;
		void deserialize(std::ifstream &file);

		// REPORT
		void report(std::ostream& outstr) const;

	private:
		Slot<TKey, TData>** _slots;
		int _overflowIdx;
		unsigned int _count, _maxSlots;

		// SLOT SETUP
		void initializeSlots(unsigned int maxSlots);
	};

	template<class TKey, class TData>
	inline Bucket<TKey, TData>::Bucket() : Bucket(1)
	{

	}

	template<class TKey, class TData>
	inline Bucket<TKey, TData>::Bucket(unsigned int maxSlots) : Bucket(-1, 0, maxSlots)
	{
	}

	template<class TKey, class TData>
	inline Bucket<TKey, TData>::Bucket(int overflowIdx, unsigned int count, unsigned int maxSlots)
	{
		this->_overflowIdx = -1;
		this->_count = count;
		this->_maxSlots = maxSlots;
		this->initializeSlots(maxSlots);
	}

	template<class TKey, class TData>
	inline Bucket<TKey, TData>::Bucket(Slot<TKey, TData>* slots[], int overflowIdx, unsigned int count, unsigned int maxSlots) : Bucket(overflowIdx, count, maxSlots)
	{
		for (unsigned int i = 0; i < maxSlots; i++)
		{
			this->set(slots[i], i);
		}
	}

	template<class TKey, class TData>
	inline Bucket<TKey, TData>::Bucket(const Bucket & bucket)
	{
	}

	template<class TKey, class TData>
	inline Bucket<TKey, TData>::~Bucket()
	{
		if (_slots)
		{
			for (unsigned int i = 0; i < this->_maxSlots; i++)
			{
				if (_slots[i])
				{
					delete _slots[i];
				}
			}
			delete _slots;
		}
	}

	template<class TKey, class TData>
	inline TKey Bucket<TKey, TData>::getKey(int slotIdx) const
	{
		return this->_slots[slotIdx]->getKey();
	}

	template<class TKey, class TData>
	inline TData Bucket<TKey, TData>::getData(int slotIdx) const
	{
		return this->_slots[slotIdx]->getData();
	}

	template<class TKey, class TData>
	inline int Bucket<TKey, TData>::getChainLength() const
	{
		return this->_count;
	}

	template<class TKey, class TData>
	inline int Bucket<TKey, TData>::getOverflowIdx() const
	{
		return this->_overflowIdx;
	}

	template<class TKey, class TData>
	inline int Bucket<TKey, TData>::getSlotNumberByKey(TKey key) const
	{
		for (unsigned int i = 0; i < this->_count; i++)
		{
			if (this->_slots[i]->getKey() == key)
			{
				return i;
			}
		}
		return -1; // not found
	}

	template<class TKey, class TData>
	inline void Bucket<TKey, TData>::setKey(TKey key, int slotIdx)
	{
		this->_slots[slotIdx]->setKey(key);
	}

	template<class TKey, class TData>
	inline void Bucket<TKey, TData>::setData(TData data, int slotIdx)
	{
		this->_slots[slotIdx]->setData(data);
	}

	template<class TKey, class TData>
	inline void Bucket<TKey, TData>::set(TKey key, TData data, int slotIdx)
	{
		this->_slots[slotIdx]->set(key, data);
	}

	template<class TKey, class TData>
	inline void Bucket<TKey, TData>::set(Slot<TKey, TData>* slot, int slotIdx)
	{
		*this->_slots[slotIdx] = *slot;
	}

	template<class TKey, class TData>
	inline void Bucket<TKey, TData>::setOverflowIdx(int overflowIdx)
	{
		this->_overflowIdx = overflowIdx;
	}

	template<class TKey, class TData>
	inline void Bucket<TKey, TData>::insert(TKey key, TData data)
	{
		this->_slots[this->_count]->set(key, data);
		this->_count++;
	}

	template<class TKey, class TData>
	inline bool Bucket<TKey, TData>::hasMatch(TKey key) const
	{
		return -1 != this->getSlotNumberByKey(key);
	}

	template<class TKey, class TData>
	inline bool Bucket<TKey, TData>::hasFreeSlot() const
	{
		return this->_count < this->_maxSlots;
	}

	template<class TKey, class TData>
	inline bool Bucket<TKey, TData>::hasAvailableOverflow() const
	{
		return -1 != this->_overflowIdx;
	}

	template<class TKey, class TData>
	inline void Bucket<TKey, TData>::serialize(std::ofstream & file) const
	{
		file.write((char*)&this->_overflowIdx, sizeof(this->_overflowIdx));
		file.write((char*)&this->_count, sizeof(this->_count));
		file.write((char*)&this->_maxSlots, sizeof(this->_maxSlots));
		for (unsigned int i = 0; i < this->_maxSlots; i++)
		{
			this->_slots[i]->serialize(file);
		}
	}

	template<class TKey, class TData>
	inline void Bucket<TKey, TData>::deserialize(std::ifstream & file)
	{
		file.read((char*)&this->_overflowIdx, sizeof(this->_overflowIdx));
		file.read((char*)&this->_count, sizeof(this->_count));
		file.read((char*)&this->_maxSlots, sizeof(this->_maxSlots));
		for (unsigned int i = 0; i < this->_maxSlots; i++)
		{
			this->_slots[i]->deserialize(file);
		}
	}

	template<class TKey, class TData>
	inline void Bucket<TKey, TData>::report(std::ostream& outstr) const
	{
		for (unsigned int i = 0; i < this->_maxSlots; i++)
		{
			outstr << "\tSlot " << i + 1 << ": ";
			this->_slots[i]->report(outstr);
			outstr << std::endl;
		}
		outstr << "\tOverflow Pointer: " << this->_overflowIdx << std::endl;
	}

	template<class TKey, class TData>
	inline void Bucket<TKey, TData>::initializeSlots(unsigned int maxSlots)
	{
		this->_slots = new Slot<TKey, TData>*[maxSlots];
		for (unsigned int i = 0; i < maxSlots; i++)
		{
			this->_slots[i] = new Slot<TKey, TData>();
		}
	}

}

#endif