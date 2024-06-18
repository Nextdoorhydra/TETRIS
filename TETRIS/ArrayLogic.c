//Procedure
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <math.h>
#include <string.h>
#include "ArrayLogic.h"
#include "Display.h"

//Global
extern int ROW, COLUMN;
extern int GameMap[210];
extern int COMPONENT;

//memset(arr, 0, sizeof(int) * 5); 크기 5 만큼 0으로 초기화   memset(myArray + 2, 1, 5 * sizeof(int)); strcpy(end, start); subBrick

//Brick



int BrickRotate(int middle, int A[16], int direction) {
    int a = 0; int b = 0;
    if (direction == 1) {
        a = A[middle - 4];
        A[middle - 4] = A[middle - 1];
        A[middle - 1] = A[middle + 4];
        A[middle + 4] = A[middle + 1];
        A[middle + 1] = a;

        b = A[middle - 5];
        A[middle - 5] = A[middle + 3];
        A[middle + 3] = A[middle + 5];
        A[middle + 5] = A[middle - 3];
        A[middle - 3] = b;
    }
    if (direction == 2) {
        a = A[middle - 4];
        A[middle - 4] = A[middle + 1];
        A[middle + 1] = A[middle + 4];
        A[middle + 4] = A[middle - 1];
        A[middle - 1] = a;

        b = A[middle - 5];
        A[middle - 5] = A[middle - 3];
        A[middle - 3] = A[middle + 5];
        A[middle + 5] = A[middle + 3];
        A[middle + 3] = b;
    }
    return 0;
}

//브릭논리 연산들 B에 저장됨
int BrickAtoB(int A[16], int B[16]) {
    for (int i = 0; i < 16; i++) B[i] = A[i];
    return 0;
}

int BrickAndAtoB(int A[16], int B[16]) {
    for (int i = 0; i < 16; i++) B[i] &= A[i];
    for (int i = 0; i < 16; i++) if (B[i]) return 1; //교집합이 있으면 1을 내보낸다
    return 0;
}

int BrickSubtractAtoB(int A[16], int B[16]) {
    BrickAndAtoB(B, A);
    BrickXorAtoB(A, B);
    return 0;
}

int BrickMergerAtoB(int A[16], int B[16]) {
    for (int i = 0; i < 16; i++) B[i] |= A[i];
    return 0;
}

int BrickXorAtoB(int A[16], int B[16]) {
    for (int i = 0; i < 16; i++) B[i] ^= A[i];
    for (int i = 0; i < 16; i++) if (B[i]) return 0;

    return 1;//일치하면 1을 내보낸다
}

//0행 체커
int BrickZeroRowChecker(int ROW, int Brick[16]) {
    for (int i = 0; i < 4; i++) {
        if (Brick[4*(ROW-1) + i]) return 0;
    }
    return 1; //0행 발견
}

//0열 체커
int BrickZeroColumnChecker(int Column, int Brick[16]) {
    for (int i = 0; i < 16; i += 4) {
        if (Brick[Column + i - 1]) return 0;
    }
    return 1; //0열 발견
}

int BrickPrinterEdge(int i) {
    if (13 <= COLUMN) return 0;//넥스트브릭 표시용
    if (1 > COLUMN + i % 4) {
        printf("\x1b[%d;%dH", 21, 11); //맵구석으로 커서옮겨서 잘라버림
    }
    else if (10 < COLUMN + i % 4) {
        printf("\x1b[%d;%dH", 21, 11);
    }
    return 0;
}

//Brick 출력 완성
int BrickPrinter(int Brick[16]) { 
    printf("\x1b[%d;%dH", ROW, COLUMN); //ROW COLLUMN 위치에서 순차적으로 나열 1234 1234(5678)
    for (int i = 0; i < 16; i++) {
        printf("\x1b[%d;%dH", ROW + i / 4, COLUMN + i % 4);//11 12 13 14 21 22 23 24 .. 회전수
        BrickPrinterEdge(i); //사이드로 잘릴 경우
        if (1 == Brick[i]) printf("■");
        if (0 == (i + 1) % 4) printf("\n"); //4열마다 행개행
    }
    return 0;
}

//브릭 중앙 일치값만 모으고 나머지 날리는 중앙 모집기
int BrickSymemtry(int Brick[16]) {
    for (int i = 1; i < 15;) {
        if (1 != Brick[i] || 1 != Brick[i + 1]) {
            Brick[i] = 0;
            Brick[i + 1] = 0;
        }
        i += 4;
    }
    for (int j = 0; j < 16;) {
        Brick[j] = 0;
        j += 3;
        Brick[j] = 0;
        j += 1;
    }
    return 0;
}

//대칭이동 블럭 왼쪽 열 정렬
int BrickLeftSort(int Left, int Brick[16]) {
    for (int i = 1; i < 16; i++) {
        if (Brick[i]) {
            Brick[i - Left] = 1;
            Brick[i] = 0;
        }
    }
    return 0;
}

//Brick 대칭 이동
int  BrickSwapper(int Brick[16]) {
    int subBrick[16] = { 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 };

    //기존 값 임시 저장
    BrickAtoB(Brick, subBrick);

    //데칼코마니 처럼 브릭에 원소를 섭브릭에 전사시킴
    if (BrickZeroColumnChecker(4, subBrick)) {
        for (int i = 0; i < 16; i++) {
            if (Brick[i + 3] != Brick[i])Brick[i + 3] = Brick[i];
            else {
                Brick[i] = 0; Brick[i + 3] = 0;
            }
            if (Brick[i + 2] != Brick[i + 1]) Brick[i + 2] = Brick[i + 1];
            else {
                Brick[i + 1] = 0; Brick[i + 2] = 0;
            }
            i += 3; //3구간 점프
        }
        //기존과 데칼코마니된 브릭을 xor 시켜서 대칭이동함
        BrickXorAtoB(subBrick, Brick);
        //DisplayCursor(ROW, COLUMN - 2);

        return 0;
    }//아래는 그냥 만든거임 대칭구조... 안씀
    else if (BrickZeroColumnChecker(1, subBrick)) {
        for (int i = 15; i > -1; i--) {
            if (Brick[i - 3] != Brick[i]) Brick[i - 3] = Brick[i];
            else {
                Brick[i] = 0; Brick[i - 3] = 0;
            }
            if (Brick[i - 2] != Brick[i - 1]) Brick[i - 2] = Brick[i - 1];
            else {
                Brick[i - 1] = 0; Brick[i - 2] = 0;
            }
            i -= 3; //3구간 점프
        }
        //기존과 데칼코마니된 브릭을 xor 시켜서 대칭이동함
        BrickXorAtoB(subBrick, Brick);
        //DisplayCursor(ROW, COLUMN - 1);

        return 0;
    }
}

//Brick spin

int BrickSpiner(int KEY) {
    return 0;
}



