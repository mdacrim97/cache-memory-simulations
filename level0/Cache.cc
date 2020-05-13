#include "Cache.h"
using namespace std;

//Mario Alex Crim

//	constructor
Cache::Cache(int setCount, int associativity, int lineSize)
{
    for (int i=0; i<setCount; i++)
    {
        cacheSets.push_back(CacheSet(lineSize, associativity));
    }

    number_of_sets = setCount;
    associativity_factor = associativity;
    line_size = lineSize;

    bits_in_set = power_of_two(setCount);		// computed, assumes the set count
    											//	is a power of 2
	bits_in_offset = power_of_two(lineSize);	// computed, assumes lineSize
												 //	is a power of 2
}

int Cache::power_of_two(int value)
{
    int result = 0;
    const int limit  = 100;

    while (value > 1 && result < limit)
    {
        value = value >> 1;
        result ++;
    }
    if (value == 1)
        return result;
    else
        return -result;
}

void Cache::splitAddress(int address, int &tag, int &setNumber, int &offset)
{
    int offset_mask,
        set_mask;

    offset_mask = (1 << bits_in_offset) - 1;
    offset = address & offset_mask;

    address = address >> bits_in_offset;
    set_mask = (1 << bits_in_set) - 1;
    setNumber = address & set_mask;

    tag = address >> bits_in_set;
}

bool Cache::readByte(int address){

    int tag, 
		setNumber, 
		offset;

    splitAddress(address, tag, setNumber, offset);

    if (cacheSets[setNumber].readByte(tag, offset))
        cacheSets[setNumber].incrementHit();
    else
        cacheSets[setNumber].incrementMiss();

	cacheSets[setNumber].incrementRead();

    return true;
}

int Cache::getHitCount()
{
    int totalHits = 0;
    for(int i = 0;i<cacheSets.size();i++)
        totalHits += cacheSets[i].getHitCount();

    return totalHits;
}

int Cache::getMissCount()
{
    int totalMisses =0;
    for(int i = 0;i<cacheSets.size();i++)
        totalMisses += cacheSets[i].getMissCount();

    return totalMisses;
}

int Cache::getMemoryReadCount()
{
    int totalReads = 0;
    for(int i = 0;i<cacheSets.size();i++)
        totalReads += cacheSets[i].getMemoryReadCount();

    return totalReads;
}

