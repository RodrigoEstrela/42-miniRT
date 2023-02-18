#include "../../inc/minirt.h"

int	key_press(int key, t_data *data)
{
	char		*cmd;
	char		**obj_code;
	static char	code[3];
	static int	n;

	if (key == key_ESC)
		exit(0);
	else if (key == key_TAB)
	{
		printf("EDITOR MODE\n");
		printf("Press enter to exit editor mode or\n");
		printf("Enter the object code and the object number:\n");
		cmd = get_next_line(0);
		obj_code = ft_split(cmd, ' ');
		code[0] = ft_itoa(checkcode(obj_code[0], data))[0];
		n = ft_atoi(obj_code[1]);
		free(cmd);
		free(obj_code[0]);
		free(obj_code[1]);
		free(obj_code);
	}
	else if (key == key_ENTER)
		n = -1;
	else if (key == key_D && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '1', '1'}, n, 0.5f);
		thread_master(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == key_F && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '1', '2'}, n, 0.5f);
		thread_master(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == key_LEFT && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '2', '1'}, n, 0.5f);
		thread_master(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == key_RIGHT && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '2', '2'}, n, 0.5f);
		thread_master(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == key_UP && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '2', '3'}, n, 0.5f);
		thread_master(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == key_DOWN && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '2', '4'}, n, 0.5f);
		thread_master(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == key_SPACE && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '2', '5'}, n, 0.5f);
		thread_master(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == key_C && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '2', '6'}, n, 0.5f);
		thread_master(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == key_X && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '3', '1'}, n, 0.5f);
		thread_master(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == key_Y && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '3', '2'}, n, 0.5f);
		thread_master(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == key_Z && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '3', '3'}, n, 0.5f);
		thread_master(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == key_H && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '3', '4'}, n, 0.5f);
		thread_master(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == key_J && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '3', '5'}, n, 0.5f);
		thread_master(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == key_K && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '3', '6'}, n, 0.5f);
		thread_master(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == key_E && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '4', '1'}, n, 0.5f);
		thread_master(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if (key == key_R && n > -1)
	{
		clean_slate(data);
		transform(data, (char [3]){code[0], '4', '2'}, n, 0.5f);
		thread_master(data);
		mlx_put_image_to_window(data->mlx, data->mlx_win, data->img.img, 0, 0);
	}
	else if  (key == key_V && n > -1)
	{
		clean_slate(data);
		if (data->camera_index < data->nb_objs->nb_cameras - 1)
			data->camera_index += 1;
		else
			data->camera_index = 0;
		thread_master(data);
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
