
#include "../../inc/minirt.h"

t_vector	transform_vector(t_vector v, float **matrix)
{
	t_vector	result;

	result.x = v.x * matrix[0][0] + v.y * matrix[1][0] + v.z * matrix[2][0];
	result.y = v.x * matrix[0][1] + v.y * matrix[1][1] + v.z * matrix[2][1];
	result.z = v.x * matrix[0][2] + v.y * matrix[1][2] + v.z * matrix[2][2];
	return (result);
}

float	deg_to_rad(float degrees)
{
	return (degrees * M_PI / 180.00f);
}

t_ray	get_ray(t_data *data, int x, int y)
{
	float		aspect_ratio;
	t_vector	camera;
	t_ray		ray;

	aspect_ratio = WIND_W / WIND_H;
	camera.x = -(2 * (x + 0.5) / WIND_W - 1) * aspect_ratio * tan(deg_to_rad(FOV) / 2);
	camera.y = (1 - 2 * (y + 0.5) / WIND_H) * tan(deg_to_rad(FOV) / 2);
	camera.z = 1;
	normalize_vector(&camera);
	ray.origin = data->scene->cameras[0].origin;
	ray.direction = transform_vector(camera, data->scene->cameras[0].view_matrix);
	normalize_vector(&ray.direction);
	return (ray);
}

void	*ray_tracer(void *tdata)
{
	t_ray ray;
	int x;
	int y;
	int x_max;
	int y_max;
	int color;
	t_hit_obj	hit;

	x = ((t_thread_data *)tdata)->x;
	y = ((t_thread_data *)tdata)->y;
	x_max = ((t_thread_data *)tdata)->x_max;
	y_max = ((t_thread_data *)tdata)->y_max;
	while (x < x_max)
	{
//		render_progress_bar(x);
		while (y < y_max)
		{
			ray = get_ray(((t_thread_data *)tdata)->data, x, y);
			hit = get_closest_intersection(((t_thread_data *)tdata)->data, ray);
			if (hit.t_min < 4535320)
			{
				hit.color = reflection_refraction(((t_thread_data *)tdata)->data, ray, hit, REFLECTION_DEPTH, 1.0f);
				color = shading(hit, ray, ((t_thread_data *)tdata)->data);
				color = blend_colors(color, hit.color, hit.light_absorb_ratio);
//				color = hit.color;
			}
			else
				color = background_color(y, BACKGROUND1, BACKGROUND2);
			put_pxl(&(((t_thread_data *)tdata)->data)->img, x, y, color);
			y++;
		}
		y = 0;
		x++;
	}
	return (0);
//	printf("\rProgress: 100%% | \n");
}

void thread_master(t_data *data)
{
	int i = -1;
	pthread_t thread_data[16];
	// LINHA DE CIMA
	pthread_create(&thread_data[0], 0, ray_tracer,
				   (t_thread_data [5]){data, 0, 0, WIND_W * 0.25f, WIND_H * 0.25f});
	pthread_create(&thread_data[1], 0, ray_tracer,
				   (t_thread_data [5]){data, WIND_W * 0.25f, 0, WIND_W * 0.5f, WIND_H * 0.25f});
	pthread_create(&thread_data[2], 0, ray_tracer,
				   (t_thread_data [5]){data, WIND_W * 0.5f, 0, WIND_W * 0.75f, WIND_H * 0.25f});
	pthread_create(&thread_data[3], 0, ray_tracer,
				   (t_thread_data [5]){data, WIND_W * 0.75f, 0, WIND_W, WIND_H * 0.25f});
	// SEGUNDA LINHA
	pthread_create(&thread_data[4], 0, ray_tracer,
				   (t_thread_data [5]){data, 0, WIND_H * 0.25f, WIND_W * 0.25f, WIND_H * 0.5f});
	pthread_create(&thread_data[5], 0, ray_tracer,
				   (t_thread_data [5]){data, WIND_W * 0.25f, WIND_H * 0.25f, WIND_W * 0.5f, WIND_H * 0.5f});
	pthread_create(&thread_data[6], 0, ray_tracer,
				   (t_thread_data [5]){data, WIND_W * 0.5f, WIND_H * 0.25f, WIND_W * 0.75f, WIND_H * 0.5f});
	pthread_create(&thread_data[7], 0, ray_tracer,
				   (t_thread_data [5]){data, WIND_W * 0.75f, WIND_H * 0.25f, WIND_W, WIND_H * 0.5f});
	// TERCEIRA LINHA
	pthread_create(&thread_data[8], 0, ray_tracer,
				   (t_thread_data [5]){data, 0, WIND_H * 0.5f, WIND_W * 0.25f, WIND_H * 0.75f});
	pthread_create(&thread_data[9], 0, ray_tracer,
				   (t_thread_data [5]){data, WIND_W * 0.25f, WIND_H * 0.5f, WIND_W * 0.5f, WIND_H * 0.75f});
	pthread_create(&thread_data[10], 0, ray_tracer,
				   (t_thread_data [5]){data, WIND_W * 0.5f, WIND_H * 0.5f, WIND_W * 0.75f, WIND_H * 0.75f});
	pthread_create(&thread_data[11], 0, ray_tracer,
				   (t_thread_data [5]){data, WIND_W * 0.75f, WIND_H * 0.5f, WIND_W, WIND_H * 0.75f});
	// LINHA DE BAIXO
	pthread_create(&thread_data[12], 0, ray_tracer,
				   (t_thread_data [5]){data, 0, WIND_H * 0.75f, WIND_W * 0.25f, WIND_H});
	pthread_create(&thread_data[13], 0, ray_tracer,
				   (t_thread_data [5]){data, WIND_W * 0.25f, WIND_H * 0.75f, WIND_W * 0.5f, WIND_H});
	pthread_create(&thread_data[14], 0, ray_tracer,
				   (t_thread_data [5]){data, WIND_W * 0.5f, WIND_H * 0.75f, WIND_W * 0.75f, WIND_H});
	pthread_create(&thread_data[15], 0, ray_tracer,
				   (t_thread_data [5]){data, WIND_W * 0.75f, WIND_H * 0.75f, WIND_W, WIND_H});
	while (++i < 16)
		pthread_join(thread_data[i], 0);
}
