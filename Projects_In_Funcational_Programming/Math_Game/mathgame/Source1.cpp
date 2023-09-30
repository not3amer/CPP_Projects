#include <iostream>
using namespace std;
enum enQestionLevels { Easy = 1, Med = 2, Hard = 3, Mix = 4 };
enum enQestionType { Add = 1, Sub = 2, Mul = 3, Div = 4, Mixx = 5 };
struct questionVars
{
	float num1=0, num2=0, num3=0;
};
struct gameVars {
	int qustionNumbers;
	int qestionLevel;
	int qestionType;
	int trueCounter=0;
	int falseCounter=0;
};
int inputQustionNumbers(gameVars &game) {
	cout << "how many qestion you want? ";
	cin >> game.qustionNumbers;
	return game.qustionNumbers;
}
int inputQustionLevel(gameVars &game) {
	cout << "Enter qustion level [1] Easy, [2] Med, [3] Hard, [4] Mix ? ";
	cin >> game.qestionLevel;
	return game.qestionLevel;
}
int inputQustionType(gameVars &game) {
	cout << "Enter qustion level [1] Add, [2] Sub, [3] Mul, [4] Div, [5] Mix ? ";
	cin >> game.qestionType;
	return game.qestionType;
}
int getRandomNumbers(int from, int to) {
	return rand() % (to - from + 1) + from;
}
char getRandomOperator() {
	int op = getRandomNumbers(42, 47);
	while (op == 44 || op == 46) {
		op = getRandomNumbers(42, 47);
	}
	return char(op);
}
void getFinalResult(questionVars qustion,gameVars &game) {
	if (qustion.num3 == (qustion.num1 + qustion.num2))
		game.trueCounter ++ ;
	else
		game.falseCounter++;
}
void questionBasedOperator(questionVars &question,char op, int start, int end) {
	question.num1 = getRandomNumbers(start, end);
	question.num2 = getRandomNumbers(start, end);
	cout << question.num1 << op << question.num2 << endl << "--------" << endl;
	cin >> question.num3;
}
void askBaseType(questionVars & question,gameVars game, int start, int end) {
	if (game.qestionType == enQestionType::Add) {
		questionBasedOperator(question, '+', start, end);
	}else if (game.qestionType == enQestionType::Sub) {
		questionBasedOperator(question, '-', start, end);
	}
	else if (game.qestionType == enQestionType::Mul) {
		questionBasedOperator(question, '*', start, end);
	}
	else if (game.qestionType == enQestionType::Div) {
		questionBasedOperator(question, '/', start, end);
	}else if (game.qestionType == enQestionType::Mixx) {
		char op = getRandomOperator();
		switch (op)
		{
		case '+':
			questionBasedOperator(question, '+', start, end);
			break;
		case '-':
			questionBasedOperator(question, '-', start, end);
			break;
		case '*':
			questionBasedOperator(question, '*', start, end);
			break;
		case '/' :
			questionBasedOperator(question, '/', start, end);
			break;
		}
	}
}
void getQuestion(questionVars &question,gameVars &game) {
	switch (game.qestionLevel)
	{
	case enQestionLevels::Easy:
		askBaseType(question,game, 1, 10);
		getFinalResult(question, game);
		break;
	case enQestionLevels::Med:
		askBaseType(question,game ,10, 100);
		getFinalResult(question, game);
		break;
	case enQestionLevels::Hard:
		askBaseType(question,game ,100, 1000);
		getFinalResult(question, game);
		break;
	case enQestionLevels::Mix:
		askBaseType(question,game, 1, 1000);
		getFinalResult(question, game);
		break;
	}
}
void passOrFail(gameVars game) {
	if (game.trueCounter >= game.falseCounter)
		cout << "\t\t\t\t\tTotal           : " << "Pass" << endl;
	else if 
		(game.trueCounter < game.falseCounter)
		cout << "\t\t\t\t\tTotal           : " << "Fail" << endl;
}
void printGameResults() {
	questionVars question;
	gameVars game;
	game.qustionNumbers = inputQustionNumbers(game);
	game.qestionLevel = inputQustionLevel(game);
	game.qestionType = inputQustionType(game);

	for (int i = 1; i <= game.qustionNumbers; i++)
	{
		cout << "\n\nQuestion number [ " << i << "/" << game.qustionNumbers << " ]" << endl;
		getQuestion(question,game);

	}
	cout << "\t\t\t_________________________________________________" << endl;
	cout << "\n\t\t\t\t\t  +++Quizz Results+++" << endl << endl;
	cout << "\t\t\t_________________________________________________" << endl;
	cout << "\t\t\t\t\tQuestion Number : " << game.qustionNumbers << endl;
	cout << "\t\t\t\t\tcorrect         : " << game.trueCounter << endl;
	cout << "\t\t\t\t\tincorrect       : " << game.falseCounter << endl;
	passOrFail(game);
}
void startgame() {
	string newgame = "y";
	do {
		system("cls");
		printGameResults();
		cout << "want to play agin? (y,n) ";
		cin >> newgame;
	} while (newgame == "y" || newgame == "Y");
}
int main() {
	srand((unsigned)time(NULL));
	
	startgame();

	return 0;
}