#include <iostream>
#include <stdlib.h>
#include <string>

using namespace std;

struct discipline {
    string name;
    int grade[5];
};

struct student {
    string facultyId;
    string name;
    discipline disciplines[12];
    string sex;
    int age=0;
    string status;
};

int mainMenu();
int addStudentMenu();
student createStudent();


void main()
{
    setlocale(LC_ALL, "Bulgarian");
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
                     for (int i = 0; i < 30; i++)
                     {
                         if (group[i].age == 0)
                         {
                             group[i] = s;
                             break;
                         }
                     }
                 }
                 else if (selection==2)
                 {
                     int n;
                     cout << "�������� ����� �� ���������� ����� ������ �� ��������." << endl;
                     cin >> n;
                     for (int i = 0; i < n; i++)
                     {
                         student s = createStudent();
                         for (int i = 0; i < 30; i++)
                         {
                             if (group[i].age == 0)
                             {
                                 group[i] = s;
                                 break;
                             }
                         }
                     }
                 }
            }
            catch (const std::exception&)
            {
                continue;
            }
            break;
        }
        case 2: {

            break;
        }
        case 3: {
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
        cout << "�������� ������� ���������� �� ����������� ���" << endl;
        cout << "1) �������� �������� � �����." << endl;
        cout << "2) ��������� �� ��������." << endl;
        cout << "3) ��������� �� ������ �� �������." << endl;
        cout << "4) �����"<<endl;
        cin >> selection;
        system("CLS");
        return selection;
}

int addStudentMenu() {
    int selection=0;
    do {
        cout << "�������� ������� ���������� �� ����������� ���" << endl;
        cout << "1) �������� �� �������." << endl;
        cout << "2) �������� �� �������� �� ��������." << endl;
        cout << "3) �����."<<endl;
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
        cout << "������� ������� �� �������� � ������� ������:" << endl;
        cout << "���������� �����" << endl;
        cin >> facultyN;
        cout << "���" << endl;
        cin.ignore();
        getline(cin, name);
        cout << "���" << endl;
        cin >> sex;
        cout << "�������" << endl;
        cin >> age;
    }
    catch (const std::exception&)
    {
        cout << "��������� �����";
    }
    student newStudent;
    newStudent.facultyId = facultyN;
    newStudent.name = name;
    newStudent.sex = sex;
    newStudent.status = "";

    discipline disciplines[12];
    discipline ET = { "��������������" };
    discipline ETLU = { "�.�.��������������" };
    discipline ETSU = { "�.�.��������������" };
    discipline BP = { "������ ������������" };
    discipline BPLU = { "�.�.������ ������������" };
    discipline BPSU = { "�.�.������ ������������" };
    discipline OKS = { "���� ���������� �������" };
    discipline OKSLU = { "�.�.���� ���������� �������" };
    discipline Math = { "����������" };
    discipline MathSU = { "�.�.����������" };
    discipline AESU = { "�.�.���������" };
    discipline SSP = { "���" };
    newStudent.disciplines[0] = ET;
    newStudent.disciplines[1] = ETLU;
    newStudent.disciplines[2] = ETSU;
    newStudent.disciplines[3] = BP;
    newStudent.disciplines[4] = BPLU;
    newStudent.disciplines[5] = BPSU;
    newStudent.disciplines[6] = OKS;
    newStudent.disciplines[7] = OKSLU;
    newStudent.disciplines[8] = Math;
    newStudent.disciplines[9] = MathSU;
    newStudent.disciplines[10] = AESU;
    newStudent.disciplines[11] = SSP;

    return newStudent;
}