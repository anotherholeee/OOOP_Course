#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <stack>
#include <memory>
#include <string>

// Предварительное объявление класса Answer
class Answer;

class AnswerState {
private:
    std::string fio;
    std::string faculty;
    int groupNum;
    std::string date;
    std::string testName;
    
public:
    AnswerState(const Answer& answer);
    void restore(Answer& answer) const;
};

class TransactionHistory {
private:
    std::stack<std::unique_ptr<AnswerState>> history;
    Answer* currentAnswer;
    
public:
    TransactionHistory();
    void saveState(Answer& answer);
    void commitAll();
    bool rollbackLast();
    bool canRollback() const;
    int getHistorySize() const;
};

#endif