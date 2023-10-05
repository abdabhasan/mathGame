#include <iostream>

using namespace std;

enum enQuestionsLevel {Easy = 1, Med = 2, Hard = 3, Mix = 4};
enum enOperationType {Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5};

struct stQuestion {
    int number1 = 0;
    int number2 = 0;
    enOperationType operationType;
    enQuestionsLevel questionLevel;
    int correctAnswer = 0;
    int playerAnswer = 0;
    bool answerResult = false;
};

struct stQuizz{
    stQuestion questionList[100];
    short numberOfQuestions;
    enQuestionsLevel questionsLevel;
    enOperationType opType;
    short numberOfWrongAnswers;
    short numberOfRightAnswers;
    bool isPass = false;
};

int randomNumber(int from, int to){

    int randNum = rand() % (to - from + 1) + from;
    return randNum;
}

short readHowManyQuestions(){
    short numberOfQuestions;

    do{
        cout << "How many Questions do you want to answer ? ";
        cin >> numberOfQuestions;
    }while(numberOfQuestions < 1 || numberOfQuestions > 10);
    
    return numberOfQuestions;
}

int simpleCalculator(int number1 , int number2, enOperationType opType){

    switch (opType){
        case enOperationType::Add:
            return number1 + number2;    
        case enOperationType::Sub:
            return number1 - number2;    
        case enOperationType::Mult:
            return number1 * number2;    
        case enOperationType::Div:
            return number1 / number2;    
        default:
            return number1 + number2;    
    }
}

string getFinalRestultsText(bool pass){
    if(pass)
        return "PASS :)";
    else 
        return "FAIL :(";


}

string getQuestionLevelText(enQuestionsLevel questionLevel){
    string arrQuestionLevelText[4] = {"Easy", "Med", "Hard", "Mix"};
    return arrQuestionLevelText[questionLevel - 1];
}

string getOpTypeSymbol(enOperationType opType){
    
    switch (opType){
    case enOperationType::Add:
        return "+";
    case enOperationType::Sub:
        return "-";
    case enOperationType::Mult:
        return "x";
    case enOperationType::Div:
        return "/";
    default:
        return "Mix";
    }
}

enQuestionsLevel readQuestionsLevel(){

    short questionsLevel = 0;

    do{
        cout << "Enter Questions Level [1]: Easy, [2]: Med, [3]: Hard, [4]: Mix ? ";
        cin >> questionsLevel;
    }while(questionsLevel < 1 || questionsLevel > 4);
    
    return (enQuestionsLevel)questionsLevel;
}

enOperationType readOpType(){

    short opType;

    do{
        cout << "Enter Operation Type [1]: Add, [2]: Sub, [3]: Mul, [4]: Div, [5]: Mix ? ";
        cin >> opType;
    }while(opType < 1 || opType > 4);
    
    return (enOperationType)opType;
}

enOperationType getRandomOperationType(){

    int op = randomNumber(1, 4);
    return (enOperationType) op;
}

stQuestion generateQuestion(enQuestionsLevel questionLevel, enOperationType opType){

    stQuestion question;

    if(questionLevel == enQuestionsLevel::Mix){
        questionLevel = (enQuestionsLevel)randomNumber(1, 3);
    }
    if(opType == enOperationType::MixOp){
        opType = getRandomOperationType();
    }

    question.operationType = opType;
    switch (questionLevel){
    case enQuestionsLevel::Easy:
        question.number1 = randomNumber(1, 10);
        question.number2 = randomNumber(1, 10);

        question.correctAnswer = simpleCalculator(question.number1, question.number2, question.operationType);
        question.questionLevel = questionLevel;
        return question;
    case enQuestionsLevel::Med:
        question.number1 = randomNumber(10, 50);
        question.number2 = randomNumber(10, 50);

        question.correctAnswer = simpleCalculator(question.number1, question.number2, question.operationType);
        question.questionLevel = questionLevel;
        return question;
    case enQuestionsLevel::Hard:
        question.number1 = randomNumber(50, 100);
        question.number2 = randomNumber(50, 100);

        question.correctAnswer = simpleCalculator(question.number1, question.number2, question.operationType);
        question.questionLevel = questionLevel;
        return question;
    }
    return question;
}

void generateQuizzQuestions(stQuizz& quizz){

    for(short question = 0; question < quizz.numberOfQuestions; question++){
        quizz.questionList[question] = generateQuestion(quizz.questionsLevel, quizz.opType);
    }    
}

void printTheQuestion(stQuizz& quizz, short questionNumber){

    cout << "\n";
    cout << "Question [" << questionNumber + 1 << "/" << quizz.numberOfQuestions << "] \n\n";
    cout << quizz.questionList[questionNumber].number1 << endl;
    cout << quizz.questionList[questionNumber].number2 << " ";
    cout << getOpTypeSymbol(quizz.questionList[questionNumber].operationType);
    cout << "\n____________" << endl;

}

int readQuestionAnswer(){
    int answer = 0;
    cin >> answer;
    return answer;
}

void correctTheQuestionAnswer(stQuizz& quizz, short questionNumber){

    if(quizz.questionList[questionNumber].playerAnswer != quizz.questionList[questionNumber].correctAnswer){
        quizz.questionList[questionNumber].answerResult = false;
        quizz.numberOfWrongAnswers++;

        cout << "Wrong Answer :( \n";
        cout << "The right answer is: ";
        cout << quizz.questionList[questionNumber].correctAnswer;
        cout << "\n";
    } else {
        quizz.questionList[questionNumber].answerResult = true;
        quizz.numberOfRightAnswers++;

        cout << "Right answer :) \n";
    }
    
    cout << endl;
    

}

void askAndCorrectQuestionListAnswers(stQuizz& quizz){

    for( short questionNumber = 0; questionNumber < quizz.numberOfQuestions; questionNumber++){
        printTheQuestion(quizz, questionNumber);
        quizz.questionList[questionNumber].playerAnswer = readQuestionAnswer();
        correctTheQuestionAnswer(quizz, questionNumber);
    }
    quizz.isPass = (quizz.numberOfRightAnswers >= quizz.numberOfWrongAnswers);
}

void printQuizzResults(stQuizz quizz){
    cout << "\n";
    cout << "________________\n\n";
    cout << "Final Results " << getFinalRestultsText(quizz.isPass);
    cout << "\n________________\n\n";

    cout << "Number of Questions    : " << quizz.numberOfQuestions << endl;
    cout << "Questions Level        : " << getQuestionLevelText(quizz.questionsLevel) << endl;
    cout << "OpType                 : " << getOpTypeSymbol(quizz.opType) << endl;
    cout << "Number of Right Answers: " << quizz.numberOfRightAnswers << endl;
    cout << "Number of Right Answers: " << quizz.numberOfWrongAnswers << endl;
    cout << "________________\n\n";
}

void playMathGame(){

    stQuizz quizz;
    quizz.numberOfQuestions = readHowManyQuestions();
    quizz.questionsLevel = readQuestionsLevel();
    quizz.opType = readOpType();

    generateQuizzQuestions(quizz);
    askAndCorrectQuestionListAnswers(quizz);
    printQuizzResults(quizz);
}

void resetScreen(){

    system("clear");
}

void startGame(){
    
    char playAgain = 'Y';

    do{

        resetScreen();
        playMathGame();

        cout << endl << "Do you want to play again? Y/N? ";
        cin >> playAgain;
    }while(playAgain == 'Y' || playAgain == 'y');
}

int main(){

    srand((unsigned)time(NULL));

    startGame();


    return 0;
}