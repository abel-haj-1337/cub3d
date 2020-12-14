#include "cub3d.h"

t_mlx		mlx;
t_player	player;
int			window_height = 500;
int			window_width = 500;

void            my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_height + x * (data->bpp / 8));
    *(unsigned int*)dst = color;
}


int			main(void)
{
	void *image_address;
	t_image	image;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, window_width, window_height, "MLX Put Image");

	image.img = mlx_new_image(mlx.mlx, window_width/4, window_height/4);
	image.addr = mlx_get_data_addr(image.img, &image.bpp, &image.line_height, &image.endian);
	my_mlx_pixel_put(&image, 5, 5, rgb_to_hex(255, 0, 0));
	mlx_put_image_to_window(mlx.mlx, mlx.win, image.img, 0, 0);

	mlx_loop(mlx.mlx);

	return 0;
}
