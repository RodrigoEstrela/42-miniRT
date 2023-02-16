#include "../../inc/minirt.h"

int	key_press(int key, t_data *data)
{
	char	*cmd;
	char **obj_code;
	static char code[3];
	static int n;

//	printf("key: %d\n", key);
	if (key == 65307)
		exit(0);
	else if (key == 65289)
	{
		cmd = get_next_line(0);
		obj_code = ft_split(cmd, ' ');
		code[0] = ft_itoa(checkcode(obj_code[0], data))[0];
		n = ft_atoi(obj_code[1]);
		printf("code: %c, n: %d\n", code[0], n);
	}
	else if (key == 65293)
	{
		n = -1;
	}
	else if (key == 100 && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '1', '1'}, n, 0.5f);
		ray_tracer(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == 102 && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '1', '2'}, n, 0.5f);
		ray_tracer(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == 65361 && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '2', '1'}, n, 0.5f);
		ray_tracer(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == 65363 && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '2', '2'}, n, 0.5f);
		ray_tracer(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == 65362 && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '2', '3'}, n, 0.5f);
		ray_tracer(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == 65364 && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '2', '4'}, n, 0.5f);
		ray_tracer(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == 32 && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '2', '5'}, n, 0.5f);
		ray_tracer(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == 99 && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '2', '6'}, n, 0.5f);
		ray_tracer(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == 120 && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '3', '1'}, n, 0.5f);
		ray_tracer(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == 121 && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '3', '2'}, n, 0.5f);
		ray_tracer(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == 122 && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '3', '3'}, n, 0.5f);
		ray_tracer(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == 101 && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '4', '1'}, n, 0.5f);
		ray_tracer(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == 114 && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '4', '2'}, n, 0.5f);
		ray_tracer(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	return (0);
}

int	close_window(t_data *data)
{
	mlx_destroy_window(data->mlx, data->mlx_win);
	exit(0);
}

void	controls(t_data *data)
{
	mlx_hook(data->mlx_win, 2, 1L<<0, key_press, data);
	mlx_hook(data->mlx_win, 17, 1L<<17, close_window, data);
}
