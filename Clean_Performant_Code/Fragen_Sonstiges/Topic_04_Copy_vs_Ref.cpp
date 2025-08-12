


#include <iostream>
#include <string_view>
#include <vector>
#include <algorithm>
#include <print>



class Person
{
private:
    std::string m_first;
    std::string m_last;

public:
    std::string getFirstName() const { // Kopie
        return m_first;
    }

    const std::string& getLastName() const { // Referenz
        return m_last;
    }

    // Ref. ist so lange gültig, wie das Objekt existiert
};

void tueWas(int n)
{
    int m = n;
}

void tueWasEx(const int& n)
{
    int m = n;
}

void rufeTueWasAuf()
{
    int x = 123;
    tueWas(x);
    tueWasEx(x);
}
