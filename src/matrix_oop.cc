#include "matrix_oop.h"

/*  CONSTRUCTORS AND DESTRUCTORS  */
S21Matrix::S21Matrix() {
  rows_ = 0;
  cols_ = 0;
  CreateMatrix();
}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  CreateMatrix();
}

S21Matrix::S21Matrix(const S21Matrix &other) : rows_(other.rows_), cols_(other.cols_){
  this->CreateMatrix();
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = other.operator()(i, j);
    }
  }
}

S21Matrix::S21Matrix(S21Matrix &&other) {
  if (this != &other) {
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.cols_ = 0;
    other.rows_ = 0;
    other.matrix_ = nullptr;
  }
}

S21Matrix::~S21Matrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  delete[] matrix_;
}
/*  /CONSTRUCTORS AND DESTRUCTORS  */

/*  OPERATIONS  */
bool S21Matrix::EqMatrix(const S21Matrix &other) {
  bool result = true;
  if (cols_ == other.cols_ && rows_ == other.rows_) {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        if (fabs(matrix_[i][j] - other.operator()(i, j)) >= 1e-7) {
          result = false;
          break;
        }
      }
      if (!result) break;
    }
  } else {
    result = false;
  }
  return result;
}

void S21Matrix::SumMatrix(const S21Matrix &other) {
  if (!(matrix_ && other.matrix_ && rows_ > 0 && cols_ > 0 && other.rows_ > 0 &&
        other.cols_ > 0)) {
    throw std::length_error("Incorrect input matrix.");
  } else if (!(rows_ == other.rows_ && cols_ == other.cols_)) {
    throw std::length_error("Different matrix size.");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = (matrix_[i][j] + other.operator()(i, j));
      }
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix &other) {
  if (!(matrix_ && other.matrix_ && rows_ > 0 && cols_ > 0 && other.rows_ > 0 &&
        other.cols_ > 0)) {
    throw std::length_error("Incorrect input matrix.");
  } else if (!(rows_ == other.rows_ && cols_ == other.cols_)) {
    throw std::length_error("Different matrix size.");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = (matrix_[i][j] - other.operator()(i, j));
      }
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  if (!(matrix_ && rows_ > 0 && cols_ > 0)) {
    throw std::length_error("Incorrect input matrix.");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = (matrix_[i][j] * num);
      }
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix &other) {
  if (!(matrix_ && other.matrix_ && rows_ > 0 && cols_ > 0 && other.rows_ > 0 &&
        other.cols_ > 0)) {
    throw std::length_error("Incorrect input matrix.");
  }
  if (cols_ != other.rows_) {
    throw std::length_error("Incorrect matrix size");
  }
  S21Matrix result(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        result.matrix_[i][j] += matrix_[i][k] * other.operator()(k, j);
      }
    }
  }
  *this = result;
}

S21Matrix S21Matrix::Transpose() {
  if (!(matrix_ && rows_ > 0 && cols_ > 0)) {
    throw std::length_error("Incorrect input matrix.");
  }

  S21Matrix result(cols_, rows_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      result.matrix_[j][i] = matrix_[i][j];
    }
  }
  return result;
}

double S21Matrix::Determinant() {
  double det = 0.0, tmpDet = 0.0;
  if (matrix_ && rows_ == 0 && cols_ == 0) {
    throw std::length_error("Incorrect input matrix.");
  } else if (rows_ != cols_) {
    throw std::length_error("Matrix is not square.");
  } else {
    if (rows_ == 1) {
      det = matrix_[0][0];
    } else if (rows_ == 2) {
      det = (matrix_[0][0] * matrix_[1][1]) - (matrix_[1][0] * matrix_[0][1]);
    } else {
      int ii, jj, di = 0, dj;
      S21Matrix tmpM(rows_ - 1, cols_ - 1);
      for (int i = 0; i < rows_; i++) {
        for (ii = 0; ii < rows_ - 1; ii++) {
          if (ii == rows_) di = 1;
          dj = 0;
          for (jj = 0; jj < cols_ - 1; jj++) {
            if (jj == cols_) dj = 1;
            tmpM.matrix_[ii][jj] = matrix_[ii + di][jj + dj];
          }
        }
        tmpDet = tmpM.Determinant();
        det += matrix_[0][i] * pow(-1, i) * tmpDet;
      }
    }
  }
  return det;
}

S21Matrix S21Matrix::CalcComplements() {
  S21Matrix result(rows_, cols_);
  if (!(matrix_ && rows_ > 1 && cols_ > 1)) {
    throw std::length_error("Incorrect input matrix.");
  } else if (rows_ != cols_) {
    throw std::length_error("Matrix is not square.");
  } else {
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        S21Matrix matrixMinors = Minor(i, j);
        double det = matrixMinors.Determinant();
        det *= pow(-1, 2 + i + j);
        result.matrix_[i][j] = det;
      }
    }
  }
  return result;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (rows_ != cols_) {
    throw std::length_error("Incorrect input matrix.");
  }
  const double determinant = Determinant();
  if (determinant == 0.0) {
    throw std::length_error("Determinant shouldn't be a zero.");
  }
  const double det = 1 / determinant;
  S21Matrix tmp(CalcComplements());
  S21Matrix result(tmp.Transpose());
  result.MulNumber(det);
  return result;
}
/*  /OPERATIONS  */

/*  OPERATORS */
S21Matrix S21Matrix::operator+(const S21Matrix &other) {
  S21Matrix result(rows_, cols_);
  result.SumMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator-(const S21Matrix &other) {
  S21Matrix result(rows_, cols_);
  result.SubMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const S21Matrix &other) {
  S21Matrix result(rows_, cols_);
  result.MulMatrix(other);
  return result;
}

S21Matrix S21Matrix::operator*(const double number) {
  S21Matrix result(rows_, cols_);
  result.MulNumber(number);
  return result;
}

S21Matrix operator*(const double num, S21Matrix &A) {
  S21Matrix sol(A);
  sol.MulNumber(num);
  return sol;
}

S21Matrix &S21Matrix::operator=(const S21Matrix &other) {
  if (this != &other) {
    DeleteMatrix(*this);
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = new double *[other.rows_];
    for (int i = 0; i < other.rows_; i++) {
      matrix_[i] = new double[other.cols_];
    }
    for (int i = 0; i < rows_; i++) {
      for (int j = 0; j < cols_; j++) {
        matrix_[i][j] = other.operator()(i, j);
      }
    }
  }
  return *this;
}

S21Matrix &S21Matrix::operator=(S21Matrix &&other) noexcept {
  if (this != &other) {
    DeleteMatrix(*this);
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.cols_ = 0;
    other.rows_ = 0;
    other.matrix_ = nullptr;
  }
  return *this;
}

bool S21Matrix::operator==(const S21Matrix &other) {
  return this->EqMatrix(other);
}

S21Matrix S21Matrix::operator+=(const S21Matrix &other) {
  SumMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator-=(const S21Matrix &other) {
  SubMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const S21Matrix &other) {
  MulMatrix(other);
  return *this;
}

S21Matrix S21Matrix::operator*=(const double number) {
  MulNumber(number);
  return *this;
}

double &S21Matrix::operator()(int i, int j) {
  if (i >= rows_ || j >= cols_) {
    throw std::logic_error("\nIndex out of range\n");
  }
  return matrix_[i][j];
}

double &S21Matrix::operator()(int i, int j) const {
  if (i >= rows_ || j >= cols_) {
    throw std::logic_error("\nIndex out of range\n");
  }
  return matrix_[i][j];
}
/*  /OPERATORS */

/*  ADDITIONS  */
void S21Matrix::CreateMatrix() {
  matrix_ = new double *[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

void S21Matrix::FillNumber(double x) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] = x;
    }
  }
}

S21Matrix S21Matrix::Minor(int i, int j) {
  S21Matrix result(rows_ - 1, cols_ - 1);
  int i_counter = 0, j_counter = 0;
  for (int k = 0; k < rows_; k++) {
    if (k == i) continue;
    for (int l = 0; l < cols_; l++) {
      if (l == j) continue;
      result.matrix_[i_counter][j_counter] = matrix_[k][l];
      j_counter++;
    }
    j_counter = 0;
    i_counter++;
  }
  return result;
}

void S21Matrix::DeleteMatrix(S21Matrix &other) {
  for (int i = 0; i < other.rows_; i++) {
    delete[] other.matrix_[i];
  }
  delete[] other.matrix_;
}

int S21Matrix::GetRows() const { return rows_; }

int S21Matrix::GetCols() const { return cols_; }

void S21Matrix::SetRows(int rows) {
  if (rows <= 0)
    throw std::out_of_range("Incorrect input, size should be positive");
  if (rows != rows_) {
    double **result = new double *[rows];
    for (int i = 0; i < rows; i++) {
      result[i] = new double[cols_];
      for (int j = 0; j < cols_; j++) {
        if (i < rows_) {
          result[i][j] = matrix_[i][j];
        } else {
          result[i][j] = 0;
        }
      }
    }
    DeleteMatrix(*this);
    rows_ = rows;
    matrix_ = result;
  }
}

void S21Matrix::SetCols(int cols) {
  if (cols <= 0)
    throw std::out_of_range("Incorrect input, size should be positive");
  if (cols != cols_) {
    double **result = new double *[rows_];
    for (int i = 0; i < rows_; i++) {
      result[i] = new double[cols];
      for (int j = 0; j < cols; j++) {
        if (j < cols_) {
          result[i][j] = matrix_[i][j];
        } else {
          result[i][j] = 0;
        }
      }
    }
    DeleteMatrix(*this);
    cols_ = cols;
    matrix_ = result;
  }
}
/*  /ADDITIONS  */