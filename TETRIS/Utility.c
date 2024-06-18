//시간 함수, 커서
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <Windows.h>
#include "Utility.h"
#include <conio.h>
#include "ArrayLogic.h"
#include "Display.h"

//Global
static clock_t start_time = 0;
extern RandomTable[100];
extern LINETHATCLEARED;
extern TestConstant[16];
extern COMPONENT[16];
extern ROW, COLUMN;

//커서 숨김
void CursorView() {
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //커서 굵기 (1 ~ 100)
    cursorInfo.bVisible = FALSE; //커서 Visible TRUE(보임) FALSE(숨김)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// 경과 시간을 밀리초 단위의 정수로 반환하는 함수
void ElapsedTime() {
    printf("\x1b[%d;%dH", 1, 12);
    printf(" Time : %d", elapsedTime());
}

int elapsedTime() {
    if (start_time == 0) {
        start_time = clock();
        return 0; // 초기 호출 시 0 반환
    }
    else {
        clock_t current_time = clock();
        int elapsed_time = (int)((current_time) / CLOCKS_PER_SEC);
        return elapsed_time;
    }
}

int NoInputTimeChecker(int seconds) {
    DWORD start_time, current_time;
    int elapsed_time = 0;

    // 현재 시간을 기록
    start_time = GetTickCount64();

    while (elapsed_time < 1100 - seconds) {
        if (_kbhit()) return 1;
        // 100ms(0.1초) 동안 대기
        Sleep(100);

        // 경과 시간 누적
        current_time = GetTickCount64();
        elapsed_time = current_time - start_time;
    }

    // 2초 동안 입력이 없으면
    return 0;
}

//Random function
int reduplicationChecker(int set[7]) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            if (i != j) {
                if (set[i] == set[j]) return 1;
            }
        }
    }
    return 0;
}

int RamdomDistributer(int set[7]) {
    int random;
    for (int i = 0; i < 7; i++) set[i] = 0;

    while(reduplicationChecker(set)){
        for (int i = 0; i < 7; i++) {
            random = rand() % 7 + 1;
            set[i] = random;
        }
    }
    return 0;
}

int RandomSeedMaker() {
    int i = 0; int set[7] = { 0,0,0,0,0,0,0 };;
    srand((unsigned int)time(NULL));

    for (int i = 0; i < 100; i++) {
        RamdomDistributer(set);
        for (int j = 0; j < 7; j++) {
            RandomTable[i + j] = set[j];
        }
        i += 6;
    }

    return 0; //랜덤 시드 호출은 전역변수에서 가져오기 100회 이후 초기화는 메인에서 처리
}

int SeedCheker(int next) {
    if (100 == next) {
        RandomSeedMaker();
        return 0;
    }
    return next;
}

int LEVEL() {
    int seconds = 0;
    seconds = 100 * ((LINETHATCLEARED / 10)+ 1);
    return seconds;
}

void Tester() {
    int Save[2] = { 0, };
    //커서 초기 위치 백업
    Save[0] = ROW; Save[1] = COLUMN;

    //BrickAtoB(COMPONENT, TestConstant);

    DisplayCursor(15, 20);

    BrickPrinter(TestConstant);
    //커서 원위치
    DisplayCursor(Save[0], Save[1]);
}