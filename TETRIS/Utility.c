//�ð� �Լ�, Ŀ��
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

//Ŀ�� ����
void CursorView() {
    CONSOLE_CURSOR_INFO cursorInfo = { 0, };
    cursorInfo.dwSize = 1; //Ŀ�� ���� (1 ~ 100)
    cursorInfo.bVisible = FALSE; //Ŀ�� Visible TRUE(����) FALSE(����)
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
}

// ��� �ð��� �и��� ������ ������ ��ȯ�ϴ� �Լ�
void ElapsedTime() {
    printf("\x1b[%d;%dH", 1, 12);
    printf(" Time : %d", elapsedTime());
}

int elapsedTime() {
    if (start_time == 0) {
        start_time = clock();
        return 0; // �ʱ� ȣ�� �� 0 ��ȯ
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

    // ���� �ð��� ���
    start_time = GetTickCount64();

    while (elapsed_time < 1100 - seconds) {
        if (_kbhit()) return 1;
        // 100ms(0.1��) ���� ���
        Sleep(100);

        // ��� �ð� ����
        current_time = GetTickCount64();
        elapsed_time = current_time - start_time;
    }

    // 2�� ���� �Է��� ������
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

    return 0; //���� �õ� ȣ���� ������������ �������� 100ȸ ���� �ʱ�ȭ�� ���ο��� ó��
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
    //Ŀ�� �ʱ� ��ġ ���
    Save[0] = ROW; Save[1] = COLUMN;

    //BrickAtoB(COMPONENT, TestConstant);

    DisplayCursor(15, 20);

    BrickPrinter(TestConstant);
    //Ŀ�� ����ġ
    DisplayCursor(Save[0], Save[1]);
}