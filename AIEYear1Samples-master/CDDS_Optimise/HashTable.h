#pragma once

template<typename T>

class HashTable
{
public:
	HashTable(unsigned int size) : m_size(size), m_data(new T[size]) {}

	~HashTable() { delete[] m_data; }
	
	T& operator [] (const std::string& key) {
		auto hashedKey = hash(key) % m_size;
		return m_data[hashedKey];
	}

	const T& opperator[](const std::string& key) const {
		auto HashedKey = hash(key) % m_size;
		return m_data[HashedKey];
	}

private:
	unsigned int hashFunction(const std::string& key);
	T* m_data;
	unsigned int m_size;
};

