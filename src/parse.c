/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trhee <trhee@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 17:54:19 by trhee             #+#    #+#             */
/*   Updated: 2021/06/15 18:34:34 by trhee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int					return_line(char **s, char **line, int len, int i)
{
	char			*tmp;

	if (i == -1)
	{
		*line = ft_strdup(*s);
		free(*s);
		*s = 0;
		if (len == 0)
			return (0);
	}
	else
	{
		(*s)[i] = '\0';
		*line = ft_strdup(*s);
		tmp = ft_strdup(*s + i + 1);
		free(*s);
		*s = tmp;
		if ((*s)[0] == '\0')
		{
			free(*s);
			*s = 0;
		}
	}
	return (1);
}

int					get_next_line(int fd, char **line)
{
	char			buf[2];
	int				len;
	static char		*s[OPEN_MAX];
	char			*tmp;

	if (fd < 0 || !line)
		return (-1);
	while ((len = read(fd, buf, 1)) > 0)
	{
		buf[len] = '\0';
		if (!s[fd])
			s[fd] = ft_strdup("");
		tmp = ft_strjoin(s[fd], buf);
		free(s[fd]);
		s[fd] = tmp;
		if ((is_newline(s[fd])) > -1)
			break ;
	}
	if (len < 0)
		return (-1);
	else if (len == 0 && (!s[fd]))
		*line = ft_strdup("");
	else
		return (return_line(&s[fd], line, len, is_newline(s[fd])));
	return (0);
}

int					ft_line(t_all *s, char *line)
{
	int				i;

	i = 0;
	if ((line[i] == '1' || line[i] == ' ' || s->err.m == 1) && line[i] != '\0')
		s->err.n = ft_map(s, line, &i);
	else if (line[i] == 'R' && line[i + 1] == ' ')
		s->err.n = ft_res(s, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.n, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.s, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.w, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.e, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		s->err.n = ft_colors(&s->tex.f, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		s->err.n = ft_colors(&s->tex.c, line, &i);
	if (ft_spaceskip(line, &i) && !s->err.n && s->err.m == 1 && line[i] != '\0')
		return (ft_strerror(-10));
	return (s->err.n < 0 ? ft_strerror(s->err.n) : 0);
}

int					ft_padding(t_all *s)
{
	int				i;
	int				j;
	char			**tmp;

	if (!(tmp = malloc(sizeof(char *) * (s->map.y + 1))))
		return (-1);
	i = 0;
	while (i < s->map.y)
	{
		j = -1;
		if (!(tmp[i] = malloc(sizeof(char) * (s->map.x + 1))))
			return (-1);
		while (s->map.tab[i][++j] != '\0')
			tmp[i][j] = s->map.tab[i][j];
		while (j < s->map.x)
			tmp[i][j++] = '*';
		tmp[i][j] = '\0';
		free(s->map.tab[i]);
		i++;
	}
	free(s->map.tab);
	tmp[i] = NULL;
	s->map.tab = tmp;
	return (0);
}

int					ft_parse(t_all *s, char *cub)
{
	char			*line;
	int				fd;
	int				ret;

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
	ft_padding(s);
	if (ret == -1 || ret == -3)
		return (ft_strerror(ret + 1));
	if (ft_pos(s) == -1 || s->err.pos)
		return (ft_strerror(-18));
	return (ft_parcheck(s));
}
