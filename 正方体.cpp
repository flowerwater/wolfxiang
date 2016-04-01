//����������
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
	glutInitWindowSize(400, 400);//���ڵĴ�С
	glutInitWindowPosition(100, 100);//���ڵ�λ��
	glutCreateWindow("window");//ֱ�Ӵ�������

	glutDisplayFunc(display_wire);
	glutMainLoop();
	return 0;

}
///����������ķ���
void display_wire(void)
{
	GLdouble *points = NULL, *tmp = NULL;
	GLdouble i, j, distance = 0.4;
	int size = 4, length = 0;
	//�����Ŷ�������
	points = (GLdouble *)malloc(sizeof(GLdouble)*size * 3);
	tmp = points;
	//���������ÿ�����㸳ֵ
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

	//������������
	glEnableClientState(GL_VERTEX_ARRAY);
	//��point ��λ�������������
	glVertexPointer(3, GL_DOUBLE, 0, points);

	glPushMatrix();

	glRotatef(30, 1, 0, 0);
	glBegin(GL_LINE_STRIP);
	for (size = 0; size<length; size++)
	{
		glArrayElement(size);
	}
	glEnd();

	//����ֻ�ǻ������������������Σ�������Ҫ��������
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