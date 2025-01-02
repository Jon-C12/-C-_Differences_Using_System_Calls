This project involves developing a C program to compare the contents of two input files using low-level system calls (open, close, read, and write), while demonstrating proficiency in dynamic memory management and Unix file permissions. The program will perform a byte-by-byte comparison of the two input files and output any differences into two separate files: differencesFoundInFile1.txt (containing bytes unique to the first file) and differencesFoundInFile2.txt (containing bytes unique to the second file). If these output files already exist in the directory, the program must overwrite them; otherwise, it should create the files with appropriate read and write permissions for the owner.

The implementation will be split into two distinct steps. In the first step, the program will read and compare one byte at a time from each input file using a small buffer of size 2 (one byte for the data and one for the null terminator). Any mismatched bytes from the first file will be written to differencesFoundInFile1.txt. In the second step, the program will perform a similar process to identify and write mismatched bytes from the second file into differencesFoundInFile2.txt.

The program must adhere to strict requirements: it should be implemented in a single source file named proj3.c and must compile using a provided Makefile to generate an executable named proj3.out. Additionally, the program should not use standard file I/O functions such as fopen or fread, and it must avoid memory leaks, ensuring dynamic memory is properly managed and verified using tools like valgrind. Finally, the program will measure and output the execution time for each step, providing insights into the efficiency of the operations. This project reinforces knowledge of system programming, file permissions, debugging with GDB, and efficient file handling in Unix.

Test Cases:

./proj3.out
Usage: proj3.out <file1> <file2>

./proj3.out input1.txt
Usage: proj3.out <file1> <file2>

./proj3.out a b
There was an error reading a file.

./proj3.out input1.txt input2.txt; cat differencesFoundInFile1.txt differencesFoundInFile2.txt;
Step 1 took 0.038000 milliseconds
Step 2 took 0.018000 milliseconds
cat!dog.

./proj3.out input1.txt input2.txt; cat differencesFoundInFile1.txt differencesFoundInFile2.txt | wc -c;
Step 1 took 0.066000 milliseconds
Step 2 took 0.040000 milliseconds
8

./proj3.out input3.txt input4.txt; cat differencesFoundInFile1.txt differencesFoundInFile2.txt;
Step 1 took 0.034000 milliseconds
Step 2 took 0.016000 milliseconds
aaaaa
b

./proj3.out input3.txt input4.txt; cat differencesFoundInFile1.txt differencesFoundInFile2.txt | wc -c;
Step 1 took 0.056000 milliseconds
Step 2 took 0.017000 milliseconds
8

./proj3.out input5.txt input6.txt; cat differencesFoundInFile1.txt differencesFoundInFile2.txt;
Step 1 took 0.027000 milliseconds
Step 2 took 0.039000 milliseconds
a
bbbbbb
3

./proj3.out input5.txt input6.txt; cat differencesFoundInFile1.txt differencesFoundInFile2.txt | wc -c;
Step 1 took 0.026000 milliseconds
Step 2 took 0.016000 milliseconds
9

./proj3.out alice1.txt alice2.txt; cat differencesFoundInFile1.txt differencesFoundInFile2.txt;
Step 1 took 113.053000 milliseconds
Step 2 took 0.724000 milliseconds
showingAliceBender*Zoey!

./proj3.out alice1.txt alice2.txt; cat differencesFoundInFile1.txt differencesFoundInFile2.txt | wc -c;
Step 1 took 113.401000 milliseconds
Step 2 took 0.784000 milliseconds
24

./proj3.out alice1.txt alice1.txt; cat differencesFoundInFile1.txt differencesFoundInFile2.txt | wc -c;
Step 1 took 114.963000 milliseconds
Step 2 took 0.646000 milliseconds
0
