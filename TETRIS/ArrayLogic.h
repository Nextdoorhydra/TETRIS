#pragma once

int BrickAtoB(int A[16], int B[16]);

int BrickMergerAtoB(int A[16], int B[16]);

int BrickXorAtoB(int A[16], int B[16]);

int BrickAndAtoB(int A[16], int B[16]);

int BrickRotate(int middle, int A[16], int direction);



//0�� üĿ
int BrickZeroRowChecker(int Column, int Brick[16]);
int BrickZeroColumnChecker(int Column, int Brick[16]);

//Brick ��� �ϼ�
int BrickPrinter(int Brick[16]);

int BrickPrinterEdge(int Brick[16]);

int BrickLeftSort(int Left, int Brick[16]);

//Brick ��Ī �̵�
int  BrickSwapper(int Brick[16]);

int BrickSpiner(int KEY);