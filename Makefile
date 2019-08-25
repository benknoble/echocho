SHELL = /bin/sh

.POSIX:

.SUFFIXES:
.SUFFIXES: .c .o

objects = bsd.o posix.o sysv.o xsi.o echo.o
binaries = bsd posix sysv xsi

all: $(binaries)

$(binaries): echo.o

$(objects): echo.h

clean:
	-$(RM) $(binaries) $(objects)
