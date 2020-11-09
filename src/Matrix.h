#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <vector>

template <typename T> class Matrix
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

        //Print method for printing the whole matrix
        void Print(std::ostream & outFile=std::cout) const;

        std::vector<T> GetRow() const;

        //Getters for width, height, and specific indices in the matrix
        unsigned int GetWidth() const;
        unsigned int GetHeight() const;
        const T operator()(const unsigned int i, const unsigned int j) const;
        std::vector<T> operator()(const unsigned int row) const;

        //Setter for specific index in matrix
        void operator()(const unsigned int i, const unsigned int j, const T& value);

        Matrix<T> operator=(const Matrix<T>& rhs);

        Matrix<T> operator+(const Matrix<T>& rhs) const;
        Matrix<T> operator+=(const Matrix<T>& rhs);

        Matrix<T> operator-(const Matrix<T>& rhs) const;
        Matrix<T> operator-=(const Matrix<T>& rhs);

        Matrix<T> operator*(const T& scalar) const;
        Matrix<T> operator*=(const T& scalar);

        Matrix<T> operator*(const Matrix<T>& rhs) const;
        Matrix<T> operator*=(const Matrix<T>& rhs);

        void Transpose();
        void Reverse();
        void Rotate();

    private:
        unsigned int m_width;
        unsigned int m_height;
        std::vector<std::vector<T>> m_matrix;
};


#include "Matrix.cpp"
#endif
