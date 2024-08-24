#include "master.hpp"
#include "misc.cpp"
#include "__exceptions.cpp"
#include "encryptionUI.cpp"
#include "decryptionUI.cpp"

void mainMenu();

int main(void)
{
    
    while(true) mainMenu();
    return 0;
}

void mainMenu()
{
    system("CLS");
    cout << setfill('*') << setw(120) << "*" << endl;
    cout << setfill(' ') << setw(65) << "DeEnc v0.1" << endl;
    cout << setfill('*') << setw(120) << "*" << setfill(' ') << endl;
    cout << setfill(' ') << setw(75) << "Select what you'd like to do:" << endl << endl;
    cout << setw(65) << "1. Encrypt" << endl;
    cout << setw(65) <<"2. Decrypt" << endl;
    cout << setw(62) <<"3. Help" << endl;
    cout << setw(63) <<"4. About" << endl;
    cout << setw(62) <<"5. Exit" << endl;
    cout << setw(59) <<"--> ";
    int mainMenuChoice; cin >> mainMenuChoice;

    switch (mainMenuChoice)
    {
        case 1:
            encrypt();
            break;
        
        case 2:
            decrypt();
            break;

        case 3:
            help();
            break;

        case 4:
            about();
            break;

        case 5:
            exit(0);
            break;

        default:
            cout << "Enter a valid choice!" << endl;
            system("PAUSE");
            break;
    }
}