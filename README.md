# PC-Assignment
Repository for Parallel Computing Assignment on Brute Force Search

# Description
  - The source files in this repository are both serial/sequential and 
    parallel (using OpenMP) implementations of a Brute Force Search program.
    The programs encrypt a plain text message using a hard coded True Key, 
    conducts the search and compare possible key combinations against the true key. 
    When a match is found, the programs will then decrypt the encrypted message 
    using the key solution found via the Brute Force Search. More detail can be found 
    within the source files themselves via the comments and internal documentation.

# Pre-Requisites
  - OpenSSL must be installed, including the libcrypto library
    If you do not already have OpenSSL installed, you can find it at the following link
    https://www.openssl.org/source/
    
  - OpenMP must also be installed.
    Note - OpenMP is typically installed as part of gcc.
    
# Compiling & Running
  - A basic Makefile is provided in the repository for compiling the programs.
  
  - Running "make serial" will compile the serial/sequential version of the program.
  - Running "make omp" will compile the version of the program that uses OpenMP.
  - Running "make clean" will remove the .o files in the directory.
