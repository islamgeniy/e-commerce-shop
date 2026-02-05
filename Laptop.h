// Laptop.h
#ifndef LAPTOP_H
#define LAPTOP_H

#include<iostream>
#include<string>

using namespace std;

//=========================//
//  Defining Paptop Class  //
//=========================//
class Laptop 
{

public:
    string name;
    string brand;
    double price;

    Laptop() {}

    //===================================//
    // Defining parametrized constructor //
    //===================================//
    Laptop(const string& n, const string& b, double p) : name(n), brand(b), price(p) {}

    void display(int index = -1) const 
    {
        if (index >= 0)
            cout << "   " << index + 1 << ". ";
        cout << brand << " - " << name << " ($" << price << ")\n";
    }
};

#endif // LAPTOP_H
