#pragma once
class HashTable 
{
public:
	HashTable(unsigned int size); // Thye Contrustor For the Has Table

public:

	unsigned int Add(char* Texture); // Adding Data To the Hast Table
	const char* Retrieve(unsigned int key); // Getting Back The Data From the Hash Table


private:
	unsigned int Hash(char* key); //Putting Data Int Centrendt hash zones

	unsigned int M_size; // The Size Of the HashTable Size
	const char* m_data; // The Data That iS going into the Hash Table
};

