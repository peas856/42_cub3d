/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trhee <trhee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 18:20:17 by trhee             #+#    #+#             */
/*   Updated: 2021/06/15 19:02:32 by trhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <limits.h>

# define ESC 53
# define W 13
# define A 0
# define S 1
# define D 2
# define LEFT 123
# define RIGHT 124
# define NONE 0xFF000000

# define SPEED 30
# define ANGLE 0.03
# define TEXWIDTH 64
# define TEXHEIGHT 64

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

typedef struct	s_img
{
	void			*ptr;
	unsigned int	*adr;
}				t_img;

typedef struct	s_err
{
	int				n;
	int				m;
	int				pos;
}				t_err;

typedef struct	s_map
{
	char			**tab;
	int				x;
	int				y;
}				t_map;

typedef struct	s_tex
{
	unsigned int	*n;
	unsigned int	*s;
	unsigned int	*e;
	unsigned int	*w;
	unsigned int	c;
	unsigned int	f;
}				t_tex;

typedef struct	s_pos
{
	double			x;
	double			y;
}				t_pos;

typedef struct	s_dir
{
	double			x;
	double			y;
	double			a;
}				t_dir;

typedef struct	s_ray
{
	double			x;
	double			y;
	int				i;
	double			stepx;
	double			stepy;
	double			deltadistx;
	double			deltadisty;
	double			sidedistx;
	double			sidedisty;
}				t_ray;

typedef struct	s_hit
{
	int				h;
	int				side;
}				t_hit;

typedef struct	s_draw
{
	int				tex_x;
	int				line_h;
	int				start;
	int				end;
}				t_drwa;

typedef struct	s_all
{
	t_mlx			mlx;
	t_win			win;
	t_img			img;
	t_err			err;
	t_map			map;
	t_tex			tex;
	t_pos			pos;
	t_dir			dir;
	t_ray			ray;
	t_hit			hit;
	t_drwa			drw;
	int				*buf;
	int				mapx;
	int				mapy;
	unsigned int	*tex_num;
}				t_all;

void			ft_init(char *cub);
void			ft_declare(t_all s, char *cub);
int				ft_cubed(t_all s, char *cub);
void			ft_draw(t_all *s);

int				ft_parse(t_all *s, char *cub);
int				get_next_line(int fd, char **line);
int				ft_line(t_all *s, char *line);
int				ft_padding(t_all *s);

int				ft_map(t_all *s, char *line, int *i);
char			*ft_slab(t_all *s, char *line, int *i);
int				ft_slablen(t_all *s, char *line);
int				ft_texture(t_all *s, unsigned int **adr, char *line, int *i);
int				ft_xpm(t_all *s, unsigned int **adr, char *file);

int				ft_pos(t_all *s);
int				ft_colors(unsigned int *color, char *line, int *i);
int				ft_res(t_all *s, char *line, int *i);

int				ft_parcheck(t_all *s);
int				val_check(t_all *s, int i, int j);
int				ft_mapcheck(t_all *s);
int				ft_filecheck(char *av, char *s);
int				ft_strcmp(const char *s1, const char *s2);

int				ft_key(int key, void *arg);
void			ft_rotate(t_all *s, double c);
void			ft_move(t_all *s, double c, int dir);
int				ft_close(t_all *s, int win);

void			ft_ray(t_all *s);
void			ft_dir(t_all *s);
void			ft_hit(t_all *s);

void			ft_screen(t_all *s);
void			imagedraw(t_all *s);
void			ft_tex(t_all *s);
void			ft_wall(t_all *s);
void			ft_side(t_all *s);

size_t			ft_strlen(const char *s);
size_t			ft_strlcpy(char *dst, const char *src, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t n);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strdup(const char *s1);

int				is_newline(char *buf);
int				ft_atoi(char *line, int *i);
int				ft_spaceskip(char *line, int *i);
int				ft_strerror(int err);

#endif
