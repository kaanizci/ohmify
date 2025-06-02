#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "utils.h"
// utils.h


void calculate_voltage() {
    float I, R;
    printf("Enter current (I in amperes): ");
    scanf("%f", &I);
    printf("Enter resistance (R in ohms): ");
    scanf("%f", &R);
    float V = I * R;
    printf("Voltage (V) = %.2f V\n", V);
    char result[100];
    sprintf(result, "Calculated Voltage: %.2f V (I=%.2f, R=%.2f)", V, I, R);
    save_to_file(result);
}

void calculate_current() {
    float V, R;
    printf("Enter voltage (V in volts): ");
    scanf("%f", &V);
    printf("Enter resistance (R in ohms): ");
    scanf("%f", &R);
    float I = V / R;
    printf("Current (I) = %.2f A\n", I);
    char result[100];
    sprintf(result, "Calculated Current: %.2f A (V=%.2f, R=%.2f)", I, V, R);
    save_to_file(result);
}

void calculate_resistance() {
    float V, I;
    printf("Enter voltage (V in volts): ");
    scanf("%f", &V);
    printf("Enter current (I in amperes): ");
    scanf("%f", &I);
    float R = V / I;
    printf("Resistance (R) = %.2f ohms\n", R);
    char result[100];
    sprintf(result, "Calculated Resistance: %.2f ohms (V=%.2f, I=%.2f)", R, V, I);
    save_to_file(result);
}

void load_from_file() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Cannot open input.txt\n");
        return;
    }
    char line[100];
    float V = -1, I = -1, R = -1;
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\r\n")] = 0;
        if (strlen(line) == 0 || line[0] == '#') {
            if (V != -1 && I != -1) R = V / I;
            else if (V != -1 && R != -1) I = V / R;
            else if (I != -1 && R != -1) V = I * R;
            if ((V != -1 && I != -1) || (V != -1 && R != -1) || (I != -1 && R != -1)) {
                printf("Result: V=%.2f, I=%.2f, R=%.2f\n", V, I, R);
                char result[150];
                sprintf(result, "Loaded Result: V=%.2f, I=%.2f, R=%.2f", V, I, R);
                save_to_file(result);
            }
            V = I = R = -1;
            continue;
        }
        if (strncmp(line, "V=", 2) == 0) V = atof(line + 2);
        else if (strncmp(line, "I=", 2) == 0) I = atof(line + 2);
        else if (strncmp(line, "R=", 2) == 0) R = atof(line + 2);
    }
    fclose(file);
}

int main() {
    int choice;
    do {
        printf("\nWelcome to Ohmify!\n");
        printf("1. Calculate Voltage (V = I × R)\n");
        printf("2. Calculate Current (I = V ÷ R)\n");
        printf("3. Calculate Resistance (R = V ÷ I)\n");
        printf("4. Load values from input.txt\n");
        printf("5. Exit\n");
        printf("Choose an option (1–5): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: calculate_voltage(); break;
            case 2: calculate_current(); break;
            case 3: calculate_resistance(); break;
            case 4: load_from_file(); break;
            case 5: printf("Goodbye!\n"); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}