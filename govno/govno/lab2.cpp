#include "functions.h"
// Test for Questions 1 to 8

void findArray();
void findSecondLargest();
void copyArray();
void insertElement();
void deleteElement();
void countDuplicates();
void countElements();

int main()
{
	// leap year
	std::cout << "Leapyear" << std::endl;
	if (!isLeapYear(1700))
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}
	if (isLeapYear(1600))
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}
	if (isLeapYear(2016))
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}

	// palindrome / reversed
	std::cout << "NumberReversed" << std::endl;
	if (Reversed(123) == 321)
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}

	if (Reversed(1) == 1)
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}
	if (Reversed(1234) != 321)
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}


	std::cout << "Palindrome" << std::endl;
	if (isAPalindrome(1))
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}
	if (isAPalindrome(121))
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}
	if (!isAPalindrome(1213))
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}

	// prime 
	std::cout << "Prime Number" << std::endl;
	if (isAPrimeNumber(3))
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}
	if (isAPrimeNumber(2147483647))
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}
	if (!isAPrimeNumber(4))
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}

	// binary to decimal
	std::cout << "Binary to Decimal" << std::endl;
	if (convertBinarytoDecimal(110) == 6)
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}
	if (convertBinarytoDecimal(111) == 7)
	{
		std::cout << "yes" << std::endl;
	}
	else {
		std::cout << "no" << std::endl;
	}

	// char to int
	std::cout << "\n5 chars to int" << std::endl;
	std::cout << "Enter a characters: \n";
	int convertedInt = input5CharsConvertToInt();
	std::cout << convertedInt << std::endl;


	nestedLoopsTask6();
	nestedLoopsTask7();

	findArray();
	findSecondLargest();
	copyArray();
	insertElement();
	deleteElement();
	countElements();
	countDuplicates();


	std::cout << "\nTriangles" << std::endl;
	drawRightAngledTriangle();
	drawIsocelesTriangle();

}

void findArray()
{
	const int SIZE = 5;
	int toFind = 3;
	int array[SIZE] = { 1,2,3,4,5 };

	int displayFoundIndex = 0;

	displayFoundIndex = find(SIZE, array, toFind);

	std::cout << "Found index: " << displayFoundIndex << std::endl;
}

void findSecondLargest()
{
	const int SIZE = 5;
	int array[SIZE] = { 7,5,6,5,2 };
	int secondLargest = 0;

	secondLargest = find2ndLargest(SIZE, array);
	std::cout << "Found largest number: " << secondLargest << std::endl;

}


void copyArray()
{

	const int SIZE = 5;

	int array1[SIZE] = { 1,233,3,4,5 };
	int array2[SIZE] = { 0 };

	copyArraytoArray(SIZE, array1, array2);
}

void insertElement()
{
	const int SIZE = 6;
	int count = 0;
	int array[SIZE] = { 1,2,3,4,5 };
	int elementToInsert = 10;
	int insertIndex = 2;

	for (int i = 0; i < SIZE; ++i)
	{
		if (array[i] == 0) // treat 0 as "unused"
			break;
		++count;
	}

	std::cout << "\nCount before insert: " << count << std::endl;
	if (insertElement(SIZE, count, array, elementToInsert, insertIndex))
	{
		std::cout << "\nInserted. New count: " << count << std::endl;
		for (int i = 0; i < count; ++i) std::cout << array[i] << ' ';
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Insert failed." << std::endl;
	}

}

void deleteElement()
{
	const int SIZE = 6; // must be non-const so it can bind to int& in the helper
	int array[SIZE] = { 1,2,3,4,5, }; 
	int count = 0;
	int deleteIndex = 2;

	// compute current count by stopping at the first sentinel (0)
	for (int i = 0; i < SIZE; ++i)
	{
		if (array[i] == 0) break;
		++count;
	}

	std::cout << "\nCount before delete: " << count << std::endl;
	if (deleteElement(SIZE, count, array, deleteIndex))
	{
		std::cout << "Deleted. New count: " << count << std::endl;
		for (int i = 0; i < count; ++i) std::cout << array[i] << ' ';
		std::cout << std::endl;
	}
	else
	{
		std::cout << "Delete failed." << std::endl;
	}


}

void countElements()
{
	const int SIZE = 5;
	int array[SIZE] = { 1,2,3,4,5 };
	int valueToCount = 3;
	int frequency = frequencyCount(SIZE, array, valueToCount);
	std::cout << "Frequency of " << valueToCount << ": " << frequency << std::endl;
}

void countDuplicates()
{
	
	const int SIZE = 5;
	int array[SIZE] = { 1,2,3,3,5 };
	int duplicates = countDuplicates(SIZE, array);
	std::cout << "\nDuplicate occurrences: " << duplicates << std::endl;
}