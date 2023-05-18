# matrix+

## Information

### C++ and C

C++ is a programming language based on the C language for implementing programs using an object-oriented approach. This means that the C++ syntax rules are directly derived from C, and so, most of the C code can be copied into programs with C++ and successfully compiled.
For the most part, C++ only adds new opportunities for the programmer or modifies them rather than removes something, so when it comes to C++, it's easier to talk about the differences (see materials) than the similarities.

### An example of a matrix class in C++
```cpp
class Matrix {
    private:
        // Attributes
        int rows_, cols_;         // Rows and columns
        double **matrix_;         // Pointer to the memory where the matrix is allocated

    public:
        Matrix();              // Default constructor
        ~Matrix();             // Destructor

        void SumMatrix(const Matrix& other); 
        // Other methods..
}
```

## Matrix operations

There is a brief description of the matrix operations below that need to be implemented in the developing library.
They are similar to the operations you performed earlier in «structured programming», so you can see a more detailed description of them there.
Note that some operations have exceptional situations that require special handling using the exception mechanism.

| Operation | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `bool EqMatrix(const Matrix& other)` | Checks matrices for equality with each other |  |
| `void SumMatrix(const Matrix& other)` | Adds the second matrix to the current one | different matrix dimensions |
| `void SubMatrix(const Matrix& other)` | Subtracts another matrix from the current one | different matrix dimensions |
| `void MulNumber(const double num) ` | Multiplies the current matrix by a number |  |
| `void MulMatrix(const Matrix& other)` | Multiplies the current matrix by the second matrix | the number of columns of the first matrix is not equal to the number of rows of the second matrix |
| `Matrix Transpose()` | Creates a new transposed matrix from the current one and returns it |  |
| `Matrix CalcComplements()` | Calculates the algebraic addition matrix of the current one and returns it | the matrix is not square |
| `double Determinant()` | Calculates and returns the determinant of the current matrix | the matrix is not square |
| `Matrix InverseMatrix()` | Calculates and returns the inverse matrix | matrix determinant is 0 |

Apart from those operations, you also need to implement constructors and destructors:

| Method | Description |
| ----------- | ----------- |
| `Matrix()` | A basic constructor that initialises a matrix of some predefined dimension |  
| `Matrix(int rows, int cols) ` | Parametrized constructor with number of rows and columns |
| `Matrix(const Matrix& other)` | Copy constructor |
| `Matrix(Matrix&& other)` | Move constructor |
| `~Matrix()` | Destructor |

And you also need to overload the following operators, partly corresponding to the operations above:

| Operator | Description | Exceptional situations |
| ----------- | ----------- | ----------- |
| `+`      | Addition of two matrices | different matrix dimensions |
| `-`   | Subtraction of one matrix from another | different matrix dimensions |
| `*`  | Matrix multiplication and matrix multiplication by a number | the number of columns of the first matrix does not equal the number of rows of the second matrix |
| `==`  | Checks for matrices equality (`EqMatrix`) | |
| `=`  | Assignment of values from one matrix to another one | |
| `+=`  | Addition assignment (`SumMatrix`) | different matrix dimensions |
| `-=`  | Difference assignment (`SubMatrix`) | different matrix dimensions |
| `*=`  | Multiplication assignment (`MulMatrix`/`MulNumber`) | the number of columns of the first matrix does not equal the number of rows of the second matrix |
| `(int i, int j)`  | Indexation by matrix elements (row, column) | index is outside the matrix |

## Implementation of the matrix_oop.h library functions

- The program must be developed in C++ language of C++17 standard using gcc compiler
- The program code must be located in the src folder
- When writing code it is necessary to follow the Google style
- Implement the matrix as an `Matrix` class
- Use only the `matrix_`, `rows_` and `cols_` fields as private.
- Implement the access to private fields `rows_` and `cols_` via accessor and mutator. If the matrix increases in size, it is filled with zeros. If it decreases in size, the excess is simply discarded.
- Make it as a static library (with matrix_oop.h header file)
- Implement the operations described [above](#matrix-operations)
- Overload the operators according to the table in the chapter [above](#matrix-operations)
- Prepare full coverage of library functions code with unit-tests using the GTest library
- Provide a Makefile for building the library and tests (with targets all, clean, test, matrix_oop.a)
