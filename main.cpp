#include <iostream>
#include <vector>
#include <regex>
#include <limits>
#include <cmath>
#include "StringHelper.h"
#include "mines.h"
namespace sh = StringHelper;
using namespace std;

struct Coordinate{
	int x = -1;
	int y = -1;
	bool flag = false;
};

bool promptForBoard(int &c, int &r, int &m, int &t);
bool stringToCoords(string coord, Coordinate &coordRef);

int main(int argc, char *argv[]){
	int c, r, m, t, response;
	bool exit = false;
	string input, clear = "\033[2J\033[1;1H\n";
	Coordinate tempCoord;

	init:
	cout << clear;


	do{
		c = 0;
		r = 0;
		m = 0;
		t = 0;
	}while(!promptForBoard(c, r, m, t));

	cout << clear;

	Board myBoard = Board(c, r, m);
	myBoard.buildBoard();
	myBoard.showBoard();
	cout << "\nWhere would you like to click?\n";

	do{
		cin >> input;
		if(input == "exit"){
			exit = true;
		}
		else{
			if(stringToCoords(input, tempCoord)){
				response = myBoard.click(tempCoord.x, tempCoord.y, tempCoord.flag);
			
				switch(response){
					case 0:
						cout << clear;
						myBoard.showBoard();
						cout << "\nWhere would you like to click?\n";
						break;

					case 1:
						cout << clear;
						myBoard.showBoard();
						cout << "\nThat was a mine! X.X" << endl;
						break;

					case 2:
						cout << "\nPlease enter coordinates within the board range." << endl;
						break;
				}
			}
			else{
				cout << "\nPlease enter coordinates in the manner of: x,y\nOr to flag a coordinate: !x,y" << endl;
			}
		}

	}while(!exit);

	cout << "\nExiting..." << endl;
	myBoard.garbageDump();
	return 0;
}

bool promptForBoard(int &c, int &r, int &m, int &t){
	int tempIn;

	while(c == 0){
		cout << "\nHow many columns would you like the board to be? MIN: 2; MAX: 99\n";
		cin >> tempIn;
		if(!cin){
			cout << "\nPlease enter a number from 2 to 99.\n";
		    cin.clear();
		    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if((tempIn > 1) && (tempIn < 100)){
			c = tempIn;
		}
		else{
			cout << "\nPlease enter a number from 2 to 99.\n";
		}
	}

	while(r == 0){
		cout << "\nHow many rows would you like the board to be? MIN: 2; MAX: 99\n";
		cin >> tempIn;
		if(!cin){
			cout << "\nPlease enter a number from 2 to 99.\n";
		    cin.clear();
		    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if((tempIn > 1) && (tempIn < 100)){
			r = tempIn;

		}
		else{
			cout << "\nPlease enter a number from 2 to 99.\n";
		}
	}

	t = c * r;

	while(m == 0){
		cout << "\nHow many mines would you like the board to have? MIN: 2; MAX: " << (t - 1) << "\n";
		cin >> tempIn;
		if(!cin){
			cout << "\nPlease enter a number from 2 to " << (t - 1) << ".\n";
		    cin.clear();
		    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		}
		else if((tempIn > 1) && (tempIn < t)){
			m = tempIn;
		}
		else{
			cout << "\nPlease enter a number from 2 to " << (t - 1) << ".\n";
		}
	}

	cout << "\nYou chose a board that is " << t << " tiles large with " << floor(((double)m / (double)t) * 100) << "% of them being mines.\n\nDo you wish to continue with this board? [Y/N]\n";

	string tempString;
	cin >> tempString;

	return (sh::strToLower(tempString) == "y");
}

bool stringToCoords(string coord, Coordinate &coordRef){
	size_t index = coord.find(","); 									//check input is in the form of a coordinate

	if (index != string::npos){											//comma is found
		
		index = coord.find("!");										//check if player is flagging
		if(index == 0){													//`!` found; user is flagging
			coord.erase(0,1);
			coordRef.flag = true;
		}

		vector<string> coordinates = sh::split(coord, ",");
		if(regex_match(coordinates[0], regex("[0-9]+"))  &&  regex_match(coordinates[1], regex("[0-9]+"))) {
			coordRef.x = stoi(coordinates[0]);
			coordRef.y = stoi(coordinates[1]);
		}
		else{
			return false;
		}
	}
	else{
		return false;
	}

	return true;
}
