#include <iostream>
#include<stdlib.h>   // malloc free; //realloc calloc//堆区的分配
#include<assert.h>
#include<string.h>

using namespace std;

struct Student {
    char s_id[20];
    char s_name[20];
    char s_sex[10];
    char s_major[20];
    int s_age;
};
typedef struct Student ElemType;//类型重命名
typedef struct DuNode {
    ElemType data;      //   	56
    struct DuNode *prev; // 4
    struct DuNode *next;  // 4
} DuNode;

typedef struct {
    struct DuNode *head;
    int cursize;
} DuLinkList;

struct DuNode *Buynode(struct DuNode *parg = nullptr, struct DuNode *narg = nullptr)//申请一个结点
{
    struct DuNode *s = (struct DuNode *) malloc(sizeof(struct DuNode));//4+4+4=12个字节
    if (nullptr == s) exit(EXIT_FAILURE);//如果nullptr==s，申请空间失败
    s->prev = (parg == nullptr ? s : parg);
    s->next = (narg == nullptr ? s : narg);
    return s;
}

void Freenode(struct DuNode *p)//释放空间
{
    free(p);
}

void InitList(DuLinkList *plist)//初始化函数
{
    assert(plist != nullptr);
    plist->head = Buynode();//头结点或哨兵节点
    plist->cursize = 0;
}

int GetSize(DuLinkList *plist) {
    assert(plist != nullptr);
    return plist->cursize;
}

bool Is_Empty(DuLinkList *plist) {
    assert(plist != nullptr);
    return GetSize(plist) == 0;
}

void PrintList(DuLinkList *plist)//打印函数
{
    assert(plist != nullptr);
    struct DuNode *p = plist->head->next; // 此时p指向第一个有数据的结点
    while (p != plist->head) {
        p = p->next;
    }
    cout << endl;
}

struct DuNode *FindValue(DuLinkList *plist, ElemType val)//查询函数
{
    assert(plist != nullptr);
    struct DuNode *p = plist->head->next; //
    //while (p != plist->head && p->data!= val)
    {
        p = p->next;
    }
    if (p == plist->head) {
        p = nullptr;
    }
    return p;
}

bool InsertNode(DuLinkList *plist, struct DuNode *ptr, struct DuNode *newnode)//插入一个结点
{
    assert(plist != nullptr);
    if (ptr == nullptr || newnode == nullptr)//二者有一个为空就无法进行插入
    {
        return false;//插入失败
    }
    newnode->next = ptr; // 1
    newnode->prev = ptr->prev;    //2
    ptr->prev->next = newnode; // 3
    ptr->prev = newnode;    // 4
    plist->cursize += 1;
    return true;
}

bool Push_back(DuLinkList *plist, ElemType val)//插入到当前列表末尾
{
    assert(plist != nullptr);
    struct DuNode *newnode = Buynode();
    newnode->data = val;
    return InsertNode(plist, plist->head, newnode);
}

bool Push_front(DuLinkList *plist, ElemType val)////插入到当前列表前段
{
    assert(plist != nullptr);
    struct DuNode *newnode = Buynode();
    newnode->data = val;
    return InsertNode(plist, plist->head->next, newnode);
}

bool EarseList(DuLinkList *plist, struct DuNode *ptr)//删除结点
{
    assert(plist != nullptr);
    if (nullptr == ptr) return false;
    ptr->prev->next = ptr->next;
    ptr->next->prev = ptr->prev;
    plist->cursize -= 1;
    cout << "删除成功" << endl;
    return true;
}

bool Pop_back(DuLinkList *plist)//删除最后一个数据结点
{
    assert(plist != nullptr);
    if (Is_Empty(plist)) return false;
    return EarseList(plist, plist->head->prev);
}

bool Pop_front(DuLinkList *plist)//删除第一个数据结点
{
    assert(plist != nullptr);
    if (Is_Empty(plist)) return false;
    return EarseList(plist, plist->head->next);
}

struct DuNode *FindStudentId(DuLinkList *plist, char id[]);

bool Remove(DuLinkList *plist, char stuId[])//删除结点
{
    assert(plist != nullptr);
    struct DuNode *p = FindStudentId(plist, stuId);
    if (nullptr == p) return false;
    return EarseList(plist, p);
}

void ClearList(DuLinkList *plist) {
    assert(plist != nullptr);
    while (!Is_Empty(plist)) {
        Pop_back(plist);
    }
}

void DestroyList(DuLinkList *plist)//摧毁链表
{
    assert(plist != nullptr);
    ClearList(plist);
    Freenode(plist->head);
    plist->head = nullptr;
}

int FindMenu() {
    int select = 0;

    cout << "*****学生的查询*****" << endl;
    cout << "*  1. 按学号查询   *" << endl;
    cout << "*  2. 按姓名查询   *" << endl;
    cout << "*  3. 按性别查询   *" << endl;
    cout << "*  4. 按年龄查询   *" << endl;
    cout << "*  5. 按专业查询   *" << endl;
    cout << "*  0. 退出查询     *" << endl;
    cout << "********************" << endl;
    cout << "请选择..... " << endl;
    cin >> select;
    return select;
}

int MainMenu() {
    int select = 0;
    cout << "*********学生信息管理系统*********" << endl;
    cout << "* 1. 添加                2.查询*" << endl;
    cout << "* 3. 修改                4.专业统计*" << endl;
    cout << "* 5. 显示                6.性别统计*" << endl;
    cout << "* 7. 年龄统计            8.删除*" << endl;
    cout << "* 9. 插入                0.退出*" << endl;
    cout << "******************************" << endl;
    cout << "请选择..... " << endl;
    cin >> select;
    return select;
}


void AddStudent(DuLinkList *plist) {
    assert(plist != nullptr);
    struct Student tmp = {};
    cout << "请输入学生的学号: ";
    cin >> tmp.s_id;
    cout << "请输入学生的姓名: ";
    cin >> tmp.s_name;
    cout << "请输入学生的性别: ";
    cin >> tmp.s_sex;
    cout << "请输入学生的年龄: ";
    cin >> tmp.s_age;
    cout << "请输入学生的专业: ";
    cin >> tmp.s_major;
    Push_back(plist, tmp);
}

//显示学生信息
void PrintStudent(struct DuNode *p) {
    assert(p != nullptr);
    cout << "id: ";
    cout.width(20);
    cout << p->data.s_id;
    cout << " name: ";
    cout.width(20);
    cout << p->data.s_name;
    cout << " sex: ";
    cout.width(10);
    cout << p->data.s_sex;
    cout << " age: ";
    cout.width(8);
    cout << p->data.s_age;
    cout << " major: ";
    cout.width(20);
    cout << p->data.s_major << endl;
}

void ShowStudent(DuLinkList *plist) {
    assert(plist != nullptr);
    struct DuNode *p = plist->head->next; // first;
    while (p != plist->head) {
        PrintStudent(p);
        p = p->next;
    }
    cout << "\n-------------------------------------" << endl;
}


//查找学生
void FindStudent_Id(DuLinkList *plist, char id[]) {
    assert(plist != nullptr);
    struct DuNode *p = plist->head->next;
    while (p != plist->head) {
        if (strcmp(p->data.s_id, id) == 0) {
            PrintStudent(p);
        }
        p = p->next;
    }

}

struct DuNode *FindStudentId(DuLinkList *plist, char id[]) {
    assert(plist != nullptr);
    struct DuNode *p = plist->head->next;
    while (p != plist->head) {
        if (strcmp(p->data.s_id, id) == 0) {
            return p;

        }
        p = p->next;
    }
    return nullptr;
}

void FindStudent_Name(DuLinkList *plist, char name[]) {
    assert(plist != nullptr);
    struct DuNode *p = plist->head->next;
    while (p != plist->head) {
        if (strcmp(p->data.s_name, name) == 0) {
            PrintStudent(p);
        }
        p = p->next;
    }

}

void FindStudent_Sex(DuLinkList *plist, char sex[]) {
    assert(plist != nullptr);
    struct DuNode *p = plist->head->next;
    while (p != plist->head) {
        if (strcmp(p->data.s_sex, sex) == 0) {
            PrintStudent(p);
        }
        p = p->next;
    }

}

void FindStudent_Major(DuLinkList *plist, char major[]) {
    assert(plist != nullptr);
    struct DuNode *p = plist->head->next;
    while (p != plist->head) {
        if (strcmp(p->data.s_major, major) == 0) {
            PrintStudent(p);
        }
        p = p->next;
    }

}

void FindStudent_Age(DuLinkList *plist, int age) {
    assert(plist != nullptr);
    struct DuNode *p = plist->head->next;
    while (p != plist->head) {
        if (p->data.s_age == age) {
            PrintStudent(p);
        }
        p = p->next;
    }

}

void FindStudent(DuLinkList *plist) {
    assert(plist != nullptr);
    char id[20] = {};
    char name[20] = {};
    char sex[10] = {};
    char major[20] = {};

    int age = 0;
    int select = 0;
    do {
        select = FindMenu();
        switch (select) {
            case 0:
                break;
            case 1:
                cout << "请入学生的学号: ";
                cin >> id;
                FindStudent_Id(plist, id);
                break;
            case 2:
                cout << "请入学生的姓名: ";
                cin >> name;
                FindStudent_Name(plist, name);
                break;
            case 3:
                cout << "请入学生的性别: ";
                cin >> sex;
                FindStudent_Sex(plist, sex);
                break;
            case 4:
                cout << "请入学生的年龄: ";
                cin >> age;
                FindStudent_Age(plist, age);
                break;
            case 5:
                cout << "请入学生的专业: ";
                cin >> major;
                FindStudent_Major(plist, major);
                break;
            default:
                cout << "选择错误 .... 重新选择 " << endl;
                break;
        }
    } while (select != 0);
}


//根据性别统计
void CountGender(DuLinkList *plist) {
    assert(plist != nullptr);
    struct DuNode *p = plist->head->next;

    int male_count = 0;
    int female_count = 0;
    while (p != plist->head) {
        if (strcmp(p->data.s_sex, "男")) {
            male_count++;
        } else if (strcmp(p->data.s_sex, "女")) {
            female_count++;
        }
        p = p->next;
    }
    cout << "女性人数：" << male_count << endl;
    cout << "男性人数：" << female_count << endl;
}

//根据专业统计
void CountStudent_Major(DuLinkList *plist, char major[]) {
    assert(plist != nullptr);
    struct DuNode *p = plist->head->next;
    int count = 0;
    while (p != plist->head) {
        if (strcmp(p->data.s_major, major) == 0) {
            count++;
        }
        p = p->next;
    }
    cout << "专业 " << major << "的学生人数为:" << count << endl;
}

//根据年龄
void CountStudent_Age(DuLinkList *plist, int age) {
    assert(plist != nullptr);
    int count = 0;
    struct DuNode *p = plist->head->next;
    while (p != plist->head) {
        if (p->data.s_age == age) {
            count++;
        }
        p = p->next;
    }
    cout << "Age " << age << ": " << count << " students" << endl;
}


void SaveFile(DuLinkList *plist) {
    assert(plist != nullptr);
    FILE *fp = fopen("stud.txt", "w"); // "w" "r" "a" "wb" "rb" "ab"
    if (fp == nullptr) return;
    fprintf(fp, "%d\n", GetSize(plist));
    struct DuNode *p = plist->head->next; // first
    while (p != plist->head) {
        fprintf(fp, "%s %s %s %d \n",
                p->data.s_id, p->data.s_name, p->data.s_sex, p->data.s_age);
        p = p->next;
    }
    fclose(fp); //
    fp = nullptr;
}

void LoadFile(DuLinkList *plist) {
    assert(plist != nullptr);
    int num = 0;
    struct Student tmp = {};
    FILE *fp = fopen("stud.txt", "r");
    if (nullptr == fp) return;
    fscanf(fp, "%d", &num);
    for (int i = 0; i < num; ++i) {
        fscanf(fp, "%s %s %s %d  %s", tmp.s_id, tmp.s_name, tmp.s_sex, &tmp.s_age, tmp.s_major);
        Push_back(plist, tmp);
    }
    fclose(fp);
    fp = nullptr;
}

void ModifyStudent(DuLinkList *plist, char name[]) {

    assert(plist != nullptr);
    struct DuNode *p = plist->head->next;
    while (p != plist->head) {
        if (strcmp(p->data.s_name, name) == 0) {
            cout << "该学生学号为：" << p->data.s_id << endl;
            cout << "请输入新的学号：" << endl;
            cin >> p->data.s_id;

            cout << "该学生姓名为：" << p->data.s_name << endl;
            cout << "请输入新的姓名：" << endl;
            cin >> p->data.s_name;

            cout << "该学生性别为：" << p->data.s_sex << endl;
            cout << "请输入新的性别：" << endl;
            cin >> p->data.s_sex;

            cout << "该学生年龄为：" << p->data.s_age << endl;
            cout << "请输入新的年龄：" << endl;
            cin >> p->data.s_age;

            cout << "该学生专业为：" << p->data.s_major << endl;
            cout << "请输入新的专业：" << endl;
            cin >> p->data.s_major;

        }
        p = p->next;
    }
}

struct Student InputStudent() {
    struct Student temp = {};
    cout << "输入学生的学号";
    cin >> temp.s_id;
    cout << "输入学生的姓名";
    cin >> temp.s_name;
    cout << "输入学生的性别";
    cin >> temp.s_sex;
    cout << "输入学生的年龄";
    cin >> temp.s_id;
    cout << "输入学生的专业";
    cin >> temp.s_major;
    return temp;


}

int main() {

    DuLinkList studlist;
    struct Student temp;
    int select = 0;

    InitList(&studlist);
    LoadFile(&studlist);
    DuLinkList plist = studlist;

    do {
        select = MainMenu();
        switch (select) {
            case 0:
                cout << "退出系统....." << endl;
                break;
            case 1:
                AddStudent(&studlist);
                break;
            case 2:
                FindStudent(&studlist);
                break;
            case 3:
                char name[20];
                cout << "请输入修改信息学生的姓名: ";
                cin >> name;
                ModifyStudent(&studlist, name);

                break;
            case 4:
                char major[20];
                cout << "请输入要统计的专业: ";
                cin >> major;
                CountStudent_Major(&studlist, major);
                break;
            case 5:
                ShowStudent(&studlist);
                break;
            case 6:
                CountGender(&studlist);
                break;
            case 7:
                int age;
                cout << "请输入要统计的年龄: ";
                cin >> age;
                CountStudent_Age(&studlist, age);
                break;

            case 8:
                char stuId[20];
                cout << "请输入要删除的学生的学号: ";
                cin >> stuId;
                Remove(&studlist, stuId);
                break;
            case 9: {
                char id[20];
                struct DuNode *newnode = Buynode();
                cout << "请输入要在哪个学号之前插入学生信息:";
                cin >> id;
                struct DuNode *p = FindStudentId(&studlist, id);
                assert(p != nullptr);
                cout << "请输入待插入学生的学号:";
                cin >> newnode->data.s_id;
                cout << "请输入待插入学生的姓名:";
                cin >> newnode->data.s_name;
                cout << "请输入待插入学生的性别:";
                cin >> newnode->data.s_sex;
                cout << "请输入待插入学生的年龄:";
                cin >> newnode->data.s_age;
                cout << "请输入待插入学生的专业:";
                cin >> newnode->data.s_major;
                InsertNode(&studlist, p, newnode);
                cout << "插入成功";
                break;
            }
            default:
                cout << "选择错误 .... 重新选择 " << endl;
                break;
        }
    } while (select != 0);

    SaveFile(&studlist);
    DestroyList(&studlist);
    return 0;
}