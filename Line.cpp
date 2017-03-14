// Circle.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <GL/freeglut.h>
#include <iostream>
#include <math.h>
using namespace std;
#define ROUND(a) ((int)a+0.5)

#include "number.h"

void drawLine_dda(void) {
	glClearColor(1.0, 0.6, 0.6, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


	//int x1 = -20, y1 = -640, x2 = 80, y2 = 640;
	int dx, dy, steps;
	float x, y;
	x = cons.x1, y = cons.y1;
	float addx, addy;
	dx = cons.x2 - cons.x1;
	dy = cons.y2 - cons.y1;

	if (abs(dx) > abs(dy)) steps = abs(dx);
	else steps = abs(dy);
	addx = dx / (float)steps;
	addy = dy / (float)steps;

	cout << addx << " " << addy << endl;
	glPointSize(3);
	glBegin(GL_POINTS);
	
	glVertex2f(x / 640, y / 640);
	if (abs(addy) == 1) {
		for (int i = 0; addy*i + cons.y1 != cons.y2; i++) {
			x = addx + x;
			y = addy + y;
			glVertex2f(ROUND(x)/640 , ROUND(y)/640);
		}
	}

	if (abs(addx) == 1) {
		for (int i = 0; addx*i + cons.x1 != cons.x2; i++) {
			x = addx + x;
			y = addy + y;
			glVertex2f(ROUND(x)/640, ROUND(y)/640);
		}
	}
	glEnd();

	glutSwapBuffers();
}

//|m|<=1时分类不同情况的分类有阅读网络资料：http://blog.csdn.net/cp4wanger/article/details/7840688  
//无照搬代码
void drawLine_Bresenham(void) {
	glClearColor(1.0, 0.6, 0.6, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();


//	int x1 = -50, y1 = 80, x2 = 80, y2 = 640;
	float dx, dy, p, x, y;

	dx = cons.x2 - cons.x1;
	dy = cons.y2 - cons.y1;
	int flag = 0;
	if (abs(dy) > abs(dx)) {
		flag = 1;
	}

	p = 2 * abs(dy) - abs(dx);

	x = cons.x1, y = cons.y1;

	glPointSize(3);

	glBegin(GL_POINTS);
	glVertex2f(x / 640, y / 640);
	int ix = abs(dx) / dx;
	int iy = abs(dy) / dy;
	if (flag == 0) {
		for (float i = 0; i*ix + cons.x1 != cons.x2; i++) {
			x += ix;
			if (p <= 0) {
				glVertex2f(x / 640, y / 640);
				p = p + 2 * abs(dy);
			}
			else {
				y += iy;
				glVertex2f(x / 640, y / 640);
				p = p + 2 * abs(dy) - 2 * abs(dx);
			}
		}
	}
	if (flag == 1) {
		for (float i = 0; i*iy + cons.y1 != cons.y2; i++) {
			y += iy;
			if (p <= 0) {
				glVertex2f(x / 640, y / 640);
				p = p + 2 * abs(dx);
			}
			else {
				x += ix;
				glVertex2f(x / 640, y / 640);
				p = p + 2 * abs(dx) - 2 * abs(dy);
			}
		}
	}
	glEnd();


	glutSwapBuffers();
}


//详细算法讲解参考http://blog.csdn.net/mmogega/article/details/53055625
//无照搬代码
void drawcircle_Bresenham() {
	glPointSize(3);
	glBegin(GL_POINTS);
	glVertex2f(ccons.x/640, ccons.y/640);
	float endx, endy = ccons.r;
	float d = 5 - 4 * ccons.r;
	for (endx = 0; endx <= endy; endx++) { //因为对称，以x为标准
		glVertex2f((-endx + ccons.x) / 640, (-endy + ccons.y) / 640);
		glVertex2f((endx + ccons.x) / 640, (-endy + ccons.y) / 640);
		glVertex2f((-endx + ccons.x) / 640, (endy + ccons.y) / 640);
		glVertex2f((endx + ccons.x) / 640, (endy + ccons.y) / 640);

		glVertex2f((-endy + ccons.x) / 640, (-endx + ccons.y) / 640);
		glVertex2f((endy + ccons.x) / 640, (-endx + ccons.y) / 640);
		glVertex2f((-endy + ccons.x) / 640, (endx + ccons.y) / 640);
		glVertex2f((endy + ccons.x) / 640, (endx + ccons.y) / 640);

		if (d < 0) {
			d += 2 * endx + 3;
		}
		else {
			d += 2 * (endx - endy ) + 5;
			endy--;
		}
	}
	glEnd();

	glutSwapBuffers();
}

int main(int argc, char *argv[]) {
	int flag;
	cout << "画圆请输入0，画直线请输入1" << endl;
	cin >> flag;
	if (flag == 1) {
		cout << "请输入起始点坐标x1, y1. -640 <= x1, y1 <= 640" << endl;
		cin >> cons.x1 >> cons.y1;
		cout << "请输入结束点坐标x1, y1. -640 <= x1, y1 <= 640" << endl;
		cin >> cons.x2 >> cons.y2;
	}
	else {
		cout << "请输入圆中点坐标, -640 <= x, y <= 640" << endl;
		cin >> ccons.x >> ccons.y;
		cout << "请输入圆的半径" << endl;
		cin >> ccons.r;
	}


	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 640);
	glutCreateWindow("drawLine");
	if (flag == 1) {
		//glutDisplayFunc(drawLine_Bresenham);
		glutDisplayFunc(drawLine_dda);
	}
	else {
		glutDisplayFunc(drawcircle_Bresenham);
	}
	glutMainLoop();
	return 0;
}