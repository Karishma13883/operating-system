#include <stdio.h>
#define NUM_PROCESSES 5
#define NUM_RESOURCES 3
int available[NUM_RESOURCES];
int maximum[NUM_PROCESSES][NUM_RESOURCES];
int allocation[NUM_PROCESSES][NUM_RESOURCES];
int need[NUM_PROCESSES][NUM_RESOURCES];
int finish[NUM_PROCESSES];

void initialize() {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        scanf("%d", &available[i]);
    }

    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            scanf("%d", &maximum[i][j]);
        }
    }

    for (int i = 0; i < NUM_PROCESSES; i++) {
        for (int j = 0; j < NUM_RESOURCES; j++) {
            allocation[i][j] = 0;
            need[i][j] = maximum[i][j];
        }
        finish[i] = 0;
    }
}

int request_resources(int process_id, int request[]) {
    for (int i = 0; i < NUM_RESOURCES; i++) {
        if (request[i] > need[process_id][i] || request[i] > available[i]) {
            return 0;
        }
    }

    for (int i = 0; i < NUM_RESOURCES; i++) {
        available[i] -= request[i];
        allocation[process_id][i] += request[i];
        need[process_id][i] -= request[i];
    }

    if (is_safe()) {
        return 1;
    } else {
        for (int i = 0; i < NUM_RESOURCES; i++) {
            available[i] += request[i];
            allocation[process_id][i] -= request[i];
            need[process_id][i] += request[i];
        }
        return 0;
    }
}

int is_safe() {
    int work[NUM_RESOURCES];
    int finish_copy[NUM_PROCESSES];

    for (int i = 0; i < NUM_PROCESSES; i++) {
        finish_copy[i] = finish[i];
    }

    for (int i = 0; i < NUM_RESOURCES; i++) {
        work[i] = available[i];
    }

    int count = 0;
    while (count < NUM_PROCESSES) {
        int found = 0;
        for (int i = 0; i < NUM_PROCESSES; i++) {
            if (!finish_copy[i]) {
                int j;
                for (j = 0; j < NUM_RESOURCES; j++) {
                    if (need[i][j] > work[j]) {
                        break;
                    }
                }
                if (j == NUM_RESOURCES) {
                    finish_copy[i] = 1;
                    found = 1;
                    count++;
                    for (int k = 0; k < NUM_RESOURCES; k++) {
                        work[k] += allocation[i][k];
                    }
                }
            }
        }
        if (!found) {
            return 0;
        }
    }
    return 1;
}

int main() {
    initialize();

    int process_id = 0;
    int request[NUM_RESOURCES];
    for (int i = 0; i < NUM_RESOURCES; i++) {
        scanf("%d", &request[i]);
    }

    if (request_resources(process_id, request)) {
        printf("Request granted\n");
    } else {
        printf("Request denied\n");
    }

    return 0;
}

