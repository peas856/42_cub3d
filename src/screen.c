#include "cub3d.h"

#define texWidth 64
#define texHeight 64

void	ft_ray(t_all *s)
{
	double	angle;
	double	dist;
	double	cameraX;

	s->mapX = (int)(s->pos.x);
	s->mapY = (int)(s->pos.y);
	cameraX = (2 * s->ray.i / (double)s->win.x) - 1;
	angle = 33 * cameraX * M_PI / 180;
	s->ray.x = s->dir.x * cos(angle) - s->dir.y * sin(angle);
	s->ray.y = s->dir.y * cos(angle) + s->dir.x * sin(angle);
	dist = hypot(s->ray.x, s->ray.y);
	s->ray.x /= dist;
	s->ray.y /= dist;
}

void	ft_dir(t_all *s)
{
	s->ray.deltadistX = fabs(1 / s->ray.x);
	s->ray.deltadistY = fabs(1 / s->ray.y);
	if (s->ray.x >= 0)
	{
		s->ray.stepX = 1;	
		s->ray.sidedistX = (s->mapX + 1.0 - s->pos.x) * s->ray.deltadistX;
	}
	else
	{
		s->ray.stepX = -1;
		s->ray.sidedistX = (s->pos.x - s->mapX) * s->ray.deltadistX;
	}
	if (s->ray.y >= 0)
	{
		s->ray.stepY = 1;
		s->ray.sidedistY = (s->mapY + 1 - s->pos.y) * s->ray.deltadistY;
	}	
	else
	{
		s->ray.stepY = -1;
		s->ray.sidedistY = (s->pos.y - s->mapY) * s->ray.deltadistY;
	}
}

void	ft_hit(t_all *s)
{
	s->hit.h = 0;
	for (int y = 0; y < s->win.y; y++)
	{
		s->buf[y] = s->tex.f; 
		s->buf[s->win.y - y - 1] = s->tex.c;
	}
	while (s->hit.h == 0)
	{
		if (s->ray.sidedistX < s->ray.sidedistY) // 기울기가 1보다 작을 때, x축으로 검사
		{
			s->ray.sidedistX += s->ray.deltadistX;
			s->mapX += s->ray.stepX; // stepX 는 1, -1 중 하나.
			s->hit.side = 0; // x면에 부딪혔다면 side = 0
		}
		else  // 기울기가 1보다 클 때, y축 기준으로 검사 
		{
			s->ray.sidedistY += s->ray.deltadistY;
			s->mapY += s->ray.stepY; // stepY는 1, -1 중 하나.
			s->hit.side = 1; // y면에 부딪혔다면 side = 1
		}
		if (s->map.tab[s->mapY][s->mapX] == '1')
			s->hit.h = 1;
	}
}

void		ft_side(t_all *s)
{
	t_drwa drw;
	double perpwalldist;
	double wall_x;

	if (s->hit.side == 0)
		perpwalldist = (s->mapX - s->pos.x + (1 - s->ray.stepX) / 2) / s->ray.x;
	else
		perpwalldist = (s->mapY - s->pos.y + (1 - s->ray.stepY) / 2) / s->ray.y;
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
	
	if (s->hit.side == 1) // y면에 부딪히면
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

void imageDraw(t_all *s)
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
		imageDraw(s);
		s->ray.i++;
		free(s->buf);
	}
}