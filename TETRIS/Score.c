#include "Score.h"
#include <time.h>
#include <Windows.h>

extern CONTINUED;
extern SCORE;
extern LINETHATCLEARED;
extern T_SIPIN_COUNTER;


//인자값은 소거된 항의 개수, 리턴값으로 점수를 줌 점수 산정식 지워진 열^2 연속호출시 가산 티스핀 가산
int Score(int ClearLine) {/*소거열 또는 회전에서 받은 티스핀 판정*/
    printf("\x1b[%d;%dH", 22, 1);
    int ExtraPoint = CONTINUED / 2 + 1;
    LINETHATCLEARED += ClearLine;

    if (CONTINUED) {//연속 판별
        printf("\x1b[%d;%dH", 24, 1);
        printf("Removed line : %d", LINETHATCLEARED);
        if (CONTINUED < 9 && CONTINUED > 1) {
            printf("\nYou are clearing The %d lines in a row!\nScore multiplier [X%d point]", CONTINUED, ExtraPoint);
        }
        if (5 == ExtraPoint) {
            printf("\nMAx Multiplier");
            Sleep(500); printf("                       ");
        }
    }
    if (ClearLine != 2) T_SIPIN_COUNTER = 0;
    if (T_SIPIN_COUNTER) {
        printf("\a");
        printf("\x1b[%d;%dH", 22, 1);
        printf("                                 ");
        for (int i = 0; i < 11; i++) {//글씨반짝임
            printf("\x1b[%d;%dH", 22, 1);
            printf("``` `````` ```");
            Sleep(5);
            printf("\x1b[%d;%dH", 22, 1);
            printf("!!! T-spin !!!!\nYou got a %d point !", 100 * ExtraPoint);//행동 출력
            Sleep(100);
        }
        SCORE += 100 * ExtraPoint;
        T_SIPIN_COUNTER = 0;
        return 1;
    }

    switch (ClearLine) {
    case 1:
        SCORE += 20 * ExtraPoint;
        return 1;
        break;
    case 2:
        SCORE += 50 * ExtraPoint;
        return 1;
        break;
    case 3:
        SCORE += 75 * ExtraPoint;
        return 1;
        break;
    }

    if (4 == ClearLine) {
        printf("\a");
        printf("\x1b[%d;%dH", 22, 1);
        printf("                                 ");
        for (int i = 0; i < 11; i++) {//글씨반짝임
            printf("\x1b[%d;%dH", 22, 1);
            printf("``` `````` ```");
            Sleep(5);
            printf("\x1b[%d;%dH", 22, 1);
            printf("!!! TETRIS !!!\nYou got a %d point !", 100 * ExtraPoint);//행동 출력
            Sleep(100);
        }
        SCORE += 100 * ExtraPoint;
        return 1;
    }
    return 0;
}