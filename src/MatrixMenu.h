//#############################
//  Homework B by Kevin Suh   #
//#############################

#ifndef MATRIX_MENU_H
#define MATRIX_MENU_H

#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include "Matrix.h"

class MatrixMenu
{
    //private by default
    typedef std::pair<std::string, std::vector<Matrix<float>>> HistoryEntry;

    public:
        //Default Constructor
        MatrixMenu();
        //Parameterized Constructor - takes in a file name
        MatrixMenu(std::string fileInput);
        //Default destructor
        ~MatrixMenu();

        //Public method to start exeuction
        void Start();

    private:

        //Method to provide a menu interface for the user
        //arg: none
        //return: none
        void PrintMenu() const;

        //Method to read in user input
        //arg: none
        //return: none
        void ProcessInput();

        //Method to act on user input
        //arg: none
        //return: none
        void ActionInput();

        //Method to create Matrices
        //arg: none
        //return: none
        void CreateMatrices();

        //Helper method to grab dimension input
        //arg1: Reference of a matrix object
        //return: none
        void GrabDimensionInput(Matrix<float> &matrix);

        //Method to choose which Matrix to edit
        //arg: none
        //return: none
        void Edit();

        //Helper method to edit the matrix
        //arg1: string of Matrix's name
        //arg2: Reference of a matrix object
        //return: none
        void EditMatrix(const std::string name, Matrix<float> &matrix);

        //Method to print the matrices in a format
        //arg1: Matrix<float> object passed as a const reference
        //arg2: Matrix<float> object passed as a const reference
        //return: none
        void PrintMatrices(const Matrix<float>& matrix1, const Matrix<float>& matrix2) const;

        //Method to print history
        //arg: bool - will write to a file titled "output.data" if argument is true
        //return: none
        void PrintHistory(bool saveToFile=false) const;

        //Method to add two matrices
        //arg: none
        //return: none
        void AddMatrices(); 

        //Method to subtract two matrices
        //arg: none
        //return: none
        void SubtractMatrices();

        //Method to multiply two matrices
        //arg: none
        //return: none
        void MultiplyMatrices();

        //TODO: Declared but not defined - currently reusing MultiplyMatrices if Matrix is a 1x1
        //Method to multiply matrix with a scalar
        //arg: none
        //return: none
        void MultiplyMatrixScalar();

        //Method to rotate a matrix
        //arg: none
        //return: none
        void RotateMatrix();

        //Method to read a data file
        //arg: none
        //return: none
        void ProcessFile();

        //Helper method to process the arguments in the data file
        //arg1: a string indicating we are to parse
        //arg2: an integer passed by reference indicating the number of matrices to expect
        //arg3: an integer passed by reference indicating the number of operations to expect
        //arg4: an integer passed by reference indicating the row of a dimension for the first matrix
        //arg5: an integer passed by reference indicating the col of a dimension for the first matrix
        //arg6: an integer passed by reference indicating the row of a dimension for the second matrix
        //arg7: an integer passed by reference indicating the col of a dimension for the second matrix
        //return: none
        //bad design (too many arguments)
        void ProcessFileArgument(const std::string input, 
                unsigned int& numOfMatrices, unsigned int& numOfOperations,
                unsigned int& rowA, unsigned int& colA,
                unsigned int& rowB, unsigned int & colB);


        //Helper method to process the matrices in the data file 
        //Prerequisities: ifstream must be already open
        //arg1: an ifstream to continue reading the next row in the matrix
        //arg2: a string representing the elements in the matrix
        //arg3: an integer passed by reference indicating the row of a dimension for the first matrix
        //arg4: an integer passed by reference indicating the col of a dimension for the first matrix
        //arg5: an integer passed by reference indicating the row of a dimension for the second matrix
        //arg6: an integer passed by reference indicating the col of a dimension for the second matrix
        //arg6: an integer to indicate the number of matrices we have process (kind of redudnant but ran out of time)
        //return none
        //bad design (too many arguments)
        void ProcessFileMatrices(std::ifstream& file, std::string input,
                                const unsigned int& numOfMatrices,
                                unsigned int rowA, unsigned int colA,
                                unsigned int rowB, unsigned int colB,
                                unsigned int& lineCounter);


        //Helper method to process the operation types to perform on the matrices
        //will actually perform the oepration too (bad design - should break up the function)
        //Prerequisities: ifstream must be already open
        //arg1: an ifstream must be already open
        //arg2: the number of operations to expect
        void ProcessFileOperations(std::ifstream& file, std::string input, const unsigned int numOfOperations);



        //private member variables
        unsigned int                    m_state; //keeps track of the user's input
        std::string                     m_fileInput; //the data file name
        Matrix<float>                   m_matrix1; //matrix object
        Matrix<float>                   m_matrix2; //matrix object


        std::vector<HistoryEntry> m_history; //a vector containing the history of previous operations
};
#endif
