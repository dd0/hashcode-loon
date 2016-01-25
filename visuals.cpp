#include "visuals.h"

void drawTile(CImg<unsigned char> &img, int i, int j, const unsigned char *col, double op = 1)
{
	img.draw_rectangle(j*DRAW_T+1, i*DRAW_T+1, j*DRAW_T+DRAW_T-1, i*DRAW_T+DRAW_T-1, col, op);
}

void drawPath(CImg<unsigned char> &img, int i, int j, int h, int t, const unsigned char *col)
{
	unsigned char endt[] = { 0,0,255 };
	while(t--)
	{
		int ii = i + data.wind[h].di[i][j];
		int jj = j + data.wind[h].dj[i][j];
		if(ii < 0 || ii >= data.n) break;
		if(jj >= 0 && jj < data.m)
			img.draw_line(j*DRAW_T+DRAW_T/2,i*DRAW_T+DRAW_T/2,jj*DRAW_T+DRAW_T/2,ii*DRAW_T+DRAW_T/2, col);
		i = ii; j = (jj + data.m) % data.m;
		if(t == 0) drawTile(img, i, j, endt);
	}
}

void drawWind(CImg<unsigned char> &img, int h, const unsigned char *col_l, const unsigned char *col_r, double op)
{
	for(int i = 0; i < data.n; i++)
		for(int j = 0; j < data.m; j++)
		{
			int ii = i + data.wind[h].di[i][j];
			int jj = j + data.wind[h].dj[i][j];
			if(ii < 0 || ii >= data.n) continue;
			if(jj >= data.m || jj < 0) continue;
//			jj = (jj + data.m) % data.m;
			
			img.draw_line(j*DRAW_T + DRAW_T/2, i*DRAW_T + DRAW_T/2, jj * DRAW_T + DRAW_T/2, ii * DRAW_T + DRAW_T/2, j < jj ? col_r : col_l, op);
		}
}

void drawGrid(CImg<unsigned char> &img)
{
	const unsigned char gray[] = {50, 50, 50};
	for(int i = 0; i <= data.n; i++)
		img.draw_line(0, i * DRAW_T, data.m * DRAW_T, i * DRAW_T, gray);
	for(int j = 0; j <= data.m; j++)
		img.draw_line(j * DRAW_T, 0, j * DRAW_T, data.n * DRAW_T, gray);
}

void drawShade(CImg<unsigned char> &img, int i, int j, const unsigned char *col, double op)
{
	for(int di = -data.rad; di <= data.rad; di++)
		for(int dj = - data.rad; dj <= data.rad; dj++)
			if(di * di + dj * dj <= data.rad * data.rad)
				img.draw_rectangle((j+dj) * DRAW_T + 1, (i+di) * DRAW_T + 1, (j+dj) * DRAW_T + DRAW_T - 1, (i+di) * DRAW_T + DRAW_T - 1, col, op);
}

tile next(tile x, int h)
{
	if(x.i == -1 || x.j == -1) return {-1,-1};
	int ii = x.i;
	x.i += data.wind[h].di[ii][x.j];
	x.j += data.wind[h].dj[ii][x.j];
	x.j = (x.j + data.m) % data.m;
	if(x.i < 0 || x.i >= data.n) return {-1,-1};
	return x;
}

bool hasLoop(int i, int j, int h, int t)
{
	tile a = {i,j}, x = {i,j};
	while(t--)
	{
		x = next(x, h);
		if(x.i == a.i && x.j == a.j)
			return true;
	}
	return false;
}

void drawEdge(CImg<unsigned char> &img, int i, int j, int ii, int jj, const unsigned char *col, double op)
{
	img.draw_line(j*DRAW_T + DRAW_T/2, i*DRAW_T + DRAW_T/2, jj * DRAW_T + DRAW_T/2, ii * DRAW_T + DRAW_T/2, col, op);
}

void drawLoops(CImg<unsigned char> &img, int h, const unsigned char *col, double op, int t)
{
	for(int i = 0; i < data.n; i++)
		for(int j = 0; j < data.m; j++)
			if(hasLoop(i, j, h, t))
			{
			   drawTile(img, i, j, col, op);
//			   drawEdge(img, i, j, next({i,j},h).i, next({i,j},h).j, col, op);
			}
}

const unsigned char *colLevel(int i)
{
	const unsigned char res[] = {127+127*((i+1)%2), 127+127*((i+1)/2%2), 127+127*((i+1)/4%2)};
	return res;
}

void drawTargets()
{	
	CImg<unsigned char> img(data.m * DRAW_T + 1, data.n * DRAW_T + 1, 1,3,0);

	const unsigned char green[] = { 0, 200, 0 } ;
	const unsigned char col_l[] = { 255, 0, 0};
	const unsigned char col_r[] = { 0, 255, 255};
	const unsigned char path[] = {255,0,255};
	const unsigned char shade[] = {255,255,0};
	const unsigned char source[] { 255,255,255 };
	const unsigned char pink[] = { 255, 129, 129};

//	img.save("C:\\Users\\Dimitrije\\Desktop\\loon.bmp");

	CImg<unsigned char> img_d(img.width(), img.height());
	img_d = img;
	CImgDisplay disp(img_d, "Targets");

	int len = 20;
	int lvl = 0;
	while(!disp.is_closed())
	{
		img_d = img;
		drawGrid(img_d);
		drawWind(img_d, lvl, col_l, col_r, 0.3);
		
		for(auto x : data.targets)
			img_d.draw_rectangle(x.j * DRAW_T + 1, x.i * DRAW_T + 1, x.j * DRAW_T + DRAW_T - 1, x.i * DRAW_T + DRAW_T - 1, green, 0.5);
		img_d.draw_rectangle(data.start.j * DRAW_T + 1, data.start.i * DRAW_T + 1, data.start.j * DRAW_T + DRAW_T - 1, data.start.i * DRAW_T + DRAW_T - 1, source, 0.6);

		if(disp.is_keyL()) drawLoops(img_d, lvl, pink, 0.8, len);
		
//		img_d.clear();
		if(disp.button() & 1)
		{
			int i = disp.mouse_y() / DRAW_T;
			int j = disp.mouse_x() / DRAW_T;

//			std::cout << i << " " << j << std::endl;
			
			drawPath(img_d, i, j, lvl, len, path);
		}

		if(disp.button() & 2)
		{
			int i = disp.mouse_y() / DRAW_T;
			int j = disp.mouse_x() / DRAW_T;
			drawShade(img_d, i, j, shade, 0.4);
		}
		
		if(disp.is_keyP() && len < 200) len++;
		if(disp.is_keyO() && len > 5) len--;
		if(disp.is_key0()) lvl = 0;
		else if(disp.is_key1()) lvl = 1;
		else if(disp.is_key2()) lvl = 2;
		else if(disp.is_key3()) lvl = 3;
		else if(disp.is_key4()) lvl = 4;
		else if(disp.is_key5()) lvl = 5;
		else if(disp.is_key6()) lvl = 6;
		else if(disp.is_key7()) lvl = 7;

		if(disp.is_keyK())
		{
			img_d.draw_text(0, 0, "len = %d", source, green, 0.5, 13, len);
			img_d.draw_text(0,15,"(i,j) = (%d,%d)", source, green, 0.5, 13, disp.mouse_y()/DRAW_T, disp.mouse_x()/DRAW_T);
		}

		if(disp.is_keyA())
		{
			for(int ll = 0; ll < (int)data.wind.size(); ll++)
				drawLoops(img_d, ll, colLevel(ll), 0.5, len);
		}
		
		img_d.display(disp);
		disp.wait();
	}
}
