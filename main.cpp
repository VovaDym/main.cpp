//В начале каждого хода игроки вращают волчок, то есть выбирают сектор на столе, который сейчас играет. Всего таких секторов 13.
// Сектор выбирается так: с клавиатуры вводится офсет (смещение) относительно текущего сектора на барабане.
// Исходя из этого офсета вычисляется новый активный сектор, который и будет играть в этом ходе. Если выпавший сектор уже играл,
// выбирает следующий неигравший за ним. В начале всей игры стрелка установлена на первом секторе.
//Как только играет какой-то из секторов, с него берётся письмо с вопросом — то есть считывается из файла данного сектора.
// Вопрос показывается на экране.
//После того как вопрос показан, от игрока ожидается ответ на него. Игрок вводит этот ответ с помощью стандартного ввода.
// То, что он ввёл, сравнивается с ответом, который хранится во втором файле, ассоциированном с активным сектором.
// Данный файл должен содержать лишь одно слово-ответ.
//Если ответ знатока-игрока был правильным, ему начисляется один балл. Если неверен, то балл уходит телезрителям.
//Игра продолжается до тех пор, пока или игрок, или зрители не наберут шесть баллов.
// После этого называется победитель и программа заканчивает работу.
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

bool sectorCurrent (std::vector<int> &passedSectors,int n)
{
    bool sectorCurrent = true;
    for (int i = 0;i < passedSectors.size();++i)
    {
        if(passedSectors[i] == n)
        {
            sectorCurrent = false;
            break;
        }
    }
    return sectorCurrent;
}

int main() {
    int n = 0;
    int nSector = 1;
    std::vector <int> passedSectors;
    int audience = 0;
    int players = 0;
    while (passedSectors.size() < 13)
    {
        std::ifstream fileQuest ;
        fileQuest.open("Questions.txt");
        if(!fileQuest.is_open())
        {
            std::cout << "Error! FileQuestions is not open ";
            return 0;
        }
        std::cout << "Rotate turntable: " << std::endl;
        std::cin >> n;
        nSector = nSector + n;
        if(nSector > 13)
        {
            nSector = nSector % 13;
            if (nSector == 0) nSector = 1;
        }
        while(!(sectorCurrent(passedSectors,nSector)))
        {
            nSector++;
            if (nSector > 13 || nSector == 0) nSector = 1;
        }
        passedSectors.push_back(nSector);
        std::cout << " Sector: " << nSector << " << QUESTION!!! >>: ";
        std::string strQuest;
        for (int j = 1; j < nSector; j++)
        {
            fileQuest.ignore(256, '\n');// go to the desired line in the file
        }

        if (!fileQuest.eof())
        {
            getline(fileQuest, strQuest);
            std::cout << strQuest << std::endl;
        }
        fileQuest.close();
        std::cin.get();

        std::ifstream fileAnswer ;
        fileAnswer.open("Answers.txt");
        if(!fileAnswer.is_open())
        {
            std::cout << "Error! FileAnswers is not open ";
            return 0;
        }
        std::string answer;
        std::string strAnswer;
        std::cout << "Enter your answer: " << std::endl;
        std::cin >> answer;

        for (int j = 1; j < nSector; j++)
        {
            fileAnswer.ignore(256, '\n');// go to the desired line in the file
        }

        if (!fileAnswer.eof())
        {
            getline(fileAnswer, strAnswer);
            if(strAnswer == answer)
            {
                ++players;
                std::cout << "The answer is correct." << std::endl;
                std::cout << "The score << " << "Players "<< players << " : " << "Audience "<<audience << " >> "<<  std::endl;
            }
            else
            {
                ++audience;
                std::cout << "The answer is incorrect. Right answer: " << strAnswer << std::endl;
                std::cout << "The score << " << "Players "<< players << " : " << "Audience "<<audience << " >> "<<  std::endl;
            }
        }
        fileAnswer.close();
        std::cin.get();
        if (players == 6)
        {
            std::cout << "The players won! " << std::endl;
            break;
        }
        else if (audience == 6)
        {
            std::cout << "The audience won! " << std::endl;
            break;
        }
    }
    return 0;
}
