#include<iostream>
#include"getch.h"
#include<vector>
#include<string>
#include<ctime>
#include<queue>
#include<cstring>
#include "draw.h"
#include "wordSpawn.h"
#include "sentenceSpawn.h"
#pragma comment(lib, "winmm.lib")
using namespace std;

#include <curses.h>


#define MAGIC_KEY1 27  //방향키를 입력받기 위한 설정
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
enum SENTENCEMENU
{
	POEM_A = 22,
	POEM_B = 45,
	POEM_C = 49,
	BACKTOMENU=50
};

enum KEYBOARD
{
	UP = 65,
	LEFT = 68,
	RIGHT = 67,
	DOWN = 66
};

queue<string> wrongAnswerNote; // 오답노트를 위한 queue 구조 생성
Draw draw; // 화면 출력 객체 생성

//-----------Func-----------------
MENU ReadyGame()
{
	int cursor=0;
	int input = 0;
	while (true)
	{
		draw.DrawReadyGame();
		draw.DrawUserCursor(cursor);
		input = Getch();

		if (input == MAGIC_KEY1) // input이 화살표라면 진입
		{
			input = Getch();
			switch (Getch())
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
		input=Getch();
		if(input == MAGIC_KEY1){
			input = Getch();
			switch(Getch()){
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
int sentenceFlag=0;
SENTENCEMENU SentenceSet(){
	int cursor=0;
	int input = 0;
	while(true){
		draw.DrawSentenceSet();
		draw.DrawSentencesetCursor(cursor);
		input=Getch();
		if(input == MAGIC_KEY1){
			input = Getch();
			switch(Getch()){
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
					sentenceFlag=POEM_A;
					return POEM_A;
				case 1:
					sentenceFlag=POEM_B;
					return POEM_B;
				case 2:
					sentenceFlag=POEM_C;
					return POEM_C;
				case 3:
					return BACKTOMENU;
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
		input = Getch();
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



void VectorToString(const vector<int> v, string& str)
{
	str ="";
	for (int i = 0; i < static_cast<int>(v.size()); ++i)
	{

		str += v[i];
		str += "";
	}
}


void StartGame()
{
	int life = LIFE;
	int score = 0;
	int sentenceFlow=1; // 시 출력시 차례대로 출력하기 위한 제어변수
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
				questionStr =  RandWord();
				break;
			case SENTENCE:
				if(sentenceFlag==POEM_A){
					questionStr = PoemAList(sentenceFlow++);
				}else if(sentenceFlag==POEM_B){
					questionStr = PoemBList(sentenceFlow++);
				}else if(sentenceFlag==POEM_C){
					questionStr = PoemCList(sentenceFlow++);
				}
				if(questionStr== "Default"){
					draw.DrawGameWin();
					int input = 0;
					while (true)
					{
						input = Getch();
						if (input == ENTER) return;
					}

					return;
				}
				break;
			case WRONGANSWER:
				if(wrongAnswerNote.empty()==true){
					draw.DrawGameWin();
					int input = 0;
					while (true)
					{
						input = Getch();
						if (input == ENTER) return;
					}

					return;
				}
				else{
					questionStr = wrongAnswerNote.front();
					wrongAnswerNote.pop();
				}
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
					input = Getch();
					if (input == ENTER) return;
				}

				return;
			}

			//정답 하나씩 입력.

			while(true) {
				firstInput = Getch();
				if (firstInput == MAGIC_KEY1) {
					firstInput = Getch();
					firstInput = Getch();
				}
				else {
					break;
				}
			}
			// 알파벳, 기호, 공백 등 입력 처리
			if (((firstInput>64)&&(firstInput<91))||((firstInput>96)&&(firstInput<123))||(firstInput==SPACE)||(firstInput==46)||(firstInput==44)||(firstInput==33)||(firstInput==63)||(firstInput==39)) {
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
					wrongAnswerNote.push(questionStr);
					if(gameFlag!=WRONGANSWER){
						--life;
						score -= 5;
						if (score < 0) {
							score = 0;
						}
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

int main(int argc, char* argv[])
{
	srand((unsigned int)time(0));
	
	if(strcmp(argv[1],"word")==0){
		printf("%s",argv[1]);
		gameFlag = WORD;
		StartGame();
		return 0;
	}else if(argv[1]=="alphabet"){
		gameFlag = ALPHABET;
		StartGame();
	}else{
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
							switch(SentenceSet()){
								case POEM_A:
									StartGame();
									break;
								case POEM_B:
									StartGame();
									break;
								case POEM_C:
									StartGame();
									break;
								case BACKTOMENU:
									break;
							}
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
	}
	return 0;
}

