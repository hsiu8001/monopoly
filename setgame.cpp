#include<iostream>
#include<fstream>
#include<windows.h>
#include<string>
#include<ctime>
#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

void printchar(char c, int n, int newline){
	int i;
	for(i=0; i<n; i++){
		cout << c;
	}
	if(newline)
		cout << endl;
}

void MoveConsole(int x, int y){
	HANDLE hin;
    //DWORD WriteWord;
    COORD pos;
	hin = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = x, pos.Y = y; 					// 設定位置。
    SetConsoleCursorPosition(hin, pos);
}

void Welcome(){
	MoveConsole(70, 10);
	printchar('*', 30, 1);
	MoveConsole(70, 11);
	cout << "*";
	printchar(' ', 28, 0);
	cout << "*";
	MoveConsole(70, 12);
	cout << "*";
	printchar(' ', 8, 0);
	cout << "歡迎進入遊戲";
	printchar(' ', 8, 0);
	cout << "*" ;
	MoveConsole(70, 13);
	cout << "*";
	printchar(' ', 3, 0);
	cout << "請輸入遊玩人數(2~4):";
	printchar(' ', 5, 0);
	cout << "*";
	MoveConsole(70, 14);
	cout << "*";
	printchar(' ', 28, 0);
	cout << "*";
	MoveConsole(70, 15);
	printchar('*', 30, 0);
	MoveConsole(60, 16);
	cout << "*hint:如果螢幕一片黑暗可以試著輸入隨便一個按鍵唷OuO";
}

void printmap(){
    fstream file;
    char c;

    file.open("map.txt", ios::in);
	if(!file)
		cout<< "檔案不存在" << endl;
	else {
		while(file.get(c))
            cout << c;

		cout << endl;
		file.close();
	}
}

void SetColor(int color){
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole,color);
}

void PrintChooseCharacter(){
	SetColor(10);
    cout << "1" << endl << "*";
    SetColor(11);
    cout << endl << "2" << endl << "*";
    SetColor(13);
    cout << endl << "3" << endl << "*";
    SetColor(14);
    cout << endl << "4" << endl << "*";
}

void Erase(int x, int y, int Size){
    MoveConsole(x, y);
    for(int i=0; i<Size; i++){
        cout << " ";
    }
}

void printselect (int number){
	switch(number){
		case 1:
			printf("Stick\n");
			break;
		case 2:
			printf("Tiger\n");
			break;
		case 3:
			printf("Chicken\n");
			break;
		case 4:
			printf("Worm\n");
			break;
	}
}

void verse (int number){
	switch(number){
		case 1:
			printf("Stick Hitting Tiger.\n");
			break;
		case 2:
			printf("Tiger Wreck Chicken.\n");
			break;
		case 3:
			printf("Chicken Eating Worm.\n");
			break;
		case 4:
			printf("Worm Eating Stick.\n");
			break;
	}
}

int Doevent1(int property){ //劉庭吟
	int chose, grade = 0;
	int count, i, Q;
	int bet;
	srand(time(NULL));
	count=3;
	do{
		printf("You want big bet or small?(big=1, small=2)");
		scanf("%d",&bet);
	}while(bet!=1&&bet!=2);

	for(i=1;i<=count;i++){
		printf("Stick Hitting Tiger Wreck Chicken Eating Worm\n");
		printf("1.Stick 2.Tiger 3.Chicken 4.Worm\n");
		printf("Your choice (number): ");
		scanf("%d",&chose);
		while(chose>4||chose<1){
			printf("Wrong answer. Please chose again.\n");
			printf("Your choice (number): ");
			scanf("%d",&chose);
		}
		printf("yours:");
		printselect (chose);
		Q=rand()%4+1;
		printf("opponent:");
		printselect (Q);
		//比較
		if(chose>Q){
			verse (chose);
			printf("You win.\n");
			printf("(>3<)\n\n");
			grade++;
		}
		else if(chose<Q){
			verse(Q);
			printf("You lose.\n");
			printf("(T_T)\n\n");
			grade--;
		}
		else{
			printf("The match ended in a tie.\n");
		}
	}
	//計算財產
	if(bet==1){                           //big
		property+=property*grade/6;
	}
	else{                                //small
		property+=property*grade/12;
	}
	printf("Now your money $%d\n", property);
	//printf("%d",property);
	system("pause");
	return property;
}

int Doevent2(int x){    //  林季樽
	char c[10]; // 玩家出拳
	int computer, gamer; // 電腦出拳
	int result; // 比賽結果
	int count = 0;
	int i;

    gets(c);
	printf("Tips:\nWelcome to the  Rock, paper, scissors!Two out of three.If there is a tie, it will be compared again.\nIf the challenge is successful, you will get $2000,and if you fail,you will lose $1000!\n");
	for(i=0;i<3;i++){
		printf("\nPlease enter what you want throw：\n");
   		printf("1:scissors\n2:Rock\n3:paper\n");
   		scanf("%d",&gamer);
   		while(gamer!=1&& gamer!=2&& gamer!=3){
    		printf("1:scissors\n2:Rock\n3:paper\n");
    		scanf("%d",&gamer);
		}
    	printf("you throw ");
    	switch (gamer){
      		case 1:
       			printf("scissors\n");
        		gamer=1;
        		break;
      		case 2:
      			printf("Rock\n");
        		gamer=3;
        		break;
      		case 3:
      			printf("paper\n");
       		 	gamer=5;
        		break;
    	}

    srand(time(NULL)); // 隨機數種子

    computer=rand()%3; // 產生隨機數並取餘，得到電腦出拳
    result=gamer+computer; // gamer 為 char 型別，數學運算時要強制轉換型別
    printf("computer throw ");
    switch (computer)
    {
      case 0:
	  	printf("scissorsn\n");
		break;
      case 1:
	  	printf("Rock\n");
		break;
      case 2:
	  	printf("paper\n");
	  	break;
    }

    if (result==3||result==6){
    	printf("YOU WIN!\n");
    	count++;
	}
    else if (result==5||result==2) {
 		printf("COMPUTER WIN!\n");

	}

    else {
    	printf("TIE\n");// 1 4 7
    	i--;
	}

	}
	printf("\nScore: %d win %d lose\n",count,3-count);
		if(count>=2){
			printf("YOU WIN! +$2000");
			x+=2000;
		}
		else{
			printf("YOU LOSE! -$1000");
			x-=1000;
		}
    system("pause");
	return x;
}

int Doevent3(int money) {   //陳庭萱

	char arr[100][4], n[10]; //arr存取地圖資訊, n輸入
	char map[100][3] = {"A1", "A2", "A3", "A4", "A5", "A6", "A7", "A8", "A9", "B1", "B2", "B3", "B4", "B5", "B6", "B7", "B8", "B9", "C1", "C2", "C3", "C4", "C5", "C6", "C7", "C8", "C9", "D1", "D2", "D3", "D4", "D5", "D6", "D7", "D8", "D9", "E1", "E2", "E3", "E4", "E5", "E6", "E7", "E8", "E9", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8", "F9", "G1", "G2", "G3", "G4", "G5", "G6", "G7", "G8", "G9", "H1", "H2", "H3", "H4", "H5", "H6", "H7", "H8", "H9", "I1", "I2", "I3", "I4", "I5", "I6", "I7", "I8", "I9"};
	//設定格子名稱
	int i, flag;

	getchar();
	for (i = 0; i < 100; i++) {
		arr[i][0] = ' ';
		arr[i][1] = '0';
		arr[i][2] = 'B';

		if (i == 5 || i == 10 || i == 11 || i == 12 || i == 19 || i == 21 || i == 23 || i == 27 || i == 30 || i == 32 || i == 33 || i == 34 || i == 36 || i == 39 || i == 41 || i == 42 || i == 43 || i == 45 || i == 49 || i == 55 || i == 74 || i == 75 || i == 76 || i == 77 || i == 78 || i == 79 ) {
				arr[i][1] = '1';
		}

		else if (i == 8 || i == 14 || i == 26 || i == 28 || i == 29 || i == 38 || i == 39 || i == 46 || i == 48 || i == 50 || i == 52 || i == 58 || i == 65 || i == 67 || i == 68 || i == 70 ) {
			arr[i][1] = '2';
		}

		else if (i == 7 || i == 15 || i == 25 || i == 56 || i == 59 || i == 61 ) {
			arr[i][1] = '3';
		}

		else if (i == 6 || i == 16 || i == 17 || i == 20 || i == 24 || i == 37 || i == 47 || i == 51 || i == 57 || i == 60 || i == 66 || i == 69) {
			arr[i][1] = 'B';
		}
	} //對地圖輸入基本資料

	printf ("  _1____2____3____4____5____6____7____8____9___.\n");
	printf ("A |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[0][0], arr[0][0], arr[2][0], arr[3][0], arr[4][0], arr[5][0], arr[6][0], arr[7][0], arr[8][0]);
	printf ("  |____|____|____|____|____|____|____|____|____|\n");
	printf ("B |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[9][0], arr[10][0], arr[11][0], arr[12][0], arr[13][0], arr[14][0], arr[15][0], arr[16][0], arr[17][0]);
	printf ("  |____|____|____|____|____|____|____|____|____|\n");
	printf ("C |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[18][0], arr[19][0], arr[20][0], arr[21][0], arr[22][0], arr[23][0], arr[24][0], arr[25][0], arr[26][0]);
	printf ("  |____|____|____|____|____|____|____|____|____|\n");
	printf ("D |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[27][0], arr[28][0], arr[29][0], arr[30][0], arr[31][0], arr[32][0], arr[33][0], arr[34][0], arr[35][0]);
	printf ("  |____|____|____|____|____|____|____|____|____|\n");
	printf ("E |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[36][0], arr[37][0], arr[38][0], arr[39][0], arr[40][0], arr[41][0], arr[42][0], arr[43][0], arr[44][0]);
	printf ("  |____|____|____|____|____|____|____|____|____|\n");
	printf ("F |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[45][0], arr[46][0], arr[47][0], arr[48][0], arr[49][0], arr[50][0], arr[51][0], arr[52][0], arr[53][0]);
	printf ("  |____|____|____|____|____|____|____|____|____|\n");
	printf ("G |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[54][0], arr[55][0], arr[56][0], arr[57][0], arr[58][0], arr[59][0], arr[60][0], arr[61][0], arr[62][0]);
	printf ("  |____|____|____|____|____|____|____|____|____|\n");
	printf ("H |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[63][0], arr[64][0], arr[65][0], arr[66][0], arr[67][0], arr[68][0], arr[69][0], arr[70][0], arr[71][0]);
	printf ("  |____|____|____|____|____|____|____|____|____|\n");
	printf ("I |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[72][0], arr[73][0], arr[74][0], arr[75][0], arr[76][0], arr[77][0], arr[78][0], arr[79][0], arr[80][0]);
	printf ("  |____|____|____|____|____|____|____|____|____|\n"); //印出地圖

	printf ("請輸入想打開的號碼 ex:A1、C3...(Ctrl+Z結束遊戲)\n");
	printf ("破開所有數字格以通關\n");

	while (gets(n) != NULL) {
		for (i = 0; i < 100; i++) {
			flag = 0;
			if (strcmp (n, map[i]) == 0) {
				if (arr[i][1] == '1' || arr[i][1] == '2' || arr[i][1] == '3'){
					arr[i][0] = arr[i][1];
				} //點到數字，替換

				else if (arr[i][1] == 'B') {
					printf ("BOMB!!!\n");
					printf ("You Lose the Game. -$2000\n");
					money -= 2000;
					printf ("按任意鍵離開\n");
					scanf ("%c", n);
					flag = 1;
					break;
				} //點到炸彈，遊戲結束

				else if (i == 0 || i == 1 || i == 2 || i == 3 || i == 4 || i == 9 || i == 13 || i == 18 || i == 22 || i == 31 || i == 40) {
					arr[0][0] = arr[0][1];	arr[1][0] = arr[1][1];	arr[2][0] = arr[2][1];	arr[3][0] = arr[3][1];	arr[4][0] = arr[4][1];	arr[9][0] = arr[9][1];
					arr[13][0] = arr[13][1];	arr[18][0] = arr[18][1];	arr[22][0] = arr[22][1];	arr[31][0] = arr[31][1];	arr[40][0] = arr[40][1];
				}
				else if (i == 35 || i == 44 || i == 53 || i == 62 || i == 71 || i == 80) {
					arr[35][0] = arr[35][1];	arr[44][0] = arr[44][1];	arr[53][0] = arr[53][1];	arr[62][0] = arr[62][1];	arr[71][0] = arr[71][1];	arr[80][0] = arr[80][1];
				}
				else if (i == 54 || i == 63 || i == 64 || i == 72 || i == 73) {
					arr[54][0] = arr[54][1];	arr[63][0] = arr[63][1];	arr[64][0] = arr[64][1];	arr[72][0] = arr[72][1];	arr[73][0] = arr[73][1];
				} //點到空白，替換
			}



		}
		if(flag == 1)
			break;
		printf ("  _1____2____3____4____5____6____7____8____9___.\n");
		printf ("A |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[0][0], arr[0][0], arr[2][0], arr[3][0], arr[4][0], arr[5][0], arr[6][0], arr[7][0], arr[8][0]);
		printf ("  |____|____|____|____|____|____|____|____|____|\n");
		printf ("B |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[9][0], arr[10][0], arr[11][0], arr[12][0], arr[13][0], arr[14][0], arr[15][0], arr[16][0], arr[17][0]);
		printf ("  |____|____|____|____|____|____|____|____|____|\n");
		printf ("C |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[18][0], arr[19][0], arr[20][0], arr[21][0], arr[22][0], arr[23][0], arr[24][0], arr[25][0], arr[26][0]);
		printf ("  |____|____|____|____|____|____|____|____|____|\n");
		printf ("D |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[27][0], arr[28][0], arr[29][0], arr[30][0], arr[31][0], arr[32][0], arr[33][0], arr[34][0], arr[35][0]);
		printf ("  |____|____|____|____|____|____|____|____|____|\n");
		printf ("E |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[36][0], arr[37][0], arr[38][0], arr[39][0], arr[40][0], arr[41][0], arr[42][0], arr[43][0], arr[44][0]);
		printf ("  |____|____|____|____|____|____|____|____|____|\n");
		printf ("F |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[45][0], arr[46][0], arr[47][0], arr[48][0], arr[49][0], arr[50][0], arr[51][0], arr[52][0], arr[53][0]);
		printf ("  |____|____|____|____|____|____|____|____|____|\n");
		printf ("G |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[54][0], arr[55][0], arr[56][0], arr[57][0], arr[58][0], arr[59][0], arr[60][0], arr[61][0], arr[62][0]);
		printf ("  |____|____|____|____|____|____|____|____|____|\n");
		printf ("H |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[63][0], arr[64][0], arr[65][0], arr[66][0], arr[67][0], arr[68][0], arr[69][0], arr[70][0], arr[71][0]);
		printf ("  |____|____|____|____|____|____|____|____|____|\n");
		printf ("I |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |%c   |\n", arr[72][0], arr[73][0], arr[74][0], arr[75][0], arr[76][0], arr[77][0], arr[78][0], arr[79][0], arr[80][0]);
		printf ("  |____|____|____|____|____|____|____|____|____|\n");
		//印出替換過的陣列

		if (arr[5][0] == '1' && arr[10][0] == '1' && arr[11][0] == '1' && arr[12][0] == '1' && arr[19][0] == '1' && arr[21][0] == '1' &&
			arr[23][0] == '1' && arr[27][0] == '1' && arr[30][0] == '1' && arr[32][0] == '1' && arr[33][0] == '1' && arr[34][0] == '1' &&
			arr[36][0] == '1' && arr[39][0] == '1' && arr[41][0] == '1' && arr[42][0] == '1' && arr[43][0] == '1' && arr[45][0] == '1' &&
			arr[49][0] == '1' && arr[55][0] == '1' && arr[74][0] == '1' && arr[75][0] == '1' && arr[76][0] == '1' && arr[77][0] == '1' &&
			arr[78][0] == '1' && arr[79][0] == '1' &&

			arr[8][0] == '2' && arr[14][0] == '2' && arr[26][0] == '2' && arr[28][0] == '2' && arr[29][0] == '2' && arr[38][0] == '2' &&
			arr[46][0] == '2' && arr[48][0] == '2' && arr[50][0] == '2' && arr[52][0] == '2' && arr[58][0] == '2' &&
			arr[65][0] == '2' && arr[67][0] == '2' && arr[68][0] == '2' && arr[70][0] == '2' &&

			arr[7][0] == '3' && arr[15][0] == '3' && arr[25][0] == '3' && arr[56][0] == '3' && arr[59][0] == '3' && arr[61][0] == '3') {
				printf ("\nYou Win the Game!! +$3000\n");
				money += 3000;
				printf ("按任意鍵離開\n");
				scanf ("%c", n);
				flag = 1;
				break;
		} //如果所有數字格都被打開，遊戲結束

		if(flag == 1)
			break;
		printf ("請輸入想打開的號碼 ex:A1、C3...(Ctrl+Z結束遊戲)\n");
		printf ("破開所有數字格以通關\n");

	}

	return money;
}
