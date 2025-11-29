#ifndef RESULT_H
#define RESULT_H

#include "answer.h"
#include <iomanip>
#include <fstream>

class Result : public Answer {
private:
    float result;
    bool passed;

public:
    Result();
    Result(const std::string& fio, const std::string& faculty, int groupNum, const std::string& date,
           const std::string& testName, float result);
    Result(const Result& copy);
    ~Result() override = default;

    float getResult() const;
    bool getPassed() const;

    void setResult(float newResult);
    void display() const;

    static void displayTableHeader();
    static void displayTableFooter();
    void displayTableRow(int index) const;
    void saveToFile(std::ofstream& file, int index) const;
};

#endif