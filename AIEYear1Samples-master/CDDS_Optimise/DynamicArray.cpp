#include "DynamicArray.h"


template<typename T>
void DynamicArray<T>::Grow()
{
	m_allocatedElements++1;
}








template<typename T>
DynamicArray<T>::DynamicArray()
{
}

template<typename T>
DynamicArray<T>::DynamicArray(const DynamicArray& _other)
{
}

template<typename T>
DynamicArray<T>::~DynamicArray()
{
}









template<typename T>
inline void DynamicArray<T>::PushBack(T num)
{
	
}


template<typename T>
inline void DynamicArray<T>::PopBack()
{
}

template<typename T>
inline void DynamicArray<T>::Insert(T num, int index)
{
}

template<typename T>
inline void DynamicArray<T>::Remove(int index)
{
}

template<typename T>
inline void DynamicArray<T>::Resize(int size)
{
}

template<typename T>
inline void DynamicArray<T>::Clear()
{
}





template<typename T>
inline DynamicArray& DynamicArray<T>::operator=(const DynamicArray& other)
{
}

