//Peter Sands
//CISP 430 - Wed 6:30
//Spring 2016
//Assign 1

#ifndef PSANDS_CISP430_HASHTABLE_H
#define PSANDS_CISP430_HASHTABLE_H

#include "Bucket.h"
#include <fstream>
#include <iomanip>

namespace psands_cisp430
{
	// abstract hashtable class where TKey and TData must implemented serialize and deserialize
	template <class TKey, class TData>
	class Hashtable
	{
	public:
		Hashtable();
		Hashtable(int maxBucket, int maxSlots, int maxOverflowBuckets);
		Hashtable(const Hashtable &hashtable);
		~Hashtable();

		// INSERT
		void insert(TKey key, TData data);

		// IMPORT / EXPORT
		void writeToDisk(char* filename);
		void restoreToMem(char* filename);

		// REPORTING / PRINTING
		void search(std::ostream& outstr, TKey key);
		void generateReport(std::ostream& outstr, bool isBeforeRestore);
		void generateStatReport(std::ostream& outstr);


	protected:
		virtual int hashFunction(TKey key) = 0; // hashing function is dependent on TKey
		int getPrimaryBucketCount() const;

	private:
		Bucket<TKey, TData>** _buckets;
		int _nextAvailableOverflowBucketIdx;
		unsigned int _maxBuckets, _maxPrimaryBuckets, _maxSlots;

		// ACCESSOR
		int getNextAvailableOverflowIdx();

		// BUCKET SETUP / TEARDOWN
		void initializeBuckets(unsigned int maxBuckets, unsigned int maxSlots);
		void finalizeBuckets();

		// INSERT
		void insert(TKey key, TData data, int hashIdx);

		// REPORTING
		void search(std::ostream& outstr, TKey key, int hashIdx);
		void generateReportHeader(std::ostream& outstr, bool isStatReport, bool isBeforeRestore);
		int getCollisionChainLength(unsigned int bucketIdx) const;
	};

	template<class TKey, class TData>
	inline Hashtable<TKey, TData>::Hashtable()
	{
		this->_buckets = nullptr;
	}

	template<class TKey, class TData>
	inline Hashtable<TKey, TData>::Hashtable(int maxBucket, int maxSlots, int maxOverflowBuckets)
	{
		this->_nextAvailableOverflowBucketIdx = (maxBucket - maxOverflowBuckets) > 0 ? (maxBucket - maxOverflowBuckets) : -1;
		this->_maxBuckets = maxBucket;
		this->_maxPrimaryBuckets = (maxBucket - maxOverflowBuckets) > 0 ? (maxBucket - maxOverflowBuckets) : maxBucket;
		this->_maxSlots = maxSlots;

		this->initializeBuckets(maxBucket, maxSlots);
	}

	template<class TKey, class TData>
	inline Hashtable<TKey, TData>::Hashtable(const Hashtable & hashtable)
	{
		this->_buckets = hashtable._buckets;
		this->_nextAvailableOverflowBucketIdx = hashtable._nextAvailableOverflowBucketIdx;
		this->_maxBuckets = hashtable._maxBuckets;
		this->_maxPrimaryBuckets = hashtable._maxPrimaryBuckets;
		this->_maxSlots = hashtable._maxSlots;
	}

	template<class TKey, class TData>
	inline Hashtable<TKey, TData>::~Hashtable()
	{
		this->finalizeBuckets();
	}

	template<class TKey, class TData>
	inline void Hashtable<TKey, TData>::insert(TKey key, TData data)
	{
		int hashIdx = this->hashFunction(key);
		this->insert(key, data, hashIdx);
	}

	template<class TKey, class TData>
	inline void Hashtable<TKey, TData>::writeToDisk(char* filename)
	{
		ofstream outfile;
		outfile.open(filename, ios::out | ios::binary);

		outfile.write((char*)&this->_nextAvailableOverflowBucketIdx, sizeof(this->_nextAvailableOverflowBucketIdx));
		outfile.write((char*)&this->_maxBuckets, sizeof(this->_maxBuckets));
		outfile.write((char*)&this->_maxPrimaryBuckets, sizeof(this->_maxPrimaryBuckets));
		outfile.write((char*)&this->_maxSlots, sizeof(this->_maxSlots));
		for (unsigned int i = 0; i < this->_maxBuckets; i++)
		{
			this->_buckets[i]->serialize(outfile);
		}

		outfile.close();
	}

	template<class TKey, class TData>
	inline void Hashtable<TKey, TData>::restoreToMem(char* filename)
	{
		ifstream infile;
		infile.open(filename, ios::in | ios::binary);

		infile.read((char*)&this->_nextAvailableOverflowBucketIdx, sizeof(this->_nextAvailableOverflowBucketIdx));
		infile.read((char*)&this->_maxBuckets, sizeof(this->_maxBuckets));
		infile.read((char*)&this->_maxPrimaryBuckets, sizeof(this->_maxPrimaryBuckets));
		infile.read((char*)&this->_maxSlots, sizeof(this->_maxSlots));

		this->finalizeBuckets();
		this->initializeBuckets(this->_maxBuckets, this->_maxSlots);

		for (unsigned int i = 0; i < this->_maxBuckets; i++)
		{
			this->_buckets[i]->deserialize(infile);
		}

		infile.close();
	}

	template<class TKey, class TData>
	inline void Hashtable<TKey, TData>::search(std::ostream& outstr, TKey key)
	{
		int hashIdx = this->hashFunction(key);
		search(outstr, key, hashIdx);
	}

	template<class TKey, class TData>
	inline void Hashtable<TKey, TData>::generateReport(std::ostream& outstr, bool isBeforeRestore)
	{
		this->generateReportHeader(outstr, false, isBeforeRestore);

		for (unsigned int i = 0; i < this->_maxBuckets; i++)
		{
			outstr << "Bucket " << i + 1 << endl;
			this->_buckets[i]->report(outstr);
		}
	}

	template<class TKey, class TData>
	inline void Hashtable<TKey, TData>::generateStatReport(std::ostream& outstr)
	{
		double sum = 0;
		unsigned int count = 0;

		this->generateReportHeader(outstr, true, false);

		for (unsigned int i = 0; i < this->_maxPrimaryBuckets; i++)
		{
			int bucketChainLength = this->getCollisionChainLength(i);

			if (0 < bucketChainLength)
			{
				outstr << "Bucket " << i + 1 << ":\tLength: " << bucketChainLength << endl;
				sum += bucketChainLength;
				count++;
			}
		}
		outstr << "Total Collision Chain Length: " << sum << endl;
		outstr << "Average Collision Chain Length: " << sum / count << endl;
	}

	template<class TKey, class TData>
	inline int Hashtable<TKey, TData>::getCollisionChainLength(unsigned int bucketIdx) const
	{
		int collisionChainLength = this->_buckets[bucketIdx]->getChainLength();

		if (this->_buckets[bucketIdx]->hasAvailableOverflow())
		{
			collisionChainLength += this->getCollisionChainLength(this->_buckets[bucketIdx]->getOverflowIdx());
		}
		else
		{
			collisionChainLength--;
		}

		return collisionChainLength;
	}

	template<class TKey, class TData>
	inline int Hashtable<TKey, TData>::getPrimaryBucketCount() const
	{
		return this->_maxPrimaryBuckets;
	}

	template<class TKey, class TData>
	inline int Hashtable<TKey, TData>::getNextAvailableOverflowIdx()
	{
		if (-1 == this->_nextAvailableOverflowBucketIdx || this->_maxBuckets <= ++this->_nextAvailableOverflowBucketIdx)
		{
			this->_nextAvailableOverflowBucketIdx = -1;
		}
		return this->_nextAvailableOverflowBucketIdx;
	}

	template<class TKey, class TData>
	inline void Hashtable<TKey, TData>::initializeBuckets(unsigned int maxBuckets, unsigned int maxSlots)
	{
		this->_buckets = new Bucket<TKey, TData>*[maxBuckets];
		for (unsigned int i = 0; i < maxBuckets; i++)
		{
			this->_buckets[i] = new Bucket<TKey, TData>(maxSlots);
		}
	}

	template<class TKey, class TData>
	inline void Hashtable<TKey, TData>::finalizeBuckets()
	{
		if (nullptr != this->_buckets)
		{
			for (unsigned int i = 0; i < this->_maxBuckets; i++)
			{
				if (nullptr != this->_buckets[i])
				{
					delete this->_buckets[i];
				}
			}
			delete this->_buckets;
		}
	}

	template<class TKey, class TData>
	inline void Hashtable<TKey, TData>::insert(TKey key, TData data, int hashIdx)
	{
		if (this->_buckets[hashIdx]->hasFreeSlot())
		{
			this->_buckets[hashIdx]->insert(key, data);
		}
		else
		{
			if (this->_buckets[hashIdx]->hasAvailableOverflow())
			{
				hashIdx = this->_buckets[hashIdx]->getOverflowIdx();
				this->insert(key, data, hashIdx);
			}
			else
			{
				int overflowHashIdx = this->getNextAvailableOverflowIdx();
				this->_buckets[hashIdx]->setOverflowIdx(overflowHashIdx);
				this->insert(key, data, overflowHashIdx);
			}
		}
	}

	template<class TKey, class TData>
	inline void Hashtable<TKey, TData>::search(std::ostream& outstr, TKey key, int hashIdx)
	{
		outstr << setfill(' ');

		if (this->_buckets[hashIdx]->hasMatch(key))
		{
			int slotIdx = this->_buckets[hashIdx]->getSlotNumberByKey(key);
			outstr << key;
			outstr << setw(7) << hashIdx + 1 << "/" << slotIdx + 1;
			outstr << setw(25) << this->_buckets[hashIdx]->getData(slotIdx) << endl;
		}
		else
		{
			if (this->_buckets[hashIdx]->hasAvailableOverflow())
			{
				search(outstr, key, this->_buckets[hashIdx]->getOverflowIdx());
			}
			else
			{
				outstr << key << setw(32) << "Record not found" << endl;
			}
		}
	}

	template<class TKey, class TData>
	inline void Hashtable<TKey, TData>::generateReportHeader(std::ostream& outstr, bool isStatReport, bool isBeforeRestore)
	{
		outstr << setfill(' ');
		outstr << setw(30) << "Hash Table" << endl;
		if (true == isStatReport)
		{
			outstr << setw(30) << "Stat Report" << endl;
		}
		else
		{
			outstr << setw(35) << "Verification Report" << endl;
			if (true == isBeforeRestore)
			{
				outstr << setw(35) << "Before Restoration" << endl;
			}
			else
			{
				outstr << setw(34) << "After Restoration" << endl;
			}
		}
	}
}

#endif