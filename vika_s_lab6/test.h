#ifndef TEST_H
#define TEST_H

#include "user.h"
#include "answer.h"
#include "result.h"
#include "question.h"
#include <string>

class Test {
private:
    static const int MAX_QUESTIONS = 50;
    static const int MAX_ANSWERS = 100;
    static const int MAX_RESULTS = 100;
    static const int MAX_VARIANTS = 10;

    std::string testName;
    std::string testTheme;
    IQuestion* questions[MAX_QUESTIONS];
    Answer answers[MAX_ANSWERS];
    Result results[MAX_RESULTS];
    int questionCount;
    int answerCount;
    int resultCount;

public:
    Test();
    Test(std::string name, std::string theme);
    Test(const Test& other);
    Test& operator=(const Test& other);
    ~Test();

    std::string getTestName() const;
    std::string getTestTheme() const;
    int getQuestionCount() const;
    int getAnswerCount() const;
    int getResultCount() const;

    void setTestName(const std::string& name);
    void setTestTheme(const std::string& theme);

    bool addQuestion(IQuestion* question);
    bool addAnswer(const Answer& answer);
    bool addResult(const Result& result);

    void displayTestInfo() const;
    void showMenu();

private:
    void addTextQuestion();
    void addNumericQuestion();
    void displayAllQuestions() const;
    void takeTest();
    void displayResults() const;
    void displayResultsTable() const;
    void saveResultsToFile() const;
};

#endif