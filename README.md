# Homework1PartB: Matrix

## TODO
- [x] Write Matrix Library
- [x] Write unit tests for Matrix
- [x] Write menu interface
- [ ] Fix the menu interface - it should not prompt when rotating an image
- [ ] Fix bugs for menu interface
- [ ] Write a script to install google test or document steps
- [ ] Populate README.md

## Preqrequistes
Install google test
1. sudo apt-get install googletest -y
2. cd /usr/src/googletest
3. sudo mkdir build
4. cd build
5. sudo cmake ..
6. sudo make
7. sudo cp googlemock/*.a googlemock/gtest/*.a /usr/lib

## How to build and differentw ways to run:
1. `make clean ; make -j8`
> Running make will execute the unit test and run the program
2. `hw1.out`
3. `hw1.out -f <data file>`
> Provide a relative path from where the executable is

## How should the data file be structured - (Currently, not bullet proof)
1. First line has a total of 4 arguments separated by spaces
    - Number of Matrices: 1 or 2
    - Dimension for Matrix A: NxM (where N and M are positie integers)
    - Dimensions for Matrix B: NxM (where N and M are positive integers)
    - Number of Operations to expect
2. Next lines should represent the data (in float) for Matrix A
    - An empty line will represent the end of the Matrix
3. Next lines should represent the data (in float) for Matrix B
    - An empty line will represent the end of the Matrix
4. Next lines should have supported operations:
    - Add
    - Subtract
    - Multiplication
    - Rotate


## How to quit:
Keystroke: `ctrl+c`
