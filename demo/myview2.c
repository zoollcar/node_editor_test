struct nk_canvas {
    struct nk_command_buffer *painter;
    struct nk_vec2 item_spacing;
    struct nk_vec2 panel_padding;
    struct nk_style_item window_background;
};

static void
canvas_begin(struct nk_context *ctx, struct nk_canvas *canvas, nk_flags flags,
    int x, int y, int width, int height, struct nk_color background_color)
{
    /* 保存将会被重写的样式 */
    canvas->panel_padding = ctx->style.window.padding;
    canvas->item_spacing = ctx->style.window.spacing;
    canvas->window_background = ctx->style.window.fixed_background;

    /* 使用完整的窗口空间并设置背景 */
    ctx->style.window.spacing = nk_vec2(0,0);
    ctx->style.window.padding = nk_vec2(0,0);
    ctx->style.window.fixed_background = nk_style_item_color(background_color);

    /* 创建/更新 窗口 设置位置和大小 */
    flags = flags & ~NK_WINDOW_DYNAMIC;
    nk_window_set_bounds(ctx, "Window", nk_rect(x, y, width, height));
    nk_begin(ctx, "Window", nk_rect(x, y, width, height), NK_WINDOW_NO_SCROLLBAR|flags);
    /* 分配这个窗口用来绘制 */
    {
    struct nk_rect total_space;
    total_space = nk_window_get_content_region(ctx);
    nk_layout_row_dynamic(ctx, total_space.h, 1);
    nk_widget(&total_space, ctx);
    canvas->painter = nk_window_get_canvas(ctx);
    }
}

static void
canvas_end(struct nk_context *ctx, struct nk_canvas *canvas)
{
    nk_end(ctx); 
    ctx->style.window.spacing = canvas->panel_padding;
    ctx->style.window.padding = canvas->item_spacing;
    ctx->style.window.fixed_background = canvas->window_background;
}
static void
mycanvas(struct nk_context *ctx,GdiFont *font){
    /* 画布 */
        static int width = WINDOW_WIDTH, height = WINDOW_HEIGHT;
        {
        struct nk_canvas canvas;
        canvas_begin(ctx, &canvas, 0, 0, 0, width, height, nk_rgb(250,250,250));
        {
            /* 绘制矩形 */
            nk_fill_rect(canvas.painter, nk_rect(15,15,210,210), 5, nk_rgb(247, 230, 154));
            nk_fill_rect(canvas.painter, nk_rect(20,20,200,200), 5, nk_rgb(188, 174, 118));
            nk_draw_text(canvas.painter, nk_rect(30, 30, 150, 20), L"需要绘制的文字", 12, &font->nk, nk_rgb(188,174,118), nk_rgb(0,0,0));
            nk_fill_rect(canvas.painter, nk_rect(250,20,100,100), 0, nk_rgb(0,0,255));
            /* 绘制圆形 */
            nk_fill_circle(canvas.painter, nk_rect(20,250,100,100), nk_rgb(255,0,0));
            /* 绘制三角形 */
            nk_fill_triangle(canvas.painter, 250, 250, 350, 250, 300, 350, nk_rgb(0,255,0));
            /* 绘制圆形 */
            nk_fill_arc(canvas.painter, 300, 180, 50, 0, 3.141592654f * 3.0f / 4.0f, nk_rgb(255,255,0));

            /* 多边形绘制 */
            {float points[12];
            points[0] = 200; points[1] = 250;
            points[2] = 250; points[3] = 350;
            points[4] = 225; points[5] = 350;
            points[6] = 200; points[7] = 300;
            points[8] = 175; points[9] = 350;
            points[10] = 150; points[11] = 350;
            nk_fill_polygon(canvas.painter, points, 6, nk_rgb(0,0,0));}

            /* 绘制直线 */
            nk_stroke_line(canvas.painter, 15, 10, 200, 10, 2.0f, nk_rgb(189,45,75));
            nk_stroke_rect(canvas.painter, nk_rect(370, 20, 100, 100), 10, 3, nk_rgb(0,0,255));
            /* 绘制曲线 */
            nk_stroke_curve(canvas.painter, 380, 200, 405, 270, 455, 120, 480, 200, 2, nk_rgb(0,150,220));
            nk_stroke_circle(canvas.painter, nk_rect(20, 370, 100, 100), 5, nk_rgb(0,255,120));
            nk_stroke_triangle(canvas.painter, 370, 250, 470, 250, 420, 350, 6, nk_rgb(255,0,143));
        }
        canvas_end(ctx, &canvas);
        }
}
/* 加载图片 */
/* 失败的加载图片
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
static int showimg(struct nk_context *ctx){
    int x=100,y=100,n;
    // unsigned char *myimg = stbi_load("./img.png", &x, &y, &n, 0);
    BITMAPINFO bi;
    char* ppvBits;
    HDC hDC = GetDC(0);
    HDC MDC = CreateCompalibleDC(hDC);
    HBITMAP mimg = CreateCompatibleBitmap(MDC,x,y);
    SetBackColor(MDC,RGB(0,0,0));
    SetTextColor(MDC,RGB(255,0,0));
    TextOut(MDC,0,0,"zoollcar",strlen("zoollcar"));
    struct nk_rect r = {0,0,x,y};
    static struct nk_image theimg;
    theimg = nk_subimage_ptr(MDC,x,y,r);
    nk_image(ctx,theimg);
    //// SetDIBits(NULL,mimg,NULL,NULL,NULL,???,NULL);
    //// CreateDIBSection(NULL, &bi, DIB_RGB_COLORS, (void**) &ppvBits, NULL, 0);
    // stbi_image_free(myimg);
}
 */

static void
myshow1(struct nk_context *ctx){
    enum {EASY, HARD};
    static int op = EASY;
    static float value = 0.6f;
    static int i =  20;
    if (nk_begin(ctx, "myview", nk_rect(50, 50, 220, 220),
        NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|NK_WINDOW_CLOSABLE|NK_WINDOW_MINIMIZABLE)) {
        /* 固定小部件像素宽度 */
        nk_layout_row_static(ctx, 30, 80, 1);
        if (nk_button_label(ctx, "button")) {
            fprintf(stdout,"button on click\n");
        }
        /* 固定小部件宽高比 */
        nk_layout_row_dynamic(ctx, 30, 2);
        if (nk_option_label(ctx, "easy", op == EASY)) op = EASY;
        if (nk_option_label(ctx, "hard", op == HARD)) op = HARD;
        // showimg(ctx);
        /* 自定义小部件像素宽度 */
        nk_layout_row_begin(ctx, NK_STATIC, 30, 2);
        {
            nk_layout_row_push(ctx, 50);
            nk_label(ctx, "Volume:", NK_TEXT_LEFT);
            nk_layout_row_push(ctx, 110);
            nk_slider_float(ctx, 0, &value, 1.0f, 0.1f);
        }
        nk_layout_row_end(ctx);
        /* 建立一个点击出现右键菜单的区域 */
        struct nk_rect bounds;
        nk_layout_row_static(ctx, 30, 160, 1);
        bounds = nk_widget_bounds(ctx);
        nk_label(ctx, "Right click me for menu", NK_TEXT_LEFT);
        if (nk_contextual_begin(ctx, 0, nk_vec2(100, 300), bounds)) {
            /* 右键菜单 */
            static size_t prog = 40;
            static int slider = 10;
            nk_layout_row_dynamic(ctx, 25, 1);
            nk_progress(ctx, &prog, 100, NK_MODIFIABLE);
            nk_slider_int(ctx, 0, &slider, 16, 1);
            nk_contextual_end(ctx);
        }
    }
    nk_end(ctx);
}
static void
myview2(struct nk_context *ctx)
{
    myshow1(ctx);
    // mycanvas(ctx,NULL); // no font
}