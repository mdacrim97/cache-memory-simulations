#include "CacheSet.h"

using namespace std;

//Mario Alex Crim

/************************************************************************************
The CacheSet class is meant to simulate one set of CacheSet entries (in an N-way CacheSet)

*************************************************************************************/

//	constructor
CacheSet::CacheSet(int lineSize, int Nway) {
    line_size = lineSize;

    associativity_factor = Nway;
    // create a line for each entry in the set
    for (int i=0; i < Nway; i++)
        cacheLine.push_back(CacheEntry(line_size));

    hitCount  = 0;
    missCount = 0;
    memoryReadCount  = 0;
}

bool CacheSet::hit(int tag){
    bool haveHit = false;

    for (int lineNumber=0; lineNumber < associativity_factor; lineNumber ++)
        if (cacheLine[lineNumber].hit(tag))
            return true;

    return false;
}

bool CacheSet::readByte(int tag, int offset){
    if(hit(tag))
        return true;
    else if(cacheLine[0].readByte(offset))
        loadLine(tag);
    
    return false;
}

void CacheSet::loadLine(int inputTag){
    cacheLine[0].loadLine(inputTag);
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


