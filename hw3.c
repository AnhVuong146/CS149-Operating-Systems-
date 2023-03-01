// Write a C program called copy that accepts two arguments called file1 and file2. If no argument is 
// specified or only one argument is specified, the program should display a message to ask the user to 
// enter two file names and then exit. In case two arguments are specified but there is no file1, the 
// program must specify, copy cannot be performed and exit. If file1 exists but file2 does not exist, then 
// the program must create file2 and copy the content of file1 into file2. If file2 exists, the program should 
// ask if the user wants to overwrite or append to that file and then copy file1 to file2 as specified.

#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/uio.h>
#include <string.h>
#include <stdbool.h>
#include <sys/stat.h>
#define MAX_LINE 1024

int main(int argc, char *argv[]) {
    char rb[1];
    int c;
    int fd1, fd2;
    char buffer[MAX_LINE];
    char msg[50] = "testing";
    char buf;

    if (argc != 3) {
    printf("Argument number error. Must enter two file names\n");
    return 1;
    }

    fd1 = open(argv[1], O_RDONLY);
    fd2 = open(argv[2], O_RDWR);
    if (fd1 == -1) {
        printf("copy cannot be performed. Input file1 does not exist.\n");
        return 1;
        }
    else if (fd1 != -1 && fd2 == -1) {
        fd2 = open(argv[2], O_RDWR | O_CREAT, 0644);
        while(read(fd1, &buf, 1))
	    {
		write(fd2, &buf, 1);
	    }
        return 1;
    }
    else if (fd2 != -1) 
    {
        printf("Do you want to append or overwrite the existing file? (a/o)\n");
        fgets(buffer, MAX_LINE, stdin);
        if (strcmp(buffer, "o\n") == 0) 
        {
            fd2 = open(argv[2], O_WRONLY, 0644);
            while(read(fd1, &buf, 1))
	        {
		    write(fd2, &buf, 3);
	        }
            return 1;
        }
        else if (strcmp(buffer, "a\n") == 0) 
        {
            fd2 = open(argv[2], O_APPEND | O_WRONLY);
            while(read(fd1, &buf, 1))
	        {
		    write(fd2, &buf, 3);
	        }
            return 1;
        }
        
    }

    close(fd1);
	close(fd2);
    
}
