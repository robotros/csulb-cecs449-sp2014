/*********************
 * Author Aron Roberts
 * CECS 449
 * Burundi Flag in open GL
 * Due: 2/6/2014        
 ********************/


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>

int Width= 1200, Height=750;

/*draw a triangle */
void drawTriangle(float *v1, float *v2, float *v3)
{
	glBegin(GL_TRIANGLES);
	glVertex2fv(v1);
	glVertex2fv(v2);
	glVertex2fv(v3);
	glEnd();
}

/* draw a circle with center and radius of radius */
void drawCircle(float *center, float radius)
{
	float pi = 3.14159;
	glBegin(GL_TRIANGLE_FAN);
	 glVertex2fv(center);
	 for (double angle=0; angle < 2*pi; angle=angle + 0.002)
	 {
		 glVertex2f(center[0]+sin(angle)*radius, center[1]+cos(angle)*radius);
	 }
	glEnd();
}

/* draw green triangles */
void drawGreenTriangles()
{
	/* Green Triangles */
	glColor3f(0,1,0);

	/* Triangle 1 Vertex */
	float v1[2], v2[2], v3[2];
	v1[0]=570;
	v1[1]=400;
	v2[0]=100;
	v2[1]=620;
	v3[0]=100;
	v3[1]=180;

	/* Triangle 2 Vertex */
	float v4[2], v5[2], v6[2];
	v4[0]=630;
	v4[1]=400;
	v5[0]=1100;
	v5[1]=620;
	v6[0]=1100;
	v6[1]=180;

	/*draw triangles*/
	drawTriangle(v1, v2, v3);
	drawTriangle(v4, v5, v6);
}

/* draw red triangles */
void drawRedTriangles()
{
	/* Red Triangles */
	glColor3f(1,0,0);

	/* Triangle 1 Vertex */
	float v1[2], v2[2], v3[2];
	v1[0]=600;
	v1[1]=440;
	v2[0]=140;
	v2[1]=650;
	v3[0]=1060;
	v3[1]=650;

	/* Triangle 2 Vertex */
	float v4[2], v5[2], v6[2];
	v4[0]=600;
	v4[1]=360;
	v5[0]=1060;
	v5[1]=150;
	v6[0]=140;
	v6[1]=150;

	/*draw triangles*/
	drawTriangle(v1, v2, v3);
	drawTriangle(v4, v5, v6);
}
	
/* draw a 6 pointed start centered at (x,y) */
void drawStar(float x, float y)
{
	double pi= 3.14159;
	int radius1=50, radius2=25;
	int radius= radius2;

	/* draw red star */
	glColor3f(1,0,0);
	glBegin(GL_POLYGON);
	 for (double angle =0; angle < 2*pi; angle = angle + (pi/6))
	 {
		 glVertex2f(x+sin(angle)*radius, y+cos(angle)*radius);
		 if (radius==radius1)
			 radius=radius2;
		 else
			 radius=radius1;
	 }	 
	glEnd();

	/* draw green outline */

	 if (radius==radius1)
		radius=radius2;
	 else
		radius=radius1;
	glColor3f(0,1,0);
	glBegin(GL_LINE_LOOP);
	 for (double angle =0; angle < 2*pi; angle = angle + (pi/6))
	 {
		 glVertex2f(x+sin(angle)*radius, y+cos(angle)*radius);
		 if (radius==radius1)
			 radius=radius2;
		 else
			 radius=radius1;
	 }	 
	glEnd();

}

/* draw 3 Stars in a circle centered at center */
void drawStars(float *center)
{
	double pi= 3.14159;
	int radius= 75;

	 for (double angle =0; angle < 2*pi; angle = angle + (pi/1.5))
	 {
		drawStar(center[0]+sin(angle)*radius, center[1]+cos(angle)*radius);
	 }	 
	
}

/* draw flag outline */
void drawFlageOutline()
{
	/*Flag outline*/
	glColor3f(0,0,0);
	glBegin(GL_LINE_LOOP);
	 glVertex2f(100,150);
	 glVertex2f(100,650);
	 glVertex2f(1100,650);
	 glVertex2f(1100,150);
	glEnd();
}

/*write out Burundi using lines*/
void burundi()
{
	glBegin(GL_LINES);
	//B
	 glVertex2f(130,50);
	 glVertex2f(130,100);
	//U
	 glVertex2f(200,50);
	 glVertex2f(200,100);

	 glVertex2f(200,50);
	 glVertex2f(250,50);

	 glVertex2f(250,50);
	 glVertex2f(250,100);

	//R
	 glVertex2f(300,50);
	 glVertex2f(300,100);

	 glVertex2f(300,100);
	 glVertex2f(350,100);

	//U
	 glVertex2f(400,50);
	 glVertex2f(400,100);

	 glVertex2f(400,50);
	 glVertex2f(450,50);

	 glVertex2f(450,50);
	 glVertex2f(450,100);

	//N
	 glVertex2f(500,50);
	 glVertex2f(500,100);

	 glVertex2f(500,100);
	 glVertex2f(550,50);

	 glVertex2f(550,50);
	 glVertex2f(550,100);
	
	//D
	 glVertex2f(600,50);
	 glVertex2f(600,100);

	//I
	 glVertex2f(700,50);
	 glVertex2f(700,100);
	 glEnd();

	 //clean up letters with LINE_LOOP
	 float pi = 3.14159;
	 //B
	 float radius=12;
	glBegin(GL_LINE_LOOP);
	 for (double angle=0; angle < pi; angle=angle + 0.002)
	 {
		 glVertex2f(130+sin(angle)*radius, 63+cos(angle)*radius);
	 }
	glEnd();

	glBegin(GL_LINE_LOOP);
	 for (double angle=0; angle < pi; angle=angle + 0.002)
	 {
		 glVertex2f(130+sin(angle)*radius, 87+cos(angle)*radius);
	 }
	glEnd();

	//D
	radius = 25;
	glBegin(GL_LINE_LOOP);
	 for (double angle=0; angle < pi; angle=angle + 0.002)
	 {
		 glVertex2f(600+sin(angle)*radius, 75+cos(angle)*radius);
	 }
	 glEnd();
}

/* initialize window and view */
void init()
{
	glClearColor(1,1,1,0);
	glMatrixMode (GL_PROJECTION);
	glOrtho(0, 1200, 0, 750, -1.0, 1.0);

}

/* draw display */
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	float center[2];
	center[0]=600;
	center[1]=400;

	drawGreenTriangles();
	drawRedTriangles();
	glColor3f(1,1,1);
	drawCircle(center, 150);
	drawStars(center);
	drawFlageOutline();
	burundi();


	glFlush();
}

/* main */
int main(int argc, char **argv)
{

glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
glutInitWindowSize(Width, Height);
glutCreateWindow("Burundi Flag");
glutDisplayFunc(display);
init();
glutMainLoop();
}