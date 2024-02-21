#include <stdio.h>

#define MAX_PROCESSES 10

typedef struct {
    int id;
    int burst_time;
    int arrival_time;
    int priority;
    int waiting_time;
    int turnaround_time;
} Process;

void printAuthorInfo() {
    printf("\n@Author: Vaibhav Kumawat\n");
    printf("@Version: 1.0, 21/02/2024\n");
    printf("\nSJF-NP with Priority CPU Scheduling Algorithm\n");
}

void sort_by_arrival_time(Process processes[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (processes[j].arrival_time > processes[j + 1].arrival_time) {
                Process temp = processes[j];
                processes[j] = processes[j + 1];
                processes[j + 1] = temp;
            }
        }
    }
}

void sjf_np_with_priority(Process processes[], int n) {
    sort_by_arrival_time(processes, n);
    
    printf("\n*****OUTPUT*****\n");
    
    printf("Gantt Chart:\n");
    int current_time = 0;
    while (1) {
        int next_process = -1;
        int shortest_burst_time = 999999; // some large value
        for (int i = 0; i < n; i++) {
            if (processes[i].burst_time > 0 && processes[i].arrival_time <= current_time && processes[i].priority < shortest_burst_time) {
                next_process = i;
                shortest_burst_time = processes[i].priority;
            }
        }
        if (next_process == -1) {
            break;
        }
        printf("AT%d [P%d] ET%d ", current_time, processes[next_process].id, current_time + processes[next_process].burst_time);
        current_time += processes[next_process].burst_time;
        processes[next_process].turnaround_time = current_time - processes[next_process].arrival_time;
        processes[next_process].waiting_time = processes[next_process].turnaround_time - processes[next_process].burst_time;
        processes[next_process].burst_time = 0;
    }
        printf("\n\nProcess\tBurst-time(s)\tArrival-time(s)\tPriority\tWaiting-time(s)\tTurnaround-time(s)\n");
        for (int i = 0; i < n; i++) {
            printf("P%d\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n", processes[i].id, processes[i].burst_time, processes[i].arrival_time, processes[i].priority, processes[i].waiting_time, processes[i].turnaround_time);
        }

}

int main() {
    int n;

    printAuthorInfo();
    printf("\n*****Input*****\n");
    printf("Enter Number of Processes (maximum %d): ", MAX_PROCESSES);
    scanf("%d", &n);
    
    Process processes[MAX_PROCESSES];
    printf("Enter burst time for processes (separated by space): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].burst_time);
    }
    printf("Enter arrival time for processes (separated by space): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].arrival_time);
    }
    printf("Enter priority for processes (separated by space): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &processes[i].priority);
        processes[i].id = i + 1;
    }
    
    sjf_np_with_priority(processes, n);
    
    return 0;
}
