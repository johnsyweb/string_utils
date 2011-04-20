include_HEADERS = string_utils.h

TESTS = t_string_utils
check_PROGRAMS = t_string_utils
t_string_utils_CPPFLAGS = -Wall
t_string_utils_CXXFLAGS = -Wextra -Wshadow -pedantic -Wno-long-long -Wfloat-equal -Wcast-qual -g -O2 -Weffc++ -Werror -coverage
t_string_utils_SOURCES = t_string_utils.cpp string_utils.h
t_string_utils_LDFLAGS = -lunittest++

cov-reset:
	@rm -fr coverage
	@find . -name "*.gcda" -exec rm {} \;
	@lcov --directory . --zerocounters

cov-report:
	@mkdir -p coverage
	@lcov --compat-libtool --directory . --capture --output-file coverage/string_utils
	@genhtml -o coverage/ coverage/string_utils

cov:
	@make cov-report

clean-local:
	@make cov-reset

check:
	@make cov
