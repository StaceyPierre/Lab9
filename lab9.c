// Stacey Pierre
// COP3502
// Lab 9 
// April 12, 2024

#include <stdio.h>
#include <stdlib.h> // Include this for malloc and exit

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// HashType
struct HashType
{
    struct RecordType record; // Assuming each slot in the hash table can hold a record
};

// Compute the hash function
int hash(int x)
{
    // A simple hash function for demonstration purposes
    return x % 10; // Modulo 10 for simplicity
}

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	int i;

	for (i = 0; i < hashSz; ++i)
	{
		// if index is occupied with any records, print all
		if (pHashArray[i].record.id != 0)
		{
			printf("Index %d -> %d %c %d\n", i, pHashArray[i].record.id, pHashArray[i].record.name, pHashArray[i].record.order);
		}
	}
}

int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	
	// Hash implementation
	int hashTableSize = 10; // Size of the hash table
	struct HashType *hashTable = (struct HashType*)malloc(sizeof(struct HashType) * hashTableSize);
	if (hashTable == NULL)
	{
		printf("Cannot allocate memory\n");
		exit(-1);
	}

	// Initialize hash table slots
	for (int i = 0; i < hashTableSize; ++i)
	{
		hashTable[i].record.id = 0; // Assuming 0 indicates an empty slot
	}

	// Insert records into hash table
	for (int i = 0; i < recordSz; ++i)
	{
		int index = hash(pRecords[i].id); // Compute hash index
		hashTable[index].record = pRecords[i];
	}

	// Display records in hash table
	displayRecordsInHash(hashTable, hashTableSize);

	// Free allocated memory
	free(pRecords);
	free(hashTable);

	return 0;
}
