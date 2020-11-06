#include "mini_rt.h"
#include <stdio.h>

// #define	WIN1_SX		500
// #define	WIN1_SY		500

void	*mlx;
void	*win1;
t_rt	rt;
int		WIN1_SX;
int		WIN1_SY;

void	color_map_1(void *win,int w,int h);
void	sphere1();
void	sphere2();
void	sphere3();
void	sphere4();
void	sphere5();
void	sphere6();

int main(int argc, char *argv[])
{
	parse_rt(argc, argv, &rt);
	WIN1_SX = rt.res.x;
	WIN1_SY = rt.res.y;
	if (!(mlx = mlx_init()))
		return (1);
	if (!(win1 = mlx_new_window(mlx, WIN1_SX, WIN1_SY, "Title1")))
		return (1);
	
	//color_map_1(win1,WIN1_SX,WIN1_SY);
	//sphere1();
	//sphere2();
	//sleep(5);
	//sphere3();
	// sphere4();
	//sphere5();
	sphere6();
	mlx_loop(mlx);
	return (0);
}

static double	inner_product(double *a, double *b)
{
	return (a[0] * b[0] + a[1] * b[1] + a[2] * b[2]);
}

void	sphere6()
{
	int color;

	double Pv[3] = {WIN1_SX/2, WIN1_SY/2, 2000.0};
	double Pc[2][3] = {{WIN1_SX/2 - 25, WIN1_SY/2 - 25, 0.0},
						{WIN1_SX/2 + 120, WIN1_SY/2 + 120, -330.0}};
	double R[2] = {100.0, 100.0};
	
	double v[3];
	int i, j;
	i = 0;
	while (i < WIN1_SX)
	{
		j = 0;
		while (j < WIN1_SY)
		{
			v[0] = i + 0.5 - Pv[0];
			v[1] = j + 0.5 - Pv[1];
			v[2] = 0 - Pv[2];


			//discriminant
			double A, B2, C, D;
			double Pvc[3];
			double t;
			double t0;

			int k;
			int s0 = -1;
			int s = 0;
			A = inner_product(v, v);
			while (s < 2)
			{
				k = 0;
				while (k < 3)
				{
					Pvc[k] = Pv[k] - Pc[s][k];
					k++;
				}
				B2 = inner_product(Pvc, v);
				C = inner_product(Pvc, Pvc) - R[s] * R[s];
				D = B2 * B2 - A * C;
				if (D >= 0)
				{
					t = (-B2 - sqrt(D)) / A;
					if (s0 < 0 || t < t0)
					{
						s0 = s;
						t0 = t;
					}
				}
				s++;
			}
			
			//
			
			//intersection
			double P[3];
			// k = 0;
			// while (k < 3)
			// {
			// 	P[k] = Pv[k] + v[k] * t0;
			// 	k++;
			// }
			//

			//normal vector
			double PL[3] = {-20000, -20000, 20000};
			double N[3], vL[3];
			double cosA;
			// k = 0;
			// while (k < 3)
			// {
			// 	N[k] = P[k] - Pc[s0][k];
			// 	k++;
			// }
			// k = 0;
			// while (k < 3)
			// {
			// 	vL[k] = P[k] - PL[k];
			// 	k++;
			// }
			// cosA = -inner_product(vL, N);
			// cosA /= sqrt(inner_product(vL, vL) * inner_product(N, N));
			//

			//mirror
			double vR[3];
			double w, cosG;
			int n = 10;
			// w = -inner_product(vL, N) / inner_product(N, N);
			// k = 0;
			// while (k < 3)
			// {
			// 	vR[k] = 2 * w * N[k] + vL[k];
			// 	k++;
			// }
			// cosG = -inner_product(vR, v) / sqrt(inner_product(vR, vR) * inner_product(v, v));
			// if (cosG < 0)
			// 	cosG = 0;
			// cosG = pow(cosG, n);





			//mix output
			double Kd = 1.0, Ks = 0.7, Ie = 0.1, I = 255.0;
			double RGB[2][3] = {{255, 0, 0}, {0, 255, 0}};
			double color_array[3];
			double v1[3];
			double Pvc1[3];

			if (s0 >= 0)
			{
				// intersection
				k = 0;
				while (k < 3)
				{
					P[k] = Pv[k] + v[k] * t0;
					k++;
				}
				//

				s = 0;
				while (s < 2)
				{
					if (s == s0)
					{
						s++;
						continue;
					}
					k = 0;
					while (k < 3)
					{
						v1[k] = PL[k] - P[k];
						k++;
					}
					k = 0;
					while (k < 3)
					{
						Pvc1[k] = P[k] - Pc[s][k];
						k++;
					}
					A = inner_product(v1, v1);
					B2 = inner_product(Pvc1, v1);
					C = inner_product(Pvc1, Pvc1) - R[s] * R[s];
					D = B2 * B2 - A * C;
					if (D >= 0 && (-B2 - sqrt(D)) / A > 0)
						break;
					s++;
				}
				if (s < 2)
					cosA = cosG = 0.0;
				else
				{
					// cosA
					k = 0;
					while (k < 3)
					{
						N[k] = P[k] - Pc[s0][k];
						k++;
					}
					k = 0;
					while (k < 3)
					{
						vL[k] = P[k] - PL[k];
						k++;
					}
					cosA = -inner_product(vL, N);
					cosA /= sqrt(inner_product(vL, vL) * inner_product(N, N));				/* code */
					//

					// cosG
					w = -inner_product(vL, N) / inner_product(N, N);
					k = 0;
					while (k < 3)
					{
						vR[k] = 2 * w * N[k] + vL[k];
						k++;
					}
					cosG = -inner_product(vR, v) / sqrt(inner_product(vR, vR) * inner_product(v, v));
					if (cosG < 0)
						cosG = 0;
					cosG = pow(cosG, n);
					//
				}
				
				k = 0;
				while (k < 3)
				{
					color_array[k] = RGB[s0][k] * Kd * cosA;
					if (color_array[k] < I * Ks * cosG)
						color_array[k] = I * Ks * cosG;
					if (color_array[k] < RGB[s0][k] * Ie)
						color_array[k] = RGB[s0][k] * Ie;
					k++;
				}
				color =  ((int)(color_array[0])<<16) + ((int)(color_array[1])<<8) + (int)(color_array[2]);
				mlx_pixel_put(mlx, win1, i, j, color);
			}
			else
			{
				color =  (0<<16) + (0<<8) + (127);
				mlx_pixel_put(mlx, win1, i, j, color);
			}
			j++;
		}
		i++;
	}
}

void	sphere5()
{
	int color;

	double Pv[3] = {WIN1_SX/2, WIN1_SY/2, 2000.0};
	double Pc[2][3] = {{WIN1_SX/2 - 25, WIN1_SY/2 - 25, 0.0},
						{WIN1_SX/2 + 100, WIN1_SY/2 + 100, -100.0}};
	double R[2] = {100.0, 100.0};
	
	double v[3];
	int i, j;
	i = 0;
	while (i < WIN1_SX)
	{
		j = 0;
		while (j < WIN1_SY)
		{
			v[0] = i + 0.5 - Pv[0];
			v[1] = j + 0.5 - Pv[1];
			v[2] = 0 - Pv[2];


			//discriminant
			double A, B2, C, D;
			double Pvc[3];
			double t;
			double t0;

			int k;
			int s0 = -1;
			int s = 0;
			A = inner_product(v, v);
			while (s < 2)
			{
				k = 0;
				while (k < 3)
				{
					Pvc[k] = Pv[k] - Pc[s][k];
					k++;
				}
				B2 = inner_product(Pvc, v);
				C = inner_product(Pvc, Pvc) - R[s] * R[s];
				D = B2 * B2 - A * C;
				if (D >= 0)
				{
					t = (-B2 - sqrt(D)) / A;
					if (s0 < 0 || t < t0)
					{
						s0 = s;
						t0 = t;
					}
				}
				s++;
			}
			
			//
			
			//intersection
			double P[3];
			k = 0;
			while (k < 3)
			{
				P[k] = Pv[k] + v[k] * t0;
				k++;
			}
			//

			//normal vector
			double PL[3] = {-20000, -20000, 20000};
			double N[3], vL[3];
			double cosA;
			k = 0;
			while (k < 3)
			{
				N[k] = P[k] - Pc[s0][k];
				k++;
			}
			k = 0;
			while (k < 3)
			{
				vL[k] = P[k] - PL[k];
				k++;
			}
			cosA = -inner_product(vL, N);
			cosA /= sqrt(inner_product(vL, vL) * inner_product(N, N));
			//

			//mirror
			double vR[3];
			double w, cosG;
			int n = 10;
			w = -inner_product(vL, N) / inner_product(N, N);
			k = 0;
			while (k < 3)
			{
				vR[k] = 2 * w * N[k] + vL[k];
				k++;
			}
			cosG = -inner_product(vR, v) / sqrt(inner_product(vR, vR) * inner_product(v, v));
			if (cosG < 0)
				cosG = 0;
			cosG = pow(cosG, n);

			//mix output
			double Kd = 1.0, Ks = 0.7, Ie = 0.1, I = 255.0;
			double RGB[2][3] = {{255, 0, 0}, {0, 255, 0}};
			double color_array[3];
			if (s0 >= 0)
			{
				k = 0;
				while (k < 3)
				{
					color_array[k] = RGB[s0][k] * Kd * cosA;
					if (color_array[k] < I * Ks * cosG)
						color_array[k] = I * Ks * cosG;
					if (color_array[k] < RGB[s0][k] * Ie)
						color_array[k] = RGB[s0][k] * Ie;
					k++;
				}
				color =  ((int)(color_array[0])<<16) + ((int)(color_array[1])<<8) + (int)(color_array[2]);
				mlx_pixel_put(mlx, win1, i, j, color);
			}
			else
			{
				color =  (0<<16) + (0<<8) + (127);
				mlx_pixel_put(mlx, win1, i, j, color);
			}
			j++;
		}
		i++;
	}
}

void	sphere4()
{
	int color;

	double Pv[3] = {WIN1_SX/2, WIN1_SY/2, 2000.0};
	double Pc[3] = {WIN1_SX/2, WIN1_SY/2, 0.0};
	double R = 100.0;

	double v[3];
	int i, j;
	i = 0;
	while (i < WIN1_SX)
	{
		j = 0;
		while (j < WIN1_SY)
		{
			v[0] = i + 0.5 - Pv[0];
			v[1] = j + 0.5 - Pv[1];
			v[2] = 0 - Pv[2];


			//discriminant
			double A, B2, C, D;
			double Pvc[3];
			int k;
			k = 0;
			while (k < 3)
			{
				Pvc[k] = Pv[k] - Pc[k];
				k++;
			}
			A = inner_product(v, v);
			B2 = inner_product(Pvc, v);
			C = inner_product(Pvc, Pvc) - R * R;
			D = B2 * B2 - A * C;
			//
			
			//intersection
			double P[3];
			double t0;
			t0 = (-B2 - sqrt(D)) / A;
			k = 0;
			while (k < 3)
			{
				P[k] = Pv[k] + v[k] * t0;
				k++;
			}
			//

			//normal vector
			double PL[3] = {-20000, -20000, 20000};
			double N[3], vL[3];
			double cosA;
			k = 0;
			while (k < 3)
			{
				N[k] = P[k] - Pc[k];
				k++;
			}
			k = 0;
			while (k < 3)
			{
				vL[k] = P[k] - PL[k];
				k++;
			}
			cosA = -inner_product(vL, N);
			cosA /= sqrt(inner_product(vL, vL) * inner_product(N, N));
			//

			//mirror
			double vR[3];
			double w, cosG;
			int n = 10;
			w = -inner_product(vL, N) / inner_product(N, N);
			k = 0;
			while (k < 3)
			{
				vR[k] = 2 * w * N[k] + vL[k];
				k++;
			}
			cosG = -inner_product(vR, v) / sqrt(inner_product(vR, vR) * inner_product(v, v));
			if (cosG < 0)
				cosG = 0;
			cosG = pow(cosG, n);

			//mix output
			double Kd = 1.0, Ks = 0.7, Ie = 0.1, I = 255.0;
			double RGB[3] = {255, 0, 0}, color_array[3];
			if (D >= 0)
			{
				k = 0;
				while (k < 3)
				{
					color_array[k] = RGB[k] * Kd * cosA;
					if (color_array[k] < I * Ks * cosG)
						color_array[k] = I * Ks * cosG;
					if (color_array[k] < RGB[k] * Ie)
						color_array[k] = RGB[k] * Ie;
					k++;
				}
				color =  ((int)(color_array[0])<<16) + ((int)(color_array[1])<<8) + (int)(color_array[2]);
				mlx_pixel_put(mlx, win1, i, j, color);
			}
			else
			{
				color =  (0<<16) + (0<<8) + (127);
				mlx_pixel_put(mlx, win1, i, j, color);
			}
			j++;
		}
		i++;
	}
}

void	sphere3()
{
	int color;

	double Pv[3] = {WIN1_SX/2, WIN1_SY/2, 2000.0};
	double Pc[3] = {WIN1_SX/2, WIN1_SY/2, 0.0};
	double R = 100.0;

	double v[3];
	int i, j;
	i = 0;
	while (i < WIN1_SX)
	{
		j = 0;
		while (j < WIN1_SY)
		{
			v[0] = i + 0.5 - Pv[0];
			v[1] = j + 0.5 - Pv[1];
			v[2] = 0 - Pv[2];


			//discriminant
			double A, B2, C, D;
			double Pvc[3];
			int k;
			k = 0;
			while (k < 3)
			{
				Pvc[k] = Pv[k] - Pc[k];
				k++;
			}
			A = inner_product(v, v);
			B2 = inner_product(Pvc, v);
			C = inner_product(Pvc, Pvc) - R * R;
			D = B2 * B2 - A * C;
			//
			
			//intersection
			double P[3];
			double t0;
			t0 = (-B2 - sqrt(D)) / A;
			k = 0;
			while (k < 3)
			{
				P[k] = Pv[k] + v[k] * t0;
				k++;
			}
			//

			//normal vector
			double PL[3] = {-20000, -20000, 20000};
			double N[3], vL[3];
			double cosA;
			k = 0;
			while (k < 3)
			{
				N[k] = P[k] - Pc[k];
				k++;
			}
			k = 0;
			while (k < 3)
			{
				vL[k] = P[k] - PL[k];
				k++;
			}
			cosA = -inner_product(vL, N);
			cosA /= sqrt(inner_product(vL, vL) * inner_product(N, N));
			//

			//mirror
			double vR[3];
			double w, cosG;
			int n = 10;
			w = -inner_product(vL, N) / inner_product(N, N);
			k = 0;
			while (k < 3)
			{
				vR[k] = 2 * w * N[k] + vL[k];
				k++;
			}
			cosG = -inner_product(vR, v) / sqrt(inner_product(vR, vR) * inner_product(v, v));
			if (cosG < 0)
				cosG = 0;
			cosG = pow(cosG, n);
			
			// output
			if (D >= 0)
			{
				if (cosG >= 0)
				{
					color =  ((int)(255 * cosG)<<16) + (0<<8) + (0);
					mlx_pixel_put(mlx, win1, i, j, color);
				}
				else
				{
					color =  (0<<16) + (0<<8) + (0);
					mlx_pixel_put(mlx, win1, i, j, color);
				}
			}
			else
			{
				color =  (0<<16) + (0<<8) + (127);
				mlx_pixel_put(mlx, win1, i, j, color);
			}
			j++;
		}
		i++;
	}
}
void	sphere2()
{
	int color;

	double Pv[3] = {WIN1_SX/2, WIN1_SY/2, 2000.0};
	double Pc[3] = {WIN1_SX/2, WIN1_SY/2, 0.0};
	double R = 100.0;

	double v[3];
	int i, j;
	i = 0;
	while (i < WIN1_SX)
	{
		j = 0;
		while (j < WIN1_SY)
		{
			v[0] = i + 0.5 - Pv[0];
			v[1] = j + 0.5 - Pv[1];
			v[2] = 0 - Pv[2];


			//discriminant
			double A, B2, C, D;
			double Pvc[3];
			int k;
			k = 0;
			while (k < 3)
			{
				Pvc[k] = Pv[k] - Pc[k];
				k++;
			}
			A = inner_product(v, v);
			B2 = inner_product(Pvc, v);
			C = inner_product(Pvc, Pvc) - R * R;
			D = B2 * B2 - A * C;
			//

			//intersection
			double P[3];
			double t0;
			t0 = (-B2 - sqrt(D)) / A;
			k = 0;
			while (k < 3)
			{
				P[k] = Pv[k] + v[k] * t0;
				k++;
			}
			//

			//normal vector
			double PL[3] = {-20000, -20000, 20000};
			double N[3], vL[3];
			double cosA;
			k = 0;
			while (k < 3)
			{
				N[k] = P[k] - Pc[k];
				k++;
			}
			k = 0;
			while (k < 3)
			{
				vL[k] = P[k] - PL[k];
				k++;
			}
			cosA = -inner_product(vL, N);
			cosA /= sqrt(inner_product(vL, vL) * inner_product(N, N));
			//

			// output
			if (D >= 0)
			{
				if (cosA >= 0)
				{
					color =  ((int)(255 * cosA)<<16) + (0<<8) + (0);
					mlx_pixel_put(mlx, win1, i, j, color);
				}
				else
				{
					color =  (0<<16) + (0<<8) + (0);
					mlx_pixel_put(mlx, win1, i, j, color);
				}
			}
			else
			{
				color =  (0<<16) + (0<<8) + (127);
				mlx_pixel_put(mlx, win1, i, j, color);
			}
			j++;
		}
		i++;
	}
}

void	sphere1()
{
	int color;

	double Pv[3] = {WIN1_SX/2, WIN1_SY/2, 2000.0};
	double Pc[3] = {WIN1_SX/2, WIN1_SY/2, 0.0};
	double R = 100.0;

	double v[3];
	int i, j;
	i = 0;
	while (i < WIN1_SX)
	{
		j = 0;
		while (j < WIN1_SY)
		{
			v[0] = i + 0.5 - Pv[0];
			v[1] = j + 0.5 - Pv[1];
			v[2] = 0 - Pv[2];


			//discriminant
			double A, B2, C, D;
			double Pvc[3];
			int k;
			k = 0;
			while (k < 3)
			{
				Pvc[k] = Pv[k] - Pc[k];
				k++;
			}
			A = inner_product(v, v);
			B2 = inner_product(Pvc, v);
			C = inner_product(Pvc, Pvc) - R * R;
			D = B2 * B2 - A * C;
			//


			if (D >= 0)
			{
				color =  (255<<16) + (0<<8) + (0);
				mlx_pixel_put(mlx, win1, i, j, color);
			}
			else
			{
				color =  (0<<16) + (0<<8) + (127);
				mlx_pixel_put(mlx, win1, i, j, color);
			}
			j++;
		}
		i++;
	}
}

void	color_map_1(void *win,int w,int h)
{
	int	x;
	int	y;
	int	color;
	
	x = w;
	while (x--)
	{
		y = h;
		while (y--)
		{
			// color = (x*255)/w+((((w-x)*255)/w)<<16)+(((y*255)/h)<<8);
			color =  (0<<16) + (100<<8) + (100);
			mlx_pixel_put(mlx,win,x,y,color);
		}
	}
  	mlx_clear_window(mlx,win1);
}
