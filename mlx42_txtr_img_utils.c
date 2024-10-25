
#include "cub3d.h"

void	init_txtr(t_map *md, t_tx *t)
{
	t->n = mlx_load_png("./textures/N.png");
	t->s = mlx_load_png("./textures/S.png");
	t->e = mlx_load_png("./textures/E.png");
	t->w = mlx_load_png("./textures/W.png");
	if (!t->n || !t->s || !t->e || !t->w)
		error_exit(md);
	md->txtr = t;
}

void	delete_textures(t_tx *t)
{
	if (t->n)
		mlx_delete_texture(t->n);
	if (t->s)
		mlx_delete_texture(t->s);
	if (t->e)
		mlx_delete_texture(t->e);
	if (t->w)
		mlx_delete_texture(t->w);
}
