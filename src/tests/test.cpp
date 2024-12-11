#include <gtest/gtest.h>

#include "../s21_matrix_oop.h"

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Suite_constructor, TestException_1) {
  EXPECT_THROW(
      {
        try {
          S21Matrix m(0, 0);
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ("Incorrect matrix size, rows and cols must be >= 0",
                       e.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(Suite_constructor, TestException_2) {
  EXPECT_THROW(
      {
        try {
          S21Matrix m(1, 0);
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ("Incorrect matrix size, rows and cols must be >= 0",
                       e.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(Suite_constructor, TestException_3) {
  EXPECT_THROW(
      {
        try {
          S21Matrix m(0, 1);
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ("Incorrect matrix size, rows and cols must be >= 0",
                       e.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(Suite_constructor, TestException_4) {
  EXPECT_THROW(
      {
        try {
          S21Matrix m(-1, -123);
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ("Incorrect matrix size, rows and cols must be >= 0",
                       e.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(Suite_constructor, TestException_5) {
  EXPECT_THROW(
      {
        try {
          S21Matrix m(-1, -123);
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ("Incorrect matrix size, rows and cols must be >= 0",
                       e.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(Suite_constructor, TestCreation_1) {
  S21Matrix m;
  EXPECT_EQ(m.get_rows(), 2);
  EXPECT_EQ(m.get_cols(), 2);
}

TEST(Suite_constructor, TestCreation_2) {
  S21Matrix m(1, 1);
  EXPECT_EQ(m.get_rows(), 1);
  EXPECT_EQ(m.get_cols(), 1);
}

TEST(Suite_constructor, TestCreation_3) {
  S21Matrix m(2, 2);
  EXPECT_EQ(m.get_rows(), 2);
  EXPECT_EQ(m.get_cols(), 2);
}

TEST(Suite_constructor, TestCreation_4) {
  S21Matrix m(5, 5);
  EXPECT_EQ(m.get_rows(), 5);
  EXPECT_EQ(m.get_cols(), 5);
}

TEST(Suite_constructor, TestCreation_5) {
  S21Matrix m(10, 13);
  EXPECT_EQ(m.get_rows(), 10);
  EXPECT_EQ(m.get_cols(), 13);
}

TEST(Suite_constructor, TestCopy_1) {
  S21Matrix m(3, 3);
  S21Matrix m2(m);
  EXPECT_EQ(m2.get_rows(), 3);
  EXPECT_EQ(m2.get_cols(), 3);
}

TEST(Suite_constructor, TestCopy_2) {
  S21Matrix m(3, 3);
  m(0, 0) = 4;
  m(0, 1) = -3;
  m(0, 2) = 5;
  S21Matrix m2(m);
  EXPECT_DOUBLE_EQ(m2(0, 0), 4);
  EXPECT_DOUBLE_EQ(m2(0, 1), -3);
  EXPECT_DOUBLE_EQ(m2(0, 2), 5);
}

TEST(Suite_constructor, TestMove_1) {
  S21Matrix m(3, 3);
  S21Matrix m2(std::move(m));
  EXPECT_EQ(m2.get_rows(), 3);
  EXPECT_EQ(m2.get_cols(), 3);
}

TEST(Suite_constructor, TestMove_2) {
  S21Matrix m(3, 3);
  m(0, 0) = 4;
  m(0, 1) = -3;
  m(0, 2) = 5;
  S21Matrix m2(std::move(m));
  EXPECT_EQ(m2(0, 0), 4);
  EXPECT_EQ(m2(0, 1), -3);
  EXPECT_EQ(m2(0, 2), 5);
}

TEST(Suite_operation, TestEqual_1) {
  S21Matrix m(3, 3);
  S21Matrix m2(3, 3);
  EXPECT_EQ(m.EqMatrix(m2), 1);
}

TEST(Suite_operation, TestEqual_2) {
  S21Matrix m(3, 3);
  S21Matrix m2(2, 3);
  EXPECT_EQ(m.EqMatrix(m2), 0);
}

TEST(Suite_operation, TestEqual_3) {
  S21Matrix m(3, 3);
  S21Matrix m2(3, 3);
  m(0, 0) = 5;
  m(0, 1) = 6;
  m(0, 2) = 7;
  m2(0, 0) = 5;
  m2(0, 1) = 6;
  m2(0, 2) = 7;
  EXPECT_EQ(m.EqMatrix(m2), 1);
}

TEST(Suite_operation, TestEqual_4) {
  S21Matrix m(3, 3);
  S21Matrix m2(3, 3);
  m(0, 0) = 5;
  m(0, 1) = 6;
  m(0, 2) = 7;
  m2(0, 0) = 5;
  m2(0, 1) = 6;
  m2(0, 2) = 5;
  EXPECT_EQ(m.EqMatrix(m2), 0);
}

TEST(Suite_operation, TestSum_1) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 1;
  m(1, 0) = 1;
  m(1, 1) = 1;

  m2(0, 0) = 1;
  m2(0, 1) = 1;
  m2(1, 0) = 1;
  m2(1, 1) = 1;

  m.SumMatrix(m2);
  EXPECT_DOUBLE_EQ(m(0, 0), 2);
  EXPECT_DOUBLE_EQ(m(0, 1), 2);
  EXPECT_DOUBLE_EQ(m(1, 0), 2);
  EXPECT_DOUBLE_EQ(m(1, 1), 2);
}

TEST(Suite_operation, TestSum_2) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m.SumMatrix(m2);
}

TEST(Suite_operation, TestSumException_1) {
  EXPECT_THROW(
      {
        try {
          S21Matrix m(2, 3);
          S21Matrix m2(2, 2);

          m.SumMatrix(m2);
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ(
              "Sizes of matrixes differ, please add only equal size matrix",
              e.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(Suite_operation, TestSub_1) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 1;
  m(1, 0) = 1;
  m(1, 1) = 1;

  m2(0, 0) = 1;
  m2(0, 1) = 1;
  m2(1, 0) = 1;
  m2(1, 1) = 1;

  m.SubMatrix(m2);
  EXPECT_DOUBLE_EQ(m(0, 0), 0);
  EXPECT_DOUBLE_EQ(m(0, 1), 0);
  EXPECT_DOUBLE_EQ(m(1, 0), 0);
  EXPECT_DOUBLE_EQ(m(1, 1), 0);
}

TEST(Suite_operation, TestSub_2) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 10;
  m(0, 1) = 20;
  m(1, 0) = 30;
  m(1, 1) = 40;

  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 3;
  m2(1, 1) = 4;

  m.SubMatrix(m2);
  EXPECT_DOUBLE_EQ(m(0, 0), 9);
  EXPECT_DOUBLE_EQ(m(0, 1), 18);
  EXPECT_DOUBLE_EQ(m(1, 0), 27);
  EXPECT_DOUBLE_EQ(m(1, 1), 36);
}

TEST(Suite_operation, TestSubException_1) {
  EXPECT_THROW(
      {
        try {
          S21Matrix m(2, 3);
          S21Matrix m2(2, 2);

          m.SubMatrix(m2);
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ(
              "Sizes of matrixes differ, please substruct only equal size "
              "matrix",
              e.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(Suite_operation, TestMulNumber_1) {
  S21Matrix m(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 1;
  m(1, 0) = 1;
  m(1, 1) = 1;
  double x = 3;
  m.MulNumber(x);

  EXPECT_DOUBLE_EQ(m(0, 0), 3);
  EXPECT_DOUBLE_EQ(m(0, 1), 3);
  EXPECT_DOUBLE_EQ(m(1, 0), 3);
  EXPECT_DOUBLE_EQ(m(1, 1), 3);
}

TEST(Suite_operation, TestMulNumber_2) {
  S21Matrix m(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;
  double x = -1;
  m.MulNumber(x);

  EXPECT_DOUBLE_EQ(m(0, 0), -1);
  EXPECT_DOUBLE_EQ(m(0, 1), -2);
  EXPECT_DOUBLE_EQ(m(1, 0), -3);
  EXPECT_DOUBLE_EQ(m(1, 1), -4);
}

TEST(Suite_operation, TestMulNumber_3) {
  S21Matrix m(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;
  double x = 10;
  m.MulNumber(x);

  EXPECT_DOUBLE_EQ(m(0, 0), 10);
  EXPECT_DOUBLE_EQ(m(0, 1), 20);
  EXPECT_DOUBLE_EQ(m(1, 0), 30);
  EXPECT_DOUBLE_EQ(m(1, 1), 40);
}

TEST(Suite_operation, TestMulNumberException_1) {
  EXPECT_THROW(
      {
        try {
          S21Matrix m(2, 2);
          double x = INFINITY;
          m.MulNumber(x);
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ("Invalid double number", e.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(Suite_operation, TestMulMatrix_1) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 1;
  m(1, 0) = 1;
  m(1, 1) = 1;

  m2(0, 0) = 1;
  m2(0, 1) = 1;
  m2(1, 0) = 1;
  m2(1, 1) = 1;

  m.MulMatrix(m2);
  EXPECT_DOUBLE_EQ(m(0, 0), 2);
  EXPECT_DOUBLE_EQ(m(0, 1), 2);
  EXPECT_DOUBLE_EQ(m(1, 0), 2);
  EXPECT_DOUBLE_EQ(m(1, 1), 2);
}

TEST(Suite_operation, TestMulMatrix_2) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  m2(0, 0) = 2;
  m2(0, 1) = 1;
  m2(1, 0) = -1;
  m2(1, 1) = -2;

  m.MulMatrix(m2);
  EXPECT_DOUBLE_EQ(m(0, 0), 0);
  EXPECT_DOUBLE_EQ(m(0, 1), -3);
  EXPECT_DOUBLE_EQ(m(1, 0), 2);
  EXPECT_DOUBLE_EQ(m(1, 1), -5);
}

TEST(Suite_operation, TestMulMatrixException_1) {
  EXPECT_THROW(
      {
        try {
          S21Matrix m(2, 2);
          S21Matrix m2(3, 2);
          m.MulMatrix(m2);
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ(
              "The number of columns in matrix_1 must be equal to number of "
              "rows in matrix_2",
              e.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(Suite_operation, TestTranspose_1) {
  S21Matrix m(2, 3);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(0, 2) = 3;
  m(1, 0) = 4;
  m(1, 1) = 5;
  m(1, 2) = 6;
  S21Matrix m2 = m.Transpose();

  EXPECT_DOUBLE_EQ(m2(0, 0), 1);
  EXPECT_DOUBLE_EQ(m2(0, 1), 4);
  EXPECT_DOUBLE_EQ(m2(1, 0), 2);
  EXPECT_DOUBLE_EQ(m2(1, 1), 5);
  EXPECT_DOUBLE_EQ(m2(2, 0), 3);
  EXPECT_DOUBLE_EQ(m2(2, 1), 6);
}

TEST(Suite_operation, TestTranspose_2) {
  S21Matrix m(3, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;
  m(2, 0) = 5;
  m(2, 1) = 6;
  S21Matrix m2 = m.Transpose();

  EXPECT_DOUBLE_EQ(m2(0, 0), 1);
  EXPECT_DOUBLE_EQ(m2(0, 1), 3);
  EXPECT_DOUBLE_EQ(m2(0, 2), 5);
  EXPECT_DOUBLE_EQ(m2(1, 0), 2);
  EXPECT_DOUBLE_EQ(m2(1, 1), 4);
  EXPECT_DOUBLE_EQ(m2(1, 2), 6);
}

TEST(Suite_operation, TestDeterminant_1) {
  S21Matrix m(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  double d = m.Determinant();

  EXPECT_DOUBLE_EQ(d, -2.0);
}

TEST(Suite_operation, TestDeterminant_2) {
  S21Matrix m(3, 3);

  m(0, 0) = 3;
  m(0, 1) = 4;
  m(0, 2) = 5;
  m(1, 0) = 1;
  m(1, 1) = 2;
  m(1, 2) = 3;
  m(2, 0) = 6;
  m(2, 1) = 7;
  m(2, 2) = 8;

  double d = m.Determinant();

  EXPECT_DOUBLE_EQ(d, 0.0);
}

TEST(Suite_operation, TestDeterminant_3) {
  S21Matrix m(3, 3);

  m(0, 0) = 3;
  m(0, 1) = 4;
  m(0, 2) = -5;
  m(1, 0) = 1;
  m(1, 1) = -2;
  m(1, 2) = 3;
  m(2, 0) = -6;
  m(2, 1) = 7;
  m(2, 2) = 8;

  double d = m.Determinant();

  EXPECT_DOUBLE_EQ(d, -190.0);
}

TEST(Suite_operation, TestDeterminantException_1) {
  EXPECT_THROW(
      {
        try {
          S21Matrix m(3, 4);
          m.Determinant();
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ(
              "To calculate determinant equal number of rows and cols are "
              "required",
              e.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(Suite_operation, TestCalcComplements_1) {
  S21Matrix m(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  S21Matrix m2 = m.CalcComplements();

  EXPECT_DOUBLE_EQ(m2(0, 0), 4);
  EXPECT_DOUBLE_EQ(m2(0, 1), -3);
  EXPECT_DOUBLE_EQ(m2(1, 0), -2);
  EXPECT_DOUBLE_EQ(m2(1, 1), 1);
}

TEST(Suite_operation, TestCalcComplements_2) {
  S21Matrix m(3, 3);

  m(0, 0) = 3;
  m(0, 1) = 4;
  m(0, 2) = -5;
  m(1, 0) = 1;
  m(1, 1) = -2;
  m(1, 2) = 3;
  m(2, 0) = -6;
  m(2, 1) = 7;
  m(2, 2) = 8;

  S21Matrix m2 = m.CalcComplements();

  EXPECT_DOUBLE_EQ(m2(0, 0), -37);
  EXPECT_DOUBLE_EQ(m2(0, 1), -26);
  EXPECT_DOUBLE_EQ(m2(0, 2), -5);
  EXPECT_DOUBLE_EQ(m2(1, 0), -67);
  EXPECT_DOUBLE_EQ(m2(1, 1), -6);
  EXPECT_DOUBLE_EQ(m2(1, 2), -45);
  EXPECT_DOUBLE_EQ(m2(2, 0), 2);
  EXPECT_DOUBLE_EQ(m2(2, 1), -14);
  EXPECT_DOUBLE_EQ(m2(2, 2), -10);
}

TEST(Suite_operation, TestCalcComplementsException_1) {
  EXPECT_THROW(
      {
        try {
          S21Matrix m(3, 4);
          S21Matrix m2 = m.CalcComplements();
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ(
              "To calculate algebraic complements equal number of rows and "
              "cols are required",
              e.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(Suite_operation, TestInverseMatrix_1) {
  S21Matrix m(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  S21Matrix m2 = m.InverseMatrix();

  EXPECT_DOUBLE_EQ(m2(0, 0), -2);
  EXPECT_DOUBLE_EQ(m2(0, 1), 1);
  EXPECT_DOUBLE_EQ(m2(1, 0), 1.5);
  EXPECT_DOUBLE_EQ(m2(1, 1), -0.5);
}

TEST(Suite_operation, TestInverseMatrix_2) {
  S21Matrix m(3, 3);

  m(0, 0) = 3;
  m(0, 1) = 4;
  m(0, 2) = -5;
  m(1, 0) = 1;
  m(1, 1) = -2;
  m(1, 2) = 3;
  m(2, 0) = -6;
  m(2, 1) = 7;
  m(2, 2) = 8;

  S21Matrix m2 = m.InverseMatrix();

  EXPECT_LE(std::fabs(m2(0, 0) - 0.194736842105263), 0.00000009);
  EXPECT_LE(std::fabs(m2(0, 1) - 0.352631578947368), 0.00000009);
  EXPECT_LE(std::fabs(m2(0, 2) - (-0.010526315789474)), 0.00000009);
  EXPECT_LE(std::fabs(m2(1, 0) - 0.136842105263158), 0.00000009);
  EXPECT_LE(std::fabs(m2(1, 1) - 0.031578947368421), 0.00000009);
  EXPECT_LE(std::fabs(m2(1, 2) - 0.073684210526316), 0.00000009);
  EXPECT_LE(std::fabs(m2(2, 0) - 0.026315789473684), 0.00000009);
  EXPECT_LE(std::fabs(m2(2, 1) - 0.236842105263158), 0.00000009);
  EXPECT_LE(std::fabs(m2(2, 2) - 0.052631578947368), 0.00000009);
}

TEST(Suite_operation, TestInverseMatrixException_2) {
  EXPECT_THROW(
      {
        try {
          S21Matrix m(2, 2);
          m(0, 0) = 1;
          m(0, 1) = 1;
          m(1, 0) = 1;
          m(1, 1) = 1;
          S21Matrix m2 = m.InverseMatrix();
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ(
              "Unable to find inverse matrix due to invalid matrix determinant",
              e.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(Suite_operation, TestInverseMatrixException_1) {
  EXPECT_THROW(
      {
        try {
          S21Matrix m(3, 4);
          S21Matrix m2 = m.InverseMatrix();
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ(
              "To calculate an inverse matrix equal number of rows and cols "
              "are required",
              e.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(Suite_operator, TestSet_1) {
  S21Matrix m(3, 3);
  S21Matrix m2 = m;
  EXPECT_EQ(m2.get_rows(), 3);
  EXPECT_EQ(m2.get_cols(), 3);
}

TEST(Suite_operator, TestSet_2) {
  S21Matrix m(3, 3);
  m(0, 0) = 4;
  m(0, 1) = -3;
  m(0, 2) = 5;
  S21Matrix m2 = m;
  EXPECT_DOUBLE_EQ(m2(0, 0), 4);
  EXPECT_DOUBLE_EQ(m2(0, 1), -3);
  EXPECT_DOUBLE_EQ(m2(0, 2), 5);
}

TEST(Suite_operator, TestSum_1) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 1;
  m(1, 0) = 1;
  m(1, 1) = 1;

  m2(0, 0) = 1;
  m2(0, 1) = 1;
  m2(1, 0) = 1;
  m2(1, 1) = 1;

  S21Matrix m3 = m + m2;
  EXPECT_DOUBLE_EQ(m3(0, 0), 2);
  EXPECT_DOUBLE_EQ(m3(0, 1), 2);
  EXPECT_DOUBLE_EQ(m3(1, 0), 2);
  EXPECT_DOUBLE_EQ(m3(1, 1), 2);
}

TEST(Suite_operator, TestSum_2) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 3;
  m2(1, 1) = 4;

  S21Matrix m3 = m + m2;
  EXPECT_DOUBLE_EQ(m3(0, 0), 2);
  EXPECT_DOUBLE_EQ(m3(0, 1), 4);
  EXPECT_DOUBLE_EQ(m3(1, 0), 6);
  EXPECT_DOUBLE_EQ(m3(1, 1), 8);
}

TEST(Suite_operator, TestSub_1) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 1;
  m(1, 0) = 1;
  m(1, 1) = 1;

  m2(0, 0) = 1;
  m2(0, 1) = 1;
  m2(1, 0) = 1;
  m2(1, 1) = 1;

  S21Matrix m3 = m - m2;
  EXPECT_DOUBLE_EQ(m3(0, 0), 0);
  EXPECT_DOUBLE_EQ(m3(0, 1), 0);
  EXPECT_DOUBLE_EQ(m3(1, 0), 0);
  EXPECT_DOUBLE_EQ(m3(1, 1), 0);
}

TEST(Suite_operator, TestSub_2) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 10;
  m(0, 1) = 20;
  m(1, 0) = 30;
  m(1, 1) = 40;

  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 3;
  m2(1, 1) = 4;

  S21Matrix m3 = m - m2;
  EXPECT_DOUBLE_EQ(m3(0, 0), 9);
  EXPECT_DOUBLE_EQ(m3(0, 1), 18);
  EXPECT_DOUBLE_EQ(m3(1, 0), 27);
  EXPECT_DOUBLE_EQ(m3(1, 1), 36);
}

TEST(Suite_operator, TestMulNumber_1) {
  S21Matrix m(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 1;
  m(1, 0) = 1;
  m(1, 1) = 1;
  double x = 3;
  S21Matrix m3 = m * x;

  EXPECT_DOUBLE_EQ(m3(0, 0), 3);
  EXPECT_DOUBLE_EQ(m3(0, 1), 3);
  EXPECT_DOUBLE_EQ(m3(1, 0), 3);
  EXPECT_DOUBLE_EQ(m3(1, 1), 3);
}

TEST(Suite_operator, TestMulNumber_2) {
  S21Matrix m(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;
  double x = -1;
  S21Matrix m3 = m * x;

  EXPECT_DOUBLE_EQ(m3(0, 0), -1);
  EXPECT_DOUBLE_EQ(m3(0, 1), -2);
  EXPECT_DOUBLE_EQ(m3(1, 0), -3);
  EXPECT_DOUBLE_EQ(m3(1, 1), -4);
}

TEST(Suite_operator, TestMulNumber_3) {
  S21Matrix m(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;
  double x = 10;
  S21Matrix m3 = m * x;

  EXPECT_DOUBLE_EQ(m3(0, 0), 10);
  EXPECT_DOUBLE_EQ(m3(0, 1), 20);
  EXPECT_DOUBLE_EQ(m3(1, 0), 30);
  EXPECT_DOUBLE_EQ(m3(1, 1), 40);
}

TEST(Suite_operator, TestMulMatrix_1) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 1;
  m(1, 0) = 1;
  m(1, 1) = 1;

  m2(0, 0) = 1;
  m2(0, 1) = 1;
  m2(1, 0) = 1;
  m2(1, 1) = 1;

  S21Matrix m3 = m * m2;
  EXPECT_DOUBLE_EQ(m3(0, 0), 2);
  EXPECT_DOUBLE_EQ(m3(0, 1), 2);
  EXPECT_DOUBLE_EQ(m3(1, 0), 2);
  EXPECT_DOUBLE_EQ(m3(1, 1), 2);
}

TEST(Suite_operator, TestMulMatrix_2) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  m2(0, 0) = 2;
  m2(0, 1) = 1;
  m2(1, 0) = -1;
  m2(1, 1) = -2;

  S21Matrix m3 = m * m2;
  EXPECT_DOUBLE_EQ(m3(0, 0), 0);
  EXPECT_DOUBLE_EQ(m3(0, 1), -3);
  EXPECT_DOUBLE_EQ(m3(1, 0), 2);
  EXPECT_DOUBLE_EQ(m3(1, 1), -5);
}

TEST(Suite_operator, TestEqual_1) {
  S21Matrix m(3, 3);
  S21Matrix m2(3, 3);
  EXPECT_EQ(m == m2, 1);
}

TEST(Suite_operator, TestEqual_2) {
  S21Matrix m(3, 3);
  S21Matrix m2(2, 3);
  EXPECT_EQ(m == m2, 0);
}

TEST(Suite_operator, TestEqual_3) {
  S21Matrix m(3, 3);
  S21Matrix m2(3, 3);
  m(0, 0) = 5;
  m(0, 1) = 6;
  m(0, 2) = 7;
  m2(0, 0) = 5;
  m2(0, 1) = 6;
  m2(0, 2) = 7;
  EXPECT_EQ(m == m2, 1);
}

TEST(Suite_operator, TestEqual_4) {
  S21Matrix m(3, 3);
  S21Matrix m2(3, 3);
  m(0, 0) = 5;
  m(0, 1) = 6;
  m(0, 2) = 7;
  m2(0, 0) = 5;
  m2(0, 1) = 6;
  m2(0, 2) = 5;
  EXPECT_EQ(m == m2, 0);
}

TEST(Suite_operator, TestSetSum_1) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 1;
  m(1, 0) = 1;
  m(1, 1) = 1;

  m2(0, 0) = 1;
  m2(0, 1) = 1;
  m2(1, 0) = 1;
  m2(1, 1) = 1;

  m += m2;
  EXPECT_DOUBLE_EQ(m(0, 0), 2);
  EXPECT_DOUBLE_EQ(m(0, 1), 2);
  EXPECT_DOUBLE_EQ(m(1, 0), 2);
  EXPECT_DOUBLE_EQ(m(1, 1), 2);
}

TEST(Suite_operator, TestSetSum_2) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 3;
  m2(1, 1) = 4;

  m += m2;
  EXPECT_DOUBLE_EQ(m(0, 0), 2);
  EXPECT_DOUBLE_EQ(m(0, 1), 4);
  EXPECT_DOUBLE_EQ(m(1, 0), 6);
  EXPECT_DOUBLE_EQ(m(1, 1), 8);
}

TEST(Suite_operator, TestSetSub_1) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 1;
  m(1, 0) = 1;
  m(1, 1) = 1;

  m2(0, 0) = 1;
  m2(0, 1) = 1;
  m2(1, 0) = 1;
  m2(1, 1) = 1;

  m -= m2;
  EXPECT_DOUBLE_EQ(m(0, 0), 0);
  EXPECT_DOUBLE_EQ(m(0, 1), 0);
  EXPECT_DOUBLE_EQ(m(1, 0), 0);
  EXPECT_DOUBLE_EQ(m(1, 1), 0);
}

TEST(Suite_operator, TestSetSub_2) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 10;
  m(0, 1) = 20;
  m(1, 0) = 30;
  m(1, 1) = 40;

  m2(0, 0) = 1;
  m2(0, 1) = 2;
  m2(1, 0) = 3;
  m2(1, 1) = 4;

  m -= m2;

  EXPECT_DOUBLE_EQ(m(0, 0), 9);
  EXPECT_DOUBLE_EQ(m(0, 1), 18);
  EXPECT_DOUBLE_EQ(m(1, 0), 27);
  EXPECT_DOUBLE_EQ(m(1, 1), 36);
}

TEST(Suite_operator, TestSetMulNumber_1) {
  S21Matrix m(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 1;
  m(1, 0) = 1;
  m(1, 1) = 1;
  double x = 3;
  m *= x;

  EXPECT_DOUBLE_EQ(m(0, 0), 3);
  EXPECT_DOUBLE_EQ(m(0, 1), 3);
  EXPECT_DOUBLE_EQ(m(1, 0), 3);
  EXPECT_DOUBLE_EQ(m(1, 1), 3);
}

TEST(Suite_operator, TestSetMulNumber_2) {
  S21Matrix m(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;
  double x = -1;
  m *= x;

  EXPECT_DOUBLE_EQ(m(0, 0), -1);
  EXPECT_DOUBLE_EQ(m(0, 1), -2);
  EXPECT_DOUBLE_EQ(m(1, 0), -3);
  EXPECT_DOUBLE_EQ(m(1, 1), -4);
}

TEST(Suite_operator, TestSetMulNumber_3) {
  S21Matrix m(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;
  double x = 10;
  m *= x;

  EXPECT_DOUBLE_EQ(m(0, 0), 10);
  EXPECT_DOUBLE_EQ(m(0, 1), 20);
  EXPECT_DOUBLE_EQ(m(1, 0), 30);
  EXPECT_DOUBLE_EQ(m(1, 1), 40);
}

TEST(Suite_operator, TestSetMulMatrix_1) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 1;
  m(1, 0) = 1;
  m(1, 1) = 1;

  m2(0, 0) = 1;
  m2(0, 1) = 1;
  m2(1, 0) = 1;
  m2(1, 1) = 1;

  m *= m2;
  EXPECT_DOUBLE_EQ(m(0, 0), 2);
  EXPECT_DOUBLE_EQ(m(0, 1), 2);
  EXPECT_DOUBLE_EQ(m(1, 0), 2);
  EXPECT_DOUBLE_EQ(m(1, 1), 2);
}

TEST(Suite_operator, TestSetMulMatrix_2) {
  S21Matrix m(2, 2);
  S21Matrix m2(2, 2);

  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  m2(0, 0) = 2;
  m2(0, 1) = 1;
  m2(1, 0) = -1;
  m2(1, 1) = -2;

  m *= m2;
  EXPECT_DOUBLE_EQ(m(0, 0), 0);
  EXPECT_DOUBLE_EQ(m(0, 1), -3);
  EXPECT_DOUBLE_EQ(m(1, 0), 2);
  EXPECT_DOUBLE_EQ(m(1, 1), -5);
}

TEST(Suite_operator, TestCoordinatesAccess_1) {
  S21Matrix m(2, 2);
  m(0, 1) = 2;
  EXPECT_DOUBLE_EQ(m(0, 1), 2);
}

TEST(Suite_operator, TestCoordinatesAccessException_1) {
  EXPECT_THROW(
      {
        try {
          S21Matrix m(2, 2);
          m(1, 3) = 2;
        } catch (const std::invalid_argument& e) {
          EXPECT_STREQ("Matrix index out of bounds", e.what());
          throw;
        }
      },
      std::invalid_argument);
}

TEST(Suite_accessor, TestSetRows_1) {
  S21Matrix m(2, 2);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  m.set_rows(4);
  EXPECT_EQ(m.get_rows(), 4);
  EXPECT_DOUBLE_EQ(m(0, 0), 1);
  EXPECT_DOUBLE_EQ(m(0, 1), 2);
  EXPECT_DOUBLE_EQ(m(1, 0), 3);
  EXPECT_DOUBLE_EQ(m(1, 1), 4);
  EXPECT_DOUBLE_EQ(m(2, 0), 0);
  EXPECT_DOUBLE_EQ(m(2, 1), 0);
  EXPECT_DOUBLE_EQ(m(3, 0), 0);
  EXPECT_DOUBLE_EQ(m(3, 1), 0);
}

TEST(Suite_accessor, TestSetRows_2) {
  S21Matrix m(2, 2);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  m.set_rows(1);
  EXPECT_EQ(m.get_rows(), 1);
  EXPECT_DOUBLE_EQ(m(0, 0), 1);
  EXPECT_DOUBLE_EQ(m(0, 1), 2);
}

TEST(Suite_accessor, TestSetCols_1) {
  S21Matrix m(2, 2);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  m.set_cols(4);
  EXPECT_EQ(m.get_cols(), 4);
  EXPECT_DOUBLE_EQ(m(0, 0), 1);
  EXPECT_DOUBLE_EQ(m(0, 1), 2);
  EXPECT_DOUBLE_EQ(m(0, 2), 0);
  EXPECT_DOUBLE_EQ(m(0, 3), 0);
  EXPECT_DOUBLE_EQ(m(1, 0), 3);
  EXPECT_DOUBLE_EQ(m(1, 1), 4);
  EXPECT_DOUBLE_EQ(m(1, 2), 0);
  EXPECT_DOUBLE_EQ(m(1, 3), 0);
}

TEST(Suite_accessor, TestSetCols_2) {
  S21Matrix m(2, 2);
  m(0, 0) = 1;
  m(0, 1) = 2;
  m(1, 0) = 3;
  m(1, 1) = 4;

  m.set_cols(1);
  EXPECT_EQ(m.get_cols(), 1);
  EXPECT_DOUBLE_EQ(m(0, 0), 1);
  EXPECT_DOUBLE_EQ(m(1, 0), 3);
}