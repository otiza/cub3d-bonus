/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sprites.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:00:26 by otaouil           #+#    #+#             */
/*   Updated: 2021/03/07 19:11:13 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

extern struct s_all	data;

void	drawspr2(t_spr spr)
{
	double		spr_i;
	double		spr_h;

	spr_h = (data.map.ts / (spr.d * cos(spr.spra))) *
		(data.win.x / 2) / tan(FOV_ANGLE / 2);
	spr.top = (data.win.y / 2) - (spr_h / 2);
	spr.top = (spr.top < 0) ? 0 : spr.top;
	spr.a = atan2(spr.y - data.ply.y, spr.x - data.ply.x) - data.ply.rotang;
	spr_i = (data.win.x / 2) + (tan(spr.a) * ((data.win.x / 2) /
		tan(FOV_ANGLE / 2))) - (spr_h / 2);
	drawtextspr(spr, spr_i - 1, spr.top, spr_h);
}

void	drawspr(void)
{
	int			i;

	i = -1;
	while (++i < data.map.spr)
	{
		if (data.spr[i].v == 1)
			drawspr2(data.spr[i]);
		if(++(data.spr[i].sn) == 4)
			data.spr[i].sn = 0;
	}
}

void	ft_sorder(void)
{
	t_spr		tmp;
	int			i;
	int			j;

	i = 0;
	while (i < data.map.spr - 1)
	{
		j = i + 1;
		while (j < data.map.spr)
		{
			if (data.spr[i].d < data.spr[j].d)
			{
				tmp = data.spr[i];
				data.spr[i] = data.spr[j];
				data.spr[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	sprites(void)
{
	double		spr_ang;
	int			i;

	i = -1;
	ft_slist();
	//HADI ^ B3D MATCONFIGURA 
	while (++i < data.map.spr)
	{
		spr_ang = data.ply.rotang - atan2(data.spr[i].y - data.ply.y,
			data.spr[i].x - data.ply.x);
		if (spr_ang > M_PI)
			spr_ang -= (2 * M_PI);
		else if (spr_ang < -M_PI)
			spr_ang += (2 * M_PI);
		spr_ang = fabs(spr_ang);
		if (spr_ang < (FOV_ANGLE / 2) + 0.2)
		{
			data.spr[i].v = 1;
			data.spr[i].spra = spr_ang;
			data.spr[i].d = distance(data.spr[i].x, data.spr[i].y, data.ply.x,
				data.ply.y);
		}
	}
	ft_sorder();
	drawspr();
}
