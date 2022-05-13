// siaode10.cpp : 
/*1) Назовем строку палиндромом, если она
одинаково читается слева направо и справа налево.
Примеры палиндромов : "abcba", "55", "q", "xyzzyx".
Требуется для заданной строки найти максимальную
по длине ее подстроку, являющуюся палиндромом.
2) Дан текст, содержащий имена файлов.Имена
разделяются запятыми.Найти имена текстовых
файлов, в имени которых последний символ цифра, а
первый символ – заданная буква.

Эффективный
алгоритм Бойера
и Мура
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;
vector <string> Words(string sent) //разбить на слова
{
    vector <string> words;
    string buf = "";
    for (int i = 0; i < sent.size(); i++)
    {
        if (sent[i] != ',' && sent[i] != ' ' && sent[i] != '.')
        {
            buf += sent[i];
        }
        else
        {
            words.push_back(buf);
            buf = "";
        }
    }
    if (buf != "")
        words.push_back(buf);
    return words;
}
string max_Palindrom(vector <string> word, int nomer[100], int& count) // нахождение и вывод самого длинного палиндрома
{
    int maxpal = 0;
    int nomer_max = -1;
    for (int i = 0; i < word.size(); i++)
    {
        string obr = "";
        for (int j = word[i].size() - 1; j >= 0; j--)
        {
            obr.push_back(word[i][j]);
        }
        //cout << obr << " " << word[i] << endl; //вывод обратных слов для проверки
        if (obr == word[i])
        {
            nomer[count] = i;
            count += 1;
            if (word[i].size() > maxpal)
            {
                maxpal = word[i].size();
                nomer_max = i;
            }
        }
    }
    if (nomer_max != -1)
        return word[nomer_max];
    else return "[none]";
}
int main()
{
    setlocale(LC_ALL, "Russian");
    string text = "слова есть, палиндромы есть? Есть. Например? Например: \n шабаш \n шалаш \n шамаш шиш шорош шш ыгы язя оно ими";
    vector <string> words;
    words = Words(text);
    int nomer[100];
    int count = 0;
    cout << "The longest palindrome: " << max_Palindrom(words, nomer, count);
    string files = "home.txt,war thunder.exe,state1.txt,korm2.txt,sobaka.png,cat.jpeg,course100.txt";

}

