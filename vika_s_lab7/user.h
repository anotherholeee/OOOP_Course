#ifndef USER_H
#define USER_H

#include <string>
#include <memory>

class User {
protected:
    std::string fio;
    std::string faculty;
    int groupNum;
    
public:
    User();
    User(std::string fio, std::string faculty, int groupNum);
    User(const User& copy);
    virtual ~User() = default;

    std::string getFio() const;
    std::string getFaculty() const;
    int getGroupNum() const;

    void setFio(const std::string& newFio);
    void setFaculty(const std::string& newFaculty);
    void setGroupNum(int newGroupNum);
};

#endif