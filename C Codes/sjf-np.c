#include <stdio.h>

struct proc {
    int no;
    int at;
    int bt;
    int it;
    int ct;
    int tat;
    int wt;
};

struct proc read(int i) {
    struct proc p;
    printf("\nProcess Number: %d\n", i);
    p.no = i;
    printf("Enter arrival time: ");
    scanf("%d", &p.at);
    printf("Enter burst time: ");
    scanf("%d", &p.bt);
    return p;
}

void printGanttChart(struct proc p[], int n) {
    printf("\nGantt Chart:\n");
    int currentTime = 0;
    for (int i = 0; i < n; i++) {
        printf("AT%d [P%d] ET%d ", currentTime, p[i].no, currentTime + p[i].bt);
        currentTime += p[i].bt;
    }
    printf("\n\n");
}

int main() {
    int n, j, min = 0;
    float avgtat = 0, avgwt = 0;
    struct proc p[10], temp;

    // Author and version information
    printf("\n@Author: Vaibhav Kumawat\n");
    printf("@Version: 1.0, 14/02/2024\n");
    printf("\nSJF-NP CPU Scheduling Algorithm\n");
    
    printf("\n*****INPUT*****");
    printf("\nEnter Number of Processes (maximum 10):");
    scanf("%d", &n);

    printf("Enter burst time for processes (separated by space): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].bt);
    }

    printf("Enter arrival time for processes (separated by space): ");
    for (int i = 0; i < n; i++) {
        scanf("%d", &p[i].at);
        p[i].no = i + 1;
    }

    for (int i = 0; i < n - 1; i++) {
        for (j = 0; j < n - i - 1; j++) {
            if (p[j].at > p[j + 1].at) {
                temp = p[j];
                p[j] = p[j + 1];
                p[j + 1] = temp;
            }
        }
    }
    for (j = 1; j < n && p[j].at == p[0].at; j++) {
        if (p[j].bt < p[min].bt) {
            min = j;
        }
    }
    temp = p[0];
    p[0] = p[min];
    p[min] = temp;
    p[0].it = p[0].at;
    p[0].ct = p[0].it + p[0].bt;
    for (int i = 1; i < n; i++) {
        for (j = i + 1, min = i; j < n && p[j].at <= p[i - 1].ct; j++) {
            if (p[j].bt < p[min].bt) {
                min = j;
            }
        }
        temp = p[i];
        p[i] = p[min];
        p[min] = temp;
        if (p[i].at <= p[i - 1].ct) {
            p[i].it = p[i - 1].ct;
        } else {
            p[i].it = p[i].at;
        }
        p[i].ct = p[i].it + p[i].bt;
    }

    printf("\n*****OUTPUT*****");
    printGanttChart(p, n);
    printf("Process\tBurst-time(s)\tArrival-time(s)\tWaiting-time(s)\tTurnaround-time(s)\n");
    for (int i = 0; i < n; i++) {
        p[i].tat = p[i].ct - p[i].at;
        avgtat += p[i].tat;
        p[i].wt = p[i].tat - p[i].bt; // Corrected waiting time calculation
        avgwt += p[i].wt; // Accumulating waiting times for average calculation
        printf("P%d\t%d\t\t%d\t\t%d\t\t%d\n", p[i].no, p[i].bt, p[i].at, p[i].wt, p[i].tat);
    }
    avgtat /= n;
    avgwt /= n;
    printf("\nAverage Turnaround Time : %.2f\nAverage Waiting Time : %.2f", avgtat, avgwt);
    return 0;
}
