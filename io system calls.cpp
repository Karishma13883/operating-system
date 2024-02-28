#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>

int main() 
{
  
    int fd = open("document.txt", O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }


    char buffer[100];
    ssize_t bytes_read = read(fd, buffer, sizeof(buffer));
    if (bytes_read == -1) {
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }
    buffer[bytes_read] = '\0';
    printf("Contents of the file:\n%s\n", buffer);

    struct stat file_stat;
    if (fstat(fd, &file_stat) == -1) {
        perror("fstat");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("File size: %ld bytes\n", file_stat.st_size);


    if (lseek(fd, 0, SEEK_SET) == -1) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }

    
    DIR *dir = opendir(".");
    if (dir == NULL) {
        perror("opendir");
        close(fd);
        exit(EXIT_FAILURE);
    }

 
    printf("Directory contents:\n");
    struct dirent *dir_entry;
    while ((dir_entry = readdir(dir)) != NULL) {
        printf("%s\n", dir_entry->d_name);
    }

 
    closedir(dir);
    close(fd);

    return 0;
}

