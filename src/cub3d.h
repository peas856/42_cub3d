#ifndef CUB3D_H
# define CUB3D_H

# include "../mlx/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

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
# define LEFT 123
# define RIGHT 124

# define SPEED 30
# define ANGLE 0.03

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
	double			stepX;
	double			stepY;
	double			deltadistX;
	double			deltadistY;
	double			sidedistX;
	double			sidedistY;
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
	int				mapX;
	int				mapY;
	unsigned int	*tex_num;
}				t_all;

void			ft_init(char *cub);
void			ft_declare(t_all s, char *cub);
int				ft_cubed(t_all s, char *cub);
void			ft_draw(t_all *s);

int				ft_parse(t_all *s, char *cub);
int				get_next_line(int fd, char **line);
int				ft_line(t_all *s, char *line);

int				ft_map(t_all *s, char *line, int *i);
char			*ft_slab(t_all *s, char *line, int *i);
int				ft_slablen(t_all *s, char *line);
int				ft_texture(t_all *s, unsigned int **adr, char *line, int *i);
int				ft_xpm(t_all *s, unsigned int **adr, char *file);

int				ft_pos(t_all *s);
int				ft_colors(unsigned int *color, char *line, int *i);
int				ft_res(t_all *s, char *line, int *i);

int				ft_parcheck(t_all *s);
int				ft_mapcheck(t_all *s);
int				ft_filecheck(char *av, char *s);
int				ft_strcmp(const char *s1, const char *s2);

int				ft_key(int key, void *arg);
void			ft_rotate(t_all *s, double c);
void			ft_move(t_all *s, double c, int dir);
int				ft_close(t_all *s, int win);

void			ft_screen(t_all *s);
void			ft_ray(t_all *s);
void			ft_dir(t_all *s);
void			ft_hit(t_all *s);
void			ft_hor(t_all *s);

void			ft_stock(t_all *s);
int				ft_size(t_all *s);
void			ft_column(t_all *s, int start);
unsigned int	ft_pixel(t_all *s, double i);

char			*error(char *stock);
int				newline_check(char *stock, int read_size);
char			*buf_join(char *stock, char *buf);
char			*stock_trim(char *stock);
char			*get_line(char *stock);

int				ft_atoi(char *line, int *i);
int				ft_spaceskip(char *line, int *i);
int				ft_strerror(int err);

#endif
