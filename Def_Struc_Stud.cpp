#include "Def_Struc_Stud.h"


Stud InitStud()
{
    Stud st;
    cout << "f Name" << "\t";
    cin.getline(st.fname,20);
    cout << "l Name" << "\t";
    cin.getline(st.lname, 20);
    cout << "Age" << "\t";
    cin.getline(st.age, 20); 
    cout << "Curs" << "\t";
    cin.getline(st.curs, 20); 
    cout << "Special" << "\t";
    cin.getline(st.special, 25);

    return st;
}

ArrStud InitArrStud(int size)
{
    ArrStud arrst;
    arrst.arr = new Stud[size];
    for (int i = 0; i < size; i++) {
        cout << "Студент " << i + 1 << endl;
        arrst.arr[i] = InitStud();
        cout << endl << endl;
    }
    
    arrst.size = size;
    return arrst;
}
Stud InitFStud(char* line)
{
    Stud st;
    char* context = nullptr;
    char* word = strtok_s(line, " ", &context);
    if (word) strncpy_s(st.fname, word, _TRUNCATE);


    word = strtok_s(nullptr, " ", &context);
    if (word) strncpy_s(st.lname, word, _TRUNCATE);

    word = strtok_s(nullptr, " ", &context);
    if (word) strncpy_s(st.age, word, _TRUNCATE);

    word = strtok_s(nullptr, " ", &context);
    if (word) strncpy_s(st.curs, word, _TRUNCATE);

    word = strtok_s(nullptr, " ", &context);
    if (word) strncpy_s(st.special, word, sizeof(st.special) - 1);

    return st;
}
ArrStud InitFArrStud(const char* f)
{
    fstream file(f, ios::in);
    if (!file) { 
    cout << "Open File ERROR" << endl;
    ArrStud err;
    err.arr = nullptr;
    err.size = 0;
    return err;
     }

    const int size_buf = 100;
    char ch[size_buf];
    
    ArrStud arrst;
    arrst.arr = new Stud[size_buf];
    int i = 0;

    while (file.getline(ch, size_buf)) {
        if (i >= size_buf) { break; }

         arrst.arr[i++] = InitFStud(ch);

        
    }
    arrst.size = i;
    file.close();
    return arrst;
}
void PrintStud(const Stud st) {
    
    cout << "f Name" << st.fname<<" ";
    cout << "l Name" << st.lname << " ";
    cout << "Special" << st.special << " ";
    cout << "Age" << st.age << " ";
    cout << "Curs" << st.curs << endl;
}

void PrintArr(const ArrStud& arrst) {
    if (arrst.arr == nullptr || arrst.size == 0) {
        cout << "Нет данных для вывода." << endl;
        return;
    }

    for (int i = 0; i < arrst.size; ++i) {
        PrintStud(arrst.arr[i]);
    }
}
void FreeMemory(ArrStud& arr) {
    if (arr.arr != nullptr) {
        delete[] arr.arr;
        arr.arr = nullptr;
        arr.size = 0;
    }
}

void RedactStud(ArrStud& arrst)
{
    Stud* st = FindStud(arrst);
    if (!st) return;

    PrintArr(arrst); 

    while (true) {
        int op = 0;
        char buf[25];
        cout << "Введите параметр который хотите поменять: " << endl;
        cout << "1  fname" << endl;
        cout << "2  lname" << endl;
        cout << "3  special" << endl;
        cout << "4  age" << endl;
        cout << "5  curs" << endl;
        cout << "\n0  Выход" << endl;
        cin >> op;
        if (op == 0) { break; }
        else if (op == 1) {
            cout << "New  fname" << endl;
            cin >> buf;
            strncpy_s(st->fname, buf, _TRUNCATE);
        }
        else if (op == 2) {
            cout << "new  lname" << endl;
            cin >> buf;
            strncpy_s(st->lname, buf, _TRUNCATE);
        }
        else if (op == 3) {
            cout << "new  special" << endl;
            cin >> buf;
            strncpy_s(st->special, buf, _TRUNCATE);
        }
        else if (op == 4) {
            cout << "new  age" << endl;
            cin >> buf;
            strncpy_s(st->age, buf, _TRUNCATE);
        }
        else if (op == 5) {
            cout << "new  curs" << endl;
            cin >> buf;
            strncpy_s(st->curs, buf, _TRUNCATE);
        }
    }
}


Stud* FindStud(ArrStud& arrst)
{
    if (arrst.arr == nullptr || arrst.size == 0) {
        cout << "Нет данных для вывода." << endl;

        return nullptr;;
        
    }
    
    while (true) {
        int num = 0;


        cout << "Введите номер студента или 0 для выхода: " << endl;
        cin >> num;

        if (num == 0) { cout << "Выход...\n"; break; }

        else if (num >= 1 && num <= arrst.size)
        {
            return &arrst.arr[num - 1];

        }
        else {
            cout << "ERROR num. Let`s agen cin " << endl;
        }

        int choise = 0;
        cout << "1. Продолжить       2. Выход" << endl;
        cin >> choise;
        if (choise == 2) { break; }
    }

}
bool isDubl(const Stud& a,const Stud& b) {

    return strcmp(a.fname, b.fname)==0 &&
        strcmp(a.lname, b.lname) == 0 &&
        strcmp(a.special, b.special) == 0 &&
        strcmp(a.age, b.age) == 0 &&
        strcmp(a.curs, b.curs) == 0 ;
}
void DeleteStud(ArrStud& arrst)
{
    Stud* st = FindStud(arrst);
    if (!st) return;

    ArrStud temp;
    temp.arr= new Stud [arrst.size-1];
    int p = 0;

    for (int i = 0; i < arrst.size; i++) {
        if (isDubl(arrst.arr[i],*st)) {
            continue;
        }
        if(p < arrst.size-1)
        temp.arr[p++] = arrst.arr[i];
    }

    delete[]arrst.arr;
    arrst.arr = temp.arr;
    arrst.size = arrst.size - 1;

}

void FindStudLN(const ArrStud& arrst, const char* ln)
{
    if (!arrst.arr) { cout << "ERROR" << endl; return; }
    bool fS = false;
    for (int i = 0; i < arrst.size; i++) {
        if (strcmp(arrst.arr[i].fname, ln) == 0) {
            PrintStud(arrst.arr[i]);
            fS = true;
        }
    }
    if (!fS) {
        cout << "Студентов по заданному имени не найдено" << endl;
    }

}
int FindChFN(const char* gl_ln, const char* ln) {
    int isF = 0;
    for (int i = 0; i < strlen(ln) + 1; i++) {
        if (ln[i] == gl_ln[i]) {
            isF++;
        }
    }


    return isF;
}

void PrintStudAgLn(const ArrStud& arrst, const char* ag, const char* ln)
{
    if (!arrst.arr) { cout << "ERROR" << endl; return; }
    bool fS = false;
    for (int i = 0; i < arrst.size; i++) {
        if (strcmp(arrst.arr[i].age, ag) == 0 || FindChFN(arrst.arr[i].lname,ln)>0) {
            PrintStud(arrst.arr[i]);
            fS = true;
            
        }
    }
    if (!fS) {
            cout << "Студентов по заданному имени не найдено" << endl;
        }
}

void SafeArrStud(const ArrStud& arrst, const char* f)
{
    ofstream file(f);
    if (!file) { cout << "Open File ERROR" << endl; return; }

    for (int i = 0; i < arrst.size; i++) {

        file << arrst.arr[i].fname << " "
            << arrst.arr[i].lname << " "
            << arrst.arr[i].age << " "
            << arrst.arr[i].curs << " "
            << arrst.arr[i].special << "\n";
    }
    file.close();  
}
//Программа должна обеспечивать ввод данных, редактирование данных сотрудника, удаление сотрудника, поиск сотрудника по фамилии, вывод информации обо всех сотрудниках, указанного возраста, или фамилия которых начинается на указанную букву.Организуйте возможность сохранения найденной информации в файл.
void MainMenu()
{
    ArrStud stud;
    int choise = 0;
    cout<<"Программа студенты" << endl;
    while (true) {

        cout << "Введите действие " << endl;
        cout << "1.   Ввести данные студентов или загрузить из файла\n2.   Редактирование студента\n3.   Удаление студента\n4.   Поиск студента по фамилии\n5.   Вывод информации обо всех студентах\n6.   Вывод информации обо всех сотрудниках, указанного возраста, или фамилия которых начинается на указанную букву\n7.   Сохранение студентов в файл\n8.   Выход\n";
        cin >> choise;

        cin.ignore(); 

        if (choise == 1) {
            FreeMemory(stud); 
            cout << "1. Ввод с клавиатуры\n2. Загрузка из файла\nВаш выбор: ";
            int sub;
            cin >> sub;
            cin.ignore();
            if (sub == 1) {
                int num;
                cout << "Введите количество студентов: ";
                cin >> num;
                cin.ignore();
                stud = InitArrStud(num);
            }
            else if (sub == 2) {
                char filename[100];
                cout << "Введите имя файла: ";
                cin.getline(filename, 100);
                stud = InitFArrStud(filename);
            }
        }

        else if (choise == 2) {
            RedactStud(stud);
        }

        else if (choise == 3) {
            DeleteStud(stud);
        }

        else if (choise == 4) {
            char ln[20];
            cout << "Введите фамилию для поиска: ";
            cin.getline(ln, 20);
            FindStudLN(stud, ln);
        }

        else if (choise == 5) {
            PrintArr(stud);
        }

        else if (choise == 6) {
            char ag[4], ln[20];
            cout << "Введите возраст: ";
            cin.getline(ag, 4);
            cout << "Введите начало фамилии: ";
            cin.getline(ln, 20);
            PrintStudAgLn(stud, ag, ln);
        }

        else if (choise == 7) {
            char filename[100];
            cout << "Введите имя файла для сохранения: ";
            cin.getline(filename, 100);
            SafeArrStud(stud, filename);
        }

        else if (choise == 8) {
            cout << "Завершение работы..." << endl;
            SafeArrStud(stud, "rezsafe.txt");
            break;
        }

        else {
            cout << "Неверный выбор. Попробуйте снова." << endl;
        }
    }

    FreeMemory(stud);
    
}
