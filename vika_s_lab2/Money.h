#ifndef MONEY_H
#define MONEY_H

#include<iostream>

#define MAX 1000000


class Money {
private:
    long rubles;
    int copeykas;
    void normalize() ;

public:
    Money();
    Money(int r, int c);
    Money(const Money &m);
    ~Money();

    long getRubles() const;
    int getCopeykas() const;
    void setRubles(long r);
    void setCopeykas(int k);

    operator float() const;

    Money operator*(float f) const;
    friend Money operator*(float f, const Money& money);
    Money operator+(const Money &other) const ;
    Money operator-(const Money &other) const;
    Money& operator=(const Money &other) ;

    bool operator == (const Money &other) const ;

    friend std::ostream& operator<<(std::ostream& os, const Money& money);
    friend std::istream& operator>>(std::istream& is, Money& money);

};


#endif //MONEY_H
