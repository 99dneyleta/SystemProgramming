#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include <iostream>
#include <list>
#include <fstream>

std::string const OUT_FILE = "output.txt";
std::string const PATH_TO_FILE = "inputWords.txt";
std::string const META_STR = "ewT$";

bool isRegExp(std::string uStr) {
    bool out = false;
    int count = 0, numbersCount = 0;
    std::string exampleStr = META_STR;
    while(exampleStr.length() > 0 || uStr.length() > 0)
    {
        if(exampleStr[0] == '$')
        {
            if(uStr[0] >= '0' && uStr[0] <= '9')
            {
                while (uStr[0] >= '0' && uStr[0] <= '9')
                {
                    numbersCount++;
                    uStr.erase(uStr.begin());
                }
            }
            else
                return out;
            while(exampleStr[0] == '$')
            {
                count++;
                exampleStr.erase(exampleStr.begin());
            }
            if(count > numbersCount)
                return out;
        }
        else
        {
            while (exampleStr[0] != '$' || (uStr[0] >= '0' && uStr[0] <= 9)) {
                if(uStr[0] == exampleStr[0])
                {
                    exampleStr.erase(exampleStr.begin());
                    uStr.erase(uStr.begin());
                    if(exampleStr.length() == 0 && uStr.length() ==0)
                        return out = true;
                }
                else
                    return out;
            }
        }
        count = 0;
        numbersCount = 0;
    }
    out = true;
    return out;
    }



std::list<std::string> readFile() {
    std::list<std::string> wordsWithFile;
    std::string line = "";
    std::ifstream file;
    file.open(PATH_TO_FILE);
    while (file>>line)
        wordsWithFile.push_back(line);
    file.close();
    return wordsWithFile;
}



std::list<std::string> printToFile(std::list<std::string> words)
{
    std::list<std::string> rez;
    std::ofstream file;
    file.open(OUT_FILE);
    while (!words.empty())
    {
        file<<words.front();
        file<<" ";
        words.erase(words.begin());
    }
    
    
    return rez;
}




std::list<int> findIndexOfCorrect()
{
    int i = 0;
    std::list<int> rez;
    std::list<std::string> inputWords;
    bool isExp;
    inputWords = readFile();
    while (!inputWords.empty())
    {
        isExp = isRegExp(inputWords.front());
        if(isExp)
            rez.push_back(i);
        
        inputWords.pop_front();
        i++;
    }
    return rez;
}



std::list<std::string> correctWords(std::list<int> indexOfCorrectWords, std::list<std::string> inputWords)
{
    int position = 0;
    std::list<std::string> rez;
    while (!indexOfCorrectWords.empty())
    {
        if (indexOfCorrectWords.front() == position)
        {
            rez.push_back(inputWords.front());
            indexOfCorrectWords.erase(indexOfCorrectWords.begin());
        }
        inputWords.erase(inputWords.begin());
        position++;
    }
    return rez;
}


std::string changeInputString(std::list<int> correctWords, std::list<std::string> inputWords)
{
    int position = 0, count = 0;
    std::string out;
    std::string metaWord = META_STR;
    while (!inputWords.empty()) {
        if(correctWords.front() == position)
        {
            std::string element = inputWords.front();
            while (!element.empty())
            {
                if (element[0] >= '1' && element[0] <= '9')
                {
                    count++;
                    element.erase(element.begin());
                }
                else if (count != 0)
                {
                    if(metaWord.front() == '$' && metaWord[1] == '$')
                    {
                        while (metaWord[1] == '$')
                        {
                            count--;
                            out += '1';
                            metaWord.erase(metaWord.begin());
                        }
                    }
                    out += std::to_string(count);
                    count = 0;
                }
                else
                {
                    out+=element[0];
                    element.erase(element.begin());
                    metaWord.erase(metaWord.begin());
                }
            }
            correctWords.erase(correctWords.begin());
            if (count != 0)
            {
                out += std::to_string(count);
                count = 0;
            }
            out += " ";
        }
        else
            out += inputWords.front() + " ";
        inputWords.erase(inputWords.begin());
        position++;
    }
    return out;
}



int main(int argc, const char * argv[]) {
    //std::cout<<changeInputString(findIndexOfCorrect(), readFile());
    printToFile(correctWords(findIndexOfCorrect(), readFile()));
    //std::cout<<isRegExp("!$ty#$", "12qwerty#12");
    return 0;
}
