#include <stdio.h>
#include <stdlib.h>

void sort(int arr[], int n) {
for (int i = 0; i < n - 1; i++) {
for (int j = 0; j < n - i - 1; j++) {
if (arr[j] > arr[j + 1]) {
int temp = arr[j];
arr[j] = arr[j + 1];
arr[j + 1] = temp;
}
}
}
}

void print_table(int seek_sequence[], int seek_count, int total_seek_time) {
printf("\nDisk Scheduling - SCAN\n");
printf("------------------------------------------------\n");
printf("| Request Order | Position | Seek Time (Head -> Request) |\n");
printf("------------------------------------------------\n");

int current_position = seek_sequence[0];
for (int i = 1; i <= seek_count; i++) {
int seek_distance = abs(seek_sequence[i] - current_position);
printf("| %2d | %3d | %3d ms |\n", i, seek_sequence[i], seek_distance);
current_position = seek_sequence[i];
}
printf("------------------------------------------------\n");
printf("| Total Seek Time: %d ms |\n", total_seek_time);
printf("------------------------------------------------\n");
}

int scan_disk_scheduling(int requests[], int n, int head, int disk_size, int direction) {
int seek_sequence[n + 1];
int total_seek_time = 0;
int seek_count = 0;

// Add initial head position to seek sequence
seek_sequence[seek_count++] = head;

// Sort the requests
sort(requests, n);

int current_position = head;
int closest_index = 0;

// Find the closest request in the chosen direction
for (int i = 0; i < n; i++) {
if (requests[i] >= head) {
closest_index = i;
break;
}
}

// SCAN in the specified direction (0 = left, 1 = right)
if (direction == 1) {
// Move towards the end of the disk
for (int i = closest_index; i < n; i++) {
seek_sequence[seek_count++] = requests[i];
total_seek_time += abs(current_position - requests[i]);
current_position = requests[i];
}
// After reaching end, reverse direction if needed
if (current_position < disk_size - 1) {
total_seek_time += abs(current_position - (disk_size - 1));
current_position = disk_size - 1;
seek_sequence[seek_count++] = current_position;
}
// Move back towards the start
for (int i = closest_index - 1; i >= 0; i--) {
seek_sequence[seek_count++] = requests[i];
total_seek_time += abs(current_position - requests[i]);
current_position = requests[i];
}
} else {
// Move towards the start of the disk
for (int i = closest_index - 1; i >= 0; i--) {
seek_sequence[seek_count++] = requests[i];
total_seek_time += abs(current_position - requests[i]);
current_position = requests[i];
}
// After reaching start, reverse direction if needed
if (current_position > 0) {
total_seek_time += abs(current_position - 0);
current_position = 0;
seek_sequence[seek_count++] = current_position;
}
// Move back towards the end
for (int i = closest_index; i < n; i++) {
seek_sequence[seek_count++] = requests[i];
total_seek_time += abs(current_position - requests[i]);
current_position = requests[i];
}
}

// Display the table
print_table(seek_sequence, seek_count - 1, total_seek_time);
return total_seek_time;
}

int main() {
int n, head, disk_size, direction;

// Input: Number of disk requests
printf("Enter the number of disk requests: ");
scanf("%d", &n);

int requests[n];

// Input: Disk request sequence
printf("Enter the disk requests (in sequence): ");
for (int i = 0; i < n; i++) {
scanf("%d", &requests[i]);
}

// Input: Disk size and initial head position
printf("Enter the disk size: ");
scanf("%d", &disk_size);

printf("Enter the initial head position: ");
scanf("%d", &head);

// Input: Direction (0 for left, 1 for right)
printf("Enter the direction (0 = left, 1 = right): ");
scanf("%d", &direction);

// Calculate total seek time using SCAN
int total_seek_time = scan_disk_scheduling(requests, n, head, disk_size, direction);

printf("Total Seek Time using SCAN: %d ms\n", total_seek_time);

return 0;
}

/*
7
200
50
82 170 43 140 24 16 190
*/