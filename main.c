#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "utils.h"

// 1. Spannung berechnen
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

// 2. Strom berechnen
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

// 3. Widerstand berechnen
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

// 4. Leistung berechnen
void calculate_power() {
    float V, I;
    printf("Enter voltage (V in volts): ");
    scanf("%f", &V);
    printf("Enter current (I in amperes): ");
    scanf("%f", &I);
    float P = V * I;
    printf("Power (P) = %.2f watts\n", P);
    char result[100];
    sprintf(result, "Calculated Power: %.2f W (V=%.2f, I=%.2f)", P, V, I);
    save_to_file(result);
}

// 5. input.txt laden (mehrere Datensätze)
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

// 6. Farbcode (Textbasiert)
int color_to_digit(const char *color) {
    if (strcmp(color, "schwarz") == 0) return 0;
    if (strcmp(color, "braun") == 0) return 1;
    if (strcmp(color, "rot") == 0) return 2;
    if (strcmp(color, "orange") == 0) return 3;
    if (strcmp(color, "gelb") == 0) return 4;
    if (strcmp(color, "gruen") == 0) return 5;
    if (strcmp(color, "blau") == 0) return 6;
    if (strcmp(color, "violett") == 0) return 7;
    if (strcmp(color, "grau") == 0) return 8;
    if (strcmp(color, "weiss") == 0) return 9;
    return -1;
}

void resistor_color_code() {
    char color1[20], color2[20], multiplier_color[20];
    printf("Enter first band color: ");
    scanf("%s", color1);
    printf("Enter second band color: ");
    scanf("%s", color2);
    printf("Enter multiplier band color: ");
    scanf("%s", multiplier_color);

    int d1 = color_to_digit(color1);
    int d2 = color_to_digit(color2);
    int mult = color_to_digit(multiplier_color);

    if (d1 == -1 || d2 == -1 || mult == -1) {
        printf("Invalid color input.\n");
        return;
    }

    long resistance = (d1 * 10 + d2) * pow(10, mult);
    printf("Resistance: %ld ohms\n", resistance);

    char result[150];
    sprintf(result, "Resistor Code: %s-%s-%s = %ld ohms", color1, color2, multiplier_color, resistance);
    save_to_file(result);
}

// 7. Spannungsteiler
void voltage_divider() {
    float Vin, R1, R2;
    printf("Enter input voltage (Vin): ");
    scanf("%f", &Vin);
    printf("Enter R1 (ohms): ");
    scanf("%f", &R1);
    printf("Enter R2 (ohms): ");
    scanf("%f", &R2);

    float Vout = Vin * R2 / (R1 + R2);
    printf("Output Voltage (Vout) across R2: %.2f V\n", Vout);

    char result[150];
    sprintf(result, "Voltage Divider: Vin=%.2f, R1=%.2f, R2=%.2f → Vout=%.2f V", Vin, R1, R2, Vout);
    save_to_file(result);
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
        printf("6. Calculate Power (P = V × I)\n");
        printf("7. Resistor Color Code Calculator\n");
        printf("8. Voltage Divider Simulation\n");
        printf("Choose an option (1–8): ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: calculate_voltage(); break;
            case 2: calculate_current(); break;
            case 3: calculate_resistance(); break;
            case 4: load_from_file(); break;
            case 5: printf("Goodbye!\n"); break;
            case 6: calculate_power(); break;
            case 7: resistor_color_code(); break;
            case 8: voltage_divider(); break;
            default: printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}