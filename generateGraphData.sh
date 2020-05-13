#! /bin/sh

#Mario Alex Crim

if [$# -lt 1]
then 
	echo "level not given"
	exit 1
fi

LEVEL=$1

#change directory to level
cd "$LEVEL"


#delete old graphs if regenerating data. so does not append.
rm "graph1data.csv"
rm "graph2data.csv"
rm "graph3data.csv"

#save graph 1 data
#x is the cacheSize
for x in 1024 2048 4096 8192 16384 32768 65536
do
  	DATA=$(./a.out -s $x -b 32 -a 4 | awk '/Cache\ Size:/{print $NF} /Miss\ Rate:/ {print $NF}')
	##get values and save them
  	CACHE_SIZE=$(echo $DATA | head -n1 | awk '{print $1;}')
  	MISS_RATE=$(echo $DATA | head -n1 | awk  '{print $NF}')
	echo "$CACHE_SIZE, $MISS_RATE" >> graph1data.csv
done

#save graph 2 data
#x is the blockSize
for x in 1 2 4 8 16 32 64
do
	DATA=$(./a.out -s 8192 -b $x -a 4 | awk '/Block\ Size/{print $NF} /Miss\ Rate/ {print $NF}')
	##get values and save them
  	BLOCK_SIZE=$(echo $DATA | head -n1 | awk '{print $1;}')
  	MISS_RATE=$(echo $DATA | head -n1 | awk  '{print $NF}')
	echo "$BLOCK_SIZE, $MISS_RATE" >> graph2data.csv
done

#save graph 3 data
#x is the associativity
for x in 1 2 4 8 16 32
do
	DATA=$(./a.out -s 8192 -b 32 -a $x | awk '/Associativity/{print $NF} /Miss\ Rate:/ {print $NF}')
	##get values and save them
  	ASSOC_SIZE=$(echo $DATA | head -n1 | awk '{print $1;}')
  	MISS_RATE=$(echo $DATA | head -n1 | awk  '{print $NF}') 
	echo "$ASSOC_SIZE, $MISS_RATE" >> graph3data.csv
done
	
	




