#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <unistd.h>

void comp1(int fileDesc1, int fileDesc2);
void step2(int fileDesc1, int fileDesc2);
void reportTime(struct timeval start, struct timeval end, const char * stepName);

/*                                                                                                               
 * The main function compares our given files by what our command-line arguments                                  
 * specify. It uses the comp1 and step2 functions described below to compare these                               
 * files while also tracking times for each step using the reportTime function.                                  
 */

int main(int argc, char * argv[]) {
    if (argc != 3) {
        printf("Usage: proj3.out <file1> <file2>\n");
        return 1;
    }

    int fileDesc1 = open(argv[1], O_RDONLY);
    int fileDesc2 = open(argv[2], O_RDONLY);

    if (fileDesc1 == -1 || fileDesc2 == -1) {
        printf("There was an error reading a file.\n");
        if (fileDesc1 != -1) close(fileDesc1);
        if (fileDesc2 != -1) close(fileDesc2);
        return 1;
    }

    struct timeval start, end;

    // Step 1 tracking
    gettimeofday(&start, NULL);
    comp1(fileDesc1, fileDesc2);
    gettimeofday(&end, NULL);
    reportTime(start, end, "Step 1");
    lseek(fileDesc1, 0, SEEK_SET);
    lseek(fileDesc2, 0, SEEK_SET);

    // Step 2 tracking 
    gettimeofday(&start, NULL);
    step2(fileDesc1, fileDesc2);
    gettimeofday(&end, NULL);
    reportTime(start, end, "Step 2");

    close(fileDesc1);
    close(fileDesc2);

    return 0;
}

/*                                                                                                               
 * The comp1 function compares two files by each character. It then writes any                                   
 * differing characters to "differencesFoundInFile1.txt". This version ensures                                   
 * that the correct number of bytes are written to avoid incorrect counts.                                       
 */

void comp1(int fileDesc1, int fileDesc2) {
    // Opening or creating the differences file for file 1
    int fileDif1 = open("differencesFoundInFile1.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fileDif1 == -1) {
        printf("Error writing to a file.\n");
        return;
    }

    // Get file sizes
    struct stat fileStat1, fileStat2;
    if (fstat(fileDesc1, &fileStat1) == -1 || fstat(fileDesc2, &fileStat2) == -1) {
        printf("Error getting file size.\n");
        close(fileDif1);
        return;
    }

    size_t size1 = fileStat1.st_size;
    size_t size2 = fileStat2.st_size;

    // Dynamically allocate arrays of exact size
    char *fileBuffer1 = (char *)malloc(size1);
    char *fileBuffer2 = (char *)malloc(size2);

    if (!fileBuffer1 || !fileBuffer2) {
        printf("Memory allocation failed.\n");
        free(fileBuffer1);
        free(fileBuffer2);
        close(fileDif1);
        return;
    }

    // Read files into buffers
    read(fileDesc1, fileBuffer1, size1);
    read(fileDesc2, fileBuffer2, size2);

    // Compare buffers and write differences from file 1
    for (size_t i = 0; i < size1; i++) {
        if (i >= size2 || fileBuffer1[i] != fileBuffer2[i]) {
            write(fileDif1, &fileBuffer1[i], 1);
        }
    }

    close(fileDif1);
    free(fileBuffer1);
    free(fileBuffer2);
}

/*                                                                                                               
 * The step2 function reads both files into dynamically allocated arrays of exact sizes.                          
 * It then compares the arrays byte by byte and writes any differing bytes from                                   
 * file two into a third dynamically allocated array, which is copied into                                       
 * "differencesFoundInFile2.txt".                                                                                
 */

void step2(int fileDesc1, int fileDesc2) {
    // Get file sizes
    struct stat fileStat1, fileStat2;
    if (fstat(fileDesc1, &fileStat1) == -1 || fstat(fileDesc2, &fileStat2) == -1) {
        printf("Error getting file size.\n");
        return;
    }

    size_t size1 = fileStat1.st_size;
    size_t size2 = fileStat2.st_size;

    // Dynamically allocate arrays of exact size
    char *fileBuffer1 = (char *)malloc(size1);
    char *fileBuffer2 = (char *)malloc(size2);

    if (!fileBuffer1 || !fileBuffer2) {
        printf("Memory allocation failed.\n");
        free(fileBuffer1);
        free(fileBuffer2);
        return;
    }

    // Read files into the buffers
    read(fileDesc1, fileBuffer1, size1);
    read(fileDesc2, fileBuffer2, size2);

    // Allocate memory for the differences array (size of file 2)
    char *differencesBuffer = (char *)malloc(size2);
    if (!differencesBuffer) {
        printf("Memory allocation for differences array failed.\n");
        free(fileBuffer1);
        free(fileBuffer2);
        return;
    }

    int differencesCount = 0;

    // Compare buffers and store differences from file 2
    for (size_t i = 0; i < size2; i++) {
        if (i >= size1 || fileBuffer1[i] != fileBuffer2[i]) {
            differencesBuffer[differencesCount++] = fileBuffer2[i];
        }
    }

    // Open or create the differences file for file 2
    int fileDif2 = open("differencesFoundInFile2.txt", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    if (fileDif2 == -1) {
        printf("Error writing to a file.\n");
        free(fileBuffer1);
        free(fileBuffer2);
        free(differencesBuffer);
        return;
    }

    // Write the differences to the file
    write(fileDif2, differencesBuffer, differencesCount);

    close(fileDif2);
    free(fileBuffer1);
    free(fileBuffer2);
    free(differencesBuffer);
}

/*                                                                                                               
 * The reportTime function calculates and prints our elapsed times of each step.                                 
 * It does this through utilization of two timeval structures, it then also                                      
 * converts these given values to milliseconds through a couple extra steps.                                     
 * Finally it prints this value stored in the elapsedTime variable.                                              
 */

void reportTime(struct timeval start, struct timeval end, const char *stepName) {
    double elapsedTime = (end.tv_sec - start.tv_sec) * 1000.0;
    elapsedTime += (end.tv_usec - start.tv_usec) / 1000.0;
    printf("%s took %.6f milliseconds\n", stepName, elapsedTime);
}

