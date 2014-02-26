/* simple painting program with text, lines, triangles,
rectangles, and points */

/************************************************
* Modified by: Aron Roberts
* CECS 449
* due: 2/25/2014
* description: Modified paint program to  meet specified course requirements.
* some code reduction by seperating redundant code into function calls
* simple example of how to use open_GL to create some "fun" projects.
*
************************************************/

#define NULL 0
#define LINE 1
#define RECTANGLE 2
#define TRIANGLE 3
#define POINTS 4
#define TEXT 5
#define CIRCLE 6
#define ZIGZAG 7

#include <cstdlib>
#include <GL\glut.h> 
#include <math.h>


void mouse(int, int, int, int);
void key(unsigned char, int, int);
void display();
void drawPoint(int, int);
void drawCircle(int, int);
void myReshape(GLsizei, GLsizei);
void myinit();
void screen_box(int, int, int);
void right_menu(int);
void middle_menu(int);
void color_menu(int);
void pixel_menu(int);
void fill_menu(int);
int pick(int, int);


/* globals */

GLsizei wh = 500, ww = 500; /* initial window size */
GLfloat size = 3.0;   /* half side length of square */
int draw_mode = 0; /* drawing mode */
int rx, ry; /*raster position*/

GLfloat r = 1.0, g = 1.0, b = 1.0; /* drawing color */
int fill = 0; /* fill flag */



/******************************
* drawing Functions
******************************/

/* draw line */
void drawLine(int x1[], int y1[])
{
	glBegin(GL_LINES);
	 glVertex2i(x1[1],wh-y1[1]);
	 glVertex2i(x1[0],wh-y1[0]);
	glEnd();
}

/* draw rectangle */
void drawRect( int x1[], int y1[])
{
	if(fill) glBegin(GL_POLYGON);
	else glBegin(GL_LINE_LOOP);
	 glVertex2i(x1[1],wh-y1[1]);
     glVertex2i(x1[1],wh-y1[0]);
     glVertex2i(x1[0],wh-y1[0]);
     glVertex2i(x1[0],wh-y1[1]);
    glEnd();
    
}

/* draw triangle */
void drawTriangle(int x1[], int y1[])
{
	if(fill) glBegin(GL_POLYGON);
    else glBegin(GL_LINE_LOOP);
      glVertex2i(x1[0],wh-y1[0]);
      glVertex2i(x1[1],wh-y1[1]);
      glVertex2i(x1[2],wh-y1[2]);
    glEnd();
}

/* draw dots */
void drawPoint(int x, int y)
{
        y=wh-y;
        //glColor3f( r, g, b);
        glBegin(GL_POLYGON);
                glVertex2f(x+size, y+size);
                glVertex2f(x-size, y+size);
                glVertex2f(x-size, y-size);
                glVertex2f(x+size, y-size);
        glEnd();
}


/* draw circle */
void drawCircle(int x, int y,int r)
{
	int radius=r;
	double pi = 3.14159;

	if(fill) glBegin(GL_POLYGON);
	else glBegin(GL_LINE_LOOP);
	 for(double angle=0; angle < 2*pi; angle= angle+0.02)
			 glVertex2f(x+sin(angle)*radius, wh-y+cos(angle)*radius);	
	glEnd();
}

/* reshaping routine called whenever window is resized or moved */
void myReshape(GLsizei w, GLsizei h)
{

/* adjust clipping box */

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, (GLdouble)w, 0.0, (GLdouble)h, -1.0, 1.0);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();

/* adjust viewport and clear */

        glViewport(0,0,w,h);
        glClearColor (0.8, 0.8, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        display();
        glFlush();

/* set global size for use by drawing routine */

        ww = w;
        wh = h;
}

void myinit()
{

 glViewport(0,0,ww,wh);


/* Pick 2D clipping window to match size of X window. This choice
avoids having to scale object coordinates each time window is
resized. */

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        glOrtho(0.0, (GLdouble) ww , 0.0, (GLdouble) wh , -1.0, 1.0);

/* set clear color to black and clear window */

        glClearColor (0.8, 0.8, 0.8, 1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
}

void drawMenu()
{
	/* set color */
	int shift=0;
    glColor3f(0.0, 0.0, 0.0);

	/*draw top boxes*/
    screen_box(0,wh-ww/10,ww/10);
    screen_box(ww/10,wh-ww/10,ww/10);
    screen_box(ww/5,wh-ww/10,ww/10);
    screen_box(3*ww/10,wh-ww/10,ww/10);
    screen_box(2*ww/5,wh-ww/10,ww/10);
	screen_box(ww/2,wh-ww/10,ww/10);
	screen_box(3*ww/5,wh-ww/10,ww/10);


	/*******************
	* draw menu shapes
	********************/
    glBegin(GL_LINES);
       glVertex2i(wh/40,wh-ww/20);
       glVertex2i(wh/40+ww/20,wh-ww/20);
    glEnd();

	glBegin(GL_QUADS);
		glVertex2i(ww/10+ww/40,wh-ww/10+ww/40);
		glVertex2i(ww/10+ww/40,wh-ww/10+3*ww/40);
		glVertex2i(ww/10+3*ww/40,wh-ww/10+3*ww/40);
		glVertex2i(ww/10+3*ww/40,wh-ww/10+ww/40);
	glEnd();
	
    glBegin(GL_TRIANGLES);
       glVertex2i(ww/5+ww/40,wh-ww/10+ww/40);
       glVertex2i(ww/5+ww/20,wh-ww/40);
       glVertex2i(ww/5+3*ww/40,wh-ww/10+ww/40);
    glEnd();

    glPointSize(3.0);
    glBegin(GL_POINTS);
       glVertex2i(3*ww/10+ww/20, wh-ww/20);
    glEnd();

    glRasterPos2i(2*ww/5,wh-ww/20);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'A');
    shift=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'A');
    glRasterPos2i(2*ww/5+shift,wh-ww/20);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'B');
    shift+=glutBitmapWidth(GLUT_BITMAP_9_BY_15, 'B');
    glRasterPos2i(2*ww/5+shift,wh-ww/20);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, 'C');


	drawCircle((ww/2+ww/20),(ww/20), ww/30);

	glBegin(GL_LINE_STRIP);
		glVertex2f(3*ww/5+4,wh-ww/80);
		glVertex2f(3*ww/5+ww/10-4,wh-ww/40);
		//glVertex2f(3*ww/5+ww/10-4,wh-ww/40);
		glVertex2f(3*ww/5+4,wh-ww/20);
		//glVertex2f(3*ww/5+4,wh-ww/20);
		glVertex2f(3*ww/5+ww/10-4,wh-ww/10);
	glEnd();
}

/***************************************
* Tracks Mouse Clicks to select a shape or set control points.
*****************************************/
void mouse(int btn, int state, int x, int y)
{
    static int count; //track number of current control points
    int where; 
    static int xp[3],yp[3]; // arrays to hold control points
    if(btn==GLUT_LEFT_BUTTON && state==GLUT_DOWN)
    {
       glPushAttrib(GL_ALL_ATTRIB_BITS);
       where = pick(x,y);
       glColor3f(r, g, b);
       if(where != 0)
       {
          count = 0;
          draw_mode = where;
       }
       else switch(draw_mode)
       {
         case(LINE):
          if(count==0)
          {
              xp[0] = x;
              yp[0] = y;
			  count++;
			  drawPoint(x,y);
          }
          else
          {
			  xp[1] = x;
              yp[1] = y;
			  drawPoint(x,y);
			  drawLine(xp,yp);
              draw_mode=0;
              count=0;
          }
          break;
        case(RECTANGLE):
          if(count == 0)
          {
              
              xp[0] = x;
              yp[0] = y;
			  count++;
			  drawPoint(x,y);

          }
          else
          {
			  drawPoint(x,y);
			  xp[1] = x;
              yp[1] = y;
			  drawRect(xp,yp);
              draw_mode=0;
              count=0;
          }
          break;
        case (TRIANGLE):
          switch(count)
          {
            case(0):
              count++;
			  drawPoint(x,y);
              xp[0] = x;
              yp[0] = y;
              break;
            case(1):
              count++;
			  drawPoint(x,y);
              xp[1] = x;
              yp[1] = y;
              break;
            case(2):
				drawPoint(x,y);
				xp[2] = x;
				yp[2] = y;
				drawTriangle(xp,yp);
              draw_mode=0;
              count=0;
          }
          break;
        case(POINTS):
          {
             drawPoint(x,y);
             count=0;
			 draw_mode=0;
          }
		break;
		case(TEXT):
		{
			rx=x;
			ry=wh-y;
			glRasterPos2i(rx,ry);
			count=0;
		}
		break;
		case(CIRCLE):
			if(count==0)
			{
              xp[0] = x;
              yp[0] = y;
			  count++;
			  drawPoint(x,y);
			}
			else
			{
			  drawPoint(x,y);
			  drawCircle(xp[0],yp[0],sqrt(pow((float)x-xp[0],2)+pow((float)y-yp[0],2)));
			  draw_mode=0;
              count=0;
			}
          break;
		
		case(ZIGZAG):
		{
		  switch(count){
			case(0):
              xp[0] = x;
              yp[0] = y;
			  count++;
			  drawPoint(x,y);
			 break;

			case(1):
			  xp[1] = x;
              yp[1] = y;
			  count++;
			  drawPoint(x,y);
			  drawLine(xp,yp);
			  break;
			
			default:
			  xp[0] = xp[1];
              yp[0] = yp[1];
			  xp[1] = x;
              yp[1] = y;
			  if (xp[0]==xp[1] || yp[0]==yp[1])
			  {
				  count=0;
				  draw_mode=0;
				  break;
			  }
			  drawPoint(x,y);
			  count++;
			  drawLine(xp,yp);
		  }

		}

       }
	   if (!draw_mode) drawMenu();

       glPopAttrib();
       glFlush();
     }
}

/***************
* Mouse select Shape
****************/
int pick(int x, int y)
{
    y = wh - y;
	glColor3f(r,g,b);
    if(y < wh-ww/10) return 0;
    else if(x < ww/10)
	{
		glBegin(GL_LINES);
			glVertex2i(wh/40,wh-ww/20);
			glVertex2i(wh/40+ww/20,wh-ww/20);
		glEnd();
		glColor3f(1,1,0); 
	   screen_box(0,wh-ww/10,ww/10);
	   glColor3f(r,g,b);
		return LINE;

	}
    else if(x < ww/5)
	{
		glBegin(GL_QUADS);
			glVertex2i(ww/10+ww/40,wh-ww/10+ww/40);
			glVertex2i(ww/10+ww/40,wh-ww/10+3*ww/40);
			glVertex2i(ww/10+3*ww/40,wh-ww/10+3*ww/40);
			glVertex2i(ww/10+3*ww/40,wh-ww/10+ww/40);
		glEnd();
		glColor3f(1,1,0); 
	   screen_box(ww/10,wh-ww/10,ww/10);
	   glColor3f(r,g,b);
		return RECTANGLE;
	}
    else if(x < 3*ww/10) 
	{
		glBegin(GL_TRIANGLES);
			glVertex2i(ww/5+ww/40,wh-ww/10+ww/40);
			glVertex2i(ww/5+ww/20,wh-ww/40);
			glVertex2i(ww/5+3*ww/40,wh-ww/10+ww/40);
		glEnd();		
	   glColor3f(1,1,0); 
	   screen_box(ww/5,wh-ww/10,ww/10);
	   glColor3f(r,g,b);
    
		return TRIANGLE;
	}
    else if(x < 2*ww/5) 
	{
		glPointSize(3.0);
			glBegin(GL_POINTS);
			glVertex2i(3*ww/10+ww/20, wh-ww/20);
		glEnd();
	   glColor3f(1,1,0); 
	    screen_box(3*ww/10,wh-ww/10,ww/10);
	   glColor3f(r,g,b);
		return POINTS;
	}
	else if(x < ww/2){
		 glColor3f(1,1,0); 
	   screen_box(2*ww/5,wh-ww/10,ww/10);
	   glColor3f(r,g,b);
	   return TEXT;}
	else if(x < 3*ww/5) 
	{
		drawCircle((ww/2+ww/20),(ww/20), ww/30);
		glColor3f(1,1,0);
	   screen_box(ww/2,wh-ww/10,ww/10);
	   glColor3f(r,g,b);
	  
    
		return CIRCLE;
	}
	else if(x < 7*ww/10)
	{
		glBegin(GL_LINE_STRIP);
		glVertex2f(3*ww/5+4,wh-ww/80);
		glVertex2f(3*ww/5+ww/10-4,wh-ww/40);
		glVertex2f(3*ww/5+4,wh-ww/20);
		glVertex2f(3*ww/5+ww/10-4,wh-ww/10);
		glEnd();

		glColor3f(1,1,0);
		screen_box(3*ww/5,wh-ww/10,ww/10);
	    glColor3f(r,g,b);
	  
       	screen_box(3*ww/5,wh-ww/10,ww/10);
		return ZIGZAG;
	}
    else return 0;
}


/* Boxes used for menu */
void screen_box(int x, int y, int s )
{
    glBegin(GL_LINE_LOOP);
      glVertex2i(x, y);
      glVertex2i(x+s, y);
      glVertex2i(x+s, y+s);
      glVertex2i(x, y+s);
    glEnd();
}

/******************
* Menus
*******************/
void right_menu(int id)
{
   if(id == 1) exit(0);
   else display();
}

void middle_menu(int id)
{

}

void color_menu(int id)
{
   if(id == 1) {r = 1.0; g = 0.0; b = 0.0;} // red
   else if(id == 2) {r = 0.0; g = 1.0; b = 0.0;} // green
   else if(id == 3) {r = 0.0; g = 0.0; b = 1.0;} // blue
   else if(id == 4) {r = 0.0; g = 1.0; b = 1.0;} // cyan
   else if(id == 5) {r = 1.0; g = 0.0; b = 1.0;} //magenta
   else if(id == 6) {r = 1.0; g = 1.0; b = 0.0;} // yellow
   else if(id == 7) {r = 1.0; g = 1.0; b = 1.0;} // white
   else if(id == 8) {r = 0.0; g = 0.0; b = 0.0;} //black
}

void pixel_menu(int id)
{
   if (id == 1) size = 2 * size;
   else if (size > 1) size = size/2;
}

void fill_menu(int id)
{
   if (id == 1) fill = 1;
   else fill = 0;
}


/**************************************
* Use keyboard to select color or fill
***************************************/
void key(unsigned char k, int xx, int yy) 
{

   if(draw_mode!=TEXT){
	    if (k == 'r') color_menu(1); //red
		if (k == 'g') color_menu(2); //green
		if (k == 'b') color_menu(3); //blue
		if (k == 'c') color_menu(4); //cyan
		if (k == 'm') color_menu(5); //magenta
		if (k == 'y') color_menu(6); //yellow
		if (k == 'w') color_menu(7); //white
		if (k == 'k') color_menu(8); //black
		if (k == 'f') { if (fill) fill_menu(0);
						else fill_menu(1);}//fill
		return;
   }

  glColor3f(r,g,b);
   glRasterPos2i(rx,ry);
   glutBitmapCharacter(GLUT_BITMAP_9_BY_15, k);
 /*glutStrokeCharacter(GLUT_STROKE_ROMAN,i); */
   rx+=glutBitmapWidth(GLUT_BITMAP_9_BY_15,k);

}

/* main display function */
void display()
{

    glPushAttrib(GL_ALL_ATTRIB_BITS);
    glClearColor (0.9, 0.9, 0.9, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
	drawMenu();
    glFlush();
    glPopAttrib();
}


/* MAIN!!!**/
int main(int argc, char** argv)
{
    int c_menu, p_menu, f_menu;

    glutInit(&argc,argv);
    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutCreateWindow("square");
    glutDisplayFunc(display);
    c_menu = glutCreateMenu(color_menu);
    glutAddMenuEntry("Red",1);
    glutAddMenuEntry("Green",2);
    glutAddMenuEntry("Blue",3);
    glutAddMenuEntry("Cyan",4);
    glutAddMenuEntry("Magenta",5);
    glutAddMenuEntry("Yellow",6);
    glutAddMenuEntry("White",7);
    glutAddMenuEntry("Black",8);
    p_menu = glutCreateMenu(pixel_menu);
    glutAddMenuEntry("increase pixel size", 1);
    glutAddMenuEntry("decrease pixel size", 2);
    f_menu = glutCreateMenu(fill_menu);
    glutAddMenuEntry("fill on", 1);
    glutAddMenuEntry("fill off", 2);
    glutCreateMenu(right_menu);
    glutAddMenuEntry("quit",1);
    glutAddMenuEntry("clear",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    glutCreateMenu(middle_menu);
    glutAddSubMenu("Colors", c_menu);
    glutAddSubMenu("Pixel Size", p_menu);
    glutAddSubMenu("Fill", f_menu);
    glutAttachMenu(GLUT_MIDDLE_BUTTON);
    myinit ();
    glutReshapeFunc (myReshape);
    glutKeyboardFunc(key);
    glutMouseFunc (mouse);
    glutMainLoop();

}
