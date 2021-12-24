#include <iostream>
#include <stdlib.h>
#include <string>
#include <fstream>
#include <windows.h>
#include <iomanip>

using namespace std;
//��������� �� ������������
struct discipline {
    char name[25]; //��� �� ������������
    int grade; //������ �� ������������
};

struct student {
    int facultyId=0;  //���������� ����� �� �������
    char name[30]=""; //��� �� �������
    discipline disciplines[6];  //���������� �� ��������
    char sex[10]="";  //��� �� ��������
    int age=0; //������� �� ��������
    char status[10]="";  //������ �� ��������
};

const int disciplinesCount = 6;  //����� �� ���������� � ������ � ����������
const int groupCount = 30;  //����� �� ���������� � ������ ��� ��������
const string fileName = "students.bin";  //��� �� ����� � ����� �� �������� �������

int mainMenu(); //����������� �������� ����
int addStudentMenu();//����������� ��������� �� �������� �� ��������
int printStudentsMenu(); //����������� ��������� �� ��������� �� ��������
int gradesMenu(); //����������� ��������� �� �������� � ������� �� ������
int allInfoMenu();//����������� ��������� �� ������� �� ��������

void createStudent(student group[]);//������� �������
void printStudents(student group[]); //������� ����������
void findStudentByFn(student group[]);//������� ���������� � ������� ����� 6 ����� �� ����������� �����
bool addGrades(int fn, student group []);//������ ������ �� ��������������
bool editGrades(int fn, student group[]);//������� �������� �� ��������������
void changeStudentStatus(student group[]);//������ ������� �� ���������� ����� � ������� ������� ��
void printStudentsAllInfo(student group[], string sex);//������� �������� ���������� �� ����������

student* sortByName(student group[]);//������� ���������� �� ����� � ������� ���
student* sortByAgeDesc(student group[]);//������� ���������� �� ������� � �������� ���
student* sortByAgeAndSexAsc(student group[], string sex);//������� ���������� �� ����� ��� �� ������� ��� �������� ���
student findStudentWithBiggestAvg(student group[]);//������ �������� � ���-����� ������ �����

void writeToFile(student group[]);//���� ����� � �������� ����
void readFromFile(student group[]);//���� ����� �� �������� ����


int main()
{
    setlocale(LC_ALL, "Bulgarian");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    bool hasChanges = false;//������ ���������� ����� ������� ���� ��� ������� ����� ������ �� ����� �������� ��� �����
    bool end = false;//������ ���������� ����� ������� ���� ���������� ������ �� ��������
    int code; //��� ����� ������ ��������
    student def = { 0,"", {},"",0,"" };//��������� ����� ����� �� �������� �� ������������
    student group[30] = {def};//������������ ����� � 30 �������� � �� ������ �������� �� ������������
    readFromFile(group);//���� ������� �� �������� ���� � �� ������� � ������
    while (end != true) { //������� �� ����� ������ �� �� ������ ����� �� ���� �� ����������
        if (hasChanges) { //��������� ���� ��� ������� ����� ������ �� �� ������� � �������� ����
            writeToFile(group);//���� ����� � �������� ����
            readFromFile(group);//���� ����� �� �������� ����
            hasChanges = false;//������ ������������
        }
        code = mainMenu(); //����������� �� �������� ���� � �� ����� ��������� �� ����������� �����
        switch (code)//������ ������� �� ���������� ���������� ��������
        {
        case 1: { //��� ����� �� ����� �����
                 int selection= addStudentMenu();//����������� �� ������ �� �������� �� �������� � �� ����� ��������� �����
                 if (selection==1)//��� ������ �� ����� ����� �� ���������
                 {
                     createStudent(group);//������� �� ��� �������
                 }
                 else if (selection==2) //��� ������ �� ������� ����� �� ���������
                 {
                     int n;
                     cout << "�������� ����� �� ���������� ����� ������ �� ��������." << endl;
                     cin >> n; //������� �� ����� �� ���������� ����� �� ����� ��������
                     for (int i = 0; i < n; i++)//����� �� ����� �� ��������� �� ���������� ����
                     {
                         createStudent(group);//������� �� ��� �������
                         if (n-1>i)//��� ���� �� ���������� ������� �� � �������� �� ���� �� �� �������� ����������� �� �������
                         cout << "������� �� �� �������� ������� ������?    yes/no" << endl;
                         string answer;
                         cin >> answer;//������� �� ���������
                         if (answer != "yes")//��� ��������� � yes ����������� �� ������� ������� �� ���� ����������
                             break;//���������� �� �������
                         system("CLS");//�������� �� ���������
                     }
                 }
                 hasChanges = true;//��� ������� ����� �� ������ �� ���� �������� ��� �����
            break;
        }
        case 2: {//��� ����� ����� �� ������
            int selection = printStudentsMenu();//����������� �� ������ �� ��������� �� �������� � �� ����� ������ �� �����������
            if (selection ==1)//��� ����� ����� �� ���������
                printStudents(group);//�������� �� ������ ��������
            if (selection == 2)//��� ����� ����� �� ���������
                findStudentByFn(group);//�������� �� ������ �������� � ������� ����� 6 ����� �� ����������� �����
            break;
        }
        case 3: {//��� ����� ����� �� ������
            int selection = gradesMenu();//����������� �� ������ �� ������
            bool found;//������� ���� � ������� �������
            int fn;
            if (selection == 1)//��� ����� ����� �� ���������
            {
                do {

                    cout << "�������� ������������ ����� �� �������." << endl;
                    cin >> fn;//������� �� ����������� ����� �� �������� ����� �� �����
                    found = addGrades(fn, group);//�������� �� �������� � �� ����� true. ��� �� � ������� �������-false
                    if (found == false) {//��� �� � ������� ��������
                        cout << "�� ��������� ����� ������� � �������" << endl;
                        system("pause");//���������� ����� �� ��������� �� enter
                        break;
                    }
                } while (found == false);//������� �� ���������� ����� ������ �� ���� ������ �������
            }
            if (selection == 2)//��� ����� ����� �� ���������
            {
                cout << "�������� ������������ ����� �� �������." << endl;
                cin >> fn;//������� �� ����������� ����� �� �������� ����� �� �����
                found = editGrades(fn, group);//�������� �� �������� � �� ����� true. ��� �� � ������� �������-false
                if (found == false) {//��� �� � ������� ��������
                    cout << "�� ��������� ����� ������� � �������" << endl;
                    system("pause");//���������� ����� �� ��������� �� enter
                    break;
                }
            }
            hasChanges = true;//��� ������� ����� �� ������ �� ���� �������� ��� �����
            break;
        }
        case 4: {
            changeStudentStatus(group);//����� �� ������� �� �������
            hasChanges = true;//��� ������� ����� �� ������ �� ���� �������� ��� �����
            break;
        }
        case 5: {
            int selection = allInfoMenu();//����������� �� ��������� �� ������� � �� ����� ��������� �� ����������� �����
            student* sorted;//��������� ����� �� ����� ����������� ����� �� ��������
            if (selection==1)//��� ����� ����� �� ���������
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
                cout << "�������� ���� (�����/������)";
                cin >> sex;
                sorted = sortByAgeAndSexAsc(group,sex);
                printStudentsAllInfo(sorted,sex);
            }
            if (selection == 4)
            {
                student st = findStudentWithBiggestAvg(group);
                cout << setw(22) << left << "��� �� �������" << setw(17) << left << "���������� ����� " << setw(8) << left << "���" << setw(2) << left << " �������" << setw(19) << left << " ������" << endl << endl;
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
        cout << "�������� ������� ���������� �� ����������� ���" << endl;
        cout << "1) �������� �������� � �����." << endl;
        cout << "2) ��������� �� ��������." << endl;
        cout << "3) ��������� � ������� �� ������ �� �������." << endl;
        cout << "4) ����� �� ������ �� �������." << endl;
        cout << "5) ������� �� ��������" << endl;
        cout << "6) �����"<<endl;
        cin >> selection;
        system("CLS");
        return selection;
}

int gradesMenu() {
    int selection = 0;
    do {
        system("CLS");
        cout << "�������� ������� ���������� �� ����������� ���" << endl;
        cout << "1) ��������� �� ������ �� �������." << endl;
        cout << "2) ������� �� ������ �� �������."<<endl;
        cout << "3) �����" << endl;
        cin >> selection;
        system("CLS");
    } while (selection > 3 || selection < 1);
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

int printStudentsMenu() {
    int selection = 0;
    do {
        cout << "�������� ������� ���������� �� ����������� ���." << endl;
        cout << "1) ��������� �� ������ �������� �� �������." << endl;
        cout << "2) ��������� �� �������� � �������� ����� 6 ����� �� ���������� �����." << endl;
        cout << "3) �����." << endl;
        cin >> selection;
        system("CLS");
    } while (selection < 1 || selection>3);
    return selection;
}

int allInfoMenu() {
    int selection = 0;
    do {
        system("CLS");
        cout << "�������� ������� ���������� �� ����������� ���." << endl;
        cout << "1) ��������� �� ���������� �� ���." << endl;
        cout << "2) ��������� �� ���������� �� �������." << endl;
        cout << "3) ��������� �� ���-������� �������� �� ���." << endl;
        cout << "4) ��������� �� �������� � ���-����� ������ �����" << endl;
        cout << "5) �����." << endl;
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
    strcpy_s(newStudent.name, name.c_str());
    strcpy_s(newStudent.sex, sex.c_str());
    string status = "����";
    strcpy_s(newStudent.status, status.c_str());
    newStudent.age = age;

    newStudent.disciplines[0] = { "��������������" ,0};
    newStudent.disciplines[1] = { "������ ������������", 0};
    newStudent.disciplines[2] = { "���� ���������� �������" , 0};
    newStudent.disciplines[3] = { "����������" ,0};
    newStudent.disciplines[4] = { "���������" ,0};
    newStudent.disciplines[5] = { "���" ,0};

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
    cout << "��������: " << page<<endl;
        cout << setw(26) << left << "��� �� �������" << "���������� �����" << endl;
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
                cout << "��������: " << page << endl;
                cout << setw(26) << left << "��� �� �������" << "���������� �����" << endl;
                page++;
            }
        }
        if (printed == 0)
        {
            system("CLS");
            cout << "���� ������� ��������" << endl;
        }
    system("pause");
}

void printStudentsAllInfo(student group[], string sex) {
    int printed = 0;
    cout << setw(25) << left << "��� �� �������" <<setw(16)<<left<< "���������� ����� "<<setw(8)<<left <<"���"<<setw(2)<<left<<" �������"<<setw(19)<<left<<" ������"<< endl<<endl;

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
        cout << "���� ������� ��������" << endl;
    }
    system("pause");
}

void changeStudentStatus(student group[]) {
    cout << "�������� ��� �� ��������." << endl;
    char name[30];
    cin.ignore();
    cin.getline(name, 30);
    bool found = false;
    for (int i = 0; i < groupCount; i++)
    {
        if (strcmp(group[i].name, name) == 0) {
            strcpy_s(group[i].status, "��������");
            system("CLS");
            cout << "������� �� " << group[i].name << " � ������ �������." << endl;
            found = true;
            break;
        }
    }
    if (!found)
    {
        system("CLS");
        cout << "�� � ������� ����� �������." << endl;
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
        cout << "�� �� ������ �� ������ ��: " << group[stIndex].disciplines[i].name << "?    (yes/no)"<<endl;
        cin >> answer;
        if (answer == "yes")
        {
            cout << "�������� ������ ��: " << group[stIndex].disciplines[i].name << endl;
            cin >> grade;
            group[stIndex].disciplines[i].grade = grade;
            addedGrades++;
        }
        else
            continue; 
        system("CLS");
    }
    if (addedGrades == 0)
        cout << "������ ������ �� �������� �� ��������!" << endl;
    else
        cout << "�������� �� �������� �������!"<<endl;
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
            cout << "�������� ���� ������ �� ���� �������. �� �� ������ ��?  (yes/no)" << endl;
        else
            cout << "�� �� ������� �� �������� ��: " << group[stIndex].disciplines[i].name << "? ������ ������: "<<group[stIndex].disciplines[i].grade<<"(yes/no)" << endl;
        cin >> answer;
        if (answer == "yes")
        {
            cout << "�������� ������ ��: " << group[stIndex].disciplines[i].name << endl;
            cin >> grade;
            group[stIndex].disciplines[i].grade = grade;
            editedGrades++;
        }
        else
            continue;
        system("CLS");
    }
    if (editedGrades == 0)
        cout << "�� �� ��������� ������� �� �������� �� ��������." << endl;
    else
        cout << "�������� �� ��������� ������� �������!" << endl;
    system("pause");
    return true;
}

void findStudentByFn(student group[]) {
    int fn;
    do {
        cout << "�������� ������� 6 ����� �� ���������� �����." << endl;
        cin >> fn;
    } while (fn > 999999 || fn < 100000);
    system("CLS");

    cout << setw(26) << left << "��� �� �������" << "���������� �����" << endl;
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
        cout << "�� �� �������� �������� � ���� ���������� �����!"<<endl;
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
        //cout << "��������� �������� �� �����!" << endl;
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
        //cout << "��������� �������� �� �����!" << endl;
}
