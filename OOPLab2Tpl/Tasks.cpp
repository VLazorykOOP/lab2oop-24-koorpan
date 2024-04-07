#include <iostream>
#include <fstream>
#include "Tasks.h"
#include "Examples.h"
#include <string>
using namespace std;

void MenuTask()
{
    setlocale(LC_CTYPE, "Ukr");
    cout << "     Menu Task   \n";
    cout << "    1.  Завдання 1  \n";
    cout << "    2.  Завдання 2(Дані виводяться в файл C:\Users\Віталій\source\repos\lab2oop-24-koorpan\OOPLab2Tpl) \n";
    cout << "    3.  Завдання 3(Відсутнє) \n";
    cout << "    4.  Завдання 4 \n";
    cout << "    5.  Приклади \n";
    cout << "    6.  Вийти \n";
}

void task1() {
    int a, b, c, d;
    cout << "Введіть значення a, b, c, d: ";
    cin >> a >> b >> c >> d;
    int result = (a << 5) + ((13 * a + (12 * c)) >> 6) - (b << 8) + (d << 7) - (c << 4) - (c << 1);
    int result1 = a * 34 + (13 * a + 12 * c) / 64 - b * 2560 + d * 127 - c * 18;
    cout << "Результат(1): " << result1 << endl;
    cout << "Результат(2): " << result1 << endl;
    system("pause");
}

void task2() {
    const int ROWS = 4;
    const int COLUMNS = 16;
    char s[ROWS][COLUMNS + 1]; // рядки тексту
    unsigned short sh_dat[ROWS * COLUMNS]; // масив для шифрованих даних
    unsigned short sd2[ROWS * COLUMNS]; // масив для розшифрованих даних

    //ввід тексту для шифрування
    cout << "Введіть текст для шифрування:" << endl;
    for (int i = 0; i < ROWS; i++) {
        cin.getline(s[i], COLUMNS + 1, '\n');
        //доповнення рядків пробілами до 16 символів
        int len = strlen(s[i]);
        for (int j = len; j < COLUMNS; j++) {
            s[i][j] = ' ';
        }
        s[i][COLUMNS] = '\0';
    }

    //шифр тексту
    int j = 0;
    for (int i = 0; i < ROWS; i++) {
        for (int l = 0; l < COLUMNS; l++) {
            unsigned short r = s[i][l] & 0xFF;  // аскіі-код букви
            r |= (i << 4) & 0x30;               // номер рядка
            r |= (l << 6) & 0xC0;               //позиція в рядку
            r |= ((s[i][l] >> 4) & 0x0F) << 10; //молодша частина аскіі-коду
            //обчис бітів парності
            unsigned short b1 = 0, b2 = 0;
            for (int k = 0; k < 4; k++) {
                if (r & (1 << k)) {
                    b1++;
                }
                if (r & (1 << (k + 4))) {
                    b2++;
                }
            }
            r |= (b1 % 2) << 14;
            r |= (b2 % 2) << 15;
            sh_dat[j] = r;
            j++;
        }
    }

    //запис шифр даних у бін файл
    ofstream ofsb("encrypted_data.bin", ios::out | ios::binary);
    ofsb.write((char*)sh_dat, ROWS * COLUMNS * sizeof(unsigned short));
    ofsb.close();

    //читання шифр даних з бін файлу
    ifstream ifs("encrypted_data.bin", ios::in | ios::binary);
    ifs.read((char*)sd2, ROWS * COLUMNS * sizeof(unsigned short));
    ifs.close();

    //розшифр даних
    char so[ROWS][COLUMNS + 1]; //розшифр текст
    for (int i = 0; i < ROWS * COLUMNS; i++) {
        unsigned short r = sd2[i];
        unsigned short b1 = (r >> 14) & 1;
        unsigned short b2 = (r >> 15) & 1;
        unsigned short c1 = r & 0x0F;
        unsigned short c2 = (r >> 10) & 0x0F;
        unsigned short n = (r >> 4) & 0x03;
        unsigned short m = (r >> 6) & 0x0F;
        //перевірка бітів парності
        bool valid = true;
        for (int k = 0; k < 4; k++) {
            if ((c1 & (1 << k)) != b1) {
                valid = false;
                break;
            }
            if ((c2 & (1 << k)) != b2) {
                valid = false;
                break;
            }
        }
        //розшифр рядка
        so[n][m] = c1 | (c2 << 4);
    }
    //запис розшифр тексту у файл
    ofstream ofst("decrypted_text.txt");
    for (int i = 0; i < ROWS; i++) {
        ofst << s[i] << endl;
    }
    ofst.close();
    cout << "Дані розшифровано та записано у decrypted_text.txt" << endl;
}
void task3()
{

}
void task4()
{
    unsigned int a, b;
    cout << "Введіть значення a та b: ";
    cin >> a >> b;
    unsigned int result = 0;
    while (b > 0) {
        if (b & 1) {
            result += a;
        }
        a <<= 1;
        b >>= 1;
    }
    cout << "Добуток a та b: " << result << endl;
    system("pause");
}