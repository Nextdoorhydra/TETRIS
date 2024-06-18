//줄소거 판정 함수
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <math.h>
#include "C:\Users\ndhph\Desktop\code\c_study\Tetris\TETRIS\TETRIS\AfterCollision.h"
#include "Display.h"
#include "CollisionChecker.h"
#include "ArrayLogic.h"
#include "Score.h"

extern int GameMap[210];
extern int ROW, COLUMN;
extern int CONTINUED;
extern int COMPONENT;

//Declaration
int DownTheMap();

int LineChecker() {
    int ClearLine[4] = { 0, };
    int cnt = 0; int index = 0;
    for (int i = 1; i < 21; i++) {
        for (int j = 0; j < 10; j++) {
            if (!GameMap[10 * (i - 1) + j]) cnt = 0;
        }
            if (1 == cnt) {
                ClearLine[index] = i;
                index += 1;
        }
            cnt = 1;
    }

    //연속판정
    if (0 == ClearLine[0] && 0 == ClearLine[1] && 0 == ClearLine[2] && 0 == ClearLine[3]) CONTINUED = 0;
    else CONTINUED += 1;

    Score(index);

    for (int k = 0; k < 4; k++) {
        if (ClearLine[k]) LineEliminate(ClearLine[k]);
        DownTheMap();
    }
    return 0;
}

int LineEliminate(int line) {
    for (int i = 0; i < 10; i++) {
        GameMap[10*(line-1) + i] = 0;
    }
    RemoveAnimation(line);
    CONTINUED += 1;
    return 0;
}

int RemoveAnimation(int NUM){
    printf("\x1b[%d;1H", NUM);
    printf("▧▧▧▧▧▧▧▧▧▧");
    Sleep(150);
    printf("\x1b[%d;1H", NUM);
    printf("**********");
    Sleep(150);
    printf("\x1b[%d;1H", NUM);
    printf("++++++++++");
    Sleep(150);
    printf("\x1b[%d;1H", NUM);
    printf("``````````");
    Sleep(150);
    return 0;
}

int ComponentToMap(int Component[16]) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (Component[4 * i + j]) GameMap[10 * (ROW - 1 + i) + COLUMN - 1 + j] = Component[4 * i + j];
        }
    }
    LineChecker();
    return 1;
}

int SolveTheLine() {
    return 0;
}

//0행 체커
int MapZeroRowChecker(int ROW, int Brick[210]) {
    for (int i = 0; i < 10; i++) {
        if (Brick[10 * (ROW-1) + i]) return 0;
    }
    return 1; //0행 발견
}

//배열 아래로 전사 함수
int DownTheMap() {
    for (int i = 20; i > 0; i--){
        if (MapZeroRowChecker(i, GameMap)) {
            for (int j = 0; j < 10; j++) {
                GameMap[10 * (i-1) + j] = GameMap[10 * (i /*위행으로 가시오*/-1 - 1) + j];
                GameMap[10 * (i - 1 /*전행으로 가시오*/ - 1) + j] = 0;
            }
        }
    }
    return 0;
}