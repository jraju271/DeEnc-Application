#ifndef DECRYPT_CPP
#define DECRYPT_CPP
#include <queue>
#include <algorithm>
#include "master.hpp"
#include "__exceptions.cpp"
#include <iostream>
#include "encrypt.cpp"
#include "misc.cpp"
using namespace std;
	

class Decrypt
{
    private:
        stack<string> ciphers;
        string fileContents;
        string actualFileContents;
        bool passwordVerified;
        bool hasContent;
        bool decryptable;
        int dType; // 0: string, 1: manual, 2: automatic
    protected:
        bool checkPassword(const string&);
        void extractActualContents();
        void decrypt();
    public:
        void shift(int);
        void caesar() { this->shift(-3); }
        void rot13() { this->shift(13); }
        void atBash();
        void route(string&);
        Decrypt(ifstream &, const string&);
        Decrypt(ifstream &);
        Decrypt(string& str): actualFileContents(str), passwordVerified(true), hasContent(!str.empty()), decryptable(!str.empty()), dType(0) {}
        void writeIntoFile(ofstream& f);
        void display() { cout << actualFileContents << endl; }
};

Decrypt :: Decrypt(ifstream& f)
{
    dType = 1;
    passwordVerified = hasContent = decryptable = true;
    if(f.peek() == ifstream::traits_type::eof()) { hasContent = decryptable = false; throw FileEmptyException(); }
    try
    {
        ostringstream contentsTemp;
        contentsTemp << f.rdbuf();
        actualFileContents = contentsTemp.str();
    } catch(...) { decryptable = false; throw InsufficientPermissionsException(); }
    
    if(*(actualFileContents.rbegin()) != '\n') throw AutomaticDecryptionException();

    actualFileContents.pop_back();

}

Decrypt :: Decrypt(ifstream &f, const string& pw)
{
    // if(pw == "101486705044280") dType = 1;
    dType = 2;
    passwordVerified = hasContent = decryptable = true;
    if(f.peek() == ifstream::traits_type::eof()) { hasContent = decryptable = false; throw FileEmptyException(); }
    try
    {
        ostringstream contentsTemp;
        contentsTemp << f.rdbuf();
        fileContents = contentsTemp.str();
    } catch(...) { decryptable = false; throw InsufficientPermissionsException(); }
    passwordVerified = checkPassword(pw);
    if(*(fileContents.rbegin()) == '\n') { decryptable = false; throw ManualDecryptionException(); }
    if(!passwordVerified) { decryptable = false; throw PasswordMismatchException(); }
    extractActualContents();
    decrypt();
}

void Decrypt :: shift(int key)
{   
    if((!passwordVerified) && dType == 2) throw ManualDecryptionException();
    else if((!passwordVerified) && dType == 1) throw AutomaticDecryptionException();
    else if(!passwordVerified) throw PasswordMismatchException();
    else if(!hasContent) throw FileEmptyException();
    else if(!decryptable) throw NonDecryptableException();

    try
    {
        key *= -1;
        key = key % 26;
        if(key < 0) key = (key % 26) + 26;
        for(int i = 0; i < actualFileContents.length(); ++i)
        {
            char &current = actualFileContents.at(i);
            if(islower(current)) current = (current - 97 + key) % 26 + 97;
            else if(isupper(current)) current = (current - 65 + key) % 26 + 65;
        }
    } catch(...) { decryptable = false; throw ImproperFileContentException(); }
}

void Decrypt :: atBash()
{
    if((!passwordVerified) && dType == 2) throw ManualDecryptionException();
    else if((!passwordVerified) && dType == 1) throw AutomaticDecryptionException();
    else if(!passwordVerified) throw PasswordMismatchException();
    else if(!hasContent) throw FileEmptyException();
    else if(!decryptable) throw NonDecryptableException();

    try
    {
        for(int i = 0; i < actualFileContents.length(); ++i)
        {
            char &current = actualFileContents.at(i);
            if(islower(current)) current = 219 - current;
            else if(isupper(current)) current = 155 - current;
        }
    } catch(...) { decryptable = false; throw ImproperFileContentException(); }
}

void Decrypt :: route(string& decipherPattern)
{
    if((!passwordVerified) && dType == 2) throw ManualDecryptionException();
    else if((!passwordVerified) && dType == 1) throw AutomaticDecryptionException();
    else if(!passwordVerified) throw PasswordMismatchException();
    else if(!hasContent) throw FileEmptyException();
    else if(!decryptable) throw NonDecryptableException();

    try
    {
        decipherPattern.erase(decipherPattern.begin());
        replace(decipherPattern.begin(), decipherPattern.end(), '-', ' ');
        vector<vector<char>> matrix;
        vector<char> column;
        string decodedString("");
        stringstream ss(decipherPattern);
        string buffer;
        ss >> buffer;

        for(const auto& c: actualFileContents)
        {
            column.push_back(c);
            if(column.size() == std::stoi(buffer)) { matrix.push_back(column); column.clear(); ss >> buffer; continue; }
        }

        if(!column.empty()) matrix.push_back(column);

        for(int i = 0; i < matrix.at(0).size(); ++i)
        {
            for(int j = 0; j < matrix.size(); ++j)
                try { decodedString += matrix.at(j).at(i); } catch(...) {}
        }

        actualFileContents = decodedString;
    } catch(...) { decryptable = false; throw ImproperFileContentException(); }
}


void Decrypt :: writeIntoFile(ofstream &f)
{
    if((!passwordVerified) && dType == 2) throw ManualDecryptionException();
    else if((!passwordVerified) && dType == 1) throw AutomaticDecryptionException();
    else if(!passwordVerified) throw PasswordMismatchException();
    else if(!hasContent) throw FileEmptyException();
    else if(!decryptable) throw NonDecryptableException();

    try { f << actualFileContents; } catch(...) { throw UnWritableException(); }    
}

bool Decrypt :: checkPassword(const string& p)
{
    if((!passwordVerified) && dType == 2) throw ManualDecryptionException();
    else if((!passwordVerified) && dType == 1) throw AutomaticDecryptionException();
    else if(!passwordVerified) throw PasswordMismatchException();
    else if(!hasContent) throw FileEmptyException();
    else if(!decryptable) throw NonDecryptableException();

    try
    {
        hash<string> pHash;
        string pw;
        stack<char> pwStack;

        auto i = fileContents.rbegin();
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

        // cout << pw.empty() << endl;
        return to_string(pHash(p)) == pw;
    } catch(...) { decryptable = false; throw TamperedException(); }
}

void Decrypt :: extractActualContents()
{
    if((!passwordVerified) && dType == 2) throw ManualDecryptionException();
    else if((!passwordVerified) && dType == 1) throw AutomaticDecryptionException();
    else if(!passwordVerified) throw PasswordMismatchException();
    else if(!hasContent) throw FileEmptyException();
    else if(!decryptable) throw NonDecryptableException();

    try
    {
        int count = 0;
        string :: reverse_iterator i;
        i = fileContents.rbegin();
        while(count != 2 && i != fileContents.rend())
        {
            if(*i == '\n') count++;
            i++;
        }
        string :: iterator i2;
        i2 = fileContents.begin();
        while (i2 != i.base())
        {
            actualFileContents.push_back(*i2);
            i2++;
        }
    } catch(...) { decryptable = false; throw ImproperFileContentException(); }
}

void Decrypt :: decrypt()
{
    if((!passwordVerified) && dType == 2) throw ManualDecryptionException();
    else if((!passwordVerified) && dType == 1) throw AutomaticDecryptionException();
    else if(!passwordVerified) throw PasswordMismatchException();
    else if(!hasContent) throw FileEmptyException();
    else if(!decryptable) throw NonDecryptableException();

    try
    {
        int count = 0;
        string :: reverse_iterator i;
        string :: iterator starting;
        string :: iterator ending;
        i = fileContents.rbegin();
        while(count != 2 && i != fileContents.rend())
        {
            if(*i == '\n') count++;
            if(*i == '\n' && count == 1) ending = i.base();
            i++;
        }
        starting = i.base();
        string cipherCodes(starting, ending);
        queue<string> cipherTokens;

        istringstream ss(cipherCodes);
        string token;
        while(ss >> token) cipherTokens.push(token);

        while(!cipherTokens.empty())
        {
            string currToken = cipherTokens.front();
            if(currToken.at(0) == '!') route(currToken);
            else if(currToken.length() == 10) shift(stoi(currToken.substr(4, 2)));
            else if(currToken.length() == 8) atBash();
        
            cipherTokens.pop();
        }
    } catch(...) { decryptable = false; throw TamperedException(); }
}

#endif
