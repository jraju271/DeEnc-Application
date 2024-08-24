#ifndef ENCRYPTION_UI_CPP
#define ENCRYPTION_UI_CPP
#include "encryptionUI.hpp"
#include "encrypt.cpp"

void encrypt()
{
    system("CLS");

    do
    {
        system("CLS");
        cout << "Select the preferred option or press '0' to back: \n1. Type the message to encrypt\n2. Select a .txt file to encrypt\
    \n--> ";
        int fileOrNot; cin >> fileOrNot;

        while(fileOrNot != 0 && fileOrNot != 1 && fileOrNot != 2)
        { cout << "Enter a valid option! (0/1/2): "; cin >> fileOrNot; }

        if(!fileOrNot) return;
        encrypt_postFileOrNot(fileOrNot);
    } while(true);

} 

void encrypt_postFileOrNot(const int fileOrNot)
{
    system("CLS");
    string toBeEncrypted("");
    string fileName;
    string password;
    Encrypt *obj1 = NULL;
    ifstream file;
    bool fileGood = true;

    if(fileOrNot == 1)
    {
        cout << "Enter the message you want to encrypt: " << endl; getchar();
        
        getline(cin, toBeEncrypted);
        obj1 = new Encrypt(toBeEncrypted);
    }
    else
    {
        do
        {
            system("CLS");
            fileGood = true;
            cout << "Enter file name with extension (Preferably along with directory): "; getchar();
            getline(cin, fileName);
            file.open(fileName);

            while(!file.is_open())
            {
                cout << "Either no such file exists in the specified directory or file doesn't have enough permissions. Kindly try again: ";
                getline(cin, fileName);
                file.close();
                file.open(fileName);
            }


            try { obj1 = new Encrypt(file); }
            catch(const FileEmptyException& fee) { cout << fee.what() << endl; fileGood = false; file.close(); system("PAUSE"); }
            catch(const PreEncryptedException& pe) { cout << pe.what() << endl; fileGood = false; file.close(); system("PAUSE"); }
            catch(const InsufficientPermissionsException& ipe) { cout << ipe.what() << endl; fileGood = false; file.close(); system("PAUSE"); }
            
        } while(!fileGood);
        // cout << "Enter a password for the file: "; getline(cin, password);
        file.close();
    }

    encrypt_postFileOrNot_cipherSelection(obj1, fileOrNot);
}

void encrypt_postFileOrNot_cipherSelection(Encrypt *obj, const int fileOrNot)
{
    char loopChoice;
    do
    {
        system("CLS");
        __cipherChoice();
        int cipherChoice; cin >> cipherChoice;

        while(cipherChoice != 0 && cipherChoice != 1 && cipherChoice != 2 && cipherChoice != 3 && cipherChoice != 4 && cipherChoice != 5)
        { cout << "Enter a valid option! (0-5): "; cin >> cipherChoice; }

        if(!cipherChoice)
        {
            delete obj;
            return;
        }

        switch(cipherChoice)
        {                
            case 1:
                {
                    int key; cout << "Enter key: "; cin >> key;
                    obj->shift(key);
                }
                break;
            
            case 2:
                obj->caesar();
                break;
            
            case 3:
                obj->rot13();
                break;
            
            case 4:
                obj->atBash();
                break;
            
            case 5:
                {
                    int key; cout << "Enter key: "; cin >> key;
                    obj->route(key);
                    cout << "Kindly note this unique code down if you're planning for manual decryption: " << obj->getTopElement() << endl;
                }
                break;
        
            default: cout << "Enter a valid option!"; break;
        }

        cout << "Want to add more \"layers\" of encryption? (y/n): ";
        cin >> loopChoice;

        while(loopChoice != 'y' && loopChoice != 'Y' && loopChoice != 'n' && loopChoice != 'N')
        {
            cout << "Couldn't recognise the input, try again! (y/n): ";
            cin >> loopChoice;
        }
    } while(loopChoice == 'y' || loopChoice == 'Y');

    while(true)
    {
        system("CLS");
        cout << "Select the preferred option or press '0' to exit:\n1. Display the encrypted contents\n2. Write to file for automatic decryption\
        \n3. Write to file for manual decryption\n--> ";
        int writeChoice; cin >> writeChoice;

        while(writeChoice != 0 && writeChoice != 1 && writeChoice != 2 && writeChoice != 3 && writeChoice != 4)
        { cout << "Enter a valid option! (0-4): "; cin >> writeChoice; }

        switch(writeChoice)
        {
            case 0:
                delete obj;
                exit(0);
                
            case 1:
                cout << "Encrypted contents are given below: " << endl; obj->display();
                break;
            
            case 2:
            {
                cout << "Enter the file (with extension) to write into (If the file has contents, they'll be erased): ";
                string fileName; getline(cin, fileName);
                getline(cin, fileName);

                ofstream file(fileName);

                while(!file.is_open())
                {
                    cout << "Either no such file exists in the specified directory or file doesn't have enough permissions. Kindly try again: ";
                    getline(cin, fileName);
                    file.close();
                    file.open(fileName);
                }

                string pw;
                cout << "Enter a password for the file: "; getline(cin, pw);
                obj->setPassword(pw);

                obj->writeIntoFile(file);
                file.close();
            } break;

            case 3:
            {
                cout << "Enter the file (with extension) to write into (If the file has contents, they'll be erased): ";
                string fileName; getline(cin, fileName);
                getline(cin, fileName);

                ofstream file(fileName);

                while(!file.is_open())
                {
                    cout << "Either no such file exists in the specified directory or file doesn't have enough permissions. Kindly try again: ";
                    getline(cin, fileName);
                    file.close();
                    file.open(fileName);
                }

                obj->quickWrite(file);
                file.close();
            } break;

            default: cout << "Enter a valid option!"; break;
        }
        system("PAUSE");

    }
}

#endif