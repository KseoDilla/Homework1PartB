//#############################
//  Homework B by Kevin Suh   #
//#############################

#ifndef MATRIXMENU_CPP
#define MATRIXMENU_CPP

#include "MatrixMenu.h"
#include <string>
#include <limits>
#include <iostream>
#include <sstream>
#include <fstream>


//Default constructor
MatrixMenu::MatrixMenu() : 
m_state(0),
m_fileInput(""),
m_matrix1(),
m_matrix2()
{
}



//Default constructor
MatrixMenu::MatrixMenu(std::string fileInput) :
m_state(0),
m_fileInput(fileInput),
m_matrix1(),
m_matrix2()
{
}



//Default destructor
MatrixMenu::~MatrixMenu()
{
}



void
MatrixMenu::Start()
{
    std::cout << std::endl;
    std::cout << "***********************************" << std::endl;
    std::cout << "***********************************" << std::endl;
    std::cout << "Welcome to Homework Part 1B: Matrix" << std::endl;
    std::cout << "***********************************" << std::endl;
    std::cout << "***********************************" << std::endl;
    std::cout << std::endl;
    if(!m_fileInput.empty())
    {
        ProcessFile();
    }
    else
    {
        CreateMatrices();
    }
    while(true)
    {
        PrintMenu();
        ProcessInput();
        ActionInput();
    }
}



void
MatrixMenu::PrintMenu() const
{
    std::cout << "1) Initialize Matrices" << std::endl;
    std::cout << "2) Edit Matrix" << std::endl;
    std::cout << "3) Add Two Matrices" << std::endl;
    std::cout << "4) Subtract Two Matrices" << std::endl;
    std::cout << "5) Multiply Matrix with Scalar" << std::endl;
    std::cout << "6) Multiply Two Matrices" << std::endl;
    std::cout << "7) Rotate Matrix" << std::endl;
    std::cout << "8) Read Matrix File" << std::endl;
    std::cout << "9) Print History" << std::endl;
    std::cout << "10) Save Results Into File" << std::endl; 
    std::cout << "Input:";
}



void
MatrixMenu::ActionInput()
{
    try
    {
        switch(m_state)
        {
            case 1:
                CreateMatrices();
                break;
            case 2:
                Edit();
                break;
            case 3:
                AddMatrices();
                break;
            case 4:
                SubtractMatrices();
                break;
            case 5:
            case 6:
                MultiplyMatrices();
                break;
            case 7:
                RotateMatrix();
                break;
            case 8:
            {
                std::cout << "Please provide a filename: ";
                getline(std::cin, m_fileInput);
                ProcessFile();
                break;
            }
            case 9:
                PrintHistory(false);
                break;
            case 10:
                PrintHistory(true);
                break;
            default:
                std::cout << m_state << " not yet defined" << std::endl;
        }
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
    }
}



void
MatrixMenu::ProcessInput()
{
    do {
        std::cin >> m_state;
        std::cin.ignore();
        //capture overflow inputs
        if(std::cin.fail() || (m_state <= 0 || m_state >= 11))
        {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid Input" << std::endl;
            PrintMenu();
            continue;
        }
        else
            break;
    } while((m_state <= 0 || m_state >=11 ));
}



void
MatrixMenu::CreateMatrices()
{
    //make sure they populate both
    std::cout << "Please provide a dimension for Matrix A:";
    GrabDimensionInput(m_matrix1);
    m_matrix1.Print();
    std::cout << "Please provide a dimension for Matrix B:";
    GrabDimensionInput(m_matrix2);
    m_matrix2.Print();
    std::cout << std::endl;
}



void
MatrixMenu::GrabDimensionInput(Matrix<float> &matrix)
{
    const unsigned int max = 2;
    std::string input;
    getline(std::cin, input);
    if(input.empty())
        return;
    else
    {
        std::vector<std::string> indices;
        std::istringstream iss(input);
        std::string s;
        for(unsigned int i = 0; i < max; ++i)
        {
            if(!iss.eof())
                iss >> s;
            else
            {
                std::cin >> s;
                std::cin.ignore();
            }
            indices.push_back(s);
        }
        matrix = Matrix<float>(stoi(indices[0]), stoi(indices[1]));
    }
}


void
MatrixMenu::PrintMatrices(const Matrix<float>& matrix1, const Matrix<float>& matrix2) const
{
    unsigned int rowA = 0, rowB = 0;
    unsigned int widthA = matrix1.GetWidth(), widthB = matrix2.GetWidth();
    std::cout << "Matrix A" << std::endl;
    while(rowA < widthA)
    {
        if(rowA < widthA)
        {
            std::vector<float> row = matrix1(rowA++);
            std::cout << "| ";
            for(auto it : row)
                printf("%f ", it);
            std::cout << "|" << std::endl;
        }
    }
    std::cout << "Matrix B" << std::endl;
    while(rowB < widthB)
    {
        if(rowB < widthB)
        {
            std::vector<float> row = matrix2(rowB++);
            std::cout << "| ";
            for(auto it : row)
                printf("%f ", it);
            std::cout << "|" << std::endl;
        }
    }
}


void
MatrixMenu::AddMatrices()
{
    PrintMatrices(m_matrix1, m_matrix2);
    std::cout << "Matrix A + Matrix B" << std::endl;
    Matrix<float> result = m_matrix1 + m_matrix2;
    result.Print();

    std::vector<Matrix<float>> history{m_matrix1, m_matrix2, result};
    m_history.push_back(std::make_pair("+", history));
}



void
MatrixMenu::MultiplyMatrices()
{
    PrintMatrices(m_matrix1, m_matrix2);
    std::cout << "Matrix A * Matrix B" << std::endl;
    Matrix<float> result;
    //This isn't really standard math but I thought "why not? a 1x1 is really just a scalar"
    if(m_matrix2.GetWidth() == 1 && m_matrix2.GetHeight() == 1)
    {
        result = m_matrix1 * m_matrix2(0,0);
    }
    else
    {
        result = m_matrix1 * m_matrix2;
    }
    result.Print();

    std::vector<Matrix<float>> history{m_matrix1, m_matrix2, result};
    m_history.push_back(std::make_pair("*", history));
}



void
MatrixMenu::SubtractMatrices()
{
    PrintMatrices(m_matrix1, m_matrix2);
    std::cout << "Matrix A - Matrix B" << std::endl;
    Matrix<float> result = m_matrix1 - m_matrix2;
    result.Print();

    std::vector<Matrix<float>> history{m_matrix1, m_matrix2, result};
    m_history.push_back(std::make_pair("-", history));
}



void
MatrixMenu::PrintHistory(const bool saveToFile) const
{
    std::ofstream of;
    std::string fileName;
    try
    {
        if(saveToFile)
        {
            of.open("output.data", std::ios::out);
        }
        std::ostream & outFile = (saveToFile ? of : std::cout);
        outFile << std::endl;
        for(auto it : m_history)
        {
            if(it.second.size() == 3)
            {
                outFile << "Matrix A:" << std::endl;
                it.second[0].Print(outFile);
                outFile << "Matrix B:" << std::endl;
                it.second[1].Print(outFile);
                outFile << "Matrix A " <<  it.first << " Matrix B: " << std::endl;
                it.second[2].Print(outFile);
            }
            else if(it.second.size() == 2)
            {
                outFile << "Matrix" << std::endl;
                it.second[0].Print(outFile);
                outFile << "Matrix " << it.first << " Operation" << std::endl;
                it.second[1].Print(outFile);
            }
            else
            {
                outFile << "Serious Bug Contact Maintainer" << std::endl;
            }
            outFile << std::endl;
        }
        if(saveToFile)
            std::cout << std::endl << "History Complete: saved to output.data"  << std::endl << std::endl;
        else
            std::cout << std::endl << "History Complete!" << std::endl << std::endl;
    }
    catch(std::exception &e)
    {
        std::cout << "Standard Exception: " << e.what() << std::endl;
    }
    catch(...)
    {
        std::cout << "FATAL Exception: Contact Maintainer" << std::endl;
    }
    of.close();
}



void
MatrixMenu::Edit()
{
    std::cout << "Please choose what matrix you would like to modify" << std::endl;
    std::cout << "1) Matrix A" << std::endl;
    std::cout << "2) Matrix B" << std::endl;
    std::cout << "3) Exit" << std::endl;
    std::cout << "Input: ";
    int input = 0;
    std::cin >> input;
    std::cin.ignore(); //flush the buffer
    switch(input)
    {
        case 1:
            EditMatrix("Matrix A", m_matrix1);
            break;
        case 2:
            EditMatrix("Matrix B", m_matrix2);
            break;
        case 3:
            break;
        default:
            std::cout << "Input is not supported." << std::endl;
            break;
    }
}



void
MatrixMenu::EditMatrix(const std::string name, Matrix<float> &matrix)
{
    do {
        std::cout << name << std::endl;
        matrix.Print();
        std::cout << "Please provide which index you would like to modify separated by space (provide empty to stop this mode):";
        std::string input;
        getline(std::cin, input);
        if(input.empty())
            break;
        else
        {
            const unsigned int max = 2;
            std::vector<std::string> indices;
            std::istringstream iss(input);
            std::string s;
            for(unsigned int i = 0; i < max; ++i)
            {
                if(!iss.eof())
                    iss >> s;
                else
                {
                    std::cin >> s;
                    std::cin.ignore();
                }
                indices.push_back(s);
            }
            std::cout << "Provide a value to update this index with: ";
            std::cin >> input;
            std::cin.ignore();
            matrix(stoi(indices[0]),stoi(indices[1]),stof(input));
        }
    } while(true);
}


//Not the best function
void
MatrixMenu::ProcessFile()
{
    std::cout << "Processing file: " << m_fileInput << std::endl;
    std::ifstream file;
    std::string delimiter = "x";
    try
    {
        file.open(m_fileInput);
        if(!file.is_open())
        {
            std::cout << "File is not open: " << m_fileInput << " does not exist!" << std::endl;
        }
        else
        {
            std::string input;
            std::string dimensionA;
            std::string dimensionB;
            unsigned int numOfMatrices = 0;
            unsigned int numOfOperations = 0;
            unsigned int rowA = 0, colA = 0, rowB = 0, colB = 0;
            unsigned int lineCounter = 0;
            while(getline(file, input))
            {
                if(input == "EOF")
                    break;
                else if (input.empty())
                    continue;
                else
                {
                    if(lineCounter == 0)
                    {
                        ProcessFileArgument(input, numOfMatrices, numOfOperations, rowA, colA, rowB, colB);
                        lineCounter++;
                    }
                    else if(lineCounter <= numOfMatrices)
                    {
                        ProcessFileMatrices(file, input, numOfMatrices, rowA, colA, rowB, colB, lineCounter);
                    }
                    else
                    {
                        ProcessFileOperations(file, input, numOfOperations);
                        lineCounter = 0;
                    }
                }
            }
        }
        file.close();
        return;
    }
    catch(const std::exception &e)
    {
        std::cout << "Standard exception: " << e.what() << std::endl;
        std::cout << "Skipping rest of the file" << std::endl;
    }
    catch(...)
    {
        std::cout << "FATAL Exception in ProcessFile()" << std::endl;
        std::cout << "Skipping rest of the file" << std::endl;
    }
    file.close();
}

void
MatrixMenu::ProcessFileArgument(const std::string input,
                                unsigned int& numOfMatrices, unsigned int& numOfOperations,
                                unsigned int& rowA, unsigned int& colA,
                                unsigned int& rowB, unsigned int & colB)
{
    const unsigned int max = 4;
    std::string dimensionA, dimensionB;
    std::vector<std::string> args;

    std::istringstream iss(input);
    std::string s;
    for(unsigned int i = 0; i < max; ++i)
    {
        iss >> s;
        args.push_back(s);
    }
    numOfMatrices = std::stoi(args[0]);
    dimensionA = args[1];
    dimensionB = args[2];
    numOfOperations = std::stoi(args[3]);

    std::string delimiter = "x";
    rowA = std::stoi(dimensionA.substr(0, dimensionA.find(delimiter)));
    colA = std::stoi(dimensionA.substr(dimensionA.find(delimiter)+1));

    rowB = std::stoi(dimensionB.substr(0, dimensionB.find(delimiter)));
    colB = std::stoi(dimensionB.substr(dimensionB.find(delimiter)+1));
    //first read how many matrices, the dimensions, and how many operations
    m_matrix1 = Matrix<float>(rowA, colA);
    m_matrix2 = Matrix<float>(rowB, colB);
}


//This function assumes the file is already open
void
MatrixMenu::ProcessFileMatrices(std::ifstream& file, std::string input,
                    const unsigned int& numOfMatrices,
                    unsigned int rowA, unsigned int colA,
                    unsigned int rowB, unsigned int colB,
                    unsigned int& lineCounter)

{
    for(unsigned int matrixCounter = 0; matrixCounter < numOfMatrices;)
    {
        //process empty lines
        if(input.empty())
        {
            getline(file,input);
            continue;
        }
        else if(matrixCounter == 0)
        {
            for(unsigned int i = 0; i < rowA; ++i)
            {
                std::istringstream iss(input);
                std::string s;
                for(unsigned int j = 0; j < colA; ++j)
                {
                    iss >> s;
                    m_matrix1(i,j,std::stof(s));
                }
                getline(file, input);
            }
            ++matrixCounter;
        }
        else
        {
            for(unsigned int i = 0; i < rowB; ++i)
            {
                std::istringstream iss(input);
                std::string s;
                for(unsigned int j = 0; j < colB; ++j)
                {
                    iss >> s;
                    m_matrix2(i,j,std::stof(s));
                }
                getline(file, input);
            }
            ++matrixCounter;
        }
        lineCounter++;
    }
}

void
MatrixMenu::ProcessFileOperations(std::ifstream& file, std::string input, const unsigned int numOfOperations)
{

    unsigned int operationCounter = 0;
    while(operationCounter < numOfOperations)
    {
        try
        {
            if(!input.empty())
            {
                if(input == "Add" || input == "Addition" || input == "+")
                {
                    AddMatrices();
                }
                else if(input == "Minus" || input == "Subtract" || input == "-")
                {
                    SubtractMatrices();
                }
                else if(input == "Multiply" || input == "Product" || input == "*")
                {
                    MultiplyMatrices();
                }
                else if(input == "Rotate")
                {
                    RotateMatrix();
                }
                else
                {
                    std::cout << "Unknown operation!" << std::endl;
                }
                operationCounter++;
                std::cout << std::endl << "Operation " << input << " complete." << std::endl;
            }
        }
        catch(std::exception &e)
        {
            operationCounter++;
            std::cout << "Standard Exception: " << e.what() << std::endl;
        }
        std::cout << std::endl;
        getline(file,input);
    }
}


//Method to rotate a matrix
void
MatrixMenu::RotateMatrix()
{
    std::cout << "Please choose which Matrix you would like to rotate:" << std::endl;
    std::cout << "1) Matrix A " << std::endl;
    std::cout << "2) Matrix B " << std::endl;
    std::cout << "3) Exit" << std::endl;
    unsigned int input = 0;
    std::cin >> input;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    std::cout << std::endl;
    if(input == 1)
    {
        std::cout << "Matrix Before Rotation: " << std::endl;
        m_matrix1.Print();
        Matrix<float> result = m_matrix1; 
        result.Rotate();
        std::vector<Matrix<float>> history{m_matrix1, result};
        m_matrix1 = result;
        std::cout << "Matrix After Rotation: " << std::endl;
        m_matrix1.Print();
        m_history.push_back(std::make_pair("Rotate", history));
    }
    else if(input == 2)
    {
        std::cout << "Matrix Before Rotation: " << std::endl;
        m_matrix2.Print();
        Matrix<float> result = m_matrix2; 
        result.Rotate();
        std::vector<Matrix<float>> history{m_matrix2, result};
        m_matrix2 = result;
        std::cout << "Matrix After Rotation: " << std::endl;
        m_matrix2.Print();
        m_history.push_back(std::make_pair("Rotate", history));
    }
    else
    {
        //3 or invalid input - just exit
        return;
    }
}

#endif
