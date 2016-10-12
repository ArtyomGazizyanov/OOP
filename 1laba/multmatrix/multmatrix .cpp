// multimatrix.cpp: определяет точку входа для консольного приложения.

#include <fstream>
#include <string>
#include <iostream>

using namespace std;

static const size_t MATRIX_SIZE = 3u;
typedef double Matrix3x3[3][3]; 

bool IsFileEmpty(ifstream& file)
{
	return file.peek() == ifstream::traits_type::eof();
}

bool IsInvalidArgumentsCount(int arguments)
{
	return (arguments != 3);
}

bool FileHasErrors(ifstream &file)
{
	return (file.is_open());
}

void ReadMatrixFromFile(ifstream & inputFile, Matrix3x3 &matrix)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			inputFile >> matrix[i][j];
		}
	}
}

void WriteMatrixToOutput(Matrix3x3 const& matrix)
{
	std::cout.precision(3);
	std::cout.setf(std::ios::fixed);

	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			cout << matrix[i][j];
			cout << " ";
		}
		cout << endl;
	} 
}

void MultiplyMatrix(Matrix3x3 const& matrix1,Matrix3x3 const& matrix2, Matrix3x3 & resultMatrix)
{
	for (int i = 0; i < MATRIX_SIZE; i++)
	{
		for (int j = 0; j < MATRIX_SIZE; j++)
		{
			resultMatrix[i][j] = 0;
			for (int k = 0; k < MATRIX_SIZE; k++)
			{
				resultMatrix[i][j] = resultMatrix[i][j] + (matrix1[i][k] * matrix2[k][j]);
			}  
		}
	} 
}

int main(int argc, char* argv[])
{
	int const MAX_MATRIX_SIZE = 3; 

	if (!IsInvalidArgumentsCount(argc))
	{
		cout << "Invalid arguments count \n"
			<< "Usage: invert.exe <matrix file1> <matrix file2> \n";
		return 1;
	}

	ifstream file1(argv[1]);
	if (!FileHasErrors(file1))
	{
		cout << "Failed to open " << argv[1] << "  file doesn`t exist)\n";
		return 1;
	}

	ifstream file2(argv[2]);
	if (!FileHasErrors(file2))
	{
		cout << "Failed to open " << argv[2] << "  file doesn`t exist)\n";
		return 1;
	}

	Matrix3x3 matrix1;
	Matrix3x3 matrix2;
	Matrix3x3 resultMatrix; 


	if (IsFileEmpty(file1) && IsFileEmpty(file2))
	{
		cout << "File(s) is(are) empty!";
	
	}
	else
	{
		ReadMatrixFromFile(file1, matrix1);
		ReadMatrixFromFile(file2, matrix2);

		MultiplyMatrix(matrix1, matrix2, resultMatrix);

		WriteMatrixToOutput(resultMatrix);
	}

	return 0;
}