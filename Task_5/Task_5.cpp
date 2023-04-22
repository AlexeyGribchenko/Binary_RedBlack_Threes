#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <chrono>
#include "BinaryTree.h"
#include "RBTree.h"

using namespace std;


int main()
{
    setlocale(0, "ru");

    string result;
    string fileName;
    int choice = -1;
    int key, position;
    int numberOfElems;
    BinaryTree binTree;
    RBTree rbTree;

    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();

    BinFileManagment::CreateNewBinFile("binFile", 100);
    BinFileManagment::CreateNewTxtFile("txtFile", 40);

    while (choice != 0)
    {
        system("cls");
        cout << "Практическая работа №5. \"Сбалансированные деревья поиска\" Грибченко А. Ю. Вариант 6";
        cout << "\nВыберите действие:\n";
        cout << "0 - Прекратить работу программы.\n";
        cout << "1 - Работа с бинарным файлом.\n";
        cout << "2 - Работа с бинарным деревом.\n";
        cout << "3 - Работа с красно-черным деревом.\n";
        cout << "4 - Тестирование операций над деревьями.\n";
        cout << "5 - Тестирование поиска.\n";
        cout << "---> ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "Введите имя файла: ";
            cin >> fileName;

            while (choice != 0)
            {
                system("cls");
                cout << "Практическая работа №5. \"Сбалансированные деревья поиска\"";
                cout << "Имя текущего файла: " + fileName;
                cout << "Выберите действие:\n";
                cout << "0 - Прекратить работу программы.\n";
                cout << "1 - Создать двоичный файл записей фиксированной длины из заранее подготовленных данных в текстовом файле.\n";
                cout << "2 - Найти и вывести запись в файле с помощью линейного поиска.\n";
                cout << "3 - Вывести запись по известному адресу в файле.\n";
                cout << "4 - Добавить новую запись в файл.\n";
                cout << "---> ";

                cin >> choice;

                switch (choice)
                {
                case 1:
                    if (BinFileManagment::ConvertTextToBinary(fileName))
                    {
                        fileName = "bin" + fileName;
                        cout << "\n\nБинарный файл " + fileName + " был создан\n\n";
                    }
                    else
                    {
                        cout << "\n\nОшибка работы с файлом!\n\n";
                    }
                    system("pause");
                    break;
                case 2:
                    cout << "\n\nВведите значение ключа для поиска:";
                    cin >> key;
                    result = BinFileManagment::LinearSearch(fileName, key);
                    if (result != "")
                    {
                        cout << "\n\nЗапись, найденная линейным поиском по файлу:\n";
                        cout << result << "\n\n";
                    }
                    else
                    {
                        cout << "\n\nЗапись не найдена!\n\n";
                    }
                    break;
                case 3:
                    cout << "\n\nВведите номер записи:";
                    cin >> key;
                    if (BinFileManagment::ReadBinValueByIndex(fileName, key, result))
                    {
                        cout << "\n\nЗапись под номером " << key << " :\n";
                        cout << result << "\n\n";
                    }
                    else
                    {
                        cout << "\n\nЗапись не найдена!\n\n";
                    }
                    break;
                case 4:
                    cout << "\n\nВведите новую запись:";
                    cin >> result;
                    if (BinFileManagment::AppendValueToBinFile(fileName, result))
                    {
                        cout << "\n\nЗапись " + result + " была добавлена\n\n";
                    }
                    else
                    {
                        cout << "\n\nОшибка работы с файлом!\n\n";
                    }
                    break;
                default:
                    break;
                }
            }
            choice = -1;
            break;
        case 2:
            while (choice != 0)
            {
                system("cls");
                cout << "Практическая работа №5. \"Сбалансированные деревья поиска\"";
                cout << "Выберите действие:\n";
                cout << "0 - Прекратить работу программы.\n";
                cout << "1 - Построить дерево по существующему файлу.\n";
                cout << "2 - Добавить элемент в дерево.\n";
                cout << "3 - Поиск по ключу в дереве.\n";
                cout << "4 - Удалить элемент из дерева.\n";
                cout << "5 - Вывести дерево в консоль.\n";
                cout << "---> ";

                cin >> choice;

                switch (choice)
                {
                case 1:
                    cout << "\n\nВведите имя файла: \n\n";
                    cin >> fileName;
                    binTree.buildTreeByFile(fileName);
                    cout << "\n\nДерево было построено.\n\n";
                    system("pause");
                    break;
                case 2:
                    cout << "\n\nВведите ключ и значение: \n\n";
                    cin >> key >> position;
                    binTree.addElement(key, position);
                    cout << "\n\nНовый узел с ключом " << key << " и значением " << position << " был добавлен.\n\n";
                    system("pause");
                    break;
                case 3:
                    cout << "\n\nВведите ключ: \n\n";
                    cin >> key;
                    position = binTree.findElementByKey(key);
                    if (position != -1)
                    {
                        cout << "\n\nЗначение узла с ключом " << key << ": " << position << ".\n\n";
                    }
                    else
                    {
                        cout << "\n\nКлюч не найден!\n\n";
                    }
                    system("pause");
                    break;
                case 4:
                    cout << "\n\nВведите ключ: \n\n";
                    cin >> key;
                    if (binTree.deleteElementByKey(key))
                    {
                        cout << "\n\nУзел с ключом " << key << "успешно удален.\n\n";
                    }
                    else
                    {
                        cout << "\n\nКлюч не найден!\n\n";
                    }
                    system("pause");
                    break;
                case 5:
                    cout << "\n\n";
                    binTree.printTree();
                    cout << "\n\n";
                    system("pause");
                    break;
                default:
                    break;
                }
            }
            choice = -1;
            break;
        case 3:
            while (choice != 0)
            {
                system("cls");
                cout << "Практическая работа №5. \"Сбалансированные деревья поиска\"";
                cout << "Выберите действие:\n";
                cout << "0 - Прекратить работу программы.\n";
                cout << "1 - Построить дерево по существующему файлу.\n";
                cout << "2 - Добавить элемент в дерево.\n";
                cout << "3 - Поиск по ключу в дереве.\n";
                cout << "4 - Удалить элемент из дерева.\n";
                cout << "5 - Вывести дерево в консоль.\n";
                cout << "---> ";

                cin >> choice;

                switch (choice)
                {
                case 1:
                    cout << "\n\nВведите имя файла: \n\n";
                    cin >> fileName;
                    rbTree.buildTreeByFile(fileName);
                    cout << "\n\nДерево было построено.\n\n";
                    system("pause");
                    break;
                case 2:
                    cout << "\n\nВведите ключ и значение: \n\n";
                    cin >> key >> position;
                    rbTree.addElement(key, position);
                    cout << "\n\nНовый узел с ключом " << key << " и значением " << position << " был добавлен.\n\n";
                    system("pause");
                    break;
                case 3:
                    cout << "\n\nВведите ключ: \n\n";
                    cin >> key;
                    position = rbTree.findElementByKey(key);
                    if (position != -1)
                    {
                        cout << "\n\nЗначение узла с ключом " << key << ": " << position << ".\n\n";
                    }
                    else
                    {
                        cout << "\n\nКлюч не найден!\n\n";
                    }
                    system("pause");
                    break;
                case 4:
                    cout << "\n\nВведите ключ: \n\n";
                    cin >> key;
                    if (rbTree.deleteElementByKey(key))
                    {
                        cout << "\n\nУзел с ключом " << key << "успешно удален.\n\n";
                    }
                    else
                    {
                        cout << "\n\nКлюч не найден!\n\n";
                    }
                    system("pause");
                    break;
                case 5:
                    cout << "\n\n";
                    rbTree.printTree();
                    cout << "\n\n";
                    system("pause");
                    break;
                default:
                    break;
                }
            }
            choice = -1;
            break;
        case 4:

            // конверт - создание 2 деревьев - вставка / поиск / удаление - линейный поиск в файле

            BinFileManagment::CreateNewTxtFile("txtFile", 15);
            BinFileManagment::ConvertTextToBinary("txtFile");
            
            // Бинарное дерево поиска
            cout << "Бинарное дерево поиска, построенное по бинарному файлу\n" << endl;
            binTree.buildTreeByFile("bintxtFile");
            binTree.printTree();
            cout << "\n\n\n";

            cout << "Вставляем 750 в бинарное дерево\n" << endl;
            binTree.addElement(750, -1);
            binTree.printTree();
            cout << "\n\n\n";

            cout << "Вставляем 10000 в бинарное дерево\n" << endl;
            binTree.addElement(10000, -1);
            binTree.printTree();
            cout << "\n\n\n";

            cout << "Ищем по ключу 3811 в бинарном дереве" << endl;
            cout << binTree.findElementByKey(3811) << endl;
            cout << "\n\n\n";

            cout << "Ищем по ключу 547 в бинарном дереве" << endl;
            cout << binTree.findElementByKey(547) << endl;
            cout << "\n\n\n";

            cout << "Удаляем 3811 из бинарного дерева\n" << endl;
            binTree.deleteElementByKey(3811);
            binTree.printTree();
            cout << "\n\n\n";

            cout << "Удаляем 547 в бинарного дерева\n" << endl;
            binTree.deleteElementByKey(547);
            binTree.printTree();
            cout << "\n\n\n";

            // Красно черно дедерево
            cout << "Красно черное дерево, построенное по бинарному файлу\n" << endl;
            rbTree.buildTreeByFile("bintxtFile");
            rbTree.printTree();
            cout << "\n\n\n";

            cout << "Вставляем 36 в красно черное дерево\n" << endl;
            rbTree.addElement(36, -1);
            rbTree.printTree();
            cout << "\n\n\n";

            cout << "Вставляем 35 в красно черное дерево\n" << endl;
            rbTree.addElement(35, -1);
            rbTree.printTree();
            cout << "\n\n\n";

            cout << "Ищем по ключу 3811 в красно черном дереве (позиция в файле)" << endl;
            cout << rbTree.findElementByKey(3811) << endl;
            cout << "\n\n\n";

            cout << "Ищем по ключу 547 в красно черном дереве (позиция в файле)" << endl;
            cout << rbTree.findElementByKey(547) << endl;
            cout << "\n\n\n";

            cout << "Удаляем 644 (корень) из красно-черного дерева дерева\n" << endl;
            rbTree.deleteElementByKey(644);
            rbTree.printTree();
            cout << "\n\n\n";

            cout << "Удаляем 664 из красно-черного дерева дерева\n" << endl;
            rbTree.deleteElementByKey(664);
            rbTree.printTree();
            cout << "\n\n\n";

            cout << "Удаляем 37 из красно-черного дерева дерева\n" << endl;
            rbTree.deleteElementByKey(37);
            rbTree.printTree();
            cout << "\n\n\n";
            system("pause");
            break;
        case 5:
            numberOfElems = 899999;

            cout << "\nКоличество записей: " << numberOfElems << ".\n\n";
            BinFileManagment::CreateNewBinFile("bigFile", numberOfElems);

            start = chrono::steady_clock::now();
            rbTree.buildTreeByFile("bigFile");
            end = chrono::steady_clock::now();
            cout << "\nВремя заполнения красно-черного дерева: " << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.f << " мс\n" << endl;

            start = chrono::steady_clock::now();
            binTree.buildTreeByFile("bigFile");
            end = chrono::steady_clock::now();
            cout << "\nВремя заполнения бинарного дерева: " << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.f << " мс" << endl;

            // линейный поиск
            start = chrono::steady_clock::now();
            BinFileManagment::LinearSearch("bigFile", 100000);
            end = chrono::steady_clock::now();
            cout << "Время поиска записи в начале файла линейным поиском: " << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.f << " мс" << endl;

            start = chrono::steady_clock::now();
            BinFileManagment::LinearSearch("bigFile", 100000 + numberOfElems / 2);
            end = chrono::steady_clock::now();
            cout << "Время поиска записи в середине файла линейным поиском: " << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.f << " мс" << endl;

            start = chrono::steady_clock::now();
            BinFileManagment::LinearSearch("bigFile", 100000 + numberOfElems);
            end = chrono::steady_clock::now();
            cout << "Время поиска записи в конце файла линейным поиском: " << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.f << " мс" << endl;

            // бин дерево
            cout << "\n\n";
            start = chrono::steady_clock::now();
            binTree.findElementByKey(100000);
            end = chrono::steady_clock::now();
            cout << "Время поиска записи в начале файла по бинарному дереву: " << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.f << " мс" << endl;

            start = chrono::steady_clock::now();
            binTree.findElementByKey(100000 + numberOfElems / 2);
            end = chrono::steady_clock::now();
            cout << "Время поиска записи в середине файла по бинарному дереву: " << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.f << " мс" << endl;

            start = chrono::steady_clock::now();
            binTree.findElementByKey(100000 + numberOfElems);
            end = chrono::steady_clock::now();
            cout << "Время поиска записи в конце файла по бинарному дереву: " << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.f << " мс" << endl;

            // красно черное дерево
            cout << "\n\n";
            start = chrono::steady_clock::now();
            rbTree.findElementByKey(100000);
            end = chrono::steady_clock::now();
            cout << "Время поиска записи в начале файла по красно-черному дереву: " << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.f << " мс" << endl;

            start = chrono::steady_clock::now();
            rbTree.findElementByKey(100000 + numberOfElems / 2);
            end = chrono::steady_clock::now();
            cout << "Время поиска записи в середине файла по красно-черному дереву: " << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.f << " мс" << endl;

            start = chrono::steady_clock::now();
            rbTree.findElementByKey(100000 + numberOfElems);
            end = chrono::steady_clock::now();
            cout << "Время поиска записи в конце файла по красно-черному дереву: " << chrono::duration_cast<chrono::microseconds>(end - start).count() / 1000.f << " мс\n" << endl;
            system("pause");
            break;
        case 6:
            cout << "\nОпределим среднее число поворотов при вставке ключей в красно-черное дерево при его формировании из двоичного файла.\n\n";
            BinFileManagment::CreateNewBinFile("veryBigFile", 500000);
            rbTree.buildTreeByFile("veryBigFile");

            cout << "Общее число узлов в дереве: 500000\n";
            cout << "Общее число выполненных поворотов при вставке: " << numberOfRotates << "\n";
            cout << "Среднее число поворотов при вставке узла в красно-черно дерево: " << (float)numberOfRotates / 500000.f << "\n\n";
            system("pause");
            break;
        default:
            break;
        }
    }
    return 0;
}
