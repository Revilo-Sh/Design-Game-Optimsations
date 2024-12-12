#pragma once

template <typename T>
class DynamicArray
{
private:
	int m_allocatedElements;
	int m_usedElements;
	T* m_data;

private:
	void Grow(); // used to increase the allocted elements

public:
	DynamicArray(); 
	DynamicArray(const DynamicArray& _other);
	~DynamicArray();


	void PushBack(T num); // Addeds to the end
	void PopBack(); // Removes from end

	void Insert(T num, int index); // adds element into a specified index in the arry 
	void Remove(int index); // removes vaule a index

	void Resize(int size); // resoze array to be a size of passed values

	void Clear(); // clear the whole array

public:
	DynamicArray& operator =(const DynamicArray& other);
};




