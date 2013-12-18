AUTOMAKE_OPTIONS = subdir-objects
if CHECK

TESTS = check_priority
check_PROGRAMS = check_priority

check_priority_SOURCES = priority_test.c testmain.c ../src/priority.c

MY_LDFLAGS_1 = -lcheck
MY_CFLAGS_1 = -I../include




AM_CPPFLAGS = $(MY_CFLAGS_1)
check_priority_LDFLAGS = $(MY_LDFLAGS_1)

clean-local:
	rm -f *.g*


endif
