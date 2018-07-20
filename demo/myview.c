#include "game.c"
static void
myview(struct nk_context *ctx,struct mymsg *s_msg)
{
    if (nk_begin(ctx, "myview", nk_rect(300, 50, 400, 500),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
        NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
        enum {EASY, HARD};
        static int op = EASY;
        static float value = 0.6f;
        // static int i =  20;
        static char show_value[10];
        //下面是贪吃蛇使用
        static int one = 1;
        int i,j;
        static enum way s_way = D;
        static struct mode *head;
        static int appleX,appleY;
        static char grid[Y][X+1];
        // 重置地图
        for (i=0;i<Y;i++){
            for (j=0;j<X;j++)
                grid[i][j] = '.';
            grid[i][X] = '\0';
        }
        // 初始化
        if(one == 1){
            head = s_init();
            appleX = rand() % X; 
            appleY = rand() % Y; 
            printf("apple at %d %d\n",appleX,appleY);
            one = 0;
        }
        // 点击鼠标左键
        if(s_msg->LBUTTONDOWN)
            s_way = turn_left(s_way);
        
        if(s_msg->key != 0)
            s_way = turn_to(s_msg->key);
        // 蛇移动
        head = s_work(head,s_way,&appleX,&appleY);
        // 绘制蛇和苹果
        gamework(grid,head);
        grid[appleY][appleX] = '$';
        // 固定小部件像素宽度
        // 创建小部件之前使用 nk_layout_xxx 来说明后面的小部件布局
        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "button")) {
            // 点击事件
            fprintf(stdout,"button on click\n");
        }
        // 小部件横向动态（默认是纵向）
        nk_layout_row_dynamic(ctx, 30, 2);
        
        if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
        if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
        
        // 小部件横向分布开始
        nk_layout_row_begin(ctx, NK_STATIC, 30, 3);
        
        // 小部件宽度固定（单位像素）
        nk_layout_row_push(ctx, 50);
        nk_label(ctx, "Volume:", NK_TEXT_LEFT);
        nk_layout_row_push(ctx, 110);
        if (nk_slider_float(ctx, 0, &value, 1.0f, 0.02f)){
            sprintf(show_value,"%f",value);
        }
        nk_layout_row_push(ctx, 50);
        nk_label(ctx, show_value, NK_TEXT_LEFT);
        // 小部件横向分布结束
        nk_layout_row_end(ctx);
        
        // nk_layout_row_static(ctx, 4, 50, 1);
        // nk_layout_row_dynamic(ctx, 4, 1);
        nk_layout_space_begin(ctx, NK_STATIC, 500, INT_MAX);
        for (i = 0; i <Y; ++i) {
                nk_layout_space_push(ctx, nk_rect(0,i*12,200,100));
                nk_label(ctx, grid[i], NK_TEXT_LEFT);
                //fprintf(stdout,grid[i]);
        }
        nk_layout_space_end(ctx);
    }
    nk_end(ctx);
}