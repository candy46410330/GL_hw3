#include <glut.h>
#include <windows.h> 
#include <gl\gl.h> 
#include <gl\glu.h> 
#include <glaux.h>
#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "SMFLoader.h"
using namespace std;
#define TIMER 33
#ifdef WIN32 
#pragma warning( disable : 4305) 
#endif 
static float xrot;
GLUquadric *quad;
SMFLoader loader;   //(2) declare SMFLoader
void keyboard();
void display();

float Lfleg1 = 0, Lfleg2 = 0, Rgleg1 = 0, Rgleg2 = 0, Larm1 = 0, Larm2 = 0, Rarm1 = 0, Rarm2 = 0;
float hipy = 0, hipx = 0, hip_ground = 0;
int LL1change = 5, LL2change = 5;
int RL1change = 5, RL2change = 5;
int LA1change = 5, LA2change = 5;
int RA1change = 5, RA2change = 5;
int hipychange = 5;
int hipxchange = 5;
float dischange = 0.1;
float dis = 0;
float dis2 = 0;
float dis3 = 0;
int key = 0;
float light_position[] = { 0, 0, 20 };    //光源的位置

//float* tmp = new float[9];
//float* putin = new float[9];

// angle of rotation for the camera direction
float angle = 0.0;
// actual vector representing the camera’s direction
float lx = 0.0f, lz = -1.0f;
// XZ position of the camera
float x = 0.0f, z = 5.0f;
float fraction = 0.1f;

void init(){
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_COLOR_MATERIAL);
}
static float rotateAngle = 0;
static int times1 = 0;
void selfRotateWhole(){
	times1++;
	if (times1 > 50)
		times1 = 0;
	if (times1 % 50 == 0){
		Rarm1 = ((int)Rarm1 - RA1change);
		if (Rarm1>60)
			RA1change = -RA1change;
		if (Rarm1<-60)
			RA1change = -RA1change;

		Larm1 = ((int)Larm1 + LA1change);
		if (Larm1>60)
			LA1change = -LA1change;
		if (Larm1<-60)
			LA1change = -LA1change;
		Lfleg1 = ((int)Lfleg1 + LL1change);
		if (Lfleg1>60)
			LL1change = -LL1change;
		if (Lfleg1<-60)
			LL1change = -LL1change;
		Rgleg1 = ((int)Rgleg1 - RL1change);
		if (Rgleg1>60)
			RL1change = -RL1change;
		if (Rgleg1<-60)
			RL1change = -RL1change;
	}
}
void SetLightSource(){
	float light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	float light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glEnable(GL_LIGHTING);                           //開燈

	// 設定發光體的光源的特性
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);      //環境光(Ambient Light)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);      //散射光(Diffuse Light)
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);      //反射光(Specular Light)

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);      //光的座標

	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);                        //深度測試
}
void DisSetLightSource(){
	float light_ambient[] = { 1.0, 1.0, 1.0, 1.0 };
	float light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	float light_specular[] = { 1.0, 1.0, 1.0, 1.0 };

	glDisable(GL_LIGHTING);                           //開燈

	// 設定發光體的光源的特性
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);      //環境光(Ambient Light)
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);      //散射光(Diffuse Light)
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);      //反射光(Specular Light)

	glLightfv(GL_LIGHT0, GL_POSITION, light_position);      //光的座標

	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);                        //深度測試
}
void SetMaterial(){
	float material_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
	float material_diffuse[] = { 0.3, 0.3, 0.3, 1.0 };
	float material_specular[] = { 0.2, 0.2, 0.2, 1.0 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
}

void drawScene(GLenum order){
	GLfloat pos[4] = { -2.8, 10., 1.8, 1. };
	glLightfv(GL_LIGHT1, GL_POSITION, pos);
	
	glPushMatrix();
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glFrontFace(order);
	/* Draw the walls
	glColor3f(1., 1., 0.);
	glBegin(GL_QUADS);
	glNormal3f(1., 0., 0.);
	glVertex3f(-6., 4., 5.);
	glVertex3f(-6., -4., 5.);
	glVertex3f(-6., -4., -3.5);
	glVertex3f(-6., 4., -3.5);*/

	/*glVertex3f(-6., 4., 5.);  //鏡子的位置
	glVertex3f(-6., -4., 5.);
	glVertex3f(-6., -4., -3.5);
	glVertex3f(-6., 4., -3.5);*/

	/*glNormal3f(0., 0., 1.);//X
	glVertex3f(-3., 3., -3.);
	glVertex3f(-3., -3., -3.);
	glVertex3f(3., -3., -3.);
	glVertex3f(3., 3., -3.);
	glNormal3f(-1., 0., 0.);
	glVertex3f(3., 3., -3.);
	glVertex3f(3., -3., -3.);
	glVertex3f(3., -3., 3.);
	glVertex3f(3., 3., 3.);*/
	glEnd();
	glDisable(GL_CULL_FACE);
	glRotatef(xrot, 1., 0., 0.);
	///////////////////////////////
	/*glPushMatrix();    //新物體
	glColor3f(1.0, 0.5, 0.5);
	glScalef(1, 1, 1);
	glTranslatef(1, 0., 0.); /// AAAA
	glRotatef(180, 0, 1, 0);
	glutSolidCube(6);
	glPopMatrix();*/
	//////////////////////////////////////
	glPopMatrix();
}
void display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	GLint viewport[4];
	glGetIntegerv(GL_VIEWPORT, viewport);
	double aspect = (double)viewport[2] / (double)viewport[3];
	gluPerspective(60, aspect, 1, 100);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, 9.5f, z,       //視角(初始:第一人稱)
		x + lx, 9.2f, z + lz,
		0.0f, 1.0f, 0.0f);
	// move back a bit
	glTranslatef(0, 0, -35);

	static float angle = 0;
	angle += 1.0f;

	glEnable(GL_BLEND);//啟動混和功能
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	///////////地板////////////// 我好感動....QQ
	glRotatef(hip_ground, 0.0, 1.0, 0.0);//轉地面換視野

	glPushMatrix(); //地板
	glColor3f(0.0, 1.0, 0.0);
	glScalef(10, 0.1, 10);
	glTranslatef(0, -170, -5);
	glRotatef(180, 0, 1, 0);
	glutSolidCube(20);
	glPopMatrix();
	//////////////////////////
	selfRotateWhole();
	glRotatef(hipy, 0.0, 1.0, 0.0);//左轉
	glRotatef(-hipx, 0.0, 1.0, 0.0);//右轉
	////////////////////////////
	glPushMatrix();    //新物體
	glColor3f(1.0, 0.5, 0.5);
	glScalef(1, 1.5, 1);
	glTranslatef(-10, -10, -5);
	glRotatef(180, 0, 1, 0);
	glutSolidCube(10);
	glPopMatrix();
	///////////////////////////////
	glPushMatrix();   //頭
	glTranslatef(dis, 5, dis2 + 35);
	//glRotatef(angle, 0.1, 0.2, 0.5);
	glRotatef(0, 0, 1, 0);
	glColor3ub(255, 0, 255);
	glutSolidCube(5);
	//glPopMatrix();

	glPushMatrix();//身體
	glScalef(1, 2, 1);
	glTranslatef(-0, -3.8, 0);
	glColor3ub(255, 0, 0);
	glutSolidCube(5);
	//glPopMatrix();

	glPushMatrix();//腳1
	glScalef(0.5, 1, 1);
	glTranslatef(-7.8, -3, 0);
	glColor3ub(255, 100, 0);
	glutSolidCube(5);
	//glPopMatrix();

	glPushMatrix();//腳2
	glTranslatef(15.8, -0, 0);
	glColor3ub(255, 0, 160);
	glutSolidCube(5);
	//glPopMatrix();

	glPushMatrix();//手1
	glScalef(4, 0.25, 1);
	glTranslatef(-5.8, 20, 0);
	glColor3ub(0, 0, 255);
	glutSolidCube(5);
	//glPopMatrix();

	glPushMatrix();//手2
	glTranslatef(7.6, 0, 0);
	glColor3ub(255, 255, 0);
	glutSolidCube(5);
	glPopMatrix();
	glPopMatrix();
	//////////////////////////////////////

	///////////////load鴨////////////////
	glPushMatrix();
	glScalef(0.025,0.025,0.025);
	glTranslatef(-250,-20,0);
	//loader.getFace(9);
	float* vertex = NULL;
	float* color = NULL;
	//float* normal = NULL;
	for (int i = 0; i<loader.getFaceSize(); i++){	//每一迴圈畫一個三角面
		//loader.getFaces();
		//loader.getVertices();
		//loader.getColors();
		//loader.getFace(9);
		vertex = loader.getFace(i);// 得到一個面上的3個點  總共9個數值
		color = loader.getFaceColor(i);// 得到一個面上的每個點的顏色 總共9個數值
		//normal = loader.getFacenormal(i);
		glBegin(GL_TRIANGLES);

		if (color){
			glColor3f(255,255, 0);
			glVertex3f(vertex[0], vertex[1], vertex[2]);
			//glNormal3f(normal[0], normal[1], normal[2]);
		}
		if (color){
			glColor3f(255, 255, 0);
			glVertex3f(vertex[3], vertex[4], vertex[5]);
			//glNormal3f(normal[3], normal[4], normal[5]);
		}
		if (color){
			glColor3f(255, 255, 0);
			glVertex3f(vertex[6], vertex[7], vertex[8]);
			//glNormal3f(normal[6], normal[7], normal[8]);
		}
		glEnd();
	}
	glPopMatrix();
	glPopMatrix();
	///////////////////////////////////

	////////////鏡子////////////////////	
	/* Draw reflected scene first*/
	glPushMatrix();
	/* Mirrors lies in YZ plane, so scale by -1.0 in X axis */
	glScalef(0.,1., 1.); //X
	/* Mirror is 2.0 units from origin, so translate by 4.0*/
	glTranslatef(-0., -1., -35.5); //調整鏡子位置 (z)
	drawScene(GL_CW);
	glPopMatrix();

	/* draw mirror */
	glClear(GL_DEPTH_BUFFER_BIT);
	glPushAttrib(0xffffffff);
	glDisable(GL_LIGHTING);
	/* Create imperfect reflector effect by blending a black
	mirror over the reflected scene with alpha of 0.05 */
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glColor4f(0., 0., 0., 0.05);
	glBegin(GL_QUADS);
	glVertex3f(-6., 4., 5.);
	glVertex3f(-6., -4., 5.);
	glVertex3f(-6., -4., -3.5);
	glVertex3f(-6., 4., -3.5);
	glEnd();
	glPopAttrib();

	/* Draw the real scene */
	drawScene(GL_CCW);
	//glutSwapBuffers();
	{
		int err = glGetError();
		if (err != GL_NO_ERROR)
			printf("Error %x\n", err);
	}
	///////////////////////////////////////
	glutSwapBuffers();
}
void reshape(int w, int h){
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(50., (float)w / (float)h, 1., 20.);
}
void timer(int extra){
	glutPostRedisplay();
	glutTimerFunc(16, timer, 0);
}
static void idle(void){
	glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y){
	switch (key) {
		//Leftarm1
	/*case 'q':
		Larm1 = ((int)Larm1 + LA1change);
		if (Larm1>60)
			LA1change = -LA1change;
		if (Larm1<-60)
			LA1change = -LA1change;
		glutPostRedisplay();
		break;
		SetLightSource();*/
		//Leftarm2
	case 'w'://關燈
		DisSetLightSource();
	case 'a':		//
		Rarm1 = ((int)Rarm1 + RA1change);
		if (Rarm1>60)
			RA1change = -RA1change;
		if (Rarm1<-60)
			RA1change = -RA1change;
		glutPostRedisplay();
		break;
	case 's':		//
		Rarm2 = ((int)Rarm2 + RA2change);
		if (Rarm2>60)
			RA2change = -RA2change;
		if (Rarm2<-60)
			RA2change = -RA2change;
		glutPostRedisplay();
		break;
	case 'e':		//
		Lfleg1 = ((int)Lfleg1 + LL1change);
		if (Lfleg1>60)
			LL1change = -LL1change;
		if (Lfleg1<-60)
			LL1change = -LL1change;
		glutPostRedisplay();
		break;
	case 'r':		//
		Lfleg2 = ((int)Lfleg2 + LL2change);
		if (Lfleg2>60)
			LL2change = -LL2change;
		if (Lfleg2<-60)
			LL2change = -LL2change;
		glutPostRedisplay();
		break;
	case 'd':		//
		Rgleg1 = ((int)Rgleg1 + RL1change);
		if (Rgleg1>60)
			RL1change = -RL1change;
		if (Rgleg1<-60)
			RL1change = -RL1change;
		glutPostRedisplay();
		break;
	case 'f': //
		Rgleg2 = ((int)Rgleg2 + RL2change);
		if (Rgleg2>60)
			RL2change = -RL2change;
		if (Rgleg2<-60)
			RL2change = -RL2change;
		glutPostRedisplay();
		break;
	case 'g'://地板轉視野
		hip_ground = ((int)hip_ground + hipychange);
		if (hip_ground>360)
			hip_ground -= 360;
		glutPostRedisplay();
		break;
	case 'h'://地板左
		angle -= 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case 'j'://地板右
		angle += 0.01f;
		lx = sin(angle);
		lz = -cos(angle);
		break;
	case 'k'://地板前
		printf("groung_up\n");
		x += lx * fraction;
		z += lz * fraction;
		break;
	case 'l'://地板後
		x -= lx * fraction;
		z -= lz * fraction;
		break;
	case 'z'://轉身左
		hipy = ((int)hipy + hipychange);
		if (hipy>360)
			hipy -= 360;
		glutPostRedisplay();
		break;
	case 'x'://轉身右
		hipx = ((int)hipx + hipxchange);
		if (hipx>360)
			hipx -= 360;
		glutPostRedisplay();
		break;
	case 'c'://左
		dis = dis - dischange;
		glutPostRedisplay();
		printf("test\n");
		break;
	case 'v'://右
		dis = dis + dischange;
		glutPostRedisplay();
		break;
	case 'b'://前
		dis2 = dis2 + dischange;
		glutPostRedisplay();
		break;
	case 'n'://後
		dis2 = dis2 - dischange;
		glutPostRedisplay();
		break;
	}
}
int main(int argc, char **argv){
	loader.load("rubber_duck.smf");	// (3) Load model file contant
	glutInit(&argc, argv);
	glutInitWindowSize(640, 480);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow("Hw3");
	
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutTimerFunc(0, timer, 0);

	SetLightSource();
	SetMaterial();

	init();
	//glutIdleFunc(idle);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}
