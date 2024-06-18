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

//로테이트 상수를 인덱스로 변환함 서로수 배수로 할당
int RotateConverter() {
    //N RN 은 자기 넘버 <-> 0 , 


    return ROTATE;
}

int SpinBrickList(int KEY) {
    //BrickTmp
    int SBrickTmp[16] = { 0, };

    //Spin set 하위 함수 로테이트 컨버터, 전사 회전, 중앙회전, 엔 칸 올리기
    int S_N_Brick[16] = { 0,1,0,0, 1,1,0,0, 1,0,0,0, 0,0,0,0 };
    int S_I_Brick[16] = { 1,1,1,1, 0,0,0,0, 0,0,0,0, 0,0,0,0 };

    for (int index = 1; index <= 7; index++) {
        BrickList(index, SBrickTmp);
        if (( ROTATE > 0 || BrickXorAtoB(COMPONENT, SBrickTmp))) {//브릭템프에 컴포넌트가 전사된 상태
            if (ROTATE > 0) index = RotateConverter();
            switch (index) {
            case 1://L 중앙점 기준 회전
                
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
                    //전사 컴포넌트 더 씌어도 콜리전에서 복구 가능
                    if (ROTATE == 3) { //로테이트 초기화
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
                    if (ROTATE == 4) { //로테이트 초기화
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
                    //전사 컴포넌트 더 씌어도 콜리전에서 복구 가능
                    if (ROTATE > 0) { //로테이트 초기화
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

            case 6://Sqr 회전없음
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



//Brick setup 컴포넌트로 옮김
int BrickSet(int NUM) { //스폰함수
    int BrickTmp[16];

    BrickList(NUM, BrickTmp);
    BrickAtoB(BrickTmp, COMPONENT);

    //스폰 브릭 보여짐
    BrickPrinter(COMPONENT);

    ROTATE = 0; //회전 상수 초기화

    return 0;
}

