#include <iostream>
#include <string>
#include "Draw.h"
#include "getch.h"
#include <cstdio>
using namespace std;

	void Draw::gotoxy(int x, int y) {
			printf("\033[%d;%df", y, x);
			fflush(stdout);
		}
	void Draw::DrawReadyGame(){
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
	void Draw::DrawInfoGame()
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

	void Draw::DrawStartGame(const int life, const int score, const string questionStr, const string answerStr)
		{
			system("clear");
			gotoxy(2, 1);
			cout << "*******************************************";
			gotoxy(4, 3);
			cout << "Life : " << life << " / " << "3";
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

	void Draw::DrawGameOver(const int playTime)
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

	void Draw::DrawUserCursor(int& y)
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



