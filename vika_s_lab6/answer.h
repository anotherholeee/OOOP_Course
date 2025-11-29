#ifndef ANSWER_H
#define ANSWER_H

#include "user.h"
#include <string>
using namespace std;

class Answer : public User {
protected:
    string date;
    string testName;
public:
    Answer();
    Answer(string fio, const string& faculty, int groupNum, string date, string testName);
    Answer(const Answer& copy);
    ~Answer() override;

    string getDate() const;
    string getTestName() const;

    void setDate(const string& newDate);
    void setTestName(const string& newTestName);
};

#endif