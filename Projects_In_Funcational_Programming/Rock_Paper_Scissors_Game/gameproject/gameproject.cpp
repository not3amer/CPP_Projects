#include <iostream>
using namespace std;
struct roundInfo
{
	int roundsNumber;
	int playerChoice;
	int computerChoice;
	string roundWinner;
};
struct gameInfo
{
	int rounds;
	int playerTimes=0;
	int computerTimes=0;
	string finalWinner;
};
int inputRoundsNumber(roundInfo round) {
	cout << "how many rounds you want? ";
	cin >> round.roundsNumber;
	return round.roundsNumber;
}
int computerChoice(int from, int to) {
	return rand() % (to - from + 1) + from;
}
string getWinner(roundInfo round) {
	if (round.playerChoice == round.computerChoice)
		return "[No Winner]";
	else if (round.playerChoice == 1 && round.computerChoice == 2)
		return "[Computer]";
	else if (round.playerChoice == 2 && round.computerChoice == 3)
		return "[Computer]";
	else if (round.playerChoice == 3 && round.computerChoice == 1)
		return "[Computer]";
	else
		return "[Player]";
}
string getNameOfChoise(int Choice) {
	if (Choice == 1)
		return "Stone";
	else if (Choice == 2)
		return "Paper";
	else
		return "Scissors";
}
void printRoundResults(roundInfo round) {

	getNameOfChoise(round.computerChoice);
	if (round.roundWinner == "[Computer]") {
		cout << "\a";
		system("color 4F");
	}
	else if (round.roundWinner == "[Player]")
		system("color 2F");
	else
		system("color 6F");

	cout << "Player 1 Choise : " << getNameOfChoise(round.playerChoice) << endl;
	cout << "Computer Choise : " << getNameOfChoise(round.computerChoice) << endl;
	cout << "Round Winner    : " << round.roundWinner << endl;
	cout << "_________________________________\n";

}
gameInfo getFinalResults(roundInfo round, gameInfo &game) {
	//get number of wins times
	if (round.roundWinner == "[Computer]")
		game.computerTimes++;
	else if (round.roundWinner == "[Player]")
		game.playerTimes++;

	return game;
}
void printGameResults() {
	roundInfo round;
	gameInfo game;
	int roundsNumber = inputRoundsNumber(round);
	for (int i = 1; i <= roundsNumber; i++)
	{
		cout << "\n\nRound [ " << i << " ] begins : " << endl;
		// get user choice and get random choice for computer
		round.computerChoice = computerChoice(1, 3);
		cout << "your choice : [1] Stone, [2] Paper, [3] Scissors ?";
		cin >> round.playerChoice;

		//print round results from (printRoundResults) fun
		round.roundWinner = getWinner(round);
		printf("\n_____________Round %d_____________\n", i);
		printRoundResults(round);
		getFinalResults(round, game);
	}
	if (game.playerTimes < game.computerTimes)
		game.finalWinner = "Computer";
	else if (game.playerTimes > game.computerTimes)
		game.finalWinner = "Player 1";

	else if (game.playerTimes == game.computerTimes)
		game.finalWinner = "No one";

	cout << "\t\t\t_________________________________________________" << endl;
	cout << "\n\t\t\t\t\t  +++Game Over+++" << endl << endl;
	cout << "\t\t\t_________________________________________________" << endl;

	cout << "\t\t\t\t\tGame rounds   : " << roundsNumber << endl;
	cout << "\t\t\t\t\tplayer win    : " << game.playerTimes << endl;
	cout << "\t\t\t\t\tComputer win  : " << game.computerTimes << endl;
	cout << "\t\t\t\t\tDraw Times    : " << roundsNumber - (game.playerTimes + game.computerTimes) << endl;
	cout << "\t\t\t\t\tFinal Winner  : " << game.finalWinner << endl;
}
void resetScreen() {
	system("cls");
	system("color 0F");
}
void startgame() {
	string newgame = "y";
	do {
		resetScreen();
		printGameResults();
		cout << "want to play agin? (y,n) ";
		cin >> newgame;
	} while (newgame == "y" || newgame == "Y");
}

int main()
{
	srand((unsigned)time(NULL));

	startgame();

	return 0;
}