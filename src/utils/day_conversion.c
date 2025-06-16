#include <stdio.h>
#include "./utils/day_conversion.h"

// Array com o número acumulado de dias até o início de cada mês (não bissexto)
int days_until_month[13] = {
    0,   // Start of January
    31,  // Start of February
    59,  // Start of March
    90,  // Start of April
    120, // Start of May
    151, // Start of June
    181, // Start of July
    212, // Start of August
    243, // Start of September
    273, // Start of October
    304, // Start of November
    334, // Start of December
    365  // End of year
};

// Função que retorna o dia do ano dado o mês e o dia
int day_of_year(int month, int day) {
    if (month < 1 || month > 12 || day < 1 || day > 31) {
        return -1; // Retorna -1 para entradas inválidas
    }
    return days_until_month[month - 1] + day;
}

void month_day(int day_of_year, int* month, int* day) {
    if (day_of_year < 1 || day_of_year > 365) {
        *month = -1; // Invalid input
        *day = -1;   // Invalid input
        return;
    }

    // Loop through each month to find where the day fits
    for (int i = 0; i < 12; i++) {
        if (day_of_year <= days_until_month[i + 1]) {
            *month = i + 1;
            *day = day_of_year - days_until_month[i];
            return;
        }
    }

    // If day_of_year doesn't match, set to invalid
    *month = -1;
    *day = -1;
}


