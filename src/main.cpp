/*
//Homework B by Kevin Suh
*/
#include <iostream> //std::cout,cin
#include <stdio.h> //printf
#include <unistd.h>
#include <csignal>
#include "Matrix.h"

using namespace std;


//A signal handler to have the program end quietly
//allows us to ctrl+c from when the executable is ran from the Makefile
//and still exit quietly
void sighandler(int signal)
{
    switch(signal)
    {
        case 2:
            exit(0);
        default:
            exit(signal);
    }
} 


// Helper function to print the usages that arguments that we support
// should only exist in main.cpp - let's make it static to be explicit
// Output: None
static void ShowInfo(std::string name)
{
    std::cerr << "Usage: " << name << " <option(s)> SOURCES\n"
        << "Options:\n"
        << "\t-h,--help\t\tShow this help message\n"
        << "\tOPTIONAL -f,--file\t\tFile for data input\n"
        << "\tOPTIONAL -n,--width\t\tWidth of the matrix\n"
        << "\tOPTIONAL -m,--height\t\tHeight of the matrix\n"
        << std::endl;
}


// Helper function to parse arguments
// optarg is an extern variable set implicitly
// by the getopt library
// Output:
//       - False on undefined argument or missing parameter
//       - True on successful parameter
static bool ParseArgs(int argc, char* argv[], std::string& fileName, std::string& width, std::string& height)
{
    int opt;
    while((opt = getopt(argc, argv, "f:n:m")) != -1)
    {
        switch(opt)
        {
            case 'f':
                fileName = optarg;
                break;
            case 'n':
                width = optarg;
                break;
            case 'm':
                height = optarg;
                break;
            default:
                ShowInfo(argv[0]);
                return false;
        }
    }
    return true;
}

int main(int argc, char* argv[])
{
    std::signal(SIGINT, sighandler);

    std::string fileName = "";
    std::string width = "1"; //default width
    std::string height = "1"; //default height
    if(ParseArgs(argc, argv, fileName, width, height))
    {
        try
        {
            while(1)
            {
                try
                {
                    //Let's construct the object
                    Matrix(stoul(width), stoul(height));
                }
                catch(std::exception &e)
                {
                    std::cout << &e << std::endl;
                }
            }
        }
        catch(...)
        {
            std::cout << "FATAL EXCEPTION: Uknown Error!" << std::endl;
        }
    }
    return 0;
};
