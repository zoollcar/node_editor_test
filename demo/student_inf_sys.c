#include "student_inf_sys_base.c"
static void
student_inf_sys(struct nk_context *ctx)
{
    if (nk_begin(ctx, "学生信息管理系统", nk_rect(350, 50, 300, 400),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
        NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
    {
        
        static student *head=NULL;
        static student test = {"1","aa",{1,2,3},0,0,0,NULL}; 
        static int show_Insert_stu = nk_false;
        static int show_Del_stu = nk_false;
        
        if (show_Insert_stu) // 增加学生弹出式窗口
        {
            /* about popup */
            static struct nk_rect s = {20, 100, 300, 400};
            if (nk_popup_begin(ctx, NK_POPUP_STATIC, "About", NK_WINDOW_CLOSABLE, s))
            {
                static student new = {"\0","\0",{0},0,0,0,NULL};
                static int timpa[5];
                static char timpb[3][15];
                static const float ratio[] = {200, 150};
                nk_layout_row(ctx, NK_STATIC, 25, 1, ratio);
                nk_label(ctx,"请输入学生信息:", NK_TEXT_LEFT);
                // 学号  姓名  数学  英语  数据  总分  平均  排名
                nk_label(ctx, "学号:", NK_TEXT_LEFT);
                nk_edit_string(ctx, NK_EDIT_SIMPLE, new.no, &timpa[0], 11, nk_filter_default);
                nk_label(ctx, "姓名:", NK_TEXT_LEFT);
                nk_edit_string(ctx, NK_EDIT_SIMPLE, new.name, &timpa[1], 15, nk_filter_default);
                nk_label(ctx, "数学:", NK_TEXT_LEFT);
                nk_edit_string(ctx, NK_EDIT_SIMPLE, timpb[0], &timpa[2], 10, nk_filter_decimal);
                new.score[0] = atoi(timpb[0]);
                nk_label(ctx, "英语:", NK_TEXT_LEFT);
                nk_edit_string(ctx, NK_EDIT_SIMPLE, timpb[1], &timpa[3], 10, nk_filter_decimal);
                new.score[1] = atoi(timpb[1]);
                nk_label(ctx, "数据:", NK_TEXT_LEFT);
                nk_edit_string(ctx, NK_EDIT_SIMPLE, timpb[2], &timpa[4], 10, nk_filter_decimal);
                new.score[2] = atoi(timpb[2]);
                if (nk_button_label(ctx, "增加记录")){
                    fprintf(stdout,"Insert\n");
                    // 如果是第一个添加的信息就新建表，否则追加表
                    if (head == NULL){
                        Create(head,&new);
                    }else{
                        Append(head,&new);
                    }
                    Compute(head);
                    show_Insert_stu = nk_false;
                }
                nk_popup_end(ctx);
            } else show_Insert_stu = nk_false;
        }
        if (show_Del_stu) // 增加学生弹出式窗口
        {
            /* about popup */
            static struct nk_rect s = {20, 100, 300, 400};
            if (nk_popup_begin(ctx, NK_POPUP_STATIC, "About", NK_WINDOW_CLOSABLE, s))
            {
                static int timpa;
                static char timpb[11];
                static const float ratio[] = {200, 150};
                nk_layout_row(ctx, NK_STATIC, 25, 1, ratio);
                nk_label(ctx,"请输入要删除学生学号:", NK_TEXT_LEFT);
                nk_edit_string(ctx, NK_EDIT_SIMPLE, timpb, &timpa, 11, nk_filter_default);
                if (nk_button_label(ctx, "删除记录")){
                    head=Del(head,timpb);
                    show_Del_stu = nk_false;
                }
                nk_popup_end(ctx);
            } else show_Del_stu = nk_false;
        }
        
        nk_layout_row_static(ctx, 30, 80, 3);
        if (nk_button_label(ctx, "增加记录")) {
            fprintf(stdout,"Insert on click\n");
            show_Insert_stu = nk_true;
        }
        if (nk_button_label(ctx, "排序记录")) {
            fprintf(stdout,"Sort on click\n");
            head=Sort(head);
        }
        if (nk_button_label(ctx, "删除记录")) {
            fprintf(stdout,"Del on click\n");
            show_Del_stu = nk_true;
        }
        if (nk_button_label(ctx, "读取记录")) {
            fprintf(stdout,"load on click\n");
            head=Load(head);
        }
        if (nk_button_label(ctx, "保存记录")) {
            fprintf(stdout,"Save on click\n");
            Save(head);
        }

        student *timp = head;
        Print(head,ctx);
        head = timp;
        
    }
    nk_end(ctx);
}