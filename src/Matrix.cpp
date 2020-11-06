// Matrix Class
#include "Matrix.h"
#include <stdexcept>


//Default constructor
Matrix::Matrix()
:m_width(1), m_height(1)
{
    m_matrix.resize(m_width);
    m_matrix[0].resize(m_height, 0.0);
}



//Parameter Constructor
Matrix::Matrix(unsigned int width, unsigned int height)
: m_width(width), m_height(height)
{
    m_matrix.resize(m_width);
    for(unsigned int i = 0; i < m_width; ++i)
    {
        m_matrix[i].resize(m_height, 0.0);
    }
}



//Copy Constructor
Matrix::Matrix(const Matrix& rhs)
{
    m_width = rhs.m_width;
    m_height = rhs.m_height;
    m_matrix = rhs.m_matrix;
}



//Default destructor
Matrix::~Matrix()
{
    //no heap allocation
}



//Getter for width
unsigned int
Matrix::GetWidth() const
{
    return m_width;
}



//Getter for height
unsigned int
Matrix::GetHeight() const
{
    return m_height;
}



Matrix
Matrix::operator=(const Matrix& rhs)
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



long double
Matrix::operator()(unsigned int i, unsigned int j) const
{
    if(i >= m_width || j >= m_height)
    {
        throw std::invalid_argument("Fatal Exception: operator() Index out of bound");
    }
    return m_matrix[i][j];
}



void
Matrix::operator()(const unsigned int i, const unsigned int j, long double value)
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
//Does not support unequal matrices
Matrix
Matrix::operator+(const Matrix& rhs) const
{
    if(( m_width != rhs.m_width) || (m_height != rhs.m_height))
        throw std::invalid_argument("Opeartion not supported: Matrices are not the same size");
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

//Overload the addition operator so we can subtract between two matrices
//Does not support unequal matrices
Matrix
Matrix::operator+=(const Matrix& rhs)
{
    if((m_width != rhs.m_width) || (m_height != rhs.m_height))
        throw std::invalid_argument("Opeartion not supported: Matrices are not the same size");
    Matrix result(m_width, m_height);
    for(unsigned int i = 0; i < m_width; ++i)
    {
        for(unsigned int j = 0; j < m_height; ++j)
        {
            m_matrix[i][j] += rhs.m_matrix[i][j];
        }
    }
    return result;
}



//Overload the subtraction operator so we can subtract between two matrices
//Does not support unequal matrices
Matrix
Matrix::operator-(const Matrix& rhs) const
{
    if(( m_width != rhs.m_width) || (m_height != rhs.m_height))
        throw std::invalid_argument("Operation not supported: Matrices are not the same size");
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
Matrix
Matrix::operator-=(const Matrix& rhs)
{
    if((m_width != rhs.m_width) || (m_height != rhs.m_height))
        throw std::invalid_argument("Opeartion not supported: Matrices are not the same size");
    Matrix result(m_width, m_height);
    for(unsigned int i = 0; i < m_width; ++i)
    {
        for(unsigned int j = 0; j < m_height; ++j)
        {
            m_matrix[i][j] -= rhs.m_matrix[i][j];
        }
    }
    return result;
}

Matrix
Matrix::operator*(const long double rhs) const
{
    Matrix result = *this;
    for(unsigned int i = 0; i < m_width; ++i)
    {
        for(unsigned int j = 0; j < m_height; ++j)
            result.m_matrix[i][j] = m_matrix[i][j] * rhs;
    }
    return result;
}
