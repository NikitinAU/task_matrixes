#include <iostream>
#include <fstream>
//____________________________TASK 6___________________________
//in matrix, find a row with the longest sequence of repeating number
//basically just an extension of the last task
template <typename T>
size_t maxConsecRepeats(const T* arr, const size_t size) //O(size)
{
	//simple counters
	size_t maxRepeats = 1,
		curRepeats = 1;
    for (size_t i = 1; i < size; ++i)
    {
        if (arr[i] == arr[i - 1])
            ++curRepeats;
        else
        {
            if (curRepeats > maxRepeats)
                maxRepeats = curRepeats;
            curRepeats = 1;
        }
    }
	//current repeats can be more then max if it's right in the end of array
    return (curRepeats > maxRepeats ? curRepeats : maxRepeats);
}
//find a row with the longest sequence of repeating number
// -1 = no repeating numbers
template<typename T>
int findLongestRepeatingSequence(T** matrix, size_t rows, size_t cols) //O(rows*cols)
{
    int max = 1,
		cur = 0,
		index = -1;
	for (size_t i = 0; i < rows; ++i)
	{
        cur = maxConsecRepeats<T>(matrix[i], cols);
        if (cur > max) {
            max = cur;
            index = i;
        }
	}
    return index;
}
template<typename T>
void printArray(T* arr, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
        std::cout << arr[i] << ' ';
	}
    std::cout << '\n';
}
template<typename T>
void printMatrix(T** matrix, size_t rows, size_t cols)
{
	for (size_t i = 0; i < rows; ++i)
	{
        printArray<T>(matrix[i], cols);
	}
}
template<typename T>
void printPointToRow(T** matrix, size_t rows, size_t cols, size_t pointTo)
{
	for (size_t i = 0; i < rows; ++i)
	{
		if (i == pointTo)
			std::cout << " -> ";
		else
			std::cout << "    ";
		printArray<T>(matrix[i], cols);
	}
}
void main()
{
	std::ifstream in("infile.txt");
	if (!in.is_open())
	{
		std::cerr << "File cannot be opened\n";
		return;
	}
	while (!in.eof()) {
		size_t rows = 0,
			   cols = 0;
		in >> rows;
		in >> cols;
		if (rows > 0 && cols > 0) {
			int** matrix = new int* [rows];
			for (int i = 0; i < rows; ++i) {
				matrix[i] = new int[cols];
				for (int j = 0; j < cols; ++j) {
					in >> matrix[i][j];
				}
			}
			printMatrix(matrix, rows, cols);
			int LRS = findLongestRepeatingSequence(matrix, rows, cols);
			if (LRS != -1) {
				std::cout << "row with the longest sequence of repeating number: " << LRS + 1 << '\n';
				printPointToRow(matrix, rows, cols, LRS);
			}
			else
				std::cout << "no repeating numbers in any row\n";
			std::cout << '\n';
			for (int i = 0; i < rows; ++i) {
				delete[] matrix[i];
			}
			delete[] matrix;
		}
	}
	in.close();
}