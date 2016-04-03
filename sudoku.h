#include <iostream>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Sudoku{
	public:
		void giveQuestion();
		void readIn();
		void solve();
		void changeNum(int num1, int num2);
		void changeRow(int rowset1, int rowset2);
		void changeCol(int colset1, int colset2);
		void rotate(int times);
		void flip(int flipway);
		void transform();
};
