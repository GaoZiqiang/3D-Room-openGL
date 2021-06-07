/*****************************************************************************
        FILE : submit.c (Assignment 1)
        NOTE : you have to implement functions in this file
*****************************************************************************/
/*****************************************************************************
		Student Information
		Student ID: 
		Student Name: 
*****************************************************************************/

#include <stdlib.h>
#include <GL/glut.h>
const GLdouble FRUSTDIM = 100.0f;

int option = 0, i = 0;
bool enableLight = 1;

/* Do  animation*/
GLfloat angle = 0,tea_p = -40 , tea_face = 100 , donut_size = 3 , seat_pos = -60, board_pos = 65;
GLUquadricObj *quadobj;

/* For lighting*/
GLfloat light0pos[] = {0.0f, 76.f, 0.f, 0.f};
GLfloat light0_mat1[] = {1.0, 1.0, 1.0, 1.f};
GLfloat light0_diff[] = {1.0, 1.0, 1.0, 0.3};

void init(void) // All Setup For OpenGL Goes Here 
{
	/* Light 0 Settings */

	glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);

	quadobj = gluNewQuadric();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);		/* Define Counter-Clockwise as front face */

	glEnable(GL_COLOR_MATERIAL);
}

void display(void) // Here's Where We Do All The Drawing
{
	/* Clear the buffer */
	glClearColor(0.0, 0.0, 0.0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0, 0, -550);
 
	/* Initialize material properties */
	GLfloat no_mat[] = {0.0,0.0,0.0,1.0};
	GLfloat mat_diffuse[] = {0.9,0.9,0.9,1.0};
	GLfloat mat_specular[] = {0.3,0.3,0.3,1.0};
	GLfloat high_shininess[] = {20.0};
	GLfloat high_mat[] = {1.0,1.0,1.0,1.0};


	glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);


	/* Draw a Table START */
	glPushMatrix();
		glTranslatef(0.f, 0.f,70.f);

		/* Draw a support for table */
		glPushMatrix();
			glColor3f(0.168f, 0.23f, 1.0f);
			glTranslatef(0.f, -90.f, 130.f);
			glRotatef(-90, 1.f, 0.f, 0.f);
			gluCylinder(quadobj, 10.f, 5.f, 40.f, 20.f, 20.f);
		glPopMatrix();

		/* form the table (cyclinder part) */
		glPushMatrix();
			glColor3f(0.168f, 0.23f, 1.0f);
			glTranslatef(0.f, -50.f, 130.f);
			glRotatef(-90, 1.f, 0.f, 0.f);
			gluCylinder(quadobj, 50.f, 50.f, 10.2f, 30.f, 30.f);
		glPopMatrix();

		/*form the table (upper part) */
		glPushMatrix();
			glColor3f(0.168f, 0.23f, 1.0f);
			glTranslatef(0.f, -40.f, 130.f);
			glRotatef(-90, 1.f, 0.f, 0.f);
			gluDisk(quadobj, 0.f, 50.7f, 20.f, 20.f);
		glPopMatrix();

		/* Rotate with angle */
		glTranslatef(0.f, -40.f, 130.f);
		glRotatef(angle, 0.f, 1.f, 0.f);

		/*Draw a teapot on table */
		glPushMatrix();
			glColor4f(0.5f, 0.0f, 0.0f,0.5f);
			glTranslatef(-30.f, 10.f, 0.f);
			glRotatef(-90.f, 0.f, 1.f, 0.f);
			glScalef(100.f, 100.0f, -100.f);
			glutSolidTeapot(0.1);
		glPopMatrix();

		/*Draw a plate*/
		glPushMatrix();
			glColor3f(0.7f, 0.7f, 0.7f);
			glTranslatef(30.f, 0.f, 0.f);
			glRotatef(-90, 1.f, 0.f, 0.f);
			gluCylinder(quadobj, 3.f, 10.f, 2.f, 30.f, 30.f);
		glPopMatrix();

		/*Draw a donut*/
		glPushMatrix();
			glColor3f(0.4f, 0.20f, 0.f);
			glTranslatef(30.f,donut_size, 0.f);
			glRotatef(-90.f, 1.f, 0.f, 0.f);	
			glutSolidTorus(donut_size - 1 , donut_size, 110.f, 110.f);
		glPopMatrix();

	glPopMatrix();
	/* draw a table END */

	/* pull or push the seat*/
	glTranslatef(seat_pos, -100.f, 98.f);

	/*Draw seat START*/
	glPushMatrix();
		glColor3f(0.0f, 0.25f, 0.0f);
		glTranslatef(0.f,0.f,0.f);
		glRotatef(-90, 1.f, 0.f, 0.f);
		gluCylinder(quadobj, 2.f, 2.f, 77, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.f,0.f,80.f);
		glRotatef(-90, 1.f, 0.f, 0.f);
		gluCylinder(quadobj, 2.f, 2.f, 77, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(30.f,0.f,0.f);
		glRotatef(-90, 1.f, 0.f, 0.f);
		gluCylinder(quadobj, 2.f, 2.f, 38, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(30.f,0.f,80.f);
		glRotatef(-90, 1.f, 0.f, 0.f);
		gluCylinder(quadobj, 2.f, 2.f, 38, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.f,20.f,0.f);
		glRotatef(90, 0.f, 1.f, 0.f);
		gluCylinder(quadobj, 2.f, 2.f, 30, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.f,20.f,80.f);
		glRotatef(90, 0.f, 1.f, 0.f);
		gluCylinder(quadobj, 2.f, 2.f, 30, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0.f,60.f,0.f);
		glRotatef(0, 1.f, 0.f, 0.f);
		gluCylinder(quadobj, 2.f, 2.f, 80, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(30.f,37.f,80.f);
		glRotatef(-90, 0.f, 1.f, 0.f);
		gluCylinder(quadobj, 3.f, 3.f, 30, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(30.f,37.f,0.f);
		glRotatef(-90, 0.f, 1.f, 0.f);
		gluCylinder(quadobj, 3.f, 3.f, 30, 20, 20);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(30.f,37.f,-2.f);
		glRotatef(0, 1.f, 0.f, 0.f);
		gluCylinder(quadobj, 3.f, 3.f, 84, 20, 20);
	glPopMatrix();

	//seat pan
	glPushMatrix();
		glTranslatef(15.f, 37.f, 40.f);
		glScalef(30.f, 5.0f, 82.f);
		glutSolidCube(1.f);
	glPopMatrix();

	glTranslatef(-seat_pos, 100.f, -98.f);
/* Draw seat END*/

	/*Draw board START*/
		glPushMatrix();
			glColor3f(0.168f, 0.522f, 0.169f);
			glTranslatef(50.f, 20.f, 140.f);
			glutSolidSphere(3.f, 10.f, 10.f);
		glPopMatrix();

		glPushMatrix();
			glColor4f(0.0f, 0.0f, 0.0f,0.1f);
			glTranslatef(50.f, -47.f, 65.f);
			glRotatef(90.f, 0.f, 0.f, 30.f);
			glScalef(7.f, 60.0f, 150.f);
			glutSolidCube(1.f);
		glPopMatrix();

		glPushMatrix();
			glColor4f(0.8f, 0.8f, 0.3f,0.1f);
			glTranslatef(50.f, -25.f, 65.f);
			glRotatef(90.f, 0.f, 0.f, 30.f);
			glScalef(40.f, 60.0f, 150.f);
			glutSolidCube(1.f);
		glPopMatrix();

		glPushMatrix();
			glColor3f(0.168f, 0.522f, 0.169f);
			glTranslatef(50.f, -25.f, 140.f);
			glutSolidSphere(3.f, 10.f, 10.f);
		glPopMatrix();

		glPushMatrix();
			glColor4f(0.0f, 0.0f, 0.0f,0.1f);
			glTranslatef(50.f, -3.f, 65.f);
			glRotatef(90.f, 0.f, 0.f, 30.f);
			glScalef(7.f, 60.0f, 150.f);
			glutSolidCube(1.f);
		glPopMatrix();

		glPushMatrix();
			glColor4f(0.8f, 0.8f, 0.3f,0.1f);
			glTranslatef(50.f, 20.f, 65.f);
			glRotatef(90.f, 0.f, 0.f, 30.f);
			glScalef(40.f, 60.0f, 150.f);
			glutSolidCube(1.f);
		glPopMatrix();

		glPushMatrix();
			glColor4f(0.8f, 0.8f, 0.3f,0.1f);
			glTranslatef(50.f, -70.f, 65.f);
			glRotatef(90.f, 0.f, 0.f, 30.f);
			glScalef(40.f, 60.0f, 150.f);
			glutSolidCube(1.f);
		glPopMatrix();

		glPushMatrix();
			glColor4f(0.8f, 0.8f, 0.3f,0.1f);
			glTranslatef(50.f, -70.f, board_pos);
			glRotatef(90.f, 0.f, 0.f, 30.f);
			glScalef(40.f, 60.0f, 150.f);
			glutSolidCube(1.f);
		glPopMatrix();


		glPushMatrix();
			glColor3f(0.168f, 0.522f, 0.169f);
			glTranslatef(50.f, -68.f, board_pos + 75);
			glutSolidSphere(3.f, 10.f, 10.f);
		glPopMatrix();
/*Draw board END*/



/*Draw Light bulb START*/
	
	glPushMatrix();
			glColor4f(0.8f, 0.8f, 0.7f,0.1f);
			glTranslatef(0.f, 90.f, 200);
			glRotatef(-90.f, 1.f, 0.f, 0.f);	
			glutSolidTorus(2 , 2, 110.f, 110.f);
	glPopMatrix();

	glPushMatrix();
			glColor4f(0.8f, 0.8f, 0.7f,0.1f);
			glTranslatef(0.f, 87.f, 200);
			glRotatef(-90.f, 1.f, 0.f, 0.f);	
			glutSolidTorus(2 , 2, 110.f, 110.f);
		glPopMatrix();

	glPushMatrix();
			glColor4f(0.8f, 0.8f, 0.7f,0.1f);
			glTranslatef(0.f, 84.f, 200);
			glRotatef(-90.f, 1.f, 0.f, 0.f);	
			glutSolidTorus(2 , 2, 110.f, 110.f);
	glPopMatrix();

	glPushMatrix();
			glMaterialfv(GL_FRONT, GL_EMISSION, light0_mat1);
			glColor4f(0.8f, 0.8f, 0.7f,0.1f);
			glTranslatef(0.f, 76.f, 200.f);
			glutSolidSphere(10.f, 50.f, 50.f);
	glPopMatrix();
			glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

/*Draw Light bulb END*/

	/*Draw Calender START*/
	glBegin(GL_POLYGON);
		glColor3f(1.0f,0.2f,0.2f);
		glVertex3f(-85.0, 100.0,-200.f);
		glVertex3f(-15.0, 100.0,-200.f);
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(-15.0, 50.0,-200.f);
		glVertex3f(-85.0, 50.0,-200.f);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0.8f,0.8f,0.8f);
		glVertex3f(-85.0, 50.0,-200.f);
		glVertex3f(-15.0, 50.0,-200.f);		
		glVertex3f(-15.0, 0.0,-200.f);
		glVertex3f(-85.0, 0.0,-200.f);
	glEnd();

	
	glBegin(GL_LINES);
		glColor3f(0.7,0.7,0.7);
		for(i=50;i>=0;i-=10){
			glVertex3f(-85.0, i,-199.f);
			glVertex3f(-15.0, i,-199.f);
		}

		for(i=-15;i>=-85;i-=10){
			glVertex3f(i, 50.0,-199.f);
			glVertex3f(i, 0.0,-199.f);
		}
	glEnd();

	glPointSize(5);
	glBegin(GL_POINTS);
		glColor3f(0.5f,0.5f,0.f);
		glVertex3f(-24.0, 45.0,-199.f);
		glVertex3f(-53.0, 37.0,-199.f);
		glVertex3f(-77.0, 26.0,-199.f);
		glVertex3f(-59.0, 26.0,-199.f);
		glVertex3f(-29.0, 16.0,-199.f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(0.5f,0.5f,0.5f);
		glVertex3f(-55.0, 80.0,-199.f);
		glVertex3f(-75.0, 90.0,-199.f);
		glVertex3f(-77.0, 82.0,-199.f);
	glEnd();

	glBegin(GL_TRIANGLES);
		glColor3f(0.5f,0.5f,0.5f);
		glVertex3f(-45.0, 80.0,-199.f);
		glVertex3f(-25.0, 90.0,-199.f);
		glVertex3f(-23.0, 82.0,-199.f);
	glEnd();

	glBegin(GL_POLYGON);
		glColor3f(0.45f,0.45f,0.45f);
		glVertex3f(-60.0, 67.0,-199.f);
		glVertex3f(-40.0, 67.0,-199.f);		
		glVertex3f(-40.0, 62.0,-199.f);
		glVertex3f(-60.0, 62.0,-199.f);
	glEnd();
	/*Draw Calender END*/


	/* Draw the wall START */
	/* Back wall */
	glBegin(GL_TRIANGLE_FAN);
		glColor3f(1.f,0.54f,0.f);
		glVertex3f(-110.0f, 110.0f, -200.0f);
		glVertex3f(-110.0f, -110.0f, -200.0f);	
		glVertex3f(110.0f, -110.0f, -200.0f);
		glVertex3f(110.0f, 110.0f,-200.0f);
	glEnd();

	/* Top wall */
	glBegin(GL_POLYGON);
	glColor3f(1.f,0.84f,0.3f);
		glVertex3f(-80.0f, 80.0f, 0.0f);
		glVertex3f(80.0f, 80.0f, 0.0f);
		glVertex3f(190.0f, 190.0f,0.0f);
		glVertex3f(-190.0f, 190.0f, 0.0f);
	glEnd();

	glBegin(GL_QUADS);	
		/* Bottom wall */
		glColor3f(0.8f,0.44f,0.0f);
		glVertex3f(80.f, -80.f, 0.f);
		glVertex3f(-80.f, -80.f, 0.f);
		glColor3f(1.f,0.54f,0.5f);
		glVertex3f(-190.f, -190.f, 0.f);
		glVertex3f(190.f, -190.f, 0.f);

		/* Right wall */
		glColor3f(0.9f,0.87f,0.9f);
		glVertex3f(190.0f, 190.0f, 0.0f);
		glColor3f(1.f,0.54f,0.4f);
		glVertex3f(80.0f, 80.0f, 0.0f);
		glColor3f(1.f,0.54f,0.f);
		glVertex3f(80.0f, -80.0f, 0.0f);
		glColor3f(1.f,0.54f,0.3f);
		glVertex3f(190.0f, -190.0f, 0.0f);

		/* Left wall */
		glColor3f(0.9f,0.87f,0.9f);
		glVertex3f(-190.0f, 190.0f, 0.0f);
		glColor3f(1.f,0.54f,0.4f);
		glVertex3f(-80.0f, 80.0f, 0.0f);
		glColor3f(1.f,0.54f,0.f);
		glVertex3f(-80.0f, -80.0f, 0.0f);
		glColor3f(1.f,0.54f,0.3f);
		glVertex3f(-190.0f, -190.0f, 0.0f);
	glEnd();
	/* Draw the wall END */
	glPopMatrix();

	glutSwapBuffers();
	glFlush();	

	/* Refresh the frame */
	glutPostRedisplay();
}

void reshape(int w, int h) // Resize the GL Window. w=width, h=height
{
//	winWidth = w; winHeight = h;
	glViewport(0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Frustum Setting
	glFrustum(-FRUSTDIM, FRUSTDIM, -FRUSTDIM, FRUSTDIM, 300., 800.);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y) // Handle the keyboard events here
{
	switch (key) 
	{
		case '\033':
			exit(0);
			break;
		case 'p': /*pause*/
			option = 1;
			break;	

		case '1': /*decrease light*/
			if (enableLight)
				if(light0_mat1[0] >= 0){
					for (i=0; i<=3 ; i++){
						light0_mat1[i] -= 0.01;
						light0_diff[i] -= 0.01;
					}
					glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1);
					glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);
					glEnable(GL_LIGHT0);
				}
			break;

		case '2': /*increase light*/
				if (enableLight)
					if(light0_mat1[0] <= 1){
						for (i=0; i<=3 ; i++){
							light0_mat1[i] += 0.01;
							light0_diff[i] += 0.01;
						}
					glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1);
					glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);
					glEnable(GL_LIGHT0);
				}
			break;

		case 's': /*switch on/off the light*/
			option = 4;
			break;
		case '4':
			option = 2;
			break;
		case '5':
			option = 3;
			break;
		case '6':
			option = 5;
			break;	
		case '7':
			option = 6;
			break;	
		case 'q':
			option = 7;
			break;	
		case 'w':
			option = 8;
			break;
		case 'e':
			option = 9;
			break;	
		case 'r':
			option = 10;
			break;
	}
}

void idle()
{
	if(option == 1)
	{

	}
	else if(option == 2)	/* Anti-clockwise */
	{
		if(angle >= 360)
			angle = 0;
		angle++;
	}
	else if(option == 3)	/* Clockwise */
	{
		if(angle <= -360)
			angle = 0;
		angle--;
	}
	else if(option == 4)
	{	
		if(enableLight)
		{
			enableLight = 0;			
			for (i=0; i<=3 ; i++){
				light0_mat1[i] = 0.0;
			}
			glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1);
			glDisable(GL_LIGHT0);
			option = 1;
		}
		else
		{
			enableLight = 1;
			for (i=0; i<=3 ; i++){
				light0_diff[i] = 1.0;
				light0_mat1[i] = 1.0;
			}
			glLightfv(GL_LIGHT0, GL_AMBIENT, light0_mat1);
			glLightfv(GL_LIGHT0, GL_DIFFUSE, light0_diff);
			glEnable(GL_LIGHT0);
			option = 1;
		}
	}
	else if(option == 5)
	{
		if(donut_size <= 5)
			donut_size += 0.2;
	}
	else if(option == 6)
	{
		if(donut_size > 3)
			donut_size -= 0.2;
	}
	else if(option == 7)
	{
		if(seat_pos >= -100)
			seat_pos -= 1;
	}
	
	else if(option == 8)
	{
		if(seat_pos < -60)
			seat_pos += 1;
	}

	else if(option == 9)
	{
		if(board_pos <= 160)
			board_pos += 10;
	}
	else if(option == 10)
	{
		if(board_pos >= 75)
			board_pos -= 10;
	}
	else{}
}


int main(int argc, char** argv)
{

	/* Initialization of GLUT Library */
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA|GLUT_DOUBLE|GLUT_DEPTH);

	/* Create a window with title specified */
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Assignment 1: Creating a 3D Room");

	init();	/* not GLUT call, initialize several parameters */

	/* Register different CALLBACK function for GLUT to response 
	 * with different events, e.g. window sizing, mouse click or
	 * keyboard stroke*/
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);		
	glutKeyboardFunc(keyboard);	
	glutIdleFunc(idle);
	
	/*Enter the GLUT event processing loop which never returns.
	it will call different registered CALLBACK according
	to different events. */
	glutMainLoop();

        return 0;
}
