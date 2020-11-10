//#############################
//  Homework B by Kevin Suh   #
//#############################

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
        //takes an ostream if it needs to print to a file
        void Print(std::ostream & outFile=std::cout) const;

        //Getters for width
        unsigned int GetWidth() const;


        //Getter for height
        unsigned int GetHeight() const;
        
        //Getter for grabbing a specific element in the matrix
        const T operator()(const unsigned int i, const unsigned int j) const;

        //Getter for returning a row
        std::vector<T> operator()(const unsigned int row) const;

        //Setter for specific index in matrix
        void operator()(const unsigned int i, const unsigned int j, const T& value);

        //Overloading the assignment operator
        Matrix<T> operator=(const Matrix<T>& rhs);

        //Overload of the  addition operator
        Matrix<T> operator+(const Matrix<T>& rhs) const;
        //Overload of the addition assignment operator
        Matrix<T> operator+=(const Matrix<T>& rhs);

        //Overload of the subtraction operator
        Matrix<T> operator-(const Matrix<T>& rhs) const;
        //Overload of the subtraction assignment operator
        Matrix<T> operator-=(const Matrix<T>& rhs);

        //Overload of the multiplication scalar operator
        Matrix<T> operator*(const T& scalar) const;
        //Overload the multiplication scalar assignment operator:w
        Matrix<T> operator*=(const T& scalar);

        //Overload of the multiplication matrix-matrix operator
        Matrix<T> operator*(const Matrix<T>& rhs) const;
        //Overload of the multiplication matrix-matrix assignment operator
        Matrix<T> operator*=(const Matrix<T>& rhs);

        //Public method to tranpose a matrix
        void Transpose();
        //Public method to reverse a matrix
        void Reverse();
        //Public method to rotate a matrix clock wise
        void Rotate();

    private:
        unsigned int m_width;
        unsigned int m_height;
        std::vector<std::vector<T>> m_matrix;
};

//include the definition
#include "Matrix.cpp"

#endif
