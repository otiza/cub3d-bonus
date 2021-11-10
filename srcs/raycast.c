/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:23:51 by otaouil           #+#    #+#             */
/*   Updated: 2021/03/07 19:11:45 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

extern struct s_all	data;

void	casthorz(t_ray *rayss)
{
	double		x1;
	double		y1;
	double		xstp;
	double		ystp;

	y1 = floor(data.ply.y / data.map.ts) * data.map.ts;
	y1 += (rayss->isfacd) ? data.map.ts : 0;
	x1 = data.ply.x + (y1 - data.ply.y) / tan(rayss->ryang);
	ystp = data.map.ts;
	ystp *= !rayss->isfacd ? -1 : 1;
	xstp = data.map.ts / tan(rayss->ryang);
	xstp *= !rayss->isfacr && xstp > 0 ? -1 : 1;
	xstp *= rayss->isfacr && xstp < 0 ? -1 : 1;
	while (x1 >= 0 && x1 <= data.map.x * data.map.ts
		&& y1 >= 0 && y1 <= data.map.y * data.map.ts)
		if (haswallat(x1, y1 + (!rayss->isfacd ? -1 : 0)))
			break ;
		else
		{
			x1 += xstp;
			y1 += ystp;
		}
	rayss->wllhtx = x1;
	rayss->wllhty = y1;
}

void	castvert(double *x, double *y, t_ray *rayss)
{
	double		xstp;
	double		ystp;

	*x = floor(data.ply.x / data.map.ts) * data.map.ts;
	*x += (rayss->isfacr) ? data.map.ts : 0;
	*y = data.ply.y + (*x - data.ply.x) * tan(rayss->ryang);
	xstp = data.map.ts;
	xstp *= (!rayss->isfacr) ? -1 : 1;
	ystp = data.map.ts * tan(rayss->ryang);
	ystp *= !rayss->isfacd && ystp > 0 ? -1 : 1;
	ystp *= rayss->isfacd && ystp < 0 ? -1 : 1;
	while (*x >= 0 && *x <= data.map.x * data.map.ts
		&& *y >= 0 && *y <= data.map.y * data.map.ts)
		if (haswallat(*x - (!rayss->isfacr ? 1 : 0), *y))
			break ;
		else
		{
			*x += xstp;
			*y += ystp;
		}
}

void	cast(t_ray *rays)
{
	double		x;
	double		y;

	casthorz(rays);
	castvert(&x, &y, rays);
	if (distance(data.ply.x, data.ply.y, x, y) <
		distance(data.ply.x, data.ply.y, rays->wllhtx, rays->wllhty) && y > 0)
	{
		rays->wllhtx = x;
		rays->wllhty = y;
		rays->washitv = 1;
	}
	rays->dst = distance(data.ply.x, data.ply.y, rays->wllhtx, rays->wllhty);
}

void	castallrays(void)
{
	int			i;
	double		rayangle;

	i = -1;
	if (data.rays != NULL)
		free(data.rays);
	if (!(data.rays = malloc(sizeof(t_ray) * (data.num_rays + 1))))
		return ;
	rayangle = data.ply.rotang - (FOV_ANGLE / 2);
	while (++i < data.num_rays)
	{
		ray_config(&data.rays[i], rayangle);
		cast(&data.rays[i]);
		rayangle += FOV_ANGLE / data.num_rays;
	}
}
