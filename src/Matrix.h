#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <vector>

class Matrix
{
    public:
        //default constructor
        Matrix();

        //parameterized constructor
        Matrix(unsigned int width, unsigned int height);

        //copy constructor
        Matrix(const Matrix& rhs);

        //Default destructor
        ~Matrix();

        //Getters for width, height, and specific indices in the matrix
        unsigned int GetWidth() const;
        unsigned int GetHeight() const;
        long double operator()(const unsigned int i, const unsigned int j) const;

        //Setter for specific index in matrix
        void operator()(const unsigned int i, const unsigned int j, long double value);

        Matrix operator=(const Matrix& rhs);
        Matrix operator+(const Matrix& rhs) const;
        Matrix operator+=(const Matrix& rhs);
        Matrix operator-(const Matrix& rhs) const;
        Matrix operator-=(const Matrix& rhs);
        Matrix operator*(const long double scalar) const;

    private:
        std::string m_fileName;
        unsigned int m_width;
        unsigned int m_height;
        std::vector<std::vector<long double>> m_matrix;
};


#endif
