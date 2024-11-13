#include <stdio.h>

int find_LRU(int time[], int n) {
    int min = time[0], pos = 0;
    for (int i = 1; i < n; i++) {
        if (time[i] < min) {
            min = time[i];
            pos = i;
        }
    }
    return pos;
}

int page_faults_LRU(int pages[], int n, int capacity) {
    int frame[capacity]; // Holds pages in memory
    int time[capacity];  // Tracks the time each page was last used
    int page_faults = 0, counter = 0;

    // Initialize frames with -1 to represent empty slots
    for (int i = 0; i < capacity; i++) {
        frame[i] = -1;
    }

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        int found = 0;

        // Check if the page is already in the frame
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == page) {
                found = 1;  // Page is found in frame
                time[j] = counter++; // Update last used time
                break;
            }
        }

        // If page is not found, it is a page fault
        if (!found) {
            int pos = -1;

            // If there is an empty slot, find it
            for (int j = 0; j < capacity; j++) {
                if (frame[j] == -1) {
                    pos = j;
                    break;
                }
            }

            // If no empty slot, replace the LRU page
            if (pos == -1) {
                pos = find_LRU(time, capacity);
            }

            // Replace the page at the LRU position with the new page
            frame[pos] = page;
            time[pos] = counter++;
            page_faults++;
        }

        // Display current frame contents
        printf("Frame: ");
        for (int j = 0; j < capacity; j++) {
            if (frame[j] == -1)
                printf("- ");
            else
                printf("%d ", frame[j]);
        }
        printf("\n");
    }

    return page_faults;
}

int main() {
    int n, capacity;

    printf("Enter the number of pages: ");
    scanf("%d", &n);

    int pages[n];
    printf("Enter the reference string (page numbers): ");
    for (int i = 0; i < n; i++)
        scanf("%d", &pages[i]);

    printf("Enter the frame capacity: ");
    scanf("%d", &capacity);

    int faults = page_faults_LRU(pages, n, capacity);
    printf("Total page faults: %d\n", faults);

    return 0;
}

/*Enter the number of pages: 7
Enter the reference string (page numbers): 0 1 2 0 3 1 2
Enter the frame capacity: 3*/