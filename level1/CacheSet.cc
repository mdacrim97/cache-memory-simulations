#include "CacheSet.h"

using namespace std;

//Mario Alex Crim

/************************************************************************************
The CacheSet class is meant to simulate one set of CacheSet entries (in an N-way CacheSet)

*************************************************************************************/

//	constructor
CacheSet::CacheSet(int lineSize, int Nway){
    line_size = lineSize;

    associativity_factor = Nway;
    // create a line for each entry in the set
    for (int i=0; i < Nway; i++)
        cacheLine.push_back(CacheEntry(line_size));

    hitCount  = 0;
    missCount = 0;
    memoryReadCount  = 0;
}

bool CacheSet::hit(int tag, int& location){
    bool haveHit = false;

    for (int lineNumber=0; lineNumber < associativity_factor; lineNumber ++)
        if (cacheLine[lineNumber].hit(tag)){
			location = lineNumber;
            return true;
		}

    return false;
}

bool CacheSet::readByte(int tag, int offset){

	int location; //where the hit is located.
	if(hit(tag, location)){
		for(int i=0; i<cacheLine.size(); i++)
			if(i == location)
				cacheLine[i].setLRU();
			else
				cacheLine[i].incrementLRU();
		return true;
	}
	else{
		loadLine(tag, offset);
		return false;
	}
}

void CacheSet::loadLine(int inputTag, int offset){

	int lastUsed = cacheLine[0].getLRU();
    int location = 0; //location for which Entry to replace
    bool replaced = false;

    // find which line to write
    for(int i = 1;i<cacheLine.size();i++)
        if(lastUsed < cacheLine[i].getLRU())
        {
            lastUsed = cacheLine[i].getLRU();
            location = i;
        }

    // confirm replacement.
    if(cacheLine[location].readByte(offset)){
        cacheLine[location].loadLine(inputTag);
        replaced = true;
    }

    for(int i = 0;i<cacheLine.size();i++)
        if(i == location && replaced)
            cacheLine[location].setLRU();
        else
            cacheLine[i].incrementLRU();
}

int CacheSet::getHitCount(){ 
	return hitCount;
}

int CacheSet::getMissCount(){ 
	return missCount;
}

int CacheSet::getMemoryReadCount(){ 
	return memoryReadCount;
}

void CacheSet::incrementHit(){
	hitCount++;
}

void CacheSet::incrementMiss(){
	missCount++;
}

void CacheSet::incrementRead(){
	memoryReadCount++;
}
