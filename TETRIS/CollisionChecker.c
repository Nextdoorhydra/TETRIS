#include < stdio.h>
#include "CollisionChecker.h"
#include "ArrayLogic.h"
#include "Display.h"
#include "SponeBrick.h"

//G
extern int ROW, COLUMN;
extern int COMPONENT[16];
extern int GameMap[210];
extern int ROTATE;
extern int T_SIPIN_COUNTER;

//declaration
int CollisionChecker(int KEY);
int DisplayCollisonChecker(int KEY);

int DecompositionTheMap(int PartOfTheMap[16]) {
	int row = ROW; int column = COLUMN;

	//맵 밖은 못자르게 제한
	//if (row > 17) row = 17;
	//if (column < 1 || column > 7) column = 7;

	for (int i = 0; i < 4; i++) { //4까지 추출
		for (int j = 0; j < 4; j++) { //4열까지 추출
			PartOfTheMap[4*i + j] = GameMap[10 * (row-1 + i) + column -1 + j];
		}
	}


	return 0;
}

//@@@@@@@@@@@@@@@검증필요 위의 함수랑 같이 검증필요 @@@@@@@@@@@@@@@@@@@@@@@@@@@
int CollisionChecker(int KEY) { //AND= 1, 충돌 ,return 1 개임맵에서 로우 컬럼 위치에서부터 +4까지 익스트랙트 배열은 00에서 시작하므로 + 1 미리 빼줌(이동하면 움직이는 양)
	int PartOfTheMap[16] = { 0, }; int BrickTmp[16] = { 0, };

	if (75 == KEY) {
		DisplayCursor(ROW, COLUMN - 1);
		DecompositionTheMap(PartOfTheMap);
		if (BrickAndAtoB(COMPONENT, PartOfTheMap)) {
			DisplayCursor(ROW, COLUMN + 1);
			return 1;
		}
		DisplayCursor(ROW, COLUMN + 1);
		return 0; 
	}
	else if (77 == KEY) {
		DisplayCursor(ROW, COLUMN + 1);
		DecompositionTheMap(PartOfTheMap);
		if (BrickAndAtoB(COMPONENT, PartOfTheMap)) {
			DisplayCursor(ROW, COLUMN - 1);
			return 1;
		}
		DisplayCursor(ROW, COLUMN - 1);
		return 0; 
	}
	else if (80 == KEY) {
		DisplayCursor(ROW + 1, COLUMN);
		DecompositionTheMap(PartOfTheMap);
		if (BrickAndAtoB(COMPONENT, PartOfTheMap)) {
			DisplayCursor(ROW - 1, COLUMN);
			return 1;
		}
		DisplayCursor(ROW - 1, COLUMN);
		return 0; 
	}
	else	if ('q' == KEY) {//회전은 스폰 브릭리스트 넣어서 검사해야함
		BrickAtoB(COMPONENT, BrickTmp); //컴포넌트 백업
		SpinBrickList(KEY);
		if (DisplayCollisonChecker(KEY)) {//스핀 상태에서 디스플레이 검사 한 번 하기
			BrickAtoB(BrickTmp, COMPONENT); //불발났으므로 컴포넌트 복구 시킴
			BrickPrinter(COMPONENT);
			return 1;
		}
		DecompositionTheMap(PartOfTheMap);
		if (BrickAndAtoB(COMPONENT, PartOfTheMap)) {
			BrickAtoB(BrickTmp, COMPONENT); //불발났으므로 컴포넌트 복구 시킴
			BrickPrinter(COMPONENT);
			return 1;
		}
		//티스핀 점수
		if (5 == ROTATE) {
			T_SIPIN_COUNTER = 1;
		}
		return 0;
	}
	else if ('e' == KEY) {
		BrickAtoB(COMPONENT, BrickTmp); //컴포넌트 백업
		SpinBrickList(KEY);
		if(DisplayCollisonChecker(KEY)){//스핀 상태에서 디스플레이 검사 한 번 하기
			BrickAtoB(BrickTmp, COMPONENT); //불발났으므로 컴포넌트 복구 시킴
			BrickPrinter(COMPONENT);
			return 1;
		}
		DecompositionTheMap(PartOfTheMap);
		if (BrickAndAtoB(COMPONENT, PartOfTheMap)) {
			BrickAtoB(BrickTmp, COMPONENT); //불발났으므로 컴포넌트 복구 시킴
			BrickPrinter(COMPONENT);
			return 1;
		}
		return 0;
	}
}

int DisplayCollisonChecker(int KEY) {
	if (75 == KEY) {
		if (COLUMN >1) return 0;
		else if (1 <= COLUMN) {
			for (int i = 1 * (1 == COLUMN) + 1 - COLUMN; i < 3; i++) {
				if (BrickZeroColumnChecker(i, COMPONENT)) return 0;
				else return 1;
			}
		}
	}
	else if (77 == KEY) {
		if (COLUMN < 7) return 0;
		else if (7 <= COLUMN) {
			for (int j = 11 - COLUMN; j > 0; j--) {
				if (BrickZeroColumnChecker(j, COMPONENT)) return 0;
				else return 1;
			}
		}
	}
	else if (80 == KEY) { // 단지 맵뚫는거만 막는데 의의 아래 1과 판정은 ㄴ
		if (ROW < 17) return 0;
		else {
			for (int j = 4 + 17 - ROW; j > 0; j--) {
				if (BrickZeroRowChecker(j, COMPONENT)) return 0;
				else return 1;
			}
		}
	}
	else if ('q' == KEY) { //현재 열행에서 스핀된 상태의 블럭을 검사하는 상태
		if (COLUMN > 1) return 0;
		else if (1 <= COLUMN) {
			for (int i = 1 * (1 == COLUMN) + 1 - COLUMN; i < 3; i++) {
				if (BrickZeroColumnChecker(i, COMPONENT)) return 0;
				else return 1;
			}
		}
	}
	else if ('e' == KEY) { 
		if (ROW < 17) return 0;
		else {
			if (COLUMN < 7) return 0;
			else if (7 <= COLUMN) {
				for (int j = 11 - COLUMN; j > 0; j--) {
					if (BrickZeroColumnChecker(j, COMPONENT)) return 0;
					else return 1;
				}
			}
		}
	}
	else return 0;
}
