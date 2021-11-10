/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:04:47 by otaouil           #+#    #+#             */
/*   Updated: 2021/03/16 15:19:25 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

extern struct s_all	data;

int		haswallat(double x, double y)
{
	int			xx;
	int			yy;

	xx = floor(x / data.map.ts);
	yy = floor(y / data.map.ts);
	if (xx <= 0 || xx >= data.map.x || yy <= 0 || yy >= data.map.y)
		return (1);
	return (data.map.tab[yy][xx] == '1' || data.map.tab[yy][xx] == '\0');
}

int		ft_slist(void)
{
	int			i;
	int			j;
	int			k;

	if (data.spr != NULL)
		free(data.spr);
	if (!(data.spr = malloc(sizeof(t_spr) * data.map.spr)))
		return (-1);
	i = 0;
	j = -1;
	while (++j < data.map.y)
	{
		k = -1;
		while (++k < data.map.x)
		{
			if (data.map.tab[j][k] == '2')
			{
				data.spr[i].y = (double)(j + 0.5) * data.map.ts;
				data.spr[i].x = (double)(k + 0.5) * data.map.ts;
				data.spr[i].sn = 0;
				data.spr[i++].v = 0;
			}
		}
	}
	return (1);
}

void	drawtextspr(t_spr spr, int i, int top, double h)
{
	int			j;
	double		x;
	int			bot;
	double		y;

	bot = (data.win.y / 2) + (h / 2);
	bot = (bot > data.win.y) ? data.win.y : bot;
	y = i + h;
	i = i < 0 ? -1 : i;
	while (++i < y && i < data.win.x)
	{
		j = (i - (y - h)) * (64 / h);
		top = spr.top - 1;
		while (++top < bot && top < data.win.y)
		{
			x = top + (h / 2) - (data.win.y / 2);
			x = x * (64 / h);
			if (spr.d < data.rays[i].dst && x >= 0 &&
				data.tex.i[((int)x * 64) + j] != BLACK)
				my_mlx_pixel_put(i, top, data.tex.i[spr.sn][((int)x * 64) + j]);
		}
	}
}

int		ft_line2(t_all *s, char *line)
{
	int			i;

	i = 0;
	if (line[i] == '\0' && s->err.m == 1)
		return (ft_strerror(-12));
	return (s->err.n < 0 ? ft_strerror(s->err.n) : 0);
}
