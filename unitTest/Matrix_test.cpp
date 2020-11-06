#include "gtest/gtest.h"
#include "../src/Matrix.cpp"


class MatrixTest : public ::testing::Test
{
    protected:
        Matrix* pMatrix1;
        Matrix* pMatrix2;

    MatrixTest() {
    }

    virtual ~MatrixTest() {
    }

    virtual void SetUp()
    {
        pMatrix1 = new Matrix(3,3);
        pMatrix2 = new Matrix(3,3);
        for(unsigned int i = 0; i < 3 ; ++i)
        {
            for(unsigned int j = 0; j < 3; ++j)
            {
                //set the index
                pMatrix1->operator()(i, j, 1.0);
                pMatrix2->operator()(i, j, 1.0);
            }
        }
    }

    virtual void TearDown()
    {
        delete pMatrix1;
        delete pMatrix2;
    }
};

//Test the default constructor
TEST(MatrixStandAlone_Test, MatrixDefaultConstructor)
{
    Matrix matrix;
    unsigned int N = matrix.GetWidth();
    unsigned int M = matrix.GetHeight();
    EXPECT_EQ(1, N);
    EXPECT_EQ(1, M);

    for(unsigned int i = 0; i < N; ++i)
    {
        for(unsigned int j = 0; j < M; ++j)
            EXPECT_EQ(0.0, matrix(i,j));
    }
}


//Test the paramterized constructor - they should be 3x3
TEST_F(MatrixTest, MatrixConstructor)
{
    EXPECT_EQ(3, pMatrix1->GetWidth());
    EXPECT_EQ(3, pMatrix1->GetHeight());
}


//Test the overloaded function call operator which
//gets and sets indexes of a matrix
//Test that it throws if we pass an invalid index
TEST_F(MatrixTest, MatrixSetterGetter)
{
    unsigned int N = pMatrix1->GetWidth();
    unsigned int M = pMatrix1->GetHeight();
    for(unsigned int i = 0; i < N ; ++i)
    {
        for(unsigned int j = 0; j < M ; ++j)
            //set the index
            pMatrix1->operator()(i, j, 0.141519);
    }

    for(unsigned int i = 0; i < N ; ++i)
    {
        for(unsigned int j = 0; j < M ; ++j)
        {
            //retrieve the index
            EXPECT_DOUBLE_EQ(0.141519, pMatrix1->operator()(i,j));
        }
    }
    EXPECT_THROW(pMatrix1->operator()(900, 900), std::invalid_argument);
    EXPECT_THROW(pMatrix1->operator()(-1, -1, 100), std::invalid_argument);
}



TEST_F(MatrixTest, MatrixAddition)
{
    Matrix bad_dimension(1,3);

    EXPECT_THROW(bad_dimension + *pMatrix1, std::invalid_argument);

    unsigned int N = pMatrix1->GetWidth();
    unsigned int M = pMatrix1->GetHeight();
    for(unsigned int i = 0; i < N ; ++i)
    {
        for(unsigned int j = 0; j < M ; ++j)
            //set the index
            pMatrix1->operator()(i, j, 1.141519);
    }

    //Test the addition operator
    Matrix result = *pMatrix1 + *pMatrix2;
    for(unsigned int i = 0; i < N; ++i)
    {
        for(unsigned int j = 0; j < M; ++j)
        {
            EXPECT_DOUBLE_EQ(2.1415189999999997, result(i,j));
        }
    }

    //Test the addition assignment operator
    result += *pMatrix1;
    for(unsigned int i = 0; i < N; ++i)
    {
        for(unsigned int j = 0; j < M; ++j)
        {
            EXPECT_DOUBLE_EQ(3.2830379999999999, result(i,j));
        }
    }
}


TEST_F(MatrixTest, MatrixSubtraction)
{
    unsigned int N = pMatrix1->GetWidth();
    unsigned int M = pMatrix1->GetHeight();
    for(unsigned int i = 0; i < N ; ++i)
    {
        for(unsigned int j = 0; j < M ; ++j)
            //set the index
            pMatrix2->operator()(i, j, 0.0000000000001);
    }

    Matrix result = *pMatrix1 - *pMatrix2;
    for(unsigned int i = 0; i < N; ++i)
    {
        for(unsigned int j = 0; j < M; ++j)
        {
            EXPECT_DOUBLE_EQ(0.99999999999989997, result(i,j));
        }
    }
}


//Test scalar, and matrix-matrix multiplcation
TEST_F(MatrixTest, MatrixMultiplication)
{
    unsigned int N = pMatrix1->GetWidth();
    unsigned int M = pMatrix1->GetHeight();
    Matrix result = *pMatrix1 * 5.555555;

    for(unsigned int i = 0; i < N; ++i)
    {
        for(unsigned int j = 0; j < M; ++j)
        {
            EXPECT_DOUBLE_EQ(5.555555, result(i,j));
        }
    }
}
