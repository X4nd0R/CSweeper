#include <iostream>
#include <ctime>
#include "mines.h"

Board::Board(int c, int r, int m){
    rows = r;
    fields = c;
    mines = m;
}

int Board::getRows(){
    return rows;
}

int Board::getColumns(){
    return fields;
}

int Board::getMines(){
    return mines;
}

void Board::buildBoard(){
	int row = 0, field = 0, cnt = 0;
    board = new int*[rows];
    clicked = new int*[rows];
    flagged = new int*[rows];
    for(row = 0; row < rows; row++){
    	board[row] = new int[fields];
    	clicked[row] = new int[fields];
    	flagged[row] = new int[fields];
		for(field = 0; field < fields; field++){
			board[row][field] = 0;
			clicked[row][field] = 0;
			flagged[row][field] = 0;
		}
    }

    std::srand(std::time(nullptr));
    while(cnt < mines){
    	row = std::rand() % rows;
    	field = std::rand() % fields;
    	if(!board[row][field]){
    		board[row][field] = 1;
    		cnt++;
    	}
    }
}

void Board::showBoard(){
	int row = 0;
	int field = 0;
	std::string outputString = "   | " + std::to_string(field + 1) + " ";

	for(field = 1; field < fields; field++){
		outputString += "| " + std::to_string(field + 1);
		if(field < 9){
			outputString += " ";
		}
	}
	outputString += "|";
	std::cout << outputString << std::endl;

	for(row = 0; row < rows; row++){
		outputString = "---";
		for(field = 0; field < fields; field++){
			outputString += "----";
		}
		outputString += "---";
		std::cout << outputString << std::endl;

		outputString = " ";
		if(row < 9){
			outputString += " ";
		}
		outputString += std::to_string(row + 1);

		for(field = 0; field < fields; field++){
			outputString += "| ";
			if(clicked[row][field]){
				if(board[row][field]){
					outputString += "0";
				}
				else{
					outputString += "-";
				}
			}
			else{
				if(flagged[row][field]){
					outputString += "!";
				}
				else{
					outputString += "X";
				}
			}
			outputString += " ";

		}
		outputString += "| " + std::to_string(row + 1);
		std::cout << outputString << std::endl;
	}

	outputString = "---";
	for(field = 0; field < fields; field++){
		outputString += "----";
	}
	outputString += "---";
	std::cout << outputString << std::endl;

	field = 0;
	outputString = "   | " + std::to_string(field + 1) + " ";

	for(field = 1; field < fields; field++){
		outputString += "| " + std::to_string(field + 1);
		if(field < 9){
			outputString += " ";
		}
	}
	outputString += "|";
	std::cout << outputString << std::endl;
}

/* Responses:
 * 0: Success/No mine
 * 1: Success/Mine
 * 2: Out of range
 */
int Board::click(int field, int row, bool flag){
	field--;
	row--;
	if(row < rows  &&  row >= 0  &&  field < fields  &&  field >= 0){
		clicked[row][field] = 1;
		if(!board[row][field]){
			flagged[row][field] = flag;
			return 0;
		}
		else{
			return 1;
		}
	}
	else{
		return 2;
	}
}

void Board::garbageDump(){
	if(board != nullptr){
		for(int i = 0; i < fields; i++){
			delete[] board[i];
		}
		delete[] board;
		board = nullptr;
	}

	if(clicked != nullptr){
		for(int i = 0; i < fields; i++){
			delete[] clicked[i];
		}
		delete[] clicked;
		clicked = nullptr;
	}

	if(flagged != nullptr){
		for(int i = 0; i < fields; i++){
			delete[] flagged[i];
		}
		delete[] flagged;
		flagged = nullptr;
	}
}
