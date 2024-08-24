#include "master.hpp"
#ifndef ENCRYPT_CPP
#define ENCRYPT_CPP
#include "__exceptions.cpp"
#include <iostream>
#include "decrypt.cpp"
#include "misc.cpp"
using namespace std;

class Encrypt
{
    private:
        string fileContents;
        string password;
        stack<string> ciphers;
        bool hasContent;
        bool preEncrypted;
        bool encryptable;
        bool isString;
    protected:
        bool checkPreEncryption();
    public:
        Encrypt() { hasContent = encryptable = preEncrypted = false; }
        Encrypt(ifstream &);
        Encrypt(string&);
        void shift(int);
        void caesar() { this->shift(-3); }
        void rot13() { this->shift(13); }
        void atBash();
        void route(const int);
        // void set(string& msg) { fileContents = msg; hasContent = encryptable = msg.empty(); preEncrypted = false; }
        void display() { cout << fileContents << endl; }
        void setPassword(const string& pw) { password = pw; }
        void writeIntoFile(ofstream &);
        void quickWrite(ofstream&);
        const string& getTopElement() const { return ciphers.top(); }
};

Encrypt :: Encrypt(string& str): fileContents(str), hasContent(!str.empty()), preEncrypted(false), encryptable(!str.empty()), password(""), isString(true) {} 
Encrypt :: Encrypt(ifstream &f)
{
    hasContent = encryptable = true;
    preEncrypted = !encryptable;
    if(f.peek() == ifstream::traits_type::eof()) { hasContent = false; encryptable = false; throw FileEmptyException(); }
    try
    {
        ostringstream contentsTemp;
        contentsTemp << f.rdbuf();
        fileContents = contentsTemp.str();
    } catch(...) { encryptable = false; throw InsufficientPermissionsException(); }
    if(checkPreEncryption()) { encryptable = false; throw PreEncryptedException(); }
    // password = pw;
}

void Encrypt :: shift(int key)
{
    if(!hasContent) throw FileEmptyException();
    else if(preEncrypted) throw PreEncryptedException();
    else if(!encryptable) throw NonEncryptableException();

    try
    {
        key = key % 26;
        if(key < 0) key = (key % 26) + 26;
        for(int i = 0; i < fileContents.length(); ++i)
        {
            char &current = fileContents.at(i);
            if(islower(current)) current = (current - 97 + key) % 26 + 97;
            else if(isupper(current)) current = (current - 65 + key) % 26 + 65;
        }
        string keyString = to_string(key);
        if(keyString.length() == 1) keyString = "0" + keyString;
        string code = to_string((rand() % 9000) + 1000) + to_string((rand() % 9000) + 1000);
        code = code.insert(4, keyString);
        ciphers.push(code);
    } catch(...) { encryptable = false; throw ImproperFileContentException(); }
}

void Encrypt :: atBash()
{
    if(!hasContent) throw FileEmptyException();
    else if(preEncrypted) throw PreEncryptedException();
    else if(!encryptable) throw NonEncryptableException();

    try
    {
    for(int i = 0; i < fileContents.length(); ++i)
    {
        char &current = fileContents.at(i);
        if(islower(current)) current = 219 - current;
        else if(isupper(current)) current = 155 - current;
    }
    string code = to_string((rand() % 9000) + 1000) + to_string((rand() % 9000) + 1000);
    ciphers.push(code);
    } catch(...) { encryptable = false; throw ImproperFileContentException(); }
}

void Encrypt :: route(const int key)
{
    if(!hasContent) throw FileEmptyException();
    else if(preEncrypted) throw PreEncryptedException();
    else if(!encryptable) throw NonEncryptableException();

    try
    {
        std::vector<std::vector<char>> matrix;
        std::vector<char> columns;
        std::string encodedString("");
        std::string forDecipher("");

        for(char &c: fileContents)
        {
            if(columns.size() == key)
            {
                matrix.push_back(columns);
                columns.clear();
            }
            columns.push_back(c);
        }

        if(!columns.empty()) { matrix.push_back(columns); }

        bool flag;
        int i, j;
        for(i = 0; i < matrix.at(0).size(); ++i)
        {
            for(j = 0; j < matrix.size(); ++j)
            {
                flag = false;
                try { encodedString += matrix.at(j).at(i); }
                catch(...){ flag = true; forDecipher.append(std::to_string(j) + '-'); }
            }
            if(!flag) forDecipher.append(std::to_string(j) + '-');
        }

        fileContents = encodedString;

        string code = '!' + forDecipher;
        ciphers.push(code);
    } catch(...) { encryptable = false; throw ImproperFileContentException(); }

}


void Encrypt :: writeIntoFile(ofstream &f)
{
    if(!hasContent) throw FileEmptyException();
    else if(preEncrypted) throw PreEncryptedException();
    else if(!encryptable) throw NonEncryptableException();
    
    try
    {
        f << fileContents << '\n';
        while(!ciphers.empty())
        {
            f << ciphers.top() << " ";
            ciphers.pop();
        }
        hash<string> pHash;
        f << '\n' << pHash(password);
    } catch(...) { throw UnWritableException(); }
}

bool Encrypt :: checkPreEncryption()
{
    if(!hasContent) throw FileEmptyException();
    else if(preEncrypted) throw PreEncryptedException();
    else if(!encryptable) throw NonEncryptableException();

    try
    {
        auto i = fileContents.rbegin();
        string pw;
        stack<char> pwStack;
        bool allGood = true;

        while (i != fileContents.rend())
        {
            if(*i == '\n') break;
            else pwStack.push(*i);
            i++;
        }
        
        while(!pwStack.empty())
        {
            pw += pwStack.top();
            pwStack.pop();
        }
        for(char &c: pw)
            if(!isdigit(c)) { allGood = false; break; }
        return allGood && (pw.length() >= 19);
    } catch(...) { encryptable = false; throw ImproperFileContentException(); }
}

void Encrypt :: quickWrite(ofstream& f) { f << fileContents << '\n'; }

#endif
