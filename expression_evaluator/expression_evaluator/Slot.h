//Peter Sands
//CISP 430 - Wed 6:30
//Spring 2016
//Assign 1

#ifndef PSANDS_CISP430_SLOT_H
#define PSANDS_CISP430_SLOT_H

#include <fstream>
#include "Str.h"

namespace psands_cisp430
{
	template <class TKey, class TData>
	class Slot
	{
	public:
		Slot();
		Slot(TKey key, TData data);
		Slot(const Slot &slot);

		// ACCESSORS
		TKey getKey() const;
		TData getData() const;

		// MUTATORS
		void setKey(TKey key);
		void setData(TData data);
		void set(TKey key, TData data);

		// OPERATOR OVERLOADS
		const Slot &operator=(const Slot &slot);

		// IMPORT / EXPORT
		void serialize(std::ofstream &file) const;
		void deserialize(std::ifstream &file);

		// REPORT
		void report(std::ostream& outstr) const;

	private:
		TKey _key;
		TData _data;
	};

	template<class TKey, class TData>
	inline Slot<TKey, TData>::Slot()
	{
		this->_key = TKey();
		this->_data = TData();
	}

	template<class TKey, class TData>
	inline Slot<TKey, TData>::Slot(TKey key, TData data) : Slot()
	{
		this->set(key, data);
	}

	template<class TKey, class TData>
	inline Slot<TKey, TData>::Slot(const Slot & slot) : Slot(slot.getKey(), slot.getData())
	{
	}

	template<class TKey, class TData>
	inline TKey Slot<TKey, TData>::getKey() const
	{
		return this->_key;
	}

	template<class TKey, class TData>
	inline TData Slot<TKey, TData>::getData() const
	{
		return this->_data;
	}

	template<class TKey, class TData>
	inline void Slot<TKey, TData>::setKey(TKey key)
	{
		this->_key = key;
	}

	template<class TKey, class TData>
	inline void Slot<TKey, TData>::setData(TData data)
	{
		this->_data = data;
	}

	template<class TKey, class TData>
	inline void Slot<TKey, TData>::set(TKey key, TData data)
	{
		this->setKey(key);
		this->setData(data);
	}

	template<class TKey, class TData>
	inline const Slot<TKey, TData> & Slot<TKey, TData>::operator=(const Slot & slot)
	{
		if (this == &slot) return *this;
		this->setKey(slot.getKey());
		this->setData(slot.getData());
		return *this;
	}

	template<class TKey, class TData>
	inline void Slot<TKey, TData>::serialize(std::ofstream & file) const
	{
		this->_key.serialize(file);
		this->_data.serialize(file);
	}

	template<class TKey, class TData>
	inline void Slot<TKey, TData>::deserialize(std::ifstream & file)
	{
		this->_key.deserialize(file);
		this->_data.deserialize(file);
	}

	template<class TKey, class TData>
	inline void Slot<TKey, TData>::report(std::ostream& outstr) const
	{
		outstr << this->getKey() << this->getData();
	}
}

#endif

