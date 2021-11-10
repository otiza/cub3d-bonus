/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: otaouil <otaouil@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 02:13:36 by otaouil           #+#    #+#             */
/*   Updated: 2021/03/15 11:42:17 by otaouil          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "../minilibx_opengl/mlx.h"
# include "../inc/get_next_line.h"

# define NONE 0xFF000000
# define WHITE 0x00FFFFFF
# define BLACK 0x00000000
# define RED 0x00FF0000
# define GREEN 0x0000FF00
# define BLUE 0x000000FF
# define MAGENTA 0x00FF00FF
# define YELLOW 0x00FFFF00
# define CYAN 0x0000FFFF

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define UP 126
# define DOWN 125
# define LEFT 123
# define RIGHT 124

# define SPEED 4
# define TURN 0.05
# define MSF 0.1

# define FOV_ANGLE  1.04719755

typedef struct	s_mlx
{
	void			*ptr;
}				t_mlx;

typedef struct	s_win
{
	void			*ptr;
	int				x;
	int				y;
}				t_win;

typedef struct	s_err
{
	int				n;
	int				m;
	int				l;
	int				p;
}				t_err;

typedef struct	s_img
{
	void			*ptr;
	char			*adr;
	int				n;
	int				fsh;
	int				m;
}				t_img;

typedef struct	s_map
{
	char			**tab;
	int				x;
	int				y;
	int				ts;
	int				spr;
}				t_map;

typedef struct	s_ply
{
	double			x;
	double			y;
	int				rds;
	int				trndir;
	int				wlkdir;
	int				wlkdir2;
	double			rotang;
}				t_ply;

typedef struct	s_ray
{
	double			ryang;
	double			wllhtx;
	double			wllhty;
	double			dst;
	int				washitv;
	int				isfacd;
	int				isfacr;
}				t_ray;

typedef struct	s_tex
{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;
	unsigned int	*h;
	unsigned int	*w;
	unsigned int	**i;
	unsigned int	c;
	unsigned int	f;
}				t_tex;

typedef struct	s_spr
{
	double			x;
	double			y;
	double			a;
	double			spra;
	double			top;
	int				v;
	int				sn;
	
	double			d;
}				t_spr;

typedef struct	s_all
{
	t_mlx			mlx;
	t_win			win;
	t_map			map;
	t_err			err;
	t_ply			ply;
	t_tex			tex;
	t_img			img;
	int				num_rays;
	t_spr			*spr;
	t_ray			*rays;
}				t_all;

int				ft_namecheck(char *arg, char *ext);
int				ft_strcheck(char *arg, char *str);
int				ft_unpress(int key, void *param);
int				ft_press(int key, void *param);
int				ft_dynamic(void);
void			ft_draw(void);
int				ft_init2(char *cub, int bmp);
void			ft_init(char *cub, int bmp);

void			bitmap_header(int fd);
void			dib_header(int fd);
void			fill_bmp(int *i, int fd);
int				ft_bitmap(t_all s);
void			drawspr2(t_spr spr);
void			drawspr(void);
void			ft_sorder(void);
void			sprites(void);
int				haswallat(double x, double y);
int				ft_slist(void);
void			drawtextspr(t_spr spr, int i, int top, double h);
int				ft_strerror(int err);
int				ft_spaceskip(char *line, int *i);
int				ft_atoi(char *line, int *i);
int				ft_close(t_all *s, int win);
int				ft_texture(char *line, unsigned int **adr, int *i);
double			ft_normalizeangle(double angle);
void			ray_config(t_ray *r, double rayangle);
char			*ft_slab(t_all *s, char *line, int i, int x);
int				ft_map(t_all *s, char *line);
int				ft_mapcheck(t_all *s);
int				ft_parcheck(t_all *s);
int				ft_xppm(unsigned int **adr, char *file);
void			my_mlx_pixel_put(int x, int y, int color);
int				ft_res(t_all *s, char *line, int *i);
int				ft_slablen(char *line);
int				ft_colors(unsigned int *color, char *line, int *i);
int				ft_line(t_all *s, char *line);
void			ft_pos(t_all *s);
int				config(t_all *s, char *cub);
void			casthorz(t_ray *rayss);
void			castvert(double *x, double *y, t_ray *rayss);
void			cast(t_ray *rays);
void			castallrays(void);
void			drawline(int x0, int y0, int y1, int i);
void			drawwall(int d, int i, int x, t_ray *r);
void			render3d(void);
double			distance(double x1, double y1, double x2, double y2);
int				ft_line2(t_all *s, char *line);
void			plyupdate(void);
int				colorval(t_ray *r, int y, int s);

#endif
