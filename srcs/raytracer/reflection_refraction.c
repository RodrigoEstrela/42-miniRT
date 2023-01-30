#include "../../inc/minirt.h"

t_vector	calc_reflected_ray(t_vector ray, t_vector normal)
{
	t_vector	reflected_ray;

	reflected_ray = vector_sub(ray, vector_scale(normal, 2 * dot_product(ray, normal)));
	return (reflected_ray);
}

t_hit_obj get_reflected_color(t_data *data, t_ray reflect_ray, t_hit_obj hit)
{
	t_hit_obj	reflect_hit;

	reflect_hit = get_closest_intersection(data, reflect_ray);
	if (reflect_hit.t_min < 4535320)
		reflect_hit.color = shading(reflect_hit, reflect_ray, data);
	else
		reflect_hit.color = hit.color;
	return (reflect_hit);
}

float get_random_number(float min, float max)
{
	float random = (float)rand() / (float)RAND_MAX;
	float diff = max - min;
	float r = random * diff;
	return (min + r);
}

void	vector_rand(t_vector *reflect_dir, float randomness)
{
	reflect_dir->x += get_random_number(0, randomness);
	reflect_dir->y += get_random_number(0, randomness);
	reflect_dir->z += get_random_number(0, randomness);
}

int blend_colors(int color1, int color2, float ratio)
{
	if (ratio > 1)
		ratio = 1;
	if (ratio < 0)
		ratio = 0;
	int r = (int)((float)((color1 >> 16) & 0xFF) * ratio + (float)((color2 >> 16) & 0xFF) * (1 - ratio));
	int g = (int)((float)((color1 >> 8) & 0xFF) * ratio + (float)((color2 >> 8) & 0xFF) * (1 - ratio));
	int b = (int)((float)((color1) & 0xFF) * ratio + (float)((color2) & 0xFF) * (1 - ratio));
	return (r << 16 | g << 8 | b);
}

float	fresnel(t_vector incident_dir, t_vector normal, float material_light_absortion)
{
	float	r0 = pow((1.0f - MATERIAL_REFRACTION) / (1.0f + MATERIAL_REFRACTION), 2);
	float	cos_theta = -dot_product(normal, incident_dir);
	float 	x = 1.0f - cos_theta;
	float 	ret = r0 + (1.0f - r0) * pow(x, 5);
	ret = material_light_absortion + (1.0f - material_light_absortion) * ret;
	return (ret);
}

int reflection_refraction(t_data *data, t_ray ray, t_hit_obj hit, int depth, float light_intensity)
{
	t_ray		reflected_ray;
	t_hit_obj 	reflected_hit;
	float		fresnel_ratio;

	reflected_ray.direction = calc_reflected_ray(ray.direction, hit.normal);
//	vector_rand(&reflected_ray, 0.1f);
	normalize_vector(&reflected_ray.direction);
	fresnel_ratio = fresnel(ray.direction, hit.normal, hit.light_absorb_ratio);
	reflected_ray.origin = hit.hit_point;
	reflected_hit = get_reflected_color(data, reflected_ray, hit);
	reflected_hit.color = blend_colors(hit.color, reflected_hit.color, fresnel_ratio/*hit.light_absorb_ratio *//*+ (1 - light_intensity)*/);
	reflected_hit.color = blend_colors(reflected_hit.color, hit.color, light_intensity);
	light_intensity = light_intensity - hit.light_absorb_ratio;
	if (depth > 1 && light_intensity > 0.01f)
		return (reflection_refraction(data, reflected_ray, reflected_hit, depth - 1, light_intensity));
	return (reflected_hit.color);
}
