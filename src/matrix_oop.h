#ifndef S21_MATRIX_OOP_H
#define S21_MATRIX_OOP_H

#include <cmath>
#include <cstring>
#include <iostream>

class S21Matrix {
 public:
  /*  CONSTRUCTORS AND DESTRUCTOR  */
  S21Matrix();
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix &other);  // Консруктор копирования
  S21Matrix(S21Matrix &&other);  // Конструктор перемещения
  ~S21Matrix();                  // Деструктор
  /*  /CONSTRUCTORS AND DESTRUCTOR  */

  /*  OPERATIONS  */
  bool EqMatrix(const S21Matrix &other);
  void SumMatrix(const S21Matrix &other);
  void SubMatrix(const S21Matrix &other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix &other);
  S21Matrix Transpose();
  S21Matrix CalcComplements();
  double Determinant();
  S21Matrix InverseMatrix();
  /*  /OPERATIONS  */

  /*  OPERATORS */
  S21Matrix operator+(const S21Matrix &other);
  S21Matrix operator-(const S21Matrix &other);
  S21Matrix operator*(const S21Matrix &other);
  S21Matrix operator*(const double number);
  friend S21Matrix operator*(const double num, S21Matrix &A);
  S21Matrix &operator=(
      const S21Matrix &other);  // Оператор присваивания копированием
  S21Matrix &operator=(
      S21Matrix &&other) noexcept;  // Оператор присваивания перемещения
  bool operator==(const S21Matrix &other);
  S21Matrix operator+=(const S21Matrix &other);
  S21Matrix operator-=(const S21Matrix &other);
  S21Matrix operator*=(const S21Matrix &other);
  S21Matrix operator*=(const double number);
  double &operator()(int i, int j);
  double &operator()(int i, int j) const;
  /*  /OPERATORS */

  /*  ADDITIONS  */
  void FillNumber(double x);
  int GetRows() const;
  int GetCols() const;
  void SetRows(int rows);
  void SetCols(int cols);
  /*  /ADDITIONS  */

 private:
  double **matrix_;
  int rows_, cols_;

  /*  ADDITIONS  */
  void CreateMatrix();
  S21Matrix Minor(int i, int j);
  void DeleteMatrix(S21Matrix &other);
  /*  /ADDITIONS  */
};

#endif