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
    char username[21];   //用户名
    char phone[12];       //电话号吗
    char carname[21];   //车牌号
    char stall[6];         //对应车位
    int balance;    //余额
    int suit;       //车辆状态：0为出场，1为在场，其余为状态异常
    time reach;
    time leave;
    struct useraccount *UserNext;
};
struct del
{
    char deleteaccount[11];
    struct del *delnext;
};

//函数声明
void addUser(char *account, char *password,char *username,char *phone,char *carname,char *stall,int balance1,int suit1,
             int year2,int month2,int day2,int hour2,int min2,int year3,int month3,int day3,int hour3,int min3);
void addAdmin(char *account, char *password);
void AdminMeau();
void UserMeau(struct useraccount *UserCurrent);
int Adminlogin();
int Userlogin();
void Login();
struct useraccount *Deleteuser(struct useraccount *UserHead,char account1[11]);             //删除指定用户
struct adminaccount *Deleteadmin(struct adminaccount *AdminHead,char account1[11]);      //删除指定管理员
void adddelaccount(char account1[11]);                                 //将申请注销的用户添加到通知链表
struct del *Deleteacc(struct del *Delhead,char account1[11]);       //清除通知链表中已删除的用户
int days(int year, int month);                          //计算月份的天数
int leapyear(int year1);                                 //判断是否为闰年
int daysgap(time t1, time t2);                           //计算日期间隔


//全局变量声明
struct useraccount  *UserHead = NULL;               //用户链表头节点
struct adminaccount *AdminHead = NULL;               //管理员链表头节点
struct adminaccount *adminnewNode = NULL;           //管理员信息新节点
struct useraccount *userNode = NULL;                //用户信息新节点
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

void AdminMeau()                //管理员菜单
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
       printf("\n%s请求注销用户！！\n",p3->deleteaccount);
       p3=p3->delnext;
    }
    printf("\n**************登陆成功***********\n");
    printf("**********1.查找车位状态*********\n");
    printf("**********2.查找车辆信息*********\n");
    printf("**********3.用户余额更改*********\n");
    printf("**********4.车位状态更改*********\n");
    printf("**********5.添加新用户***********\n");
    printf("**********6.添加新管理员*********\n");
    printf("**********7.显示所有车辆信息*****\n");
    printf("**********8.更改用户信息*********\n");
    printf("**********9.更改管理员账号密码***\n");
    printf("**********10.导出所有用户信息****\n");
    printf("**********11.删除用户************\n");
    printf("**********12.删除管理员**********\n");
    printf("**********13.返回登陆页面********\n");
    printf("**********14.退出****************\n");
    printf("*********************************\n");
    printf("----请输入相应的数字选择功能!----\n");

D:
    scanf("%d", &a);
    switch (a)
    {
    case 1://查找车位状态
    H:
        printf("请输入查询的车位:");
        scanf("%s", c);
        while(p!=NULL)
        {
            if (strcmp(p->stall, c) == 0)
            {
                if (p->suit == 0)
                {
                    printf("**查询到车位**\n%s:空\n", c);
                    break;
                }
                else if (p->suit == 1)
                {
                    printf("**查询到车位**\n%s:%s已停\n用户：%s\n电话：%s\n", c,p->carname, p->username, p->phone);
                    break;
                }
                else {
                    printf("**车位状态异常！**\n");
                    break;
                }
            }
            else if(p->UserNext==NULL&&p->stall!=c)
            {
                printf("未查询到车位，请重新输入\n");
                p=UserHead;
                goto H;
            }
            else p=p->UserNext;
        }
        break;
    case 2://查找车辆信息
    I:
        printf("请输入车牌号：");
        scanf("%s", c);
        while(p!=NULL)
        {
            if (strcmp(p->carname, c) == 0)
            {
              printf("**查找成功**\n车牌号为：%s\n用户：%s\n电话：%s\n车位：%s\n车辆状态：%d\n",p->carname,p->username,p->phone, p->stall,p->suit);
                break;
            }
            else if(p->UserNext==NULL&&p->carname!=c)
            {
                printf("未查询到车辆，请重新输入");
                p=UserHead;
                goto I;
            }
            else p=p->UserNext;
        }
        break;
    case 3://用户余额更改
        L:
        printf("请输入用户名：");
        scanf("%s", c);
        for (x = 0; x < 200; x++)
         while(p!=NULL)
        {
            if (strcmp(p->username, c) == 0)
            {
              printf("**查找成功**\n用户：%s\n余额：%d\n",p->username,p->balance);
                printf("请输入新的车辆余额：");
                scanf("%d", &b);
                p->balance = b;
                printf("**更改成功**\n现在车辆余额为：%d\n", p->balance);
                goto Y;
            }
            else if(p->UserNext==NULL&&p->username!=c)

            {
                printf("未查询到用户，请重新输入");
                p=UserHead;
                goto L;
            }
            else p=p->UserNext;
        }
    Y:
        break;
    case 4://车位状态更改
    J:
        printf("请输入车位：");
        scanf("%s", c);
       while(p!=NULL)
        {
            if (strcmp(p->stall, c) == 0)
            {
                    printf("**查找成功**\n车牌号为：%s\n车位：%s\n车辆状态：%d\n请输入车位新状态：", p->carname, p->stall,p->suit);
                    scanf("%d", &e);
                    if (e == 0)
                        printf("**更改完成**\n车辆状态：空\n");
                    else if (e == 1)
                        printf("**更改完成**\n车辆状态：已停\n");
                    else
                        printf("**更改完成**\n车辆状态：异常\n");
                    break;
            }
            else if(p->UserNext==NULL&&p->stall!=c)
            {
                printf("未查询到车位，请重新输入");
                p=UserHead;
                goto J;
            }
            else p=p->UserNext;
        }
        break;
    case 5://添加新用户
        printf("请输入新用户账号：");
        scanf("%s",account1);
        printf("请输入新用户密码：");
        scanf("%s",password1);
        printf("请输入新用户用户名：");
        scanf("%s",username1);
        printf("请输入新用户电话：");
        scanf("%s",phone1);
        printf("请输入新用户车牌号：");
        scanf("%s",carname1);
        printf("请输入新用户车位：");
        scanf("%s",stall1);
        printf("请输入新用户余额：");
        scanf("%d",&balance1);
        printf("请输入新用户现车位状态：");
        scanf("%d",&suit1);
        printf("请输入入场时间：(例如：2024 5 17 7 15)");
        scanf("%d%d%d%d%d",&year2,&month2,&day2,&hour2,&min2);
        printf("请输入出场时间：(例如：2024 5 17 7 15)");
        scanf("%d%d%d%d%d",&year3,&month3,&day3,&hour3,&min3);
        addUser(account1, password1,username1,phone1,carname1,stall1,balance1,suit1,year2,month2,day2,hour2,min2,year3,month3,day3,hour3,min3);
        printf("**添加成功**\n用户名：%s\n电话：%s\n车牌号：%s\n对应车位：%s\n余额：%d\n车位状态：%d\n",
               userNode->username,userNode->phone,userNode->carname,userNode->stall,userNode->balance,userNode->suit);
        break;
    case 6://添加新管理员
        printf("请输入新管理员用户名：");
        scanf("%s", c);
        printf("请输入新管理员密码：");
        scanf("%s", d);
        addAdmin(c,d);
        printf("**添加完成**\n新管理员账号：%s\n密码：%s\n", adminnewNode->account,adminnewNode->password);
        break;
    case 7://显示所有车辆信息
        printf("┃       车牌号       ┃          用户      ┃   电话    ┃车位 ┃余额┃状态┃\n");
        while(p!=NULL)
        {
            printf("┃%20s┃%20s┃%11s┃%5s┃%4d┃%4d┃\n", p->carname,  p->username,  p->phone,  p->stall, p->balance,p->suit);
            p=p->UserNext;
        }
        break;
    case 8://更改用户信息
    F:
        printf("请输入原用户名：");
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
                printf("\n用户名：%s\n电话：%s\n车牌号：%s\n对应车位：%s\n余额：%d\n已停车时间：%d天%d小时%d分\n",
                       p->account,p->phone,p->carname,p->stall,p->balance,days1,hour1,min1);
                printf("请选择更改内容:\n1.用户名\n2.密码\n3.电话\n4.车牌号\n5.车位\n6.入场时间\n7.出场时间\n");
                scanf("%d", &x);
                if (x == 1)
                {
                    printf("请输入新的用户名：");
                    scanf("%s", c);
                    strcpy( p->username, c);
                    strcpy( p->account, c);
                    printf("**更改完成**\n新用户名为：%s", p->account);
                }
                else if (x == 2)
                {
                    printf("请输入新的密码：");
                    scanf("%s", d);
                    strcpy( p->password, d);
                    printf("**更改完成**\n新密码为：%s",  p->password);
                }
                else if (x == 3)
                {
                    printf("请输入新的电话：");
                    scanf("%s", phone1);
                    strcpy( p->phone, phone1);
                    printf("**更改完成**\n新电话为：%s", p->phone);
                }
                else if (x == 4)
                {
                    printf("请输入新的车牌号：");
                    scanf("%s", carname1);
                    strcpy( p->carname, carname1);
                    printf("**更改完成**\n新车牌号为：%s",  p->carname);
                }
                else if (x == 5)
                {
                    printf("请输入新的车位：");
                    scanf("%s", stall1);
                    strcpy( p->stall, stall1);
                    printf("**更改完成**\n新车位为：%s", p->stall);
                }
                 else if (x == 6)
                {
                    printf("请输入新的入场时间：");
                    scanf("%d%d%d%d%d",&year2,&month2,&day2,&hour2,&min2);
                    p->reach.year=year2;
                    p->reach.month=month2;
                    p->reach.day=day2;
                    p->reach.hour=hour2;
                    p->reach.min=min2;
                    printf("**更改完成**\n新入场时间为：%d/%d/%d %d:%d",
                        p->reach.year,p->reach.month,p->reach.day,p->reach.hour,p->reach.min);
                }
                 else if (x == 7)
                {
                    printf("请输入新的出场时间：");
                    scanf("%d%d%d%d%d",&year3,&month3,&day3,&hour3,&min3);
                    p->leave.year=year3;
                    p->leave.month=month3;
                    p->leave.day=day3;
                    p->leave.hour=hour3;
                    p->leave.min=min3;
                    printf("**更改完成**\n新出场时间为：%d/%d/%d %d:%d",
                           p->leave.year,p->leave.month,p->leave.day,p->leave.hour,p->leave.min);
                }
                else
                {
                    printf("**输入错误请重新输入**\n");
                    goto E;
                }
                break;
            }
            else if(p->UserNext==NULL&&p->username!=c)
            {
                printf("**未查询到该用户信息，请重新输入用户名**");
                p=UserHead;
                goto F;
            }
            else p=p->UserNext;
        }
            break;
    case 9://更改管理员账号密码
    G:
        printf("请输入原管理员账号:");
        scanf("%s", c);
        while(p2!=NULL)
            {if (strcmp(p2->account, c) == 0)
            {   printf("请选择更改内容:\n1.账号\n2.密码");
                scanf("%d", &x);

                if (x == 1)
                {
                    printf("请输入新的账号：");
                    scanf("%s", c);
                    strcpy(p2->account, c);
                    printf("**更改完成**\n新账号为：%s", p2->account);
                    break;
                }
                else if (x == 2)
                {
                    printf("请输入新的密码：");
                    scanf("%s", d);
                    strcpy(p2->password, d);
                    printf("**更改完成**\n新密码为：%s", p2->password);
                    break;
                }
            }
            else if(p2->AdminNext==NULL&&p2->account!=c)
            {
                printf("**未查询到该用户信息，请重新输入账号**\n");
                p2=AdminHead;
                goto G;
            }
            p2=p2->AdminNext;
        }
        break;
    case 10://导出所有用户信息
        pFile = fopen("Part.txt", "w+");         //打开Part.txt
        fprintf(pFile,"|       车牌号        |          用户      |   电话           |车位 |余额|状态|\n");
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
        printf("**导出完成**\n");
        break;
    case 11:
        printf("请输入要删除的用户账号：");
        scanf("%s",account1);
        UserHead=Deleteuser(UserHead,account1);
        Delhead=Deleteacc(Delhead,account1);
        break;
    case 12:
        printf("请输入要删除的管理员账号：");
        scanf("%s",account1);
        AdminHead=Deleteadmin(AdminHead,account1);
        break;
    case 13://返回登陆页面
        Login();
        break;
    case 14://退出
        exit(0);
    default:
        printf("**输入错误请重新输入**\n");
        goto D;
        }
        goto T;
}
void UserMeau(struct useraccount *UserCurrent)              //用户菜单  //获取传递的用户信息节点
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
    printf("\n用户名：%s\n电话：%s\n车牌号：%s\n对应车位：%s\n余额：%d\n已停车时间：%d天%d小时%d分\n需缴费%d元\n",
    UserCurrent->username,UserCurrent->phone,UserCurrent->carname,UserCurrent->stall,UserCurrent->balance,days1,hour1, min1,totalmoney);
    printf("\n**********登陆成功************\n");
    printf("**********1.停车缴费**********\n");
    printf("**********2.余额充值**********\n");
    printf("**********3.更改车牌号********\n");
    printf("**********4.更改电话**********\n");
    printf("**********5.修改用户名********\n");
    printf("**********6.修改密码**********\n");
    printf("**********7.返回登陆页面******\n");
    printf("**********8.注销账户**********\n");
    printf("**********9.退出**************\n");
    printf("******************************\n");
    printf("--请输入相应的数字选择功能！--\n");
B:
    scanf("%d", &a);
    switch (a)
    {
    case 1://停车缴费
        printf("需缴费%d元，请输入yes确认支付或其他字符取消\n",totalmoney);
        scanf("%s",c);
        if(strcmp(c,"yes")==0)
        {   if(UserCurrent->balance>=totalmoney)
            {printf("缴费完成\n");
            UserCurrent->balance-=totalmoney;}
            else
            printf("余额不足！请充值！\n");
        }
        else
        {
            printf("已取消\n");
        }
        break;
    case 2://余额充值
        printf("请输入充值金额：");
        scanf("%d", &b);
        UserCurrent->balance+= b;
        printf("**充值完成**\n现在的余额为：%d\n", UserCurrent->balance);
        break;
    case 3://更改车牌号
        printf("请输入新的车牌号：");
        scanf("%s", c);
        strcpy(UserCurrent->carname, c);
        printf("更改成功\n现在车牌号为：%s\n",  UserCurrent->carname);
        break;
    case 4://更改电话
        printf("请输入新的电话号码：");
        scanf("%s", c);
        strcpy( UserCurrent->phone, c);
        printf("更改成功\n现在电话为：%s\n",  UserCurrent->phone);
        break;
    case 5://修改用户名
        printf("请输入新的用户名(20字符以内)：");
        scanf("%s", c);
        strcpy( UserCurrent->username, c);
        printf("修改成功\n现在用户名为：%s\n", UserCurrent->username);
        break;
    case 6://修改密码
        printf("请输入新的密码(20字符以内)：");
        scanf("%s", c);
        strcpy( UserCurrent->password, c);
        printf("修改成功\n现在密码为：%s\n",UserCurrent->password);
        break;
    case 7://返回登陆页面
        Login();
        break;
    case 8:
        printf("你确定要注销账户吗？\n请输入yes确定或其他字符取消\n");
        scanf("%s",c);
        if(strcmp(c,"yes")==0)
        {   ++message;
            adddelaccount(UserCurrent->account);
            printf("已向管理员发送注销请求,即将返回登陆界面\n");
            Login();
        }
        else
        {
            printf("已取消\n");
        }
        break;
    case 9://退出
        exit(0);
    default:
        printf("输入错误请重新输入\n");
        goto B;

    }goto V;

}
void Login()
{   int b,c;
    char a[10];
    C:
    printf("请选择：\n1.用户登陆\n2.管理员登陆\n");
    scanf("%s",a);
    if (strcmp(a,"1")==0)                                   //用户登陆
    {A:
        b=Userlogin();
        if (b==0)
        {
            printf("输入错误，请重新输入\n");
            goto A;
        }

    }
    else if(strcmp(a,"2")==0)                               //管理员登陆
    {  B:
        c=Adminlogin();
        if(c==0)
        {
            printf("输入错误，请重新输入\n");
            goto B;
        }
    }
    else
    {
        printf("输入不合法，请重试！");
        goto C;
    }
}
int Userlogin()
{
    char account[11], password[21];
    struct useraccount *UserCurrent = UserHead;
    printf("请输入用户账号密码以登陆\n");
    while (1) {                                                         // 使用无限循环，直到找到账户
        printf("账号：");
        scanf("%10s", account);

        while (UserCurrent != NULL) {
            if (strcmp(UserCurrent->account, account) == 0) {
                break;                                                  // 找到匹配的账户,跳出循环
            }
            UserCurrent = UserCurrent->UserNext;
        }

        if (UserCurrent != NULL)
        {                                                                   // 如果找到账户则判断密码显示用户菜单
            int passwordCorrect = 0;
            do {
                printf("密码：");
                scanf("%20s", password);
                if (strcmp(UserCurrent->password, password) == 0) {
                    passwordCorrect = 1;
                    UserMeau(UserCurrent);
                    return 1;                                                // 账号密码正确，返回1表示登录成功
                }
                else
                {
                    printf("密码输入错误，请重新输入\n");
                }
            } while (!passwordCorrect);                                     // 密码不正确时继续循环
        }
        else
        {                                                            // 如果没有找到账户
            printf("账户不存在，请重新输入\n");
            UserCurrent=UserHead;
        }
    }
}
int Adminlogin()
{
    char account[11], password[21];
    struct adminaccount *AdminCurrent = NULL;
    AdminCurrent=AdminHead;                                        // 从头节点开始遍历链表
    printf("请输入管理员账号密码以登陆\n");
    while (1) {                                                    // 使用无限循环，直到找到账户
        printf("账号：");
        scanf("%10s", account);
        while (AdminCurrent != NULL)
        {
            if (strcmp(AdminCurrent->account, account) == 0)
            {
                break;                                              // 找到匹配的账户,跳出循环
            }
            AdminCurrent = AdminCurrent->AdminNext;             // 没找到，移动到下一个节点
        }
        if (AdminCurrent != NULL)                               // 如果找到账户则判断密码显示用户菜单
    {
            int passwordCorrect = 0;
        do {
                printf("密码：");
                scanf("%20s", password);
                if (strcmp(AdminCurrent->password, password) == 0) {
                    passwordCorrect = 1;
                    AdminMeau();
                    return 1;                                   // 账号密码正确，返回1表示登录成功
                }
                else
                {
                    printf("密码输入错误，请重新输入\n");
                }
            } while (!passwordCorrect);                         // 密码不正确时继续循环
    }
        else
        {                                                          // 如果没有找到账户则重新输入
            printf("账户不存在，请重新输入\n");
            AdminCurrent=AdminHead;
        }
    }
}
void addUser(char *account, char *password,char *username,char *phone,char *carname,char *stall,int balance1,int suit1,
             int year2,int month2,int day2,int hour2,int min2,int year3,int month3,int day3,int hour3,int min3)
{
    userNode = (struct useraccount *)malloc(sizeof(struct useraccount));
    strncpy(userNode->account, account, sizeof(userNode->account) - 1); //限制添加长度
    userNode->account[sizeof(userNode->account) - 1] = '\0';           // 在末尾添加‘0’确保账号字符串正确结束
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
        UserHead= userNode;                                                  // 如果链表为空，将新节点设置为头节点
        userNode->UserNext  = NULL;
    }
    else                                                            // 否则，找到链表的最后一个节点进行添加
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
    strncpy(adminnewNode->account, account, sizeof(adminnewNode->account) - 1);//限制添加长度
    adminnewNode->account[sizeof(adminnewNode->account) - 1] = '\0';           // 在末尾添加‘0’确保账号字符串正确结束
    strncpy(adminnewNode->password, password, sizeof(adminnewNode->password) - 1);
    adminnewNode->password[sizeof(adminnewNode->password) - 1] = '\0';
    if (AdminHead == NULL)               // 如果链表为空，将新节点设置为头节点
    {
        AdminHead = adminnewNode;
        adminnewNode->AdminNext = NULL;
    }
    else                            // 否则，找到链表的最后一个节点进行添加
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
    if (Delhead== NULL)               // 如果链表为空，将新节点设置为头节点
    {
        Delhead= delnode;
        delnode->delnext = NULL;
    }
    else                            // 否则，找到链表的最后一个节点进行添加
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
struct useraccount *Deleteuser(struct useraccount *UserHead,char account1[11])//删除指定用户
{
    struct useraccount * pb,*pf;
    pb=UserHead;//让pb指向头节点
    if(UserHead == NULL)//链表为空链表
    {
        printf("用户链表为空\n");
    }
    while(strcmp(pb->account,account1)!=0 && pb->UserNext!=NULL)//遍历用户链表
    {
        pf=pb;
        pb=pb->UserNext;
    }
    if(strcmp(pb->account,account1)==0)
    {
        if(pb == UserHead)//找到的节点是头节点
        {
            UserHead= pb->UserNext;
        }
        else//找到节点
        {
            pf->UserNext = pb->UserNext;
        }
            free(pb);
            printf("**删除成功**\n");
    }
    else//没有找到要删除的节点
    {
        printf("没有找到您要删除的用户\n");
    }
    return UserHead;
}
struct adminaccount *Deleteadmin(struct adminaccount *AdminHead,char account1[11])//删除指定管理员，只有一个管理员时无法删除
{
    struct adminaccount * pb,*pf;
    pb=AdminHead;
    while(strcmp(pb->account,account1)!=0 && pb->AdminNext!=NULL)//遍历管理员链表
    {
        pf=pb;
        pb=pb->AdminNext;
    }
    if(strcmp(pb->account,account1)==0)//找到了一个节点的num和num相等
    {
        if(pb == AdminHead)//找到的节点是头节点
        {   if(pb->AdminNext==NULL)//只有头节点，无法删除
            {
                printf("仅有一个管理员！！无法删除！！\n");
            }
            AdminHead= pb->AdminNext;
        }
        else  //找到节点
        {
            pf->AdminNext = pb->AdminNext;
            printf("**删除成功**\n");
        }
            free(pb);
    }
    else     //没有找到要删除的节点
    {
        printf("没有找到您要删除的管理员\n");
    }
    return AdminHead;
}
struct del *Deleteacc(struct del *Delhead,char account1[11])//删除指定用户
{
    struct del * pb,*pf;
    pb=Delhead;            //让pb指向头节点
    while(strcmp(pb->deleteaccount,account1)!=0 && pb->delnext!=NULL)//遍历用户链表
    {
        pf=pb;
        pb=pb->delnext;
    }
    if(strcmp(pb->deleteaccount,account1)==0)
    {
        if(pb == Delhead)//找到的节点是头节点
        {
            Delhead= pb->delnext;
        }
        else//找到节点
        {
            pf->delnext = pb->delnext;
        }
            free(pb);
    }
    return Delhead;
}
int days(int year, int month)//计算月份的天数
{
    int PerMonth[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    if (month == 2 && leapyear(year))
    {
        return 29;
    }
    return PerMonth[month-1];
}
int leapyear(int year1)//判断是否为闰年
{
    if ((year1%4==0 && year1%100!=0)||year1%400==0)
    {
        return 1;
    }
    return 0;
}
int daysgap(time t1, time t2)//计算日期间隔
{
    if (t1.year>t2.year||(t1.year==t2.year&&t1.month>t2.month)||(t1.year==t2.year&&t1.month==t2.month&&t1.day>t2.day)) // 如果时间1在时间2之后，则时间异常
    {
       printf("停车时间异常！请联系管理员！！");
    }
    int gap;
    for (int y = t1.year;y<t2.year;y++) // 计算年份之间的天数差
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
    for (int m=t1.month; m<t2.month; m++)  //计算月份之间的天数差
    {
        gap+=days(t1.year,m);
    }
    gap+=(t2.day-t1.day);  // 计算日期之间的天数差
    return gap;
}
