#include <stdio.h>
#include <stdlib.h>
#include "../mlx/mlx.h"

# define WIN_WIDTH 800
# define WIN_HEIGHT 600

# define IMG_WIDTH 400
# define IMG_HEIGHT 300

typedef struct  s_img
{
    void        *img_ptr;
    int         *data;
    int         size_l;
    int         bpp;
    int         endian;
}               t_img;

typedef struct  s_mlx
{
    void        *mlx_ptr;
    void        *win;
}               t_mlx;

t_mlx   *mlx;
int     counter;

int         key_hook(int key, void *param __attribute__((unused)))
{
    t_img   img;
    int     count_w;
    int     count_h;

    printf("key hook called\n");
    img.img_ptr = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
    img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);

    count_h = -1;
    while (++count_h < IMG_HEIGHT)
    {
        count_w = -1;
        while (++count_w < IMG_WIDTH)
        {
            if (count_w % 20)
                img.data[count_h * IMG_WIDTH + count_w] = (counter % 2) ? 0xFFFFFF : 0x2485FF;
            else
                img.data[count_h * IMG_WIDTH + count_w] = (counter % 2) ? 0x00FF00 : 0x008500;
        }
    }
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img.img_ptr, 0, 0);
    if (key == 0xFF1B)
    {
        exit(0);
    }
    mlx_destroy_image(mlx->mlx_ptr, img.img_ptr);
    counter++;
    return (0);
}

int main(void)
{
    int     count_w;
    int     count_h;
    t_img   img;

    counter = 0;
    mlx = malloc(sizeof(t_mlx));
    mlx->mlx_ptr = mlx_init();
    mlx->win = mlx_new_window(mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "A simple example");
    img.img_ptr = mlx_new_image(mlx->mlx_ptr, IMG_WIDTH, IMG_HEIGHT);
    img.data = (int *)mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);

    count_h = -1;
    while (++count_h < IMG_HEIGHT)
    {
        count_w = -1;
        while (++count_w < IMG_WIDTH)
        {
            if (count_w % 20)
                img.data[count_h * IMG_WIDTH + count_w] = 0xFFFFFF;
            else
                img.data[count_h * IMG_WIDTH + count_w] = 0x00FF00;
        }
    }
    mlx_put_image_to_window(mlx->mlx_ptr, mlx->win, img.img_ptr, 0, 0);
    mlx_hook(mlx->win, 2, (1L << 0), key_hook, NULL);
    mlx_loop(mlx->mlx_ptr);
    return (0);
}