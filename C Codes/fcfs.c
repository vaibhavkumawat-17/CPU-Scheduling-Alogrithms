#include <stdio.h>

int main() {
    int at[10], at2[10], bt[10], ex[10], seq[10], re[10], wt[10], tat[10];
    int n, i, j, start, pos, max = 0, min, idle = 0, k = 0;
    float av1 = 0, av2 = 0;


    // Author and version information
    printf("\n@Author: Vaibhav Kumawat\n");
    printf("@Version: 1.0, 14/02/2024\n");
    printf("\nFCFS CPU Scheduling Algorithm\n");

    printf("\n*****INPUT*****");
    printf("\nEnter number of processes (maximum 10): ");
    scanf("%d", &n);

    printf("Enter burst time for processes (separated by space):");
    for (i = 0; i < n; i++) {
        scanf("%d", &bt[i]);
    }

    printf("Enter arrival time for processes (separated by space):");
    for (i = 0; i < n; i++) {
        scanf("%d", &at[i]);
        at2[i] = at[i];
    }

    start = at[0];
    for (i = 1; i < n; i++) {
        if (start > at[i]) {
            start = at[i];
        }
    }

    printf("\n*****OUTPUT*****\n");

    printf("Gantt chart:\n");
    for (i = 0; i < n; i++) {
        if (max < at[i]) {
            max = at[i];
        }
    }

    max = max + 1;
    for (i = 1; i <= n; i++, k++) {
        min = max;
        for (j = 0; j < n; j++) {
            if (at[j] != -1) {
                if (at[j] < min) {
                    min = at[j];
                    pos = j;
                }
            }
        }

        if (start < at[pos]) {
            printf("[-]   ");
            idle += at[pos] - start;
            start = at[pos];
        }

        printf("AT%d   ", start);
        printf("[P%d]  ", pos + 1);
        seq[k] = pos;

        re[pos] = start;
        printf("ET%d   ", start + bt[pos]);
        start += bt[pos];
        at[pos] = -1;
        ex[pos] = start;
    }

    for (i = 0; i < n; i++) {
        tat[i] = ex[i] - at2[i];
        wt[i] = tat[i] - bt[i];
    }
    printf("\n");

    printf("\nProcess  Burst-time(s)  Arrival-time(s)  Waiting-time(s)  Turnaround-time(s)\n");
    for (i = 0; i < n; i++) {
        printf("P%d            %2d              %2d             %2d               %2d\n", i+1,  bt[i],at2[i], wt[i], tat[i]);
    }

    for (i = 0; i < n; i++) {
        av1 += tat[i];
        av2 += wt[i];
    }

    printf("\nAverage waiting time(s): %0.2f\n", av2 / n);
    printf("Average turnaround time(s): %0.2f\n", av1 / n);
    printf("CPU idle time(s): %d\n", idle);

    return 0;
}
