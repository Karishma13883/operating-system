#include <stdio.h>
typedef struct {
    int pid; 
    int burst_time; 
    int arrival_time;
    int completion_time;
    int turnaround_time; 
    int waiting_time;
    int priority; 
    int executed; 
} Process;
void calculateTimes(Process processes[], int n) {
    int current_time = 0;
    int completed_processes = 0;
    while (completed_processes < n) {
        int highest_priority_index = -1;
        int highest_priority = -1;
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= current_time && !processes[i].executed && processes[i].priority > highest_priority) {
                highest_priority_index = i;
                highest_priority = processes[i].priority;
            }
        }
        if (highest_priority_index == -1) {
            int next_arrival = _INT_MAX_;
            for (int i = 0; i < n; ++i) {
                if (processes[i].arrival_time > current_time && processes[i].arrival_time < next_arrival) {
                    next_arrival = processes[i].arrival_time;
                }
            }
            current_time = next_arrival;
        } else {
            processes[highest_priority_index].completion_time = current_time + processes[highest_priority_index].burst_time;
            processes[highest_priority_index].turnaround_time = processes[highest_priority_index].completion_time - processes[highest_priority_index].arrival_time;
            processes[highest_priority_index].waiting_time = processes[highest_priority_index].turnaround_time - processes[highest_priority_index].burst_time;
            processes[highest_priority_index].executed = 1;
            current_time = processes[highest_priority_index].completion_time;
            completed_processes++;
        }
    }
}
void calculateAverages(Process processes[], int n, float *avg_turnaround_time, float *avg_waiting_time) {
    *avg_turnaround_time = 0;
    *avg_waiting_time = 0;
    for (int i = 0; i < n; ++i) {
        *avg_turnaround_time += processes[i].turnaround_time;
        *avg_waiting_time += processes[i].waiting_time;
    }
    *avg_turnaround_time /= n;
    *avg_waiting_time /= n;
}
void displayProcesses(Process processes[], int n) {
    printf("PID\tBurst Time\tArrival Time\tCompletion Time\tTurnaround Time\tWaiting Time\n");
    for (int i = 0; i < n; ++i) {
        printf("%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].burst_time, processes[i].arrival_time,
               processes[i].completion_time, processes[i].turnaround_time, processes[i].waiting_time);
    }
}
int main() {
    int n;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    Process processes[n];
    printf("Enter burst time, arrival time, and priority for each process:\n");
    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d %d", &processes[i].burst_time, &processes[i].arrival_time, &processes[i].priority);
        processes[i].executed = 0;
    }
    calculateTimes(processes, n);
    float avg_turnaround_time, avg_waiting_time;
    calculateAverages(processes, n, &avg_turnaround_time, &avg_waiting_time);
    displayProcesses(processes, n);
    printf("\nAverage Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    return 0;
}

