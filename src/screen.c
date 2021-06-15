#include "cub3d.h"

void		ft_side(t_all *s)
{
	t_drwa drw;
	double perpwalldist;
	double wall_x;

	if (s->hit.side == 0)
		perpwalldist = (s->mapx - s->pos.x + (1 - s->ray.stepX) / 2) / s->ray.x;
	else
		perpwalldist = (s->mapy - s->pos.y + (1 - s->ray.stepY) / 2) / s->ray.y;
	drw.line_h = (int)(s->win.y / perpwalldist);
	drw.start = (-drw.line_h / 2) + (s->win.y / 2);
	if (drw.start < 0)
		drw.start = 0;
	drw.end = (drw.line_h / 2) + (s->win.y / 2);
	if (drw.end >= s->win.y)
		drw.end = s->win.y - 1;
	if (s->hit.side == 0)
		wall_x = s->pos.y + perpwalldist * s->ray.y;
	else
		wall_x = s->pos.x + perpwalldist * s->ray.x;
	wall_x -= floor(wall_x);
	drw.tex_x = (int)(wall_x * (double)texWidth);
	s->drw = drw;
}

void		ft_wall(t_all *s)
{
	s->tex_num = 0;
	
	if (s->hit.side == 1)
	{
		if (s->ray.y >= 0)
			s->tex_num = s->tex.n;
		else
			s->tex_num = s->tex.s;
	}
	else
	{
		if (s->ray.x >= 0)
			s->tex_num = s->tex.w;
		else
			s->tex_num = s->tex.e;
	}
	if (s->hit.side == 0 && s->ray.x > 0)
		s->drw.tex_x = texWidth - s->drw.tex_x - 1;
	if (s->hit.side == 1 && s->ray.y < 0)
		s->drw.tex_x = texWidth - s->drw.tex_x - 1;
	
}
void		ft_tex(t_all *s)
{
	double step;
	double tex_pos;
	int		i;
	int		tex_y;

	i = 0;
	while(i < s->win.y)
	{
		s->buf[i] = s->tex.f; 
		s->buf[s->win.y - i - 1] = s->tex.c;
		i++;
	}
	step = 1.0 * texHeight / s->drw.line_h;
	tex_pos = (s->drw.start - s->win.y / 2 + s->drw.line_h / 2) * step;
	i = s->drw.start;
	tex_y = 0;
	while(i < s->drw.end)
	{
		tex_y = (int)tex_pos & (texHeight - 1);
		tex_pos += step;
		s->buf[i] = s->tex_num[texHeight * tex_y + s->drw.tex_x];
		i++;
	}
}

void imagedraw(t_all *s)
{
	int y;
	
	y = 0;
    while (s->ray.i < s->win.x * s->win.y)
	{
        s->img.adr[s->ray.i] = s->buf[y];
		s->ray.i += s->win.x;
		y++;
	}
    s->ray.i -= s->win.x * s->win.y;
}

void	ft_screen(t_all *s)
{
	int		bpp;
	int		sl;
	int		end;

	s->img.ptr = mlx_new_image(s->mlx.ptr, s->win.x, s->win.y);
	s->img.adr = (unsigned int *)mlx_get_data_addr(s->img.ptr, &bpp, &sl, &end);
	while (s->ray.i < s->win.x)
	{
		s->buf = (int *)malloc(sizeof(int) * s->win.y);
		ft_ray(s);
		ft_dir(s);
		ft_hit(s);
		ft_side(s);
		ft_wall(s);
		ft_tex(s);
		imagedraw(s);
		s->ray.i++;
		free(s->buf);
	}
}