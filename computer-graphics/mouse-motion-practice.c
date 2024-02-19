#include<GL/glut.h>
// opengl libraries

float red = 1.0, green = 1.0, blue = 1.0;
int scale, mouseCurPositionX, mouseCurPositionY, startMovement, mouseCurButton;

void mydisplay() {
	glClear(GL_COLOR_BUFFER_BIT); // 버퍼 클리어
	glColor3f(red, green, blue);

	//사각형 그리기
	glBegin(GL_POLYGON);
	glVertex2f(-0.5, -0.5); // 왼아래
	glVertex2f(-0.5, 0.5); // 왼위
	glVertex2f(0.0, 0.5); // 오른 위
	glVertex2f(0.0, -0.5); //오른 아래
	glEnd();

	//삼각형 그리기
	glBegin(GL_POLYGON);
	glVertex2f(0.1, 0); // 왼아래
	glVertex2f(0.5, 0.5); // 오른 위
	glVertex2f(0.5, 0.0); // 오른 아래
	glEnd();

	//오각형 그리기
	glBegin(GL_POLYGON);
	glVertex2f(0.1, -0.5); // 왼 아래
	glVertex2f(0.1, -0.2); // 왼 위  	
	glVertex2f(0.3, -0.1);  // 윗 꼭짓점
	glVertex2f(0.5, -0.2);  // 오른 위
	glVertex2f(0.5, -0.5);  // 오른 아래
	glEnd();

	glFlush();
}

void mouseMotion(int x, int y) {
	if (mouseCurButton == GLUT_LEFT_BUTTON) {
		scale = x - mouseCurPositionX;
		if (scale > 0) {
			red = 1.0; green = 0.0; blue = 0.0;
		}
		else {
			red = 0.0; green = 1.0; blue = 0.0;
		}
		glutPostRedisplay();
		mouseCurPositionX = x;
		mouseCurPositionY = y;
	}
}

void init() {
	glClearColor(1.0, 1.0, 0.0, 1.0); // 배경 (r, g, b, 투명도)
	glColor3f(1.0, 1.0, 1.0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity(); // 카메라 설정

	gluOrtho2D(-1.0, 1.0, -1.0, 1.0); // 2차원
}

int main(int argc, char** argv) {

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("seom-j");
	glutDisplayFunc(mydisplay);
	glutMotionFunc(mouseMotion);
	init();
	glutMainLoop();
}
