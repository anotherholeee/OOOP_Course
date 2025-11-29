#include "user.h"

User::User() : groupNum(0) {}

User::User(string fio, string faculty, int groupNum) 
    : fio(std::move(fio)), faculty(std::move(faculty)), groupNum(groupNum) {}

User::User(const User& copy) 
    : fio(copy.fio), faculty(copy.faculty), groupNum(copy.groupNum) {}

User::~User() = default;

string User::getFio() const { return fio; }
string User::getFaculty() const { return faculty; }
int User::getGroupNum() const { return groupNum; }

void User::setFio(const string& newFio) {
    if (!newFio.empty()) {
        fio = newFio;
    }
}

void User::setFaculty(const string& newFaculty) {
    if (!newFaculty.empty()) {
        faculty = newFaculty;
    }
}

void User::setGroupNum(int newGroupNum) {
    if (newGroupNum >= 100000 && newGroupNum <= 999999) {
        groupNum = newGroupNum;
    }
}