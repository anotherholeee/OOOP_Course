#ifndef ANSWER_H
#define ANSWER_H

#include "user.h"
#include "transaction.h"
#include <string>
#include <memory>

// Объявление класса Answer
class Answer : public User {
protected:
    std::string date;
    std::string testName;
    std::unique_ptr<TransactionHistory> history;

public:
    Answer();
    Answer(std::string fio, const std::string& faculty, int groupNum,
           std::string date, std::string testName);
    Answer(const Answer& copy);
    ~Answer() override = default;

    std::string getDate() const;
    std::string getTestName() const;

    void setDate(const std::string& newDate);
    void setTestName(const std::string& newTestName);

    // Методы для работы с историей изменений
    void saveCurrentState();
    bool undoLastChange();
    void commitAllChanges();
    bool hasUnsavedChanges() const;
    int getChangeHistorySize() const;

    // Методы из User, которые нам нужны
    using User::setFio;
    using User::setFaculty;
    using User::setGroupNum;
    using User::getFio;
    using User::getFaculty;
    using User::getGroupNum;
};

#endif