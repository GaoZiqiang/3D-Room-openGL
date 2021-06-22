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
#include <bits/stdc++.h>
#include <iostream>
#include <unistd.h>

#define Pi 3.1415927

using namespace std;

const GLdouble FRUSTDIM = 100.0f;

int option = 0, i = 0;
bool enableLight = 1;

/* Do  animation 动画*/
GLfloat angle = 0,tea_p = -40 , tea_face = 100 , donut_size = 3 , seat_pos = -60, board_pos = -50;
GLboolean deskLight = false, air_open = false;

clock_t clock_agl1 = 0;// 分针
clock_t clock_agl2 = 90;// 时针

GLUquadricObj *quadobj;

/* For lighting*/
GLfloat light0pos[] = {0.0f, 1.0f, 0.0f, 0.0f};
GLfloat light0_mat1[] = {1.0, 1.0, 1.0, 1.f};
GLfloat light0_diff[] = {1.0, 1.0, 1.0, 0.3};
GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };// 镜面反射光

//设置材质颜色
float blackMat[] = { 0.0f,0.0f,0.0f,1.0f };
float ambientMat[] = { 0.1f,0.1f,0.1f,1.0f };
float diffuseMat[] = { 0.4f,0.4f,0.4f,1.0f };
float specularMat[] = { 0.9f,0.9f,0.9f,1.0f };

GLfloat spot_position[] = { -1.0, -1.0, 0};// 指定聚光灯的方向

void init(void) // All Setup For OpenGL Goes Here 
{
	/* Light 0 Settings */

	// OpenGL把现实世界中的光照系统近似归为三部分，分别是光源、材质和光照环境
    // 创建广光源GL_LIGHT1 并设置三个属性GL_POSITION GL_AMBIENT GL_DIFFUSE
    glLightfv(GL_LIGHT1, GL_POSITION, light0pos);// 设置光源的位置
    glLightfv(GL_LIGHT1, GL_AMBIENT, light0_mat1);// 设置光的环境强度 环境光Ambient
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light0_diff);// 散色光 漫射光Diffuse
    glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);// 镜面反射光

    glLightf(GL_LIGHT1, GL_SPOT_CUTOFF, 45);//设置聚光灯的角度
    glLightfv(GL_LIGHT1, GL_SPOT_DIRECTION, spot_position);//指定聚光灯的方向

    // 材质和颜色
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambientMat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuseMat);
    glMaterialfv(GL_FRONT, GL_SPECULAR, specularMat);

	quadobj = gluNewQuadric();

    // 打开光照
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT1);

	glEnable(GL_NORMALIZE);
	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);		/* Define Counter-Clockwise as front face */

	glEnable(GL_COLOR_MATERIAL);
}

//吊灯
void draw_light(void)
{
    // 定义相关材料参数params
    GLfloat matBlack_light[] = { 0.0f,0.0f,0.0f,1.0f };
    GLfloat matWhite_light[] = { 0.0f,0.0f,0.0f,0.0f };
    GLfloat matShininess_light[] = { 0.0f,0.1f,0.0f,0.0f };
    GLfloat matYellow_light[] = { 0.0f,0.0f,0.5f,0.0f };
    bool aCeilingLight = true;

    glPushMatrix();					//Celling Light

    glColor3f(1, 1, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, matYellow_light);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellow_light);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite_light);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShininess_light);
    glMaterialfv(GL_FRONT, GL_EMISSION, matBlack_light);
    if(aCeilingLight) glMaterialfv(GL_FRONT, GL_EMISSION, matYellow_light);
    glTranslatef(0,8.99,-10);
    glRotatef(90, 1, 0, 0);
    glutSolidCone(1,1,16,16);

    glPopMatrix();
}

//床
void draw_bed(void)
{
    GLfloat x = 6;
    GLfloat y1 = -7.5;
    GLfloat y2 = -5;
    GLfloat z1 = -19.9;
    GLfloat z2 = -5;
    //床头
    glBegin(GL_QUADS);
    glColor3f(0.f,0.54f,0.5f);
    glVertex3f(x, y2, z1);
    glVertex3f(-x, y2,z1);
    glVertex3f(-x, y1,z1);
    glVertex3f(x, y1, z1);
    glEnd();

    //床身
    glBegin(GL_QUADS);
    glColor3f(1.f,0.54f,0.5f);
    glVertex3f(x, y1, z1);
    glVertex3f(-x, y1,z1);
    glVertex3f(-x, y1,z2);
    glVertex3f(x, y1, z2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.f,0.54f,0.5f);
    glVertex3f(-x, y1, z1);
    glVertex3f(-x, -8.99,z1);
    glVertex3f(-x, -8.99,z2);
    glVertex3f(-x, y1, z2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.f,0.54f,0.5f);
    glVertex3f(x, y1, z1);
    glVertex3f(x, -8.99,z1);
    glVertex3f(x, -8.99,z2);
    glVertex3f(x, y1, z2);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.f,0.54f,0.5f);
    glVertex3f(-x, y1,z2);
    glVertex3f(x, y1, z2);
    glVertex3f(x, -8.99, z2);
    glVertex3f(-x, -8.99,z2);
    glEnd();

    //枕头
    glBegin(GL_QUADS);
    glColor3f(1.0f,0.84f,0.5f);
    glVertex3f(x-0.5, -7, z1+0.5);
    glVertex3f(0.5, -7,z1+0.5);
    glVertex3f(0.5, -7,-17);
    glVertex3f(x-0.5, -7,-17);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f,0.84f,0.5f);
    glVertex3f(0.5, -7,-17);
    glVertex3f(x-0.5, -7,-17);
    glVertex3f(x-0.5, y1,-17);
    glVertex3f(0.5, y1,-17);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f,0.84f,0.5f);
    glVertex3f(-x+0.5, -7, z1+0.5);
    glVertex3f(-0.5, -7,z1+0.5);
    glVertex3f(-0.5, -7,-17);
    glVertex3f(-x+0.5, -7,-17);
    glEnd();

    glBegin(GL_QUADS);
    glColor3f(1.0f,0.84f,0.5f);
    glVertex3f(-0.5, -7,-17);
    glVertex3f(-x+0.5, -7,-17);
    glVertex3f(-x+0.5, y1,-17);
    glVertex3f(-0.5, y1,-17);
    glEnd();

    //被子
    glPushMatrix();
    glTranslatef(0, -7.49, -10.5);
    glScalef(10 * x, 100.1, 100);
    glutSolidCube(1);
    glPopMatrix();

}

// 空调
void draw_air_conditioning(void)
{
//    bool tv_open = false;
    glPushMatrix();
    glTranslatef(-100, 50, 100);

    // 空调
    if (air_open){// 开空调
        glPushMatrix();
        glTranslatef(0, 10, -2);
        glScalef( 8.3, 20, 86);
        glColor3f(1.0, 1.0, 1.0);// 白色
        glutSolidCube(1);
        glLineWidth(4);
        glColor3f(1, 1, 1);
        glutWireCube(1);
        glLineWidth(1);
        glPopMatrix();


        glPushMatrix();
        glTranslatef(0, -1, 0);
        glScalef( 0.001, 0.001, 83);
        glColor3f(0.0, 0.0, 0.0);// 黑色
        glutSolidCube(1);
        glLineWidth(3);
        glColor3f(0.0, 0.0, 0.0);
        glutWireCube(1);
        glLineWidth(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(3.0, -0.5, 0);
        glScalef( 0.001, 0.001, 83);
        glColor3f(0.0, 0.0, 0.0);// 黑色
        glutSolidCube(1);
        glLineWidth(3);
        glColor3f(0.0, 0.0, 0.0);
        glutWireCube(1);
        glLineWidth(1);
        glPopMatrix();

//        glPushMatrix();
//        glTranslatef(5.5, 0, 0);
//        glScalef( 0.001, 0.001, 83);
//        glColor3f(0.0, 0.0, 0.0);// 黑色
//        glutSolidCube(1);
//        glLineWidth(3);
//        glColor3f(0.0, 0.0, 0.0);
//        glutWireCube(1);
//        glLineWidth(1);
//        glPopMatrix();
    }else{// 关空调
        glPushMatrix();
        glTranslatef(0, 10, -2);
        glScalef( 8.3, 20, 86);
        glColor3f(1.0, 1.0, 1.0);// 白色
        glutSolidCube(1);
        glLineWidth(4);
        glColor3f(1, 1, 1);
        glutWireCube(1);
        glLineWidth(1);
        glPopMatrix();
    }

    glPopMatrix();

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


	/* 房间元素区域 */
    draw_air_conditioning();

    // 床腿
    /* Draw a Bed START */
    glPushMatrix();
        glTranslatef(-50.f, -20.f, 195.f);

        // 床腿板子设置
        glPushMatrix();
        glColor4f(0.2f, 0.2f, 0.2f,0.1f);
        glTranslatef(0.f, -45.f, 65.f);
        glRotatef(90.f, 0.f, 0.f, 30.f);
        glScalef(70.f, 100.0f, 40.f);//x:高 y:宽 z:长
        glutSolidCube(0.7f);// 床的厚度
        glPopMatrix();

        /* Rotate with angle */
        glTranslatef(0.f, -40.f, 130.f);
        glRotatef(angle, 0.f, 1.f, 0.f);

    glPopMatrix();
    /* draw a 床腿 END */

	// 床
    /* Draw a Bed START */
    glPushMatrix();
//    glTranslatef(-100.f, 0.f,100.f);
    glTranslatef(-50.f, -10.f, 200.f);

    /* Draw a support for table 支柱*/
    glPushMatrix();
    glColor3f(0.2f, 0.2f, 0.2f);
    glTranslatef(0.f, -90.f, 130.f);
    glRotatef(-90, 1.f, 0.f, 0.f);
    gluCylinder(quadobj, 10.f, 5.f, 40.f, 20.f, 20.f);
    glPopMatrix();

    // 床面
    glPushMatrix();
        glColor3f(0.2f, 0.2f, 0.2f);
        glTranslatef(0.f, -45.f, 65.f);
        glRotatef(90.f, 0.f, 0.f, 30.f);
        glScalef(25.f, 100.0f, 400.f);//x:高 y:宽 z:长
        glutSolidCube(0.7f);// 床的厚度

    glPopMatrix();


    //枕头
    glPushMatrix();
        GLfloat x = 6;
        GLfloat z1 = -19.9;
        glBegin(GL_QUADS);
        glColor3f(1.0f,0.0f,0.0f);
        glTranslatef(0.f, -45.f, 65.f);
        glVertex3f(10, -45, 65);
        glVertex3f(0.5, -45,70);
        glVertex3f(0.5, -40,70);
        glVertex3f(0.5, -25,70);
        glEnd();
    glPopMatrix();

    /* Rotate with angle */
    glTranslatef(0.f, -40.f, 130.f);
    glRotatef(angle, 0.f, 1.f, 0.f);

    glPopMatrix();
    /* draw a Bed END */



	/* Draw a Table START */
	glPushMatrix();
		glTranslatef(100.f, 0.f,-100.f);

		/* form the table (cyclinder part) 柱面*/
        glPushMatrix();
        glColor3f(1.0f, 1.0f, 1.0f);
        glTranslatef(0.f, -45.f, 130.f);
//        glRotatef(-90, 1.f, 0.f, 0.f);
        glScalef(130.f, 15.0f, 120.f);//x:宽度 y:厚度 z:长度
        glutSolidCube(0.7f);// 厚度
        glPopMatrix();

		/* Rotate with angle */
		glTranslatef(0.f, -40.f, 130.f);
		glRotatef(angle, 0.f, 1.f, 0.f);

        // 花瓶
        GLfloat matBlack[] = { 0.0f,0.0f,0.0f,1.0f };
        GLfloat matWhite[] = { 0.0f,0.0f,0.0f,0.0f };
        GLfloat matShininess[] = { 0.0f,0.1f,0.0f,0.0f };
        GLfloat matYellow[] = { 0.0f,0.0f,0.5f,0.0f };

        /* 台灯 */
        glPushMatrix();

            // 定义相关材料参数params
            GLfloat matBlack_light[] = { 0.0f,0.0f,0.0f,1.0f };
            GLfloat matWhite_light[] = { 0.0f,0.0f,0.0f,0.0f };
            GLfloat matShininess_light[] = { 0.0f,0.1f,0.0f,0.0f };
            GLfloat matYellow_light[] = { 0.0f,0.0f,0.5f,0.0f };
            // bool aCeilingLight = false;

            glMaterialfv(GL_FRONT, GL_AMBIENT, matYellow_light);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, matYellow_light);
            glMaterialfv(GL_FRONT, GL_SPECULAR, matWhite_light);
            glMaterialfv(GL_FRONT, GL_SHININESS, matShininess_light);
            glMaterialfv(GL_FRONT, GL_EMISSION, matBlack_light);
            if(deskLight) glMaterialfv(GL_FRONT, GL_EMISSION, matYellow_light);

//            glTranslatef(20.f, 20.f, 0.f);
            /* 台灯灯罩 */
            glPushMatrix();					//Celling Light
                glColor4f(0.5f, 0.0f, 0.0f,0.5f);
                glTranslatef(20.f, 20.f, 0.f);
                glRotatef(90, 1, 0, 0);
                glScalef(20.f, 20.0f, -20.f);
                glutSolidCone(1,1,16,16);// Cone:圆锥
            glPopMatrix();

            /* 台灯柱*/
            glPushMatrix();
                glColor3f(0.7f, 0.7f, 0.7f);
                glTranslatef(20.f, 0.f, 0.f);
    //            glTranslatef(-30.f, 10.f, 0.f);
                glRotatef(-90, 1.f, 0.f, 0.f);
                gluCylinder(quadobj, 3.f, 3.f, 20.f, 30.f, 30.f);
            glPopMatrix();

            /* 台灯底座*/
            glPushMatrix();
            glColor3f(0.0f, 0.7f, 0.0f);
            glTranslatef(20.f, 0.f, 0.f);
        //            glTranslatef(-30.f, 10.f, 0.f);
            glRotatef(-90, 1.f, 0.f, 0.f);
            gluCylinder(quadobj, 10.f, 10.f, 5.f, 30.f, 30.f);
            glPopMatrix();
        glPopMatrix();

	glPopMatrix();
	/* draw a table END */

	// 椅子
	/* pull or push the seat 椅子*/
	glTranslatef(seat_pos, -100.f, 98.f);

	/*Draw seat START*/
    glPushMatrix();
        glTranslatef(10.f, 0.f,-80.f);
        // 长竖棍后
        glPushMatrix();
            // 控制椅子上所有line的颜色
            glColor3f(0.0f, 0.0f, 0.0f);
            glTranslatef(70.f,0.f,0.f);
            glRotatef(-90, 1.f, 0.f, 0.f);
            gluCylinder(quadobj, 2.f, 2.f, 77, 20, 20);
        glPopMatrix();

        // 长竖棍前
        glPushMatrix();
            glTranslatef(70.f,0.f,80.f);
            glRotatef(-90, 1.f, 0.f, 0.f);
            gluCylinder(quadobj, 2.f, 2.f, 77, 20, 20);
        glPopMatrix();

        // 短竖棍后
        glPushMatrix();
            glTranslatef(100.f,0.f,0.f);
            glRotatef(-90, 1.f, 0.f, 0.f);
            gluCylinder(quadobj, 2.f, 2.f, 38, 20, 20);
        glPopMatrix();

        // 短竖棍前
        glPushMatrix();
            glTranslatef(100.f,0.f,80.f);
            glRotatef(-90, 1.f, 0.f, 0.f);
            gluCylinder(quadobj, 2.f, 2.f, 38, 20, 20);
        glPopMatrix();

        // 短横棍后
        glPushMatrix();
            glTranslatef(70.f,20.f,0.f);
            glRotatef(90, 0.f, 1.f, 0.f);
            gluCylinder(quadobj, 2.f, 2.f, 30, 20, 20);
        glPopMatrix();

        // 短横棍前
        glPushMatrix();
            glTranslatef(70.f,20.f,80.f);
            glRotatef(90, 0.f, 1.f, 0.f);
            gluCylinder(quadobj, 2.f, 2.f, 30, 20, 20);
        glPopMatrix();

        // 后背横棍
        glPushMatrix();
            glTranslatef(70.f,60.f,0.f);
            glRotatef(0, 1.f, 0.f, 0.f);
            gluCylinder(quadobj, 2.f, 2.f, 80, 20, 20);
        glPopMatrix();

        // 做垫横棍前
        glPushMatrix();
            glTranslatef(100.f,37.f,80.f);
            glRotatef(-90, 0.f, 1.f, 0.f);
            gluCylinder(quadobj, 3.f, 3.f, 30, 20, 20);
        glPopMatrix();

        // 做垫横棍后
        glPushMatrix();
            glTranslatef(100.f,37.f,0.f);
            glRotatef(-90, 0.f, 1.f, 0.f);
            gluCylinder(quadobj, 3.f, 3.f, 30, 20, 20);
        glPopMatrix();

        // 做垫横棍右
        glPushMatrix();
            glTranslatef(100.f,37.f,-2.f);
            glRotatef(0, 1.f, 0.f, 0.f);
            gluCylinder(quadobj, 3.f, 3.f, 84, 20, 20);
        glPopMatrix();

        //seat pan 垫子
        glPushMatrix();
            glTranslatef(85.f, 37.f, 40.f);
            glScalef(30.f, 5.0f, 82.f);
            glutSolidCube(1.f);
        glPopMatrix();

    glPopMatrix();
	glTranslatef(-seat_pos, 100.f, -98.f);
/* Draw seat END*/

		// 最下面黑色横条
		glPushMatrix();
			glColor4f(0.0f, 0.0f, 0.0f,0.1f);
			glTranslatef(-50.f, -47.f, 65.f);
			glRotatef(90.f, 0.f, 0.f, 30.f);
            glScalef(7.f, 70.0f, 40.f);//x:高 y:宽
			glutSolidCube(1.f);
		glPopMatrix();

		// 中间柜子
		glPushMatrix();
			glColor4f(0.8f, 0.8f, 0.3f,0.1f);
			glTranslatef(-50.f, -25.f, 65.f);
			glRotatef(90.f, 0.f, 0.f, 30.f);
            glScalef(40.f, 70.0f, 40.f);//x:高 y:宽
			glutSolidCube(1.f);
		glPopMatrix();

		// 最上面柜子
		glPushMatrix();
			glColor4f(0.8f, 0.8f, 0.3f,0.1f);
			glTranslatef(-50.f, 20.f, 65.f);
			glRotatef(90.f, 0.f, 0.f, 30.f);
            glScalef(50.f, 70.0f, 40.f);//x:高 y:宽 z:长
			glutSolidCube(1.f);
		glPopMatrix();

        // 最下面柜子
		glPushMatrix();
			glColor4f(0.8f, 0.8f, 0.3f,0.1f);
			// glTranslatef(-50.f, -70.f, 65.f);
            glTranslatef(board_pos, -70.f, 65.f);
			glRotatef(90.f, 0.f, 0.f, 30.f);
            glScalef(40.f, 70.0f, 40.f);//x:高 y:宽
			glutSolidCube(1.f);
		glPopMatrix();

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

	/* 时钟 */
    glPushMatrix();
        // 角度
//        clock_t clock_agl1 = 0;// 时针
//        clock_t clock_agl2 = 180;// 分针
//        Pi = 3.14;

        glTranslatef(50, 40, -19.0);
        glScalef(10.f, 10.f, 10.f);
        //圆盘
        gluDisk(quadobj, 2.2, 2.5, 20, 4);
        //时针
        glLineWidth(2);
        glBegin(GL_LINES);
        glVertex3f(2.0 * cos(clock_agl1 * Pi / 180), 2.0 * sin(clock_agl1 * Pi / 180), 0);
        glVertex3f(0, 0, 0);
        glVertex3f(0, 0, 0);
        glVertex3f(1, 0, 0);
        glVertex3f(0, 0, 0);
//        glLineWidth(10);
        glVertex3f(1 * cos(clock_agl2 * Pi / 180), 1.5 * sin(clock_agl2 * Pi / 180), 0);
        glColor3f(0.0f,0.0f,0.0f);
        glVertex3f(0, 1.9, 0);
        glVertex3f(0, 2.2, 0);
        glVertex3f(1.9, 0, 0);
        glVertex3f(2.2, 0, 0);
        glVertex3f(0, -1.9, 0);
        glVertex3f(0, -2.2, 0);
        glVertex3f(-1.9, 0, 0);
        glVertex3f(-2.2, 0, 0);
        glEnd();
        glLineWidth(1);
        glColor3f(0.25, 0.25, 0.25);
        gluDisk(quadobj, 0, 2.2, 20, 4);
        glFlush();// 刷新
    glPopMatrix();

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
	switch (key)// 获取键盘值
	{
		case '\033':
			exit(0);
			break;
		case 'p': /*pause*/
			option = 1;
			break;	

		case '1': /*decrease light*/
		    option = 11;
			break;

		case '2': /*increase light*/
		    option = 12;
			break;

		case 's': /*switch on/off the light*/
			option = 4;
			break;
		case '3':// 控制台灯 开
			option = 2;// 看option==2
			break;
		case '5':// 时钟
			option = 3;
			break;
		case '6':
			option = 5;
			break;	
		case '7':// 空调开
			option = 13;
			break;
        case '8':// 空调关
            option = 14;
            break;
		case 'q':// 椅子向外移动
			option = 7;
			break;	
		case 'w':// 椅子向内移动
			option = 8;
			break;
		case 'e':// 柜子外移
			option = 9;
			break;	
		case 'r':// 柜子内移
			option = 10;
			break;
	}
}

void idle()
{
	if(option == 1)
	{

	}
	else if(option == 2)	/* 控制台灯开关 */
	{
        if(enableLight)// 如果灯开着，则关灯 和大灯一致 都是黑暗
        {
            enableLight = 0;
            for (i=0; i<=3 ; i++){
                light0_mat1[i] = 0.0;
            }
            glLightfv(GL_LIGHT1, GL_AMBIENT, light0_mat1);
            glDisable(GL_LIGHT1);
            option = 1;
        }
        else// 如果等关闭，则开灯，灯光的强度和散度都减半
        {
            enableLight = 1;
            for (i=0; i<=3 ; i++){
                light0_diff[i] = 0.5;
                light0_mat1[i] = 0.5;
            }
            glLightfv(GL_LIGHT1, GL_AMBIENT, light0_mat1);
            glLightfv(GL_LIGHT1, GL_DIFFUSE, light0_diff);
            glEnable(GL_LIGHT1);
            option = 1;
        }
	}
	else if(option == 3)	/* Clockwise */
	{
	    // clock_agl2 = 180;
	    int a = 1;
        clock_agl1 += 90;
		if (clock_agl1 % 360 == 0) {
            clock_agl2 += 30;
		}
        glutPostRedisplay(); // 重画
		sleep(a);
	}
	else if(option == 4)
	{	
		if(enableLight)
		{
			enableLight = 0;
			for (i=0; i<=3 ; i++){
				light0_mat1[i] = 0.0;
			}
			glLightfv(GL_LIGHT1, GL_AMBIENT, light0_mat1);
			glDisable(GL_LIGHT1);
			option = 1;
		}
		else
		{
			enableLight = 1;
			for (i=0; i<=3 ; i++){
				light0_diff[i] = 1.0;
				light0_mat1[i] = 1.0;
			}
			glLightfv(GL_LIGHT1, GL_AMBIENT, light0_mat1);
			glLightfv(GL_LIGHT1, GL_DIFFUSE, light0_diff);
			glEnable(GL_LIGHT1);
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
		if(seat_pos >= -80)
			seat_pos -= 1;
	}
	
	else if(option == 8)
	{
		if(seat_pos < -60)
			seat_pos += 1;
	}

	else if(option == 9)// 柜子外移
	{
//	    cout << "board_pos:" << board_pos << endl;
		if(board_pos < -25){
            // cout << "board_pos:" << board_pos << endl;
            board_pos += 5;
		}
	}
	else if(option == 10)
	{
		if(board_pos > -50)
			board_pos -= 5;
	}
    else if(option == 11)// 光线变弱
    {
        if (enableLight)
            if(light0_mat1[0] >= 0){
                for (i=0; i<=3 ; i++){
                    light0_mat1[i] -= 0.01;
                    light0_diff[i] -= 0.01;
                }
                glLightfv(GL_LIGHT1, GL_AMBIENT, light0_mat1);
                glLightfv(GL_LIGHT1, GL_DIFFUSE, light0_diff);
                glEnable(GL_LIGHT1);
            }
    }
    else if(option == 12)// 光线变强
    {
        if (enableLight)
            if(light0_mat1[0] <= 1){
                for (i=0; i<=3 ; i++){
                    light0_mat1[i] += 0.01;
                    light0_diff[i] += 0.01;
                }
                glLightfv(GL_LIGHT1, GL_AMBIENT, light0_mat1);
                glLightfv(GL_LIGHT1, GL_DIFFUSE, light0_diff);
                glEnable(GL_LIGHT1);
            }
    }
    else if(option == 13)
    {
        if (!air_open)
            air_open = true;
    }
    else if(option == 14)
    {
        if (air_open)
            air_open = false;
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
	glutCreateWindow("Creating a 3D Room by SZ2016072 GaoZiqiang");

	init();	/* not GLUT call, initialize several parameters */

	/* Register different CALLBACK function for GLUT to response 
	 * with different events, e.g. window sizing, mouse click or
	 * keyboard stroke*/
	glutReshapeFunc(reshape);
	glutDisplayFunc(display);
//    glutDisplayFunc(draw_light);
	glutKeyboardFunc(keyboard);	
	glutIdleFunc(idle);
//    draw_light();
	
	/*Enter the GLUT event processing loop which never returns.
	it will call different registered CALLBACK according
	to different events. */
	glutMainLoop();

        return 0;
}
