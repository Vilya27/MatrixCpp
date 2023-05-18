#include <gtest/gtest.h>

#include <cstdlib>
#include <iostream>

#include "s21_matrix_oop.h"

TEST(test_EqMatrix, test1) {
  S21Matrix matrix1(3, 3);
  S21Matrix matrix2(3, 3);
  matrix2.FillNumber(2);
  ASSERT_EQ(matrix2.EqMatrix(matrix1), false);
}

TEST(SubMatrix, test2) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix1(2, 2);
  S21Matrix matrix_res(2, 2);
  matrix.FillNumber(1);
  matrix1.FillNumber(2);
  matrix_res.FillNumber(3);
  matrix_res.SubMatrix(matrix1);
  ASSERT_EQ(matrix_res.EqMatrix(matrix), true);
}

TEST(SumMatrix, test3) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix1(2, 2);
  S21Matrix matrix_res(2, 2);
  matrix.FillNumber(3);
  matrix1.FillNumber(2);
  matrix_res.FillNumber(1);
  matrix_res.SumMatrix(matrix1);
  ASSERT_EQ(matrix_res.EqMatrix(matrix), true);
}

TEST(MulMatrix, test4) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix1(2, 2);
  S21Matrix matrix_res(2, 2);
  matrix.FillNumber(2);
  matrix1.FillNumber(1);
  matrix_res.FillNumber(1);
  matrix_res.MulMatrix(matrix1);
  ASSERT_EQ(matrix_res.EqMatrix(matrix), true);
}

TEST(trans, test5) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix1(2, 2);
  matrix.FillNumber(1);
  matrix1.FillNumber(1);
  matrix.Transpose();
  ASSERT_EQ(matrix.EqMatrix(matrix1), true);
}

TEST(det, test6) {
  S21Matrix matrix(3, 3);
  double matrix_res = 0;
  matrix.FillNumber(1);
  double a = matrix.Determinant();
  EXPECT_EQ(a, matrix_res);
}

TEST(calc, test7) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix1(2, 2);
  matrix.CalcComplements();
  ASSERT_EQ(matrix.EqMatrix(matrix1), true);
}

TEST(inverse, test8) {
  S21Matrix matrix(2, 2);
  S21Matrix matrix1(2, 2);
  matrix(0, 0) = 1;
  matrix(0, 1) = 3;
  matrix(1, 0) = 1;
  matrix(1, 1) = 2;
  matrix1(0, 0) = -2;
  matrix1(0, 1) = 3;
  matrix1(1, 0) = 1;
  matrix1(1, 1) = -1;
  matrix.InverseMatrix();
  ASSERT_EQ(matrix.EqMatrix(matrix1), true);
}

int main(int argc, char *argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
