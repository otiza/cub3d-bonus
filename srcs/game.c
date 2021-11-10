/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 17:37:38 by otaouil           #+#    #+#             */
/*   Updated: 2021/03/07 19:13:21 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

extern struct s_all	data;

int		ft_texture(char *line, unsigned int **adr, int *i)
{
	char		*file;
	int			j;

	(*i) += 2;
	ft_spaceskip(line, i);
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	if (!(file = malloc(sizeof(char) * (*i - j + 1))))
		return (-8);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		file[j++] = line[(*i)++];
	file[j] = '\0';
	if (*adr != NULL)
		return (-7);
	j = ft_xppm(adr, file);
	free(file);
	return (j == -1 ? -9 : 0);
}

double	ft_normalizeangle(double angle)
{
	angle = fmod(angle, 2 * M_PI);
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

void	ray_config(t_ray *r, double rayangle)
{
	r->ryang = ft_normalizeangle(rayangle);
	r->isfacd = (r->ryang > 0 && r->ryang < M_PI);
	r->isfacr = (r->ryang > 1.5 * M_PI || r->ryang < 0.5 * M_PI);
	r->washitv = 0;
}

void	plyupdate(void)
{
	double		movestep;
	double		x;
	double		y;
	double		z;

	data.ply.rotang += data.ply.trndir * TURN;
	data.ply.rotang = ft_normalizeangle(data.ply.rotang);
	movestep = data.ply.wlkdir * SPEED;
	x = data.ply.x + cos(data.ply.rotang) * movestep;
	y = data.ply.y + sin(data.ply.rotang) * movestep;
	movestep = data.ply.wlkdir2 * SPEED;
	z = data.ply.rotang + fabs(data.ply.wlkdir2 * M_PI / 2);
	x += cos(z) * movestep;
	y += sin(z) * movestep;
	if (!haswallat(x, y) &&
		data.map.tab[(int)y / data.map.ts][(int)x / data.map.ts] != '2')
	{
		data.ply.x = x;
		data.ply.y = y;
	}
	castallrays();
}
