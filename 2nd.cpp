#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFER_SIZE 4096
int main(int argc, char *argv[]) {
    if(argc != 3) {
        fprintf(stderr, "Usage: %s <sourcefile> <destinationfile>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int source_fd = open(argv[1], O_RDONLY);
    if(source_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    int dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0666);
    if(dest_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;
    while((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(dest_fd, buffer, bytes_read);
        if(bytes_written != bytes_read) {
            perror("write");
            exit(EXIT_FAILURE);
        }
    }
    if(bytes_read == -1) {
        perror("read");
        exit(EXIT_FAILURE);
    }#include <stdio.h>
 
//user-defined function
int findLRU(int time[], int n)
{
   int i, minimum = time[0], pos = 0;
 
   for (i = 1; i < n; ++i)
   {
      if (time[i] < minimum)
      {
         minimum = time[i];
         pos = i;
      }
   }
 
   return pos;
}
 
//main function
int main()
{
   int no_of_frames, no_of_pages, frames[10], pages[30], counter = 0, time[10], flag1, flag2, i, j, pos, faults = 0;
   printf("Enter number of frames: ");
   scanf("%d", &no_of_frames);
 
   printf("Enter number of pages: ");
   scanf("%d", &no_of_pages);
 
   printf("Enter reference string: ");
 
   for (i = 0; i < no_of_pages; ++i)
   {
      scanf("%d", &pages[i]);
   }
 
   for (i = 0; i < no_of_frames; ++i)
   {
      frames[i] = -1;
   }
 
   for (i = 0; i < no_of_pages; ++i)
   {
      flag1 = flag2 = 0;
 
      for (j = 0; j < no_of_frames; ++j)
      {
         if (frames[j] == pages[i])
         {
            counter++;
            time[j] = counter;
            flag1 = flag2 = 1;
            break;
         }
      }
 
      if (flag1 == 0)
      {
         for (j = 0; j < no_of_frames; ++j)
         {
            if (frames[j] == -1)
            {
               counter++;
               faults++;
               frames[j] = pages[i];
               time[j] = counter;
               flag2 = 1;
               break;
            }
         }
      }
 
      if (flag2 == 0)
      {
         pos = findLRU(time, no_of_frames);
         counter++;
         faults++;
         frames[pos] = pages[i];
         time[pos] = counter;
      }
 
      printf("\n");
 
      for (j = 0; j < no_of_frames; ++j)
      {
         printf("%d\t", frames[j]);
      }
   }
 
   printf("\nTotal Page Faults = %d", faults);
 
   return 0;
}
    if(close(source_fd) == -1 || close(dest_fd) == -1) {
        perror("close");
        exit(EXIT_FAILURE);
    }

    printf("File copied successfully.\n");

    return 0;
}

