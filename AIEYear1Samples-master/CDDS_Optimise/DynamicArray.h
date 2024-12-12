#pragma once

template <typename T>
class DynamicArray
{
private:
	int m_allocatedElements;
	int m_usedElements;
	T* m_data;

private:
	void Grow();

public:
	DynamicArray();
	DynamicArray(const DynamicArray& _other);
	~DynamicArray();


	void PushBack(T num);
	void PopBack();

	void Insert(T num, int index);
	void Remove(int index);

	void Resize(int size);

	void Clear();

public:
	DynamicArray& operator =(const DynamicArray& _other);
};

