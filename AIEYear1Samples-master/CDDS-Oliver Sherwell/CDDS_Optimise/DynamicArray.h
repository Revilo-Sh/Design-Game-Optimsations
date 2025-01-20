#pragma once
#include "Critter.h"
#include <iostream>

class DynamicArray
{
private:
	int m_allocatedElmemnts;
	int m_usedElements;
	Critter* critterArray = nullptr;




private:
	void Grow() {
		m_allocatedElmemnts = m_allocatedElmemnts * 2; // Added More Allocted Slots
		Critter* TempArray = new Critter[m_allocatedElmemnts]; // Make a Temp Array we Can put data into

		for (int i = 0; i < m_allocatedElmemnts; i++) // Increase Throught the Array 
		{
			TempArray[i] = critterArray[i]; // Moves the Data from CritterArray Over to the Temp
		}
		delete[] critterArray; // Deletes all the data
		critterArray = TempArray; // puts back in the data with also the new size of the array
		//Doing this will increase the array by a factor of 2
	}

public:
	DynamicArray() {
		m_allocatedElmemnts = 200;
		m_usedElements = 0;
		critterArray = new Critter[m_allocatedElmemnts];
	};

	DynamicArray(int size) {
		this->m_allocatedElmemnts = m_usedElements;
		m_usedElements = 0;
		critterArray = new Critter[m_allocatedElmemnts];
	};


	~DynamicArray() {
		
	};

	void PushBack(Critter InValue) {
		int TempIndex;
		if (m_usedElements == m_allocatedElmemnts) { // Checks to see if we have used up all of our elements
			Grow(); // Increase the allcatedElment Size
		}
		
		for (int i = m_allocatedElmemnts; i > m_usedElements - 1; i--) {
			TempIndex = i;
		}
		critterArray[TempIndex] = InValue;
		m_usedElements++;

	};

	void PopBack() {
		Critter* TempArray = new Critter[m_allocatedElmemnts];
		for (int i = 0; i < m_usedElements - 1; i++) {
			TempArray[i] = critterArray[i];
		}
		delete[] critterArray;
		critterArray = TempArray;
	}

	


	void Insert(Critter inValue, int index) {
		if (index > m_usedElements) {
			std::cout << "Cant Set Out Of Array Bounds!" << std::endl;
		}

		if (m_usedElements == m_allocatedElmemnts) { 
			Grow();
		}

		for (int i = m_usedElements; i > index; i--){
			critterArray[i + 1] = critterArray[i];
		}
		critterArray[index] = inValue;
		m_usedElements++;
	}




	void Remove(int index) {
		for (int i = 0; i < m_usedElements; i++) {
			critterArray[i] = critterArray[i + 1];
		}
		m_usedElements--;

		if (m_usedElements == (m_allocatedElmemnts / 3)) { // The Rest is just the Grow But Backwards

			m_allocatedElmemnts = m_allocatedElmemnts / 2;
			Critter* TempArray = new Critter[m_allocatedElmemnts];

			for (int i = 0; i < m_allocatedElmemnts; i++) {
				TempArray[i] = critterArray[i]; 
			}
			delete[] critterArray; 
			critterArray = TempArray; 
		}
	}

	void Clear() {
		delete[] critterArray;
		m_usedElements = 0;
		Critter* critterArray = new Critter[m_usedElements];
	};

public:
	DynamicArray& operator =(const DynamicArray& _others);
	// LOST THIS

};




