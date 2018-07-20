#define X 20
#define Y 20
enum way {U,D,L,R}; //上下左右
struct mode {
    int x;
    int y;
    struct mode *next;
};
enum way turn_left(enum way a){
    if(a == U)return L;
    if(a == D)return R;
    if(a == L)return D;
    if(a == R)return U;
}
enum way turn_to(int a){
    if(a == 1)return U;
    if(a == 2)return D;
    if(a == 3)return L;
    if(a == 4)return R;
}
struct mode * s_init(){
    // 初始化为有三段的蛇
    struct mode *head;
    head = (struct mode *)malloc(sizeof(struct mode));
    head->x = 10;
    head->y = 10;
    head->next = malloc(sizeof(struct mode));
    head->next->x = 10;
    head->next->y = 9;
    head->next->next = malloc(sizeof(struct mode));
    head->next->next->x = 10;
    head->next->next->y = 8;
    head->next->next->next = NULL;
    printf("init ok\n");
    return head;
}
void gamework(char grid[Y][X+1],struct mode *head){
    struct mode *p = head;
    // 绘制蛇头
    grid[p->y][p->x] = '@';
    p = p->next;
    // 绘制蛇身
    while(p!=NULL){
        grid[p->y][p->x] = 'X';
        p = p->next;
    }
}
void die(){
    printf("Game over");
    exit(0);
}
struct mode* s_work(struct mode *head,enum way myway,int *x,int *y){
    static long i = 0;
    struct mode *newhead;
    // printf("%ld %ld\n",clock(),i);
    if(clock()/300 > i){
        i = clock()/300;
        newhead = malloc(sizeof(struct mode));
        //根据蛇的行走方向头部延长
        switch(myway){
        case U:newhead->x = head->x;
                newhead->y = head->y -1;
                if(newhead->y >= Y || newhead->y <0)die();
                newhead->next = head;
                break;
        case D:newhead->x = head->x;
                newhead->y = head->y +1;
                if(newhead->y >= Y || newhead->y <0)die();
                newhead->next = head;
                break;
        case L:newhead->x = head->x -1;
                newhead->y = head->y;
                if(newhead->x >= X || newhead->x <0)die();
                newhead->next = head;
                break;
        case R:newhead->x = head->x +1;
                newhead->y = head->y;
                if(newhead->x >= X || newhead->x <0)die();
                newhead->next = head;
                break;
        }
        // 根据是否吃到苹果去掉尾部与否
        if(newhead->x == *x && newhead->y == *y){
            *x = rand() % X;
            *y = rand() % Y;
        }else{
            while(head->next->next)
                head = head->next;
            free(head->next);
            head->next = NULL;
        }
        return newhead;
    }
    return head;
}