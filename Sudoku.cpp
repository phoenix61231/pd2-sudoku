#include "Sudoku.h"

int map[9][9]={0};
void Sudoku::giveQuestion(){
	cout<<"1 0 8 0 0 0 0 0 0\n2 3 0 0 1 5 8 0 0\n0 5 0 0 0 3 0 6 0\n3 0 0 0 2 0 0 8 0\n9 8 0 0 3 0 0 1 6\n0 1 0 0 7 0 0 0 3\n0 9 0 8 0 0 0 2 0\n0 0 3 1 5 0 0 9 8\n0 0 0 0 0 0 6 0 4\n"<<endl;	
}//done

void Sudoku::readIn(){
	int mapcount1=0,mapcount2=0;
	char drop;
	for(mapcount2=0;mapcount2<9;mapcount2++){
		scanf("%d%c",&map[mapcount1][mapcount2],&drop);
		if(drop=='\n'){mapcount1++;}
	}
}//done checked

void Sudoku::solve(){	
	readIn();
	int num=0;
	//initialize the possiblenumbers database 
	int row=0,column=0,ini=0;
	bool posnum[9][9][9];	
	for(row=0;row<9;row++){
		for(column=0;column<9;column++){
			if(map[row][column]!=0){
				for(ini=0;ini<9;ini++){
					posnum[row][column][ini]=false;}
				posnum[row][column][map[row][column]-1]=true;
			}
			else{
				for(ini=0;ini<9;ini++){
					posnum[row][column][ini]=true;}
			}
		}
	}
	//done
	int plus=0,count=0;
	while(plus<5){
		//count
		for(row=0;row<9;row++){
			for(column=0;column<9;column++){
				if(map[row][column]!=0){count++;}
			}
		}
		//done
		//print ans
		if(count==81){
			cout<<"1"<<endl;
			for(row=0;row<9;row++){
				for(column=0;column<9;column++){
					if(column<8){printf("%d ",map[row][column]);}
					else{printf("%d\n",map[row][column]);}
				}
			}
			break;
		}
		//done
		//analyze the each row,column or square
		bool ana[9],anacount;
		//row
		for(row=0;row<9;row++){
			for(anacount=0;anacount<9;anacount++){
					ana[anacount]=true;
			}
			for(column=0;column<9;column++){
				if(map[row][column]!=0){
					ana[map[row][column]-1]=false;
				}
			}
			for(column=0;column<9;column++){
				for(anacount=0;anacount<9;anacount++){
					if(map[row][column]==0){
						posnum[row][column][anacount]=ana[anacount];
					}
				}
			}
		}
		//rdone
		//column
		for(column=0;column<9;column++){
			for(anacount=0;anacount<9;anacount++){
					ana[anacount]=true;
			}
			for(row=0;row<9;row++){
				if(map[row][column]!=0){
					ana[map[row][column]-1]=false;
				}
			}
			for(row=0;row<9;row++){
				for(anacount=0;anacount<9;anacount++){
					if(map[row][column]==0){
						if(posnum[row][column][anacount]==true && ana[anacount]==false){
							posnum[row][column][anacount]=false;
						}
					}
				}
			}
		}
		//cdone
		//square
		for(int sqcou1=0;sqcou1<7;sqcou1+=3){
			for(int sqcou2=0;sqcou2<7;sqcou2+=3){
				for(anacount=0;anacount<9;anacount++){
					ana[anacount]=true;
				}
				for(row=sqcou2;row<sqcou2+3;row++){
					for(column=sqcou1;column<sqcou1+3;column++){
						if(map[row][column]!=0){
							ana[map[row][column]-1]=false;
						}
					}
				}
				for(row=sqcou2;row<sqcou2+3;row++){
					for(column=sqcou1;column<sqcou1+3;column++){
						for(anacount=0;anacount<9;anacount++){
							if(map[row][column]==0){
								if(posnum[row][column][anacount]==true && ana[anacount]==false){
									posnum[row][column][anacount]=false;
								}
							}
						}
					}
				}
			}
		}
		//sdone
		//done
		//fill in the blanks
		int posans=0;
		for(row=0;row<9;row++){
			for(column=0;column<9;column++){
				int sum=0;
				if(map[row][column]==0){
					for(int pos=0;pos<9;pos++){
						if(posnum[row][column][pos]==true){sum++;posans=pos+1;}
					}
				}			
				if(sum==1){map[row][column]=posans;}
			}
		}
		plus++;
	}
	if(count==81){exit(1);}
	for(row=0;row<9;row++){
		for(column=0;column<9;column++){
			count=0;
			for(count=0;count<9;count++){
				if(posnum[row][column][count]==true){count++;}
			}
			if(count==0){cout<<"0"<<endl;exit(1);}
		}
	}
	printf("2");	
	
}//done

void Sudoku::changeNum(int num1, int num2){
	for(int row=0;row<9;row++){
		for(int column=0;column<9;column++){
			if(map[row][column]==num1){
				map[row][column]=num2;
			}
			else if(map[row][column]==num2){
				map[row][column]=num1;
			}
		}
	}
}//done checked

void Sudoku::changeRow(int rowset1, int rowset2){
	int row1,row2,column,swap,rowset=rowset1+rowset2;
	switch(rowset){
		case 1:for(row1=0,row2=3;row1<3,row2<6;row1++,row2++){
					for(column=0;column<9;column++){
						swap=map[row1][column];
						map[row1][column]=map[row2][column];
						map[row2][column]=swap;
					}
				}
				break;							
		case 2:for(row1=0,row2=6;row1<3,row2<9;row1++,row2++){
					for(column=0;column<9;column++){
						swap=map[row1][column];
						map[row1][column]=map[row2][column];
						map[row2][column]=swap;
					}
				}
				break;
		default:for(row1=3,row2=6;row1<6,row2<9;row1++,row2++){
					for(column=0;column<9;column++){
						swap=map[row1][column];
						map[row1][column]=map[row2][column];
						map[row2][column]=swap;
					}
				}
				break;
	}						
}//done checked

void Sudoku::changeCol(int colset1, int colset2){
	int col1,col2,row,swap,colset=colset1+colset2;
	switch(colset){
		case 1:for(col1=0,col2=3;col1<3,col2<6;col1++,col2++){
					for(row=0;row<9;row++){
						swap=map[row][col1];
						map[row][col1]=map[row][col2];
						map[row][col2]=swap;
					}
				}
				break;							
		case 2:for(col1=0,col2=6;col1<3,col2<9;col1++,col2++){
					for(row=0;row<9;row++){
						swap=map[row][col1];
						map[row][col1]=map[row][col2];
						map[row][col2]=swap;
					}
				}
				break;
		default:for(col1=3,col2=6;col1<6,col2<9;col1++,col2++){
					for(row=0;row<9;row++){
						swap=map[row][col1];
						map[row][col1]=map[row][col2];
						map[row][col2]=swap;
					}
				}
				break;
	}					
}//done checked

void Sudoku::rotate(int times){
	int row,column,count,rot[9][9];
	times=times%4;
	for(count=0;count<times;count++){
		for(row=0;row<9;row++){
			for(column=0;column<9;column++){
				rot[column][8-row]=map[row][column];
			}
		}
		for(row=0;row<9;row++){
			for(column=0;column<9;column++){
				map[row][column]=rot[row][column];
			}
		}
	}		
}//done checked

void Sudoku::flip(int flipway){
	int row,column,tmp;
	switch(flipway){
		case 0:for(row=0;row<4;row++){
					for(column=0;column<9;column++){
						tmp=map[row][column];
						map[row][column]=map[8-row][column];
						map[8-row][column]=tmp;
					}
				}
				break;
		case 1:for(column=0;column<4;column++){
					for(row=0;row<9;row++){
						tmp=map[row][column];
						map[row][column]=map[row][8-column];
						map[row][8-column]=tmp;
					}
				}
				break;
	}
}//done checked

void Sudoku::transform(){
	int row,column;
	srand(time(NULL));
	rotate(rand()%101);
	changeNum(rand()%10,rand()%10);
	changeNum(rand()%10,rand()%10);
	flip(0);
	changeRow(rand()%3,rand()%3);
	for(row=0;row<9;row++){
		for(column=0;column<9;column++){
			if(column<8){printf("%d ",map[row][column]);}
			else{printf("%d\n",map[row][column]);}
		}
	}
}//done checked
