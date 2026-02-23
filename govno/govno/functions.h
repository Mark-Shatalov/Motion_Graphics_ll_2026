#pragma once
#include <iostream>

bool isLeapYear(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 == 0)
		{
			if (year % 400 == 0)
			{
				return true;
			}
			else
			{
				return false;
			}
		}
		else
		{
			return true;    
		}
	}
	else
	{
		return false;
	}
}



int Reversed(int testNumber)
{
	int reversed = 0;

	while (testNumber != 0)
	{
		int digit = testNumber % 10;     // Get last digit
		reversed = reversed * 10 + digit; // Add digit to reversed number
		testNumber /= 10;                // Remove last digit
	}

	return reversed;
}
bool isAPalindrome(int testNumber)
{

	if (testNumber < 0)
	{
		return false;
	}

	return testNumber == Reversed(testNumber);
}


bool isAPrimeNumber(int numbertoTest)
{
	if (numbertoTest <= 1)
		return false;

	if (numbertoTest == 2)
		return true;

	if (numbertoTest % 2 == 0)
		return false;

	// Check only odd numbers up to sqrt(number)
	for (long i = 3; i * i <= numbertoTest; i += 2)
	{
		if (numbertoTest % i == 0)
			return false;
	}

	return true;
}

int convertBinarytoDecimal(int binaryNumber)
{
	int decimal = 0;
	int base = 1;  // Represents 2^0, 2^1, 2^2, ...

	while (binaryNumber > 0)
	{
		int lastDigit = binaryNumber % 10;  // Get last binary digit

		decimal += lastDigit * base;        // Add to decimal result

		base *= 2;                          // Move to next power of 2
		binaryNumber /= 10;                 // Remove last digit
	}
	//std::cout << "Decimal: " << decimal << std::endl;
	return decimal;
}

int input5CharsConvertToInt()
{
	int returnInt = 0;
	char inputChar;
	for (int i = 0; i < 5; i++)
	{
		std::cin >> inputChar;
		//check if its a digit.
		//do something

		if (inputChar < '0' || inputChar > '9')
		{
			return 0;
		}
		returnInt = returnInt * 10 + (inputChar - '0');
	}
	return returnInt;
}



void nestedLoopsTask6()
{
	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < i; j++)
		{
			std::cout << "A ";
		}
		std::cout << std::endl;
	}
}

void nestedLoopsTask7()
{
	std::cout << std::endl;
	for (int i = 0; i < 7; i++)   // 7 total rows
	{
		int count;

		if (i < 4)
		{
			count = i + 1;
		}
		// Increasing part
		else
		{
			count = 7 - i;       // Decreasing part
		}

		for (int j = 0; j < count; j++)
		{
			std::cout << "A ";
		}

		std::cout << std::endl;
	}
}

int find(int size, int arr[], int toFind)
{
	/*bool found = false;
	int foundIndex = 0;*/
	for (int i = 0; i < size; i++)
	{
		if ( arr[i] == toFind)
		{
			/*found = true;
			foundIndex = i;
			break;*/
			return i;
		}
	}
	return -1;
}


int find2ndLargest(int size, int arr[])
{
	int largest = -1;
	int secondLargest = -1;

	for (int i = 0; i < size; i++)
	{
		if (arr[i] > largest)
		{
			secondLargest = largest;
			largest = arr[i];
		}
		else if (arr[i] < largest && arr[i] > secondLargest)
		{
			secondLargest = arr[i];
		}
	}

	return secondLargest; // returns -1 if no second largest exists
}



void copyArraytoArray(int size, int arr1[], int arr2[])
{
	for (int i = 0; i < size; i++)
	{
		arr2[i] = arr1[i];
	}

	// display 
	for (int i = 0; i < size; i++)
	{
		std::cout << i + 1 << " element: " << arr2[i] << "\n";
	}
}


bool insertElement(const int size, int& count, int arr[], int elementToInsert, int insertIndex)
{
	if (insertIndex < 0 || insertIndex > count)
	{
		return false;
	}

	if (count >= size)
	{
		return false;
	}
	
	for (int i = count; i > insertIndex; i--)
	{
		arr[i] = arr[i - 1];
	}

	arr[insertIndex] = elementToInsert;
	++count;
	return true;

}


bool deleteElement(const int size, int& count, int arr[], int deleteIndex)
{
	if (count <= 0) return false;
	if (deleteIndex < 0 || deleteIndex >= count) return false;

	for (int i = deleteIndex; i < count - 1; ++i)
	{
		arr[i] = arr[i + 1];
	}

	arr[count - 1] = 0;
	--count;
	return true;
}



int frequencyCount(int size, int arr[], int value)
{
	if (size <= 0 || arr == nullptr) return 0;

	int count = 0;
	for (int i = 0; i < size; ++i)
	{
		if (arr[i] == value)
			++count;
	}
	return count;
}


int countDuplicates(int size, int arr[])
{
	if (size <= 0 || arr == nullptr) return 0;

	int duplicates = 0;
	for (int i = 0; i < size; ++i)
	{
		// If this value appeared earlier, count this occurrence as a duplicate.
		bool seenBefore = false;
		for (int j = 0; j < i; ++j)
		{
			if (arr[j] == arr[i])
			{
				seenBefore = true;
				break;
			}
		}
		if (seenBefore) ++duplicates;
	}
	return duplicates;
}

void drawRightAngledTriangle()
{

}
void drawIsocelesTriangle()
{

}
void drawIsocelesTriangle2()
{

}







void reverse(int size, int arr[])
{
	return;
}
int rotateLeft(int size, int arr[])
{
	return -1;
}
bool twoMovies(int flightLength, int movieLengths[], int size)
{
	return false;
}
int wordCounter(int size, char characters[])
{
	return 0;
}