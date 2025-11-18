#ifndef BOX_H
#define BOX_H

#include<iostream>

class Box {
private:
    int length, width, height;

public:
    Box();
    Box(int l, int w, int h);
    Box(const Box& copy);

    int area() const;
    int perimetr() const;
    int capacity() const;
    void show_info() const;
};

void get_info(int &l, int &w, int &h);
void box_info(const Box &box);

#endif