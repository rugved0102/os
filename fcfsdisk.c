#include <stdio.h>
#include <stdlib.h>


void calculateFCFS(int requests[], int n, int initial_head) {
    int total_seek_time = 0;
    int current_head = initial_head;


    printf("\nDisk Scheduling using FCFS Algorithm:\n");
    printf("------------------------------------------------\n");
    printf("| Request No. |  Request   |  Seek Time      |\n");
    printf("------------------------------------------------\n");
   
    for (int i = 0; i < n; i++) {
        int seek_time = abs(requests[i] - current_head);
        total_seek_time += seek_time;
        printf("|      %2d      |    %3d     |     %3d        |\n", i + 1, requests[i], seek_time);
        current_head = requests[i];
    }


    printf("------------------------------------------------\n");
    printf("Total Seek Time: %d\n", total_seek_time);
}


int main() {
    int n;
    int initial_head;


    // Accept number of requests and initial head position
    printf("Enter the number of disk requests: ");
    scanf("%d", &n);


    int requests[n];
    printf("Enter the initial head position: ");
    scanf("%d", &initial_head);


    printf("Enter the disk requests: \n");
    for (int i = 0; i < n; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }


    // Calculate and display the FCFS scheduling
    calculateFCFS(requests, n, initial_head);


    return 0;
}

/*Enter the number of disk requests: 6
Enter the initial head position: 50
Enter the disk requests: 
Request 1: 82 170 43 140 24 16 190
Request 2: Request 3: Request 4: Request 5: Request 6: 
Disk Scheduling using FCFS Algorithm:
------------------------------------------------
| Request No. |  Request   |  Seek Time      |
------------------------------------------------
|       1      |     82     |      32        |
|       2      |    170     |      88        |
|       3      |     43     |     127        |
|       4      |    140     |      97        |
|       5      |     24     |     116        |
|       6      |     16     |       8        |
------------------------------------------------
Total Seek Time: 468*/