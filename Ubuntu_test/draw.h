#include <iostream>
#include <string>
#include <cstdio>
using namespace std;
class Draw{
	private:
	void gotoxy(int x, int y) {
			printf("\033[%d;%df", y, x);
			fflush(stdout);
		}
	public:
	void DrawReadyGame(){
		system("clear");
		gotoxy(5, 2);
		cout << "*************************************";
		gotoxy(5, 3);
		cout << "*        English Typing Test        *";
		gotoxy(5, 4);
		cout << "*************************************";
		gotoxy(10, 8);
		cout << "GameStart";
		gotoxy(10, 9);
		cout << "GameInfo";
		gotoxy(10, 10);
		cout << "Quit" << endl;
	}
	void DrawGameSet(){
		system("clear");
		gotoxy(5,2);
		cout << "*************************************";
		gotoxy(5,3);
		cout << "*           Select Game             *";
		gotoxy(5,4);
		cout << "*************************************";
		gotoxy(10,8);
		cout << "Alphabet Game";
		gotoxy(10,9);
		cout << "Word Game";
		gotoxy(10,10);
		cout << "Sentence Game";
		gotoxy(10,11);
		cout << "Check Wrong Answers";
		gotoxy(10,12);
		cout << "Back";

	}
	void DrawSentenceSet(){
		system("clear");
		gotoxy(5,2);
		cout << "*************************************";
		gotoxy(5,3);
		cout << "*           Select Poem             *";
		gotoxy(5,4);
		cout << "*************************************";
		gotoxy(10,8);
		cout << "The Road Not Taken";
		gotoxy(10,9);
		cout << "Still I Rise";
		gotoxy(10,10);
		cout << "Daddy";
		gotoxy(10,11);
		cout << "Back";

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
		cout << "press ENTER! to return to main menu" <<endl;
	}

	void DrawStartGame(const int life, const int score, const string questionStr, const string answerStr)
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
			cout << "press ENTER! after input done.";
			gotoxy(2, 18);
			cout << "*******************************************" << endl;
		}

	void DrawGameOver()
		{
			system("clear");
			gotoxy(2, 1);
			cout << "*******************************************";
			gotoxy(8, 8);
			cout << "-------------------";
			gotoxy(8, 9);
			cout << "| G A M E O V E R |";
			gotoxy(8, 10);
			cout << "-------------------";
			gotoxy(4, 12);
			cout << "press ENTER! to return to main menu";
			gotoxy(2, 18);
			cout << "*******************************************" <<endl;
		}
	void DrawGameWin(){
			system("clear");
			gotoxy(2, 1);
			cout << "*******************************************";
			gotoxy(8, 8);
			cout << "-------------------";
			gotoxy(8, 9);
			cout << "| Y O U   W I N ! |";
			gotoxy(8, 10);
			cout << "-------------------";
			gotoxy(4, 12);
			cout << "press ENTER! to return to main menu";
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
	void DrawGamesetCursor(int& y){
		if(y<=0){
			y=0;
		}
		else if( y>=4){
			y=4;
		}
		gotoxy(9,8+y);
		cout<< ">";
	}
	void DrawSentencesetCursor(int& y){
		if(y<=0){
			y=0;
		}
		else if( y>=3){
			y=3;
		}
		gotoxy(9,8+y);
		cout<< ">";
	}
};


