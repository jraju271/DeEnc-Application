#ifndef EXCPTNS_CPP
#define EXCPTNS_CPP
#include <exception>
#include<iostream>
#include "encrypt.cpp"
#include "decrypt.cpp"
#include "master.hpp"
using namespace std;


class PasswordMismatchException: std::exception
{
    public:
        const char * what() const noexcept
        {
            return "Password Mismatch detected";
        }
};


class NonDecryptableException: std::exception
{
    public:
        const char * what() const noexcept
        {
            return "The file cannot be decrypted";
        }
};

class FileEmptyException: std::exception
{
    public:
        const char * what() const noexcept
        {
            return "The file is empty";
        }
};

class TamperedException: std::exception
{
    public:
        const char * what() const noexcept
        {
            return "The file has been tampered with";
        }
};

class AutomaticDecryptionException: std::exception
{
    public:
        const char * what() const noexcept
        {
            return "The file is suitable for automatic decryption";
        }
};

class ManualDecryptionException: std::exception
{
    public:
        const char * what() const noexcept
        {
            return "The file is suitable for manual decryption";
        }
};



class InsufficientPermissionsException: std::exception
{
    public:
        const char * what() const noexcept
        {
            return "The file has insufficient permissions";
        }
};

class ImproperFileContentException: std::exception
{
    public:
        const char * what() const noexcept
        {
            return "The file has contents which are not suitable for modifications";
        }
};

class UnWritableException: std::exception
{
    public:
        const char * what() const noexcept
        {
            return "The contents cannot be written due to some error";
        }
};

class PreEncryptedException: std::exception
{
    public:
        const char * what() const noexcept
        {
            return "The contents are already encrypted";
        }
};

class NonEncryptableException: std::exception
{
    public:
        const char * what() const noexcept
        {
            return "The contents cannot be encrypted";
        }
};



#endif
