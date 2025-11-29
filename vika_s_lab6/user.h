#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
    string fio;
    string faculty;
    int groupNum;
public:
    User();
    User(string fio, string faculty, int groupNum);
    User(const User& copy);
    virtual ~User();

    string getFio() const;
    string getFaculty() const;
    int getGroupNum() const;

    void setFio(const string& newFio);
    void setFaculty(const string& newFaculty);
    void setGroupNum(int newGroupNum);
};

#endif