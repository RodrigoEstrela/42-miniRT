/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fde-albe <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 10:05:30 by fde-albe          #+#    #+#             */
/*   Updated: 2023/03/01 12:17:33 by fde-albe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minirt.h"

void	check_hit_planes(t_data *data, t_ray ray, t_hit_obj *hit)
{
	int			i;
	float		t;

	i = -1;
	while (++i < data->nb_objs->nb_planes)
	{
		t = intersect_ray_plane(ray, data->scene->planes[i]);
		if (t)
		{
			if (t < hit->t_min)
			{
				hit->t_min = t;
				hit->closest_plane = i;
				hit->closest_sphere = -1;
			}
		}
	}
}

float	intersect_ray_plane(t_ray ray, t_plane plane)
{
	float		t;
	float		denom;
	t_vector	p0l0;

	denom = dot_product(plane.normal, ray.direction);
	if (fabsf(denom) > 0.0001f)
	{
		p0l0 = vector_from_points(ray.origin, plane.point);
		t = dot_product(p0l0, plane.normal) / denom;
		if (t > 0.0001f)
			return (t);
	}
	return (0);
}
