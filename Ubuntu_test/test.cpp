#include<iostream>
#include"getch.h"
#include<vector>
#include<string>
#include<ctime>
#include "Draw.h"
#pragma comment(lib, "winmm.lib")
using namespace std;

//By. BlockDMask.
//[PART1] make screen, change screen, input.
//[PART2] input&output, question, life.
//[PART3] setting level, play music, play time

//#include <stdio.h>
#include <curses.h>
//#define gotoxy(x,y) wmove(stdscr,y-1,x-1)

#define MAGIC_KEY1 27
#define MAGIC_KEY2 91
#define SPACE 32
#define KEY_NUM 4
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
/*void gotoxy(int x, int y)
{
	COORD Pos;
	Pos.X = 2 * x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), Pos);
}*/
void SetConsoleView()
{
	//	system("mode con:cols=50 lines=20");
	//	system("title DanceDance");
}

Draw draw;
//-----------Func-----------------
MENU ReadyGame()
{
	int y = 0;
	int input = 0;
	while (true)
	{
		draw.DrawReadyGame();
		draw.DrawUserCursor(y);
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
	draw.DrawInfoGame();
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
	for (int i = 0; i < level; ++i)	//화살표의 개수 (문제 난이도)
	{
		num = rand() % KEY_NUM;	//화살표 종류.
		switch (num)
		{
		case 0:
			questionVec.push_back(UP);
			break;
		case 1:
			questionVec.push_back(RIGHT);
			break;
		case 2:
			questionVec.push_back(LEFT);
			break;
		case 3:
			questionVec.push_back(DOWN);
			break;
		}
	}
}

void VectorToString(const vector<int> v, string& str)
{
	for (int i = 0; i < static_cast<int>(v.size()); ++i)
	{
		switch (v[i])
		{
		case UP:
			str += "↑ ";
			break;
		case DOWN:
			str += "↓ ";
			break;
		case LEFT:
			str += "← ";
			break;
		case RIGHT:
			str += "→ ";
			break;
		}
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
			draw.DrawStartGame(life, score, questionStr, answerStr);

			if (life == 0)
			{
				//게임 오버일때 현재시간
				endTime = clock();
				int playTime = static_cast<int>((endTime - startTime) / CLOCKS_PER_SEC);

				draw.DrawGameOver(playTime);
				int input = 0;
				while (true)
				{
					input = _getch();
					if (input == SPACE) return;
				}

				return;
			}

			//정답 하나씩 입력.
			firstInput = _getch();
			if (firstInput == MAGIC_KEY1)
			{
				secondInput = _getch();
				secondInput = _getch();
				answerVec.push_back(secondInput);
				switch (secondInput)
				{
				case UP:
					answerStr += "↑ ";
					break;
				case DOWN:
					answerStr += "↓ ";
					break;
				case LEFT:
					answerStr += "← ";
					break;
				case RIGHT:
					answerStr += "→ ";
					break;
				}
			}
			else if (firstInput == SPACE)
			{
				//답안 제출
				//답안 확인
				if (CheckAnswer(questionVec, answerVec))
				{
					score += 10;
				}
				else
				{
					//틀렸다.
					--life;
					score -= 5;
					if (score < 0)
					{
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
	SetConsoleView();
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

