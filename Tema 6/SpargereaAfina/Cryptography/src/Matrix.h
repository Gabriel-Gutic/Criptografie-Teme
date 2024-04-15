#pragma once


class Matrix
{
public:
	static int N;
public:
	Matrix(int rows = 2, int cols = 2);
	Matrix(const Matrix& other);
	Matrix& operator=(const Matrix& other);
	~Matrix();

	int Determinant() const;

	int* operator[](int index);
	const int* operator[](int index) const;

	Matrix operator-() const;
	friend Matrix operator+(const Matrix& A, const Matrix& B);
	friend Matrix operator-(const Matrix& A, const Matrix& B);
	friend Matrix operator*(const Matrix& A, const Matrix& B);

	friend std::ostream& operator<<(std::ostream& os, const Matrix& M);
private:
	int** m_Data;
	int m_Rows;
	int m_Cols;
};