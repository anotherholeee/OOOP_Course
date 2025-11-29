#include "user.h"

User::User() : groupNum(0) {}

User::User(std::string fio, std::string faculty, int groupNum)
    : fio(std::move(fio)), faculty(std::move(faculty)), groupNum(groupNum) {}

std::string User::getFio() const { return fio; }
std::string User::getFaculty() const { return faculty; }
int User::getGroupNum() const { return groupNum; }

void User::setFio(const std::string& newFio) {
    if (!newFio.empty()) {
        fio = newFio;
    }
}

void User::setFaculty(const std::string& newFaculty) {
    if (!newFaculty.empty()) {
        faculty = newFaculty;
    }
}

void User::setGroupNum(int newGroupNum) {
    if (newGroupNum >= 100000 && newGroupNum <= 999999) {
        groupNum = newGroupNum;
    }
}