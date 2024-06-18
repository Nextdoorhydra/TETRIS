/*■□▦▩ 테트리스 ▧▤▥▢*/
//Basic library
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <Windows.h>
#include <math.h>

//Header files
#include "Matproduct.h"
#include "Display.h"
#include "Utility.h"
#include "Component.h"
#include "SponeBrick.h"
#include "ArrayLogic.h"
#include "C:\Users\ndhph\Desktop\code\c_study\Tetris\TETRIS\TETRIS\AfterCollision.h"

//FPS & TIME limit
#define _USE_MATH_DEFINES
#define FRAME_RATE 30
#define GAME_TIME 999

//Global variation
static const int MICROSECONDS_PER_FRAME = 1000000 / FRAME_RATE; // 각 프레임 간의 마이크로초

//Global variation that set by me
int ROW; int COLUMN;
int SCORE;
int CONTINUED;
int LINETHATCLEARED;
int COMPONENT[16];
int GameMap[210] = { 0, };
int RandomTable[100];
int ROTATE = 0;
int T_SIPIN_COUNTER = 0;

//Function declaration
int GAME_OUT(int STATE);
int ClearTheGame(int STATE);
int TestConstant[16] = {0, };


//Main
void main() {
	//Variation
	int brickSet[9] = { 0, };
	int Next = 0; //스폰시 카운트 증가
	int score = 0;
	int STATE = 1;

	int MapTest();
	printf("\a");
	CursorView();

	//난수 테이블 생성
	RandomSeedMaker();

	DisplayCursor(1, 5);//초기 커서 메인 디스플레이 > 스코어보드 > 넥스트 블럭 > 스폰함수 (커서 초기화) > 컴포넌트 인풋 맞춰서 커서 따라가기) > 디스플레이 > 스폰함수 > 컴포넌트 3스텝

	//초기 스폰 이후부터 스폰은 충돌에서 호출
	BrickSet(RandomTable[Next]);
	Next += 1;

	//후기 디스플레이
	NextBrickLog(Next);

	while (STATE) {
		CursorView();

		//디스플레이 로드
		MainDisplay();
		scoreBoard(SCORE);

		//컴포넌트 (충돌 처리까지 끝나고 메인 돌아옴)
		if (Component()) {
			ComponentToMap(COMPONENT);
			if (10 == LEVEL()) ClearTheGame(STATE);
			DisplayCursor(1, 5);
			BrickSet(RandomTable[Next]);
			Next += 1; //스폰 
			GAME_OUT(STATE);
		}

		printf("\x1b[%d;%dH", 5, 30);
		printf(" Row:%d Column:%d    ", ROW, COLUMN);

		//스코어 계산 소거 판정

		//게임 오버 판정

		//후기 디스플레이
		NextBrickLog(Next);
	}

	GAME_OUT(STATE);
}

int ClearTheGame(int STATE) {
	printf("\x1b[%d;%dH", 13, 13);
	printf("!!! Clear the game !!!");
	printf("\x1b[%d;%dH", 14, 13);
	printf("!!! Your score : %d !!!", SCORE);

}

int GAME_OUT(int STATE) {
	int time = elapsedTime();

	if (999 < time) {
		printf("\x1b[%d;%dH", 13, 13);
		printf(":( GAME OVER");
		printf("\x1b[%d;%dH", 14, 13);
		printf("!!! Your score : %d !!!", SCORE);
		Sleep(3000);
		STATE = 0;
	}

	for (int i = 0; i < 10; i++) {
		if (GameMap[i]) {
			printf("\x1b[%d;%dH", 13, 13);
			printf(":( GAME OVER");
			printf("\x1b[%d;%dH", 14, 13);
			printf("!!! Your score : %d !!!", SCORE);
			Sleep(3000);
			STATE = 0;
		}
	}


	return 0;
}