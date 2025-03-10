/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    basic_function.c
  * @brief   This file contains the headers of the interrupt handlers.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2025
  * All rights reserved.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

#include "basic_functions.h"
#include "stdint.h"
#include "stm32f1xx_hal.h"  // Für HAL_MAX_DELAY
#include "usart.h"
#include "stdarg.h"

void uprints(char* first_str, ...) {
    va_list args;  // Argumentenliste für variable Argumente
    va_start(args, first_str);  // Initialisierung der Argumentenliste mit dem ersten übergebenen Argument

    const char* current_str = first_str;  // Zeiger auf die aktuelle Zeichenkette in der Argumentenliste

    while (current_str != NULL) {
        // Jedes Zeichen der aktuellen Zeichenkette über UART übertragen
        while (*current_str != '\0') {
            HAL_UART_Transmit(&huart2, (uint8_t*)current_str, 1, 0xF);  // Achte darauf, dass 'huart2' richtig definiert ist
            current_str++;  // Zum nächsten Zeichen in der aktuellen Zeichenkette wechseln
        }

        // Zum nächsten String in der Argumentenliste wechseln
        current_str = va_arg(args, char*);
    }

    va_end(args);  // Aufräumen der Argumentenliste nach Verwendung
}

void u32toStringDec(uint32_t value, char* buffer) {
    // Anzahl der Ziffern in der Zahl bestimmen
    int numDigits = 1;  // Mindestens eine Ziffer für den Wert 0
    uint32_t temp = value;

    // Schleife, um die Anzahl der Ziffern zu bestimmen
    while (temp >= 10) {
        temp /= 10;
        numDigits++;
    }

    // Umwandlung der Zahl in eine Zeichenkette ohne Umkehrung
    for (int i = numDigits - 1; i >= 0; --i) {
        buffer[i] = '0' + (value % 10);  // Das letzte Ziffer durch Modulo extrahieren
        value /= 10;  // Die letzte Ziffer entfernen
    }

    buffer[numDigits] = '\0';  // Null-Zeichen für das Ende der Zeichenkette hinzufügen
}


void i32toStringDec(int32_t value, char* buffer) {
    int isNegative = (value < 0);  // Überprüfen, ob die Zahl negativ ist

    int numDigits = 1;  // Mindestens eine Ziffer für den Wert 0
    int32_t temp = (isNegative) ? -value : value;  // Temporäre Variable für die Berechnung der Anzahl der Ziffern

    if (isNegative) {
        buffer[0] = '-';  // Wenn negativ, füge das Minuszeichen zum Puffer hinzu
        value = -value;  // Mache den Wert positiv für die spätere Verarbeitung
    }

    // Schleife zur Bestimmung der Anzahl der Ziffern in der Zahl
    while (temp >= 10) {
        temp /= 10;
        numDigits++;
    }

    // Schleife zur Umwandlung der Zahl in eine Zeichenkette
    for (int i = numDigits + isNegative - 1; i >= isNegative; --i) {
        buffer[i] = '0' + (value % 10);  // Das letzte Ziffer durch Modulo extrahieren
        value /= 10;  // Die letzte Ziffer entfernen
    }

    buffer[numDigits + isNegative] = '\0';  // Null-Zeichen für das Ende der Zeichenkette hinzufügen
}
