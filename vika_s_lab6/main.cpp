#include<iostream>
#include<windows.h>
#include<string>

using namespace std;

class Test { //название теста, тема теста, перечень вопросов, перечень полученных ответов
    private:
    string testName;
    string testTheme;

    static const int MAX_QUESTIONS = 100;
    static const int MAX_ANSWERS = 1000;



};

class User { //ФИО, факультет, номер группы
protected:
    string fio;
    string faculty;
    int groupNum;
public:
User(): fio(""), faculty(""), groupNum(0){};
User(const string& fio, const string& faculty, int groupNum): fio(fio), faculty(faculty), groupNum(groupNum){};

User(const User& copy): fio(copy.fio), faculty(copy.faculty), groupNum(copy.groupNum) {};

};

class Answer: public User{ //дата выполнения теста, ФИО выполнившего тест
    private:
int date;
    public:
Answer(): date(date), User() {};
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
    Question(): questionText(""), variants(""), rightVariant("") {};
    Question(const string& questionText, const string& variants, const string& rightVariant, int scores): questionText(questionText), variants(variants), rightVariant(rightVariant) {};
    Question(const Question& copy): questionText(copy.questionText), variants(copy.variants), rightVariant(copy.rightVariant) {};
};

class Result: public Answer { //ФИО, факультет, номер группы, результат(в %), сдал/не сдал
    private:
    float result;
    //добавить bool сдал/не сдал

};









using namespace std;
int main() {
SetConsoleOutputCP(CP_UTF8);



    return 0;
}