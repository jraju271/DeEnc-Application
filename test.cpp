#include "encrypt.cpp"
#include "decrypt.cpp"
#include<iostream>
#include "master.hpp"
using namespace std;

int main(void)
{
    ifstream f("d2.txt");
    Encrypt s1(f,"hello_world");
    s1.display();
    s1.atBash();
    s1.rot13();
    s1.shift(-3);
    s1.atBash();
    // s1.routeCipher(7);
    // s1.routeCipher(5);
    // // s1.atBash();
    // // s1.rot13();
    // // s1.shift(5);
    s1.display();
    // ofstream f2("temp.txt");
    // s1.writeIntoFile(f2);
    // f.close();
    // remove("d2.txt");
    // f2.close();
    // rename("temp.txt", "d2.txt");

    /*cout << endl << endl;

    ifstream fd("d2.txt");
    try{
    Decrypt d1(fd, "hello_world");
    // d1.shift(5);
    // d1.rot13();
    // d1.atBash();
    // d1.atBash();
    // d1.shift(-3);
    // d1.display();
    ofstream f2("temp.txt");
    d1.writeIntoFile(f2);
    fd.close();
    remove("d2.txt");
    f2.close();
    rename("temp.txt", "d2.txt");
    }
    catch(exception &e) { cout << e.what() << endl; }
    
    fd.close();


    // string s1 = "Hello";
    // string s2 = "Hello";
    // hash<string> h1;
    // hash<string> h2;
    // cout << h1(s1) << endl << h2(s2) << endl;

    return 0;*/
}
