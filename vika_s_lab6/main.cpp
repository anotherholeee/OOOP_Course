#include<iostream>
#include<windows.h>
#include<string>

using namespace std;

class User { //ФИО, факультет, номер группы
protected:
    string fio;
    string faculty;
    int groupNum;
public:
User(): groupNum(0){};
User(string fio, string faculty, int groupNum): fio(std::move(fio)), faculty(std::move(faculty)), groupNum(groupNum){};

User(const User& copy): groupNum(copy.groupNum) {}
};

class Answer: public User{ //дата выполнения теста, ФИО выполнившего тест
    private:
int date;
    public:
Answer(): date(0) {};
    Answer(const string& fio, const string& faculty, int groupNum, int date): User(fio, faculty, groupNum), date(date) {};
Answer(const Answer& copy): User(copy.fio, copy.faculty, copy.groupNum), date(copy.date) {};

};

class Question { //Текст вопроса, варианты ответа, правильный ответ, баллы за вопрос
    private:
    string questionText;
    string variants;
    string rightVariant;
    int scores;

public:
    Question() : scores(0) {}

    Question(string questionText, string  variants, string  rightVariant, int scores) : questionText(
        std::move(questionText)), variants(std::move(variants)), rightVariant(std::move(rightVariant)), scores(scores) {}
    Question(const Question& copy): questionText(copy.questionText),variants(copy.variants),rightVariant(copy.rightVariant),scores(copy.scores) {}
};

class Result: public Answer {
//ФИО, факультет, номер группы, результат(в %), сдал/не сдал
private:
    float result;
    bool passed;
public:
    Result(): result(0), passed(false) {};
    Result(const string& fio, const string& faculty, int groupNum, int date, float result) : Answer(fio, faculty, groupNum, date), result(result), passed(result >= 60.0f) {}
Result (const Result& copy): Answer(copy), result(copy.result), passed(copy.passed) {}
};

class Test { //название теста, тема теста, перечень вопросов, перечень полученных ответов
    private:
    static const int MAX_QUESTIONS = 100;
    static const int MAX_ANSWERS = 1000;

    string testName;
    string testTheme;
Question questions[MAX_QUESTIONS];
Answer answers[MAX_ANSWERS];
    int questionCount;
    int answerCount;
    public:

    Test(): questions(), answers(), questionCount(), answerCount() {}
    Test(string testName, string testTheme): testName(std::move(testName)), testTheme(std::move(testTheme)), questionCount(0), answerCount(0) {}
    Test(const Test& copy): testName(copy.testName), testTheme(copy.testTheme), questionCount(0), answerCount(0) {}
};




using namespace std;
int main() {
SetConsoleOutputCP(CP_UTF8);



    return 0;
}