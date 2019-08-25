# Implementations of `echo`

[![This project is considered experimental](https://img.shields.io/badge/status-experimental-critical.svg)](https://benknoble.github.io/status/experimental/)

Based on [the Open Group POSIX specification](http://pubs.opengroup.org/onlinepubs/9699919799/).

## Why?

 - For fun
 - For sysadmins who need strictly compatible versions of echo
 - For someone who just "*wants echo to work, damnit*"
 - For reference

## Compiling

Build binaries with a POSIX-compatible `make`. Individual targets are provided
for the implementations listed below.

**Supported Implementations**

 - POSIX
 - BSD
 - XSI
 - SystemV

## Bugs

 - No account for environment variables, e.g., `LANG` and `LC_*`
 - Limited error checking
 - No `make` support for installation, out-of-source building, documentation
 - No tests
 - No documentation
