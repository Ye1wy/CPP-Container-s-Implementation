CXX=g++
SRCFLAGS=-Wall -Werror -Wextra -std=c++17
TEST_FLAGS=-lgtest -lgmock

CXXFLAGS+=$(SRCFLAGS) $(TEST_FLAGS)
UNAME_S = $(shell uname -s)

OSFLAGS =

ifeq ($(UNAME_S),Linux)
	OSFLAGS+=-lsubunit -lm
	CCFLAGS+=$(OSFLAGS)
endif

VALGRIND_FLAGS:=--leak-check=full --verbose --show-leak-kinds=all --track-origins=yes

HEADERS_SRC=array/s21_array.h helper/helper.h list/s21_list.h map/s21_map.h \
			multiset/s21_multiset.h queue/s21_queue.h RBtree/s21_RBtree.h \
			set/s21_set.h stack/s21_stack.h vector/s21_vector.h
TEST_SRC=tests/test_array.cc tests/test_list.cc tests/test_map.cc \
		tests/test_multiset.cc tests/test_queue.cc tests/test_run.cc \
		tests/test_set.cc tests/test_stack.cc tests/test_vector.cc
TEST_OBJECTS = $(patsubst %.cc,%.o,$(TEST_SRC))
TOTAL_FILES := $(words $(TEST_SRC))
COMPILED_FILES = 0

all: clean tests

%.o: %.cc
	$(eval COMPILED_FILES=$(shell echo $$(($(COMPILED_FILES)+1))))
	@echo "Compiling $< ($(COMPILED_FILES)/$(TOTAL_FILES))... [$$(($(COMPILED_FILES) * 100 / $(TOTAL_FILES)))%]"
	@$(CXX) -c $(SRCFLAGS) $< -o $@

tests: $(TEST_OBJECTS)
	@echo ""
	@echo "Linking ojects files..."
	@$(CXX) $(CXXFLAGS) $^ -o tester
	@echo "NOW YOU CAN RUN TESTS!"
	@echo "Executable name is tester"
  
clean:
	@echo "Cleaning up..."
	@rm -rf report
	@rm -rf tests/*.o
	@rm -rf tester
	@rm -rf a.out
	@rm -rf gcov_report
	@rm -rf *.gcda
	@rm -rf *.gcno
	@rm -rf *.gcov
	@rm -rf *.info

	
check_leaks: tests
ifeq ($(UNAME_S),Darwin)
	leaks --atExit -- ./tester
else
	valgrind $(VALGRIND_FLAGS) ./tester
endif

gcov_report: tests
	@echo "Inited GCOV REPORT!"
	@echo "Processing..."
	@$(CXX) $(CXXFLAGS) --coverage $(TEST_SRC) -o gcov_report
	@./gcov_report
	@lcov -t "stest" -o test.info --ignore-errors inconsistent --no-external -c -d .
	@genhtml -o report test.info
ifeq ($(UNAME_S), Darwin)
	@open ./report/index.html
else
	@xdg-open report/index.html
endif

style:
	clang-format -n --style=google $(TEST_SRC) $(HEADERS_SRC)
	
style_f:
	clang-format -i --style=google $(TEST_SRC) $(HEADERS_SRC)