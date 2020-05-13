#include <iostream>
#include <fstream>
#include <math.h>
#include <string.h>
#include "Cache.h"

using namespace std;

//Mario Alex Crim

int main(int argc, char** argv)
{
	int cacheSize,
		blockSize,
		associativity;

	//Get variables from command line
	if(argc != 7){
		if( argc<7)
			cerr << "Not all parameters provided." << endl;
		else
			cerr<< "To many Parameters provided." << endl;
		return -1;
	}

	char* end;
	if(strcmp(argv[1], "-s") ==0)
		cacheSize = strtol(argv[2], &end, 0);
	else{
		cerr << "parameters out of order." << endl;
		return -1;
	}

	if(strcmp(argv[3], "-b") ==0)
		blockSize = strtol(argv[4], &end, 0);
	else{
		cerr << "parameters out of order." << endl;
		return -1;
	}
	
	if(strcmp(argv[5], "-a")==0)
		associativity = strtol(argv[6], &end, 0);
	else{
		cerr << "parameters out of order." << endl;
		return -1;
	}

	/////////////////////////////////////////////////

	int address,
		sets;
	char read;

	ifstream infile("addresses.dat", ios::in);
	if(!infile){
		cerr<< "Can't open File...Cancelling" << endl;
		return 2;
	}
	
	sets = cacheSize/(blockSize*associativity);
	Cache cache = Cache(sets, associativity, blockSize);

	while(infile >> read >> address){
		if(read == 'r')
			cache.readByte(address);
	}

    //print summary
	double missRate =double(cache.getMissCount())/double(cache.getMemoryReadCount());
    cout << "Cache Size: " << cacheSize <<  endl
    	 << "Block Size: " << blockSize << endl
    	 << "Associativity: " << associativity << endl
    	 << "Total Loads: " << cache.getMemoryReadCount() << endl
    	 << "Cache Hits: " << cache.getHitCount() << endl
    	 << "Cache Misses: " << cache.getMissCount() << endl
    	 << "Miss Rate: " << missRate << endl;

	infile.close();
    return 0;
}


