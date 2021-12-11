#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

struct discipline {
    string name;
    int grade;
};

struct student {
    string facultyId;
    string name;
    discipline disciplines[6];
    string sex;
    int age;
    string status;
};

const int disciplinesCount = 6;
const int groupCount = 30;

int mainMenu();
int addStudentMenu();
student createStudent();
int printStudentsMenu();
void printStudents(int selection,int arrayCount,student (& group)[30]);
void sortStudentsByFN(int arrayCount, student(&group)[30]);
bool addGrades(string fn, student(&group)[30]);


void main()
{
    setlocale(LC_ALL, "Bulgarian");
    int arrayCount = 0;
    bool end = false;
    int code;
    student group[30];
    while (end != true) {
        code = mainMenu();
        switch (code)
        {
        case 1: {
            try
            {
                 int selection= addStudentMenu();
                 if (selection==1)
                 {
                     student s = createStudent();
                     group[arrayCount] = s;
                     arrayCount++;
                 }
                 else if (selection==2)
                 {
                     int n;
                     cout << "Въведете борят на студентите които искате да добавите." << endl;
                     cin >> n;
                     for (int i = 0; i < n; i++)
                     {
                         student s = createStudent();
                         group[arrayCount] = s;
                         arrayCount++;
                     }
                 }
            }
            catch (const std::exception&)
            {
                break;
            }
            break;
        }
        case 2: {
            int selection = printStudentsMenu();
            printStudents(selection, arrayCount, group);
            break;
        }
        case 3: {
            bool found;
            string fn;
            student st;
            do {

                cout << "Въведете Факултетният номер на ученика." << endl;
                cin >> fn;
                found = addGrades(fn, group);
                if (found==false)
                    cout << "Не присъства такъв студент в групата" << endl;
            } while (found==false);
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

student createStudent() {
    string facultyN;
    string name;
    string sex;
    int age;
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
    newStudent.name = name;
    newStudent.sex = sex;
    newStudent.status = "";

    discipline disciplines[12];
    discipline ET = { "Електротехника" };
    discipline BP = { "Базово Програмиране" };
    discipline OKS = { "Общи Компютърни системи" };
    discipline Math = { "Математика" };
    discipline AE = { "Английски" };
    discipline SSP = { "ССП" };
    newStudent.disciplines[0] = ET;
    newStudent.disciplines[1] = BP;
    newStudent.disciplines[2] = OKS;
    newStudent.disciplines[3] = Math;
    newStudent.disciplines[4] = AE;
    newStudent.disciplines[5] = SSP;

    return newStudent;
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

void printStudents(int selection,int arrayCount, student(&group)[30]) {
    if (selection == 1 && arrayCount > 0)
    {
        for (int i = 0; i < arrayCount;i++)
        {
            cout <<i+1<< ") Име: " << group[i].name << ", Факултетен номер: " << group[i].facultyId << ", пол: " << group[i].sex << ", възраст: " << group[i].age << endl;
        }
        int a;
    }
}

void sortStudentsByFN(int arrayCount, student(&group)[30]) {

}

bool addGrades(string fn, student(&group)[30]) {
    int stIndex=-1;
    int addedGrades=0;
    for (int i = 0; i < groupCount; i++)
    {
        if (group[i].facultyId == "")
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
    }
    if (addedGrades==0)
    {
        cout << "Всички оценки на студента са въведени!"<<endl;
    }
    return true;
}
