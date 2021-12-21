#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>

using namespace std;
ifstream in_stream;
ofstream out_stream;


struct discipline {
    string name;
    int grade;
};

struct student {
    int facultyId;
    string name;
    discipline disciplines[6];
    string sex;
    int age;
    string status;
};

const int disciplinesCount = 6;
const int groupCount = 30;
const string fileName = "students.dat";

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
    bool end = false;
    int code;
    student def = { 0 };
    student group[30] = {def};
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
        case 5: {
            writeToFile(group);
            break;
        }
        case 6: {
            readFromFile(group);
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
    newStudent.name = name;
    newStudent.sex = sex;
    newStudent.status = "учащ";
    newStudent.age = age;

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
    }
    if (addedGrades==0)
    {
        cout << "Всички оценки на студента са въведени!"<<endl;
    }
    return true;
}

void writeToFile(student group[]) {
    out_stream.open(fileName);
    if (out_stream.fail())
    {
        cout << "fail";
    }
    for (int i = 0; i < groupCount; i++)
    {
        if (group[i].facultyId == 0)
            continue;
        out_stream << group[i].facultyId << "," << group[i].name << "," << group[i].sex << "," << group[i].age << "," << group[i].status << ",";
        for (int j = 0; j < disciplinesCount; j++)
        {
            out_stream << group[i].disciplines[j].name << "-" << group[i].disciplines[j].grade<<",";
        }
        out_stream << endl;
    }
    out_stream.close();
}

void readFromFile(student group[]) {
    in_stream.open(fileName);
    int facultyN;
    string name;
    string sex;
    int age;
    string status;
    string line;
    string info;
    int start = 0;
    int cuts = 0;
    while (getline(in_stream, line)) {
        for (int i = 0; i < line.length(); i++)
        {
            if (i == 40)
            {
                cout << "d";
            }
            if (line[i]==',')
            {
                info =line.substr(start, i-start);
                switch (cuts)
                {
                case 0:
                    facultyN = stoi(info);
                    break;
                case 1:
                    name = info;
                    break;
                case 2:
                    sex = info;
                    break;
                case 3:
                    age = stoi(info);
                    break;
                case 4:
                    status = info;
                    break;
                }
                start = i+1;
                cuts++;
            }
        }
    }
}
