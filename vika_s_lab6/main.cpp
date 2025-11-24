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


     string getFio()  { return std::move(fio); }
     string getFaculty()  { return std::move(faculty); }
    int getGroupNum() const { return groupNum; }


    void setFio(const string& newFio) {
    if (!newFio.empty()) {
        fio = newFio;
    }
}

    void setFaculty(const string& newFaculty) {
    if (!newFaculty.empty()) {
        faculty = newFaculty;
    }
}

    void setGroupNum(int newGroupNum) {
    if (newGroupNum > 0 && newGroupNum < 1000) {
        groupNum = newGroupNum;
    }
}


};



class Answer: public User{ //дата выполнения теста, ФИО выполнившего тест
    protected:
int date;
    public:
Answer(): date(0) {};
    Answer(const string& fio, const string& faculty, int groupNum, int date): User(fio, faculty, groupNum), date(date) {};
Answer(const Answer& copy): User(copy.fio, copy.faculty, copy.groupNum), date(copy.date) {};

int getDate() const { return date; }

    void setDate(int newDate) { date = newDate; }
};


//может быть шаблонным questionText, variants
template<class TQuestion, class TVariants>
class Question { //Текст вопроса, варианты ответа, правильный ответ, баллы за вопрос
    protected:
    TQuestion questionText;
    TVariants variants;
    int rightVariantNumber;
    int scores;

public:
    Question() : rightVariantNumber(0), scores(0) {}

    Question(TQuestion questionText, TVariants variants, int rightVariantNumber, int scores)
        : questionText(questionText),
          variants(variants),
          rightVariantNumber(rightVariantNumber),
          scores(scores) {}

    Question(const Question& copy)
            : questionText(copy.questionText),
              variants(copy.variants),
              rightVariantNumber(copy.rightVariantNumber),
              scores(copy.scores) {}

    TQuestion getQuestionText() { return questionText; }
    TVariants getVariants() { return variants; }
    int getRightVariantNumber() const { return rightVariantNumber; }
    int getScores() const { return scores; }

    void setQuestionText(string&& newQuestionText) {
        if (!newQuestionText.empty()) {
            questionText = newQuestionText;
        }
    }

    void setVariants(TVariants newVariants) {
        if (!newVariants.empty()) {
            variants = newVariants;
        }
    }

    void setRightVariantNumber(int newRightVariantNumber) {
        if (newRightVariantNumber > 0) {  // обычно номера ответов начинаются с 1
            rightVariantNumber = newRightVariantNumber;
        }
    }

    void setScores(int newScores) {
        if (newScores >= 0) {
            scores = newScores;
        }
    }

    bool checkAnswer(int userAnswer) const {
        return userAnswer == rightVariantNumber;
    }

    // Метод для отображения вопроса и вариантов ответа
    void displayQuestion() const {
        cout << "Вопрос: " << questionText << endl;
        cout << "Варианты ответов:\n" << variants << endl;
        cout << "Баллы за вопрос: " << scores << endl;
    }

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

float getResult() const { return result; }
    bool getPassed() const { return passed; }

    void setResult(float newResult) {
        result = newResult;
        passed = (result >= 60.0f);
    }

    void setPassed(bool newPassed) { passed = newPassed; }


};



class Test { //название теста, тема теста, перечень вопросов, перечень полученных ответов
    private:
    static const int MAX_QUESTIONS = 100;
    static const int MAX_ANSWERS = 1000;

    string testName;
    string testTheme;
    Question<int> questions[MAX_QUESTIONS]{}; //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
Answer answers[MAX_ANSWERS];
    int questionCount;
    int answerCount;
    public:

    Test(): questions(), answers(), questionCount(), answerCount() {}
    Test(string testName, string testTheme): testName(std::move(testName)), testTheme(std::move(testTheme)), questionCount(0), answerCount(0) {}
    Test(const Test& copy): testName(copy.testName), testTheme(copy.testTheme), questionCount(0), answerCount(0) {}

string getTestName() { return std::move(testName); }
    string getTestTheme() { return std::move(testTheme); }

    int getQuestionCount() const{ return questionCount; }
    int getAnswerCount() const{ return answerCount; }

    void setTestName(string newTestName) { testName = std::move(newTestName); }
    void setTestTheme(string newTestTheme) { testTheme = std::move(newTestTheme); }
    void setQuestionCount(int newCount) { questionCount = newCount; }
    void setAnswerCount(int newCount) { answerCount = newCount; }

};




using namespace std;
int main() {
SetConsoleOutputCP(CP_UTF8);



    return 0;
}