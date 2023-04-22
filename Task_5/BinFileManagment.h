#pragma once
#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

using namespace std;

struct Product
{
    int code;
    char name[32];

    void readProductFromLine(std::string& line)
    {
        std::stringstream input(line);
        input >> this->code;
        input >> this->name;
    }

    void writeProductInLine(std::string& line)
    {
        line = "";
        line += std::to_string(this->code);
        line += ' ';
        for (int i = 0; i < sizeof(this->name) / sizeof(char); i++)
        {
            if ((int)this->name[i] > 64 && (int)this->name[i] < 123)
            {
                line += this->name[i];
            }
            else
            {
                break;
            }
        }
    }
};

class BinFileManagment
{
public:

    static bool ConvertTextToBinary(std::string fileName)
    {
        ifstream file;
        file.open(fileName + ".txt", ios::in);
        if (!file.is_open())
        {
            return false;
        }
        ofstream newBinaryFile;
        newBinaryFile.open("bin" + fileName + ".dat", ios::binary | ios::out | ios::trunc);

        string line;
        Product inputProduct;


        while (!file.eof()) {
            getline(file, line);
            inputProduct.readProductFromLine(line);
            newBinaryFile.write((char*)&inputProduct, sizeof(Product));
        }

        if (!newBinaryFile.good())
        {
            return false;
        }

        file.close();
        newBinaryFile.close();
        return true;
    }

    static std::string LinearSearch(std::string fileName, int key)
    {
        ifstream binFile;
        binFile.open(fileName + ".dat", ios::binary | ios::in);
        if (!binFile.is_open())
        {
            return "";
        }
        Product product;
        string line = "";
        binFile.read((char*)&product, sizeof(Product));
        while (!binFile.eof())
        {
            if (product.code == key)
            {
                product.writeProductInLine(line);
                break;
            }
            binFile.read((char*)&product, sizeof(Product));
        }
        binFile.close();
        return line;
    }

    static bool ReadBinValueByIndex(std::string fileName, int index, std::string& line)
    {
        ifstream binFile;
        binFile.open(fileName + ".dat", ios::binary | ios::in);
        if (!binFile.is_open() || index < 1)
        {
            return false;
        }

        Product product;
        binFile.seekg((index - 1) * sizeof(Product), ios::beg);
        binFile.read((char*)&product, sizeof(Product));
        product.writeProductInLine(line);

        if (!binFile.good())
        {
            return false;
        }

        binFile.close();
        return true;
    }

    static bool AppendValueToBinFile(std::string fileName, std::string& productString)
    {
        ifstream binFile;
        binFile.open(fileName + ".dat", ios::binary | ios::in);
        if (!binFile.is_open())
        {
            cout << "Файл не открыт!\n" << endl;
            return false;
        }
        binFile.close();

        ofstream addBinFile;
        addBinFile.open(fileName + ".dat", ios::binary | ios::out | ios::app);

        Product product;
        product.readProductFromLine(productString);
        addBinFile.write((char*)&product, sizeof(Product));

        if (!addBinFile.good())
        {
            cout << "Ошибка записи!\n" << endl;
            return false;
        }
        addBinFile.close();
        return true;
    }

    static void CreateNewBinFile(std::string fileName, int numberOfLines)
    {
        ofstream binFile;
        binFile.open(fileName + ".dat", ios::trunc | ios::binary | ios::out);
        string productLine = "1 someProduct";
        Product product;
        product.readProductFromLine(productLine);
        for (int i = 100000; i < 100000 + numberOfLines; i++)
        {
            product.code = i;
            binFile.write((char*)&product, sizeof(Product));
        }
        if (!binFile.good())
        {
            cout << "Ошибка записи!\n" << endl;
            return;
        }
        binFile.close();
    }

    static void CreateNewTxtFile(std::string fileName, int numberOfLines)
    {
        ofstream file;
        file.open(fileName + ".txt", ios::trunc | ios::out);
        string productLine = "1 someProduct";
        Product product;
        product.readProductFromLine(productLine);

        product.code = rand() % 10000;
        product.writeProductInLine(productLine);
        file << productLine;
        for (int i = 100000; i < 100000 + numberOfLines; i++)
        {
            product.code = rand() % 1000;
            product.writeProductInLine(productLine);
            file << '\n' << productLine;
        }
        if (!file.good())
        {
            cout << "Ошибка записи!\n" << endl;
            return;
        }
        file.close();
    }
};