#include <ostream>
#include <iostream>
#include <cstdlib>
#include "CacheEntry.h" 

using namespace std;

//Mario Alex Crim

CacheEntry::CacheEntry(int newLineSize){
    if (newLineSize < 1 || newLineSize > CACHE_MAX_BLOCK_SIZE)
		{
		cerr << "ERROR: in CacheEntry, newLineSize (" << newLineSize 
			 << ") is out of acceptable range" << endl;
		exit (4);
	}
    lineSize = newLineSize;
    valid = false;
    dirty = false;
    tag = 0;
}

bool CacheEntry::hit(int testTag) const {
    return (valid && tag == testTag);
}

bool  CacheEntry::readByte (int offset) const{

    if (offset >= lineSize)
	{
		cerr << "ERROR: in CacheEntry::readByte; attempt to read past "
			 << "end of cache line\n\toffset is: "
		 	 << offset << "  lineSize is " << lineSize << endl;
		return false;
	}
    return true;
}

// writeByte()	writes a Byte value to this cache entry
//		the offset of data read must be <= cache line size
bool CacheEntry::writeByte (int offset)
{
    if (offset >= lineSize)
	{
		cerr << "ERROR: in CacheEntry::writeByte; attempt to write past end of cache line"
			 << "\n\toffset is: " << offset << endl;
		return false;
	}
    dirty = true;    
    return true;
}

// loadLine()	loads a line of cache (actually sets the tag and the valid bit)
void CacheEntry::loadLine(int inputTag){
	tag = inputTag;
	valid = true;
	dirty = false;
}

bool CacheEntry::isDirty() const{
	return dirty;
}


// setDirty()	sets the dirty flag to true
void CacheEntry::setDirty(){
	dirty = true;
}

// resetDirty()	resets the dirty flag to false
void CacheEntry::resetDirty(){
	dirty = false;
}

std::ostream& operator << (std::ostream& outstream, const CacheEntry& value) 
{
 
   outstream  << "CacheEntry:: linesize:\t" << value.lineSize 
		<< "\n\tValid bit:\t" << value.valid 
		<< "\n\ttag:\t\t" << value.tag 
		<< "\n\tDirty bit:\t" << value.dirty
		<< endl;
   return outstream;
}

int CacheEntry::getLRU() const{
	return lruCount;
}

void CacheEntry::incrementLRU(){
	lruCount++;
}

int CacheEntry::setLRU(){
	lruCount = 0;
}

