#include<iostream>
#include"getch.h"
#include<vector>
#include<string>
#include<ctime>
#include "Draw.h"
#include "letterSpawn.h"
#pragma comment(lib, "winmm.lib")
using namespace std;

#include <curses.h>

#define MAGIC_KEY1 27
#define MAGIC_KEY2 91
#define ENTER 10
#define KEY_NUM 52
#define LIFE 3
#define MAX_LEVEL 11
#define BACKSPACE 127
#define SPACE 32

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
enum GAMEMENU
{
	ALPHABET = 0,
	WORD,
	SENTENCE,
	WRONGANSWER,
	BACK
};

enum KEYBOARD
{
	UP = 65,
	LEFT = 68,
	RIGHT = 67,
	DOWN = 66
};

void SetConsoleView()
{
	//	system("mode con:cols=50 lines=20");
	//	system("title DanceDance");
}

Draw draw;
//-----------Func-----------------
MENU ReadyGame()
{
	int cursor=0;
	int input = 0;
	while (true)
	{
		draw.DrawReadyGame();
		draw.DrawUserCursor(cursor);
		input = _getch();
		//→←↑↓
		if (input == MAGIC_KEY1)
		{
			input = _getch();
			switch (_getch())
			{
			case UP:
				--cursor;
				break;
			case DOWN:
				++cursor;
				break;
			}
		}
		else if (input == ENTER)
		{
			switch (cursor)
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
int gameFlag=0;
GAMEMENU GameSet(){
	int cursor=0;
	int input = 0;
	while(true){
		draw.DrawGameSet();
		draw.DrawGamesetCursor(cursor);
		input=_getch();
		if(input == MAGIC_KEY1){
			input = _getch();
			switch(_getch()){
				case UP:
					--cursor;
					break;
				case DOWN:
					++cursor;
					break;
			}
		}
		else if(input == ENTER){
			switch(cursor){
				case 0:
					gameFlag=ALPHABET;
					return ALPHABET;
				case 1:
					gameFlag=WORD;
					return WORD;
				case 2:
					gameFlag=SENTENCE;
					return SENTENCE;
				case 3:
					gameFlag=WRONGANSWER;
					return WRONGANSWER;
				case 4:
					return BACK;
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
		if (input == ENTER) return;
	}
}

void SetQuestion(vector<int>& questionVec, int level)
{
	if (level > MAX_LEVEL)
	{
		level = MAX_LEVEL;
	}

	int num = 0;
	
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
void SetQuestion(vector<int>& questionVec, int level,int wordFlag)
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
	str ="";
	for (int i = 0; i < static_cast<int>(v.size()); ++i)
	{

		str += v[i];
		str += "";
	}
}

bool CheckAnswer(string questionStr, string answerStr)
{
	//숫자의 배열이 같다.
	//길이 체크
	if (questionStr.size() != answerStr.size())
	{
		//길이 다르네
		return false;
	}

	//내용물 체크
	for (int i = 0; i < static_cast<int>(questionStr.size()); ++i)
	{
		if (questionStr[i] != answerStr[i])
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

		switch(gameFlag){
			case ALPHABET:
				SetQuestion(questionVec, level);
				VectorToString(questionVec, questionStr);
			break;
			case WORD:
				questionStr =  randletter();
				break;
			case SENTENCE:
				questionStr = randletter();
				break;
			case WRONGANSWER:
				questionStr = randletter();
				break;
			default:
				SetQuestion(questionVec, level);
				VectorToString(questionVec, questionStr);
		}
		while (true)
		{
			//1문제를 가지고 문제를 푼다.
			draw.DrawStartGame(life, score, questionStr, answerStr);

			if (life == 0)
			{
				
				draw.DrawGameOver();
				int input = 0;
				while (true)
				{
					input = _getch();
					if (input == ENTER) return;
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
			if (((firstInput>64)&&(firstInput<91))||((firstInput>96)&&(firstInput<123))||(firstInput==SPACE)) {
				answerVec.push_back(firstInput);
				answerStr += firstInput;
				answerStr += "";
			}
			else if(firstInput == BACKSPACE){
				answerVec.pop_back();
				VectorToString(answerVec,answerStr);
				
			}
			else if (firstInput == ENTER) {
				if (questionStr==answerStr) {
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
			switch(GameSet()){
				case ALPHABET:
					StartGame();
					break;
				case WORD:
					StartGame();
					break;
				case SENTENCE:
					StartGame();
					break;
				case WRONGANSWER:
					StartGame();
					break;
				case BACK:
					break;
			}
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

