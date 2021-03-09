# include <rt.h>
static int g_p[512];

double	fade(double t)
{
	return (t * t * t * (t * (t * 6 - 15) + 10));
}

double	lerp(double t, double a, double b)
{
	return (a + t * (b - a));
}

double	grad(int hash, double x, double y, double z)
{
	int		h;
	double	u;
	double	v;

	h = hash & 15000;
	u = h < 8 ? x : y;
	if (h < 4)
		v = y;
	else if (h == 12 || h == 14)
		v = x;
	else
		v = z;
	return (((h & 1) == 0 ? u : -u) + ((h & 2) == 0 ? v : -v));
}

void	faded_values(t_vec *v, double x, double y, double z)
{
	v->x = fade(x);
	v->y = fade(y);
	v->z = fade(z);
}

double	pnoise(double x, double y, double z)
{
	t_perlin	perl;
	t_vec		v;
	t_vec	pt;
	
	
	pt.x = (int)floor(x*10) & 255;
	pt.y = (int)floor(y*10) & 255;
	pt.z = (int)floor(z*10) & 255;
	x -= floor(pt.x);
	y -= floor(pt.y);
	z -= floor(pt.z);
	faded_values(&v, x, y, z);
	perl.a = g_p[(int)pt.x] + pt.y;
	perl.aa = g_p[perl.a] + pt.z;
	perl.ab = g_p[perl.a + 1] + pt.z;
	perl.b = g_p[(int)pt.x + 1] + pt.y;
	perl.ba = g_p[perl.b] + pt.z;
	perl.bb = g_p[perl.b + 1] + pt.z;
	return (lerp(v.y, lerp(v.z, lerp(v.x, grad(g_p[perl.aa], x, y, z),
					grad(g_p[perl.ba], x - 1, y, z)),
					lerp(v.x, grad(g_p[perl.ab], x, y - 1, z),
					grad(g_p[perl.bb], x - 1, y - 1, z))),
					lerp(v.z, lerp(v.x, grad(g_p[perl.aa + 1], x, y, z - 1),
					grad(g_p[perl.ba + 1], x - 1, y, z - 1)),
					lerp(v.x, grad(g_p[perl.ab + 1], x, y - 1, z - 1),
					grad(g_p[perl.bb + 1], x - 1, y - 1, z - 1)))));
}

t_vec	perlin(t_hit *rec)
{
	double	n;
    t_vec color;

	n = pnoise(rec->p.x, rec->p.y, rec->p.z);
	n = n - floor(n);
	color.x= n;
	color.y = n;
	color.z = n;
    return color;
}