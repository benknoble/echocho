SHELL = /bin/sh

.POSIX:

.SUFFIXES:
.SUFFIXES: .c .o

objects = bsd.o posix.o sysv.o xsi.o echo.o escape.o
binaries = bsd posix sysv xsi

all: $(binaries)

bsd posix: echo.o
sysv xsi: escape.o

bsd.o posix.o echo.o: echo.h
sysv.o xsi.o escape.o: escape.h

clean:
	-$(RM) $(binaries) $(objects)
