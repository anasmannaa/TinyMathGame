
#include <iostream>
using namespace std;

enum enQuestionLevel
{
	Easy = 1,
	Med = 2,
	Hard = 3,
	QMix = 4,
};

enum enOpreationType
{
	Add = 1,
	Sub = 2,
	Mul = 3,
	Div = 4,
	OMix = 5,
};

enum enAnswer {Right = 1, Wrong = 2};

enum enFinalResult {Pass = 1, Fail = 2};

struct stFinalResults
{
	int NumOfQuestions;
	int NumOfRightAnswers;
	int NumOfWrongAnswers;
	enQuestionLevel QuestionLevel;
	enOpreationType OperationType;
	enFinalResult Result;
};

void ResetQuiz()
{
	system("cls");
	system("color 0F");
}

int RandomNumber(int From, int To)
{
	int randNum = rand() % (To - From + 1) + From;
	return randNum;
}

int ReadPostiveNumber(string Message)
{
	int Number;
	do
	{
		cout << "\n" << Message << endl;
		cin >> Number;
	} while (Number < 0);
	return Number;
}

enQuestionLevel GetQuestionLevel()
{
	int QuestionLevel;
	cout << "\nEnter Question Level [1] Easy, [2] Med, [3] Hard, [4] Mix: ";
	cin >> QuestionLevel;
	return (enQuestionLevel)QuestionLevel;	
}

enOpreationType GetOperationType()
{
	int OperationType;
	cout << "\nEnter Operation Type [1] Add, [2] Sub, [3] Mul, [4] Div, [5]Mix: ";
	cin >> OperationType;
	return (enOpreationType)OperationType;
}

int GetOperationNumber(enQuestionLevel QuestionLevel)
{
	switch (QuestionLevel)
	{
	case Easy:
		return RandomNumber(1, 9);
		break;
	case Med:
		return RandomNumber(10, 100);
		break;
	case Hard:
		return RandomNumber(101, 1000);
		break;
	case QMix:
		return RandomNumber(1, 1000);
		break;
	default:
		break;
	}
}

char GetRandoOperator()
{
	switch (RandomNumber(1,4))
	{
	case 1:
		return '+';
		break;
	case 2:
		return '-';
		break;
	case 3:
		return '*';
		break;
	case 4:
		return '/';
		break;
	default:
		break;
	}
}

char GetOperator(enOpreationType OperationType)
{
	switch (OperationType)
	{
	case Add:
		return '+';
		break;
	case Sub:
		return '-';
		break;
	case Mul:
		return '*';
		break;
	case Div:
		return '/';
		break;
	case OMix:
		return GetRandoOperator();
	default:
		break;
	}
}

int GetRightAnswer(int FirstNumber, int SecondNumber, char Operator)
{
	switch (Operator)
	{
	case '+':
		return FirstNumber + SecondNumber;
		break;
	case '-':
		return FirstNumber - SecondNumber;
	case '*':
		return FirstNumber * SecondNumber;
	case '/':
		return FirstNumber / SecondNumber;
	default:
		break;
	}
}

void SetScreenColor(enFinalResult Result)
{
	switch (Result)
	{
	case Pass:
		system("color 2F");
		break;
	case Fail:
		system("color 4F");
		cout << "\a";
		break;
	default:
		break;
	}
}

enAnswer PerformQuestion(enQuestionLevel QuestionLevel, enOpreationType OperationType)
{
	
	int UserAnswer;
	
	int FirstNumber = GetOperationNumber(QuestionLevel);
	int SecondNumber = GetOperationNumber(QuestionLevel);
	char Operator = GetOperator(enOpreationType(OperationType));
	cout << "\n" << FirstNumber;
	cout << "\n" << SecondNumber << " " << Operator;
	cout << "\n-------------";
	cout << "\n";
	cin >> UserAnswer;
	int RightAnswer = GetRightAnswer(FirstNumber, SecondNumber, Operator);

	if (UserAnswer == RightAnswer)
	{
		cout << "Right Answer :)\n";
		SetScreenColor(Pass);
		return enAnswer::Right;
	}
	else
	{
		cout << "Wrong Answer :(\n";
		cout << "Right Answer Is " << RightAnswer << endl;
		SetScreenColor(Fail);
		return enAnswer::Wrong;
	}
}

stFinalResults PerformQuiz(int QuestionsNum)
{
	stFinalResults FinalResult;
	int RightAnswers = 0, WrongAnswers = 0;
	enQuestionLevel QuestionLevel = GetQuestionLevel();
	enOpreationType OperationType = GetOperationType();
	for (int i = 0; i < QuestionsNum; i++)
	{
		cout << "\nQuestion [" << i + 1 << "] of " << QuestionsNum << endl;
		enAnswer Answer = PerformQuestion(QuestionLevel, OperationType);
		if (Answer == Right)
			RightAnswers++;
		else
			WrongAnswers++;
	}
	FinalResult.NumOfQuestions = QuestionsNum;
	FinalResult.NumOfRightAnswers = RightAnswers;
	FinalResult.NumOfWrongAnswers = WrongAnswers;
	FinalResult.OperationType = OperationType;
	FinalResult.QuestionLevel = QuestionLevel;

	if (RightAnswers >= WrongAnswers)
		FinalResult.Result = Pass;
	else
		FinalResult.Result = Fail;

	return FinalResult;
}

string GetResultName(enFinalResult Result)
{
	string results[2] = {"Pass", "Fail"};
	return results[Result - 1];
}

string GetQLevelName(enQuestionLevel Level)
{
	string levels[4] = { "Easy", "Medium", "Hard", "Mix"};
	return levels[Level - 1];
}

string GetOpreationTypeName(enOpreationType Type)
{
	string operations[5] = { "Add", "Sub", "Mul", "Div", "Mix"};
	return operations[Type - 1];
}

void PrintFinalResult(stFinalResults FinalResults)
{
	string smile[2] = { "(:", "):" };
	cout << "\n--------------------------------------\n";
	cout << "Final Result is " << GetResultName(FinalResults.Result);
	if (FinalResults.Result == Pass)
		cout << " :)";
	else
		cout << ":(";
	cout << "\n--------------------------------------\n";

	cout << "Number Of Questions    : " << FinalResults.NumOfQuestions << "\n";
	cout << "Questions Level        : " << GetQLevelName(FinalResults.QuestionLevel) << "\n";
	cout << "Operation Type         : " << GetOpreationTypeName(FinalResults.OperationType) << "\n";
	cout << "Number Of Right Answers: " << FinalResults.NumOfRightAnswers << "\n";
	cout << "Number Of Wrong Answers: " << FinalResults.NumOfWrongAnswers << "\n";
}
void StartQuiz()
{
	string PlayAgain = "Y";

	do {
		ResetQuiz();
		stFinalResults FinalResult = PerformQuiz(ReadPostiveNumber("How Many Questions Do You Want To Answer? "));
		
		PrintFinalResult(FinalResult);
		
		SetScreenColor(FinalResult.Result);
		cout << "\nDo You Want To Play Again Y/N? " << endl;
		cin >> PlayAgain;
	} while (PlayAgain == "Y" || PlayAgain == "y");
}

int main()
{
	srand((unsigned)time(NULL));

	StartQuiz();

	return 0;
}
