#ifndef MATRIX_MENU_H
#define MATRIX_MENU_H

#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include "Matrix.h"

class MatrixMenu
{
    typedef std::pair<std::string, std::vector<Matrix<float>>> HistoryEntry;
    //private by default
    enum MatrixOptions
    {
        CREATE=1,
        READ_FILE=2,
        PRINT_MATRIX=3,
        WRITE_FILE=9
    };


    public:
        MatrixMenu();
        MatrixMenu(std::string fileInput);
        ~MatrixMenu();
        void Start();

    private:

        void PrintMenu() const;
        void ProcessInput();
        void ActionInput();

        void CreateMatrices();
        void Edit();

        void EditMatrix(const std::string name, Matrix<float> &matrix);
        void GrabInput(Matrix<float> &matrix);

        void PrintMatrices(Matrix<float> matrix1, Matrix<float> matrix2) const;
        void PrintHistory(bool saveToFile=false) const;

        void AddMatrices(); 
        void SubtractMatrices();
        void MultiplyMatrices();
        void MultiplyMatrixScalar();
        void RotateMatrix();

        void ProcessFile();

        void ProcessFileArgument(const std::string input, 
                unsigned int& numOfMatrices, unsigned int& numOfOperations,
                unsigned int& rowA, unsigned int& colA,
                unsigned int& rowB, unsigned int & colB);

        void ProcessFileMatrices(std::ifstream& file, std::string input,
                                const unsigned int& numOfMatrices,
                                unsigned int rowA, unsigned int colA,
                                unsigned int rowB, unsigned int colB,
                                unsigned int& lineCounter);

        void ProcessFileOperations(std::ifstream& file, std::string input, const unsigned int numOfOperations);



        unsigned int                    m_state;
        std::string                     m_fileInput;
        Matrix<float>                   m_matrix1;
        Matrix<float>                   m_matrix2;


        //Key: Operation
        std::vector<HistoryEntry> m_history;
};
#endif
