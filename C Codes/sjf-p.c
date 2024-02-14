#include<stdio.h>
#include<stdlib.h>

struct node {
    char pname;
    int btime;
    int atime;
    int restime;
    int ctime;
    int wtime;
};

struct node a[10], b[10], c[10];


void insert(int n) {
    int i;
    printf("Enter burst times for processes (separated by space): ");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i].btime);
        a[i].pname = i + 1 + '0';
    }

    printf("Enter arrival times for processes (separated by space): ");
    for (i = 0; i < n; i++) {
        scanf("%d", &a[i].atime);
    }

    for (i = 0; i < n; i++) {
        a[i].wtime = -a[i].atime + 1;
    }
}

int btimeSort(const void *a, const void *b) {
    return ((struct node*)a)->btime - ((struct node*)b)->btime;
}

int atimeSort(const void *a, const void *b) {
    return ((struct node*)a)->atime - ((struct node*)b)->atime;
}

int k = 0, f = 0, r = 0;

void disp(int nop, int qt) {
    int n = nop, q;
    qsort(a, n, sizeof(struct node), atimeSort);
    int ttime = 0, i;
    int j, tArray[n];
    int alltime = 0;
    int moveLast = 0;

    for (i = 0; i < n; i++) {
        alltime += a[i].btime;
    }
    alltime += a[0].atime;

    for (i = 0; ttime <= alltime;) {
        j = i;
        while (a[j].atime <= ttime && j != n) {
            b[r] = a[j];
            j++;
            r++;
        }
        if (r == f) {
            c[k].pname = 'i';
            c[k].btime = a[j].atime - ttime;
            c[k].atime = ttime;
            ttime += c[k].btime;
            k++;
            continue;
        }
        i = j;
        if (moveLast == 1) {
            qsort(b + f, r - f, sizeof(struct node), btimeSort);
        }
        j = f;
        if (b[j].btime > qt) {
            c[k] = b[j];
            c[k].btime = qt;
            k++;
            b[j].btime = b[j].btime - qt;
            ttime += qt;
            moveLast = 1;
            for (q = 0; q < n; q++) {
                if (b[j].pname != a[q].pname) {
                    a[q].wtime += qt;
                }
            }
        }
        else {
            c[k] = b[j];
            k++;
            f++;
            ttime += b[j].btime;
            moveLast = 0;
            for (q = 0; q < n; q++) {
                if (b[j].pname != a[q].pname) {
                    a[q].wtime += b[j].btime;
                }
            }
        }
        if (f == r && i >= n)
            break;
    }

    tArray[i] = ttime;
    ttime += a[i].btime;
    for (i = 0; i < k - 1; i++) {
        if (c[i].pname == c[i + 1].pname) {
            c[i].btime += c[i + 1].btime;
            for (j = i + 1; j < k - 1; j++)
                c[j] = c[j + 1];
            k--;
            i--;
        }
    }

    int rtime = 0;
    for (j = 0; j < n; j++) {
        rtime = 0;
        for (i = 0; i < k; i++) {
            if (c[i].pname == a[j].pname) {
                a[j].restime = rtime;
                break;
            }
            rtime += c[i].btime;
        }
    }

    float averageWaitingTime = 0;
    float averageResponseTime = 0;
    float averageTAT = 0;


    printf("\n*****OUTPUT*****\n");
    // Display Gantt chart
    printf("Gantt Chart:\n");
    rtime = 0;
    for (i = 0; i < k; i++) {
        printf("    %d   ", c[i].btime);
    }
    printf("\n");
    for (i = 0; i < k; i++) {
        printf("|  P%c   ", c[i].pname);
        rtime += c[i].btime;
        for (j = 0; j < n; j++) {
            if (a[j].pname == c[i].pname)
                a[j].ctime = rtime;
        }
    }
    printf("|\n");
    rtime = 0;
    for (i = 0; i < k + 1; i++) {
        printf("%d\t", rtime);
        tArray[i] = rtime;
        rtime += c[i].btime;
    }
    printf("\n\n");
    printf("Process  Burst-time(s)  Arrival-time(s)  Response-time(s)  Waiting-time(s)  Turnaround-time(s)\n");

    for (i = 0; i < nop && a[i].pname != 'i'; i++) {
        if (a[i].pname == '\0')
            break;
        // Adjust the width as needed for each column
        printf("P%-14c", a[i].pname);
        printf("%-14d", a[i].btime);
        printf("%-17d", a[i].atime);

        printf("%-18d", a[i].restime - a[i].atime);
        averageResponseTime += a[i].restime - a[i].atime;

        printf("%-18d", a[i].wtime + a[i].ctime - rtime);
        averageWaitingTime += a[i].wtime + a[i].ctime - rtime;

        printf("%-20d", a[i].wtime + a[i].ctime - rtime + a[i].btime);
        averageTAT += a[i].wtime + a[i].ctime - rtime + a[i].btime;

        printf("\n");
    }

    printf("\n");
    printf("Average Response time: %.2f\n", (float)averageResponseTime / (float)n);
    printf("Average Waiting time: %.2f\n", (float)averageWaitingTime / (float)n);
    printf("Average TA time: %.2f\n", (float)averageTAT / (float)n);
    printf("CPU idle time(s): %d\n", ttime - alltime);
}

int main() {
    int nop, i, qt;
    
    // Author and version information
    printf("\n@Author: Vaibhav Kumawat\n");
    printf("@Version: 1.0, 14/02/2024\n");
    printf("\nSJF-P CPU Scheduling Algorithm\n");

    printf("\n*****INPUT*****");
    printf("\nEnter number of processes (maximum 10): ");
    scanf("%d", &nop);
    insert(nop);
    disp(nop, 1);
    return 0;
}
