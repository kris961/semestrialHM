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
student* sortByAgeAndSexAsc(student group[], string sex);//сортира студентите от даден пол по възраст във възходящ ред
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
            readFromFile(group);//чете данни от двоичния файл
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
                sorted = sortByName(group);
                printStudentsAllInfo(sorted,"All");
            }
            if (selection == 2)
            {
                sorted = sortByAgeDesc(group);
                printStudentsAllInfo(sorted,"All");
            }
            if (selection == 3)
            {
                string sex;
                cout << "Въведете пола (Мъжки/Женски)";
                cin >> sex;
                sorted = sortByAgeAndSexAsc(group,sex);
                printStudentsAllInfo(sorted,sex);
            }
            if (selection == 4)
            {
                student st = findStudentWithBiggestAvg(group);
                cout << setw(22) << left << "Име на студент" << setw(17) << left << "Факултетен номер " << setw(8) << left << "Пол" << setw(2) << left << " Възраст" << setw(19) << left << " Статус" << endl << endl;
                cout << setw(22) << left << st.name << setw(17) << st.facultyId << setw(9) << left << st.sex << setw(8) << left << st.age << setw(9) << left << st.status << endl;
                for (int j = 0; j < disciplinesCount; j++)
                {
                    cout << st.disciplines[j].name << " - " << st.disciplines[j].grade << " ; ";
                }
                system("pause");
            }
            break;
        }
        case 6: {
            end = true;
            continue;
            break;
        }
        default:
            continue;
            break;
        }
    }
    return 0;
}

int mainMenu(){
    system("CLS");
    int selection = 0;
        cout << "Въведете числото отговарящо на съответният ред" << endl;
        cout << "1) Добавяне студенти в група." << endl;
        cout << "2) Извеждане на студенти." << endl;
        cout << "3) Въвеждане и промяна на оценки на студент." << endl;
        cout << "4) Смяна на статус на студент." << endl;
        cout << "5) Справки за студенти" << endl;
        cout << "6) Изход"<<endl;
        cin >> selection;
        system("CLS");
        return selection;
}

int gradesMenu() {
    int selection = 0;
    do {
        system("CLS");
        cout << "Въведете числото отговарящо на съответният ред" << endl;
        cout << "1) Въвеждане на оценки на студент." << endl;
        cout << "2) Промяна на оценки на студент."<<endl;
        cout << "3) Назад" << endl;
        cin >> selection;
        system("CLS");
    } while (selection > 3 || selection < 1);
    return selection;
}

int addStudentMenu() {
    int selection=0;
    do {
        cout << "Въведете числото отговарящо на съответният ред" << endl;
        cout << "1) Добавяне на студент." << endl;
        cout << "2) Добавяне на поредица от студенти." << endl;
        cout << "3) Назад."<<endl;
        cin >> selection;
        system("CLS");
    } while (selection < 1 || selection>3);
    return selection;
}

int printStudentsMenu() {
    int selection = 0;
    do {
        cout << "Въведете числото отговарящо на съответният ред." << endl;
        cout << "1) Извеждане на всички студенти от групата." << endl;
        cout << "2) Извеждане на студенти с еднвакви пътви 6 цифри от факултетен номер." << endl;
        cout << "3) Назад." << endl;
        cin >> selection;
        system("CLS");
    } while (selection < 1 || selection>3);
    return selection;
}

int allInfoMenu() {
    int selection = 0;
    do {
        system("CLS");
        cout << "Въведете числото отговарящо на съответният ред." << endl;
        cout << "1) Извеждане на студентите по име." << endl;
        cout << "2) Извеждане на студентите по възраст." << endl;
        cout << "3) Извеждане на най-младите студенти по пол." << endl;
        cout << "4) Извеждане на студента с най-висок среден успех" << endl;
        cout << "5) Назад." << endl;
        cin >> selection;
        system("CLS");
    } while (selection > 5 || selection < 1);
    return selection;
}

void createStudent(student group[]) {
    int facultyN;
    string name;
    string sex;
    unsigned int age;
    try
    {
        cout << "Въвдете данните на студента в следния формат:" << endl;
        cout << "Факултетен номер" << endl;
        cin >> facultyN;
        cout << "Име" << endl;
        cin.ignore();
        getline(cin, name);
        cout << "Пол" << endl;
        cin >> sex;
        cout << "Възраст" << endl;
        cin >> age;
    }
    catch (const std::exception&)
    {
        cout << "Невалидни данни";
    }
    student newStudent;
    newStudent.facultyId = facultyN;
    strcpy_s(newStudent.name, name.c_str());
    strcpy_s(newStudent.sex, sex.c_str());
    string status = "учащ";
    strcpy_s(newStudent.status, status.c_str());
    newStudent.age = age;

    newStudent.disciplines[0] = { "Електротехника" ,0};
    newStudent.disciplines[1] = { "Базово Програмиране", 0};
    newStudent.disciplines[2] = { "Общи Компютърни системи" , 0};
    newStudent.disciplines[3] = { "Математика" ,0};
    newStudent.disciplines[4] = { "Английски" ,0};
    newStudent.disciplines[5] = { "ССП" ,0};

    for (int i = 0; i < groupCount; i++)
    {
        if (group[i].facultyId == 0) {
            group[i] = newStudent;
            break;
        }
    }
}

void printStudents(student group[]) {
    int page = 1;
    int start = 0;
    int end = 5;
    int printed = 0;
    cout << "страница: " << page<<endl;
        cout << setw(26) << left << "Име на студент" << "факултетен номер" << endl;
        for (int i = 0; i < groupCount;i++)
        {
            if (group[i].facultyId == 0)
                continue;
            cout << printed+1 << ") " << setw(20) << left << group[i].name << " - " << setw(10) << group[i].facultyId << endl;
            printed++;
            if (printed%5==0)
            {
                system("pause");
                system("CLS");
                page++;
                cout << "страница: " << page << endl;
                cout << setw(26) << left << "Име на студент" << "факултетен номер" << endl;
                page++;
            }
        }
        if (printed == 0)
        {
            system("CLS");
            cout << "Няма налични студенти" << endl;
        }
    system("pause");
}

void printStudentsAllInfo(student group[], string sex) {
    int printed = 0;
    cout << setw(25) << left << "Име на студент" <<setw(16)<<left<< "Факултетен номер "<<setw(8)<<left <<"Пол"<<setw(2)<<left<<" Възраст"<<setw(19)<<left<<" Статус"<< endl<<endl;

    for (int i = 0; i < groupCount;i++)
    {
        if (group[i].facultyId == 0)
            continue;
        if (sex == "All")
        {
            cout << printed + 1 << ") " << setw(22) << left << group[i].name << setw(17) << group[i].facultyId << setw(9) << left << group[i].sex << setw(8) << left << group[i].age << setw(9) << left << group[i].status << endl;
            for (int j = 0; j < disciplinesCount; j++)
            {
                cout << group[i].disciplines[j].name << " - " << group[i].disciplines[j].grade << " ; ";
            }
            cout << endl << endl;
            printed++;
        }
        else
        {
            if (group[i].sex != sex)
                continue;
            cout << printed + 1 << ") " << setw(22) << left << group[i].name << setw(17) << group[i].facultyId << setw(9) << left << group[i].sex << setw(8) << left << group[i].age << setw(9) << left << group[i].status << endl;
            for (int j = 0; j < disciplinesCount; j++)
            {
                cout << group[i].disciplines[j].name << " - " << group[i].disciplines[j].grade << " ; ";
            }
            cout << endl << endl;
            printed++;
        }

    }
    if (printed == 0)
    {
        system("CLS");
        cout << "Няма налични студенти" << endl;
    }
    system("pause");
}

void changeStudentStatus(student group[]) {
    cout << "Въведете име на студента." << endl;
    char name[30];
    cin.ignore();
    cin.getline(name, 30);
    bool found = false;
    for (int i = 0; i < groupCount; i++)
    {
        if (strcmp(group[i].name, name) == 0) {
            strcpy_s(group[i].status, "завършил");
            system("CLS");
            cout << "Статуса на " << group[i].name << " е сменен успешно." << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        system("CLS");
        cout << "Не е намерен такъв студент." << endl;
    }
    system("pause");
}

bool addGrades(int fn, student group[]) {
    int stIndex=-1;
    int addedGrades=0;
    for (int i = 0; i < groupCount; i++)
    {
        if (group[i].facultyId == 0)
            continue;
        if (group[i].facultyId == fn) 
        {
            stIndex = i;
            break;
        }
    }
    if (stIndex==-1)
        return false;
    for (int i = 0; i < disciplinesCount; i++)
    {
        if (group[stIndex].disciplines[i].grade != 0)
            continue;
        int grade;
        string answer;
        cout << "Да се добави ли оцента по: " << group[stIndex].disciplines[i].name << "?    (yes/no)"<<endl;
        cin >> answer;
        if (answer == "yes")
        {
            cout << "Въведете оценка по: " << group[stIndex].disciplines[i].name << endl;
            cin >> grade;
            group[stIndex].disciplines[i].grade = grade;
            addedGrades++;
        }
        else
            continue; 
        system("CLS");
    }
    if (addedGrades == 0)
        cout << "Всички оценки на студента са въведени!" << endl;
    else
        cout << "Оценките са въведени успешно!"<<endl;
    system("pause");
    return true;
}

bool editGrades(int fn, student group[]) {
    int stIndex = -1;
    int editedGrades = 0;
    for (int i = 0; i < groupCount; i++)
    {
        if (group[i].facultyId == 0)
            continue;
        if (group[i].facultyId == fn)
        {
            stIndex = i;
            break;
        }
    }
    if (stIndex == -1)
        return false;
    for (int i = 0; i < disciplinesCount; i++)
    {
        int grade;
        string answer;
        if (group[stIndex].disciplines[i].grade==0)
            cout << "Студента няма оценка по този предмет. Да се добави ли?  (yes/no)" << endl;
        else
            cout << "Да се промени ли оценката по: " << group[stIndex].disciplines[i].name << "? Текуща оценка: "<<group[stIndex].disciplines[i].grade<<"(yes/no)" << endl;
        cin >> answer;
        if (answer == "yes")
        {
            cout << "Въведете оценка по: " << group[stIndex].disciplines[i].name << endl;
            cin >> grade;
            group[stIndex].disciplines[i].grade = grade;
            editedGrades++;
        }
        else
            continue;
        system("CLS");
    }
    if (editedGrades == 0)
        cout << "Не са направени промени по оценките на студента." << endl;
    else
        cout << "Оценките са променени успешно успешно!" << endl;
    system("pause");
    return true;
}

void findStudentByFn(student group[]) {
    int fn;
    do {
        cout << "Въведете първите 6 цифри от факултетен номер." << endl;
        cin >> fn;
    } while (fn > 999999 || fn < 100000);
    system("CLS");

    cout << setw(26) << left << "Име на студент" << "факултетен номер" << endl;
    int count = 0;
    for (int i = 0; i < groupCount; i++)
    {
        if (to_string(group[i].facultyId).substr(0,6)==to_string(fn))
        {
            count++;
            cout << count << ") "<<setw(20)<<left << group[i].name << " - "<<setw(10) << group[i].facultyId<<endl;
        }
    }
    if (count==0)
    {
        system("CLS");
        cout << "Не са намерени студенти с този факултетен номер!"<<endl;
    }
    system("Pause");
    system("CLS");
}

student* sortByAgeAndSexAsc(student group[], string sex) {
    student temp;
    student* sorted = group;
    for (int i = 0; i < groupCount; i++)
    {
        for (int j = i + 1; j < groupCount; j++)
        {
            if (sorted[i].age > sorted[j].age)
            {
                temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    return sorted;
}

student* sortByAgeDesc(student group[]) {
    student temp;
    student* sortedGroup = group;
    for (int i = 0; i < groupCount; i++)
    {
        for (int j = i + 1; j < groupCount; j++)
        {
            if (sortedGroup[i].age < sortedGroup[j].age)
            {
                temp = sortedGroup[i];
                sortedGroup[i] = sortedGroup[j];
                sortedGroup[j] = temp;
            }
        }
    }
    return sortedGroup;
}

student* sortByName(student group[]) {
    student temp;
    student* sorted = group;
    for (int i = 0; i < groupCount; i++)
    {
        for (int j = i + 1; j < groupCount; j++)
        {
            if (strcmp(sorted[i].name, sorted[j].name) > 0)
            {
                temp = sorted[i];
                sorted[i] = sorted[j];
                sorted[j] = temp;
            }
        }
    }
    return sorted;
}

student findStudentWithBiggestAvg(student group[]) {
    int bestStudentIndex = 0;
    double biggestAverage = 0;
    for (int i = 0; i < groupCount; i++)
    {
        if (group[i].facultyId == 0)
            continue;
        int average = 0;
        for (int j = 0; j < disciplinesCount; j++)
        {
            average += group[i].disciplines[j].grade;
        }
        if (average > biggestAverage)
        {
            biggestAverage = average;
            bestStudentIndex = i;
        }
    }
    return group[bestStudentIndex];
}

void writeToFile(student group[30]) {
    fstream file;
    file.open(fileName, ios::binary | ios::out);
    file.write((char*)group, groupCount * (sizeof(student)));
    file.close();
        //cout << "Неуспешно отваряне на фаила!" << endl;
}

void readFromFile(student group[]) {
    fstream file;
    file.open(fileName, ios::binary | ios::in);
    file.seekg(0L, ios::end);
    long pos = (long)file.tellg();
    file.seekg(0L, ios::beg);
    file.close();
    int n = pos / (sizeof(student));
    file.open(fileName, ios::binary | ios::in);
    file.read((char*)group, n * (sizeof(student)));
    file.close();
        //cout << "Неуспешно отваряне на фаила!" << endl;
}
