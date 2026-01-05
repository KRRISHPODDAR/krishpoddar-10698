/*
 * Project: Electricity Bill Calculator
 * Author: Antigravity (AI Assistant)
 * Date: 2026-01-05
 * 
 * Description: 
 * This program calculates the electricity bill for a consumer based on unit consumption.
 * It uses a slab-based rate structure and includes fixed charges and surcharges.
 */

#include <stdio.h>
#include <string.h>

int main() {
    // Variable Declarations
    char consumer_name[100];
    int consumer_id;
    int units_consumed;
    float total_energy_charge = 0.0;
    float fixed_charge = 50.00; // Fixed charge for connection
    float surcharge = 0.00;
    float total_bill = 0.00;

    // Rate Constants
    const float RATE_SLAB_1 = 1.50; // First 100 units
    const float RATE_SLAB_2 = 2.50; // Next 100 units (101-200)
    const float RATE_SLAB_3 = 4.00; // Above 200 units
    const float SURCHARGE_RATE = 0.10; // 10% surcharge
    const float SURCHARGE_THRESHOLD = 500.00; // Threshold for surcharge

    // Input Section
    printf("----------------------------------------\n");
    printf("      ELECTRICITY BILL CALCULATOR       \n");
    printf("----------------------------------------\n");
    
    printf("Enter Consumer Name: ");
    // data input using fgets to handle spaces in names
    fgets(consumer_name, sizeof(consumer_name), stdin);
    // Remove trailing newline character if present
    consumer_name[strcspn(consumer_name, "\n")] = 0;

    printf("Enter Consumer ID: ");
    if (scanf("%d", &consumer_id) != 1) {
        printf("Invalid Input! Consumer ID must be a number.\n");
        return 1;
    }

    printf("Enter Units Consumed: ");
    if (scanf("%d", &units_consumed) != 1 || units_consumed < 0) {
        printf("Invalid Input! Units must be a non-negative number.\n");
        return 1;
    }

    // Calculation Section - Slab Based Logic
    if (units_consumed <= 100) {
        total_energy_charge = units_consumed * RATE_SLAB_1;
    } else if (units_consumed <= 200) {
        // First 100 units at slab 1
        total_energy_charge = (100 * RATE_SLAB_1);
        // Remaining units at slab 2
        total_energy_charge += (units_consumed - 100) * RATE_SLAB_2;
    } else {
        // First 100 at slab 1
        total_energy_charge = (100 * RATE_SLAB_1);
        // Next 100 at slab 2
        total_energy_charge += (100 * RATE_SLAB_2);
        // Remaining at slab 3
        total_energy_charge += (units_consumed - 200) * RATE_SLAB_3;
    }

    // Calculate Total Bill before surcharge
    total_bill = total_energy_charge + fixed_charge;

    // Surcharge Logic
    if (total_bill > SURCHARGE_THRESHOLD) {
        surcharge = total_bill * SURCHARGE_RATE;
        total_bill += surcharge;
    }

    // Output Section
    printf("\n\n");
    printf("========================================\n");
    printf("           ELECTRICITY BILL             \n");
    printf("========================================\n");
    printf("Consumer Name   : %s\n", consumer_name);
    printf("Consumer ID     : %d\n", consumer_id);
    printf("Units Consumed  : %d\n", units_consumed);
    printf("----------------------------------------\n");
    printf("Breakdown:\n");
    
    // Detailed breakdown display logic for transparency
    if (units_consumed <= 100) {
         printf("  0 - %d units @ %.2f : %.2f\n", units_consumed, RATE_SLAB_1, units_consumed * RATE_SLAB_1);
    } else if (units_consumed <= 200) {
         printf("  0 - 100 units @ %.2f : %.2f\n", RATE_SLAB_1, 100 * RATE_SLAB_1);
         printf("  101 - %d units @ %.2f : %.2f\n", units_consumed, RATE_SLAB_2, (units_consumed - 100) * RATE_SLAB_2);
    } else {
         printf("  0 - 100 units @ %.2f : %.2f\n", RATE_SLAB_1, 100 * RATE_SLAB_1);
         printf("  101 - 200 units @ %.2f : %.2f\n", RATE_SLAB_2, 100 * RATE_SLAB_2);
         printf("  > 200 units @ %.2f    : %.2f\n", RATE_SLAB_3, (units_consumed - 200) * RATE_SLAB_3);
    }
    
    printf("----------------------------------------\n");
    printf("Energy Charge   : %.2f\n", total_energy_charge);
    printf("Fixed Charge    : %.2f\n", fixed_charge);
    printf("Surcharge       : %.2f\n", surcharge);
    printf("----------------------------------------\n");
    printf("TOTAL PAYABLE   : %.2f\n", total_bill);
    printf("========================================\n");

    return 0;
}
