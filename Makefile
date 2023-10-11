CFLAGS = -Wall -Werror -Wextra
ARCH = $(shell arch)
ifeq "$(ARCH)" "i386"
MYFLAGS = -lm --coverage -lgtest
endif
ifeq "$(ARCH)" "x86_64"
MYFLAGS =-L/usr/lib -lm --coverage -lgtest
endif

all: clean test gcov_report

test:
	g++ -std=c++17 $(CFLAGS) model/*.cc model/tests/test.cc $(MYFLAGS) -o  test
	./test

install:
	mkdir build
	cmake CMakeLists.txt -B build
	cmake --build build
	cp -r build/smart_calc_v2.app smart_calc_v2.app
	rm -rf build

uninstall:
	rm -rf smart_calc_v2.app

dist: install
	tar -czf calc.tar.gz smart_calc_v2.app
	rm -rf smart_calc_v2.app
	
dvi:
	doxygen Doxyfile
	open doc/html/index.html

gcov_report: test
	./test
	gcovr --html-details rep.html
	open rep.html


clean:
	rm -rf *.o *.gcda *.a *.html *.gcno *.css
	rm -f test
	rm -rf *.gcno *.gcov *.gcda *.info ../*.h.gch
	rm -rf build
	rm -rf smart_calc_v2.app
	rm -rf doc

	

style:
	cp ../materials/linters/.clang-format .clang-format
	clang-format -i *.cc model/*.cc view/*.cc controller/*.cc model/tests/*.cc
	clang-format -i *.h model/*.h view/*.h controller/*.h model/tests/*.h
	
git:
	git add *.cpp *.h *.cc model/*.cc model/*.h view/*.cc view/*.h controller/*.cc controller/*.h *.ui view/*.ui
	git add Makefile
	git add CMakeLists.txt
	git add view/*.vsh view/*.fsh
	
	
