typedef struct student                        //学生信息存储结构
{
    char no[11];                              //学号
    char name[15];                            //姓名
    int score[3];                             //成绩
    int sum;                                  //总分
    float average;                            //平均分
    int order;                                //按成绩排序
    struct student *next;
} student;

int Menu_select();                            //菜单
struct student *Create(student *head,student *new);        //建立
void Print(student *head,struct nk_context *ctx);                    //打印
struct student *Compute(student *head);       //计算
struct student *Append(student *head,student *new);        //追加
struct student *Del(student *head,char *);           //删除
struct student *Insert(student *head);        //插入
struct student *change(student *head);        //修改
void Search(student *head);                   //查找
void Save(student *head);                     //保存文件
struct student *Load(student *head);          //读取文件
struct student *Sort(student *head);

/*****************************菜单****************************/
int Menu_select()
{
    int choice;
    printf("***************************菜单***************\n");
    printf("                        1  输入               \n");
    printf("                        2  打印               \n");
    printf("                        3  计算               \n");
    printf("                        4  追加               \n");
    printf("                        5  删除               \n");
    printf("                        6  插入               \n");
    printf("                        7  查找               \n");
    printf("                        8  修改               \n");
    printf("                        9  保存               \n");
    printf("                        10 读入               \n");
    printf("                        11 排序               \n");
    printf("                        12 退出               \n");
    printf("Enter your choice(0-11):");
    scanf("%d",&choice);
    return choice;
}
/*****************************建立链表************************/
struct student *Create(student *head,student *new)        //ok
{
    student *p,*q;;
    head=(student *)malloc(sizeof(student));
    head->next=NULL;
    q=head;
    
    p=(student*)malloc(sizeof(student));
    strcpy(p->no , new->no);
    strcpy(p->name , new->name);
    p->score[0] = new->score[0];
    p->score[1] = new->score[1];
    p->score[2] = new->score[2];
    p->sum=0;
    p->average=0;
    p->order=0;
    q->next=p;
    q=p;
    
    q->next=NULL;
    return head;
}
/*****************************打印****************************/
void Print(student *head,struct nk_context *ctx)              //ok
{
    static char timpstr[80];
    student *p=head;
    nk_layout_row_dynamic(ctx, 20, 1);
    if (head == NULL) {
        //nk_label(ctx, "num  nume  nath  english  C    sum  average Rank", NK_TEXT_LEFT);
        nk_label(ctx, "学号  姓名  数学  英语  数据  总分  平均  排名", NK_TEXT_LEFT);
        return;
    };
    //printf("Print working\n");
    nk_label(ctx, "学号  姓名  数学  英语  数据  总分  平均  排名", NK_TEXT_LEFT);
    //printf("1\n");
    while(p->next)
    {
        //printf("2\n");
        p=p->next;
        sprintf(timpstr,"%-7s%-7s%-7d%-7d%-7d%-7d%-7.2f%9d",p->no,p->name,p->score[0],p->score[1],p->score[2],p->sum,p->average,p->order);
        //printf(timpstr);
        //printf("\n");
        nk_label(ctx, timpstr, NK_TEXT_LEFT);
    }
    return;
}
/*****************************计算****************************/
struct student *Compute(student *head)//OK
{
    student *p=head->next;
    while(p)
    {
        p->sum=p->score[0]+p->score[1]+p->score[2];
        p->average=p->sum/3.0;
        p=p->next;
    }
    return head;
}
/*****************************追加****************************/
struct student *Append(student *head,student *new)//OK
{
    student *p,*q=head,*t;
    p=(student*)malloc(sizeof(student));
    strcpy(p->no , new->no);
    strcpy(p->name , new->name);
    p->score[0] = new->score[0];
    p->score[1] = new->score[1];
    p->score[2] = new->score[2];
    p->sum=0;
    p->average=0;
    p->order=0;
    while(q)
    {
        t=q;
        q=q->next;
    }
    t->next=p;
    t=p;
    t->next=NULL;
    return head;
}
/*****************************删除****************************/
struct student *Del(student *head,char *number) //OK
{
    if(head == NULL) {
        printf("head == NULL");
        return head;
    }
    printf("Del is working\n");
    student *p=head,*q;
    while(p->next)
    {
        if (strcmp(number,p->no) == 0){
            q->next=p->next;
            free(p);
        }
        q=p;
        p=p->next;
    }
    return head;
}
/*****************************插入****************************/
struct student *Insert(student *head)  //ok
{
    char no[11];
    student *p,*q=head,*t;
    printf("请输入要插入的学生位置：");
    scanf("%s",no);
    p=(student *)malloc(sizeof(student));
    printf("请输入要增加的学生信息:\n");
    printf("请输入学号:");
    scanf("%s",p->no);
    printf("请输入姓名:");
    scanf("%s",p->name);
    printf("请输入数学成绩:");
    scanf("%d",&p->score[0]);
    printf("请输入英语成绩:");
    scanf("%d",&p->score[1]);
    printf("请输入数据结构成绩:");
    scanf("%d",&p->score[2]);
    p->sum=0;
    p->average=0;
    p->order=0;
    while(q->next&&strcmp(q->next->no,no))
    {
        q=q->next;
        t=q;
    }
    p->next=t->next;
    t->next=p;
    return head;
}
/****************************修改*****************************/
struct student *change(student *head)   //ok
{
    char no[11];
    student *q=head->next;
    printf("请输入要修改的学生学号:");
    scanf("%s",no);
    while(q&&strcmp(q->no,no))
    {
        q=q->next;
    }
    printf("请输入学生学号:");
    scanf("%s",q->no);
    printf("请输入学生姓名:");
    scanf("%s",q->name);
    printf("请输入学生数学成绩:");
    scanf("%d",&q->score[0]);
    printf("请输入学生英语成绩:");
    scanf("%d",&q->score[1]);
    printf("请输入学生数据结构成绩:");
    scanf("%d",&q->score[2]);
    return head;
};
/****************************查找*****************************/
void Search(student *head)               //ok
{
    char no[15];
    student *p=head->next;
    printf("请输入要查询的学生学号:");
    scanf("%s",no);
    while(p&&strcmp(no,p->no))
        p=p->next;
    printf("学号    姓名    数学    英语    数据结构    总分    平均分       排名\n");
    printf("%s        %s        %d      %d      %d          %d      %.2f           %d  \n",p->no,p->name,p->score[0],p->score[1],p->score[2],p->sum,p->average,p->order);
}
/****************************文件保存*************************/
void Save(student *head)                 //ok
{
    FILE *fp;
    if((fp=fopen("student.txt","w"))==NULL)
    {
        printf("文件打开失败\n");
        getchar();
        exit(1);
    }

    student *p=head->next;
    while(p)
    {
        fprintf(fp,"%s %s %d %d %d %d %f %d\n",p->no,p->name,p->score[0],p->score[1],p->score[2],p->sum,p->average,p->order);
        p=p->next;
    }
    fclose(fp);
}
/****************************文件读取*************************/
struct student *Load(student *head)      //ok
{
    head=(student*)malloc(sizeof(student));
    head->next=NULL;
    FILE *fp;
    if((fp=fopen("student.txt","r"))==NULL)
    {
        printf("文件打开失败\n");
        getchar();
        exit(1);
    }
    student *p=(student*)malloc(sizeof(student));
    student *t;
    head->next=p;
    while(fscanf(fp,"%s%s%d%d%d%d%f%d",p->no,p->name,&p->score[0],&p->score[1],&p->score[2],&p->sum,&p->average,&p->order)==8)
    {
        t=p;
        p=(student*)malloc(sizeof(student));
        t->next=p;
    }
    free(p);
    t->next=NULL;
    fclose(fp);
    return head;
}
/****************************排序*****************************/
struct student *Sort(student *head)
{
    int i=1;
    student *q, *s, *pre ,*p,*a;
    p=head->next;
    q=p->next;
    p->next=NULL;
    while(q)
    {
        s=q;
        q=q->next;
        pre=head;
        p=head->next;
        while(p!=NULL && p->sum > s->sum)
        {
            pre=p;
            p=p->next;
        }
        s->next=p;
        pre->next=s;
    }
    a=head->next;
    while(a)
    {
        a->order=i++;
        a=a->next;
    }
    return head;
}