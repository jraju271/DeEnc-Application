#ifndef MISC_CPP
#define MISC_CPP
#include "misc.hpp"

void help()
{
    system("CLS");
    cout << endl << endl << endl;
    string line1("HOLA! Welcome to DeEnc v0.1*!");

    string line2("Encryption: \"Encryption\" basically is some process or algorithm (known as a cipher) to make information hidden or secret.");
    string line3("Decryption: It's the opposite of encryption. The algorithm used in this case is called a decipher.");
    string enc1("1. Encrypt: This option will encrypt your contents, i.e., it will make the contents hidden");
    string enc2("\t You can choose from multiple algorithms (ciphers)");
    string enc3("\t You can either type the message to encrypt yourself, or you can encrypt the contents of a text (.txt) file as well!");
    string enc4("\t You can then \"layer\" the ciphers on top of another!");
    string enc5("\t You also select from manual or automatic decryption process. If you choose manual, then the receiver would have to\n\
    \tmanually enter the deciphers. Automatic means that the user just needs to select the file to decrypt. The rest will be taken care of by DeEnc.");

    string  dec1("2. Decrypt: This option will decrypt your contents. You need to choose from manual or automatic decryption (explained above)");

    string devStageMsg("*The software, as the version number suggests, is still in its early development stage. As a result, bugs might pop up. Kindly report them :)");

    cout << line1 << endl << endl;
    cout << line2 << endl;
    cout << line3 << endl;

    cout << endl;

    cout << enc1 << endl;
    cout << enc2 << endl;
    cout << enc3 << endl;
    cout << enc4 << endl;
    cout << enc5 << endl;

    cout << endl;

    cout << dec1 << endl;

    cout << endl;

    cout << devStageMsg << endl;

    cout << endl;

    __backOrNot();
    return;
}

void about()
{

    system("CLS");
    cout << endl << endl << endl;
    cout << "Team No.: 26" << endl;
    cout << "Team members: Shubham Ghosh (7155 19 104 047)\n\t Vankateshwaran M (7155 19 104 057)" << endl;
    cout << "Time taken for completion: 21 days" << endl;
    cout << "Finished on: 15/11/2020" << endl;
    cout << "Written in: C++" << endl;
    cout << "Data structures used: Stack, linked list, queue, array (vector) etc." << endl;
    cout << "No. of lines of code: 1100+ spanned over 11 files" << endl << endl;
    __backOrNot();
    return;
}

void __cipherChoice()
{
    system("CLS");
    cout << "Enter the cipher you'd like to use or press '0' to back: " << endl;
    cout << "1. Shift\n2. Caesar\n3. Rot13\n4. AtBash\n5. Route\n--> ";
}

void __backOrNot()
{
    cout << "Press 'b' for back: "; getchar();
    char backOrNot = getchar();
    
    while(backOrNot != 'b' && backOrNot != 'B')
    {
        cout << "Couldn't recognise the input, try again! "; getchar();
        backOrNot = getchar();
    }
}

#endif