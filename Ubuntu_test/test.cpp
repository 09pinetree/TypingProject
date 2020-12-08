#include<iostream>
#include"getch.h"
#include<vector>
#include<string>
#include<ctime>
#pragma comment(lib, "winmm.lib")
using namespace std;

//By. BlockDMask.
//[PART1] make screen, change screen, input.
//[PART2] input&output, question, life.
//[PART3] setting level, play music, play time

#include <curses.h>
//#define gotoxy(x,y) wmove(stdscr,y-1,x-1)

#define MAGIC_KEY1 27
#define MAGIC_KEY2 91
#define SPACE 10
#define KEY_NUM 52
#define LIFE 3
#define MAX_LEVEL 11

typedef struct _COORD {
    short X;
    short Y;
} COORD;

enum MENU
{
	GAMESTART = 0,
	INFO,
	QUIT
};

enum KEYBOARD
{
	UP = 65,
	LEFT = 68,
	RIGHT = 67,
	DOWN = 66
};

//Cursor move

void gotoxy(int x, int y) {
    printf("\033[%d;%df", y, x);
    fflush(stdout);
}

//-----------Draw-----------------
void DrawReadyGame()
{
	system("clear");
	gotoxy(5, 2);
	cout << "******************************";
	gotoxy(5, 3);
	cout << "*        Dance Dance!        *";
	gotoxy(5, 4);
	cout << "******************************";
	gotoxy(10, 8);
	cout << "GameStart";
	gotoxy(10, 9);
	cout << "GameInfo";
	gotoxy(10, 10);
	cout << "Quit" << endl;
}

void DrawInfoGame()
{
	system("clear");
	gotoxy(1, 3);
	cout << "*******************************************";
	gotoxy(1, 4);
	cout << "|Developer - BlockDMask";
	gotoxy(1, 5);
	cout << "|Blog - https://blockdmask.tistory.com/";
	gotoxy(1, 8);
	cout << "|Thank you.";
	gotoxy(1, 9);
	cout << "*******************************************";
	gotoxy(1, 10);
	cout << "press SPACE! to return to main menu" <<endl;
}

void DrawStartGame(const int life, const int score, const string questionStr, const string answerStr)
{
	system("clear");
	gotoxy(2, 1);
	cout << "*******************************************";
	gotoxy(4, 3);
	cout << "Life : " << life << " / " << LIFE;
	gotoxy(4, 4);
	cout << "Score : " << score;
	gotoxy(4, 8);
	cout << "Q : " << questionStr;
	gotoxy(4, 10);
	cout << "A : " << answerStr;
	gotoxy(4, 12);
	cout << "press SPACE! after input done.";
	gotoxy(2, 18);
	cout << "*******************************************" << endl;
}

void DrawGameOver(const int playTime)
{
	system("clear");
	gotoxy(2, 1);
	cout << "*******************************************";
	gotoxy(8, 8);
	cout << "-------------------";
	gotoxy(8, 9);
	cout << "| G A M E O V E R |";
	gotoxy(8, 10);
	cout << " " << playTime << " sec";
	gotoxy(8, 11);
	cout << "-------------------";
	gotoxy(4, 12);
	cout << "press SPACE! to return to main menu";
	gotoxy(2, 18);
	cout << "*******************************************" <<endl;
}

void DrawUserCursor(int& y)
{
	if (y <= 0)
	{
		y = 0;
	}
	else if (y >= 2)
	{
		y = 2;
	}

	gotoxy(9, 8 + y);
	cout << ">";
}

//-----------Func-----------------
MENU ReadyGame()
{
	int y = 0;
	int input = 0;
	while (true)
	{
		DrawReadyGame();
		DrawUserCursor(y);
		input = _getch();
		//→←↑↓
		if (input == MAGIC_KEY1)
		{
			input = _getch();
			switch (_getch())
			{
			case UP:
				--y;
				break;
			case DOWN:
				++y;
				break;
			}
		}
		else if (input == SPACE)
		{
			switch (y)
			{
			case 0:
				return GAMESTART;
			case 1:
				return INFO;
			case 2:
				return QUIT;
			}
		}
	}
}

void InfoGame()
{
	int input = 0;
	DrawInfoGame();
	while (true)
	{
		input = _getch();
		if (input == SPACE) return;
	}
}

void SetQuestion(vector<int>& questionVec, int level)
{
	if (level > MAX_LEVEL)
	{
		level = MAX_LEVEL;
	}

	int num = 0;
	srand((unsigned int)time(NULL));
	for (int i = 0; i < level; ++i)	//alphabet의 개수 (문제 난이도)
	{
		num = rand() % KEY_NUM;	//alphabet 종류.
		
		if(num<26) {
			questionVec.push_back(num+65);
		}
		else {
			questionVec.push_back(num+71);
		}
	}
}

void VectorToString(const vector<int> v, string& str)
{
	for (int i = 0; i < static_cast<int>(v.size()); ++i)
	{

		str += v[i];
		str += " ";
	}
}

bool CheckAnswer(const vector<int> questionVec, const vector<int> answerVec)
{
	//숫자의 배열이 같다.
	//길이 체크
	if (questionVec.size() != answerVec.size())
	{
		//길이 다르네
		return false;
	}

	//내용물 체크
	for (int i = 0; i < static_cast<int>(questionVec.size()); ++i)
	{
		if (questionVec[i] != answerVec[i])
		{
			//다른게 있네.
			return false;
		}
	}
	return true;
}

void StartGame()
{
	int life = LIFE;
	int score = 0;
	//재생했을때 현재시간.
	clock_t startTime, endTime;
	startTime = clock();

	//→←↑↓, d a w s
	//문제
	vector<int> questionVec;
	string questionStr = "";
	//답안지
	vector<int> answerVec;
	string answerStr = "";

	int firstInput = 0;
	int secondInput = 0;
	while (true)
	{
		int level = (score / 30) + 1;

		//문제를 세팅
		SetQuestion(questionVec, level);
		//문제를 보여주기.
		VectorToString(questionVec, questionStr);
		while (true)
		{
			//1문제를 가지고 문제를 푼다.
			DrawStartGame(life, score, questionStr, answerStr);

			if (life == 0)
			{
				//게임 오버일때 현재시간
				endTime = clock();
				int playTime = static_cast<int>((endTime - startTime) / CLOCKS_PER_SEC);

				DrawGameOver(playTime);
				int input = 0;
				while (true)
				{
					input = _getch();
					if (input == SPACE) return;
				}

				return;
			}

			//정답 하나씩 입력.
			
			while(true) {
				firstInput = _getch();
				if (firstInput == MAGIC_KEY1) {
					firstInput = _getch();
					firstInput = _getch();
				}
				else {
					break;
				}
			}
			if (((firstInput>64)&&(firstInput<91))||((firstInput>96)&&(firstInput<123))) {
				answerVec.push_back(firstInput);
				answerStr += firstInput;
				answerStr += " ";
			}
			else if (firstInput == SPACE) {
				if (CheckAnswer(questionVec, answerVec)) {
					score += 10;
				}
				else {
					--life;
					score -= 5;
					if (score < 0) {
						score = 0;
					}
				}
				questionVec.clear();
				questionStr = "";
                answerVec.clear();
                answerStr = "";
				break;
			}
		}
	}
}

int main(void)
{
	while (true)
	{
		switch (ReadyGame())
		{
		case GAMESTART:
			StartGame();
			break;
		case INFO:
			InfoGame();
			break;
		case QUIT:
			return 0;
		}
	}
	return 0;
}

