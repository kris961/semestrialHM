#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <windows.h>

using namespace std;

struct discipline {
    char name[25];
    int grade;
};

struct student {
    int facultyId=0;
    char name[30]="";
    discipline disciplines[6];
    char sex[10]="";
    int age=0;
    char status[10]="";
};

const int disciplinesCount = 6;
const int groupCount = 30;
const string fileName = "students.bin";

int mainMenu();
int addStudentMenu();
void createStudent(student group[]);
int printStudentsMenu();
void printStudents(int selection,student group[]);
void sortStudentsByFN(int arrayCount, student group[]);
bool addGrades(int fn, student group []);
void writeToFile(student group[]);
void readFromFile(student group[]);


void main()
{
    setlocale(LC_ALL, "Bulgarian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    bool hasChanges = false;
    bool end = false;
    int code;
    student def = { 0,"", {},"",0,"" };
    student group[30] = {def};
    readFromFile(group);
    while (end != true) {
        if (hasChanges) {
            writeToFile(group);
            readFromFile(group);
            hasChanges = false;
        }
        code = mainMenu();
        switch (code)
        {
        case 1: {
            try
            {
                 int selection= addStudentMenu();
                 if (selection==1)
                 {
                     createStudent(group);
                 }
                 else if (selection==2)
                 {
                     int n;
                     cout << "Въведете борят на студентите които искате да добавите." << endl;
                     cin >> n;
                     for (int i = 0; i < n; i++)
                     {
                         createStudent(group);
                         cout << "Желаете ли да въведете следващ ученик?    yes/no" << endl;
                         string answer;
                         cin >> answer;
                         if (answer != "yes")
                             break;
                         system("CLS");
                     }
                 }
                 hasChanges = true;
            }
            catch (const std::exception&)
            {
                break;
            }
            break;
        }
        case 2: {
            int selection = printStudentsMenu();
            printStudents(selection, group);
            break;
        }
        case 3: {
            bool found;
            int fn;
            student st;
            do {

                cout << "Въведете Факултетният номер на ученика." << endl;
                cin >> fn;
                found = addGrades(fn,group);
                if (found == false) {
                    cout << "Не присъства такъв студент в групата" << endl;
                    cout << "Желаете ли да въведете оценки на друг студент? yes/no" << endl;
                    string answer;
                    cin >> answer;
                    if (answer != "yes")
                        break;
                }
            } while (found==false);
            hasChanges = true;
            break;
        }
        case 4: {
            end = true;
            continue;
            break;
        }
        default:
            continue;
            break;
        }
    }
}

int mainMenu(){
    system("CLS");
    int selection = 0;
        cout << "Въведете числото отговарящо на съответният ред" << endl;
        cout << "1) Добавяне студенти в група." << endl;
        cout << "2) Извеждане на студенти." << endl;
        cout << "3) Въвеждане на оценки на студент." << endl;
        cout << "4) Изход"<<endl;
        cin >> selection;
        system("CLS");
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

    discipline disciplines[6];
    disciplines[0] = { "Електротехника" ,0};
    disciplines[1] = { "Базово Програмиране", 0};
    disciplines[2] = { "Общи Компютърни системи" , 0};
    disciplines[3] = { "Математика" ,0};
    disciplines[4] = { "Английски" ,0};
    disciplines[5] = { "ССП" ,0};

    for (int i = 0; i < groupCount; i++)
    {
        if (group[i].facultyId == 0) {
            group[i] = newStudent;
            break;
        }
    }
}

int printStudentsMenu() {
    int selection = 0;
    do {
        cout << "Въведете числото отговарящо на съответният ред." << endl;
        cout << "1) Извеждане на всички студенти от групата."<< endl;
        cout << "2) Назад." << endl;
        cin >> selection;
        system("CLS");
    } while (selection < 1 || selection>2);
    return selection;
}

void printStudents(int selection, student group[]) {
    int printed = 0;
    if (selection == 1)
    {
        for (int i = 0; i < groupCount;i++)
        {
            if (group[i].facultyId == 0)
                continue;
            cout <<i+1<< ") Име: " << group[i].name << ", Факултетен номер: " << group[i].facultyId << ", пол: " << group[i].sex << ", възраст: " << group[i].age << endl;
            printed++;
        }
        if (printed == 0)
            cout << "Няма налични студенти"<<endl;
    }
    system("pause");
}

void sortStudentsByFN(student group[]) {

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
