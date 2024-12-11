#include "s21_matrix_oop.h"

/*default constructor*/
S21Matrix::S21Matrix() : rows_(2), cols_(2) {
  this->matrix = new double*[this->rows_];
  for (int i = 0; i < this->rows_; i++) {
    matrix[i] = new double[this->cols_]{0};
  }
}

/*constructor
creates matrix with y rows and x columns*/
S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 || cols <= 0)
    throw invalid_argument("Incorrect matrix size, rows and cols must be >= 0");
  this->matrix = new double*[this->rows_];
  for (int i = 0; i < this->rows_; i++) {
    matrix[i] = new double[this->cols_]{0};
  }
}

/*constructor
creates a matrix copy from another*/
S21Matrix::S21Matrix(const S21Matrix& another)
    : rows_(another.rows_), cols_(another.cols_) {
  Copy(another);
}

/*constructor
moves a matrix from another*/
S21Matrix::S21Matrix(S21Matrix&& another)
    : rows_(another.rows_), cols_(another.cols_) {
  Move(another);
}

/*destructor
frees memory allocated for matrix*/
S21Matrix::~S21Matrix() {
  if (this->matrix) {
    for (int i = 0; i < this->rows_; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
}

/*operation
checks if matrix is equal to another*/
bool S21Matrix::EqMatrix(const S21Matrix& another) {
  bool equal = true;
  if (this->rows_ != another.rows_ || this->cols_ != another.cols_) {
    equal = false;
  } else {
    for (int i = 0; i < this->rows_ && equal == true; i++) {
      for (int j = 0; j < this->cols_ && equal == true; j++) {
        if (fabs(this->matrix[i][j] - another.matrix[i][j]) > 0.00000009)
          equal = false;
      }
    }
  }
  return equal;
}

/*operation
adds another matrix to matrix*/
void S21Matrix::SumMatrix(const S21Matrix& another) {
  if (this->rows_ != another.rows_ || this->cols_ != another.cols_)
    throw invalid_argument(
        "Sizes of matrixes differ, please add only equal size matrix");
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix[i][j] += another.matrix[i][j];
    }
  }
}

/*operation
substruct another matrix from matrix*/
void S21Matrix::SubMatrix(const S21Matrix& another) {
  if (this->rows_ != another.rows_ || this->cols_ != another.cols_)
    throw invalid_argument(
        "Sizes of matrixes differ, please substruct only equal size matrix");
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix[i][j] -= another.matrix[i][j];
    }
  }
}

/*operation
multiply a matrix to number*/
void S21Matrix::MulNumber(const double num) {
  if (isinf(num) || isnan(num)) throw invalid_argument("Invalid double number");
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      this->matrix[i][j] *= num;
    }
  }
}

/*operation
multiply a matrix to another matrix*/
void S21Matrix::MulMatrix(const S21Matrix& another) {
  if (this->cols_ != another.rows_)
    throw invalid_argument(
        "The number of columns in matrix_1 must be equal to number of rows in "
        "matrix_2");
  S21Matrix tmp_matrix(this->rows_, another.cols_);
  for (int i = 0; i < tmp_matrix.rows_; i++) {
    for (int j = 0; j < tmp_matrix.cols_; j++) {
      for (int k = 0; k < this->cols_; k++) {
        tmp_matrix.matrix[i][j] += this->matrix[i][k] * another.matrix[k][j];
      }
    }
  }
  *this = tmp_matrix;
}

/*operation
returns a new transposed matrix*/
S21Matrix S21Matrix::Transpose() {
  S21Matrix t_matrix(this->cols_, this->rows_);
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      t_matrix.matrix[j][i] = this->matrix[i][j];
    }
  }
  return t_matrix;
}

/*operation
returns a matrix determinant*/
double S21Matrix::Determinant() {
  if (this->rows_ != this->cols_)
    throw invalid_argument(
        "To calculate determinant equal number of rows and cols are required");
  double determ = 0;
  if (this->rows_ == 1) {
    determ = this->matrix[0][0];
  } else if (this->rows_ == 2) {
    determ = this->matrix[0][0] * this->matrix[1][1] -
             this->matrix[1][0] * this->matrix[0][1];
  } else {
    for (int k = 0; k < this->rows_; k++) {
      S21Matrix minor = this->Fill_minor(0, k);
      if (k % 2 == 0) {
        determ += this->matrix[0][k] * minor.Determinant();
      } else {
        determ += this->matrix[0][k] * minor.Determinant() * (-1);
      }
    }
  }
  return determ;
}

/*operation
returns a minor matrix*/
S21Matrix S21Matrix::Fill_minor(int m_rows, int m_cols) {
  if (this->rows_ != this->cols_)
    throw invalid_argument(
        "To calculate minor matrix equal number of rows and cols are required");
  S21Matrix minor(this->rows_ - 1, this->cols_ - 1);
  int row = 0, column = 0;
  for (int i = 0; i < this->rows_; i++) {
    for (int j = 0; j < this->cols_; j++) {
      if (i != m_rows && j != m_cols) {
        minor.matrix[row][column] = this->matrix[i][j];
        column++;
      }
    }
    if (column) row++;
    column = 0;
  }
  return minor;
}

/*operation
returns a matrix of algebraic complements*/
S21Matrix S21Matrix::CalcComplements() {
  if (this->rows_ != this->cols_)
    throw invalid_argument(
        "To calculate algebraic complements equal number of rows and cols are "
        "required");
  S21Matrix m_complements(this->rows_, this->cols_);
  if (this->rows_ == 1) {
    m_complements.matrix[0][0] = this->matrix[0][0];
  } else {
    for (int m_rows = 0; m_rows < this->rows_; m_rows++) {
      for (int m_cols = 0; m_cols < this->cols_; m_cols++) {
        S21Matrix minor = this->Fill_minor(m_rows, m_cols);
        double det = minor.Determinant();
        if ((m_rows + m_cols) % 2 != 0) det *= (-1);
        m_complements.matrix[m_rows][m_cols] = det;
      }
    }
  }
  return m_complements;
}

/*operation
returns an inverse matrix*/
S21Matrix S21Matrix::InverseMatrix() {
  if (this->rows_ != this->cols_)
    throw invalid_argument(
        "To calculate an inverse matrix equal number of rows and cols are "
        "required");
  double dtrm = this->Determinant();
  if (!dtrm || isnan(dtrm) || isinf(dtrm)) {
    throw invalid_argument(
        "Unable to find inverse matrix due to invalid matrix determinant");
  }
  S21Matrix m_inverse(this->rows_, this->cols_);
  if (this->rows_ == 1) {
    m_inverse.matrix[0][0] = 1.0 / dtrm;
  } else {
    S21Matrix m_complements = this->CalcComplements();
    S21Matrix m_transposed = m_complements.Transpose();
    m_transposed.MulNumber(1.0 / dtrm);
    m_inverse = m_transposed;
  }
  return m_inverse;
}

/*method
creates a matrix copy from another*/
void S21Matrix::Copy(const S21Matrix& another) {
  this->rows_ = another.rows_;
  this->cols_ = another.cols_;
  this->matrix = new double*[this->rows_];
  memcpy(this->matrix, another.matrix, this->rows_ * sizeof(double*));
  for (int i = 0; i < this->rows_; i++) {
    matrix[i] = new double[this->cols_];
    memcpy(this->matrix[i], another.matrix[i], this->cols_ * sizeof(double));
  }
}

/*method
moves a matrix from another*/
void S21Matrix::Move(const S21Matrix& another) {
  this->rows_ = another.rows_;
  this->cols_ = another.cols_;
  this->matrix = new double*[this->rows_];
  memmove(this->matrix, another.matrix, this->rows_ * sizeof(double*));
  for (int i = 0; i < this->rows_; i++) {
    matrix[i] = new double[this->cols_];
    memmove(this->matrix[i], another.matrix[i], this->cols_ * sizeof(double));
  }
}

/*operator
returns matrix element by row and col number*/
double& S21Matrix::operator()(int row, int col) {
  if (row > this->rows_ - 1 || row < 0 || col > this->cols_ - 1 || col < 0)
    throw invalid_argument("Matrix index out of bounds");
  return this->matrix[row][col];
}

/*operator
writes another matrix to current matrix*/
S21Matrix S21Matrix::operator=(const S21Matrix& another) {
  if (this->matrix) {
    for (int i = 0; i < this->rows_; i++) {
      delete[] matrix[i];
    }
    delete[] matrix;
  }
  Copy(another);
  return *this;
}

/*operator
returns the result of matrix addition*/
S21Matrix S21Matrix::operator+(const S21Matrix& o) {
  S21Matrix res(*this);
  res.SumMatrix(o);
  return res;
}

/*operator
returns the result of matrix substruction*/
S21Matrix S21Matrix::operator-(const S21Matrix& o) {
  S21Matrix res(*this);
  res.SubMatrix(o);
  return res;
}

/*operator
returns the result of multiplication matrix on number*/
S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix res(*this);
  res.MulNumber(num);
  return res;
}

/*operator
returns the result of matrix multiplication*/
S21Matrix S21Matrix::operator*(const S21Matrix& o) {
  S21Matrix res(*this);
  res.MulMatrix(o);
  return res;
}

/*operator
returns true if matrix are equal*/
bool S21Matrix::operator==(const S21Matrix& o) { return this->EqMatrix(o); }

/*operator
Adds another matrix to matrix*/
S21Matrix& S21Matrix::operator+=(const S21Matrix& another) {
  this->SumMatrix(another);
  return (*this);
}

/*operator
Substruct another matrix from matrix*/
S21Matrix& S21Matrix::operator-=(const S21Matrix& another) {
  this->SubMatrix(another);
  return (*this);
}

/*operator
Multiply another matrix on matrix*/
S21Matrix& S21Matrix::operator*=(const S21Matrix& another) {
  this->MulMatrix(another);
  return (*this);
}

/*operator
Multiply matrix on number*/
S21Matrix& S21Matrix::operator*=(const double num) {
  this->MulNumber(num);
  return (*this);
}

/*accessor
Returns the number of rows*/
int S21Matrix::get_rows() { return rows_; }

/*accessor
Returns the number of cols*/
int S21Matrix::get_cols() { return cols_; }

/*mutator
Sets a new row number*/
void S21Matrix::set_rows(const int n_rows) {
  if (n_rows <= 0) {
    throw std::invalid_argument("Row number must be greater than 0");
  } else {
    S21Matrix tmp(n_rows, this->cols_);
    for (int i = 0; i < (this->rows_ < n_rows ? this->rows_ : n_rows); i++) {
      for (int j = 0; j < this->cols_; j++) {
        tmp.matrix[i][j] = this->matrix[i][j];
      }
    }
    *this = tmp;
  }
}

/*mutator
Sets a new col number*/
void S21Matrix::set_cols(const int n_cols) {
  if (n_cols <= 0) {
    throw std::invalid_argument("Col number must be greater than 0");
  } else {
    S21Matrix tmp(this->rows_, n_cols);
    for (int i = 0; i < this->rows_; i++) {
      for (int j = 0; j < (this->cols_ < n_cols ? this->cols_ : n_cols); j++) {
        tmp.matrix[i][j] = this->matrix[i][j];
      }
    }
    *this = tmp;
  }
}