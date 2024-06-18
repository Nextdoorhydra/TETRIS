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

//memset(arr, 0, sizeof(int) * 5); ũ�� 5 ��ŭ 0���� �ʱ�ȭ   memset(myArray + 2, 1, 5 * sizeof(int)); strcpy(end, start); subBrick

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

//�긯�� ����� B�� �����
int BrickAtoB(int A[16], int B[16]) {
    for (int i = 0; i < 16; i++) B[i] = A[i];
    return 0;
}

int BrickAndAtoB(int A[16], int B[16]) {
    for (int i = 0; i < 16; i++) B[i] &= A[i];
    for (int i = 0; i < 16; i++) if (B[i]) return 1; //�������� ������ 1�� ��������
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

    return 1;//��ġ�ϸ� 1�� ��������
}

//0�� üĿ
int BrickZeroRowChecker(int ROW, int Brick[16]) {
    for (int i = 0; i < 4; i++) {
        if (Brick[4*(ROW-1) + i]) return 0;
    }
    return 1; //0�� �߰�
}

//0�� üĿ
int BrickZeroColumnChecker(int Column, int Brick[16]) {
    for (int i = 0; i < 16; i += 4) {
        if (Brick[Column + i - 1]) return 0;
    }
    return 1; //0�� �߰�
}

int BrickPrinterEdge(int i) {
    if (13 <= COLUMN) return 0;//�ؽ�Ʈ�긯 ǥ�ÿ�
    if (1 > COLUMN + i % 4) {
        printf("\x1b[%d;%dH", 21, 11); //�ʱ������� Ŀ���Űܼ� �߶����
    }
    else if (10 < COLUMN + i % 4) {
        printf("\x1b[%d;%dH", 21, 11);
    }
    return 0;
}

//Brick ��� �ϼ�
int BrickPrinter(int Brick[16]) { 
    printf("\x1b[%d;%dH", ROW, COLUMN); //ROW COLLUMN ��ġ���� ���������� ���� 1234 1234(5678)
    for (int i = 0; i < 16; i++) {
        printf("\x1b[%d;%dH", ROW + i / 4, COLUMN + i % 4);//11 12 13 14 21 22 23 24 .. ȸ����
        BrickPrinterEdge(i); //���̵�� �߸� ���
        if (1 == Brick[i]) printf("��");
        if (0 == (i + 1) % 4) printf("\n"); //4������ �ళ��
    }
    return 0;
}

//�긯 �߾� ��ġ���� ������ ������ ������ �߾� ������
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

//��Ī�̵� �� ���� �� ����
int BrickLeftSort(int Left, int Brick[16]) {
    for (int i = 1; i < 16; i++) {
        if (Brick[i]) {
            Brick[i - Left] = 1;
            Brick[i] = 0;
        }
    }
    return 0;
}

//Brick ��Ī �̵�
int  BrickSwapper(int Brick[16]) {
    int subBrick[16] = { 0,0,0,0, 0,0,0,0, 0,0,0,0, 0,0,0,0 };

    //���� �� �ӽ� ����
    BrickAtoB(Brick, subBrick);

    //��Į�ڸ��� ó�� �긯�� ���Ҹ� ���긯�� �����Ŵ
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
            i += 3; //3���� ����
        }
        //������ ��Į�ڸ��ϵ� �긯�� xor ���Ѽ� ��Ī�̵���
        BrickXorAtoB(subBrick, Brick);
        //DisplayCursor(ROW, COLUMN - 2);

        return 0;
    }//�Ʒ��� �׳� ������� ��Ī����... �Ⱦ�
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
            i -= 3; //3���� ����
        }
        //������ ��Į�ڸ��ϵ� �긯�� xor ���Ѽ� ��Ī�̵���
        BrickXorAtoB(subBrick, Brick);
        //DisplayCursor(ROW, COLUMN - 1);

        return 0;
    }
}

//Brick spin

int BrickSpiner(int KEY) {
    return 0;
}



