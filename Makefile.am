ACLOCAL_AMFLAGS = -I ./m4
SUBDIRS = src

if HAVE_CPPCHECK
cppcheck:
		$(CPPCHECK) --quiet --template="{file};{line};{severity};{id};{message}" --enable=all --inconclusive --force --inline-suppr --std=c11 --std=c++14 -I Config --suppress=missingIncludeSystem ..
endif