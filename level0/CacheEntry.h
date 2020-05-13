// header file for cache Entry for CSCI 5814 Spring 2020

#ifndef cacheEntry_h
#define cacheEntry_h
#include <ostream>
#include <iostream>

using namespace std;

#define CACHE_MAX_BLOCK_SIZE 256

//Mario Alex Crim

class CacheEntry
{
    private:
		int lineSize;	// the number of bytes in the cache data block
		int tag;		// the tag for matching with the set/block number from the address
		bool valid;		// is the entry used??
		bool dirty;		// for Write, is the block dirty and needs to be written before replaced.

    public:
		CacheEntry(int lineSize=32);		// constructor with default linesize of 32


		//  hit()   returns true if a cache hit is made on the given tag
		bool hit(int tag) const;


		// readByte()	simulates reading a Byte value from this cache entry
		//		the offset of  the data read must be <= cache line size
		bool readByte(int offset) const;


		// writeByte()	writes a Byte value to this cache entry
		//		the offset of data read must be <= cache line size
		bool writeByte (int offset);


		// isDirty()	returns the value of the dirty flag
		bool isDirty() const;

		// setDirty()	sets the dirty flag to true
		void setDirty();

		// resetDirty()	resets the dirty flag to false
		void resetDirty();


		// loadLine()	loads a line of cache (actually sets the tag and the valid bit)
		void loadLine(int inputTag);


		//  print function for the CacheEntry
	 	friend  std::ostream& operator<< (std::ostream&, const CacheEntry&);

};

#endif
