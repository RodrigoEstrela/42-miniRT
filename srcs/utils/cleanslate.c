#include "../../inc/minirt.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*ptr;

	ptr = b;
	while (len-- > 0)
		*ptr++ = c;
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

void	clean_slate(t_data *g)
{
	ft_bzero(g->img.addr, WIND_H * WIND_W * (g->img.bi_per_pxl / 8));
}

int	checkcode(char *line, t_data *data)
{
	if (ft_strncmp(line, "sp", 3) == 0)
		return 1;
	else if (ft_strncmp(line, "pl", 3) == 0)
		return 2;
	else if (ft_strncmp(line, "cy", 3) == 0)
		return 3;
	else if (ft_strncmp(line, "l", 2) == 0)
		return 4;
	else if (ft_strncmp(line, "c", 2) == 0)
		return 5;
	else
		return -1;
}

t_vector	rotater(t_vector v, char e, float sign)
{
	t_vector	r;
	float		ang;

	ang = 0.5f;
	if (e == 'x')
	{
		r.x = v.x;
		r.y = v.y * cos(ang * sign) - v.z * sin(ang * sign);
		r.z = v.y * sin(ang * sign) + v.z * cos(ang * sign);
	}
	else if (e == 'y')
	{
		r.x = v.x * cos(ang * sign) + v.z * sin(ang * sign);
		r.y = v.y;
		r.z = -v.x * sin(ang * sign) + v.z * cos(ang * sign);
	}
	else if (e == 'z')
	{
		r.x = v.x * cos(ang * sign) - v.y * sin(ang * sign);
		r.y = v.x * sin(ang * sign) + v.y * cos(ang * sign);
		r.z = v.z;
	}
	return (r);
}

void transform(t_data *data, char code[3], int n, float value)
{
	if (code[0] == '1') // esferas
	{
		if (code[1] == '1') // diametro
		{
			if (code[2] == '1')
				data->scene->spheres[n].diameter += value;
			else if (code[2] == '2' && data->scene->spheres[n].diameter > 0)
				data->scene->spheres[n].diameter -= value;
		}
		else if (code[1] == '2') // centro
		{
			if (code[2] == '1')
				data->scene->spheres[n].center.x += value;
			else if (code[2] == '2')
				data->scene->spheres[n].center.x -= value;
			else if (code[2] == '3')
				data->scene->spheres[n].center.z += value;
			else if (code[2] == '4')
				data->scene->spheres[n].center.z -= value;
			else if (code[2] == '5')
				data->scene->spheres[n].center.y += value;
			else if (code[2] == '6')
				data->scene->spheres[n].center.y -= value;
		}
	}
	else if (code[0] == '2') // planos
	{
		if (code[1] == '2')
		{
			if (code[2] == '1')
				data->scene->planes[n].point.x += value;
			else if (code[2] == '2')
				data->scene->planes[n].point.x -= value;
			else if (code[2] == '3')
				data->scene->planes[n].point.z += value;
			else if (code[2] == '4')
				data->scene->planes[n].point.z -= value;
			else if (code[2] == '5')
				data->scene->planes[n].point.y += value;
			else if (code[2] == '6')
				data->scene->planes[n].point.y -= value;
		}
		else if (code[1] == '3')
		{
			if (code[2] == '1')
				data->scene->planes[n].normal = rotater(data->scene->planes[n].normal, 'x', 1);
			else if (code[2] == '2')
				data->scene->planes[n].normal = rotater(data->scene->planes[n].normal, 'y', 1);
			else if (code[2] == '3')
				data->scene->planes[n].normal = rotater(data->scene->planes[n].normal, 'z', 1);
			else if (code[2] == '4')
				data->scene->planes[n].normal = rotater(data->scene->planes[n].normal, 'x', -1);
			else if (code[2] == '5')
				data->scene->planes[n].normal = rotater(data->scene->planes[n].normal, 'y', -1);
			else if (code[2] == '6')
				data->scene->planes[n].normal = rotater(data->scene->planes[n].normal, 'z', -1);
			normalize_vector(&data->scene->planes[n].normal);
		}
	}
	else if (code[0] == '3') // cilindros
	{
		if (code[1] == '1') // diametro
		{
			if (code[2] == '1')
				data->scene->cylinders[n].diameter += value;
			else if (code[2] == '2' && data->scene->cylinders[n].diameter > 0)
				data->scene->cylinders[n].diameter -= value;
		}
		else if (code[1] == '2') // center
		{
			if (code[2] == '1')
				data->scene->cylinders[n].base_center.x += value;
			else if (code[2] == '2')
				data->scene->cylinders[n].base_center.x -= value;
			else if (code[2] == '3')
				data->scene->cylinders[n].base_center.z += value;
			else if (code[2] == '4')
				data->scene->cylinders[n].base_center.z -= value;
			else if (code[2] == '5')
				data->scene->cylinders[n].base_center.y += value;
			else if (code[2] == '6')
				data->scene->cylinders[n].base_center.y -= value;
		}
		else if (code[1] == '3') // rotation
		{
			if (code[2] == '1')
				data->scene->cylinders[n].normal = rotater(data->scene->cylinders[n].normal, 'x', 1);
			else if (code[2] == '2')
				data->scene->cylinders[n].normal = rotater(data->scene->cylinders[n].normal, 'y', 1);
			else if (code[2] == '3')
				data->scene->cylinders[n].normal = rotater(data->scene->cylinders[n].normal, 'z', 1);
			else if (code[2] == '4')
				data->scene->cylinders[n].normal = rotater(data->scene->cylinders[n].normal, 'x', -1);
			else if (code[2] == '5')
				data->scene->cylinders[n].normal = rotater(data->scene->cylinders[n].normal, 'y', -1);
			else if (code[2] == '6')
				data->scene->cylinders[n].normal = rotater(data->scene->cylinders[n].normal, 'z', -1);
			normalize_vector(&data->scene->cylinders[n].normal);
		}
		else if (code[1] == '4') // height
		{
			if (code[2] == '1')
				data->scene->cylinders[n].height += value;
			else if (code[2] == '2' && data->scene->cylinders[n].height > 0)
				data->scene->cylinders[n].height -= value;
		}
	}
	else if (code[0] == '4') // luzes
	{
		if (code[1] == '2')
		{
			if (code[2] == '1')
				data->scene->lights[n].origin.x += value;
			else if (code[2] == '2')
				data->scene->lights[n].origin.x -= value;
			else if (code[2] == '3')
				data->scene->lights[n].origin.z += value;
			else if (code[2] == '4')
				data->scene->lights[n].origin.z -= value;
			else if (code[2] == '5')
				data->scene->lights[n].origin.y += value;
			else if (code[2] == '6')
				data->scene->lights[n].origin.y -= value;
		}
	}
	else if (code[0] == '5') // câmeras
	{
		if (code[1] == '2') // center
		{
			if (code[2] == '1')
				data->scene->cameras[n].origin.x += value;
			else if (code[2] == '2')
				data->scene->cameras[n].origin.x -= value;
			else if (code[2] == '3')
				data->scene->cameras[n].origin.z += value;
			else if (code[2] == '4')
				data->scene->cameras[n].origin.z -= value;
			else if (code[2] == '5')
				data->scene->cameras[n].origin.y += value;
			else if (code[2] == '6')
				data->scene->cameras[n].origin.y -= value;
		}
		else if (code[1] == '3') // rotation
		{
			if (code[2] == '1')
				data->scene->cameras[n].normal = rotater(data->scene->cameras[n].normal, 'x', 1);
			else if (code[2] == '2')
				data->scene->cameras[n].normal = rotater(data->scene->cameras[n].normal, 'y', 1);
			else if (code[2] == '3')
				data->scene->cameras[n].normal = rotater(data->scene->cameras[n].normal, 'z', 1);
			else if (code[2] == '4')
				data->scene->cameras[n].normal = rotater(data->scene->cameras[n].normal, 'x', -1);
			else if (code[2] == '5')
				data->scene->cameras[n].normal = rotater(data->scene->cameras[n].normal, 'y', -1);
			else if (code[2] == '6')
				data->scene->cameras[n].normal = rotater(data->scene->cameras[n].normal, 'z', -1);
			normalize_vector(&data->scene->cameras[n].normal);
			data->scene->cameras[n].view_matrix = set_camera_to_world_transformation_matrix(data->scene->cameras[n], (t_vector){0, 1, 0});
		}
		else if (code[1] == '4')
		{
			if (code[2] == '1' && data->scene->cameras[n].fov < 140.0f)
				data->scene->cameras[n].fov += 10;
			else if (code[2] == '2' && data->scene->cameras[n].fov > 10.0f)
				data->scene->cameras[n].fov -= 10;
		}
	}
}
