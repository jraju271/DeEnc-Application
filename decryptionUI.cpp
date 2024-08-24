#ifndef DECRYPTION_UI_CPP
#define DECRYPTION_UI_CPP
#include "decryptionUI.hpp"
#include "decrypt.cpp"

void decrypt()
{
    system("CLS");

    do
    {
        system("CLS");
        cout << "Select the preferred option or press '0' to back: \n1. Type the message to decrypt\n2. Manual decryption from .txt file\
        \n3. Automatic decryption from .txt file\n--> ";
        int decryptionType; cin >> decryptionType;

        while(decryptionType != 0 && decryptionType != 1 && decryptionType != 2 && decryptionType != 3)
        { cout << "Enter a valid option! (0-3): "; cin >> decryptionType; }

        if(!decryptionType) return;
        decrypt_postDecryptionType(decryptionType);
    } while(true);

} 

void decrypt_postDecryptionType(const int decryptionType)
{
    system("CLS");
    string toBeDecrypted("");
    string fileName;
    string password;
    Decrypt *obj1 = NULL;
    ifstream file;
    bool fileGood = true;

    if(decryptionType == 1)
    {
        cout << "Enter the message you want to decrypt: " << endl; getchar();
        
        getline(cin, toBeDecrypted);
        obj1 = new Decrypt(toBeDecrypted);
    }

    else
    {
        system("CLS");
        fileGood = true;
        cout << "Enter file name (Preferably along with directory): "; getchar();
        getline(cin, fileName);
        file.open(fileName);

        while(!file.is_open())
        {
            cout << "Either no such file exists in the specified directory or file doesn't have enough permissions. Kindly try again: ";
            getline(cin, fileName);
            file.close();
            file.open(fileName);
        }

        if(decryptionType == 2)
        {
            try { obj1 = new Decrypt(file); }
            catch(const FileEmptyException& fee) { cout << fee.what() << endl; fileGood = false; file.close(); system("PAUSE"); }
            catch(const AutomaticDecryptionException& ade) { cout << ade.what() << endl; fileGood = false; file.close(); system("PAUSE"); }
            catch(const InsufficientPermissionsException& ipe) { cout << ipe.what() << endl; fileGood = false; file.close(); system("PAUSE"); }
        }

        else
        {
            cout << "Enter the password for this file: "; getline(cin, password);

            try { obj1 = new Decrypt(file, password); }
            catch(const FileEmptyException& fee) { cout << fee.what() << endl; fileGood = false; file.close(); system("PAUSE"); }
            catch(const ManualDecryptionException& mde) { cout << mde.what() << endl; fileGood = false; file.close(); system("PAUSE"); }
            catch(const InsufficientPermissionsException& ipe) { cout << ipe.what() << endl; fileGood = false; file.close(); system("PAUSE"); }
            catch(const PasswordMismatchException& pme) { cout << pme.what() << endl; fileGood = false; file.close(); system("PAUSE"); }
        }
            
        file.close();
        if(!fileGood) return;
    }

    decrypt_postDecryptionType_cipherSelection(obj1, decryptionType);
}

void decrypt_postDecryptionType_cipherSelection(Decrypt *obj, const int dType)
{
    char loopChoice;
    if(dType == 2 || dType == 1)
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
                        string uniqueCode; cout << "Enter unique code: "; getchar(); getline(cin, uniqueCode);
                        while(uniqueCode.front() != '!' || uniqueCode.back() != '-')
                        {
                            cout << "This is not the proper code. Try again: "; getchar();
                            getline(cin, uniqueCode);
                            uniqueCode = "!" + uniqueCode;
                        }
                        obj->route(uniqueCode);
                    }
                    break;
            
                default: cout << "Enter a valid option!"; break;
            }

            cout << "Want to decrypt once again? (y/n): ";
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
        cout << "Select the preferred option or press '0' to exit:\n1. Display the decrypted contents\n2. Write the decrypted contents to file\n--> ";
        int writeChoice; cin >> writeChoice;

        while(writeChoice != 0 && writeChoice != 1 && writeChoice != 2)
        { cout << "Enter a valid option! (0/1/2): "; cin >> writeChoice; }

        switch(writeChoice)
        {
            case 0:
                delete obj;
                exit(0);
                
            case 1:
                cout << "Decrypted contents are given below: " << endl; obj->display();
                break;
            
            case 2:
            {
                cout << "Enter the file to write into (If the file has contents, they'll be erased): ";
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

                obj->writeIntoFile(file);
                file.close();
            } break;

            default: cout << "Enter a valid option!"; break;
        }
        system("PAUSE");

    }

}

#endif