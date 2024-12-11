#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <cmath>
#include <cstring>
#include <iostream>

using namespace std;

class S21Matrix {
 private:
  int rows_, cols_;
  double** matrix;

 public:
  S21Matrix();
  S21Matrix(int x, int y);
  S21Matrix(const S21Matrix& matrix_2);
  S21Matrix(S21Matrix&& matrix_2);
  ~S21Matrix();

  bool EqMatrix(const S21Matrix& another);
  void SumMatrix(const S21Matrix& another);
  void SubMatrix(const S21Matrix& another);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& another);
  S21Matrix Transpose();
  double Determinant();
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();

  void Copy(const S21Matrix& another);
  void Move(const S21Matrix& another);
  S21Matrix Fill_minor(int m_rows, int m_cols);

  double& operator()(int row, int col);
  S21Matrix operator=(const S21Matrix& another);
  S21Matrix operator+(const S21Matrix& o);
  S21Matrix operator-(const S21Matrix& o);
  S21Matrix operator*(const double num);
  S21Matrix operator*(const S21Matrix& o);
  bool operator==(const S21Matrix& o);
  S21Matrix& operator+=(const S21Matrix& another);
  S21Matrix& operator-=(const S21Matrix& another);
  S21Matrix& operator*=(const S21Matrix& another);
  S21Matrix& operator*=(const double num);

  int get_rows();
  int get_cols();
  void set_rows(const int rows_);
  void set_cols(const int cols_);
};

#endif