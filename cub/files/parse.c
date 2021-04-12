/* ************************************************************************** */
/*                                                                            */
#include "cub3d.h"

int		ft_line(t_all *s, char *line)
{
	int		i;

	i = 0;
	ft_spaceskip(line, &i); // 라인 공백제거 
	if ((line[i] == '1' || s->err.m == 1) && line[i] != '\0') //s->err.m (ft_map에서 1로 줌),  ft_map -> 유효성체크, ft_res->윈도우사이즈, ft_texture-> 4방향 텍스처, ft_colors -> rgb 바닥 천장
		s->err.n = ft_map(s, line, &i);   // line[i] == 1이면 ft_map 실행 
	else if (line[i] == 'R' && line[i + 1] == ' ')   // resolution x.render, y.render 사이즈 
		s->err.n = ft_res(s, line, &i);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.n, line, &i);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.s, line, &i);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.w, line, &i);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		s->err.n = ft_texture(s, &s->tex.e, line, &i);
	else if (line[i] == 'S' && line[i + 1] == ' ')   //스프라이트, 스프라이트(sprite) 는 enemies, objects, goodies와 같은 2D 이미지를 말합니다. 
		s->err.n = ft_texture(s, &s->tex.i, line, &i);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		s->err.n = ft_colors(&s->tex.f, line, &i);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		s->err.n = ft_colors(&s->tex.c, line, &i);
	if (ft_spaceskip(line, &i) && s->err.n == 0 && line[i] != '\0')  // s->err.n 의 경우 에러가 없으면 0임, 있으면 0보다 작음 
		return (ft_strerror(-10)); // err -10 : "Error : Invalid line in file
	return (s->err.n < 0 ? ft_strerror(s->err.n) : 0); // s->err.n 담긴 에러 넘버가 0보다 작으면 에러발생, 아니면 리턴 0
}

int		get_next_line(int fd, char **line) // gnl 작동법 확인, 줄바꿈 문자가 나올때까지 한줄식 내뱉어줌
{
	int			read_size;
	char		buf[4096];
	static char	*stock = NULL;

	if (line == NULL || fd < 0)
		return (-3);
	*line = NULL;
	read_size = 1;
	while (!(newline_check(stock, read_size)))
	{
		if ((read_size = read(fd, buf, 4095)) == -1)
			return (-3);
		buf[read_size] = '\0';
		if ((stock = buf_join(stock, buf)) == NULL)
			return (-3);
	}
	if ((*line = get_line(stock)) == NULL)
		return (-3);
	if (read_size == 0)
		free(stock);
	if (read_size == 0)
		return (0);
	if ((stock = stock_trim(stock)) == NULL)
		return (-3);
	return (1);
}

int		ft_parse(t_all *s, char *cub)
{
	char	*line;
	int		fd;
	int		ret;

	ret = 1;
	fd = open(cub, O_RDONLY);
	if (fd == -1)   // 파일 오픈 실패 
		return (ft_strerror(-1));
	while (ret == 1)
	{
		ret = get_next_line(fd, &line);  // get_next_line에서 리턴값이 -3이 나오려면? 
		if (ft_line(s, line) == -1)   // 에러메시지가 발생했다는 뜻 
			ret = -1;
		free(line);
	}
	close(fd);
	if (ret == -1 || ret == -3)
		return (ft_strerror(ret + 1));   // err -2(Error : gnl error), err 0(그냥 리턴 -1)
	ft_pos(s);      //ft_pos?
	s->spr = NULL;   //s->spr??
	ft_slist(s);    //ft_slist??
	return (ft_parcheck(s));   //ft_parcheck -> 맵 유효성체크, 바닥, 천장, 텍스처 체크, 윈도우 사이즈 체크 등 
}
