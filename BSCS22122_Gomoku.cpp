#include<iostream>
#include<time.h>
#include<Windows.h>
#include<conio.h>
#include <fstream>
using namespace std;

const int capacity = 19;
char computer = 1;
char human = 0;

void Init2(char B[][capacity], int& Dim, int& NOP, int& WinC, char sym[], string PNames[],int &turn) {

		NOP = 2;
		cout << "Dim: ";
		cin >> Dim;
		cout << "Enter Your Name: ";
		cin >> PNames[0];
		cout << "Enter symbol: \n";
		cin >> sym[0];
		PNames[1] = "computer";
		sym[1] = 'O';
		for (int i = 0; i < Dim; i++) {
			for (int j = 0; j < Dim; j++) {
				B[i][j] = '-';
			}
		}
		cout << "Win Condition: ";
		cin >> WinC;
		srand(time(NULL));
		turn = rand() % NOP;
	
	
}
//functions
void Init(char B[][capacity], int& Dim, int& NOP, int& WinC, char sym[], string PNames[], int& turn){
	cout << "Dim: ";
	cin >> Dim;
	cout << "NOP: ";
	cin >> NOP;
	for (int i = 0; i < Dim; i++){
		for (int j = 0; j < Dim; j++){
			B[i][j] = '-';
		}
	}
	for (int i = 0; i < NOP; i++){
		cout << "Player " << i + 1 << " Name: ";
		cin >> PNames[i];
		cout << "Player " << i + 1 << " Symbol: ";
		cin >> sym[i];
	}
	cout << "Win Condition: ";
	cin >> WinC;
	srand(time(NULL));
	turn = rand() % NOP;
}
void BoardPrint(char B[][capacity], int Dim){
	for (int i = 0; i < Dim; i++){
		for (int j = 0; j < Dim; j++){
			cout << B[i][j] << " ";
		}
		cout << endl;
	}
}
void BoardPrint2(char B[][capacity], int Dim) {
	system("cls");
	for (int i = 0; i < Dim; i++) {
		for (int j = 0; j < Dim; j++) {
			cout << B[i][j] << " ";
		}
		cout << endl;
	}
}
void TurnMsg(string name){
	cout << name << "'s Turn: " << endl;
}
void SelectPosition(int Dim, int& r, int& c){
	cout << "Select Row(1..." << Dim << "): ";
	cin >> r;
	r = r - 1;
	cout << "Select Column(1..." << Dim << "): ";
	cin >> c;
	c = c - 1;
}
void PlaceMove(char B[][capacity], int r, int c, char sym){
	B[r][c] = sym;
}
void TurnChange(int& turn, int NOP){
	turn = (turn + 1) % NOP;
}
bool Valid(char B[][capacity], int Dim, int r, int c) {
	if (B[r][c] != '-') {
		return false;
	}
	if (r > Dim || c > Dim) {
		return false;
	}
	else {
		return true;
	}
}
bool Win_Horizontal(char B[][capacity], int Dim, char PSym, int WC, int ri, int ci)
{
	if (ci + WC-1 >= Dim){
		return false;
	}
	for (int i = 0; i < WC; i++){
		if (B[ri][ci + i] != PSym){
			return false;
		}
	}
	return true;
}
bool Win_Vertical(char B[][capacity], int Dim, char PSym, int WC, int ri, int ci){
	if (ri + WC-1 >= Dim){
		return false;
	}
	for (int i = 0; i < WC; i++){
		if (B[ri + i][ci] != PSym){
			return false;
		}
	}
	return true;
}
bool Win_Left2Right(char B[][capacity], int Dim, char PSym, int WC, int ri, int ci){
	if (ci + WC - 1 >= Dim || ri + WC - 1 >= Dim){
		return false;
	}
	for (int i = 0; i < WC; i++){
		if (B[ri + i][ci + i] != PSym){
			return false;
		}
	}
	return true;
}
bool Win_Right2Left(char B[][capacity], int Dim, char PSym, int WC, int ri, int ci){
	if (ci + WC - 2 >  Dim || ri+WC - 2 > Dim){
		return false;
	}
	for (int i = 0; i < WC; i++){
		if (B[ri + i][ci - i] != PSym){
			return false;
		}
	}
	return true;
}
bool Do_I_Win_Here(char B[][capacity], int Dim, char PSym, int WC, int ri, int ci){

	if (Win_Horizontal(B, Dim, PSym, WC, ri, ci) == true){
		return true;
	}
	if (Win_Vertical(B, Dim, PSym, WC, ri, ci) == true){
		return true;
	}
	if (Win_Left2Right(B, Dim, PSym, WC, ri, ci) == true){
		return true;
	}
	if (Win_Right2Left(B, Dim, PSym, WC, ri, ci) == true){
		return true;
	}
	
	return false;
}
bool IsWin(char B[][capacity], int Dim, char Psym, int WinC) {
	for (int i = 0; i < Dim; i++) {
		for (int j = 0; j < Dim; j++) {
			if (Do_I_Win_Here(B, Dim, Psym, WinC, i, j)) {
				return true;
			}
		}
	}
	return false;
}
bool IsDraw(char B[][capacity], int Dim) {
	for (int ri = 0; ri < Dim; ri++) {
		for (int ci = 0; ci < Dim; ci++) {
			if (B[ri][ci] == '-') {
				return false;
			}
		}
	}
	return true;
}
void ComputerPoisition(char B[][capacity], int Dim, int& r, int& c, char Sym[], int WC) {

	for (int win = WC; win >= 0; win--) {
		for (int i = 0; i < Dim; i++) {
			for (int j = 0; j < Dim; j++) {
				r = i;
				c = j;
				if (Valid(B, Dim, r, c)) {
					B[i][j] = Sym[human];
					if (IsWin(B, Dim, Sym[human], win)) {
						B[i][j] = '-';

						return;
					}

					B[i][j] = '-';
				}
			}
		}
		for (int i = 0; i < Dim; i++) {
			for (int j = 0; j < Dim; j++) {
				r = i;
				c = j;
				if (Valid(B, Dim, r, c)) {
					B[i][j] = Sym[computer];
					if (IsWin(B, Dim, Sym[computer], win)) {
						B[i][j] = '-';
						return;
					}
					B[i][j] = '-';
				}
			}
		}
	}
	do {
		r = rand() % Dim;
		c = rand() % Dim;
	} while (!Valid(B,Dim,r,c));
	
}

//main
void mainHUMAN(){

	int Dim, NOP, r, c, WinC, WinnerC = 0;
	bool GameOver = false;
	int winner = -1;
	char B[capacity][capacity];
	char Sym[capacity];
	string PNames[capacity];
	int Turn;
	
	Init(B, Dim, NOP, WinC, Sym, PNames, Turn);
	BoardPrint(B, Dim);
	bool isValid = false;
	do {
		TurnMsg(PNames[Turn]);
		do {
			SelectPosition(Dim, r, c);
			if (isValid = (!Valid(B, Dim, r, c))) {
				cout << "Error.....Out of bound!\nEnter Again: " << endl;
			}
		}
		while (isValid);
		PlaceMove(B, r, c, Sym[Turn]);
		system("cls");
		BoardPrint(B, Dim);
		GameOver = IsWin(B, Dim, Sym[Turn], WinC);
		if (GameOver == true) {
			winner = Turn;
		}
		if (GameOver == false) {
			GameOver = IsDraw(B, Dim);
		}
		if (GameOver == false) {
			TurnChange(Turn, NOP);
		}
	} 
	while (!GameOver);
	if (winner == -1) {
		cout << "The Game is Draw!" << endl;
	}
	else {
		cout << PNames[Turn] << " Has Won the Match!" << endl;
	}
}
void mainAIvsHuman() {
	int Dim, NOP, r, c, WinC, WinnerC = 0;
	bool GameOver = false;
	int winner = -1;
	char B[capacity][capacity];
	char Sym[capacity];
	string PNames[2];
	int Turn;
	Init2(B, Dim, NOP, WinC, Sym, PNames, Turn);
	bool isValid = false;
	BoardPrint2(B, Dim);
	do {
		TurnMsg(PNames[Turn]);
		if (Turn == 1) {
			ComputerPoisition(B, Dim, r, c, Sym, WinC);
		}
		else {
			do {
				SelectPosition(Dim, r, c);
			} while (!Valid(B, Dim, r, c));
		}
		PlaceMove(B, r, c, Sym[Turn]);
		BoardPrint2(B, Dim);
		
		
		GameOver = IsWin(B, Dim, Sym[Turn], WinC);
		if (GameOver == true) {
			winner = Turn;
		}
		if (GameOver == false) {
			GameOver = IsDraw(B, Dim);
		}
		if (GameOver == false) {
			TurnChange(Turn, NOP);
		}
	} while (!GameOver);
	if (winner == -1) {
		cout << "The Game is Draw!";
	}
	else {
		cout << PNames[winner] << " Has Won the Match!";
	}
}

int main() {
	int choose;
	cout << "Choose between\n1: MultiPlayer\n2: Single Player"<<endl;
	cin >> choose;
	while (true) {
		while (choose < 1 || choose >2) {
			cout << "Invalid Input!...Enter Again: ";
			cin >> choose;
		}
		if (choose == 1) {
			mainHUMAN();
		}
		else if (choose == 2) {
			mainAIvsHuman();
		}
	}
	return 0;
}

//////////////////////////////////
