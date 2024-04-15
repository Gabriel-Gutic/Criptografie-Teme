#include "pch.h"
#include "Matrix.h"

#include "Laborator.h"


int Matrix::N = 0;
Matrix::Matrix(int rows, int cols)
    :m_Rows(rows), m_Cols(cols)
{
    m_Data = new int * [rows];
    for (int i = 0; i < rows; i++)
    {
        m_Data[i] = new int[cols];
        for (int j = 0; j < cols; j++)
        {
            m_Data[i][j] = 0;
        }
    }
}

Matrix::Matrix(const Matrix& other)
{
    m_Rows = other.m_Rows;
    m_Cols = other.m_Cols;

    m_Data = new int* [m_Rows];
    for (int i = 0; i < m_Rows; i++)
    {
        m_Data[i] = new int[m_Cols];
        for (int j = 0; j < m_Cols; j++)
        {
            m_Data[i][j] = other.m_Data[i][j];
        }
    }
}

Matrix& Matrix::operator=(const Matrix& other)
{
    if (this != &other)
    {
        m_Rows = other.m_Rows;
        m_Cols = other.m_Cols;

        m_Data = new int* [m_Rows];
        for (int i = 0; i < m_Rows; i++)
        {
            m_Data[i] = new int[m_Cols];
            for (int j = 0; j < m_Cols; j++)
            {
                m_Data[i][j] = other.m_Data[i][j];
            }
        }
    }
    return *this;
}

Matrix::~Matrix()
{
    for (int i = 0; i < m_Rows; i++)
    {
        delete[] m_Data[i];
    }
    delete[] m_Data;
}

int Matrix::Determinant() const
{
    if (m_Rows != m_Cols) 
    {
        throw std::exception("Matrix must be square to compute determinant");
    }

    int n = m_Rows;
    if (n == 1) 
    {
        return m_Data[0][0];
    }

    int det = 0;
    for (int j = 0; j < n; ++j) 
    {
        Matrix minor(n - 1, n - 1);
        for (int k = 1; k < n; ++k) 
        {
            for (int l = 0, m = 0; l < n; ++l) 
            {
                if (l != j) 
                {
                    minor[k - 1][m++] = m_Data[k][l];
                }
            }
        }
        det += m_Data[0][j] * (j % 2 == 0 ? 1 : -1) * minor.Determinant();
    }
    return modulo(det, N);
}

int* Matrix::operator[](int index)
{
    return m_Data[index];
}

const int* Matrix::operator[](int index) const
{
    return m_Data[index];
}

Matrix Matrix::operator-() const
{
    Matrix result(m_Rows, m_Cols);

    for (int i = 0; i < m_Rows; i++)
    {
        for (int j = 0; j < m_Cols; j++)
        {
            result[i][j] = modulo(-m_Data[i][j], N);
        }
    }

    return result;
}

Matrix operator+(const Matrix& A, const Matrix& B)
{
    if (A.m_Rows != B.m_Rows || A.m_Cols != B.m_Cols)
        throw std::exception("Invalid matrices dimension");

    Matrix result(A.m_Rows, A.m_Cols);

    for (int i = 0; i < A.m_Rows; i++)
    {
        for (int j = 0; j < A.m_Cols; j++)
        {
            result[i][j] = modulo(A[i][j] + B[i][j], Matrix::N);
        }
    }

    return result;
}

Matrix operator-(const Matrix& A, const Matrix& B)
{
    return A + (-B);
}

Matrix operator*(const Matrix& A, const Matrix& B)
{
    if (A.m_Cols != B.m_Rows)
        throw std::exception("Invalid matrices dimension");

    Matrix result(A.m_Rows, B.m_Cols);

    for (int i = 0; i < A.m_Rows; i++)
    {
        for (int j = 0; j < B.m_Cols; j++)
        {
            for (int k = 0; k < A.m_Cols; ++k) 
            {
                result[i][j] += modulo(A[i][k] * B[k][j], Matrix::N);
            }
            result[i][j] = modulo(result[i][j], Matrix::N);
        }
    }

    return result;
}

std::ostream& operator<<(std::ostream& os, const Matrix& M)
{
    for (int i = 0; i < M.m_Rows; i++)
    {
        for (int j = 0; j < M.m_Cols; j++)
        {
            os << M.m_Data[i][j] << " ";
        }
        os << "\n";
    }
    return os;
}
