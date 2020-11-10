# Homework1PartB: Matrix

## TODO
- [x] Write Matrix Library
- [x] Write unit tests for Matrix
- [x] Write menu interface
- [x] Write a script to install google test or document steps
- [x] Populate README.md

## Preqrequistes
Install google test
    - 1. `sudo apt-get install googletest cmake -y`
    - 2. `cd /usr/src/googletest`
    - 3. `sudo mkdir build`
    - 4. `cd build`
    - 5. `sudo cmake ..`
    - 6. `sudo make`
    - 7. `sudo cp googlemock/*.a googlemock/gtest/*.a /usr/lib`


## How to build and differentw ways to run:
1. `make clean ; make -j8`
> Running make's default will compile all targets (src and unit tests) and execute the binaries for you
2. `make hw1.out`
> Running the make target `hw1.out` will compile only the source (just in case we have difficulty compiling the unit tests)
> Execute the binary as `hw1.out` or `hw1.out -f <relative_path_to_data_file>
3. `make test_runner`
> Running the make target `test_runner` will compile only the unit tests along with the matrix library from src

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


## How to quit out of the program:
Keystroke: `ctrl+c`


### How to improve this program:
1. Support Matrix Scalar inside the Matrix Menu without constructing a 1x1 matrix
2. Ensure data reaches the disk - file can be corrupted
3. Buff up unit test with more test cases - test negative paths
4. Improve MatrixMenu to support different data types - right now it's hard coded to floats
5. Improve MatrixMenu by removing a lot of redundant statements, espeically the ProcessFile
