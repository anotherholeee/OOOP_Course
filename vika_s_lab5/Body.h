#ifndef BODY_H
#define BODY_H

#include <string>

class Body {
private:
    std::string color;
public:
    explicit Body(std::string clr = "белый");
    void paint() const;
    virtual void inputInfo();
    std::string getColor() const;
    virtual ~Body() = default;
};

#endif