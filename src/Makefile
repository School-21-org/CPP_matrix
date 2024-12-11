 CC = g++
CFLAGS = -Wall -Wextra -Werror -g --std=c++17
SOURCE = $(wildcard *.cpp)
SOURCE_TEST = $(wildcard tests/*.cpp)
UNAME := $(shell uname)

ifeq ($(UNAME), Linux)
	# CFLAGS += -DLinux
	GFLAGS = -lgtest -lstdc++ 
endif

ifeq ($(UNAME), Darwin)
	# CFLAGS += -DDarwin
	GFLAGS = -I/opt/homebrew/include -L/opt/homebrew/lib -lgtest 
endif

all: clean s21_matrix_oop.a

s21_matrix_oop.a:
	$(CC) $(CFLAGS) -c $(SOURCE)
	ar -rc s21_matrix_oop.a s21_matrix_oop.o
	ranlib s21_matrix_oop.a
	@rm -rf *.o

test: clean s21_matrix_oop.a 
	$(CC) $(CFLAGS) $(SOURCE_TEST) s21_matrix_oop.a -o test $(GFLAGS)
	./test
	@rm s21_matrix_oop.a test

style: clean
	find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec clang-format -n -style=file:../materials/linters/.clang-format {} \;

clang:
	find . -type f \( -name "*.cpp" -o -name "*.h" \) -exec clang-format -i -style=file:../materials/linters/.clang-format {} \;

clean:
	@rm -rf a.out a.out.dSYM s21_matrix_oop.a test *.info test.dSYM

valgrind_test: clean s21_matrix_oop.a
	$(CC) $(CFLAGS) $(SOURCE_TEST) s21_matrix_oop.a -o test $(GFLAGS)
	valgrind -s -q --tool=memcheck --leak-check=yes --track-origins=yes --show-leak-kinds=all --verbose --log-file=valgrind_out.txt ./test
	cat valgrind_out.txt
	@rm s21_matrix_oop.a test valgrind_out.txt

cppcheck_test:
	cppcheck --enable=all --suppress=missingIncludeSystem *.cpp *.h tests/*.cpp tests/*.h