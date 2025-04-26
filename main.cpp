#include<stdio.h>
#include <conio.h>
#include<windows.h>
#include<math.h>
#include<stdlib.h> 
#include<time.h> 

//定义 
int stop=0;//传输终止指令（不会别的方法，就只能想到这样了555） 
int direction=90;//蛇的方向，让玩家未操作时也会移动 
int tick=1;//游戏刻，0.05s 
float rate=0.1;//刷新率`
int length=0;//蛇的长度 
char map[41][21];//游戏地图 
int longer=0;//判断是否可增长，以及增长量 
int food=1;//食物数量 

void gotoxy(short x, short y) {
  COORD coord = {x, y};
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clear() {
    printf("\033[H\033[J"); // ANSI 转义序列清屏
}

struct coordinate//坐标-结构体 
{
	int x=0,y=0;
}head,snake[100],tempt;//储存蛇的所有坐标和蛇头 

void spawn_food()//生成食物
{

		int x,y;
		
		do{

		    x = rand() % 40;
		    y = rand() % 20;
		    
		}while(map[x][y]=='*' || map[x][y]=='0');//随机到一个空坐标
		map[x][y]='0';
	
	
}

struct coordinate keyboard_listen(struct coordinate input_xy)//读取键盘输入-函数 
{
	int tdir;
    int ch;
    tdir=direction;
    if (_kbhit()){//如果有按键按下，则_kbhit()函数返回真，_kbhit()不会读入缓冲区的按键数据，按键数据会保留并交由getch()读取 
    
        ch = getch();//使用bioskey()函数获取按下的键值
//		printf("%d",ch);
        switch(ch){
        	
		    case 87  ://W 
			case 119  : 
		       direction=0;
		       break;
		       
		    case 68  ://D
		    case 100 : 
		       direction=90;
		       break;
		       
		    case 83  ://S
		    case 115  : 
		       direction=180;
		       break;
		       
		    case 65  ://A
		    case 97  : 
		       direction=270;
		       break;
		    
		    
			case 27 ://ESC
				stop=1;
				return input_xy;
				break;
				

		}
    }
    
	if(abs(tdir-direction)==180) //防止蛇180度反转 
	{
		direction=tdir;
	}
	
    switch(direction)
    {
    	case 0://UP
	    	input_xy.y--;
			break;
		case 90://RIGHT
			input_xy.x++;
			break;
		case 180://DOWN
	    	input_xy.y++;
			break;
		case 270://LEFT
	    	input_xy.x--;
			break;
		default :
			printf("Error,direction Invalid!");
	}
	
	//边界检测 
	if(input_xy.x>40)
	{
		input_xy.x=0;
	}
	else if(input_xy.x<0)
	{
			input_xy.x=40;
	}
	if(input_xy.y>20)
	{
		input_xy.y=0;
	}
	else if(input_xy.y<0)
	{
		input_xy.y=20;
	}
	

	
	return input_xy;//返回新位置 
}


void render_snake() { //将蛇渲染到地图上 
    snake[0] = head;

    for(int i = 0; i <= length; i++)
        map[snake[i].x][snake[i].y] = '*';

}

void print_map(char map0[41][21])//打印地图函数 
{
	render_snake(); //将蛇渲染到地图上 
	gotoxy(0,0);
	printf("________________________________________\n");
	for(int y=0;y<=20;y++)
	{
		printf("|");
		for(int x=0;x<=40;x++)
			printf("%c",map0[x][y]);//先打印行，换行 
		printf("|");
		printf("\n");
	}
	printf("________________________________________\n");
		
}



void paste(struct coordinate *a,struct coordinate b)//将a移动到到b的坐标上 
{
	 
	a->x=b.x;
	a->y=b.y;
	
}

void ShowCursor(bool visible) { //显示或隐藏光标
    CONSOLE_CURSOR_INFO cursor_info = {20, visible};
    //CONSOLE_CURSOR_INFO结构体包含控制台光标信息，成员分别表示光标百分比厚度和是否可见
    SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursor_info);
 //SetConsoleCursorInfo设定控制台窗口的光标大小和是否可见
}


int main()
{

	ShowCursor(false);//关闭光标
	srand(time(0));

	system("cls");
	printf("                                            WELCOME  TO                                                  \n");
	Sleep(50);
	printf("  _   _   _   _   _   _    ____   _____   ____          ____    _   _      _      _  __  _____ \n");
	Sleep(50);
	printf(" | | | | | | | | | \\ | |  / ___| | ____| |  _ \\        / ___|  | \\ | |    / \\    | |/ / | ____|\n");
	Sleep(50);
	printf(" | |_| | | | | | |  \\| | | |  _  |  _|   | |_) |       \\___ \\  |  \\| |   / _ \\   | ' /  |  _|  \n");
	Sleep(50);
	printf(" |  _  | | |_| | | |\\  | | |_| | | |___  |  _ <         ___) | | |\\  |  / ___ \\  | . \\  | |___ \n");
	Sleep(50);
	printf(" |_| |_|  \\___/  |_| \\_|  \\____| |_____| |_| \\_\\       |____/  |_| \\_| /_/   \\_\\ |_|\\_\\ |_____|\n");
	Sleep(50);
	printf("                                                                       \n");
	Sleep(50);
	printf("\n");
	Sleep(1000);
	printf("                                PLEASE PRESS THE NUMBER TO SELECT                                       \n");
	printf("\n");
	printf("                            1.START THE GAME             2.QUIT THE GAME                                 \n");
	printf("\n");
	printf("\n");
	printf("                                   THANKS FOR ENTERING THE GAME                                            \n");
	Beep(550,500);
	Beep(600,500);
	Beep(750,500);
	
	Beep(800,500);
	Beep(1000,1000);

	char option='0';
	while(1)
	{
		option=getch();
		if(option=='1')
			break;
		if(option=='2')
			return 0;
	}
	system("cls");
	int s=0;
	printf("\n");
	printf("\n");
	printf("\n");
	printf("\n");
	printf("              ");
	char a[100]="Please open the Capslock or change your Input Method.";
	while(a[s]!='\0')
	{
		printf("%c",a[s]);
		s++;
		Sleep(10);
	}
	Sleep(1000);
	
	system("cls");



label:
stop=0;//传输终止指令（不会别的方法，就只能想到这样了555） 
direction=90;//蛇的方向，让玩家未操作时也会移动 
length=0;//蛇的长度 
longer=0;//判断是否可增长，以及增长量 
food=1;//食物数量 

	//初始化 
	head.x=20;
	head.y=10;
	snake[0]=head;

	
	
	
	
	for(int y=0;y<=20;y++)
		for(int x=0;x<=40;x++)
			map[x][y]=' ';		//初始化空地图 
	
	
	print_map(map);//打印地图
	for(;food>0;food--)//初始化食物
		spawn_food();
	int t=rate;
	struct coordinate tmp=head,ttmp;
	while(1)
	{
		Sleep(tick);
		if(t<=0)
		{
			t=rate;
			ttmp=snake[length];
			for(int i=length-1;i>=0;i--)//身体逐步移动 
			{
				
				paste(&snake[i+1],snake[i]);
				
			}
			
			if(longer==0)//执行增长操作 
			{
				map[ttmp.x][ttmp.y]=' ';
			}
			else
			{
				length++;
				snake[length]=ttmp;
				longer--;
			}
			
			
			if(map[tmp.x][tmp.y]=='0')//吃食检测
			{

				map[tmp.x][tmp.y]=='*';
				longer+=1;
				spawn_food();
			}
			else if(map[tmp.x][tmp.y]=='*')
			{
				break;
			}
			head=tmp;//头移动
		}
		else
		{
			t--;
		}
		tmp=keyboard_listen(head);//头移动缓冲区 
		print_map(map);//打印地图
//		printf("%d %d",head.x,head.y);
		printf("  rate=%f  score=%d  food=%d",rate,length,food);

		
		
		
		
	}
	
	system("cls");
	printf("                                                                       \n");
	printf("   ____      _      __  __   _____      ___   __     __  _____   ____  \n");
	printf("  / ___|    / \\    |  \\/  | | ____|    / _ \\  \\ \\   / / | ____| |  _ \\ \n");
	printf(" | |  _    / _ \\   | |\\/| | |  _|     | | | |  \\ \\ / /  |  _|   | |_) |\n");
	printf(" | |_| |  / ___ \\  | |  | | | |___    | |_| |   \\ V /   | |___  |  _ < \n");
	printf("  \\____| /_/   \\_\\ |_|  |_| |_____|    \\___/     \\_/    |_____| |_| \\_\\\n");
	printf("                                                                       \n");
	printf("\n");
	printf("\n");
	printf("                        Your get %d points!!\n",length);
	printf("\n");
	Beep(850,250);
	Beep(700,250);
	Beep(600,250);
	Beep(550,500);
	Sleep(2000);
	printf("enter 1 to restart");
	while(getch()==1);
	goto label;
	

	

	return 0;
}
