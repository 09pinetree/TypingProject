#include <iostream>
#include <string>
using namespace std;

string letterlist(int a){
	switch(a){
		case 0: return "whisper"; break;
		case 1: return "weird"; break;
		case 2: return "crouch"; break;
		case 3: return "bush"; break;
		case 4: return "rust"; break;
		case 5: return "story"; break;
		case 6: return "floppy"; break;
		case 7: return "cane"; break;
		case 8: return "lap"; break;
		case 9: return "carve"; break;
		case 10: return "wrap"; break;
		case 11: return "embed"; break;
		case 12: return "signal"; break;
		case 13: return "grab"; break;
		case 14: return "nod"; break;
		case 15: return "warn"; break;
		case 16: return "snicker"; break;
		case 17: return "abrupt"; break;

		default: return "default"; break;
	}
}

string randletter(){
	return letterlist(rand()%18);
}
