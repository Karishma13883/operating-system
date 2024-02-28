#include <stdio.h>
typedef struct {
    int pid; 
    int burst_time; 
    int arrival_time; 
    int completion_time; 
    int turnaround_time; 
    int waiting_time; 
    int executed; 
} Process;
void calculateTimes(Process processes[], int n) {
    int current_time = 0;
    int completed_processes = 0;

    while (completed_processes < n) {
        int shortest_job_index = -1;
        int shortest_job_time = _INT_MAX_;
        for (int i = 0; i < n; ++i) {
            if (processes[i].arrival_time <= current_time && !processes[i].executed && processes[i].burst_time < shortest_job_time) {
                shortest_job_index = i;
                shortest_job_time = processes[i].burst_time;
            }
        }

        if (shortest_job_index == -1) {
            int next_arrival = _INT_MAX_;
            for (int i = 0; i < n; ++i) {
                if (processes[i].arrival_time > current_time && processes[i].arrival_time < next_arrival) {
                    next_arrival = processes[i].arrival_time;
                }
            }
            current_time = next_arrival;
        } else {
            processes[shortest_job_index].completion_time = current_time + processes[shortest_job_index].burst_time;
            processes[shortest_job_index].turnaround_time = processes[shortest_job_index].completion_time - processes[shortest_job_index].arrival_time;
            processes[shortest_job_index].waiting_time = processes[shortest_job_index].turnaround_time - processes[shortest_job_index].burst_time;
            processes[shortest_job_index].executed = 1;
            current_time = processes[shortest_job_index].completion_time;
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
    printf("Enter burst time and arrival time for each process:\n");
    for (int i = 0; i < n; ++i) {
        processes[i].pid = i + 1;
        printf("Process %d: ", i + 1);
        scanf("%d %d", &processes[i].burst_time, &processes[i].arrival_time);
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

