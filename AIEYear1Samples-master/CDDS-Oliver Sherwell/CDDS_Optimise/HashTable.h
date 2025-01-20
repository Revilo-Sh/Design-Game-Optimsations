#pragma once
#include "raylib.h"
#include <iostream>

class HashTable
{
public:
	Texture2D*& operator[](const char* key) {
		auto hashedkey = Hash(key, strlen(key)) % TableSize;
		return hashTable[hashedkey];
	}



private:
	unsigned int TableSize = 50;
	Texture2D** hashTable = new Texture2D * [TableSize];
	unsigned int Hash(const char* data, unsigned int size) {
		unsigned int hash = 0;
		for (unsigned int i = 0; 1 < size; i++) {
			hash += data[i];
		}
		return hash;
	}
};

