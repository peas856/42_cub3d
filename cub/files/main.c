#include "cub3d.h"

void	ft_draw(t_all *s)
{
	t_ray	ray;
	t_hit	hit;

	ray.x = 0;
	ray.y = 0;
	ray.i = 0;
	ray.v = 0;
	ray.w = 0;
	hit.x = 0;
	hit.y = 0;
	hit.d = 0;
	s->ray = ray;
	s->hit = hit;
	ft_screen(s);
	mlx_put_image_to_window(s->mlx.ptr, s->win.ptr, s->img.ptr, 0, 0);  //이미지를 스크린에 출력
	free(s->img.ptr);
	free(s->img.adr);
}

int		ft_cubed(t_all s, char *cub, int bmp)
{
	t_pos	pos;   // doulbe 형 x, y
	t_dir	dir;   // double 형 x, y, a

	pos.x = 0;
	pos.y = 0;
	dir.x = 0;
	dir.y = 0;
	s.pos = pos;
	s.dir = dir;
	s.mlx.ptr = mlx_init(); // 그래픽 시스템에 connection을 만들고 void * 를 리턴
	if (ft_parse(&s, cub) == -1)  // 에러가 발생하면 ft_close 리턴, 구조체 s와 0 전달)
		return (ft_close(&s, 0)); //
	if (bmp == 1)
		return (ft_bitmap(&s));
	ft_rotate(&s, 1);
	ft_move(&s, 1);
	ft_rotate(&s, -1);
	ft_move(&s, -1);
	s.win.ptr = mlx_new_window(s.mlx.ptr, s.win.x, s.win.y, "cub3D");  // 새 창을 생성하는 함수
	ft_draw(&s);
	mlx_hook(s.win.ptr, 2, 0, ft_key, &s);  //이벤트를 감지하기 (키보드 입력 이벤트)
	mlx_hook(s.win.ptr, 17, 0, ft_close, &s);
	mlx_loop(s.mlx.ptr);  //반환값이 없다. 이벤트를 기다린 다음 이 이벤트와 연결된 사용자 정의 함수를 호출하는 무한 루프, 키 입력, 마우스 입력)
	return (1);
}

void	ft_declare(t_all s, char *cub, int bmp)
{
	t_map	map; // tap char형 이중포인터, spr int, x, y
	t_tex	tex; // int 포인터 4개,int 2개 
	t_spr	*spr;  // stk랑 같음 
	t_stk	*stk;   // x, y, d double 형

	map.tab = NULL;
	tex.n = NULL;
	tex.s = NULL;
	tex.e = NULL;
	tex.w = NULL;
	tex.i = NULL;
	spr = NULL;
	stk = NULL;
	map.x = 0;
	map.y = 0;
	map.spr = 0;
	tex.c = NONE;
	tex.f = NONE;
	s.map = map;
	s.tex = tex;
	s.spr = spr;
	s.stk = stk;
	// 모두 초기화해준후 구조체 s를 cubed에 담아줌 
	ft_cubed(s, cub, bmp);
}

void	ft_init(char *cub, int bmp)
{
	t_all	s;  // 모든 구조체를 담아줌  
	t_mlx	mlx;  // 포인터만 담고있음 
	t_win	win; // 윈도우 띄우기 위한 포인터, x, y
	t_img	img; // 포인터, int addr, fsh ??
	t_err	err; // n, m, p int 들어있음

	// 초기화 후 s에 담아줌 
	mlx.ptr = NULL;
	win.ptr = NULL;
	img.ptr = NULL;
	img.adr = NULL;
	win.x = 0;
	win.y = 0;
	img.fsh = 0;
	err.n = 0;
	err.m = 0;
	err.p = 0;
	s.mlx = mlx;
	s.win = win;
	s.img = img;
	s.err = err;
	// declare로 넘겨줌 bmp는 int 변수 cub는 파일 포인터, s는 구조체 
	ft_declare(s, cub, bmp);
}

int		main(int ac, char **av)
{
	if (ac == 3 && !ft_cubcheck(av[1]) && !ft_strcmp(av[2], "--save"))
		ft_init(av[1], 1);
	else if (ac == 2 && !ft_cubcheck(av[1]))
		ft_init(av[1], 0);
	else
		write(2, "Error : Invalid arguments\n", 26);
	return (0);
}
