//컴포넌트 > 인풋 > 충돌 판정
#include <stdio.h>
#include <time.h>
#include <Windows.h>
#include "Component.h"
#include "ArrayLogic.h"
#include "CollisionChecker.h"
#include "Display.h"
#include "Utility.h"
#include "SponeBrick.h"
#include "C:\Users\ndhph\Desktop\code\c_study\Tetris\TETRIS\TETRIS\AfterCollision.h"

//G
extern int ROW, COLUMN;
extern int COMPONENT[9];

//Declaration
int InputKey();

int gravity() {
    if (DisplayCollisonChecker(80)) return 1;
    if (CollisionChecker(80)) { //충돌시 기다렸다가<나중에 추가애프터 콜리전으로
        return 1; //ComponentToMap();
    }
    DisplayCursor(ROW + 1, COLUMN);
    return 0;
}

int Component() {
    BrickPrinter(COMPONENT);

    ElapsedTime(); // 시간 갱신

    if (NoInputTimeChecker(LEVEL())) {
        int cnt = InputKey();
        if (1 == cnt) return 1;
        else if (2 == cnt) return 0;
    }
    else if(gravity()) return 1;
  

    ElapsedTime(); // 시간 갱신

	return 0;
}

int InputKey() {
    int KEY = 0;
    KEY = (int)_getch();  // 키 입력 대기

    if (KEY == 224) {  // 방향키의 특수키 코드
        KEY = _getch();  // 실제 키 코드 가져오기
        //Sleep(300);
        switch (KEY) {
        case 75: // 왼쪽 화살표
            if (DisplayCollisonChecker(KEY)) return 0;
            if (CollisionChecker(KEY)) { //충돌시 기다렸다가<나중에 추가애프터 콜리전으로
                return 2; //ComponentToMap();
            }
            DisplayCursor(ROW, COLUMN - 1);
            return 0;
            break;

        case 77: // 오른쪽 화살표
            if (DisplayCollisonChecker(KEY)) return 0;
            if (CollisionChecker(KEY)) { //충돌시 기다렸다가<나중에 추가애프터 콜리전으로
                return 2; //ComponentToMap();
            }
            DisplayCursor(ROW, COLUMN + 1);
            return 0;
            break;

        case 80: // 아래쪽 화살표
            if (DisplayCollisonChecker(KEY)) return 1;
            if (CollisionChecker(KEY)) { //충돌시 기다렸다가<나중에 추가애프터 콜리전으로
                return 1; //ComponentToMap();
            }
            DisplayCursor(ROW + 1, COLUMN);
            return 0;
            break;
        }
    }
    else if (inputAction(KEY)) { //스페이스바 용임 회전은 리턴 0으로 통과시키삼
        if (DisplayCollisonChecker(KEY)) return 2;
        if (CollisionChecker(KEY)) { //충돌시 기다렸다가<나중에 추가애프터 콜리전으로
            return 1; //1나오면 스폰임
        }
        return 0;
    }
}

int inputAction(int KEY) {
    switch (KEY) {
    case 'q'://좌회전 커서변경 필요없음
        if (CollisionChecker(KEY)) return 0; //충돌나면 불발 시킴 안에서 다 처리되니 의미없음 리턴 1만 안시키면 됨
        break;

    case 'e'://우회전
        if (CollisionChecker(KEY)) return 0;
        break;

    case ' '://바로 내리기
        while (1) {
            ElapsedTime();
            if (DisplayCollisonChecker(80)) return 1;
            if (CollisionChecker(80)) { //충돌시 기다렸다가<나중에 추가애프터 콜리전으로
                return 1; //ComponentToMap();
            }
            DisplayCursor(ROW + 1, COLUMN);
            BrickPrinter(COMPONENT);
            LoadMap();
        }
        return 0;
        break;
    }
    return 0;
}
