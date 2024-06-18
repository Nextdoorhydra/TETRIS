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

	//�� ���� ���ڸ��� ����
	//if (row > 17) row = 17;
	//if (column < 1 || column > 7) column = 7;

	for (int i = 0; i < 4; i++) { //4���� ����
		for (int j = 0; j < 4; j++) { //4������ ����
			PartOfTheMap[4*i + j] = GameMap[10 * (row-1 + i) + column -1 + j];
		}
	}


	return 0;
}

//@@@@@@@@@@@@@@@�����ʿ� ���� �Լ��� ���� �����ʿ� @@@@@@@@@@@@@@@@@@@@@@@@@@@
int CollisionChecker(int KEY) { //AND= 1, �浹 ,return 1 ���Ӹʿ��� �ο� �÷� ��ġ�������� +4���� �ͽ�Ʈ��Ʈ �迭�� 00���� �����ϹǷ� + 1 �̸� ����(�̵��ϸ� �����̴� ��)
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
	else	if ('q' == KEY) {//ȸ���� ���� �긯����Ʈ �־ �˻��ؾ���
		BrickAtoB(COMPONENT, BrickTmp); //������Ʈ ���
		SpinBrickList(KEY);
		if (DisplayCollisonChecker(KEY)) {//���� ���¿��� ���÷��� �˻� �� �� �ϱ�
			BrickAtoB(BrickTmp, COMPONENT); //�ҹ߳����Ƿ� ������Ʈ ���� ��Ŵ
			BrickPrinter(COMPONENT);
			return 1;
		}
		DecompositionTheMap(PartOfTheMap);
		if (BrickAndAtoB(COMPONENT, PartOfTheMap)) {
			BrickAtoB(BrickTmp, COMPONENT); //�ҹ߳����Ƿ� ������Ʈ ���� ��Ŵ
			BrickPrinter(COMPONENT);
			return 1;
		}
		//Ƽ���� ����
		if (5 == ROTATE) {
			T_SIPIN_COUNTER = 1;
		}
		return 0;
	}
	else if ('e' == KEY) {
		BrickAtoB(COMPONENT, BrickTmp); //������Ʈ ���
		SpinBrickList(KEY);
		if(DisplayCollisonChecker(KEY)){//���� ���¿��� ���÷��� �˻� �� �� �ϱ�
			BrickAtoB(BrickTmp, COMPONENT); //�ҹ߳����Ƿ� ������Ʈ ���� ��Ŵ
			BrickPrinter(COMPONENT);
			return 1;
		}
		DecompositionTheMap(PartOfTheMap);
		if (BrickAndAtoB(COMPONENT, PartOfTheMap)) {
			BrickAtoB(BrickTmp, COMPONENT); //�ҹ߳����Ƿ� ������Ʈ ���� ��Ŵ
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
	else if (80 == KEY) { // ���� �ʶմ°Ÿ� ���µ� ���� �Ʒ� 1�� ������ ��
		if (ROW < 17) return 0;
		else {
			for (int j = 4 + 17 - ROW; j > 0; j--) {
				if (BrickZeroRowChecker(j, COMPONENT)) return 0;
				else return 1;
			}
		}
	}
	else if ('q' == KEY) { //���� ���࿡�� ���ɵ� ������ ���� �˻��ϴ� ����
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
