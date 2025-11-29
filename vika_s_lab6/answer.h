#ifndef ANSWER_H
#define ANSWER_H

#include "user.h"
#include <string>

class Answer : public User {
protected:
    std::string date;
    std::string testName;
public:
    Answer();
    Answer(std::string fio, const std::string& faculty, int groupNum, std::string date, std::string testName);
    Answer(const Answer& copy);
    ~Answer() override = default;

    std::string getDate() const;
    std::string getTestName() const;

    void setDate(const std::string& newDate);
    void setTestName(const std::string& newTestName);
};

#endif