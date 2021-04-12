#include "cub3d.h"

int		ft_res(t_all *s, char *line, int *i)
{
	if (s->win.x != 0 || s->win.y != 0)  // 0이 아니면 해상도가 이미 지정되어있다는 뜻 
		return (-3); // Resolution specified twice
	(*i)++;
	s->win.x = ft_atoi(line, i);   // 0~9까지만 atoi 하고 int 숫자로 출력
	s->win.y = ft_atoi(line, i);	// 0~9까지만 atoi 하고 int 숫자로 출력, i가 포인터로 변경됨
	if (s->win.x > 2560)
		s->win.x = 2560;
	if (s->win.y > 1400)
		s->win.y = 1400;
	ft_spaceskip(line, i);
	if (s->win.x <= 0 || s->win.y <= 0 || line[*i] != '\0')
		return (-4);  // "Error : Invalid resolution\n"
	return (0);
}

int		ft_colors(unsigned int *color, char *line, int *i)
{
	int	r;
	int	g;
	int	b;

	if (*color != NONE)
		return (-5);   // "Error : Floor/ceiling specified twice\n"
	(*i)++;
	r = ft_atoi(line, i);
	(*i)++;   // 쉼표 제거 , F 220, 100, 0
	g = ft_atoi(line, i);
	(*i)++;
	b = ft_atoi(line, i);
	ft_spaceskip(line, i);
	if (line[*i] != '\0' || r > 255 || g > 255 || b > 255)
		return (-6);   // "Error : Invalid floor/ceiling line\n"
	*color = r * 256 * 256 + g * 256 + b;  //2의 8승, 256 
	return (0);
}

void	ft_pos(t_all *s)
{
	char	c;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (++i < s->map.y)
	{
		while (++j < s->map.x)
		{
			c = s->map.tab[i][j];
			if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
			{
				s->pos.y = (double)i + 0.5;
				s->pos.x = (double)j + 0.5;
				s->dir.x = (c == 'E' || c == 'W') ? 1 : 0;
				s->dir.x *= (c == 'W') ? -1 : 1;
				s->dir.y = (c == 'S' || c == 'N') ? 1 : 0;
				s->dir.y *= (c == 'N') ? -1 : 1;
				s->err.p++;
			}
		}
		j = -1;
	}
}

int		ft_slist(t_all *s)
{
	int		i;
	int		j;
	int		k;

	if (s->spr != NULL)
		free(s->spr);
	if (!(s->spr = malloc(sizeof(t_spr) * s->map.spr)))
		return (-1);
	i = 0;
	j = 0;
	while (j < s->map.y)
	{
		k = 0;
		while (k < s->map.x)
		{
			if (s->map.tab[j][k] == '2')
			{
				s->spr[i].y = (double)j + 0.5;
				s->spr[i++].x = (double)k + 0.5;
			}
			k++;
		}
		j++;
	}
	return (1);
}
