#include<iostream>
#include"setgame.h"
#include<windows.h>
#include<cstdlib>
#include<string>
#include<cstdlib>
#include<vector>
#include<ctime>
#include<conio.h>
#include<mmsystem.h>
#pragma comment(lib,"Winmm.lib")
using namespace std;

struct player{
    int color, money, land, house_account, stop_day, info_y, life;
    int house[32];
};

struct land{
    string landmark;
    int x, y, price, owner, lv, color;
};

struct land Land[34];
struct player Player[4];

void printplace(string c, int x, int y, int color);
void printall();
void PrintInfo(int i);
void Printcharacter(int people);
void DoPrison(int i);
void DoDes1(int i);
void DoDes2(int i);
void DoDes3(int i);
void DoChan1(int i);
void DoChan2(int i);
void DoChan3(int i);
void DoLand(int i, int land);
void CleanPlayer(int i);

int main(){
    system("mode con cols=172 lines=80");	//設定cmd大小
    system("title Monopoly       Create by FCU IECS109 team 12");
    PlaySound(TEXT("music.wav"),NULL,SND_FILENAME | SND_ASYNC | SND_LOOP);

    srand(time(NULL));
	char map[34][100] = {"春日部", "真心鎮", "哇賽秘境", "比奇堡", "霍格華茲", "米奇妙妙屋",	//中文*2
						"小鎮村", "米花町", "雷門", "龜有公園前派出所","杜芬舒斯的邪惡企業", "童實野市", "動物方城市", "怪獸大學",
						"天兵公園","南方公園", "怪誕小鎮", "happy tree", "蟹堡王", "海之霸",
						"卡加布列島","糖果王國", "無名小鎮", "命運", "命運", "命運", "機會", "機會",
						"機會", "EVENT","EVENT", "EVENT", "監獄", "起點"};
    int flag[34] = {0};
    int people, character, i, j, ran, start, prison, des1, des2, des3, chan1, chan2, chan3, event1, event2, event3, step, round, dead, flag_death;
    for(i=0; i<34; i++){
    	Land[i].x = Land[i].y = 0;
	}

    Welcome();
    do{
        MoveConsole(94, 13);
        cin >> people;
        if(people < 2 || people > 4){
            MoveConsole(82, 14);
            cout << "ERROR";
            MoveConsole(94, 13);
            cout << " ";
        }
    }while(people < 2 || people > 4);

    system("cls");                              //清空文字

    PrintChooseCharacter();
    SetColor();
    MoveConsole(5, 0);
    for(int i=0; i<people; i++){
        cout << "請選擇想要的角色:";
        do{
            MoveConsole(22, i);
            cin >> character;
            if(character < 1 || character > 4){
                MoveConsole(10, 1+i);
                cout << "ERROR";
                MoveConsole(22, i);
                cout << " ";
            }
            switch(character){
                case 1: Player[i].color = 10; break;
                case 2: Player[i].color = 11; break;
                case 3: Player[i].color = 13; break;
                case 4: Player[i].color = 14; break;
            }
        }while(character < 1 || character > 4);
        MoveConsole(5, 1+i);
    }

    system("cls");
    MoveConsole(0, 0);

	ran = rand() % 4;
	flag[ran] = 1;
	switch(ran){
	    case 0: prison = 0; Land[0].x = 6; Land[0].y = 5; Land[0].landmark = map[32]; break;
	    case 1: prison = 11; Land[11].x = 138; Land[11].y = 5; Land[11].landmark = map[32]; break;
	    case 2: prison = 17; Land[17].x = 6; Land[17].y = 41; Land[17].landmark = map[32]; break;
	    case 3: prison = 28; Land[28].x = 138; Land[28].y = 41; Land[28].landmark = map[32]; break;
	}

	do{
		ran = rand() % 4;
	}while(flag[ran] == 1);
	switch(ran){
        case 0: start = 0; Land[0].x = 6; Land[0].y = 5; Land[0].landmark = map[33]; break;
	    case 1: start = 11; Land[11].x = 138; Land[11].y = 5; Land[11].landmark = map[33]; break;
	    case 2: start = 17; Land[17].x = 6; Land[17].y = 41; Land[17].landmark = map[33]; break;
	    case 3: start = 28; Land[28].x = 138; Land[28].y = 41; Land[28].landmark = map[33]; break;
	}
	for(i=0; i<4; i++){
		flag[i] = 0;
	}

	j = 32;
	i = 0;
	while(i < 34){
		if(Land[i].x != 0){
			i++;
			continue;
		}
		while(j){
			ran = rand() % 32;
			if(flag[ran] == 0){
				flag[ran] = 1;
				j--;
				break;
			}
		}
		Land[i].landmark = map[ran];
		switch(ran){
            case 23: des1 = i; break;
            case 24: des2 = i; break;
            case 25: des3 = i; break;
            case 26: chan1 = i; break;
            case 27: chan2 = i; break;
            case 28: chan3 = i; break;
            case 29: event1 = i; break;
            case 30: event2 = i; break;
            case 31: event3 = i; break;
		}
		i++;
	}

    for(i=0; i<34; i++){
        Land[i].color = 7;
        Land[i].lv = 0;
        if(i == start || i == prison || i == des1 || i == des2 || i == des3 || i == chan1 || i == chan2 || i == chan3 || i == event1 || i == event2 || i == event3)
            continue;
        else{
            Land[i].price = 100 * (i+1);
            Land[i].owner = -1;
            Land[i].lv = 1;
        }
    }

    for(i=0; i<people; i++){
        Player[i].money = 15000;
        Player[i].land = start;
        Player[i].house_account = 0;
        Player[i].info_y = 4*i+1;
        Player[i].life = 1;
        MoveConsole(Land[Player[i].land].x + i, Land[Player[i].land].y);
        SetColor(Player[i].color);
        cout << "*";
    }

    SetColor();
    MoveConsole(0, 0);
    printmap();
    printall();
    Printcharacter(people);
    SetColor();
    for(j=0; j<people; j++){
        PrintInfo(j);
    }
    MoveConsole(14, 8);
    system("pause");

    dead = round = 0;
    while(dead < people-1){
        round++;
        for(i=0; i<people; i++){
            flag_death = 0;
            printall();
            if(Player[i].life == 0)
                continue;

            if(Player[i].stop_day){
                SetColor(Player[i].color);
                DoPrison(i);
                Player[i].stop_day--;
            }
            else{
                MoveConsole(14, 8);
                SetColor(Player[i].color);
                cout << "第" << round << "回合 " << i+1 << "號玩家擲骰 ";
                step = rand() % 6 + 1;
                MoveConsole(14, 9);
                cout << i+1 << "號玩家擲出" << step << "點";

                Erase(Land[Player[i].land].x + i, Land[Player[i].land].y, 1);   //清除前一次位置標記

                Player[i].land += step;
                if(Player[i].land > 33)
                    Player[i].land -= 34;

                MoveConsole(Land[Player[i].land].x + i, Land[Player[i].land].y);
                SetColor(Player[i].color);
                cout << "*";
                SetColor();

                if(Player[i].land == start){
                    Player[i].money += 2000;
                    MoveConsole(14, 11);
                    cout << "踩中起點 獲得2000元";
                }
                else if(Player[i].land == prison){
                    Player[i].stop_day = step;
                    MoveConsole(14, 11);
                    cout << "鋃鐺入獄 停止前進" << step << "天";
                }
                else if(Player[i].land == des1 || Player[i].land == des2 || Player[i].land == des3){
                    ran = rand() % 3;
                    switch(ran){
                        case 0: DoDes1(i); break;
                        case 1: DoDes2(i); break;
                        case 2: DoDes3(i); break;
                    }
                }
                else if(Player[i].land == chan1 || Player[i].land == chan2 || Player[i].land == chan3){
                    ran = rand() % 3;
                    switch(ran){
                        case 0: DoChan1(i); break;
                        case 1: DoChan2(i); break;
                        case 2: DoChan3(i); break;
                    }
                }
                else if(Player[i].land == event1 || Player[i].land == event2 || Player[i].land == event3){
                    MoveConsole(14, 11);
                    cout << "觸發EVENT";
                    MoveConsole(14, 12);
                    system("pause");
                    system("cls");
                    ran = rand() % 3;
                    switch(ran){
                        case 0: Player[i].money = Doevent1(Player[i].money); break;
                        case 1: Player[i].money = Doevent2(Player[i].money); break;
                        case 2: Player[i].money = Doevent3(Player[i].money); break;
                    }
                    system("cls");
                    printmap();
                    printall();
                    Printcharacter(people);
                    SetColor();
                }
                else{
                    DoLand(i, Player[i].land);
                }
            }

            SetColor();
            if(Player[i].money <= 0){
                    MoveConsole(14, 12);
                    system("pause");
                    Player[i].life = 0;
                    dead++;
                    CleanPlayer(i);
                    flag_death = 1;
            }

            for(j=1; j<13; j++){
                Erase(147, j, 20);
            }
            for(j=0; j<people; j++){
                SetColor();
                PrintInfo(j);
            }
            MoveConsole(14, 15);
            system("pause");
            for(j=8; j<=15; j++){
                Erase(14, j, 100);
            }

            if(flag_death)
                break;
        }

    }

    system("cls");
    for(i=0; i<people; i++){
        if(Player[i].life){
            SetColor();
            MoveConsole(70, 10);
            cout << "遊戲結束 獲勝者為" << i+1 << "號玩家";
        }
    }

	MoveConsole(0, 20);
    return 0;
}

void printplace(string c, int x, int y, int color){
	HANDLE hin;
    COORD pos;
	hin = GetStdHandle(STD_OUTPUT_HANDLE);
    pos.X = x, pos.Y = y; 					// 設定位置。
    SetConsoleCursorPosition(hin, pos);
    SetColor(color);
	cout << c;
}

void printall(){
    int x, xx, y, len, i, j;
    char map_spe[4][100] = {"龜有公園", "前派出所", "杜芬舒斯", "的邪惡企業"};
    int start_pos[] = {1, 13, 25, 37, 49, 61, 73, 85, 97, 109, 121, 133};

    x = 6;
    for(i=0; i<12; i++){
        Land[i].x = x;
        Land[i].y = 5;
        x += 12;
        xx = start_pos[i];

        if(Land[i].lv){
            MoveConsole(xx+3, 1);
            SetColor(Land[i].color);
            cout << "Lv." << Land[i].lv;
        }

		len = Land[i].landmark.length();
    	if(len == 4 || len == 5)
    		printplace(Land[i].landmark, xx+3, 3, Land[i].color);
		else if(len == 6 || len == 8)
			printplace(Land[i].landmark, xx+2, 3, Land[i].color);
		else if(len == 10)
			printplace(Land[i].landmark, xx+1, 3, Land[i].color);
		else if(len == 16){
			printplace(map_spe[0], xx+2, 2, Land[i].color);
			printplace(map_spe[1], xx+2, 3, Land[i].color);
		}
		else if(len == 18){
			printplace(map_spe[2], xx+2, 2, Land[i].color);
			printplace(map_spe[3], xx+1, 3, Land[i].color);
		}
    }

    y = 11;
    for(i=12; i<17; i++){
        Land[i].x = 138;
        Land[i].y = y;
        xx = 133;

        if(Land[i].lv){
            MoveConsole(xx+3, y-4);
            SetColor(Land[i].color);
            cout << "Lv." << Land[i].lv;
        }

        len = Land[i].landmark.length();
    	if(len == 4 || len == 5)
    		printplace(Land[i].landmark, xx+3, y-2, Land[i].color);
		else if(len == 6 || len == 8)
			printplace(Land[i].landmark, xx+2, y-2, Land[i].color);
		else if(len == 10)
			printplace(Land[i].landmark, xx+1, y-2, Land[i].color);
		else if(len == 16){
			printplace(map_spe[0], xx+2, y-3, Land[i].color);
			printplace(map_spe[1], xx+2, y-2, Land[i].color);
		}
		else if(len == 18){
			printplace(map_spe[2], xx+2, y-3, Land[i].color);
			printplace(map_spe[3], xx+1, y-2, Land[i].color);
		}
		y += 6;
    }

    x = 138;
    j = 11;
    for(i=17; i<29; i++){
        Land[i].x = x;
        Land[i].y = 41;
        x -= 12;
        xx = start_pos[j];
        j--;

        if(Land[i].lv){
            MoveConsole(xx+3, 37);
            SetColor(Land[i].color);
            cout << "Lv." << Land[i].lv;
        }

		len = Land[i].landmark.length();
    	if(len == 4 || len == 5)
    		printplace(Land[i].landmark, xx+3, 39, Land[i].color);
		else if(len == 6 || len == 8)
			printplace(Land[i].landmark, xx+2, 39, Land[i].color);
		else if(len == 10)
			printplace(Land[i].landmark, xx+1, 39, Land[i].color);
		else if(len == 16){
			printplace(map_spe[0], xx+2, 38, Land[i].color);
			printplace(map_spe[1], xx+2, 39, Land[i].color);
		}
		else if(len == 18){
			printplace(map_spe[2], xx+2, 38, Land[i].color);
			printplace(map_spe[3], xx+1, 39, Land[i].color);
		}
    }

    y = 35;
    for(i=29; i<34; i++){
        Land[i].x = 6;
        Land[i].y = y;
        xx = 1;

        if(Land[i].lv){
            MoveConsole(xx+3, y-4);
            SetColor(Land[i].color);
            cout << "Lv." << Land[i].lv;
        }

        len = Land[i].landmark.length();
    	if(len == 4 || len == 5)
    		printplace(Land[i].landmark, xx+3, y-2, Land[i].color);
		else if(len == 6 || len == 8)
			printplace(Land[i].landmark, xx+2, y-2, Land[i].color);
		else if(len == 10)
			printplace(Land[i].landmark, xx+1, y-2, Land[i].color);
		else if(len == 16){
			printplace(map_spe[0], xx+2, y-3, Land[i].color);
			printplace(map_spe[1], xx+2, y-2, Land[i].color);
		}
		else if(len == 18){
			printplace(map_spe[2], xx+2, y-3, Land[i].color);
			printplace(map_spe[3], xx+1, y-2, Land[i].color);
		}
        y -= 6;
    }
}

void DoPrison(int i){
    srand(time(NULL));
    int dice;

    MoveConsole(14, 11);
    cout <<  i+1 << "號玩家坐牢中 剩餘" << Player[i].stop_day << "天";
    MoveConsole(14, 12);
    cout << "投擲骰子 骰到偶數可無罪釋放    ";
    system("pause");
    Erase(44, 12, 25);
    dice = rand() % 6 + 1;
    if(dice % 2 == 0){
        MoveConsole(14, 13);
        cout << "點數為" << dice << " 無罪釋放";
        Player[i].stop_day = 1;
    }
    else{
        MoveConsole(14, 13);
        cout << "很可惜 點數為" << dice << " 你還有" << Player[i].stop_day << "天的牢獄之災";
    }
    MoveConsole(14, 15);
}

void DoDes1(int i){     //林季樽
    MoveConsole(14, 11);
    cout << "玩家" << i+1 << "在武漢肺炎期間帶著皮卡丘去KTV且未配戴口罩，遭罰款$1000";
    Player[i].money -= 1000;
}

void DoDes2(int i){     //劉庭吟
    MoveConsole(14, 11);
    printf("Player%d buy a KRABBY PATTY at Krusty Krab.", i+1);
    MoveConsole(14, 12);
	printf("SpongeBob : it costs 2000.");
    Player[i].money -= 2000;
}

void DoDes3(int i){     //陳庭萱
    MoveConsole(14, 11);
    printf ("您掉入了火箭隊的陷阱 -$3000");
    Player[i].money -= 3000;
}

void DoChan1(int i){    //劉庭吟
    MoveConsole(14, 11);
    printf("Player%d caught wild Pikachu! $3000 for rewards.", i+1);
    Player[i].money += 3000;
}

void DoChan2(int i){    //林季樽
    int num;
	int r;

    MoveConsole(14, 11);
    printf("流川楓上課無聊想玩猜數字遊戲，若你能猜中他心中的數字，則可以獲得$2000，猜錯則損失$1000!");
    MoveConsole(14, 12);
    printf("請輸入1~10任一數:");
    scanf("%d",&num);
	srand(time(NULL));
	r=rand()%10+1;
	MoveConsole(14, 13);

	if(num==r){
		printf("猜對了!答案是%d，獲得$2000",r);
		Player[i].money += 2000;

	}
	else{
		printf("猜錯了!答案是%d，損失$1000",r);
		Player[i].money -= 1000;
	}
}

void DoChan3(int i){     //陳庭萱
    MoveConsole(14, 11);
    printf ("在地上撿到了其他冒險者的背包 +$3000");
    Player[i].money += 3000;
}

void Printcharacter(int people){
    for(int i=0; i<people; i++){
        MoveConsole(Land[Player[i].land].x + i, Land[Player[i].land].y);
        SetColor(Player[i].color);
        cout << "*";
    }
}

void DoLand(int i, int land){
    char choice;
    int flag;

    MoveConsole(14, 11);
    if(Player[i].money >= Land[land].price && Land[land].owner == -1){
        cout << "是否要花費 $" << Land[land].price << " 購買 " << Land[land].landmark << " ?(Y/y or N/n)";
        do{
            flag = 0;
            //Erase(22, 13, 5);
            Erase(24, 12, 1);
            MoveConsole(24, 12);
            cin >> choice;
            if(choice == 'Y' || choice == 'y'){
                Player[i].house[Player[i].house_account] = land;
                Player[i].house_account++;
                Player[i].money -= Land[land].price;
                Land[land].owner = i;
                Land[land].color = Player[i].color;
                Erase(22, 13, 5);
                MoveConsole(14, 13);
                cout << "購買成功!";
            }
            else if(choice == 'N' || choice == 'n'){
                    Erase(22, 13, 5);
                    MoveConsole(14, 13);
                    cout << "購買失敗!";
            }
            else{
                MoveConsole(22, 13);
                cout << "ERROR";
                flag = 1;
            }
        }while(flag);
    }
    else if(Player[i].money < Land[land].price && Land[land].owner == -1)
        cout << Land[land].landmark << " 售價為$" << Land[land].price << " 真抱歉 您的現金不足!";
    else if(Land[land].owner != i && Land[land].owner != 4){
        cout << Land[land].landmark << " 為" <<  Land[land].owner+1 << "號玩家的地 " << i+1 << "號玩家需支付 $" << Land[land].price << " 給" << Land[land].owner+1 << "號玩家";
        Player[i].money -= Land[land].price;
        Player[Land[land].owner].money += Land[land].price;
    }
    else if(Land[land].owner == i){
        cout << "現在 " << Land[land].landmark << " 等級為" << Land[land].lv << "級 是否花費 $" << Land[land].price << " 升級?(Y/y or N/n)";
        do{
            flag = 0;
            //Erase(22, 13, 5);
            Erase(24, 12, 1);
            MoveConsole(24, 12);
            cin >> choice;
            if(choice == 'Y' || choice == 'y'){
                Player[i].money -= Land[land].price;
                Land[land].lv++;
                Land[land].price *= 2;
                Erase(22, 13, 5);
                MoveConsole(14, 13);
                cout << "升級成功!";
            }
            else if(choice == 'N' || choice == 'n'){
                    Erase(22, 13, 5);
                    MoveConsole(14, 13);
                    cout << "升級失敗!";
            }
            else{
                MoveConsole(22, 13);
                cout << "ERROR";
                flag = 1;
            }
        }while(flag);
    }
    else if(Land[land].owner == 4)
        cout << "公有土地 無法進行動作";
}

void PrintInfo(int i){
    MoveConsole(147, Player[i].info_y);
    cout << i+1 << "號玩家:";
    MoveConsole(147, Player[i].info_y+1);
    cout << "$" << Player[i].money;
}

void CleanPlayer(int i){
    Player[i].color = 136;
    for(int j=0; j<Player[i].house_account; j++){
        Land[Player[i].house[j]].color = 136;
        Land[Player[i].house[j]].owner = 4;
    }
    for(int j=11; j<14; j++){
        Erase(14, j, 100);
    }
    MoveConsole(14, 13);
    SetColor(12);
    cout << i+1 << "號玩家已被淘汰 土地收歸公有";
    MoveConsole(14, 14);
    system("pause");
}
