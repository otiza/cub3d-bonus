/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:28:26 by otaouil           #+#    #+#             */
/*   Updated: 2021/03/15 11:56:35 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

extern struct s_all	data;

void	drawline(int x0, int y0, int y1, int i)
{
	int		dx;
	int		dy;
	int		steps;
	int		j;

	dx = x0 - x0;
	dy = y1 - y0;
	steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	j = -1;
	dx = dx / (float)steps;
	dy = dy / (float)steps;
	while (++j <= steps)
	{
		my_mlx_pixel_put(x0, y0, i);
		x0 += dx;
		y0 += dy;
	}
}

int		colorval(t_ray *r, int y, int s)
{
	int				color;

	color = 0;
	if (r->isfacd && r->isfacr && (y * 64) + s > 0)
		color = (!r->washitv) ? data.tex.s[(y * 64) + s] :
			data.tex.e[(y * 64) + s];
	else if (r->isfacd && !r->isfacr && (y * 64) + s > 0)
		color = (!r->washitv) ? data.tex.s[(y * 64) + s] :
			data.tex.w[(y * 64) + s];
	else if (!r->isfacd && r->isfacr && (y * 64) + s > 0)
		color = (!r->washitv) ? data.tex.n[(y * 64) + s] :
			data.tex.e[(y * 64) + s];
	else if ((y * 64) + s > 0)
		color = (!r->washitv) ? data.tex.n[(y * 64) + s] :
			data.tex.w[(y * 64) + s];
	return (color);
}

void	drawwall(int d, int i, int x, t_ray *r)
{
	int				j;
	int				s;
	int				y;
	unsigned int	v;

	s = fmod((!r->washitv) ? r->wllhtx : r->wllhty, 64);
	v = 0;
	j = x - 1;
	while (++j < (data.win.y / 2) + (d / 2) && j < data.win.y)
	{
		y = j + (d / 2) - (data.win.y / 2);
		y = y * ((double)64 / d);
		v = colorval(r, y, s);
		my_mlx_pixel_put(i, j, v);
	}
}

void	render3d(void)
{
	float		d;
	float		w;
	int			wt;
	int			i;

	i = -1;
	while (++i < data.num_rays)
	{
		w = data.rays[i].dst * cos(data.rays[i].ryang - data.ply.rotang);
		d = (data.win.x / 2) / tan(FOV_ANGLE / 2);
		w = (data.map.ts / w) * d;
		wt = (data.win.y / 2) - (w / 2);
		drawline(i, 0, (wt < 0 ? 0 : wt), data.tex.c);
		drawwall(w, i, (wt < 0 ? 0 : wt), &data.rays[i]);
		if ((wt + w) < data.win.y)
			drawline(i, wt + w, data.win.y - 1, data.tex.f);
	}
}

double	distance(double x1, double y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}
