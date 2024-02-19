#define STB_IMAGE_IMPLEMENTATION
#include <stb-master/stb_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <gl/glut.h>
#include <gl/freeglut.h>

#define ImageWidth 64
#define ImageHeight 64
#define ImageChannel GL_RGB

static GLfloat spin = 0.0;
static GLfloat zoom = -200.0;
static int mouse_leftClick_state = 0;
static int mouse_rightClick_state = 0;
static GLsizei my_Window_width;
static GLsizei my_Window_height;
static int camera_angle_state = 0;

static GLubyte* myWoodImage;		// 0
static GLubyte* mySkyImage;			// 1
static GLubyte* myMetalImage;		// 2
static GLubyte* myCheckBlueImage;	// 3
static GLubyte* myWoodImage1;		// 4
static GLubyte* win;		// 5
static GLubyte* wall;		// 6


static GLuint texName[7];

void loadMyImages(void);
void drawWall(GLfloat x, GLfloat y, GLfloat z, GLfloat px, GLfloat py, GLfloat pz, GLubyte red, GLubyte green, GLubyte blue);
void display(void);
void spinDisplay(void);
void init();
void reshape(int w, int h);
void keyboard(unsigned char key, int x, int y);
void mouse(int button, int state, int x, int y);

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(1280, 720);
	glutInitWindowPosition(100, 25);
	glutCreateWindow("seom-j");
	init();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
	return 0;
}


void loadMyImages(void) {
	int imgWidth = ImageWidth, imgHeight = ImageHeight, imgChannel = ImageChannel;
	myWoodImage = stbi_load("asset/wood.png", &imgWidth, &imgHeight, &imgChannel, 0);
	mySkyImage = stbi_load("asset/sky.png", &imgWidth, &imgHeight, &imgChannel, 0);
	myMetalImage = stbi_load("img/metal.png", &imgWidth, &imgHeight, &imgChannel, 0);
	myCheckBlueImage = stbi_load("img/bluecheck.png", &imgWidth, &imgHeight, &imgChannel, 0);
	myWoodImage1 = stbi_load("img/wood1.png", &imgWidth, &imgHeight, &imgChannel, 0);
	win = stbi_load("img/win.png", &imgWidth, &imgHeight, &imgChannel, 0);
	wall = stbi_load("img/wall.png", &imgWidth, &imgHeight, &imgChannel, 0);


	if (myWoodImage && myMetalImage && mySkyImage && myCheckBlueImage && wall) {
		printf("이미지 로드 성공, 높이 : %d/ 길이 : %d", imgHeight, imgWidth);
	}
	else {
		printf("ERROR");
	}

	return;
}

void drawWall(GLfloat x, GLfloat y, GLfloat z, GLfloat px, GLfloat py, GLfloat pz, GLubyte red, GLubyte green, GLubyte blue) {
	// (x, y, z) 크기 관련 파라미터
	// (px, py, pz) 위치관련 파라미터
	// (red, green, blue) 색상 관련 파라미터

	glPushMatrix();
	glTranslatef(px, py, pz);
	glColor3ub(red, green, blue);
	// >>>>>>>>>>>>>>>
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1 * (x / 2.0), -1 * (y / 2.0), -0.1);
	glTexCoord2f(1.0, 0.0); glVertex3f(1 * (x / 2.0), -1 * (y / 2.0), -0.1);
	glTexCoord2f(1.0, 1.0); glVertex3f(1 * (x / 2.0), 1 * (y / 2.0), -0.1);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1 * (x / 2.0), 1 * (y / 2.0), -0.1);
	glEnd();//

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1 * (x / 2.0), -1 * (y / 2.0), -0.1);
	glTexCoord2f(1.0, 0.0); glVertex3f(1 * (x / 2.0), -1 * (y / 2.0), -0.1);
	glTexCoord2f(1.0, 1.0); glVertex3f(1 * (x / 2.0), -1 * (y / 2.0), -1 * (z + 0.1));
	glTexCoord2f(0.0, 1.0); glVertex3f(-1 * (x / 2.0), -1 * (y / 2.0), -1 * (z + 0.1));
	glEnd();//

	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1 * (x / 2.0), 1 * (y / 2.0), -0.1);
	glTexCoord2f(1.0, 0.0); glVertex3f(1 * (x / 2.0), 1 * (y / 2.0), -0.1);
	glTexCoord2f(1.0, 1.0); glVertex3f(1 * (x / 2.0), 1 * (y / 2.0), -1 * (z + 0.1));
	glTexCoord2f(0.0, 1.0); glVertex3f(-1 * (x / 2.0), 1 * (y / 2.0), -1 * (z + 0.1));
	glEnd();//
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0); glVertex3f(1 * (x / 2.0), -1 * (y / 2.0), -1 * (z + 0.1));
	glTexCoord2f(0.0, 0.0); glVertex3f(1 * (x / 2.0), -1 * (y / 2.0), -0.1);
	glTexCoord2f(0.0, 1.0); glVertex3f(1 * (x / 2.0), 1 * (y / 2.0), -0.1);
	glTexCoord2f(1.0, 1.0); glVertex3f(1 * (x / 2.0), 1 * (y / 2.0), -1 * (z + 0.1));
	glEnd();//
	glBegin(GL_POLYGON);
	glTexCoord2f(0.0, 0.0); glVertex3f(-1 * (x / 2.0), -1 * (y / 2.0), -1 * (z + 0.1));
	glTexCoord2f(1.0, 0.0); glVertex3f(-1 * (x / 2.0), -1 * (y / 2.0), -0.1);
	glTexCoord2f(1.0, 1.0); glVertex3f(-1 * (x / 2.0), 1 * (y / 2.0), -0.1);
	glTexCoord2f(0.0, 1.0); glVertex3f(-1 * (x / 2.0), 1 * (y / 2.0), -1 * (z + 0.1));
	glEnd();//
	glBegin(GL_POLYGON);
	glTexCoord2f(1.0, 0.0); glVertex3f(-1 * (x / 2.0), -1 * (y / 2.0), -1 * (z + 0.1));
	glTexCoord2f(0.0, 0.0); glVertex3f(1 * (x / 2.0), -1 * (y / 2.0), -1 * (z + 0.1));
	glTexCoord2f(0.0, 1.0); glVertex3f(1 * (x / 2.0), 1 * (y / 2.0), -1 * (z + 0.1));
	glTexCoord2f(1.0, 1.0); glVertex3f(-1 * (x / 2.0), 1 * (y / 2.0), -1 * (z + 0.1));
	glEnd();
	glPopMatrix();
	void;
}

void display(void) {
	GLfloat mat_ambient[] = { 0.3, 0.5, 0.1, 1.0 };
	GLfloat mat_diffuse[] = { 0.25, 0.25, 0.25, 1.0 };
	GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	reshape(my_Window_width, my_Window_height);	// 줌 인/아웃을 위해 한번 더 호출함.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);


	glRotatef(spin, 0.0, 0.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, texName[4]);
	//glColor3ub(179, 177, 178);
	glRectf(-50.0, -40.0, 50.0, 40.0);
	glBindTexture(GL_TEXTURE_2D, 0);


	glBindTexture(GL_TEXTURE_2D, texName[6]);
	// 가로 벽
	drawWall(100.0, 2.0, 50.0, 0.0, 40.0, 0.0, 168, 173, 169);
	glPushMatrix();
	// 세로 벽
	glRotatef(90.0, 0.0, 0.0, 1.0);
	//창가 아래 벽
	drawWall(40.0, 2.0, 12.5, 10.0, -50.0, 0.0, 168, 173, 169);
	//창가 왼쪽 벽
	drawWall(30.0, 2.0, 50.0, -25.0, -50.0, 0.0, 168, 173, 169);
	//창가 오른쪽 벽
	drawWall(10.0, 2.0, 50.0, 35.0, -50.0, 0.0, 168, 173, 169);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);


	// 침대 머리 부분
	glBindTexture(GL_TEXTURE_2D, texName[0]);

	glPushMatrix();
	drawWall(1.0, 1.0, 35.0, 48.0, 39.0, 0.0, 137, 109, 99);
	drawWall(18.0, 1.0, 20, 39.0, 39.0, -15.0, 137, 109, 99);
	drawWall(1.0, 1.0, 35.0, 30.0, 39.0, 0.0, 137, 109, 99);

	// 침대 다리 부분
	drawWall(1.0, 1.0, 15.0, 48.0, -13.0, 0.0, 137, 109, 99);
	drawWall(1.0, 1.0, 15.0, 30.0, -13.0, 0.0, 137, 109, 99);

	// 침대 몸통 부분
	glPushMatrix();
	glRotatef(90.0, 0, 0, 1);
	drawWall(54.0, 2.0, 10.0, 13.5, -30.0, -5.0, 137, 109, 99);
	drawWall(54.0, 2.0, 10.0, 13.5, -48.0, -5.0, 137, 109, 99);
	glRotatef(-90.0, 0, 0, 1);
	drawWall(18.0, 2.0, 10.0, 39.0, -13.0, -5.0, 137, 109, 99);
	drawWall(18.0, 2.0, 10.0, 39.0, 39.0, -5.0, 137, 109, 99);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);



	// 매트리스
	glBindTexture(GL_TEXTURE_2D, texName[3]);
	drawWall(18.0, 52.0, 10.0, 39.0, 13.0, -8.0, 41, 64, 82);

	//베개
	drawWall(10.0, 8.0, 3.0, 39.0, 35.0, -18.0, 64, 114, 148);

	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();


	glBindTexture(GL_TEXTURE_2D, texName[4]);
	// 창문 프레임
	glPushMatrix();
	drawWall(3.0, 2.0, 39.0, 51.0, -10.0, -12.5, 245, 245, 245);
	drawWall(3.0, 2.0, 39.0, 51.0, 10.0, -12.5, 245, 245, 245);
	drawWall(3.0, 2.0, 39.0, 51.0, 30.0, -12.5, 245, 245, 245);
	drawWall(3.0, 40.0, 2.0, 51.0, 10.0, -12.5, 245, 245, 245);
	drawWall(3.0, 40.0, 2.0, 51.0, 10.0, -50.0, 245, 245, 245);
	glBindTexture(GL_TEXTURE_2D, 0);

	// 하늘색 창문
	glBindTexture(GL_TEXTURE_2D, texName[1]);
	drawWall(1.0, 40.0, 37.5, 51.0, 10.0, -12.5, 178, 235, 244);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

	//책상

	drawWall(55.0, 25.0, 5.0, 1.0, 27.0, -12.5, 245, 245, 245);

	//책상 다리
	glBindTexture(GL_TEXTURE_2D, texName[2]);
	glPushMatrix();
	drawWall(5.0, 1.0, 12.5, -20.0, 24.0, 0.0, 71, 66, 63);
	drawWall(5.0, 10.0, 1.0, -20.0, 29.0, 0.0, 71, 66, 63);
	drawWall(5.0, 1.0, 12.5, -20.0, 34.0, 0.0, 71, 66, 63);
	drawWall(5.0, 1.0, 12.5, 22.0, 24.0, 0.0, 71, 66, 63);
	drawWall(5.0, 10.0, 1.0, 22.0, 29.0, 0.0, 71, 66, 63);
	drawWall(5.0, 1.0, 12.5, 22.0, 34.0, 0.0, 71, 66, 63);
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);

	//의자
	glPushMatrix();
	glBindTexture(GL_TEXTURE_2D, texName[2]);
	glTranslatef(12.0, 7.0, 0.0);
	//의자 다리
	drawWall(1.0, 1.0, 25.0, -19.0, 0.0, 0.0, 71, 66, 63);
	drawWall(1.0, 1.0, 25.0, -11.0, 0.0, 0.0, 71, 66, 63);
	drawWall(1.0, 1.0, 10.0, -19.0, 8.0, 0.0, 71, 66, 63);
	drawWall(1.0, 1.0, 10.0, -11.0, 8.0, 0.0, 71, 66, 63);
	//의자 등받이
	drawWall(8.0, 1.0, 8.0, -15.0, 0.0, -15.0, 71, 66, 63);
	//의자 바닥
	drawWall(9.0, 9.0, 2.0, -15.0, 4.0, -10.0, 71, 66, 63);
	glBindTexture(GL_TEXTURE_2D, 0);
	glPopMatrix();


	glBindTexture(GL_TEXTURE_2D, texName[2]);
	//모니터 목
	glPushMatrix();
	glTranslatef(20.0, 35.0, -16.9);
	glRotatef(0.0, 0.0, 0.0, 1.0);
	//받침대
	drawWall(5.0, 3.0, 1.0, -23.0, 0.0, 0.0, 184, 184, 184);
	drawWall(5.0, 1.0, 7.0, -23.0, 2.0, 0.0, 184, 184, 184);
	drawWall(5.0, 2.0, 1.0, -23.0, 1.0, -6.0, 184, 184, 184);
	//모니터
	drawWall(15.0, 2.0, 13.0, -23.0, 0.0, -6.0, 71, 66, 63);
	glBindTexture(GL_TEXTURE_2D, 0);

	//화면
	glBindTexture(GL_TEXTURE_2D, texName[5]);
	drawWall(13.0, 0.2, 11.0, -23.0, -0.95, -6.8, 245, 245, 245);
	glBindTexture(GL_TEXTURE_2D, 0);

	glPopMatrix();

	//키보드
	glPushMatrix();
	glTranslatef(13.0, 25.0, -17.0);
	//키보드 판
	drawWall(10.0, 6.5, 1.0, -17.0, 0.0, 0.0, 25, 25, 25);
	//자판키
	drawWall(6.0, 3.5, 0.5, -15.5, 0.0, -0.6, 245, 245, 245);
	//숫자키
	drawWall(2.0, 3.5, 0.5, -20.3, 0.0, -0.6, 245, 245, 245);
	glPopMatrix();

	glPopMatrix();
	glutSwapBuffers();
	return;
}
void spinDisplay(void) {
	spin += 0.1;
	if (spin > 360.0) {
		spin = spin - 360.0;
	}
	glutPostRedisplay();

	return;
}
void init() {
	glClearColor(0.83, 0.83, 0.83, 0.0); // 배경 회색


	GLfloat white_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat white_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat white_specular[] = { 1.0, 1.0, 1.0, 1.0 };
	GLfloat white_light_pos[] = { 1.0, 27.0, -12.5, 1.0 };
	GLfloat white_lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat white_shininess[] = { 40.0 };
	GLfloat white_local_view[] = { 0.0 };

	// 파란색 광원
	GLfloat blue_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat blue_diffuse[] = { 0.3, 0.3, 1.0, 1.0 };
	GLfloat blue_specular[] = { 0.3, 0.3, 1.0, 1.0 };
	GLfloat blue_light_pos[] = { -23.0, 0.0, -6.0, 1.0 };
	GLfloat blue_lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
	GLfloat blue_shininess[] = { 40.0 };
	GLfloat blue_local_view[] = { 0.0 };

	glShadeModel(GL_FLAT);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);


	loadMyImages();
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glGenTextures(7, texName);


	glBindTexture(GL_TEXTURE_2D, texName[0]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, myWoodImage);
	stbi_image_free(myWoodImage);

	glBindTexture(GL_TEXTURE_2D, texName[1]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, mySkyImage);
	stbi_image_free(mySkyImage);

	glBindTexture(GL_TEXTURE_2D, texName[2]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, myMetalImage);
	stbi_image_free(myMetalImage);

	glBindTexture(GL_TEXTURE_2D, texName[3]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, myCheckBlueImage);
	stbi_image_free(myCheckBlueImage);

	glBindTexture(GL_TEXTURE_2D, texName[4]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, myWoodImage1);
	stbi_image_free(myWoodImage1);

	glBindTexture(GL_TEXTURE_2D, texName[5]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, win);
	stbi_image_free(win);

	glBindTexture(GL_TEXTURE_2D, texName[6]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ImageWidth, ImageHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, wall);
	stbi_image_free(wall);


	// 흰색 광원 설정
	glLightfv(GL_LIGHT0, GL_AMBIENT, white_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, white_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, white_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, white_shininess);
	glLightfv(GL_LIGHT0, GL_POSITION, white_light_pos);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, white_lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, white_local_view);

	// 파란색 광원 설정
	glLightfv(GL_LIGHT1, GL_AMBIENT, blue_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, blue_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, blue_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, blue_shininess);
	glLightfv(GL_LIGHT1, GL_POSITION, blue_light_pos);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, blue_lmodel_ambient);
	glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, blue_local_view);

	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); //화면의 색과 텍스쳐 맵핑 소스의 색을 어떻게 조합하여 표현하는지 설정
	return;
}
void reshape(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	my_Window_width = w;
	my_Window_height = h;

	glLoadIdentity();
	gluPerspective(60.0, (GLsizei)w / (GLsizei)h, 0.1, 1000.0);
	if (camera_angle_state == 0)
		gluLookAt(0.0, zoom, zoom / 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, -5.0);	// 카메라 위치
	else if (camera_angle_state == 1)
		gluLookAt(0.0, 0.0, zoom, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);	// 카메라 위치

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	return;
}
void keyboard(unsigned char key, int x, int y) {
	switch (key) {
	case '0':
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		break;
	case '1':
		glEnable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		break;
	case '2':
		glEnable(GL_LIGHTING);
		glEnable(GL_LIGHT0);
		glEnable(GL_LIGHT1);
		break;
	case '3':
		glEnable(GL_LIGHTING);
		glDisable(GL_LIGHT0);
		glDisable(GL_LIGHT1);
		break;
	case '4':
		glDisable(GL_TEXTURE_2D);
		break;
	case '5':
		glEnable(GL_TEXTURE_2D);
		break;
	default:
		break;
	}
	glutPostRedisplay();
	return;
}
void mouse(int button, int state, int x, int y) {
	switch (button) {
		// 왼쪽 마우스 버튼 : 회전
	case GLUT_LEFT_BUTTON:
		// glutIdleFunc() : callback함수를 아무짓도 안 할때 계속 refresh한다는 뜻임.
		if (state == GLUT_DOWN && mouse_leftClick_state == 0) {
			printf("%d\n", mouse_leftClick_state);
			mouse_leftClick_state = 1;
			glutIdleFunc(NULL);
		}
		else if (state == GLUT_DOWN && mouse_leftClick_state == 1) {
			printf("%d\n", mouse_leftClick_state);
			mouse_leftClick_state = 0;
			glutIdleFunc(spinDisplay);
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN && mouse_rightClick_state == 0) {	//1.5배 줌
			printf("눌림. %d\n", mouse_rightClick_state);
			mouse_rightClick_state += 1;
			mouse_rightClick_state %= 3;
			zoom /= 1.5;
		}
		else if (state == GLUT_DOWN && mouse_rightClick_state == 1) {	//2배 줌
			printf("눌림. %d\n", mouse_rightClick_state);
			mouse_rightClick_state += 1;
			mouse_rightClick_state %= 3;
			zoom = (zoom * 1.5) / 2.0;
		}
		else if (state == GLUT_DOWN && mouse_rightClick_state == 2) {	// 1배 줌
			printf("눌림. %d\n", mouse_rightClick_state);
			mouse_rightClick_state += 1;
			mouse_rightClick_state %= 3;
			zoom *= 2.0;
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
	return;
}
