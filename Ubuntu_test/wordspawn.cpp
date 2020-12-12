#include <iostream>
#include <string>
using namespace std;

string LetterList(int a){
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
		case 18: return "nonsense"; break;
		case 19: return "stuff"; break;
		case 20: return "ignore"; break;
		case 21: return "overgrown"; break;
		case 22: return "weed"; break;
		case 23: return "rectangle"; break;
		case 24: return "patch"; break;
		case 25: return "porch"; break;
		case 26: return "pitcher"; break;
		case 27: return "sputter"; break;
		case 28: return "curiosity"; break;
		case 29: return "reply"; break;
		case 30: return "miserable"; break;
		case 31: return "pinky"; break;
		case 32: return "pretend"; break;
		case 33: return "delight"; break;
		case 34: return "humiliate"; break;
		case 35: return "blead"; break;
		case 36: return "monkey"; break;
		case 37: return "criminal"; break;
		case 38: return "shatter"; break;
		case 39: return "caboose"; break;
		case 40: return "consequence"; break;
		case 41: return "responsibility"; break;
		case 42: return "punish"; break;
		case 43: return "assume"; break;
		case 44: return "immediately"; break;
		case 45; return "memorize"; break;
		case 46: return "disapproval"; break;
		case 47: return "lack"; break;
		case 48: return "path"; break;
		case 49: return "impress"; break;
		case 50: return "pop"; break;
		case 51: return "definite"; break;
		case 52: return "recite"; break;
		case 53: return "spacey"; break;
		case 54: return "freckle"; break;
		case 55: return "daydream"; break;
		case 56: return "meadow"; break;
		case 57: return "count"; break;
		case 58: return "forescore"; break;
		case 59: return "command"; break;
		case 60: return "stare"; break;
		case 61: return "bloody"; break;
		case 62: return "quiver"; break;
		case 63: return "battlefield"; break;
		case 64: return "rhyme"; break;
		case 65: return "bloody"; break;
		case 66: return "wound"; break;
		case 67: return "horrible"; break;
		case 68: return "dignity"; break;
		case 69: return "befit"; break;
		case 70: return "continent"; break;
		case 71: return "befit"; break;
		case 72: return "flash"; break;
		case 73: return "conceive"; break;
		case 74: return "recess"; break;
		case 75: return "barely"; break;
		case 76: return "planter"; break;
		case 77: return "swipe"; break;
		case 78: return "warn"; break;
		case 79: return "ysterious"; break;
		case 80: return "whisper"; break;
		case 81: return "draft"; break;
		case 82: return "slip"; break;
		case 83: return "nail"; break;
		case 84: return "fascinate"; break;
		case 85: return "pound"; break;
		case 86: return "cautious"; break;
		case 87: return "approach"; break;
		case 88: return "maneuver"; break;
		case 89: return "vertical"; break;
		case 90: return "blade"; break;
		case 91: return "stem"; break;
		case 92: return "sheet"; break;
		case 93: return "arve"; break;
		case 94: return "bang"; break;
		case 95: return "measly"; break;
		case 96: return "nod"; break;
		case 97: return "ignore"; break;
		case 98: return "cracker"; break;
		case 99: return "rabies"; break;
		case 100: return"dare"; break;



		default: return "default"; break;
	}
}

string RandLetter(){
	return LetterList(rand()%100);
}
