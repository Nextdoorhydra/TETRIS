//Procedure
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <math.h>
#include "SponeBrick.h"
#include "ArrayLogic.h"

#define ALLNEXT 4

//Global variation
extern int COMPONENT[16];
extern int TestConstant[16]; //BrickAtoB(BrickTmp,TestConstant);
extern int ROTATE;

//declaration
int BrickList(int NUM, int BrickList[16]);

//������Ʈ ����� �ε����� ��ȯ�� ���μ� ����� �Ҵ�
int RotateConverter() {
    //N RN �� �ڱ� �ѹ� <-> 0 , 


    return ROTATE;
}

int SpinBrickList(int KEY) {
    //BrickTmp
    int SBrickTmp[16] = { 0, };

    //Spin set ���� �Լ� ������Ʈ ������, ���� ȸ��, �߾�ȸ��, �� ĭ �ø���
    int S_N_Brick[16] = { 0,1,0,0, 1,1,0,0, 1,0,0,0, 0,0,0,0 };
    int S_I_Brick[16] = { 1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0 };

    for (int index = 1; index <= 7; index++) {
        BrickList(index, SBrickTmp);
        if (( ROTATE > 0 || BrickXorAtoB(COMPONENT, SBrickTmp))) {//�긯������ ������Ʈ�� ����� ����
            if (ROTATE > 0) index = RotateConverter();
            switch (index) {
            case 1://L �߾��� ���� ȸ��
                
                BrickRotate(5, COMPONENT, 1);
                ROTATE = 1;

                return 0;
                break;

            case 2:
                if (!ROTATE) BrickList(2, SBrickTmp);
                BrickRotate(5, COMPONENT, 2);
                ROTATE = 2;

                return 0;
                break;

            case 3:
                    //���� ������Ʈ �� ��� �ݸ������� ���� ����
                    if (ROTATE == 3) { //������Ʈ �ʱ�ȭ
                        BrickList(3, SBrickTmp);
                        BrickAtoB(SBrickTmp, COMPONENT);
                        ROTATE = 0;
                        return 0;
                    }

                    if(ROTATE == 0) {
                        BrickAtoB(S_N_Brick, COMPONENT);
                        ROTATE = 3;
                        return 0;
                    }

                break;

            case 4:
                    if (ROTATE == 4) { //������Ʈ �ʱ�ȭ
                        BrickList(4, SBrickTmp);
                        BrickAtoB(SBrickTmp, COMPONENT);
                        ROTATE = 0;
                        return 0;
                    }

                    if (ROTATE == 0) {
                        BrickSwapper(S_N_Brick);
                        BrickLeftSort(1, S_N_Brick);
                        BrickAtoB(S_N_Brick, COMPONENT);
                        ROTATE = 4;
                        return 0;
                    }

                break;

            case 5:
                BrickRotate(5, COMPONENT, 1 + 1*(KEY == 'e'));
                ROTATE = 5;
                return 0;
                break;

            case 7:
                    //���� ������Ʈ �� ��� �ݸ������� ���� ����
                    if (ROTATE > 0) { //������Ʈ �ʱ�ȭ
                        BrickList(7, SBrickTmp);
                        BrickAtoB(SBrickTmp, COMPONENT);
                        ROTATE = 0;
                        return 0;
                    }
                    else {
                        BrickAtoB(S_I_Brick, COMPONENT);
                        ROTATE = 7;
                        return 0;
                    }

                break;

            case 6://Sqr ȸ������
                return 0;
                break;
            }
        }
    }
    return 0;
}

int BrickList(int NUM,int BrickList[16]) {
    //Type of bricks if you change that number, you can create variation 
    int L_Brick[16] = { 1,0,0,0, 1,0,0,0, 1,1,0,0, 0,0,0,0 };
    int N_Brick[16] = { 1,1,0,0, 0,1,1,0, 0,0,0,0, 0,0,0,0 };
    int T_Brick[16] = { 0,1,0,0, 1,1,0,0, 0,1,0,0, 0,0,0,0 };
    int Sqr_Brick[16] = { 1,1,0,0, 1,1,0,0, 0,0,0,0, 0,0,0,0 };
    int I_Brick[16] = { 1,0,0,0, 1,0,0,0 , 1,0,0,0 , 1,0,0,0 };

    //Randomly pull the number That mean 1 2 is 'L', 3 4 is 'N', 5 is 'T', 6 is 'square', 7 is 'I' brick.
    switch (NUM){
    case 1:
        BrickAtoB(L_Brick, BrickList);
        break;

    case 2:
        BrickSwapper(L_Brick);
        BrickLeftSort(2, L_Brick);
        BrickAtoB(L_Brick, BrickList);
        break;

    case 3:
        BrickAtoB(N_Brick, BrickList);
        break;

    case 4:
        BrickSwapper(N_Brick);
        BrickLeftSort(1, N_Brick);
        BrickAtoB(N_Brick, BrickList);
        break;

    case 5:
        BrickAtoB(T_Brick, BrickList);
        break;

    case 6:
        BrickAtoB(Sqr_Brick, BrickList);
        break;

    case 7:
        BrickAtoB(I_Brick, BrickList);
        break;

    }
    return 0;
}



//Brick setup ������Ʈ�� �ű�
int BrickSet(int NUM) { //�����Լ�
    int BrickTmp[16];

    BrickList(NUM, BrickTmp);
    BrickAtoB(BrickTmp, COMPONENT);

    //���� �긯 ������
    BrickPrinter(COMPONENT);

    ROTATE = 0; //ȸ�� ��� �ʱ�ȭ

    return 0;
}

