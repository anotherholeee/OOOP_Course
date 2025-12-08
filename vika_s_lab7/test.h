#ifndef TEST_H
#define TEST_H

#include <string>
#include <memory>
#include <vector>

// Предварительные объявления
class IQuestion;
class Answer;
class Result;

class Test {
private:
    static const int MAX_QUESTIONS = 50;
    static const int MAX_ANSWERS = 100;
    static const int MAX_RESULTS = 100;
    static const int MAX_VARIANTS = 10;

    std::string testName;
    std::string testTheme;
    std::vector<std::unique_ptr<IQuestion>> questions;
    std::vector<std::unique_ptr<Answer>> answers;
    std::vector<std::unique_ptr<Result>> results;

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

    bool addQuestion(std::unique_ptr<IQuestion> question);
    bool addAnswer(std::unique_ptr<Answer> answer);
    bool addResult(std::unique_ptr<Result> result);

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
    void manageTransactions();
};

#endif