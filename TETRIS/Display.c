#include < stdio.h>
#include <time.h>
#include <Windows.h>
#include "Display.h"
#include "Utility.h"
#include "ArrayLogic.h"
#include "SponeBrick.h"

//Global
extern int ROW, COLUMN;
extern int SCORE;
extern int CONTINUED;
extern int LINETHATCLEARED;
extern int NEXT_BRICK[16];
extern int GameMap[210];
extern int RandomTable[100];

//Function declaration
void PrintDiplayLine();
int LoadMap();
int DisplayCursor(int row, int column);

//First Display part
int MainDisplay() {
    LoadMap();
    PrintDiplayLine();
    TextLog();
    return 0;
}

int scoreBoard(int index) {
    //score board
    printf("\x1b[%d;%dH", 2, 12);
    printf(" Level : %d \n", ((LINETHATCLEARED / 10) + 1)); //레벨은 시간 따라 높아지고 그래비티 가속함
    printf("\x1b[%d;%dH", 3, 12);
    printf(" Your Score : %d point\n", SCORE); //Score 함수 리턴값 부여

    printf("\x1b[%d;%dH", 22, 1);
    printf("                                    \n");
    printf("                                    ");
    return 0;
}


int NextBrickLog(int Next) {
    int NextBrick[16];
    int Save[2];

    //커서 초기 위치 백업
    Save[0] = ROW; Save[1] = COLUMN;

    //이전 기록 소거
    printf("\x1b[%d;%dH", 6, 12);
    printf(".___________________________________.");
    printf("\x1b[%d;%dH", 7, 12);
    printf("|                                   |");
    printf("\x1b[%d;%dH", 8, 12);
    printf("|                                   |");
    printf("\x1b[%d;%dH", 9, 12);
    printf("|                                   |");
    printf("\x1b[%d;%dH", 10, 12);
    printf("|  %d     %d     %d     %d     %d     %d  |", 1, 2, 3, 4, 5, 6);
    printf("\x1b[%d;%dH", 11, 12);
    printf("|___________________________________|");

    for (int i = 0; i < 6; i++) {
            DisplayCursor(7, 14 + 6 * i);
            //DisplayCursor(6 + 4*i, 14 );
            BrickList(RandomTable[Next + i], NextBrick);
            BrickPrinter(NextBrick);
    }
    printf("\x1b[%d;%dH", 5, 13);
    printf("↓ Next block ↓");

    //커서 원위치
    DisplayCursor(Save[0], Save[1]);
    return 0;
}

//After Display part
int TextLog() {
    printf("\x1b[%d;%dH", 24, 1);
    printf("Removed line :");
    if (CONTINUED == 0) {
        printf("\x1b[%d;%dH", 25, 1);
        printf("                     ");
        printf("\x1b[%d;%dH", 26, 1);
        printf("                     ");
    }
    return 0;
}

//Child part
void PrintDiplayLine() {
    for (int i = 200; i < 210; i++) GameMap[i] = 1; //최하단 디스플레이 충돌판정용 1 삽입 줄소거 계산시 201 ~ 이상 번대는 무시할 것
    for (int j = 0; j < 22; j++) {
        if (21 == j) {
            printf("\x1b[%d;%dH", 21, 1);
            printf("▦▦▦▦▦▦▦▦▦▦■");
        }
        else {
            printf("\x1b[%d;%dH", j, 11);
            printf("|");
        }
    }
}

int LoadMap() {
    //맵출력
    Sleep(100);

    printf("\x1b[%d;%dH", 1, 1);
    for (int i = 0; i < 200; i++) {
            if (1 == GameMap[i]) printf("▩");
            else printf("`");

            if (0 == (i + 1) % 10) printf("\n");
        }
    return 0;
}

int DisplayCursor(int row, int column) {
    ROW = row, COLUMN = column;
    return 0;
}