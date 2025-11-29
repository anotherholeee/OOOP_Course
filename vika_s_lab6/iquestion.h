#ifndef IQUESTION_H
#define IQUESTION_H
#include<iostream>
#include <string>
using namespace std;

class IQuestion {
public:
    virtual ~IQuestion() = default;
    virtual void displayQuestion() const = 0;
    virtual bool checkAnswer(int userAnswer) const = 0;
    virtual int getScores() const = 0;
    virtual string getType() const = 0;
    virtual string getQuestionText() const = 0;
    virtual int getVariantsCount() const = 0;
};

#endif