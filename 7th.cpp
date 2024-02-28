#include <stdio.h>
struct process {
  int pid; 
  int arrival_time; 
  int burst_time; 
  int waiting_time; 
  int turnaround_time; 
};
void sort_processes(struct process *processes, int n) {
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      if (processes[j].burst_time > processes[j + 1].burst_time) {
        struct process temp = processes[j];
        processes[j] = processes[j + 1];
        processes[j + 1] = temp;
      }
    }
  }
}
void calculate_waiting_and_turnaround_time(struct process *processes, int n) {
  processes[0].waiting_time = 0;
  processes[0].turnaround_time = processes[0].burst_time;
  for (int i = 1; i < n; i++) {
    processes[i].waiting_time = processes[i - 1].turnaround_time;
    processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
  }
}
void print_process_schedule(struct process *processes, int n) {
  printf("Process ID\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time\n");
  for (int i = 0; i < n; i++) {
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].pid, processes[i].arrival_time, processes[i].burst_time, processes[i].waiting_time, processes[i].turnaround_time);
  }
}
int main() {
  int n; 
  printf("Enter the number of processes: ");
  scanf("%d", &n);
  struct process processes[n];
  for (int i = 0; i < n; i++) {
    printf("Enter the arrival time and burst time for process %d: ", i + 1);
    scanf("%d %d", &processes[i].arrival_time, &processes[i].burst_time);
    processes[i].pid = i + 1;
  }
  sort_processes(processes, n);
  calculate_waiting_and_turnaround_time(processes, n);
  print_process_schedule(processes, n);

  return 0;
}
