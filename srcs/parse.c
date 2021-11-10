/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 18:17:32 by otaouil           #+#    #+#             */
/*   Updated: 2021/03/15 16:08:22 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"

extern struct s_all	data;

int		ft_colors(unsigned int *color, char *line, int *i)
{
	int		r;
	int		g;
	int		b;

	if (*color != NONE)
		return (-5);
	(*i)++;
	ft_spaceskip(line, i);
	r = ft_atoi(line, i);
	if (line[(*i)++] != ',')
		return (-6);
	g = ft_atoi(line, i);
	if (line[(*i)++] != ',')
		return (-6);
	b = ft_atoi(line, i);
	ft_spaceskip(line, i);
	if (line[*i] != '\0' || r > 255 || g > 255 || b > 255)
		return (-6);
	if (line[*i] != '\0' || r < 0 || g < 0 || b < 0)
		return (-6);
	*color = r * 256 * 256 + g * 256 + b;
	return (0);
}

int		ft_line(t_all *s, char *l)
{
	int		i;

	if (!(i = 0) && s->err.m != 1)
		ft_spaceskip(l, &i);
	if ((l[i] == '1' || /*rani f map err.m*/s->err.m == 1) && l[i] != '\0' && !(s->map.spr = 0))
		s->err.n = ft_map(s, l);
	else if (l[i] == 'R' && l[i + 1] == ' ')
		s->err.n = ft_res(s, l, &i);
	else if (l[i] == 'N' && l[i + 1] == 'O' && l[i + 2] == ' ')
		s->err.n = ft_texture(l, &s->tex.s, &i);
	else if (l[i] == 'S' && l[i + 1] == 'O' && l[i + 2] == ' ')
		s->err.n = ft_texture(l, &s->tex.n, &i);
	else if (l[i] == 'W' && l[i + 1] == 'E' && l[i + 2] == ' ')
		s->err.n = ft_texture(l, &s->tex.e, &i);
	else if (l[i] == 'E' && l[i + 1] == 'A' && l[i + 2] == ' ')
		s->err.n = ft_texture(l, &s->tex.w, &i);
	else if (l[i] == 'S' && l[i + 1] == ' ')
		s->err.n = ft_texture(l, &s->tex.i[0], &i);
	else if (l[i] == 'S' && l[i + 1] == '1')
		s->err.n = ft_texture(l, &s->tex.i[1], &i);
	else if (l[i] == 'S' && l[i + 1] == '2')
		s->err.n = ft_texture(l, &s->tex.i[2], &i);
	else if (l[i] == 'S' && l[i + 1] == '3')
		s->err.n = ft_texture(l, &s->tex.i[3], &i);
	else if (l[i] == 'F' && l[i + 1] == ' ')
		s->err.n = ft_colors(&s->tex.f, l, &i);
	else if (l[i] == 'C' && l[i + 1] == ' ')
		s->err.n = ft_colors(&s->tex.c, l, &i);
	if (ft_spaceskip(l, &i) && s->err.n == 0 && l[i] != '\0')
		return (ft_strerror(-10));
	return (ft_line2(s, l));
}

void	ft_pos(t_all *s)
{
	char	c;
	int		i;
	int		j;

	i = -1;
	j = -1;
	s->map.ts = 50;
	while (++i < s->map.y && (j = -1))
		while (++j < s->map.x)
		{
			c = s->map.tab[i][j];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				s->ply.y = (double)(i * s->map.ts) + 0.5;
				s->ply.x = (double)(j * s->map.ts) + 0.5;
				if (c == 'E' || c == 'W')
					s->ply.rotang = (c == 'E') ? 0 : M_PI;
				else
					s->ply.rotang = (c == 'S') ? M_PI / 2 : 3 * M_PI / 2;
				s->err.p++;
			}
		}
}

int		config(t_all *s, char *cub)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	fd = open(cub, O_RDONLY);
	if (fd == -1)
		return (ft_strerror(-1));
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);
		if (ft_line(s, line) == -1)
			ret = -1;
		free(line);
	}
	close(fd);
	if (ret == -1 || ret == -3)
		return (ft_strerror(ret + 1));
	ft_pos(s);
	s->num_rays = s->win.x;
	fd = -1;
	return (ft_parcheck(s));
}
