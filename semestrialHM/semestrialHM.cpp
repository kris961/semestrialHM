#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <iomanip>

using namespace std;
//Структура за дисциплините
struct discipline {
    char name[25]; //име на дисциплината
    int grade; //оценка за дисциплината
};

struct student {
    int facultyId=0;  //факултетен номер на студент
    char name[30]=""; //име на студент
    discipline disciplines[6];  //дисциплини на студента
    char sex[10]="";  //пол на студента
    int age=0; //възраст на студента
    char status[10]="";  //статус на студента
};

const int disciplinesCount = 6;  //броят на елементите в масива с дисциплини
const int groupCount = 30;  //броят на елементите в масива със студенти
const string fileName = "students.bin";  //име на файла в който се записват данните

int mainMenu(); //Визуализира главното меню
int addStudentMenu();//визуализира подменюто за добавяне на студенти
int printStudentsMenu(); //визуализира подменюто за извеждане на студенти
int gradesMenu(); //визуализира подменюто за добавяне и промяна на оценки
int allInfoMenu();//визуализира подменюто за справки за студенти

void createStudent(student group[]);//създава студент
void printStudents(student group[]); //извежда студентите
void findStudentByFn(student group[]);//извежда студентите с еднакви първи 6 цифри на факултетния номер
bool addGrades(int fn, student group []);//добавя оценки по специалностите
bool editGrades(int fn, student group[]);//променя оценките по специалностите
void changeStudentStatus(student group[]);//намира студент по факултетен номер и променя статуса му
void printStudentsAllInfo(student group[], string sex);//извежда всичката информация за студентите

student* sortByName(student group[]);//сортира студентите по имена в азбучен ред
student* sortByAgeDesc(student group[]);//сортира студентите по възраст в низходящ ред
student* sortByAgeAndSexAsc(student group[]);//сортира студентите от даден пол по възраст във възходящ ред
student findStudentWithBiggestAvg(student group[]);//намира студента с най-висок среден успех

void writeToFile(student group[]);//пише данни в двоичния файл
void readFromFile(student group[]);//чете данни от двоичния файл


int main()
{
    setlocale(LC_ALL, "Bulgarian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    bool hasChanges = false;//булева променлива която показва дали има промени които трябва да бъдат записани във файла
    bool end = false;//булева променлива която показва дали програмата трябва да приключи
    int code; //код който връщат менютата
    student def = { 0,"", {},"",0,"" };//структура която служи да стойност по подразбиране
    student group[30] = {def};//инициализира масив с 30 елемента и му задава стойност по подразбиране
    readFromFile(group);//чете данните от двоичния файл и ги попълва в масива
    while (end != true) { //цикълът се върти докато не се избере опция за край на програмата
        if (hasChanges) { //проверява дали има промени които трябва да се отрязат в двоичния файл
            writeToFile(group);//пише данни в двоичния файл
            hasChanges = false;//нулира променливата
        }
        code = mainMenu(); //визуализира се глваното меню и се връща избраната от потребителя опция
        switch (code)//според опцията се изпълняват опреденели действия
        {
        case 1: { //при избор на първа опция
                 int selection= addStudentMenu();//визуализира се менюто за добавяне на студенти и се връща избраната опция
                 if (selection==1)//при избора на първа опция от подменюто
                 {
                     createStudent(group);//създава се нов студент
                 }
                 else if (selection==2) //при избора на втората опция от подменюто
                 {
                     int n;
                     cout << "Въведете борят на студентите които искате да добавите." << endl;
                     cin >> n; //въвежда се броят на студентите които юе бъдат добавени
                     for (int i = 0; i < n; i++)//върти се цикъл до достигане на зададеният брой
                     {
                         createStudent(group);//суздава се нов студент
                         if (n-1>i)//ако току що въведеният студент не е последен ще може да се прекъсне въвеждането на следващ
                         cout << "Желаете ли да въведете следващ ученик?    yes/no" << endl;
                         string answer;
                         cin >> answer;//въвежда се отговорът
                         if (answer != "yes")//ако отговорът е yes въвеждането на следващ студент ще бъде прекратено
                             break;//прекратява се цикълът
                         system("CLS");//изчиства се конзолата
                     }
                 }
                 hasChanges = true;//има промяна която ще трябва да бъде отразено във файла
            break;
        }
        case 2: {//при втори избор от менюто
            int selection = printStudentsMenu();//визуализира се менюто за извеждане на студенти и се връща избора на потребителя
            if (selection ==1)//при първи избор от подменюто
                printStudents(group);//извеждат се всички студенти
            if (selection == 2)//при втори избор от подменюто
                findStudentByFn(group);//извеждат се всички студенти с еднакви първи 6 цифри от факултетния номер
            break;
        }
        case 3: {//при трети избор от менюто
            int selection = gradesMenu();//визуализира се менюто за оценки
            bool found;//показва дали е намерен студент
            int fn;
            if (selection == 1)//при първи избор от подменюто
            {
                do {

                    cout << "Въведете Факултетният номер на ученика." << endl;
                    cin >> fn;//въвежда се факултетния номер на студента който се търси
                    found = addGrades(fn, group);//въвеждат се оценките и се връща true. Ако не е намерен студент-false
                    if (found == false) {//ако не е намерен студента
                        cout << "Не присъства такъв студент в групата" << endl;
                        system("pause");//програмата спира до натискане на enter
                        break;
                    }
                } while (found == false);//въвежда се факултетен номер докато не бъде открит студент
            }
            if (selection == 2)//при втори избор от подменюто
            {
                cout << "Въведете Факултетният номер на ученика." << endl;
                cin >> fn;//въвежда се факултетния номер на студента който се търси
                found = editGrades(fn, group);//въвеждат се оценките и се връща true. Ако не е намерен студент-false
                if (found == false) {//ако не е намерен студента
                    cout << "Не присъства такъв студент в групата" << endl;
                    system("pause");//програмата спира до натискане на enter
                    break;
                }
            }
            hasChanges = true;//има промяна която ще трябва да бъде отразено във файла
            break;
        }
        case 4: {
            changeStudentStatus(group);//сменя се статуса на студент
            hasChanges = true;//има промяна която ще трябва да бъде отразено във файла
            break;
        }
        case 5: {
            int selection = allInfoMenu();//визуализира се подменюто за справки и се връща избраната от потребителя опция
            student* sorted;//показател който ще държи сортираната група от студенти
            if (selection==1)//при първи избор от подменюто
            {
                sorted = sortByName(group);//сортира студентите по збучен ред и го записва
                printStudentsAllInfo(sorted,"All");//принтира всички сортирани студенти
            }
            if (selection == 2)
            {
                sorted = sortByAgeDesc(group);//сортира студентите в низходящ ред
                printStudentsAllInfo(sorted,"All");//принтира всички сортирани студенти
            }
            if (selection == 3)
            {
                string sex;
                cout << "Въведете пола (Мъжки/Женски)";
                cin >> sex;//въвежда се пола на студентите които ще се изведат
                sorted = sortByAgeAndSexAsc(group);//студентите се сортират във възходящ ред
                printStudentsAllInfo(sorted,sex);//извеждат се всички сортирани студенти от дадения пол 
            }
            if (selection == 4)
            {
                student st = findStudentWithBiggestAvg(group);//връща студента с най-висок среден успех
                cout << setw(22) << left << "Име на студент" << setw(17) << left << "Факултетен номер " << setw(8) << left << "Пол" << setw(2) << left << " Възраст" << setw(19) << left << " Статус" << endl << endl;
                cout << setw(22) << left << st.name << setw(17) << st.facultyId << setw(9) << left << st.sex << setw(8) << left << st.age << setw(9) << left << st.status << endl;
                for (int j = 0; j < disciplinesCount; j++)//итерира през дисциплините на студента
                {
                    cout << st.disciplines[j].name << " - " << st.disciplines[j].grade << " ; ";
                }
                system("pause");
            }
            break;
        }
        case 0: {
            end = true;//при този избор програмата приключва
            continue;
            break;
        }
        default:
            continue;//при невалиден избор програмата продължава
            break;
        }
    }
    return 0;
}

//визуализира главното меню
int mainMenu(){
    system("CLS");//изчиства конзолата
    int selection = 0;//държи избора от потребителя
        cout << "Въведете числото отговарящо на съответният ред" << endl;
        cout << "1) Добавяне студенти в група." << endl;
        cout << "2) Извеждане на студенти." << endl;
        cout << "3) Въвеждане и промяна на оценки на студент." << endl;
        cout << "4) Смяна на статус на студент." << endl;
        cout << "5) Справки за студенти" << endl;
        cout << "0) Изход"<<endl;
        cin >> selection;//въвежда се избора на потребителя
        system("CLS");//изчиства конзолата
        return selection;//връща избора
}
//визуализира менюто за оценки
int gradesMenu() {
    int selection = 0;//държи избора от потребителя
    do {
        system("CLS");//изчиства конзолата
        cout << "Въведете числото отговарящо на съответният ред" << endl;
        cout << "1) Въвеждане на оценки на студент." << endl;
        cout << "2) Промяна на оценки на студент."<<endl;
        cout << "0) Назад" << endl;
        cin >> selection;//въвежда се избора на потребителя
        system("CLS");
    } while (selection > 2 || selection < 0);//върти цикъла докато не се въведе наличен избор
    return selection;//връща избора
}
//визуализира менюто за добавяне на студенти
int addStudentMenu() {
    int selection=0;//държи избора от потребителя
    do {
        cout << "Въведете числото отговарящо на съответният ред" << endl;
        cout << "1) Добавяне на студент." << endl;
        cout << "2) Добавяне на поредица от студенти." << endl;
        cout << "0) Назад."<<endl;
        cin >> selection;
        system("CLS");//изчиства конзолата
    } while (selection < 0 || selection>2);//върти цикъла докато не се въведе наличен избор
    return selection;//връща избора
}
//виауализира менюто за извеждане на студенти
int printStudentsMenu() {
    int selection = 0;//държи избора от потребителя
    do {
        cout << "Въведете числото отговарящо на съответният ред." << endl;
        cout << "1) Извеждане на всички студенти от групата." << endl;
        cout << "2) Извеждане на студенти с еднвакви пътви 6 цифри от факултетен номер." << endl;
        cout << "0) Назад." << endl;
        cin >> selection;
        system("CLS");//изчиства конзолата
    } while (selection < 0 || selection>2);//върти цикъла докато не се въведе наличен избор
    return selection;//връща избора
}
//визуализира менюто за справки за студенти
int allInfoMenu() {
    int selection = 0;//държи избора от потребителя
    do {
        system("CLS");//изчиства конзолата
        cout << "Въведете числото отговарящо на съответният ред." << endl;
        cout << "1) Извеждане на студентите по име." << endl;
        cout << "2) Извеждане на студентите по възраст." << endl;
        cout << "3) Извеждане на най-младите студенти по пол." << endl;
        cout << "4) Извеждане на студента с най-висок среден успех" << endl;
        cout << "0) Назад." << endl;
        cin >> selection;
        system("CLS");//изчиства конзолата
    } while (selection > 4 || selection < 0);//върти цикъла докато не се въведе наличен избор
    return selection;//връща избора
}
//създава нов студент
void createStudent(student group[]) {
    int facultyN;//държи факултетния номер на новия студент
    string name;//държи името на новия студент
    string sex;//държи пола на новия студент
    unsigned int age;//държи възрастта на новия студент
    try//прави се опит за изпълнение на кода в блока
    {
        cout << "Въвдете данните на студента в следния формат:" << endl;
        cout << "Факултетен номер" << endl;
        cin >> facultyN;//въвежда се факултетния номер
        cout << "Име" << endl;
        cin.ignore();//игнорира се '\n' от предишното въвеждане
        getline(cin, name);//чете се името на студента
        cout << "Пол" << endl;
        cin >> sex;//въвежда се пола на студента
        cout << "Възраст" << endl;
        cin >> age;//въвежда се възрастта на студента
    }
    catch (const std::exception&)//при грешка при въвеждане се изпълнява кода
    {
        cout << "Невалидни данни";
        return;
    }
    student newStudent;//създава се нов студента и се присвояват съответните стойности
    newStudent.facultyId = facultyN;
    strcpy_s(newStudent.name, name.c_str());
    strcpy_s(newStudent.sex, sex.c_str());
    string status = "учащ";
    strcpy_s(newStudent.status, status.c_str());
    newStudent.age = age;
    //създава се всяка от дисциплините и се присвоява
    newStudent.disciplines[0] = { "Електротехника" ,0};
    newStudent.disciplines[1] = { "Базово Програмиране", 0};
    newStudent.disciplines[2] = { "Общи Компютърни системи" , 0};
    newStudent.disciplines[3] = { "Математика" ,0};
    newStudent.disciplines[4] = { "Английски" ,0};
    newStudent.disciplines[5] = { "ССП" ,0};

    for (int i = 0; i < groupCount; i++)//върти се цикъл до достигане на дължината на масива
    {
        if (group[i].facultyId == 0) //когато се намери студент с факултетен номер по подразбиране се присвоява новият студент на празния
        {
            group[i] = newStudent;
            break;
        }
    }
}
//извежда всички студенти
void printStudents(student group[]) {
    int page = 1;//номера на текущата страница
    int start = 0;//началния индекс от който ще се извеждат студенти
    int end = 5;//последния индекс до който ще се извежда студенти
    int printed = 0;//броя на изведените студенти
    cout << "страница: " << page<<endl;
        cout << setw(26) << left << "Име на студент" << "факултетен номер" << endl;
        for (int i = 0; i < groupCount;i++)//върти цикъл до броя на елементите в масива
        {
            if (group[i].facultyId == 0)//ако студента има факултетен номер по подразбиране, той се прескача
                continue;
            cout << printed+1 << ") " << setw(20) << left << group[i].name << " - " << setw(10) << group[i].facultyId << endl;
            printed++;//увеличава броя на принтирани студентите
            if (printed%5==0)//на всеки 5 принтирани студента се изпълнява следния блок
            {
                system("pause");//програмата спира до натискане на enter
                system("CLS");//изчиства се конзолата
                page++;//увеличава се номера на страницата
                cout << "страница: " << page << endl;
                cout << setw(26) << left << "Име на студент" << "факултетен номер" << endl;
            }
        }
        if (printed == 0)//ако не са принтирани студенти
        {
            system("CLS");
            cout << "Няма налични студенти" << endl;
        }
    system("pause");//програмата спира до натискане на enter
}
//извежда справки за студентите които за подадени на функцията
void printStudentsAllInfo(student group[], string sex) {//аргиментите са масив от студенти които ще се принтират и полът на студентите които трябва да се изкарат
    int printed = 0;//държи броя на принтираните студенти
    cout << setw(25) << left << "Име на студент" <<setw(16)<<left<< "Факултетен номер "<<setw(8)<<left <<"Пол"<<setw(2)<<left<<" Възраст"<<setw(19)<<left<<" Статус"<< endl<<endl;

    for (int i = 0; i < groupCount;i++)//върти цикъл до достигане на броя на елементите с масива
    {
        if (group[i].facultyId == 0)//ако факултетния номер на студент е този по подразбиране, се пропуска
            continue;
        if (sex == "All")//ако като аргумент е подадено all се изпълнява следния блок
        {
            cout << printed + 1 << ") " << setw(22) << left << group[i].name << setw(17) << group[i].facultyId << setw(9) << left << group[i].sex << setw(8) << left << group[i].age << setw(9) << left << group[i].status << endl;
            for (int j = 0; j < disciplinesCount; j++)//върти се цикъл до достигане на броя на дисциплините
            {
                cout << group[i].disciplines[j].name << " - " << group[i].disciplines[j].grade << " ; ";
            }
            cout << endl << endl;
            printed++;//увеличава броя на принтирани студенти
        }
        else
        {
            if (group[i].sex != sex)//ако полът на студент не съвпада с поддаденият към финкцията, той се пропуска
                continue;
            cout << printed + 1 << ") " << setw(22) << left << group[i].name << setw(17) << group[i].facultyId << setw(9) << left << group[i].sex << setw(8) << left << group[i].age << setw(9) << left << group[i].status << endl;
            for (int j = 0; j < disciplinesCount; j++)//върти цикъл до достигане на броя на елементите с масива
            {
                cout << group[i].disciplines[j].name << " - " << group[i].disciplines[j].grade << " ; ";
            }
            cout << endl << endl;
            printed++;//увеличава броя на принтирани студенти
        }

    }
    if (printed == 0)//ако не са принтирани студенти
    {
        system("CLS");
        cout << "Няма налични студенти" << endl;
    }
    system("pause");//програмата спира до натискане на enter
}
//въвежда се има на студента и се променя статусът му
void changeStudentStatus(student group[]) {
    cout << "Въведете име на студента." << endl;
    char name[30];//държи името на студента
    cin.ignore();//игнорира '\n' от предишното въвеждане
    cin.getline(name, 30);//чете името от конзолата
    bool found = false;//показва дали е намрен студент
    for (int i = 0; i < groupCount; i++)//цикъла се изпълнява до достигане на броя на студенти
    {
        if (strcmp(group[i].name, name) == 0) {//ако името въведено от конзолата и името на текущия студент съвпадат се изпълнява следният блок
            strcpy_s(group[i].status, "завършил");//статусът на студента се променя
            system("CLS");//изчиства се конзолата
            cout << "Статуса на " << group[i].name << " е сменен успешно." << endl;
            found = true;//показва че търсеният студент е намерен
            break;
        }
    }
    if (!found)//ако не е намрен студент
    {
        system("CLS");//изчиства се конзолата
        cout << "Не е намерен такъв студент." << endl;
    }
    system("pause");//програмата спира до натискане на enter
}
//търси се студент по факултетен номер и връща дали е намерен и ако е се добавят оценки
bool addGrades(int fn, student group[]) {
    int stIndex=-1;//държи индекса на студента
    int addedGrades=0;//броят на добавени оценки
    for (int i = 0; i < groupCount; i++)//изпълнява се цикъл до достигане на броя на елементите на масива
    {
        if (group[i].facultyId == 0)//ако факултетният номер на студента е този по подразбиране, този студент се пропуска
            continue;
        if (group[i].facultyId == fn) //ако факултетния номер на студента съвпада с този въведен от конзолата
        {
            stIndex = i;//присвоя ва се индекса на студента към променливата
            break;//цикълът приключва
        }
    }
    if (stIndex==-1)//показва че не де намрен такъв студент и се връща резултата от търсенето
        return false;
    for (int i = 0; i < disciplinesCount; i++)//върти се цикъл до броя на дисциплините
    {
        if (group[stIndex].disciplines[i].grade != 0)//ако студентът има оценка по тази дисциплината, то тя се пропуска
            continue;
        int grade;//държи се оценката
        string answer;//държи отговора
        cout << "Да се добави ли оцента по: " << group[stIndex].disciplines[i].name << "?    (yes/no)"<<endl;
        cin >> answer;//въвежда се отговора
        if (answer == "yes")//ако отговора е yes
        {
            cout << "Въведете оценка по: " << group[stIndex].disciplines[i].name << endl;
            cin >> grade;//въвежда се оценка
            group[stIndex].disciplines[i].grade = grade;//оценката се присвоява на сътоветната дисциплина
            addedGrades++;//броят на добавени оценки се увеличава
        }
        else
            continue; 
        system("CLS");//конзолата се изчиства
    }
    if (addedGrades == 0)//ако броят на добавени ценки е 0
        cout << "Всички оценки на студента са въведени!" << endl;
    else
        cout << "Оценките са въведени успешно!"<<endl;
    system("pause");//програма спира до натискане на enter
    return true;
}
//търи се студент по факултетен номер и връща дали е намерен и ако се променят оценките
bool editGrades(int fn, student group[]) {
    int stIndex = -1;//държи индекса на студента
    int editedGrades = 0;//броят на променените оценки
    for (int i = 0; i < groupCount; i++)//върти се цикъл до броят на студентите в масива
    {
        if (group[i].facultyId == 0)//ако факултетния номер на студента е този по подразбиране, то той се пропуска
            continue;
        if (group[i].facultyId == fn)//ако факултетният номер на студента съвпада с въведеният
        {
            stIndex = i;//индекса на студента
            break;
        }
    }
    if (stIndex == -1)//ако студента не е намрен
        return false;
    for (int i = 0; i < disciplinesCount; i++)//върти се цикъл до броя на дисциплините
    {
        int grade;//държи оценката
        string answer;//държи отговора
        if (group[stIndex].disciplines[i].grade==0)//ако студента няма оценка по тази дисциплина се пита дали да се добави
            cout << "Студента няма оценка по този предмет. Да се добави ли?  (yes/no)" << endl;
        else
            cout << "Да се промени ли оценката по: " << group[stIndex].disciplines[i].name << "? Текуща оценка: "<<group[stIndex].disciplines[i].grade<<"(yes/no)" << endl;
        cin >> answer;
        if (answer == "yes")//ако отговора е yes се добавя или променя оценка
        {
            cout << "Въведете оценка по: " << group[stIndex].disciplines[i].name << endl;
            cin >> grade;//въвежда се оценката
            group[stIndex].disciplines[i].grade = grade;//присвоява се въведенета оценка към съответната дисциплина
            editedGrades++;//увеличава се броя на променени оценки
        }
        else
            continue;
        system("CLS");//изчиства се конзолата
    }
    if (editedGrades == 0)//ако не са променяни оценки
        cout << "Не са направени промени по оценките на студента." << endl;
    else
        cout << "Оценките са променени успешно успешно!" << endl;
    system("pause");//програмата спира до натискане на enter
    return true;
}
//търсят се студенти с еднакви първи 6 цифри на факултетния номер 
void findStudentByFn(student group[]) {
    int fn;//факултетния номер
    do {
        cout << "Въведете първите 6 цифри от факултетен номер." << endl;
        cin >> fn;//въвежда се каултетен номер
    } while (fn > 999999 || fn < 100000);//кодът се повтаря до въвеждане на 6цифрено число
    system("CLS");//изчиства се конзолата

    cout << setw(26) << left << "Име на студент" << "факултетен номер" << endl;
    int count = 0;//държи броя на студентите с отговарящ факултетен номер
    for (int i = 0; i < groupCount; i++)
    {
        if (to_string(group[i].facultyId).substr(0,6)==to_string(fn))//ако първите 6 цифри на факултетния номер на студента съвпадат с въведените 6 цифри
        {
            count++;//увеличава се броя на намерени студенти
            cout << count << ") "<<setw(20)<<left << group[i].name << " - "<<setw(10) << group[i].facultyId<<endl;
        }
    }
    if (count==0)//ако не са намерени студенти
    {
        system("CLS");//изчиства се конзолата
        cout << "Не са намерени студенти с този факултетен номер!"<<endl;
    }
    system("Pause");//програмата спира до натискане на enter
    system("CLS");//изчиства се конзолата
}
//сортират се студентите по възраст възходящо
student* sortByAgeAndSexAsc(student group[]) {
    student temp;//пази стойността на един от студентите
    student* sorted = group;//масив от студентите(сортиран)
    for (int i = 0; i < groupCount; i++)
    {
        for (int j = i + 1; j < groupCount; j++)
        {
            if (sorted[i].age > sorted[j].age)//ако единият студент е по-млад, то двата студента се разменят
            {
                temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    return sorted;
}
//сортират се студентите по възраст в низходящ ред
student* sortByAgeDesc(student group[]) {
    student temp;//пази стойността на един от студентите
    student* sortedGroup = group;//масива от студентите
    for (int i = 0; i < groupCount; i++)
    {
        for (int j = i + 1; j < groupCount; j++)
        {
            if (sortedGroup[i].age < sortedGroup[j].age)//ако единият студент е по-възрастен, то те се разменят
            {
                temp = sortedGroup[i];
                sortedGroup[i] = sortedGroup[j];
                sortedGroup[j] = temp;
            }
        }
    }
    return sortedGroup;
}
//сортират се студентите по има в азбучен ред
student* sortByName(student group[]) {
    student temp;//пази стойността на един от студентите
    student* sorted = group;
    for (int i = 0; i < groupCount; i++)
    {
        for (int j = i + 1; j < groupCount; j++)
        {
            if (strcmp(sorted[i].name, sorted[j].name) > 0)//проверява кое име трябва да е първо и разменя студентите
            {
                temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    return sorted;
}
//намира и връща студента с най-висок среден успех
student findStudentWithBiggestAvg(student group[]) {
    int bestStudentIndex = 0;//пази индекса на студента с най-висок среден успех
    double biggestAverage = 0;
    for (int i = 0; i < groupCount; i++)
    {
        if (group[i].facultyId == 0)
            continue;
        int average = 0;
        for (int j = 0; j < disciplinesCount; j++)
        {
            average += group[i].disciplines[j].grade;//намира се сбора от оценките на студента
        }
        if (average > biggestAverage)//ако сбора на оценките на този студент е по-голям от този до сега, то той се присвоява като най-голям
        {
            biggestAverage = average;
            bestStudentIndex = i;
        }
    }
    return group[bestStudentIndex];//връща се студента с най-висок успех
}
//запазва данните в двоичен файл
void writeToFile(student group[30]) {
    fstream file;
    file.open(fileName, ios::binary | ios::out);//отваря се файла
    file.write((char*)group, groupCount * (sizeof(student)));//записват се данните от файла
    file.close();//затваре са файла
        //cout << "Неуспешно отваряне на фаила!" << endl;
}
//чете данни от двоичен файл
void readFromFile(student group[]) {
    fstream file;
    file.open(fileName, ios::binary | ios::in);//отваря се файл
    file.seekg(0L, ios::end);//слага се селектора в края на файла
    long pos = (long)file.tellg();//намира се размера до селектора
    file.seekg(0L, ios::beg);//слага се селектора в началото на файла
    file.close();//затваря се файла
    int n = pos / (sizeof(student));
    file.open(fileName, ios::binary | ios::in);//отваря се файл
    file.read((char*)group, n * (sizeof(student)));//чете се от файла
    file.close();//затваря се файла
}