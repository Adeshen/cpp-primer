#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fstream>
#include<iostream>
#include <algorithm>
#include <conio.h>
#include<windows.h>
#include<time.h>

using namespace std;

#define OK 1
#define ERROR 0
#define MAXSEIZE 100

int cnt=0;
typedef struct user
{
    char user[50];
    char pass_word[50];
}user;

typedef struct User
{
    user data[50];
    int length;
}User;

typedef struct student
{
    char name[20];
    char sex[10];
    int age;
    int stunum;
    char Class[20];
    int dornum;
    long long number;
    int course_number;
    int sum_credit;
    char password[7]="123456";
}student,*Student;

typedef struct course
{
    int number;
    char name[50];
    int exam;
    int normal;
    float sum;
    int time;
    int credit;
    struct course* next;
}course,*Course;


typedef struct Node
{
    student data1;
    Course data2;
    struct Node *next;
}LNode,*LNodelist;


bool cmp(LNode a,LNode b)
{
    return a.data1.stunum<b.data1.stunum;
}

void record(int x)
{
    FILE *f;
    f=fopen("text1.txt","w+");
    fprintf(f,"%d",x);
    fclose(f);
}

int get_record()
{
    FILE *f;
    f=fopen("text1.txt","r");
    int x;
    fscanf(f,"%d",&x);
    fclose(f);
    return x;
}

int createlist1(LNode *L)
{
    L = new LNode[100];
    L->data2=new course;
    L->data2->next=NULL;
    return OK;
}


int createlist2(LNode *L)
{
    L=new LNode;
    L->data2=new course;
    L->data2->next=NULL;
    L->next=NULL;
    return OK;
}

void color(int x) //设置字体颜色
{
    if(x>=0 && x<=15)
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),x);
    else
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),7);
}

int  search_LNode(LNode* L,int stunum)
{
            int low=0;
            cnt=get_record();
            int high=cnt-1;
            while(low<=high)
            {
                int mid=(low+high)/2;
                if(L[mid].data1.stunum==stunum)
                {
                    return mid;
                }else if(L[mid].data1.stunum<stunum)
                {
                    low=mid+1;
                }else
                {
                    high=mid-1;
                }
            }
            return -1;
}

int deleteNode(LNode *L,long long stunum)
{
    LNode *p=L,*pre=L;
    while(p->data1.stunum!=stunum)
    {
        pre=p;
        p=p->next;
    }
    pre->next=p->next;
    free(p);
    return OK;
}

void inserlist_course(Course &L,Course &S)
{
    S->next=L;
    L=S;
}

void inserlist_Node(LNodelist &L,LNodelist &S)
{
    //LNode *p=L,*pre=L;
	S->next=L->next;
	L->next=S;
	printf("%d",L->next->data1.stunum);
}

void showMenu()
{
    cout << "****************************************************************"<< endl;
    cout << "******************** 1.录入基本信息 ****************************" << endl;
    cout << "******************** 2.修改基本信息 ****************************" << endl;
    cout << "******************** 3.学生选课情况 ****************************" << endl;
    cout << "******************** 4.学生名单及考试成绩 **********************" << endl;
    cout << "******************** 5.输出每个同学已修学分及不及格课程 ********" << endl;
    cout << "******************** 6.删除学生信息 ****************************" << endl;
    cout << "******************** 7.查看学生信息 ****************************" << endl;
    cout<<"******************** 0.退出教务系统 ****************************"<<endl;
    cout << "****************************************************************" << endl;

}

void showMenu1()
{
    cout << "****************************************************************"<< endl;
    cout << "******************** 1.查看基本信息 ****************************" << endl;
    cout << "******************** 2.查看选课情况 ****************************" << endl;
    cout << "******************** 3.退课或者选课****************************" << endl;
    cout << "******************** 4.修改登陆密码 ****************************" << endl;
    cout<<"******************** 0.退出教务系统****************************"<<endl;
    cout << "****************************************************************" << endl;
}

void input(LNode *L)
{
    cout<<"请输入姓名：";
    cin>>L[cnt].data1.name;
    cout<<"请输入性别（m男，w女）：";
    cin>>L[cnt].data1.sex;
    cout<<"请输入年龄：";
    cin>>L[cnt].data1.age;
    cout<<"请输入电话号码:";
    cin>>L[cnt].data1.number;
    cout<<"请输入班级:";
    cin>>L[cnt].data1.Class;
    cout<<"请输入学生学号:";
    cin>>L[cnt].data1.stunum;
    cout<<"输入宿舍门牌号:";
    cin>>L[cnt].data1.dornum;
    cout<<"输入选课数量:";
    cin>>L[cnt].data1.course_number;
    int i;
    for(i=0;i<L[cnt].data1.course_number;i++)
    {
        Course S;
        S = new course;
        S->next=NULL;
        printf("输入第%门课程信息:\n",i+1);
        cout<<"请输入课程名称：";
        cin>>S->name;
        cout<<"请输入课程编号：";
        cin>>S->number;
        cout<<"请输入课程学分：";
        cin>>S->credit;
        cout<<"请输入平时成绩:";
        cin>>S->normal;
        cout<<"请输入考试成绩::";
        cin>>S->exam;
        cout<<"请输入总成绩:";
        cin>>S->sum;
        cout<<"请输入重修次数（如果未重修过则输入0）:";
        cin>>S->time;
        inserlist_course(L[cnt].data2,S);
    }
    printf("课程信息输入完毕！\n");
    cnt++;
}


int show_student(LNode *L,int stunum)
{
    int a;
    a=search_LNode(L,stunum);
    if(a==-1)
    {
    cout<<"该学生不存在！"<<endl;
    system("pause");
    return 0;
    }
    LNode *p=L+a;
    color(5);
    printf("姓名\t性别\t年龄\t电话号码\t班级\t\t学号\t宿舍门牌号\t选课数量\n");
    color(15);
    printf("%s\t%s\t%d\t%I64d\t%s\t%I64d\t%d\t\t%d\n",p->data1.name,p->data1.sex,p->data1.age,p->data1.number,p->data1.Class,p->data1.stunum,p->data1.dornum,p->data1.course_number);
    while(1)
    {
        int e;
        printf("是否输入课程信息(1是,0否)：");
        scanf("%d",&e);
        if(e==1)
        {
            int i;
            color(5);
            printf("课程名称\t课程编码\t学分\t平时成绩\t考试成绩\t总成绩\t重修次数\n");
            color(15);
            for(i=0;i<p->data1.course_number;i++)
            {
                if(p->data2->sum<=100)
				cout<<p->data2->name<<"\t"<<p->data2->number<<"\t\t"<<p->data2->credit<<"\t"<<p->data2->normal<<"\t\t"<<p->data2->exam<<"\t\t"<<p->data2->sum<<"\t"<<p->data2->time<<endl<<endl;
				if(p->data2->sum>100)
				cout<<p->data2->name<<"\t"<<p->data2->number<<"\t\t"<<p->data2->credit<<"\t"<<"未登记"<<"\t\t"<<"未登记"<<"\t\t"<<"未登记"<<"\t"<<"未登记"<<endl<<endl;
                p->data2=p->data2->next;
            }
            break;
        }else if(e==0)
        {
            break;
        }else
        {
            printf("输入错误！");
            system("pause");
            return 0;
        }
    }
    return 1;
}

void show_student_course(LNode *L,int stunum)
{
    int a;
    a=search_LNode(L,stunum);
    if(a==-1)
    {
    cout<<"该学生不存在！"<<endl;
    system("pause");
    return ;
    }
    LNode *p=L+a;
            int i;
            color(5);
            printf("课程名称\t课程编码\t学分\t平时成绩\t考试成绩\t总成绩\t重修次数\n");
            color(15);
            for(i=0;i<p->data1.course_number;i++)
            {
                if(p->data2->sum<=100)
				cout<<p->data2->name<<"\t"<<p->data2->number<<"\t\t"<<p->data2->credit<<"\t"<<p->data2->normal<<"\t\t"<<p->data2->exam<<"\t\t"<<p->data2->sum<<"\t"<<p->data2->time<<endl<<endl;
                p->data2=p->data2->next;
            }
}

void write_file1(LNode *S,const char filename[])
{
    ofstream f("text.txt");
    //FILE *fp;
    //fp=fopen(filename,"w+");
    int i;
    //f<<S->data1.name<<S->data1.sex<<S->data1.age<<S->data1.number<<S->data1.Class<<S->data1.stunum<<S->data1.dornum<<S->data1.course_number;
    for(i=0;i<cnt;i++)
    {
        f<<S->data1.name<<endl<<S->data1.sex<<endl<<S->data1.age<<endl<<S->data1.number<<endl<<S->data1.Class<<endl<<S->data1.stunum<<endl<<S->data1.dornum<<endl<<S->data1.course_number<<endl<<S->data1.password<<endl;
        //fprintf(fp,"%s\t%c\t%d\t%d\t%d\t%I64d\t%d\t%d\n",S->data1.name,S->data1.sex,S->data1.age,S->data1.number,S->data1.Class,S->data1.stunum,S->data1.dornum,S->data1.course_number);
        int i;
        Course  E;
        E=S->data2;
        for(i=0;i<S->data1.course_number;i++)
        {
            f<<E->name<<endl<<E->number<<endl<<E->credit<<endl<<E->normal<<endl<<E->exam<<endl<<E->sum<<endl<<E->time<<endl;
            //fprintf(fp,"%s\t%d\t%d\t%d\t%d\t%d\t%d\n",E->name,E->number,E->credit,E->normal,E->exam,E->sum,E->time);
            E=E->next;
        }
        S++;
    }
    f.close();
    //fclose(fp);
}


void write_file2(LNodelist &S,const char filename[])
{
    ofstream f(filename);
    int i;
    cnt=get_record();
    //LNodelist S=L->next;
    while(S!=NULL)
    {
		 f<<S->data1.name<<endl<<S->data1.sex<<endl<<S->data1.age<<endl<<S->data1.number<<endl<<S->data1.Class<<endl<<S->data1.stunum<<endl<<S->data1.dornum<<endl<<S->data1.course_number<<endl<<S->data1.password<<endl;
        int i;
        Course  E;
        E=S->data2;
        for(i=0;i<S->data1.course_number;i++)
        {
            f<<E->name<<endl<<E->number<<endl<<E->credit<<endl<<E->normal<<endl<<E->exam<<endl<<E->sum<<endl<<E->time<<endl;
            E=E->next;
        }
    S=S->next;
    }
    //fclose(fp);
    f.close();
}


void read_file1(LNode*S,const char filename[])
{
    ifstream f;
    f.open(filename);
    cnt = get_record();
    int j;
    for(j=0;j<cnt;j++)
    {
         f>>S->data1.name>>S->data1.sex>>S->data1.age>>S->data1.number>>S->data1.Class>>S->data1.stunum>>S->data1.dornum>>S->data1.course_number>>S->data1.password;
        int i=S->data1.course_number;
        while(i>0)
        {
            Course E;
            E=new course;
            E->next=NULL;
            f>>E->name>>E->number>>E->credit>>E->normal>>E->exam>>E->sum>>E->time;
            inserlist_course(S->data2,E);
            i--;
        }
        S++;
    }
    sort(S,S+cnt,cmp);
     f.close();
}


void read_file2(LNodelist &L,const char filename[])
{
    //FILE *fp;
    //fp=fopen(filename,"r");
    ifstream f;
    f.open(filename);
    cnt=get_record();
    int j;
    for(j=0;j<cnt;j++)
    {
        LNodelist S;
        S=new LNode;
        S->next=NULL;
        f >>S->data1.name>>S->data1.sex>>S->data1.age>>S->data1.number>>S->data1.Class>>S->data1.stunum>>S->data1.dornum>>S->data1.course_number>>S->data1.password;
		int i=S->data1.course_number;
        while(i>0)
        {
            Course E;
            E=new course;
            E->next=NULL;
            //fscanf(fp,"%s\t%l64d\t%d\t%d\t%d\t%d\t%d\n",&E->name,&E->number,&E->credit,&E->normal,&E->exam,&E->sum,&E->time);
            f>> E->name>>E->number>>E->credit>>E->normal>>E->exam>>E->sum>>E->time;
            inserlist_course(S->data2,E);
            i--;
        }
       	S->next=L->next;
        L->next=S;
    }
    //fclose(fp);
    f.close();
}


void write_file_user(User &U)
{
    ofstream f("text3.txt");
    int i;
    int n=U.length;
    f<<n<<endl;
    for(i=0;i<n;i++)
    {
        f<<U.data[i].user<<endl;
        f<<U.data[i].pass_word<<endl;
    }
    f.close();
}

void read_file_user(User &U)
{
    ifstream f("text3.txt");
    f>>U.length;
    int i;
    for(i=0;i<U.length;i++)
    {
        f>>U.data[i].user;
        f>>U.data[i].pass_word;
    }
    f.close();
}

void show_course_byclass(LNode *L,char x[])
{
    int i;
    int flag=0;
    cnt=get_record();
    for(i=0;i<cnt;i++)
    {
        if(strcmp(L[i].data1.Class,x))
        {
            flag=1;
            color(14);
            printf("姓名\t学号\n",L[i].data1.name,L[i].data1.stunum);
            color(10);
            printf("%s\t%d\n",L[i].data1.name,L[i].data1.stunum);
            int j;
            Course l = L[i].data2;
            color(14);
			printf("课程名称\t课程学分\t成绩\n");
            for(j=0;j < L[i].data1.course_number;j++,l=l->next)
            {
				if(l->sum>100) continue;
				color(15);
                printf("%s\t%d\t\t",l->name,l->credit);
                if(l->sum==0)
                {
                	color(4);
					printf("%.2f\n",l->sum);
					color(15);
				}else
				{
					printf("%.2f\n",l->sum);
				}
            }
			cout<<endl;
        }

    }
    if(flag==0)
    {
        color(15);
		printf("没有该班级\n");
        system("pause");
    }
    color(15);
}

void delete_student(LNodelist &head)
{
    int data,flag=0;
    cout<<"请输入要删除学生的学号(输入0退出删除):";
    cin>>data;
    if(data==0)
        goto E1;
    LNodelist p1, p2;
	if (head == NULL)
    {
		printf("没有数据！\n");
	}
	if (head->data1.stunum == data) {
		p2 = head;
		head = head->next;
		color(4);
		printf("该学生已删除！\n");
		color(15);
		flag=1;
	}
	else
	{
		p1 = head;
		p2 = head;
		while (p2->data1.stunum!=data && p2->next!=NULL)
		{
			p1 = p2;
			p2 = p2->next;
		}
		if (p2->data1.stunum== data)
        {
			p1->next = p2->next;
			free((void *)p2);
			color(4);
			printf("该学生已删除\n");
			color(15);
			flag=1;
		}
		else
        {
            printf("未找到该学生\n");
        }
	}
    if(flag==1)
         cnt--;
    record(cnt);
    E1:
    system("pause");
}

void inputPasswd(char passwd[],int max)
{
	char s[20],s1[20];
	char temp[2];
	int n;
	strcpy(s," ");
	while(1)
	{
		while(1)
		{
			n=getch();
			if(n == 13)
			{
				break;
			}
			if(n=='\b')
			{
				printf("\b");
				printf(" ");
				printf("\b");
				int l=strlen(s);
				int k;
				for(k=0;k<l-1;k++)
                {
                    s1[k]=s[k];
                }
                strcpy(s,s1);
			}else
			{
			printf("*");
			memset(temp,0,sizeof(temp));
			sprintf(temp,"%c",n);
			strcat(s,temp);
			}
		}
		if(strlen(s) > max+1)
		{
			memset(s, 0, sizeof(s));
			printf("\n密码过长请重新输入:");
			strcpy(s," ");
			continue;
		}
		if(strlen(s) < max+1)
		{
			memset(s, 0, sizeof(s));
			printf("\n密码过短请重新输入:");
			strcpy(s," ");
			continue;
		}
		break;
	}
	printf("\n");
	strcpy(passwd, s+1);
}

void Gotoxy(int x, int y)
{
    COORD pos;
    pos.X = x - 1;
    pos.Y = y - 1;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),pos);
}

void Loading()
{
    srand(time(NULL));
    color(3);
    printf("\n\n\n\n\n\n\n");
    printf("                                                        _                     _ _             \n");
    printf("                                                       | |                   | (_)            \n");
    printf("                                                       | |     ___   __ _  __| |_ _ __   __ _ \n");
    printf("                                                       | |    / _ \\ / _` |/ _` | | '_ \\ / _` |\n");
    printf("                                                       | |___| (_) | (_| | (_| | | | | | (_| |\n");
    printf("                                                       |______\\___/ \\__,_|\\__,_|_|_| |_|\\__, |\n");
    printf("                                                                                         __/ |\n");
    printf("                                                                                        |___/ \n\n\n");
    color(11);
	printf("                                                    ┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓\n");
    printf("                                                    ┃                                          ┃\n");
    printf("                                                    ┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛\n");
    Gotoxy(55,19);
    for(int i=0;i<20;i++)
    {
        color(13);
		printf("█");
        Sleep(rand()%300);
    }
    color(15);
    system("cls");
}

void show_picture1()
{
    cout<<"\t\t: :.:::.:.:::::::.:.:.:.:.:.:.:::::.:.:::.:.:.:::.:.:::.:.:.:.:.:::::::::.:.:.:::.:.:::.:.:.:.:.::: "<<endl;
cout<<"\t\t: :.:.:.:.:.:.:...   .:.:.:.......:..   ....:.:.:........   ....:.:.........:..  .:...:...:.:.:.:.:  "<<endl;
cout<<"\t\t. .:............. QB2 .........   .. 7DK.   .......      :BP   ......       . IBg. ................  "<<endl;
cout<<"\t\t: :........       BB.   ..... sBBP  rQBI .7:...... 7SgBR1BPYBBu .... Lj7PBBL  .BB   ..............:  "<<endl;
cout<<"\t\t. .......::iLqq7 MB7.u1r...... :dXLQB7 2KKQBX .....2:QB77B5MJ:...... SBdjBg.   BBius ..............  "<<endl;
cout<<"\t\t: :......KRKjBB1UBKYEBBB: ...  :. .BB .BM BQ. ... .bBBs i7QQI    ... .B7iB  5EZBBIXv  ............:  "<<endl;
cout<<"\t\t. ....... Xq BQ.MqX7 gL .... uDBB5 QBdUBMvQB ....  SBLrXIY :BBBq7:.. .BPvBB :7rBB71EQQ.............  "<<endl;
cout<<"\t\t: :......  PBBi  sBK   ....... BB .BBP BdsB1 ... .BB2jvr7SBQ.5BQQP:. .Bb.dBKP52BBrYUvi............:  "<<endl;
cout<<"\t\t. .......  YBBBi MBBi  ......  sBv QY .BP   ....JBg  BBrrbB1      .. .BE   KR  BD .BQ  ............  "<<endl;
cout<<"\t\t: :.....  QBU:BI7BU5Bq    . dQBXBQPJ: .BL     ..:    DBr:dBv   ..... :BZ   uBr BB:UBb ............:  "<<endl;
cout<<"\t\t. ......:BBi  :DBq  EBBMJ:...r.  .jEBBBBRDZgZP:..... DBi.BB1uPU..... gBg . BBBRMKsQBu .............  "<<endl;
cout<<"\t\t: :.......  ..PS. .  5BBBb... ...    .uPBBBgKr... PQQqdEgZSPRBB:.... rBu ..X5.    YB: ............:  "<<endl;
cout<<"\t\t. ............   ....     ...........        ..... .           ......   ...   ....   ..............  "<<endl;
cout<<"\t\t: ................................................................................................:  "<<endl;
cout<<"\t\t. .................................................................................................  "<<endl;
cout<<"\t\t: :................................  .......................  ....................................:  "<<endl;
cout<<"\t\t. ...........   ....   ........... ..  .................    :. .........  ....   ..................  "<<endl;
cout<<"\t\t: .......... qBS    bQX .........  BBs   ...........   ..7bBBQv ....... vi... vPU. ...............:  "<<endl;
cout<<"\t\t. .......... 7Bd Ji BB5 ........  DBBIQBE ..........IZPPBBE:  ........  BB     EBI ................  "<<endl;
cout<<"\t\t: :......   2dBPRBPUBi   ...... iBBgruBQr ..........  idQr IBu ......  DBiKd7sLJPQBJ .............:  "<<endl;
cout<<"\t\t. .......7ivsIBZBduBqrgBB7 ... LQ1 vBBB:     ...... uBBgruBBu. ..... iBB:SBg7vBBJ:  ...............  "<<endl;
cout<<"\t\t: :.....:MBbJjBBvYBrqQQi:....    7MBP.vBBR5r....... :vrjMPivbv ..... gBuQB.  YBrYBBi .............:  "<<endl;
cout<<"\t\t. ......   .QBPBdPQ sB.  ....iSRBQ7XQR7XBBBBBRi... .gBBBDPs2BBq ..... iBQ5v.MBBMBIE7  .............  "<<endl;
cout<<"\t\t: :..... rZQJ:BQv rBBE  .....rSiLJLBBi7BB    ...... 5Ii SQY  .  ..... IDr7U  BBJB:   :............:  "<<endl;
cout<<"\t\t. ......XQBMP5BB  7BBB1.   ...    SBr  BB  ....... .BB  rBv BBBJ ... 7udMdvIBB uB   .Bs ...........  "<<endl;
cout<<"\t\t: :...... :2jiBBrDBJ bBBBD1....  BBj. gB5 ....... .BBL .2BK  qBB ... XBg::MB1  7BBdZBBD ..........:  "<<endl;
cout<<"\t\t. ........  .BBJ      .v11i....qBB: YBBB ..........i   EBBu     .....    i.  .. .XbE2: ............  "<<endl;
cout<<"\t\t: ..........    ......    .....L:  . 7S  .......... ... U1 .............. ......      ............:  "<<endl;
cout<<"\t\t. .............................  ....  .................  .........................................  "<<endl;
cout<<"\t\t: :...............................................................................................:  "<<endl;
cout<<"\t\t. .:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.:.::  "<<endl;
}

void show_picture2()
{
    cout<<"BBBBBBBBBBBBBQBQBBBBBBBBBQBQBBBBBBBBBQBBBBBBBBBBBBBBBQBQBBBBBQBBBBBBBBBQBBBQBBBQ"<<endl;
cout<<"BBBBBBBBBBBBBBQBBBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBBBBBQBQBBB"<<endl;
cout<<"BQBBBQBBBBBBBQBBBQBBBBBBBBBBBBBBBBBMgdbqPKdEgQBBBBBBBBBBBQBBBBBQBBBBBBBBBBBBBBBQ"<<endl;
cout<<"BBBBQBQBBBBBBBBBQBBBBBQBBBBBgXLr:..          ...:7udQBBBBBBBBBBBBBBBBBBBBBBBBBBB"<<endl;
cout<<"BBBBBBBQBBBBBBBBBBBBBBBBDjr.. ... .           . . . .:75BBBBBBBBBBBQBQBBBQBBBBBB"<<endl;
cout<<"BBQBBBBBBBQBQBBBBBBBBZ7:......                     ......iuQBBBB27QBBBBBBBBBBBQB"<<endl;
cout<<"BBBBBBBQBBBBBBBBBBBJ:.....                             .....rPBQ  JQBBBBBBBQBBBB"<<endl;
cout<<"QBBBBBQBBBQBBBBBRv..::.                                   .:..U7   gBBBBBBBBBBBB"<<endl;
cout<<"BBBBBQBQBBBBBBBv..::.                                        7d    7RQBBBBBBBBBB"<<endl;
cout<<"BBBBBBBBBBBBB5..::.                                         .gs    :jQBBQBQBQBBB"<<endl;
cout<<"BBBBBBBBBBBB7.:::                                          .gb.     sJBQBBBBBBBB"<<endl;
cout<<"QBBBBBBBBBZ:.::.                                          .bEv      .1jBBBBBBBBB"<<endl;
cout<<"BBBBBBBBBK:.i:.   . .                             .     ..5E2        7J2BBBBBBBQ"<<endl;
cout<<"BBBBBBBBq.:i:....... . .     . .                       ..7ES:    .   .jLdBBBBBBB"<<endl;
cout<<"BBBQBBBE::i:....... ... .               .   .         ..:KPJ  ......  7s1BBBBQBQ"<<endl;
cout<<"QBQBBBBi:i:........... .             . . . . .        ..iE2Y. ........71YKBBBBBB"<<endl;
cout<<"BQBBBBv:ii:..............  .v1Ur    . . . .     :LIui  .751L7::...::irussrZBBBBB"<<endl;
cout<<"BBBBBE:ii:..............  jBBBBBQ7   . . .    .PBBBBBg:.isYY77rrr7rvLjJs7r7BBBBB"<<endl;
cout<<"BQBBB7:ii::.:..........  5Bb2uUIgBL  ......  .gQqU1jXMQi:rYsjLL7v7vLjJj777rKBBBQ"<<endl;
cout<<"BBBBgiiri:::.:......... 7BX1JUu1uEQ: ......  SQ5J1u1s2DZ:irvLujuJuJUjsrrvvrvBBQB"<<endl;
cout<<"BBBQ5:rii::::::........ dDIXPSKKKIQu ...... .Rb5PXXXPSKQv.rirrvvsYY7rir7v7riQBBB"<<endl;
cout<<"BBBBviri::::::.:.:.... .DgPv.  .sZgP ...... :BDbi   :5EQ1.:ririiiiirr77rrrriPBBB"<<endl;
cout<<"BBBBvirii::::::::.:.:...BB:   .  vBd ...... iBR.  .   SBI ::iirrrrrrririiiriSQBB"<<endl;
cout<<"BBBBrrrii:::::::.:.:....K7 .....  qu ........d: .....  E:..::::i:i:::::iirri2BBB"<<endl;
cout<<"BBBB7rrii::::::.:...:...  .......   .........  ........ ..:.:.:::.::::::irri5BBB"<<endl;
cout<<"BBBB7rrrii::::................................................ ..:.::::iirrrXBBB"<<endl;
cout<<"BQBBjr7rrii:::.:vi:.  . .................................   ..r7:.::::iirr7iDBBB"<<endl;
cout<<"BBBBXrr7ii:i::.1BBBBEXY7::..                         ..irj5DQBBBS.:::i:ri7r7QBQB"<<endl;
cout<<"BQBBQr7rrii:i:.uB:ijbRBBBBBBQEP52ujLL7v7vvLvYsUUSqZRBBBBBBQPU:rB2.::iiiirrrJBBBB"<<endl;
cout<<"BBBBBur7rrii::.rBi     ..i71SZgQBBBBQBBBBBBBBBBBQREP2Yi:.     rB:.:i:iirr7iDBBBB"<<endl;
cout<<"BQBBBgr77rrii::.EQ. .                                        .BK..::iirr7rsBBBBQ"<<endl;
cout<<"BBBBQBUr77rrii:.iBb:.                                      .:EQ:.:iiirr77rgBBBBB"<<endl;
cout<<"BQBQBQBv777rrii:.7Bgdq5Y7:.                         .:rvIXdEQQr.::iirr77rXBBBBBQ"<<endl;
cout<<"BBQBBBBQr777rrii:.rgPXKdZgDgZdKXUUJsvv7v7LvujISqPDZMgMgDPP5bEr.:iiirr77ruBBBBBBB"<<endl;
cout<<"BQBBBBBBQrr77rrii:.iPq2sjj1USIKKbPddZdEdZEZbEPbKqII1UJjsu1bK:.::iirr77rsBBBQBBBB"<<endl;
cout<<"QBBBQBBBQQ7777rrii:..jPq1ujjjjs1Juj1sjJujuJ1jjJusujjJuJ2KdL..iiiirr77rjBBBBBBBBB"<<endl;
cout<<"BQBBBBBBBBBvr77r7rri:.:udKIJjJuJjJuJ1juJuJ1JuJuj1suj1UqP1:.:iirrrr7rrIBQBBBBBBBB"<<endl;
cout<<"QBBBBBBBBBBB2rr777rrii:.:JKP5IuuJujuJuJuJujuj1juj1UqPqL:.::iirr777r7ZBBBBBQBBBBB"<<endl;
cout<<"BQBBBBBBBBBBBgYi777rriri:..i1SPKSIIUUu1juuUjUUSXPKSsr..:iirrrr7rrrIQBBBBBBBBBBBB"<<endl;
cout<<"BBBBBBBBBBBBBBBb7rr7r7rrri::..:7Y2IKXqKPKqKq55Usr:...:irrrr7r7rrsRBBBBBBBBBBBBBB"<<endl;
cout<<"BBBBBBBBBBBBBBBBBPvirr7r7rrii::.....::i:i::::...::iiirrr7r7rrr1gBBBQBBBBBBBBBBBB"<<endl;
cout<<"QBBBQBBBBBBBQBBBBBBDjrirr7rrrrrrrrii:::::::i:iirrrrrr7r7rriv5QBBBBQBBBQBBBBBQBBB"<<endl;
cout<<"BBBBBBBBBBBQBQBBBBBQBBdJ7rrrrrrr7rrrrrrrrrrrrrrr7r7rrirrv2gBBQBBBBBBBBBQBBBBBBBB"<<endl;
cout<<"QBBBBBQBBBQBQBBBBBBBBBBBBg5s7rrririrr7rrrrrrrrrriri771PQQBBBBBBBBBBBBBQBBBBBBBBB"<<endl;
cout<<"BBBBBBBBBBBQBBBQBBBBBBBBBBBBBQZKIJs7777r7r7r77sj5qgQBQBBBQBBBBBBBBBBBQBBBBBQBBBB"<<endl;
cout<<"BBBBBBBBBBBBBBBBQBQBBBBBBBQBQBBBBBBBBBQBQBBBBBBBQBQBBBBBBBBBBBQBQBBBBBBBBBBBBBBB"<<endl;
cout<<"BBBQBQBQBBBBBBBBBBBBBQBQBBBBBBBBBBBBBQBQBBBBBBBBBBBBBQBQBBBQBBBBBBBBBQBQBBBBBBBQ"<<endl;
}

void show_picture3()
{
cout<<"                                                                                                                        "<<endl;
cout<<"                                                                                                                        "<<endl;
cout<<"                                                                                                                        "<<endl;
cout<<"                                                                                                                        "<<endl;
cout<<"                                                       ...:::....                                                       "<<endl;
cout<<"                                                  ..::i:::::::::::i:..                                                  "<<endl;
cout<<"                                               .::::...... ........::i::.                                               "<<endl;
cout<<"                                             .:::.        . ...     ..::i:.                                             "<<endl;
cout<<"                                            ::..   .             ...   ..i:.                                            "<<endl;
cout<<"                                          .i:.. .7KPKPS:       iSqXqq7....::i                                           "<<endl;
cout<<"                                         :i:.  :KX:   iPj    .jPi   .22i..::ii.                                         "<<endl;
cout<<"                                        :r:.. .uq       PY   7Z.      u5..:.:ir.                                        "<<endl;
cout<<"                                       .7i.  .:5i   .   rP   1v   .   .X:..:::7r                                        "<<endl;
cout<<"                                       rv.    :1i PBBBL.v1   vj.uBBQb.i2:...::iri                                       "<<endl;
cout<<"                                       v:. .   rYgBBBBBQ2:   :jgBBBBBQ17...::::7v                                       "<<endl;
cout<<"                                      7gdPbbK:  :UgQBQEu:     :uPQBBg1i....::::rI                                       "<<endl;
cout<<"                                    .qZv::.:KE:   ..:..         .:::.. ....::::vU.                                      "<<endl;
cout<<"                                   .RS      .bu             ..           .:.::i7K.                                      "<<endl;
cout<<"                                   IK.       UP7:r:    . ... . . ...  iJi..::::1J                                       "<<endl;
cout<<"                                  .Zs   . .  7dgEKgu. .............  iBBu.::::7Ui                                       "<<endl;
cout<<"                                  :Er  ....  7qq. 7d:  ... . ...    7BBd .:::i1u                                        "<<endl;
cout<<"                                  .Zs  ....  rDv  i57            .LZBB1  .:.:1I.                                        "<<endl;
cout<<"                                   SS. ......iLi  :EBM5s7r:ir7vXRBBBU.  :::i2d.                                         "<<endl;
cout<<"                                   rMv  .....     rSSEBBBBBBBBBQMui   .:::vPq.                                          "<<endl;
cout<<"                                    ugi  ....... .LS.  ..:ii...    ..:::r5Pv                                            "<<endl;
cout<<"                                     2Qr........ :X2. .       ....:.:isqZJ.                                             "<<endl;
cout<<"                                      1Qv..:.:..:2Rb7r::::...::::r71PZqJ.                                               "<<endl;
cout<<"                                       sZr.::::iEI:ijbgPPS5U52qqbdP1i.                                                  "<<endl;
cout<<"                                       :dY:iii:rDv     .:iLuv7i:.                                                       "<<endl;
cout<<"                                       7Bu:iriivB1                                                                      "<<endl;
cout<<"                                        :. ... .:.                                                                      "<<endl;
}

void show_picture4()
{
        cout<<"	                        .:i:i.                       "<<endl;
cout<<"                               i::...:::                             "<<endl;
cout<<"                              Pvi.:.::i72v                           "<<endl;
cout<<"                              P7::::.:::iJS                          "<<endl;
cout<<"                              Y1:.:::.::::j5                         "<<endl;
cout<<"                              .q::.:::.::::P:                        "<<endl;
cout<<"                               I7.:::::::::j2                        "<<endl;
cout<<"                               7Y:.::::::::u5                        "<<endl;
cout<<"                               .u::::.:.::i5I                        "<<endl;
cout<<"                               .L:::::.::irgi                        "<<endl;
cout<<"                               r7:::::::iiIM                         "<<endl;
cout<<"                              :j::.:::.::7dv                         "<<endl;
cout<<"                             .Ui:.::::::ird.                         "<<endl;
cout<<"                            :Ui:.:::::.::rK.                         "<<endl;
cout<<"                           72i:.::::::::iiLj                         "<<endl;
cout<<"                         :2j::.::::::::::ii7jr.                      "<<endl;
cout<<"                        JI7:..:::.::::::::::rYI51vi.....:::...       "<<endl;
cout<<"                      rXv:.:::::::::::.:.:rYvv7rrr7vr7r7r7777LYY:    "<<endl;
cout<<"        :ii::....   .sJ::.:::.:::.:::::.rYriii::....:.:...:.:.:iI7   "<<endl;
cout<<"       vJJLsYJYjYsvXsr:..:::::::.:::.:.iJ::::i:::..:.:::.:.:...:iZ.  "<<endl;
cout<<"      7ri:::::::::ii:.:.:.:::::::::.:.:us.::iiii::..:.:.:.:...::LQ.  "<<endl;
cout<<"     i::.:.:.:...:...:.:::::::::::.:::iXqi::iiiii:.:.:.:::::::rqQL   "<<endl;
cout<<"    .i:::::.:::::::::.:::::::.:::.::iirUBBKjJYuYL77r7r7r77s1PQBv     "<<endl;
cout<<"    ::::::::::::::::::::::::::::.::iirrsXBQBRDZgDgEgDggQQBBBBBD7.    "<<endl;
cout<<"    i::::::::::::::::.:::.:::::::::irr771dUri:iii::.:::::......iUs   "<<endl;
cout<<"    i:::::::::::::::.:::::.:::::::iiirrr5J:::::i::.............:iEv  "<<endl;
cout<<"   .i::::::::::::::::::::.::::::::iirrrrPv::iirri:::::::::::::::7Z1  "<<endl;
cout<<"   .i::::::::::::::::::::::::::::i:ririrSD7iirrri:::.:::::::::iYdg   "<<endl;
cout<<"   .i::::::::::::::.:::.::::::::::iirrrrLbBRgZgEdqSII11u1uIUSKPU7    "<<endl;
cout<<"   .i:::::::::.:::.::::::::::::::::iiiiiiuQQDZbDDQRBBBBBQQgRDQK      "<<endl;
cout<<"    r::::::::::::::::::::::::::::::iiiiiiP1:::i::.............rv     "<<endl;
cout<<"    ii:::::::::i:iiri::i:i:iii:i:::::iii7X::iiiri:...........:iU7    "<<endl;
cout<<"    .ri:i:iiiiiiirr7ji::iiriiii:i:i:i:i:LKr:iirrr:::::::::::::rqJ    "<<endl;
cout<<"     rriiiiiiiirr77vUgj7rririririiii:i:i7dZu7v77ri:::::::::rv5Zd     "<<endl;
cout<<"      7s7r77vvLsuuXqRBBBZs7irirrririiiii71MBBBBRRZdqqSX5XXZK1L:      "<<endl;
cout<<"       rKgddDQBBBBBBBBBMIQQSv7rrrrrrrrrrrvqd25SPbgRQQBBBBBBQ         "<<endl;
cout<<"         rDBBBMXL:.       JQBQPjY77r7777vvSi:::::.........:uY        "<<endl;
cout<<"                            .IQBQBBgPPS5uXdj77rri:::.:.:.:iSS        "<<endl;
cout<<"                                :JgBBBBBBQBBDPXjLrrrrrvvuXBB:        "<<endl;
cout<<"                                             .i77LLJsusJvr.          "<<endl;
}

int landing1()
{
        LNode *D;
        D=new LNode[500];
        read_file1(D,"text.txt");
        cnt=get_record();
        sort(D,D+cnt,cmp);
        int stunum1;
        char password1[7];
        L5:
        cout<<"请输入学号：";
        cin>>stunum1;
        cout<<"请输入密码:";
        inputPasswd(password1,6);
        int mid1=search_LNode(D,stunum1);
        if(strcmp(D[mid1].data1.password,password1)==0)
          {
              system("cls");
			  cout<<"登陆成功！"<<endl;
              show_picture4();
              system("pause");
          }
        else if(mid1==-1||strcmp(D[mid1].data1.password,password1)!=0)
        {
            color(4);
			printf("账号或密码输入错误，请重新输入\n");
			color(15);
            system("pause");
            system("cls");
            goto L5;
        }
        return stunum1;
}

void landing2()
{
    User U;
    read_file_user(U);
    char user[50];
    char password[6];
L1:
    cout<<"请输入账号：";
    cin>>user;
    cout<<"请输入密码：";
    inputPasswd(password,6);
    int i;
    for(i=0;i<U.length;i++)
    {
        if(strcmp(U.data[i].user,user)==0)
        {
            if(strcmp(password,U.data[i].pass_word)==0)
            {
                system("cls");
				printf("登陆成功!\n");
                show_picture4();
                break;
            }
        }
    }
    if(i==U.length)
    {
        system("cls");
        show_picture2();
        printf("账号或密码输入错误请从新输入！\n");
        system("pause");
        system("cls");
        goto L1;
    }
    system("pause");
    system("cls");
}

void show_student_bycourese(LNode *L,char course_name[])
{
    int i;
    color(9);
	printf("姓名      平时成绩      考试成绩        总成绩\n");
	color(15);
    cnt=get_record();
    for(i=0;i<cnt;i++)
    {
        int j;
        Course C= L[i].data2;
        for(j=0;j< L[i].data1.course_number;j++)
        {
            if(strcmp(C->name,course_name)==0&&C->sum<=100)
            {
                printf("%-8s  %-8d\t%-8d\t",L[i].data1.name,C->normal,C->exam,C->sum);
                if(C->sum==0)
                {
                	color(4);
                	printf("%-8.1f\n",C->sum);
                	color(15);
				}else
				{
					printf("%-8.1f\n",C->sum);
				}
                break;
            }
            C=C->next;
        }
    }
}

void show_stude_nopass(LNode *L)
{
    int i;
    for(i=0;i<cnt;i++)
    {
        Course C;
        C=L[i].data2;
        int j;
        int n=L[i].data1.course_number;
        L[i].data1.sum_credit=0;
        for(j=0;j<n;j++)
        {
            if(C->sum!=0&&C->sum<=100) L[i].data1.sum_credit+=C->credit;
            C=C->next;
        }
        C=L[i].data2;
        color(9);
        printf("姓名\t班级\t\t学号\t总学分\n");
		color(15);
		printf("%s\t%s\t%d\t%d\n",L[i].data1.name,L[i].data1.Class,L[i].data1.stunum,L[i].data1.sum_credit);
        color(9);
		printf("不及格课程:");
        int flag=0;
        for(int k=0;k<n;k++)
        {
            if(C->sum==0)
               {
                   flag=1;
                   color(4);
                   printf("%s  ",C->name);
               }
            C=C->next;
        }
        color(2);
        if(flag==0) printf("无");
        printf("\n\n");
    }
    color(15);
    system("pause");
}

void keydown2()
{
	int choice = 0;

	while(1)
    {
        system("cls");
        showMenu();
            color(4);
    cout<<"请选择：";
    color(15);
        scanf("%d",&choice);
        switch(choice)
        {
		case 0:
		    system("cls");
            show_picture3();
		    printf("退出系统\n");
		    exit(0);
			break;
		case 1:
            system("cls");
            LNode *L;
            L=new LNode[500];
            int choice1;
            cout<<"1.输入学生名单"<<endl;
            cout<<"2.输入部分学生"<<endl;
            cout<<"0.退出输入"<<endl;
            cin>>choice1;
            int x;
            if(choice1==1)
            {

            printf("请输入要输入的学生人数:");
            scanf("%d",&x);
            int i;
            for(i=0;i<x;i++)
            {
                printf("输入第%d个学生信息\n",i+1);
                input(L);
            }
            system("cls");
            printf("学生信息输入完毕!\n");
            sort(L,L+cnt,cmp);
            write_file1(L,"text.txt");
            record(cnt);
            system("pause");
			break;
            }else if(choice1==2)
            {
                read_file1(L,"text.txt");
                cnt=get_record();
                printf("请输入要输入的学生人数：");
                scanf("%d",&x);
                int i;
                for(i=0;i<x;i++)
                {
                    printf("输入第%d个学生信息\n",i+1);
                    input(L);
                }
                printf("改学生信息输入完毕!\n");
                sort(L,L+cnt,cmp);
                write_file1(L,"text.txt");
                record(cnt);
                system("pause");
                break;
            }else
            {
                break;
            }
		case 2:
		    system("cls");
		    LNode *p3;
		    //createlist2(S);
		    p3=new LNode[500];
            while(1)
            {
                L2:
                read_file1(p3,"text.txt");
                printf("请输入要修改的学生学号(输入0退出修改):");
                int stunum;
                scanf("%d",&stunum);
                if(stunum==0)
                    break;
                int n=search_LNode(p3,stunum);
                if(n==-1)
                {
                    printf("没有该学生，请重新输入!");
                    system("pause");
                    system("cls");
                    goto L2;
                }
                LNodelist p=p3+n;
                printf("1.修改基本信息\n2.修改课程信息\n");
                int e;
                scanf("%d",&e);
                if(e==1)
                {
                    while(1)
                    {
                        printf("1.修改姓名\n2.修改学号\n3.修改年龄\n4.修改性别\n5.修改班级\n6.修改宿舍门牌号\n7.修改电话号码\n8.修改总学分\n0.退出修改\n");
                        int r;
                        scanf("%d",&r);
                        switch(r)
                        {
                        case 1:
                            printf("请输入姓名:");
                            char name[20];
                            scanf("%s",name);
                            strcpy(p->data1.name,name);
                            break;
                        case 2:
                            printf("请输入学号:");
                            int temnum;
                            scanf("%d",&temnum);
                            p->data1.stunum=temnum;
                            break;
                        case 3:
                            printf("请输入年龄:");
                            int x;
                            scanf("%d",&x);
                            p->data1.age=x;
                            break;
                        case 4:
                            printf("请输入性别（m男，w女）:");
                            char ch[10];
                            cin>>ch;
                            strcmp(p->data1.sex,ch);
                            break;
                        case 5:
                            printf("请输入班级:");
                            char ban[20];
                            scanf("%s",ban);
                            strcpy(p->data1.Class,ban);
                            break;
                        case 6:
                            printf("请输入宿舍门牌号:");
                            int su;
                            scanf("%d",&su);
                            p->data1.dornum=su;
                            break;
                        case 7:
                            printf("请输入电话号码:");
                            int dian;
                            scanf("%d",&dian);
                            p->data1.number=dian;
                            break;
                        case 8:
                            printf("请输入总学分:");
                            int cre;
                            scanf("%d",&cre);
                            p->data1.sum_credit=cre;
                        case 0:
                            break;
                        }
                        if(r==0)
                            break;
                    }
                    }else if(e==2)
                    {
                        while(1)
                        {
                            printf("请输入要修改的课程名称:");
                            char classname[50];
                            scanf("%s",&classname);
                            Course q=p->data2,pre=p->data2;
                            while(q!=NULL&&strcmp(q->name,classname)!=0)
                            {
                                pre=q;
                                q=q->next;
                            }
                            if(q==NULL)
                            {
                            printf("没有该课程");
                            continue;
                            }
                            int t;
                            printf("1.修改考试成绩\n2.修改平时成绩\n3.删除课程\n0.退出修改");
                            scanf("%d",&t);
                            switch(t)
                            {
                            case 1:
                                printf("请输入考试成绩：");
                                int kao;
                                scanf("%d",&kao);
                                q->exam=kao;
                                printf("请输入修改考试成绩后的总成绩：");
                                scanf("%.2f",&kao);
                                q->sum=kao;
                                break;
                            case 2:
                                printf("请输入平时成绩：");
                                int ping;
                                scanf("%d",&ping);
                                q->normal=ping;
                                printf("请输入修改平时成绩后的总成绩：:");
                                scanf("%.2f",&ping);
                                q->sum=ping;
                                break;
                            case 3:
                                pre->next=q->next;
                                free(q);
                                printf("课程删除成功!");
                            case 0:
                                break;
                            }
                            if(t==0)
                                break;
                        }
                    }
                    printf("是否要继续修改");
                    int q;
                    scanf("%d",&q);
                    if(q==0)
                        break;
                    }
               write_file1(p3,"text.txt");
			break;
		case 3:
		    system("cls");
		    LNode *C;
		    C=new LNode[500];
		    read_file1(C,"text.txt");
		    cnt=get_record();
		    sort(C,C+cnt,cmp);
		    char c[20];
		    printf("请输入要查看的班级(输入exit退出查看):");
		    cin>>c;
		    if(strcmp(c,"exit")==0)
                break;
            show_course_byclass(C,c);
			break;
		case 4:
		    system("cls");
		     LNode *R;
		     R=new LNode[500];
		     read_file1(R,"text.txt");
		     char course_name[50];
		     printf("请输入要查看的课程名称(输入exit退出查看)：");
		     scanf("%s",course_name);
		     if(strcmp(course_name,"exit")==0)
			 	break;
		     show_student_bycourese(R,course_name);
			break;
		case 5:
		    system("cls");
		    LNode *D;
		    D=new LNode[500];
		    read_file1(D,"text.txt");
            show_stude_nopass(D);
            write_file1(D,"text.txt");
			break;
		case 6:
		    system("cls");
		    LNodelist F;
		    F=new LNode;
		    F->next=NULL;
		    read_file2(F,"text.txt");
		    delete_student(F);
		    write_file2(F->next,"text.txt");
			break;
        case 7:
            system("cls");
            LNode *T;
		     T=new LNode[500];
		     read_file1(T,"text.txt");
		     cnt=get_record();
		     sort(T,T+cnt,cmp);
		     L3:
		     cout<<"请输入要查看的学生学号(输入0退出查看)：";
		     int stunum1;
		     cin>>stunum1;
		     if(stunum1==0)
                goto L4;
		     int x3;
		     x3=show_student(T,stunum1);
		     if(x3==0)
                goto L3;
            L4:
            system("pause");
		     break;
        default:
            printf("输入错误，请重新输入！\n");
            system("pause");
            break;
    }
    system("pause");
    system("cls");
	}
}


void keydown1(int x)
{
    int choice0;

    while(1)
    {
        system("cls");
        showMenu1();
            color(4);
    cout<<"请选择：";
    color(15);
        cin>>choice0;
        switch(choice0)
        {
            case 0:
                {
                    system("cls");
                show_picture3();
                printf("退出系统\n");
                exit(0);
                break;}
			case 1:
                {
                system("cls");
                LNode *T;
                 T=new LNode[500];
                 read_file1(T,"text.txt");
                 cnt=get_record();
                 sort(T,T+cnt,cmp);
                 int stunum1;
                 stunum1=x;
                 int x3;
                 x3=show_student(T,stunum1);
                system("pause");
                break;
                }
            case 3:
                {
                    system("cls");
                int choice4;
                LNode *T1;
                 T1=new LNode[500];
                 read_file1(T1,"text.txt");
                 cnt=get_record();
                 int x4=search_LNode(T1,x);
                sort(T1,T1+cnt,cmp);
                Q:
                cout<<"1.删除课程"<<endl;
                cout<<"2.增加课程"<<endl;
                cout<<"0.退出选择"<<endl;
                cin>>choice4;
                if(choice4==1)
                {
                    LNodelist p1 = T1+x4;
                    Course p=p1->data2;
                    int i;
                    printf("课程名字\t课程编号\t总学分\t\t平时成绩\t考试成绩\t总成绩\t重修次数\n");
                    for(i=0;i<p1->data1.course_number;i++)
                    {
                        if(p->sum<=100)
						printf("%s\t%d\t\t%d\t\t%d\t\t%d\t\t%.2f\t%d\n",p->name,p->number,p->credit,p->normal,p->exam,p->sum,p->time);
						if(p->sum>100)
						printf("%s\t%d\t\t%d\t\t未登记\t\t未登记\t\t未登记\t未登记\n",p->name,p->number,p->credit);
                        p=p->next;
                    }
                    Course t=T1[x4].data2,pre1=T1[x4].data2;
                    cout<<"输入要删除的课程名称:";
                    char coursename[50];
                    cin>>coursename;
                    while(strcmp(coursename,t->name)!=0)
                    {
                        pre1=t;
                        t=t->next;
                    }
                    pre1->next=t->next;
                    cout<<T1[x4].data1.course_number;
                    T1[x4].data1.course_number--;
                    cout<<"课程删除成功"<<endl;
                    system("pause");
                }else if(choice4==2)
                {
                    char coursename1[50];
                    int coursenumber;
                    cout<<"请输入要增加的课程名称:";
                    cin>>coursename1;
                    cout<<"请输入课程号码:";
                    cin>>coursenumber;
                    Course t1;
                    t1->next=NULL;
                    strcpy(t1->name,coursename1);
                    t1->number=coursenumber;
                    cout<<"请输入课程学分：";
                    cin>>t1->credit;
                    t1->exam=0;
                    t1->normal=0;
                    t1->sum=101;
                    t1->time=0;
                    inserlist_course(T1[x4].data2,t1);
                    cout<<"选课成功"<<endl;
                    T1[x4].data1.course_number++;
                    system("pause");
                }else if(choice4==0)
                    break;
                else
                {
                    cout<<"输入错误，请重新输入"<<endl;
                    system("pause");
                    system("cls");
                    goto Q;
                }
				write_file1(T1,"text.txt");
                break;
				}
            case 4:
                {
				system("cls");
                LNode *T2;
                 T2=new LNode[500];
                 read_file1(T2,"text.txt");
                 cnt=get_record();
                 int x5=search_LNode(T2,x);
                char newword[6];
                cout<<"是否修改密码（1.确认，0.退出）：";
                int x6;
                cin>>x6;
                if(x6==1)
                {
                    cout<<"请输入新密码6位):";
                inputPasswd(newword,6);
                cout<<"请再次输入新密码:";
                inputPasswd(newword,6);
                strcpy(T2[x5].data1.password,newword);
                cout<<"密码修改成功"<<endl;
                write_file1(T2,"text.txt");
                system("pause");
                break;
                }else if(x6==0)
                {
                    break;
                }
                }
            case 2:
            	{
            	system("cls");
                LNode *K;
                 K=new LNode[500];
                 read_file1(K,"text.txt");
                 cnt=get_record();
                 sort(K,K+cnt,cmp);
                 int stunum9;
                 stunum9=x;
                 show_student_course(K,stunum9);
                 system("pause");
                 break;
				}

            default:
            printf("输入错误，请重新输入！\n");
            system("pause");
            break;
        }
    }

}

int main()
{
    Loading();
    show_picture1();
    system("pause");
    system("cls");
    int choice3;
    cout<<"---------------------"<<endl;
    cout<<"| 1.登陆学生端系统  |"<<endl;
    cout<<"---------------------"<<endl;
    cout<<"| 2.登陆教师端系统  |"<<endl;
    cout<<"---------------------"<<endl;
    color(4);
    cout<<"请选择：";
    color(15);
    cin>>choice3;
    int x;
    if(choice3==1)
    {
        x=landing1();
        keydown1(x);//登陆学生端
    }else
    {
        landing2();
        keydown2();//登陆教师端
    }
    system("pause");
	return 0;
 }
