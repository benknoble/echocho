SHELL = /bin/sh

.POSIX:

.SUFFIXES:
.SUFFIXES: .c .o

objects = bsd.o posix.o sysv.o xsi.o echo.o echo_n.o echo_e.o escape.o
binaries = bsd posix sysv xsi

all: $(binaries)

# object dependencies
posix: echo.o echo_n.o
bsd: echo.o echo_n.o
xsi sysv: echo_e.o echo_n.o echo.o escape.o
echo.o: echo_n.o
echo_e.o: echo_n.o echo.o escape.o

# header dependencies
posix.o: echo.h
bsd.o: echo.h echo_n.h
xsi.o sysv.o: echo_e.h echo_n.h echo.h escape.h
echo.o: echo.h echo_n.h
echo_n.o: echo_n.h
echo_e.o: echo_e.h echo_n.h echo.h escape.h
escape.o: escape.h

clean:
	-$(RM) $(binaries) $(objects)
