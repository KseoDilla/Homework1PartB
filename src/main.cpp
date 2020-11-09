/*
//Homework B by Kevin Suh
*/
#include <iostream> //std::cout,cin
#include <stdio.h> //printf
#include <memory> //unique_ptr
#include <unistd.h> //getopt
#include <csignal> //signal handler
#include "MatrixMenu.h" //matrix menu

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
        << std::endl;
}


// Helper function to parse arguments
// optarg is an extern variable set implicitly
// by the getopt library
// Output:
//       - False on undefined argument or missing parameter
//       - True on successful parameter
static bool ParseArgs(int argc, char* argv[], std::string& fileName)
{
    int opt;
    while((opt = getopt(argc, argv, "f:")) != -1)
    {
        switch(opt)
        {
            case 'f':
                fileName = optarg;
                break;
            default:
                ShowInfo(argv[0]);
                return false;
        }
    }
    return true;
}


//Main entry point
//Override the signal handler - sole purpose so Makefile exits cleanly when sigint is raised
int main(int argc, char* argv[])
{
    std::signal(SIGINT, sighandler);

    std::string fileName = "";
    if(ParseArgs(argc, argv, fileName))
    {
        try
        {
            std::unique_ptr<MatrixMenu> menu;
            menu = fileName.empty() ? make_unique<MatrixMenu>() : make_unique<MatrixMenu>(fileName);
            menu->Start();
        }
        catch(...)
        {
            std::cout << "FATAL EXCEPTION: Uknown Error!" << std::endl;
        }
    }
    return 0;
};
