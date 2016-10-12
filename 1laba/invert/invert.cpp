// invert.cpp: определяет точку входа для консольного приложения.

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

typedef double Matrix3x3[3][3];
typedef double Matrix2x2[2][2];


bool ArgumentsHasErrors(int arguments)
{
	if (arguments != 2)
	{
		return false;
	}
	return true;
}

bool FileHasErrors(ifstream &file)
{
	if (!file.is_open())
	{ 
		return false;
	}
	if (!file.good())
	{
		cout << "Error: reading file problem. Found some errors in the file! \n"
			<< "PLease, check file \n";
		return false;
	}
	return true;
}

void ReadMatrixFromFile(ifstream & inputFile, Matrix3x3 &matrix, int const& maxMatrixSize)
{
	for (int i = 0; i < maxMatrixSize; i++)
	{
		for (int j = 0; j < maxMatrixSize; j++)
		{
			inputFile >> matrix[i][j];
		}
	}
}

void WriteMatrixToOutput(Matrix3x3 &matrix, int const& maxMatrixSize)
{
	for (int i = 0; i < maxMatrixSize; i++)
	{
		for (int j = 0; j < maxMatrixSize; j++)
		{
			cout << matrix[i][j]; 
		}
		cout << endl;
	}
	
}

double GetDeterminantMatrix3x3(Matrix3x3 const& matrix)
{
	double determinant = matrix[0][0] * matrix[1][1] * matrix[2][2] + matrix[0][1] * matrix[1][2] * matrix[2][0]
		+ matrix[0][2] * matrix[1][0] * matrix[2][1] - matrix[0][2] * matrix[1][1] * matrix[2][0]
		- matrix[0][0] * matrix[1][2] * matrix[2][1] - matrix[0][1] * matrix[1][0] * matrix[2][2];
	return determinant;
}

double GetDeterminantMatrix2x2(Matrix2x2 const& matrix)
{
	double determinant = matrix[0][0] * matrix[1][1] - matrix[0][1] * matrix[1][0];
	return determinant;
}

double GetMinor(Matrix3x3 const& matrix, int row, int column, int const& maxMatrixSize)
{
	int minorMatrixCountRow = 0, minorMatrixCountColumn = 0;
	Matrix2x2 minorMatrix;
	for (int i = 0; i < maxMatrixSize; i++)
	{
		if (row == i)
		{
			continue;
		}
		for (int j = 0; j < maxMatrixSize; j++)
		{
			if (column == j)
			{
				continue;
			}
			minorMatrix[minorMatrixCountRow][minorMatrixCountColumn] = matrix[i][j];
			minorMatrixCountRow++;
		}
		minorMatrixCountRow = 0;
		minorMatrixCountColumn++;
	}

	return pow(-1, (row + column)) * GetDeterminantMatrix2x2(minorMatrix);
}


int main(int argc, char* argv[])
{
	int const MAX_MATRIX_SIZE = 3;
	setlocale(LC_ALL, "rus");
	if (!ArgumentsHasErrors(argc))
	{
		cout << "Invalid arguments count \n"
			<< "Usage: invert.exe <matrix file> \n";
		return 1;
	}

	ifstream file(argv[1]);
	if (!FileHasErrors(file))
	{
		cout << "Failed to open This file doesn`t exist)\n";
		return 1;
	}

	Matrix3x3 matrix;
	ReadMatrixFromFile(file, matrix, MAX_MATRIX_SIZE);
	WriteMatrixToOutput(matrix, MAX_MATRIX_SIZE);
	 
	double determinant = GetDeterminantMatrix3x3(matrix); 


	return 0;
}