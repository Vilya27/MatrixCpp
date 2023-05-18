CC = gcc
FLAGS = -Wall -Werror -Wextra -lstdc++ -std=c++17
OS = $(shell uname)

ifeq ($(OS), Linux)
	CHECK_FLAGS = -lgtest -lm -pthread -lrt
	OPEN = firefox
else
	CHECK_FLAGS = -lgtest
	OPEN = open
endif

all: matrix_oop.a test clean

matrix_oop.o: matrix_oop.cc
	$(CC) $(FLAGS) -c matrix_oop.cc

matrix_oop.a: matrix_oop.o
	@ar rc matrix_oop.a matrix_oop.o
	@ranlib matrix_oop.a

test: test.cc matrix_oop.a
	g++ $(FLAGS) test.cc matrix_oop.a $(CHECK_FLAGS) -o test
	./test

rebuild: clean all

check:
	cp ../materials/linters/.clang-format .
	clang-format -n *.cc *.h
	rm -rf .clang-format

leaks: test
ifeq ($(OS), Linux)
	valgrind --leak-check=full -v ./test
else
	leaks --atExit -- test
endif

gcov_report: matrix_oop.a test.cc
	g++ $(FLAGS) --coverage test.cc matrix_oop.cc -o gcov_test $(CHECK_FLAGS)
	./gcov_test
	lcov -t "gcov_test" -o gcov_test.info --no-external -c -d .
	genhtml -o report/ gcov_test.info
	$(OPEN) report/index.html

clean:
	rm -rf *.o *.g* *.info *.out report *.a *.dSYM test gcov_test

	

