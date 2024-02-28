#include<stdio.h>

// Structure to represent a process
struct Process {
    int process_id;
    int burst_time;
    int arrival_time;
    int waiting_time;
};

// Function to calculate waiting time for each process
void calculate_waiting_time(struct Process processes[], int n) {
    int total_waiting_time = 0;
    int current_time = 0;

    // Calculate waiting time for each process
    for (int i = 0; i < n; i++) {
        if (current_time < processes[i].arrival_time) {
            current_time = processes[i].arrival_time;
        }
        processes[i].waiting_time = current_time - processes[i].arrival_time;
        total_waiting_time += processes[i].waiting_time;
        current_time += processes[i].burst_time;
    }

    // Calculate average waiting time
    float avg_waiting_time = (float)total_waiting_time / n;
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
}

int main() {
    int n;

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process processes[n];

    // Input process details
    printf("Enter process ID, burst time, and arrival time for each process:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].process_id, &processes[i].burst_time, &processes[i].arrival_time);
    }

    // Calculate waiting time
    calculate_waiting_time(processes, n);

    return 0;
}

