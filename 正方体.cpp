//绘制立方体
#define GLUT_DISABLE_ATEXIT_HACK  
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <gl/glut.h>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES 
#include <math.h>

void display_wire(void);
int main(int argc, char **argv)
{

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(400, 400);//窗口的大小
	glutInitWindowPosition(100, 100);//窗口的位置
	glutCreateWindow("window");//直接创出窗口

	glutDisplayFunc(display_wire);
	glutMainLoop();
	return 0;

}
///绘制立方体的方法
void display_wire(void)
{
	GLdouble *points = NULL, *tmp = NULL;
	GLdouble i, j, distance = 0.4;
	int size = 4, length = 0;
	//用语存放顶点坐标
	points = (GLdouble *)malloc(sizeof(GLdouble)*size * 3);
	tmp = points;
	//给正方体的每个顶点赋值
	for (i = -0.4; i <= 0; i += 0.4)
	{

		for (j = 0; j <= 2 * M_PI; j += M_PI / 2)
		{
			length++;
			if (length>size)
			{
				size *= 2;
				points = (GLdouble *)realloc(points, sizeof(GLdouble)*size * 3);
				tmp = points + (size / 2) * 3;
			}

			*(tmp++) = distance*cos(j);
			*(tmp++) = i;
			*(tmp++) = distance*sin(j);

		}



	}

	//开启定点数组
	glEnableClientState(GL_VERTEX_ARRAY);
	//把point 座位定点数组的数据
	glVertexPointer(3, GL_DOUBLE, 0, points);

	glPushMatrix();

	glRotatef(30, 1, 0, 0);
	glBegin(GL_LINE_STRIP);
	for (size = 0; size<length; size++)
	{
		glArrayElement(size);
	}
	glEnd();

	//上面只是画了两个单独的正方形，所以需要加四条线
	glBegin(GL_LINES);
	for (size = 0; size<4; size++)
	{

		glVertex3f(points[size * 3], points[size * 3 + 1], points[size * 3 + 2]);
		glVertex3f(points[size * 3 + 5 * 3], points[size * 3 + 5 * 3 + 1], points[size * 3 + 2 + 5 * 3]);
	}

	glEnd();

	glPopMatrix();


	glutSwapBuffers();
}