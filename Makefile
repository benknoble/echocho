SHELL = /bin/sh

.POSIX:

.SUFFIXES:
.SUFFIXES: .c .o

objects = bsd.o posix.o sysv.o xsi.o echo.o escape.o
binaries = bsd posix sysv xsi

all: $(binaries)

$(binaries): echo.o
sysv xsi: escape.o
escape.o: echo.o

bsd.o posix.o sysv.o xsi.o echo.o: echo.h
sysv.o xsi.o escape.o: escape.h
sysv.o xsi.o escape.o: echo.h

clean:
	-$(RM) $(binaries) $(objects)
