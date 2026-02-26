#include <cstdio>
#include <cstdlib>
#include <cstring>
using namespace std;

#define MAX_NAME 20
#define MAX_PHONE 15
#define MAX_MAJOR 30
#define MAX_MEMBERS 100
#define FILE_NAME "lab_members.csv"

struct Member
{
    int career;
    int sex;
    int id;
    int group;
    char major[MAX_MAJOR];
    char name[MAX_NAME];
    int age;
    char phone[MAX_PHONE];
};

struct MemberSystem
{
    Member members[MAX_MEMBERS];
    int size;
};

void showMember(Member member)
{
    printf("职业：%s\n", (member.career == 0 ? "学生" : "教师"));
    printf("性别：%s\n", (member.sex == 0 ? "男" : "女"));
    printf("姓名：%s\n", member.name);
    printf("年龄：%d\n", member.age);
    printf("电话号码：%s\n", member.phone);
    printf("ID：%d\n", member.id);
    printf("组别：%d\n", member.group);
    printf("专业：%s\n\n", member.major);
}

void menu()
{
    printf("1.添加成员\n");
    printf("2.删除成员\n");
    printf("3.查看成员\n");
    printf("4.修改成员\n");
    printf("5.清空成员\n");
    printf("6.查找成员\n");
    printf("7.退出程序\n");
}

void saveToFile(MemberSystem* system)
{
    FILE* fp = fopen(FILE_NAME, "w");
    if (fp == NULL)
    {
        printf("文件保存失败！\n");
        system("pause");
        return;
    }
    fprintf(fp, "职业,性别,姓名,年龄,电话,ID,组别,专业\n");
    for (int i = 0; i < system->size; i++)
    {
        fprintf(fp, "%d,%d,%s,%d,%s,%d,%d,%s\n",
                system->members[i].career,
                system->members[i].sex,
                system->members[i].name,
                system->members[i].age,
                system->members[i].phone,
                system->members[i].id,
                system->members[i].group,
                system->members[i].major);
    }
    fclose(fp);
}

void loadFromFile(MemberSystem* system)
{
    FILE* fp = fopen(FILE_NAME, "r");
    if (fp == NULL)
    {
        printf("首次运行，未检测到数据文件，将自动创建！\n");
        system->size = 0;
        return;
    }
    char temp[256];
    fgets(temp, 256, fp);
    int i = 0;
    while (fscanf(fp, "%d,%d,%[^,],%d,%[^,],%d,%d,%[^,]\n",
                  &system->members[i].career,
                  &system->members[i].sex,
                  system->members[i].name,
                  &system->members[i].age,
                  system->members[i].phone,
                  &system->members[i].id,
                  &system->members[i].group,
                  system->members[i].major) != EOF)
    {
        i++;
        if (i >= MAX_MEMBERS) break;
    }
    system->size = i;
    fclose(fp);
    printf("数据加载成功，当前共有%d名成员！\n", system->size);
}

int findMemberByName(MemberSystem* system, char* name)
{
    for (int i = 0; i < system->size; i++)
    {
        if (strcmp(system->members[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1;
}

void addMember(MemberSystem* system)
{
    if (system->size >= MAX_MEMBERS)
    {
        printf("成员已满，无法添加！\n");
        return;
    }
    Member newMember;
    printf("请输入成员的职业(0为学生，1为教师)：\n");
    while (true)
    {
        scanf("%d", &newMember.career);
        if (newMember.career == 0 || newMember.career == 1) break;
        else printf("输入错误，请重新输入！\n");
    }
    printf("请输入成员的性别(0为男，1为女)：\n");
    while (true)
    {
        scanf("%d", &newMember.sex);
        if (newMember.sex == 0 || newMember.sex == 1) break;
        else printf("输入错误，请重新输入！\n");
    }
    getchar();
    printf("请输入成员的姓名：\n");
    fgets(newMember.name, MAX_NAME, stdin);
    newMember.name[strcspn(newMember.name, "\n")] = 0;
    if (findMemberByName(system, newMember.name) != -1)
    {
        printf("该姓名成员已存在，添加失败！\n");
        return;
    }
    printf("请输入成员的年龄：\n");
    scanf("%d", &newMember.age);
    printf("请输入成员的电话号码：\n");
    scanf("%s", newMember.phone);
    printf("请输入成员的ID：\n");
    scanf("%d", &newMember.id);
    printf("请输入成员的组别：\n");
    scanf("%d", &newMember.group);
    getchar();
    printf("请输入成员的专业：\n");
    fgets(newMember.major, MAX_MAJOR, stdin);
    newMember.major[strcspn(newMember.major, "\n")] = 0;

    system->members[system->size] = newMember;
    system->size++;
    printf("成员添加成功！\n");
    saveToFile(system);
}

int main()
{
    MemberSystem system;
    loadFromFile(&system);
    system("pause");
    system("cls");

    int select = 0;
    char findName[MAX_NAME];
    while (true)
    {
        menu();
        printf("请输入您的选择(数字)：\n");
        scanf("%d", &select);
        getchar();
        switch (select)
        {
            case 1:
                printf("添加成员\n");
                addMember(&system);
                system("pause");
                system("cls");
                break;
            case 2:
                printf("删除成员\n");
                if (system.size == 0)
                {
                    printf("没有成员！\n");
                }
                else
                {
                    printf("请输入要删除成员的姓名：\n");
                    fgets(findName, MAX_NAME, stdin);
                    findName[strcspn(findName, "\n")] = 0;
                    int idx = findMemberByName(&system, findName);
                    if (idx != -1)
                    {
                        for (int j = idx; j < system.size - 1; j++)
                        {
                            system.members[j] = system.members[j + 1];
                        }
                        system.size--;
                        printf("成员删除成功！\n");
                        saveToFile(&system);
                    }
                    else
                    {
                        printf("未找到该成员！\n");
                    }
                }
                system("pause");
                system("cls");
                break;
            case 3:
                printf("查看成员\n");
                if (system.size == 0)
                {
                    printf("没有成员！\n");
                }
                else
                {
                    for (int i = 0; i < system.size; i++)
                    {
                        printf("成员%d：\n", i + 1);
                        showMember(system.members[i]);
                    }
                }
                system("pause");
                system("cls");
                break;
            case 4:
                printf("修改成员\n");
                if (system.size == 0)
                {
                    printf("没有成员！\n");
                }
                else
                {
                    printf("请输入要修改成员的姓名：\n");
                    fgets(findName, MAX_NAME, stdin);
                    findName[strcspn(findName, "\n")] = 0;
                    int idx = findMemberByName(&system, findName);
                    if (idx != -1)
                    {
                        printf("请输入新的职业(0为学生，1为教师)：\n");
                        while (true)
                        {
                            scanf("%d", &system.members[idx].career);
                            if (system.members[idx].career == 0 || system.members[idx].career == 1) break;
                            else printf("输入错误，请重新输入！\n");
                        }
                        printf("请输入新的性别(0为男，1为女)：\n");
                        while (true)
                        {
                            scanf("%d", &system.members[idx].sex);
                            if (system.members[idx].sex == 0 || system.members[idx].sex == 1) break;
                            else printf("输入错误，请重新输入！\n");
                        }
                        getchar();
                        printf("请输入新的姓名：\n");
                        fgets(system.members[idx].name, MAX_NAME, stdin);
                        system.members[idx].name[strcspn(system.members[idx].name, "\n")] = 0;
                        printf("请输入新的年龄：\n");
                        scanf("%d", &system.members[idx].age);
                        printf("请输入新的电话号码：\n");
                        scanf("%s", system.members[idx].phone);
                        printf("请输入新的组别：\n");
                        scanf("%d", &system.members[idx].group);
                        getchar();
                        printf("请输入新的专业：\n");
                        fgets(system.members[idx].major, MAX_MAJOR, stdin);
                        system.members[idx].major[strcspn(system.members[idx].major, "\n")] = 0;
                        printf("成员修改成功！\n");
                        saveToFile(&system);
                    }
                    else
                    {
                        printf("未找到该成员！\n");
                    }
                }
                system("pause");
                system("cls");
                break;
            case 5:
                printf("清空成员\n");
                system.size = 0;
                printf("成员已清空！\n");
                saveToFile(&system);
                system("pause");
                system("cls");
                break;
            case 6:
                printf("查找成员\n");
                if (system.size == 0)
                {
                    printf("没有成员！\n");
                }
                else
                {
                    printf("请输入要查找成员的姓名：\n");
                    fgets(findName, MAX_NAME, stdin);
                    findName[strcspn(findName, "\n")] = 0;
                    int idx = findMemberByName(&system, findName);
                    if (idx != -1)
                    {
                        printf("成员信息如下：\n");
                        showMember(system.members[idx]);
                    }
                    else
                    {
                        printf("未找到该成员！\n");
                    }
                }
                system("pause");
                system("cls");
                break;
            case 7:
                printf("退出程序\n");
                saveToFile(&system);
                system("pause");
                return 0;
            default:
                printf("输入错误，请重新输入！\n");
                system("pause");
                system("cls");
                break;
        }
    }
    return 0;
}
