#ifndef RESULT_H
#define RESULT_H

#include "answer.h"
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

class Result : public Answer {
private:
    float result;
    bool passed;

public:
    Result();
    Result(const string& fio, const string& faculty, int groupNum, const string& date,
           const string& testName, float result);
    Result(const Result& copy);
    ~Result() override;

    float getResult() const;
    bool getPassed() const;

    void setResult(float newResult);

    void display() const;
    static void displayTableHeader();
    static void displayTableFooter();
    void displayTableRow(int index) const;
    void saveToFile(ofstream& file, int index) const;
};

#endif