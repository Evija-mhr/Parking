#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Daymoney 20
#define Hourmoney 2

struct adminaccount
{
    char account[11];
    char password[21];
    struct adminaccount *AdminNext;
};
typedef struct Time
{
    int year;
    int month;
    int day;
    int hour;
    int min;
}time;
struct useraccount
{
    char account[11];
    char password[21];
    char username[21];   //�û���
    char phone[12];       //�绰����
    char carname[21];   //���ƺ�
    char stall[6];         //��Ӧ��λ
    int balance;    //���
    int suit;       //����״̬��0Ϊ������1Ϊ�ڳ�������Ϊ״̬�쳣
    time reach;
    time leave;
    struct useraccount *UserNext;
};
struct del
{
    char deleteaccount[11];
    struct del *delnext;
};

//��������
void addUser(char *account, char *password,char *username,char *phone,char *carname,char *stall,int balance1,int suit1,
             int year2,int month2,int day2,int hour2,int min2,int year3,int month3,int day3,int hour3,int min3);
void addAdmin(char *account, char *password);
void AdminMeau();
void UserMeau(struct useraccount *UserCurrent);
int Adminlogin();
int Userlogin();
void Login();
struct useraccount *Deleteuser(struct useraccount *UserHead,char account1[11]);             //ɾ��ָ���û�
struct adminaccount *Deleteadmin(struct adminaccount *AdminHead,char account1[11]);      //ɾ��ָ������Ա
void adddelaccount(char account1[11]);                                 //������ע�����û���ӵ�֪ͨ����
struct del *Deleteacc(struct del *Delhead,char account1[11]);       //���֪ͨ��������ɾ�����û�
int days(int year, int month);                          //�����·ݵ�����
int leapyear(int year1);                                 //�ж��Ƿ�Ϊ����
int daysgap(time t1, time t2);                           //�������ڼ��


//ȫ�ֱ�������
struct useraccount  *UserHead = NULL;               //�û�����ͷ�ڵ�
struct adminaccount *AdminHead = NULL;               //����Ա����ͷ�ڵ�
struct adminaccount *adminnewNode = NULL;           //����Ա��Ϣ�½ڵ�
struct useraccount *userNode = NULL;                //�û���Ϣ�½ڵ�
struct del *Delhead=NULL;
struct del *delnode=NULL;
int message=0;

int main()
{   addUser("test1","123456","test1","11223344556","A485k","A75",100,0,2024,5,10,13,15,2024,5,10,17,0);
    addUser("test2","123456","test2","112768675","A484468","A7538",10,1,2024,5,20,13,15,2024,5,21,17,0);
    addAdmin("admin","123456");
    addAdmin("admin2","123456");
    Login();
}

void AdminMeau()                //����Ա�˵�
{
    int a, b, e, x,balance1,suit1,hour2,min2,hour3,min3,year2,month2,day2,year3,month3,day3,days1,hour1,min1;
    char c[21], d[21], phone1[12], carname1[21], stall1[6],account1[11],password1[21],username1[21];
    struct useraccount *p;
    struct adminaccount *p2;
    struct del *p3;
    FILE* pFile;
    T:
    p=UserHead;
    p2=AdminHead;
    p3=Delhead;
    while(p3!=NULL)
    {
       printf("\n%s����ע���û�����\n",p3->deleteaccount);
       p3=p3->delnext;
    }
    printf("\n**************��½�ɹ�***********\n");
    printf("**********1.���ҳ�λ״̬*********\n");
    printf("**********2.���ҳ�����Ϣ*********\n");
    printf("**********3.�û�������*********\n");
    printf("**********4.��λ״̬����*********\n");
    printf("**********5.������û�***********\n");
    printf("**********6.����¹���Ա*********\n");
    printf("**********7.��ʾ���г�����Ϣ*****\n");
    printf("**********8.�����û���Ϣ*********\n");
    printf("**********9.���Ĺ���Ա�˺�����***\n");
    printf("**********10.���������û���Ϣ****\n");
    printf("**********11.ɾ���û�************\n");
    printf("**********12.ɾ������Ա**********\n");
    printf("**********13.���ص�½ҳ��********\n");
    printf("**********14.�˳�****************\n");
    printf("*********************************\n");
    printf("----��������Ӧ������ѡ����!----\n");

D:
    scanf("%d", &a);
    switch (a)
    {
    case 1://���ҳ�λ״̬
    H:
        printf("�������ѯ�ĳ�λ:");
        scanf("%s", c);
        while(p!=NULL)
        {
            if (strcmp(p->stall, c) == 0)
            {
                if (p->suit == 0)
                {
                    printf("**��ѯ����λ**\n%s:��\n", c);
                    break;
                }
                else if (p->suit == 1)
                {
                    printf("**��ѯ����λ**\n%s:%s��ͣ\n�û���%s\n�绰��%s\n", c,p->carname, p->username, p->phone);
                    break;
                }
                else {
                    printf("**��λ״̬�쳣��**\n");
                    break;
                }
            }
            else if(p->UserNext==NULL&&p->stall!=c)
            {
                printf("δ��ѯ����λ������������\n");
                p=UserHead;
                goto H;
            }
            else p=p->UserNext;
        }
        break;
    case 2://���ҳ�����Ϣ
    I:
        printf("�����복�ƺţ�");
        scanf("%s", c);
        while(p!=NULL)
        {
            if (strcmp(p->carname, c) == 0)
            {
              printf("**���ҳɹ�**\n���ƺ�Ϊ��%s\n�û���%s\n�绰��%s\n��λ��%s\n����״̬��%d\n",p->carname,p->username,p->phone, p->stall,p->suit);
                break;
            }
            else if(p->UserNext==NULL&&p->carname!=c)
            {
                printf("δ��ѯ������������������");
                p=UserHead;
                goto I;
            }
            else p=p->UserNext;
        }
        break;
    case 3://�û�������
        L:
        printf("�������û�����");
        scanf("%s", c);
        for (x = 0; x < 200; x++)
         while(p!=NULL)
        {
            if (strcmp(p->username, c) == 0)
            {
              printf("**���ҳɹ�**\n�û���%s\n��%d\n",p->username,p->balance);
                printf("�������µĳ�����");
                scanf("%d", &b);
                p->balance = b;
                printf("**���ĳɹ�**\n���ڳ������Ϊ��%d\n", p->balance);
                goto Y;
            }
            else if(p->UserNext==NULL&&p->username!=c)

            {
                printf("δ��ѯ���û�������������");
                p=UserHead;
                goto L;
            }
            else p=p->UserNext;
        }
    Y:
        break;
    case 4://��λ״̬����
    J:
        printf("�����복λ��");
        scanf("%s", c);
       while(p!=NULL)
        {
            if (strcmp(p->stall, c) == 0)
            {
                    printf("**���ҳɹ�**\n���ƺ�Ϊ��%s\n��λ��%s\n����״̬��%d\n�����복λ��״̬��", p->carname, p->stall,p->suit);
                    scanf("%d", &e);
                    if (e == 0)
                        printf("**�������**\n����״̬����\n");
                    else if (e == 1)
                        printf("**�������**\n����״̬����ͣ\n");
                    else
                        printf("**�������**\n����״̬���쳣\n");
                    break;
            }
            else if(p->UserNext==NULL&&p->stall!=c)
            {
                printf("δ��ѯ����λ������������");
                p=UserHead;
                goto J;
            }
            else p=p->UserNext;
        }
        break;
    case 5://������û�
        printf("���������û��˺ţ�");
        scanf("%s",account1);
        printf("���������û����룺");
        scanf("%s",password1);
        printf("���������û��û�����");
        scanf("%s",username1);
        printf("���������û��绰��");
        scanf("%s",phone1);
        printf("���������û����ƺţ�");
        scanf("%s",carname1);
        printf("���������û���λ��");
        scanf("%s",stall1);
        printf("���������û���");
        scanf("%d",&balance1);
        printf("���������û��ֳ�λ״̬��");
        scanf("%d",&suit1);
        printf("�������볡ʱ�䣺(���磺2024 5 17 7 15)");
        scanf("%d%d%d%d%d",&year2,&month2,&day2,&hour2,&min2);
        printf("���������ʱ�䣺(���磺2024 5 17 7 15)");
        scanf("%d%d%d%d%d",&year3,&month3,&day3,&hour3,&min3);
        addUser(account1, password1,username1,phone1,carname1,stall1,balance1,suit1,year2,month2,day2,hour2,min2,year3,month3,day3,hour3,min3);
        printf("**��ӳɹ�**\n�û�����%s\n�绰��%s\n���ƺţ�%s\n��Ӧ��λ��%s\n��%d\n��λ״̬��%d\n",
               userNode->username,userNode->phone,userNode->carname,userNode->stall,userNode->balance,userNode->suit);
        break;
    case 6://����¹���Ա
        printf("�������¹���Ա�û�����");
        scanf("%s", c);
        printf("�������¹���Ա���룺");
        scanf("%s", d);
        addAdmin(c,d);
        printf("**������**\n�¹���Ա�˺ţ�%s\n���룺%s\n", adminnewNode->account,adminnewNode->password);
        break;
    case 7://��ʾ���г�����Ϣ
        printf("��       ���ƺ�       ��          �û�      ��   �绰    ����λ ����״̬��\n");
        while(p!=NULL)
        {
            printf("��%20s��%20s��%11s��%5s��%4d��%4d��\n", p->carname,  p->username,  p->phone,  p->stall, p->balance,p->suit);
            p=p->UserNext;
        }
        break;
    case 8://�����û���Ϣ
    F:
        printf("������ԭ�û�����");
        scanf("%s", c);
       while(p!=NULL)
        { E:
            if (strcmp(p->username, c) == 0)
            {   days1=daysgap(p->reach,p->leave);
                hour1 = p->leave.hour - p->reach.hour;
                min1 = p->leave.min- p->reach.min;
                if (min1 < 0)
                {
                    min1 += 60;
                    hour1--;
                }
                printf("\n�û�����%s\n�绰��%s\n���ƺţ�%s\n��Ӧ��λ��%s\n��%d\n��ͣ��ʱ�䣺%d��%dСʱ%d��\n",
                       p->account,p->phone,p->carname,p->stall,p->balance,days1,hour1,min1);
                printf("��ѡ���������:\n1.�û���\n2.����\n3.�绰\n4.���ƺ�\n5.��λ\n6.�볡ʱ��\n7.����ʱ��\n");
                scanf("%d", &x);
                if (x == 1)
                {
                    printf("�������µ��û�����");
                    scanf("%s", c);
                    strcpy( p->username, c);
                    strcpy( p->account, c);
                    printf("**�������**\n���û���Ϊ��%s", p->account);
                }
                else if (x == 2)
                {
                    printf("�������µ����룺");
                    scanf("%s", d);
                    strcpy( p->password, d);
                    printf("**�������**\n������Ϊ��%s",  p->password);
                }
                else if (x == 3)
                {
                    printf("�������µĵ绰��");
                    scanf("%s", phone1);
                    strcpy( p->phone, phone1);
                    printf("**�������**\n�µ绰Ϊ��%s", p->phone);
                }
                else if (x == 4)
                {
                    printf("�������µĳ��ƺţ�");
                    scanf("%s", carname1);
                    strcpy( p->carname, carname1);
                    printf("**�������**\n�³��ƺ�Ϊ��%s",  p->carname);
                }
                else if (x == 5)
                {
                    printf("�������µĳ�λ��");
                    scanf("%s", stall1);
                    strcpy( p->stall, stall1);
                    printf("**�������**\n�³�λΪ��%s", p->stall);
                }
                 else if (x == 6)
                {
                    printf("�������µ��볡ʱ�䣺");
                    scanf("%d%d%d%d%d",&year2,&month2,&day2,&hour2,&min2);
                    p->reach.year=year2;
                    p->reach.month=month2;
                    p->reach.day=day2;
                    p->reach.hour=hour2;
                    p->reach.min=min2;
                    printf("**�������**\n���볡ʱ��Ϊ��%d/%d/%d %d:%d",
                        p->reach.year,p->reach.month,p->reach.day,p->reach.hour,p->reach.min);
                }
                 else if (x == 7)
                {
                    printf("�������µĳ���ʱ�䣺");
                    scanf("%d%d%d%d%d",&year3,&month3,&day3,&hour3,&min3);
                    p->leave.year=year3;
                    p->leave.month=month3;
                    p->leave.day=day3;
                    p->leave.hour=hour3;
                    p->leave.min=min3;
                    printf("**�������**\n�³���ʱ��Ϊ��%d/%d/%d %d:%d",
                           p->leave.year,p->leave.month,p->leave.day,p->leave.hour,p->leave.min);
                }
                else
                {
                    printf("**�����������������**\n");
                    goto E;
                }
                break;
            }
            else if(p->UserNext==NULL&&p->username!=c)
            {
                printf("**δ��ѯ�����û���Ϣ�������������û���**");
                p=UserHead;
                goto F;
            }
            else p=p->UserNext;
        }
            break;
    case 9://���Ĺ���Ա�˺�����
    G:
        printf("������ԭ����Ա�˺�:");
        scanf("%s", c);
        while(p2!=NULL)
            {if (strcmp(p2->account, c) == 0)
            {   printf("��ѡ���������:\n1.�˺�\n2.����");
                scanf("%d", &x);

                if (x == 1)
                {
                    printf("�������µ��˺ţ�");
                    scanf("%s", c);
                    strcpy(p2->account, c);
                    printf("**�������**\n���˺�Ϊ��%s", p2->account);
                    break;
                }
                else if (x == 2)
                {
                    printf("�������µ����룺");
                    scanf("%s", d);
                    strcpy(p2->password, d);
                    printf("**�������**\n������Ϊ��%s", p2->password);
                    break;
                }
            }
            else if(p2->AdminNext==NULL&&p2->account!=c)
            {
                printf("**δ��ѯ�����û���Ϣ�������������˺�**\n");
                p2=AdminHead;
                goto G;
            }
            p2=p2->AdminNext;
        }
        break;
    case 10://���������û���Ϣ
        pFile = fopen("Part.txt", "w+");         //��Part.txt
        fprintf(pFile,"|       ���ƺ�        |          �û�      |   �绰           |��λ |���|״̬|\n");
        while(p!=NULL)
        {
            fprintf(pFile, "|%20s|%20s|%11s|%5s|%4d|%5d|\n",
           p->carname,  p->username,  p->phone,  p->stall, p->balance,p->suit);
            if(p->UserNext==NULL)
                break;
            else
            p=p->UserNext;
        }
        fclose(pFile);
        printf("**�������**\n");
        break;
    case 11:
        printf("������Ҫɾ�����û��˺ţ�");
        scanf("%s",account1);
        UserHead=Deleteuser(UserHead,account1);
        Delhead=Deleteacc(Delhead,account1);
        break;
    case 12:
        printf("������Ҫɾ���Ĺ���Ա�˺ţ�");
        scanf("%s",account1);
        AdminHead=Deleteadmin(AdminHead,account1);
        break;
    case 13://���ص�½ҳ��
        Login();
        break;
    case 14://�˳�
        exit(0);
    default:
        printf("**�����������������**\n");
        goto D;
        }
        goto T;
}
void UserMeau(struct useraccount *UserCurrent)              //�û��˵�  //��ȡ���ݵ��û���Ϣ�ڵ�
{
    int  a, b, hour1, min1,days1,totalmoney;
    char c[21];
    days1=daysgap(UserCurrent->reach,UserCurrent->leave);
    hour1 = UserCurrent->leave.hour - UserCurrent->reach.hour;
    min1 = UserCurrent->leave.min- UserCurrent->reach.min;
    if (min1 < 0)
    {
        min1 += 60;
        hour1--;
    }
    if(min1>=30)
    totalmoney=Daymoney*days1+(hour1+1)*Hourmoney;
    else if(min1<=0&&min1<30)
    totalmoney=Daymoney*days1+hour1*Hourmoney;
V:
    printf("\n�û�����%s\n�绰��%s\n���ƺţ�%s\n��Ӧ��λ��%s\n��%d\n��ͣ��ʱ�䣺%d��%dСʱ%d��\n��ɷ�%dԪ\n",
    UserCurrent->username,UserCurrent->phone,UserCurrent->carname,UserCurrent->stall,UserCurrent->balance,days1,hour1, min1,totalmoney);
    printf("\n**********��½�ɹ�************\n");
    printf("**********1.ͣ���ɷ�**********\n");
    printf("**********2.����ֵ**********\n");
    printf("**********3.���ĳ��ƺ�********\n");
    printf("**********4.���ĵ绰**********\n");
    printf("**********5.�޸��û���********\n");
    printf("**********6.�޸�����**********\n");
    printf("**********7.���ص�½ҳ��******\n");
    printf("**********8.ע���˻�**********\n");
    printf("**********9.�˳�**************\n");
    printf("******************************\n");
    printf("--��������Ӧ������ѡ���ܣ�--\n");
B:
    scanf("%d", &a);
    switch (a)
    {
    case 1://ͣ���ɷ�
        printf("��ɷ�%dԪ��������yesȷ��֧���������ַ�ȡ��\n",totalmoney);
        scanf("%s",c);
        if(strcmp(c,"yes")==0)
        {   if(UserCurrent->balance>=totalmoney)
            {printf("�ɷ����\n");
            UserCurrent->balance-=totalmoney;}
            else
            printf("���㣡���ֵ��\n");
        }
        else
        {
            printf("��ȡ��\n");
        }
        break;
    case 2://����ֵ
        printf("�������ֵ��");
        scanf("%d", &b);
        UserCurrent->balance+= b;
        printf("**��ֵ���**\n���ڵ����Ϊ��%d\n", UserCurrent->balance);
        break;
    case 3://���ĳ��ƺ�
        printf("�������µĳ��ƺţ�");
        scanf("%s", c);
        strcpy(UserCurrent->carname, c);
        printf("���ĳɹ�\n���ڳ��ƺ�Ϊ��%s\n",  UserCurrent->carname);
        break;
    case 4://���ĵ绰
        printf("�������µĵ绰���룺");
        scanf("%s", c);
        strcpy( UserCurrent->phone, c);
        printf("���ĳɹ�\n���ڵ绰Ϊ��%s\n",  UserCurrent->phone);
        break;
    case 5://�޸��û���
        printf("�������µ��û���(20�ַ�����)��");
        scanf("%s", c);
        strcpy( UserCurrent->username, c);
        printf("�޸ĳɹ�\n�����û���Ϊ��%s\n", UserCurrent->username);
        break;
    case 6://�޸�����
        printf("�������µ�����(20�ַ�����)��");
        scanf("%s", c);
        strcpy( UserCurrent->password, c);
        printf("�޸ĳɹ�\n��������Ϊ��%s\n",UserCurrent->password);
        break;
    case 7://���ص�½ҳ��
        Login();
        break;
    case 8:
        printf("��ȷ��Ҫע���˻���\n������yesȷ���������ַ�ȡ��\n");
        scanf("%s",c);
        if(strcmp(c,"yes")==0)
        {   ++message;
            adddelaccount(UserCurrent->account);
            printf("�������Ա����ע������,�������ص�½����\n");
            Login();
        }
        else
        {
            printf("��ȡ��\n");
        }
        break;
    case 9://�˳�
        exit(0);
    default:
        printf("�����������������\n");
        goto B;

    }goto V;

}
void Login()
{   int b,c;
    char a[10];
    C:
    printf("��ѡ��\n1.�û���½\n2.����Ա��½\n");
    scanf("%s",a);
    if (strcmp(a,"1")==0)                                   //�û���½
    {A:
        b=Userlogin();
        if (b==0)
        {
            printf("�����������������\n");
            goto A;
        }

    }
    else if(strcmp(a,"2")==0)                               //����Ա��½
    {  B:
        c=Adminlogin();
        if(c==0)
        {
            printf("�����������������\n");
            goto B;
        }
    }
    else
    {
        printf("���벻�Ϸ��������ԣ�");
        goto C;
    }
}
int Userlogin()
{
    char account[11], password[21];
    struct useraccount *UserCurrent = UserHead;
    printf("�������û��˺������Ե�½\n");
    while (1) {                                                         // ʹ������ѭ����ֱ���ҵ��˻�
        printf("�˺ţ�");
        scanf("%10s", account);

        while (UserCurrent != NULL) {
            if (strcmp(UserCurrent->account, account) == 0) {
                break;                                                  // �ҵ�ƥ����˻�,����ѭ��
            }
            UserCurrent = UserCurrent->UserNext;
        }

        if (UserCurrent != NULL)
        {                                                                   // ����ҵ��˻����ж�������ʾ�û��˵�
            int passwordCorrect = 0;
            do {
                printf("���룺");
                scanf("%20s", password);
                if (strcmp(UserCurrent->password, password) == 0) {
                    passwordCorrect = 1;
                    UserMeau(UserCurrent);
                    return 1;                                                // �˺�������ȷ������1��ʾ��¼�ɹ�
                }
                else
                {
                    printf("���������������������\n");
                }
            } while (!passwordCorrect);                                     // ���벻��ȷʱ����ѭ��
        }
        else
        {                                                            // ���û���ҵ��˻�
            printf("�˻������ڣ�����������\n");
            UserCurrent=UserHead;
        }
    }
}
int Adminlogin()
{
    char account[11], password[21];
    struct adminaccount *AdminCurrent = NULL;
    AdminCurrent=AdminHead;                                        // ��ͷ�ڵ㿪ʼ��������
    printf("���������Ա�˺������Ե�½\n");
    while (1) {                                                    // ʹ������ѭ����ֱ���ҵ��˻�
        printf("�˺ţ�");
        scanf("%10s", account);
        while (AdminCurrent != NULL)
        {
            if (strcmp(AdminCurrent->account, account) == 0)
            {
                break;                                              // �ҵ�ƥ����˻�,����ѭ��
            }
            AdminCurrent = AdminCurrent->AdminNext;             // û�ҵ����ƶ�����һ���ڵ�
        }
        if (AdminCurrent != NULL)                               // ����ҵ��˻����ж�������ʾ�û��˵�
    {
            int passwordCorrect = 0;
        do {
                printf("���룺");
                scanf("%20s", password);
                if (strcmp(AdminCurrent->password, password) == 0) {
                    passwordCorrect = 1;
                    AdminMeau();
                    return 1;                                   // �˺�������ȷ������1��ʾ��¼�ɹ�
                }
                else
                {
                    printf("���������������������\n");
                }
            } while (!passwordCorrect);                         // ���벻��ȷʱ����ѭ��
    }
        else
        {                                                          // ���û���ҵ��˻�����������
            printf("�˻������ڣ�����������\n");
            AdminCurrent=AdminHead;
        }
    }
}
void addUser(char *account, char *password,char *username,char *phone,char *carname,char *stall,int balance1,int suit1,
             int year2,int month2,int day2,int hour2,int min2,int year3,int month3,int day3,int hour3,int min3)
{
    userNode = (struct useraccount *)malloc(sizeof(struct useraccount));
    strncpy(userNode->account, account, sizeof(userNode->account) - 1); //������ӳ���
    userNode->account[sizeof(userNode->account) - 1] = '\0';           // ��ĩβ��ӡ�0��ȷ���˺��ַ�����ȷ����
    strncpy(userNode->password, password, sizeof(userNode->password) - 1);
    userNode->password[sizeof(userNode->password) - 1] = '\0';
    strncpy(userNode->username, username, sizeof(userNode->username) - 1);
    userNode->username[sizeof(userNode->username) - 1] = '\0';
    strncpy(userNode->phone, phone, sizeof(userNode->phone) - 1);
    userNode->phone[sizeof(userNode->phone) - 1] = '\0';
    strncpy(userNode->carname, carname, sizeof(userNode->carname) - 1);
    userNode->carname[sizeof(userNode->carname) - 1] = '\0';
    strncpy(userNode->stall, stall, sizeof(userNode->stall) - 1);
    userNode->stall[sizeof(userNode->stall) - 1] = '\0';
    userNode->balance=balance1;
    userNode->suit=suit1;
    userNode->reach.year=year2;
    userNode->reach.month=month2;
    userNode->reach.day=day2;
    userNode->reach.hour=hour2;
    userNode->reach.min=min2;
    userNode->leave.year=year3;
    userNode->leave.month=month3;
    userNode->leave.day=day3;
    userNode->leave.hour=hour3;
    userNode->leave.min=min3;
    if (UserHead == NULL)
    {
        UserHead= userNode;                                                  // �������Ϊ�գ����½ڵ�����Ϊͷ�ڵ�
        userNode->UserNext  = NULL;
    }
    else                                                            // �����ҵ���������һ���ڵ�������
    {
        struct useraccount *current1 = UserHead;
        while (current1->UserNext != NULL)
        {
            current1 = current1->UserNext ;
        }
        current1->UserNext  = userNode;
        userNode->UserNext  = NULL;
    }
}
void addAdmin(char *account, char *password)
{
    adminnewNode = (struct adminaccount *)malloc(sizeof(struct adminaccount));
    strncpy(adminnewNode->account, account, sizeof(adminnewNode->account) - 1);//������ӳ���
    adminnewNode->account[sizeof(adminnewNode->account) - 1] = '\0';           // ��ĩβ��ӡ�0��ȷ���˺��ַ�����ȷ����
    strncpy(adminnewNode->password, password, sizeof(adminnewNode->password) - 1);
    adminnewNode->password[sizeof(adminnewNode->password) - 1] = '\0';
    if (AdminHead == NULL)               // �������Ϊ�գ����½ڵ�����Ϊͷ�ڵ�
    {
        AdminHead = adminnewNode;
        adminnewNode->AdminNext = NULL;
    }
    else                            // �����ҵ���������һ���ڵ�������
    {
        struct adminaccount *current2 = AdminHead;
        while (current2->AdminNext != NULL)
        {
            current2 = current2->AdminNext;
        }
        current2->AdminNext= adminnewNode;
        adminnewNode->AdminNext = NULL;
    }
}
void adddelaccount(char account1[11])
{   delnode=(struct del*)malloc(sizeof(struct del));
    strcpy(delnode->deleteaccount,account1);
    delnode->deleteaccount[sizeof(adminnewNode->account) - 1] = '\0';
    if (Delhead== NULL)               // �������Ϊ�գ����½ڵ�����Ϊͷ�ڵ�
    {
        Delhead= delnode;
        delnode->delnext = NULL;
    }
    else                            // �����ҵ���������һ���ڵ�������
    {
        struct del *current3 = Delhead;
        while (current3->delnext != NULL)
        {
            current3 = current3->delnext;
        }
        current3->delnext= delnode;
       delnode->delnext = NULL;
    }
}
struct useraccount *Deleteuser(struct useraccount *UserHead,char account1[11])//ɾ��ָ���û�
{
    struct useraccount * pb,*pf;
    pb=UserHead;//��pbָ��ͷ�ڵ�
    if(UserHead == NULL)//����Ϊ������
    {
        printf("�û�����Ϊ��\n");
    }
    while(strcmp(pb->account,account1)!=0 && pb->UserNext!=NULL)//�����û�����
    {
        pf=pb;
        pb=pb->UserNext;
    }
    if(strcmp(pb->account,account1)==0)
    {
        if(pb == UserHead)//�ҵ��Ľڵ���ͷ�ڵ�
        {
            UserHead= pb->UserNext;
        }
        else//�ҵ��ڵ�
        {
            pf->UserNext = pb->UserNext;
        }
            free(pb);
            printf("**ɾ���ɹ�**\n");
    }
    else//û���ҵ�Ҫɾ���Ľڵ�
    {
        printf("û���ҵ���Ҫɾ�����û�\n");
    }
    return UserHead;
}
struct adminaccount *Deleteadmin(struct adminaccount *AdminHead,char account1[11])//ɾ��ָ������Ա��ֻ��һ������Աʱ�޷�ɾ��
{
    struct adminaccount * pb,*pf;
    pb=AdminHead;
    while(strcmp(pb->account,account1)!=0 && pb->AdminNext!=NULL)//��������Ա����
    {
        pf=pb;
        pb=pb->AdminNext;
    }
    if(strcmp(pb->account,account1)==0)//�ҵ���һ���ڵ��num��num���
    {
        if(pb == AdminHead)//�ҵ��Ľڵ���ͷ�ڵ�
        {   if(pb->AdminNext==NULL)//ֻ��ͷ�ڵ㣬�޷�ɾ��
            {
                printf("����һ������Ա�����޷�ɾ������\n");
            }
            AdminHead= pb->AdminNext;
        }
        else  //�ҵ��ڵ�
        {
            pf->AdminNext = pb->AdminNext;
            printf("**ɾ���ɹ�**\n");
        }
            free(pb);
    }
    else     //û���ҵ�Ҫɾ���Ľڵ�
    {
        printf("û���ҵ���Ҫɾ���Ĺ���Ա\n");
    }
    return AdminHead;
}
struct del *Deleteacc(struct del *Delhead,char account1[11])//ɾ��ָ���û�
{
    struct del * pb,*pf;
    pb=Delhead;            //��pbָ��ͷ�ڵ�
    while(strcmp(pb->deleteaccount,account1)!=0 && pb->delnext!=NULL)//�����û�����
    {
        pf=pb;
        pb=pb->delnext;
    }
    if(strcmp(pb->deleteaccount,account1)==0)
    {
        if(pb == Delhead)//�ҵ��Ľڵ���ͷ�ڵ�
        {
            Delhead= pb->delnext;
        }
        else//�ҵ��ڵ�
        {
            pf->delnext = pb->delnext;
        }
            free(pb);
    }
    return Delhead;
}
int days(int year, int month)//�����·ݵ�����
{
    int PerMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && leapyear(year))
    {
        return 29;
    }
    return PerMonth[month-1];
}
int leapyear(int year1)//�ж��Ƿ�Ϊ����
{
    if ((year1%4==0 && year1%100!=0)||year1%400==0)
    {
        return 1;
    }
    return 0;
}
int daysgap(time t1, time t2)//�������ڼ��
{
    if (t1.year>t2.year||(t1.year==t2.year&&t1.month>t2.month)||(t1.year==t2.year&&t1.month==t2.month&&t1.day>t2.day)) // ���ʱ��1��ʱ��2֮����ʱ���쳣
    {
       printf("ͣ��ʱ���쳣������ϵ����Ա����");
    }
    int gap;
    for (int y = t1.year;y<t2.year;y++) // �������֮���������
    {
        if (leapyear(y))
        {
            gap=366;
        }
        else
        {
            gap=365;
        }
    }
    for (int m=t1.month; m<t2.month; m++)  //�����·�֮���������
    {
        gap+=days(t1.year,m);
    }
    gap+=(t2.day-t1.day);  // ��������֮���������
    return gap;
}
