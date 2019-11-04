#include <stdio.h>
#include <stdlib.h>

#define input_i(msg, f, num_ad) {printf(msg); scanf(f, num_ad);}

struct Process {
    int pid;
    float bt;
    float wt;
    float tt;
};

struct Bus {
    int size;
    struct Process *bus;
};

int main() {

    int pid_num = 0;

    input_i("Input number of processes: ", "%d", &pid_num)


    struct Bus p_bus = {pid_num, calloc(pid_num, sizeof(int))};

    for (int i = 0; i < pid_num; ++i) {
        float bt = 0;

        printf("PID %d ", i);
        input_i("\nBurst time: ", "%f", &bt)

        if (i == 0) {
            struct Process p = {i, bt, 0, bt};
            p_bus.bus[i] = p;
        } else {
            float wt = (p_bus.bus[i - 1].bt + p_bus.bus[i - 1].wt);
            float tt = bt + wt;
            struct Process p = {i, bt, wt, tt};
            p_bus.bus[i] = p;
        }
    }

    float sum_wt = 0;
    float sum_tt = 0;

    printf("\nPID\t\t bt\t\t wt\t\t tt");
    for (int j = 0; j < pid_num; ++j) {
        struct Process p = p_bus.bus[j];
        printf("\n%d\t\t%.1f\t\t%.1f\t\t%.1f", p.pid, p.bt, p.wt, p.tt);

        sum_wt += p.wt;
        sum_tt += p.tt;
    }

    float avg_wt = sum_wt / (float) pid_num;
    float avg_tt = sum_tt / (float) pid_num;

    printf("\n\navg wt = %.2f\navg tt = %.2f", avg_wt, avg_tt);

    return 0;
}