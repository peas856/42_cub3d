#include "cub3d.h"

int		ft_spaceskip(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
	|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
	return (1);
}

int		ft_atoi(char *line, int *i)
{
	int	num;

	num = 0;
	ft_spaceskip(line, i);
	while (line[*i] >= '0' && line[*i] <= '9')
	{
		num = num * 10 + (line[*i] - '0');
		(*i)++;
	}
	return (num);
}

int		ft_strerror(int err)
{
	(err == -1) ? write(2, "Error : Can not open file\n", 26) : 0;
	(err == -2) ? write(2, "Error : Gnl error\n", 18) : 0;
	(err == -3) ? write(2, "Error : Set resolution once\n", 28) : 0;
	(err == -4) ? write(2, "Error : Invalid resolution\n", 27) : 0;
	(err == -5) ? write(2, "Error : Set Floor/ceiling once\n", 31) : 0;
	(err == -6) ? write(2, "Error : Invalid floor/ceiling\n", 30) : 0;
	(err == -7) ? write(2, "Error : Set texture path once\n", 30) : 0;
	(err == -8) ? write(2, "Error : Malloc fail (texture path)\n", 35) : 0;
	(err == -9) ? write(2, "Error : Invalid texture image\n", 30) : 0;
	(err == -10) ? write(2, "Error : Invalid line in file\n", 29) : 0;
	(err == -11) ? write(2, "Error : Malloc fail (map table)\n", 32) : 0;
	(err == -12) ? write(2, "Error : Invalid map\n", 20) : 0;
	(err == -14) ? write(2, "Error : No resolution\n", 22) : 0;
	(err == -15) ? write(2, "Error : Missing texture\n", 24) : 0;
	(err == -16) ? write(2, "Error : Missing floor/ceiling color\n", 36) : 0;
	(err == -18) ? write(2, "Error : Check starting positions\n", 33) : 0;
	(err == -19) ? write(2, "Error : Map needs walls\n", 24) : 0;
	return (-1);
}
