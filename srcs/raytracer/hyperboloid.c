#include "../../inc/minirt.h"

#include "../../inc/minirt.h"

t_vector rotate_vector(t_vector v, float angles[3], t_vector center)
{
	t_vector rotated;
	// Rotate around X axis
	rotated.x = v.x;
	rotated.y = v.y * cos(angles[0]) - v.z * sin(angles[0]);
	rotated.z = v.y * sin(angles[0]) + v.z * cos(angles[0]);
	// Rotate around Y axis
	float x = rotated.x * cos(angles[1]) + rotated.z * sin(angles[1]);
	float z = -rotated.x * sin(angles[1]) + rotated.z * cos(angles[1]);
	rotated.x = x;
	rotated.z = z;
	// Rotate around Z axis
	x = rotated.x * cos(angles[2]) - rotated.y * sin(angles[2]);
	float y = rotated.x * sin(angles[2]) + rotated.y * cos(angles[2]);
	rotated.x = x;
	rotated.y = y;
	return rotated;
}

float intersection_hyperboloid(t_hiperb h, t_ray ray)
{
	t_vector ro = vector_add(rotate_vector(ray.origin, h.rotation_angles, h.center),
							 rotate_vector(h.center, (float[3]){h.rotation_angles[0],
																  h.rotation_angles[1],
																  h.rotation_angles[2] * -1}, h.center));
//	t_vector ro = rotate_vector(ray.origin, h.rotation_angles);
	t_vector rd = rotate_vector(ray.direction, h.rotation_angles, h.center);
	t_vector o = ro;
	t_vector d = rd;
	float a = h.parameters[0], b = h.parameters[1], c = h.parameters[2];
	float A = (d.x * d.x) / (a * a) + (d.y * d.y) / (b * b) - (d.z * d.z) / (c * c);
	float B = (2 * o.x * d.x) / (a * a) + (2 * o.y * d.y) / (b * b) - (2 * o.z * d.z) / (c * c);
	float C = (o.x * o.x) / (a * a) + (o.y * o.y) / (b * b) - (o.z * o.z) / (c * c) - 1;
	float discriminant = B * B - 4 * A * C;
	if (discriminant < 0)
		return 0;
	float t1 = (-B + sqrt(discriminant)) / (2 * A);
	float t2 = (-B - sqrt(discriminant)) / (2 * A);
	if (t1 < 0 && t2 < 0)
		return 0;
	float ret =  (t1 < 0 || t2 < t1) ? t2 : t1;
	t_vector point = vector_add(o, vector_scale(d, ret));
	if (point.z < -h.height/2 || point.z > h.height/2)
		return 0;
	return ret;
}

t_vector normal_hyperboloid(t_hiperb h, t_vector point)
{
	t_vector normal;
	normal.x = 2 * point.x / (h.parameters[0] * h.parameters[0]);
	normal.y = 2 * point.y / (h.parameters[1] * h.parameters[1]);
	normal.z = -2 * point.z / (h.parameters[2] * h.parameters[2]);
	normal = rotate_vector(normal, h.rotation_angles, h.center);
	normalize_vector(&normal);
	return normal;
}

