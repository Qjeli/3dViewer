.PHONY: all, install, uninstall, dist, clean, build, rebuild, check, cppcheck, valcheck, gcov_report, test

CC = gcc -std=c11
FLAGS = -Wall -Werror -Wextra
OS=$(shell uname)
ifeq ($(OS),Darwin)
    LIBS=-lcheck -lm -lpthread
    REPORT_OPEN = open
else
    LIBS=-lcheck -lm -lpthread -lrt -lsubunit
    REPORT_OPEN = xdg-open
endif

all: install

install: build
	cd Front/ && qmake && make && make clean
	@mkdir $(HOME)/Desktop/3DViewer
	@cp -rf Front/3DViewer.app $(HOME)/Desktop/3DViewer/
	make clean

open:
	$(HOME)/Desktop/3DViewer/

uninstall:
	cd Front/3DViewer.app && rm -rf Makefile 3DViewer.pro 3DViewer.pro.user .qmake.stash .qtc_clangd .tmp .qm
	rm -rf $(HOME)/Desktop/3DViewer/

build:
	mkdir build
	cd ./build/ && qmake ../Front/ && make

check: cppcheck
	cp ../materials/linters/.clang-format ./
	clang-format -i ./Back/*.c ./Back/*.h
	clang-format -n ./Back/*.c ./Back/*.h
	clang-format -i ./Front/*.cpp ./Front/*.h
	clang-format -n Front/main.cpp
	clang-format -n Front/mainwindow.cpp
	clang-format -n Front/mainwindow.h
	clang-format -n Front/glwidget.cpp
	clang-format -n Front/glwidget.h
	rm -rf .clang-format

cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.c *.h

clean:
	rm -rf *.o *.out *.gcov *.gcno *.gcda *.a *.log *.info *.dSYM s21_test report val_result.log
	rm -rf *.qmake.stash *.tar.gz *.aux *.dvi *.toc *.pdf build

rebuild: clean all

test: clean
	$(CC) $(FLAGS) s21_viewer_test.c ./Back/s21_parse.c ./Back/s21_transform.c -o s21_test $(LIBS)
	./s21_test

valcheck: clean
	$(CC) $(FLAGS) s21_viewer_test.c ./Back/s21_parse.c ./Back/s21_transform.c -o s21_test $(LIBS)
	valgrind --leak-check=summary ./s21_test  >> val_result.log 2>&1
	grep -c -e"definitely lost:" val_result.log
	grep -c -e"definitely lost: 0 bytes in 0 blocks" val_result.log
	grep -c -e"ERROR SUMMARY: 0 errors from 0 contexts" val_result.log

gcov_report: clean
	$(CC) $(FLAGS) -fprofile-arcs -ftest-coverage s21_viewer_test.c ./Back/s21_parse.c ./Back/s21_transform.c -o s21_test $(LIBS)
	./s21_test
	lcov -t "test" -o s21_test.info -c -d .
	genhtml -o report s21_test.info
	open ./report/index.html

dist:
	tar -czf 3DViewer_v1-0.tar.gz Makefile Back/*.c Back/*.h Front/main.cpp Front/mainwindow.cpp Front/mainwindow.h Front/glwidget.cpp Front/glwidget.h
dvi:
	open description.txt
	texi2dvi manual.tex
	texi2pdf manual.tex
