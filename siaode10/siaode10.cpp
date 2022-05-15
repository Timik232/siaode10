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
#include <regex>
using namespace std;
//1)
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
//2)
void badChar(string str, int badchar[256])
{
    int i;

    // заполним все вхождения как -1
    for (i = 0; i < 256; i++)
        badchar[i] = -1;

    // заполним буквы, которые есть в шаблоне
    for (i = 0; i < str.length(); i++)
    {
        badchar[(int)str[i]] = i;
        //cout << badchar[(int)str[i]] << " " << (int)str[i] << endl;
    }
}

vector <string> mur_search(string text, string shab,char first)
{
    int m = shab.length();
    int n = text.length();
    vector <string> found;
    int badchar[256]; //массив из стоп-символов (их аски-номеров)

    badChar(shab, badchar); //заполняем массив

    int s = 0; // s это позиция последнего вхождения
    while (s <= (n - m))
    {
        int j = m - 1;

        while (j >= 0 && shab[j] == text[s + j])
            j--;

        if (j < 0)
        {
            
            if (text[s + j] >= '0' && text[s + j] <= '9') //последний символ названия был равен цифре
            {
                while (text[s + j] != ',' && s + j > 0)
                    j--;
                string buf = "";
                if (text[s + j + 1] == first)//первый символ названия был равен нужной букве
                {
                    j++;
                    while (text[s+j]!=',' && s+j < n)
                    {
                        buf += text[s + j];
                        j++;
                    }
                    found.push_back(buf);
                    buf = "";
                }

            }
            //cout << "\n pattern occurs at shift = " << s;
            s += (s + m < n) ? m - badchar[text[s + m]] : 1; //если длина смещения вместе с длиной шаблона меньше, чем длина текста, то 
                                                             // прибавляем к смещению длину оставшихся от шаблона цифр

        }

        else
            s += max(1, j - badchar[text[s + j]]); //второе значение – это чтобы сместились на размер вхождения шаблона .txt
    }
    return found;
}
int main()
{
    setlocale(LC_ALL, "Russian");
    string text = "слова есть, палиндромы есть? Есть. Например? Например: \n шабаш \n шиш \n шш \n ыгы язя оно ими 151";
    vector <string> words;
    words = Words(text);
    int nomer[100];
    int count = 0;
    cout << "The longest palindrome: " << max_Palindrom(words, nomer, count) << endl;
    string files = "ho0me.txt,thund.exe,state.txt,korm2.txt,sobaka.png,cat.jpeg,course100.txt,krot8.txt";
    char first = 'k'; //первый символ, который ищем в слове (может быть любым)
    words.clear();
    string fir = to_string(first);
    cout << "Found files:";
    string shab = ".txt";
    words = mur_search(files, shab,first);
    for (int i = 0; i < words.size(); i++)
        cout << words[i] << " ";
}

