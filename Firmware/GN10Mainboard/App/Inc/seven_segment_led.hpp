#pragma once
#include <stdint.h>
#include "gpio.h"

namespace SevenSegmentLED
{
    // number
    uint8_t number_patterns[10][7] = {
        {1, 1, 1, 1, 1, 1, 0}, // 0
        {0, 1, 1, 0, 0, 0, 0}, // 1
        {1, 1, 0, 1, 1, 0, 1}, // 2
        {1, 1, 1, 1, 0, 0, 1}, // 3
        {0, 1, 1, 0, 0, 1, 1}, // 4
        {1, 0, 1, 1, 0, 1, 1}, // 5
        {1, 0, 1, 1, 1, 1, 1}, // 6
        {1, 1, 1, 0, 0, 0, 0}, // 7
        {1, 1, 1, 1, 1, 1, 1}, // 8
        {1, 1, 1, 1, 0, 1, 1}  // 9
    };
    // alphabet
    uint8_t A[7] = {1, 1, 1, 0, 1, 1, 1};
    uint8_t B[7] = {0, 0, 1, 1, 1, 1, 1};
    uint8_t C[7] = {1, 0, 0, 1, 1, 1, 0};
    uint8_t D[7] = {0, 1, 1, 1, 1, 0, 1};
    uint8_t E[7] = {1, 0, 0, 1, 1, 1, 1};
    uint8_t F[7] = {1, 0, 0, 0, 1, 1, 1};
    uint8_t G[7] = {1, 0, 1, 1, 1, 1, 1};
    uint8_t H[7] = {0, 1, 1, 0, 1, 1, 1};
    uint8_t I[7] = {0, 0, 0, 0, 1, 1, 0};
    uint8_t J[7] = {0, 1, 1, 1, 0, 0, 0};
    uint8_t K[7] = {1, 0, 0, 0, 1, 1, 1};
    uint8_t L[7] = {0, 0, 0, 1, 1, 1, 0};
    uint8_t M[7] = {1, 1, 1, 0, 1, 0, 1};
    uint8_t N[7] = {0, 1, 1, 0, 1, 0, 1};
    uint8_t O[7] = {0, 0, 1, 1, 1, 1, 1};
    uint8_t P[7] = {1, 1, 0, 0, 1, 1, 1};
    uint8_t Q[7] = {1, 1, 1, 0, 0, 1, 1};
    uint8_t R[7] = {0, 0, 0, 0, 1, 0, 1};
    uint8_t S[7] = {1, 0, 1, 1, 0, 1, 1};
    uint8_t T[7] = {1, 1, 1, 1, 1, 1, 0};
    uint8_t U[7] = {0, 1, 1, 1, 1, 1, 0};
    uint8_t V[7] = {1, 1, 1, 1, 1, 0, 0};
    uint8_t W[7] = {1, 1, 1, 1, 1, 1, 0};
    uint8_t X[7] = {1, 1, 1, 0, 1, 1, 1};
    uint8_t Y[7] = {1, 1, 1, 1, 0, 1, 1};
    uint8_t Z[7] = {1, 1, 0, 1, 1, 0, 1};

    void set_pattern(uint8_t *pattern)
    {
        HAL_GPIO_WritePin(LED_A_GPIO_Port, LED_A_Pin, pattern[0] ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, pattern[1] ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_C_GPIO_Port, LED_C_Pin, pattern[2] ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_D_GPIO_Port, LED_D_Pin, pattern[3] ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_E_GPIO_Port, LED_E_Pin, pattern[4] ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_F_GPIO_Port, LED_F_Pin, pattern[5] ? GPIO_PIN_SET : GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, pattern[6] ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }

    void set_number(uint8_t number)
    {
        if (number < 10)
        {
            set_pattern(number_patterns[number]);
        }
    }

    void set_alphabet(char alphabet)
    {
        switch (alphabet)
        {
        case 'A':
            set_pattern(A);
            break;
        case 'B':
            set_pattern(B);
            break;
        case 'C':
            set_pattern(C);
            break;
        case 'D':
            set_pattern(D);
            break;
        case 'E':
            set_pattern(E);
            break;
        case 'F':
            set_pattern(F);
            break;
        case 'G':
            set_pattern(G);
            break;
        case 'H':
            set_pattern(H);
            break;
        case 'I':
            set_pattern(I);
            break;
        case 'J':
            set_pattern(J);
            break;
        case 'K':
            set_pattern(K);
            break;
        case 'L':
            set_pattern(L);
            break;
        case 'M':
            set_pattern(M);
            break;
        case 'N':
            set_pattern(N);
            break;
        case 'O':
            set_pattern(O);
            break;
        case 'P':
            set_pattern(P);
            break;
        case 'Q':
            set_pattern(Q);
            break;
        case 'R':
            set_pattern(R);
            break;
        case 'S':
            set_pattern(S);
            break;
        case 'T':
            set_pattern(T);
            break;
        case 'U':
            set_pattern(U);
            break;
        case 'V':
            set_pattern(V);
            break;
        case 'W':
            set_pattern(W);
            break;
        case 'X':
            set_pattern(X);
            break;
        case 'Y':
            set_pattern(Y);
            break;
        case 'Z':
            set_pattern(Z);
            break;
        default:
            break;
        }
    }

    void set_blank()
    {
        HAL_GPIO_WritePin(LED_A_GPIO_Port, LED_A_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_B_GPIO_Port, LED_B_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_C_GPIO_Port, LED_C_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_D_GPIO_Port, LED_D_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_E_GPIO_Port, LED_E_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_F_GPIO_Port, LED_F_Pin, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(LED_G_GPIO_Port, LED_G_Pin, GPIO_PIN_RESET);
    }

    void set_dot(bool dot)
    {
        HAL_GPIO_WritePin(LED_DP_GPIO_Port, LED_DP_Pin, dot ? GPIO_PIN_SET : GPIO_PIN_RESET);
    }
}