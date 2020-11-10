//#############################
//  Homework B by Kevin Suh   #
//#############################

#ifndef MATRIX_CPP
#define MATRIX_CPP

// Matrix Class
#include "Matrix.h"
#include <stdexcept>


//Default constructor
template<typename T>
Matrix<T>::Matrix()
:m_width(1), m_height(1)
{
    m_matrix.resize(m_width);
    m_matrix[0].resize(m_height);
}



//Parameterized Constructor
template<typename T>
Matrix<T>::Matrix(unsigned int width, unsigned int height)
: m_width(width), m_height(height)
{
    m_matrix.resize(m_width);
    for(unsigned int i = 0; i < m_width; ++i)
    {
        m_matrix[i].resize(m_height, 0.0);
    }
}



//Copy Constructor
template<typename T>
Matrix<T>::Matrix(const Matrix<T>& rhs)
{
    m_width = rhs.m_width;
    m_height = rhs.m_height;
    m_matrix = rhs.m_matrix;
}



//Default destructor
template<typename T>
Matrix<T>::~Matrix()
{
}



template<typename T> void
Matrix<T>::Print(std::ostream& outFile) const
{
    for(unsigned int i = 0; i < m_width; ++i)
    {
        outFile << "| ";
        for(unsigned int j = 0; j < m_height; ++j)
        {
            outFile << std::fixed << m_matrix[i][j] << " ";
        }
        outFile << "|" << std::endl;
    }
}

//Getter for width
template<typename T>
unsigned int
Matrix<T>::GetWidth() const
{
    return m_width;
}



//Getter for height
template<typename T>
unsigned int
Matrix<T>::GetHeight() const
{
    return m_height;
}



//Overloading the assignment operator
template<typename T>
Matrix<T>
Matrix<T>::operator=(const Matrix<T>& rhs)
{
    if(this == &rhs)
    {
        return *this;
    }
    m_width = rhs.m_width;
    m_height = rhs.m_height;
    m_matrix.resize(m_width);
    for(unsigned int i = 0; i < m_width; ++i)
    {
        m_matrix[i].resize(m_height);
        for(unsigned int j = 0; j < m_height; ++j)
        {
            m_matrix[i][j] = rhs.m_matrix[i][j];
        }
    }
    return *this;
}



//Overloading the function call operator - this is a getter
template<typename T>
const T
Matrix<T>::operator()(unsigned int i, unsigned int j) const
{
    if(i >= m_width || j >= m_height)
    {
        throw std::invalid_argument("Fatal Exception: operator() Index out of bound");
    }
    return m_matrix[i][j];
}



//Overloading the function call operator - this is a setter
template<typename T>
void
Matrix<T>::operator()(const unsigned int i, const unsigned int j, const T& value)
{
    if(i >= m_width || j >= m_height)
    {
        throw std::invalid_argument("Fatal Exception: operator() Index out of bound");
    }
    else
    {
        m_matrix[i][j] = value;
    }
}



//Overload the addition operator so we can subtract between two matrices
template<typename T>
Matrix<T>
Matrix<T>::operator+(const Matrix<T>& rhs) const
{
    if(( m_width != rhs.m_width) || (m_height != rhs.m_height))
        throw std::invalid_argument("Operation + not supported: Matrices are not the same dimension");
    Matrix result(m_width, m_height);
    for(unsigned int i = 0; i < m_width; ++i)
    {
        for(unsigned int j = 0; j < m_height; ++j)
        {
            result.m_matrix[i][j] = m_matrix[i][j] + rhs.m_matrix[i][j];
        }
    }
    return result;
}

//Overload the addition assignment operator so we can subtract between two matrices
//Does not support unequal matrices
template<typename T>
Matrix<T>
Matrix<T>::operator+=(const Matrix<T>& rhs)
{
    if((m_width != rhs.m_width) || (m_height != rhs.m_height))
        throw std::invalid_argument("Operation += not supported: Matrices are not the same dimension");
    for(unsigned int i = 0; i < m_width; ++i)
    {
        for(unsigned int j = 0; j < m_height; ++j)
        {
            m_matrix[i][j] += rhs.m_matrix[i][j];
        }
    }
    return *this;
}



//Overload the subtraction operator so we can subtract between two matrices
//Does not support unequal matrices
template<typename T>
Matrix<T>
Matrix<T>::operator-(const Matrix<T>& rhs) const
{
    if(( m_width != rhs.m_width) || (m_height != rhs.m_height))
        throw std::invalid_argument("Operation - not supported: Matrices are not the same size");
    Matrix result(m_width, m_height);
    std::cout << "" << std::endl;
    for(unsigned int i = 0; i < rhs.m_width; ++i)
    {
        for(unsigned int j = 0; j < rhs.m_height; ++j)
        {
            result.m_matrix[i][j] = m_matrix[i][j] - rhs.m_matrix[i][j];
        }
    }
    return result;
}



//Overload the subtraction assignment so we can subtract between two matrices
//Does not support unequal matrices
template<typename T>
Matrix<T>
Matrix<T>::operator-=(const Matrix<T>& rhs)
{
    if((m_width != rhs.m_width) || (m_height != rhs.m_height))
        throw std::invalid_argument("Operation -= not supported: Matrices are not the same size");
    for(unsigned int i = 0; i < m_width; ++i)
    {
        for(unsigned int j = 0; j < m_height; ++j)
        {
            m_matrix[i][j] -= rhs.m_matrix[i][j];
        }
    }
    return *this;
}



//Overloading the multiplication scalar operator
template<typename T>
Matrix<T>
Matrix<T>::operator*(const T& scalar) const
{
    Matrix result = *this;
    for(unsigned int i = 0; i < m_width; ++i)
    {
        for(unsigned int j = 0; j < m_height; ++j)
            result.m_matrix[i][j] = m_matrix[i][j] * scalar;
    }
    return result;
}



//Overloading the multiplication scalar assignment operator 
template<typename T>
Matrix<T>
Matrix<T>::operator*=(const T& scalar)
{
    for(unsigned int i = 0; i < m_width; ++i)
    {
        for(unsigned int j = 0; j < m_height; ++j)
            m_matrix[i][j] *= scalar;
    }
    return *this;
}



//Overloading the multiplication matrix-matrix operator
template<typename T>
Matrix<T>
Matrix<T>::operator*(const Matrix<T>& rhs) const
{
    //MxN * NxP -> MxP
    if((m_height != rhs.m_width))
    {
        std::string errString="Operation * not supported: Matrix-Matrix multiplication only supported if first matrix's column matches the second matrix's row";
        throw std::invalid_argument(errString);

    }
    Matrix result(m_width, rhs.m_height);
    for(unsigned int i = 0; i < m_width; ++i)
    {
        for(unsigned int j = 0; j < rhs.m_height; ++j)
        {
            for(unsigned int x = 0; x < m_height; ++x)
            {
                result.m_matrix[i][j] += (m_matrix[i][x] * rhs(x,j));
            }
        }
    }
    return result;
}



//Overloading the multiplication matrix-matrix assignment operator
template<typename T>
Matrix<T>
Matrix<T>::operator*=(const Matrix<T>& rhs)
{
    if((m_height != rhs.m_width))
    {
        std::string errString="Operation *= not supported: Matrix-Matrix multiplication only supported if first matrix's column matches the second matrix's row";
        throw std::invalid_argument(errString);

    }
    *this = (*this) * rhs;
    return *this;
}


//Overloading the function caller operator - this returns the row in a matrix
template<typename T>
std::vector<T>
Matrix<T>::operator()(const unsigned int i) const
{
    return m_matrix[i];
}



//Rotates the matrix - uses Tranpose and Reverse as helper methods
template<typename T>
void
Matrix<T>::Rotate()
{
    if(m_height != m_width)
    {
        throw std::invalid_argument("Rotate is only supported for NxN matrices"); 
    }
    Transpose();
    Reverse();
}



//Tranposes the matrix
template<typename T>
void
Matrix<T>::Transpose()
{
    if(m_height != m_width)
    {
        throw std::invalid_argument("Transpose is only supported for NxN matrices"); 
    }
    //assume this is a NxN
    unsigned int N = m_matrix.size();
    for(unsigned int i = 0; i < N; ++i)
    {
        for(unsigned int j = i;  j < N; ++j)
        {
            unsigned int tmp = m_matrix[j][i];
            m_matrix[j][i] = m_matrix[i][j];
            m_matrix[i][j] = tmp;
        }
    }
}



//Reverses the rows
template<typename T>
void
Matrix<T>::Reverse()
{
    if(m_height != m_width)
    {
        throw std::invalid_argument("Reverse is only supported for NxN matrices"); 
    }
    //assume this is a NxN
    unsigned int N = m_matrix.size();
    for(unsigned int i = 0; i < N; ++i)
    {
        for(unsigned int j = 0;  j < N; ++j)
        {
            unsigned int tmp = m_matrix[i][j];
            m_matrix[i][j] = m_matrix[i][m_matrix.size()-j-1];
            m_matrix[i][m_matrix.size()-j-1] = tmp;
        }
    }
}
#endif
