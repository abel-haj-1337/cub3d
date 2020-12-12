# include "/usr/local/include/mlx.h"
# include "cub3d.h"

t_mlx		mlx;
t_player	player;
int			window_height = 500;
int			window_width = 500;

int			main(void)
{
	// system architecture : big/little endian
	int endian;
	// bits per pixel
	int bpp;
	// 
	int line_length;
	// 
	int offset;
	// 
	void *image;
	// 
	void *image_address;

	mlx.mlx = mlx_init();
	mlx.win = mlx_new_window(mlx.mlx, window_width, window_height, "MLX Put Image");

	image = mlx_new_image(mlx.mlx, window_width/4, window_height/4);
	image_address = mlx_get_data_addr(image, &bpp, &line_length, &endian);
	// mlx_string_put(mlx.mlx, mlx.win, 0, 0, 16000000, "~!@#$%^&*()_1654131");

	mlx_loop(mlx.mlx);

	printf("bpp\t%d\n", bpp);
	printf("line\t%d\n", line_length);
	printf("endian\t%d\n", endian);

	return 0;
}
