#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <typeinfo>
#include <windows.h>
#include <iomanip>
using namespace std;

template<class Type>
void ShowAllInfo(int tempNum, string valueType, string binNum, string hexNum, float prototype, int size)
{
    HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
    int width1 = 62;
    int width2 = 75;

    Type num = prototype;
    Type* pdec = &num;

    unsigned char* p0 = (unsigned char*) pdec;

    SetConsoleTextAttribute(hwnd, 15);
    cout << "Input num: " << hexNum;

    for (int i = 0; i < hexNum.length(); i++, width1--);

    SetConsoleTextAttribute(hwnd, 4);
    cout << setw(width1) << "* decoding *" << endl;

    SetConsoleTextAttribute(hwnd, 15);
    cout << "Type: " << valueType;

    for (int i = 0; i < valueType.length(); i++, width2--);

    SetConsoleTextAttribute(hwnd, 14);
    cout << setw(width2) << "One-byte representation in memory: "; 
    
    for (int i = 0; i < size; i++)     
        cout <<
        hex << ((int) *(p0 + i) <= 15 ? "0" : "") <<
        hex << ((int) *(p0 + i)) << " ";

    cout << endl;

    SetConsoleTextAttribute(hwnd, 15);
    cout << "Size: " << size << " " << "byte" << endl;
    cout << "Memory address: 0x" << (void*) pdec << endl;
    cout << setprecision(25) << "Prototype: " << prototype << endl;


    SetConsoleTextAttribute(hwnd, 3);
    cout << "--------------------------------------" << endl;
}

void DefinePointerType(int tempNum, string valueType, string binNum, string hexNum, int size);

string ConvertDecToBin(unsigned long decNum, int size);
unsigned long ConvertHexToDec(string hexNum);
unsigned long ConvertBinToDec(string binNum); 

template<class Type1>
float CalculatePrototypeInputNum(string binNum, string hexNum)
{
    float prototype;

    if ((typeid(Type1) == typeid(float)) || (typeid(Type1) == typeid(double)))
    {
        string binShiftExp = "";
        string binMantissa = "";
        string intPartBinNum = "";
        string newBinMantissa;

        float fractionPart = 0;
        float intPartDecNum = 0;

        int decShiftExp;
        int Exp;

        for (int i = 1; i <= binNum.length(); i++)
        {
            if (i <= 8) binShiftExp += binNum[i];
            else binMantissa += binNum[i];
        }

        decShiftExp = ConvertBinToDec(binShiftExp);
        Exp = decShiftExp - 127;

        for (int i = 1; i <= Exp ; i++)
        {
            intPartBinNum += binNum[8 + i];
        }

        intPartBinNum = '1' + intPartBinNum;
        intPartDecNum = ConvertBinToDec(intPartBinNum);

        for (int i = Exp; i < binMantissa.length(); i++)
        {
            newBinMantissa += binMantissa[i];
        }

        for (int i = 0; i < newBinMantissa.length() - 1; i++)
        {
            fractionPart += (float) (newBinMantissa[i] - 48) * pow(2.0, -1 - i);
        }


        prototype = binNum[0] == '1' ? -1 * (intPartDecNum + fractionPart) : (intPartDecNum + fractionPart);
       
    }
    else
    {
        if (binNum[0] != '0')
        {
            prototype = (Type1) ConvertHexToDec(hexNum);
        }
        else
        {
            Type1 num = (Type1) ConvertHexToDec(hexNum);
            prototype = (float) num;
        }
    }

    return prototype;
}


int main()
{   
    ifstream fin("forOther.txt");

    string hexNum, valueType;
    int size;

    for (; !fin.eof(); )
    {
        fin >> valueType >> size >> hexNum;

        unsigned long decNum = ConvertHexToDec(hexNum);
        string binNum = ConvertDecToBin(decNum, size);

        DefinePointerType(decNum, valueType, binNum, hexNum, size);
    }

    fin.close();

    system("pause");
}


void DefinePointerType(int tempNum, string valueType, string binNum, string hexNum, int size)
{
    float prototype = 0;
    if (valueType == "uchar")
    {
        prototype = CalculatePrototypeInputNum<unsigned char>(binNum, hexNum);
        ShowAllInfo<unsigned char> (tempNum, valueType, binNum, hexNum, prototype, size);
        
    }
    else if (valueType == "char")
    {
        prototype = CalculatePrototypeInputNum<char>(binNum, hexNum);
        ShowAllInfo<char>(tempNum, valueType, binNum, hexNum, prototype, size);
    }
    else if (valueType == "ushort")
    {
        prototype = CalculatePrototypeInputNum<unsigned short>(binNum, hexNum);
        ShowAllInfo<unsigned short>(tempNum, valueType, binNum, hexNum, prototype, size);
    }
    else if (valueType == "short")
    {
        prototype = CalculatePrototypeInputNum<short>(binNum, hexNum);
        ShowAllInfo<short>(tempNum, valueType, binNum, hexNum, prototype, size);
    }
    else if (valueType == "uint")
    {
        prototype = CalculatePrototypeInputNum<unsigned int>(binNum, hexNum);
        ShowAllInfo<unsigned int>(tempNum, valueType, binNum, hexNum, prototype, size);
    }
    else if (valueType == "int")
    {
        prototype = CalculatePrototypeInputNum<int>(binNum, hexNum);
        ShowAllInfo<int>(tempNum, valueType, binNum, hexNum, prototype, size);
    }
    else if (valueType == "float")
    {
        prototype = CalculatePrototypeInputNum<float>(binNum, hexNum);
        ShowAllInfo<float>(tempNum, valueType, binNum, hexNum, prototype, size);
    } 
}


unsigned long ConvertHexToDec(string hexNum)
{
    int tempDigit;
    unsigned long decNum = 0;

    for (int i = 0; i < hexNum.length(); i++)
    {
        switch (hexNum[i])
        {
            case '0':
            tempDigit = 0;
            break;
            case '1':
            tempDigit = 1;
            break;
            case '2':
            tempDigit = 2;
            break;
            case '3':
            tempDigit = 3;
            break;
            case '4':
            tempDigit = 4;
            break;
            case '5':
            tempDigit = 5;
            break;
            case '6':
            tempDigit = 6;
            break;
            case '7':
            tempDigit = 7;
            break;
            case '8':
            tempDigit = 8;
            break;
            case '9':
            tempDigit = 9;
            break;
            case 'a':
            tempDigit = 10;
            break;
            case 'b':
            tempDigit = 11;
            break;
            case 'c':
            tempDigit = 12;
            break;
            case 'd':
            tempDigit = 13;
            break;
            case 'e':
            tempDigit = 14;
            break;
            case 'f':
            tempDigit = 15;
            break;
        }

        decNum += (unsigned long) (pow(16, hexNum.length() - 1 - i)) * tempDigit;
    }

    return decNum;
}


string ConvertDecToBin(unsigned long decNum, int size)
{
    string binNum1 = "";
    string binNum2 = "";

    for (; decNum > 0; decNum /= 2)
    {
        binNum1 += (char) ((char) ('0') + decNum % 2);
    }

    for (int i = binNum1.length() - 1; i >= 0; i--)
    {
        binNum2 += binNum1[i];
    }

    if (binNum2.length() < size * 8)
    {
        binNum2 = string((size * 8 - binNum2.length()), '0') + binNum2;
    }
    return binNum2;
}


unsigned long ConvertBinToDec(string binNum)
{
    unsigned long decNum = 0;
    for (int i = binNum.length() - 1, x = 0; i >= 0; i--, x++)
    {
        decNum += (unsigned long) (int(binNum[x]) - 48) * pow(2.0, i);
    }

    return decNum;
}
