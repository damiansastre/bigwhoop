#pragma once

/*
TArray
Array implementation for DungeonCrawler.
Allows to create dynamically sized arrays based on a template typename.
*/
template <typename T>
class TArray
{
public:
	TArray()
	{
	}
	// Creates an array based on length.
	TArray(int maxLength)
	{
		items = new T[maxLength];
		length = maxLength - 1;
	}
	// Attempts to add an element to the array.
	// if the array can't accomodate the new item
	// it doubles the storage space.
	void addElement(T element)
	{
		if (currentIndex + 1 == length)
		{
			T* newArray = new T[length * 2];
			for (int index = 0; index < length; ++index)
			{
				newArray[index] = items[index];
			}
			delete[] items;
			items = newArray;
			length = length * 2;
		}
		items[currentIndex] = element;
		currentIndex += 1;

	}
	// Get an element by index.
	T getElement(int element)
	{
		if (isValidIndex(element))
		{
			return items[element];
		}
		return nullptr;
	}
	// Remove an element BY INDEX from the list and pad the rest to the left.
	// Warning: This is an O(~n) operation, should be re implemented for O(1)
	void removeElement(int element)
	{
		for (int index = element; index <= currentIndex; ++index)
		{
			items[index] = items[index + 1];
		}
		currentIndex -= 1;
	}
	// Remove an element BY OBJECT from the list and pad the rest to the left.
	// Warning: This is an O(~n) operation, should be re implemented for O(1)
	void removeElement(T element)
	{
		int index = getElementIndex(element);
		for (int i = index; i <= currentIndex; ++i)
		{
			items[i] = items[i + 1];
		}
		currentIndex -= 1;
	}
	// Attempts to get the index of an element.
	int getElementIndex(T element) 
	{
		for (int index = 0; index < currentIndex; ++index)
		{
			if (items[index] == element)
			{
				return index;
			}
		}
		return -1;
	}
	// Checks whether an index is valid for the current length of the TArray.
	bool isValidIndex(int index)
	{
		return length > index;
	}
	// Checks if TArray contains the parameter element.
	bool contains(T& element)
	{
		for (int i = 0; i < currentIndex; ++i)
		{
			if (items[i] == element)
			{
				return true;
			}
		}
		return false;

	}
	// Returns the currentIndex.
	int num()
	{
		return currentIndex;
	}

protected:
	int currentIndex = 0;
	int length = 20;
	T* items;
};