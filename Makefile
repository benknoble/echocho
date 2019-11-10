SHELL = /bin/sh

.POSIX:

.SUFFIXES:
.SUFFIXES: .c .o

objects = echo.o escape.o
binaries = bsd posix sysv xsi

all: $(binaries)

bsd posix: echo.o
sysv xsi: escape.o

echo.o: echo.h
escape.o: escape.h

clean:
	-$(RM) $(binaries) $(objects)
