#include <GL/glut.h>

// Cube and sphere sizes
float cube1_size = 0.5f;
float cube2_size = 0.25f;
float sphere1_size = 0.2f;
float sphere2_size = 0.1f;

// Cube and sphere colors
float red[] = { 1.0f, 0.0f, 0.0f };
float blue[] = { 0.0f, 0.0f, 1.0f };
float yellow[] = { 1.0f, 1.0f, 0.0f };
float green[] = { 0.0f, 1.0f, 0.0f };

// Camera parameters
float cam_pos[] = { 1.0f, 1.0f, 1.0f }; // 위치
float cam_lookat[] = { 0.0f, 0.0f, 0.0f }; // 보고 있음

float cam_up[] = { 0.0f, 1.0f, 0.0f };
float cam_fov = 45.0f;
float cam_aspect = 1.0f;
float cam_near = 0.1f;
float cam_far = 10.0f;

// Scene rotation and zoom parameters
float rot_angle = 0.0f;
float zoom_factor = 1.0f;
float mouse_x = 0.0f;
float mouse_y = 0.0f;
int mouse_dragging_middle = 0;
int mouse_dragging_right = 0;
float prev_x = 0, prev_y = 0;

// Draw a cube of the given size and color at the given position
void draw_cube(float size, float* color, float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(color[0], color[1], color[2]);
    glutSolidCube(size);
    glPopMatrix();
}

// Draw a sphere of the given size and color at the given position
void draw_sphere(float size, float* color, float x, float y, float z) {
    glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(color[0], color[1], color[2]);
    glutSolidSphere(size, 20, 20);
    glPopMatrix();
}

// Display callback function
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /*
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 0.0, 1.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(0.0, 1.0, 0.0);
    glEnd();
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, 0.0);
    glVertex3f(1.0, 0.0, 0.0);
    glEnd();
    */

    // Set up perspective projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(cam_fov, cam_aspect, cam_near, cam_far);

    // Set up camera position and orientation
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(cam_pos[0], cam_pos[1], cam_pos[2], cam_lookat[0], cam_lookat[1], cam_lookat[2], cam_up[0], cam_up[1], cam_up[2]);

    // Apply scene rotation and zoom
    glPushMatrix();
    glTranslatef(mouse_x, mouse_y, 0.0f);
    glScalef(zoom_factor, zoom_factor, zoom_factor);
    glRotatef(rot_angle, 0.0f, 0.0f, 1.0f);

    // Draw the cubes and spheres
    draw_cube(cube1_size, red, 0.1f, 0.0f, -0.1f);
    draw_cube(cube2_size, blue, 0.5f, 0.0f, -0.5f);
    draw_sphere(sphere1_size, yellow, -0.5f, -0.0f, 0.5f);
    draw_sphere(sphere2_size, green, -0.25f, -0.0f, 0.25f);

    glPopMatrix();

    glutSwapBuffers();
}

// Reshape callback function
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    cam_aspect = (float)width / (float)height;
}

// Mouse callback function
void mouse(int button, int state, int x, int y) {
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        if (x > glutGet(GLUT_WINDOW_WIDTH) / 2) {
            rot_angle += 10.0f;
        }
        else {
            rot_angle -= 10.0f;
        }
        glutPostRedisplay();
    }
    else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_DOWN) {
        mouse_x = 2.0f * ((float)x / glutGet(GLUT_WINDOW_WIDTH) - 0.5f);
        mouse_y = 2.0f * ((float)(glutGet(GLUT_WINDOW_HEIGHT) - y) / glutGet(GLUT_WINDOW_HEIGHT) - 0.5f);
        mouse_dragging_middle = 1;
    }
    else if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
        mouse_dragging_middle = 0;
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN) {
        if (x > prev_x && y > prev_y) {  // drag toward lower right corner -> zoom in
            zoom_factor *= 1.1f;
        }
        else {  // otherwise -> zoom out
            zoom_factor /= 1.1f;
        }
        prev_x = x;
        prev_y = y;
        mouse_dragging_right = 1;
        glutPostRedisplay();
    }
    else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP) {
        mouse_dragging_right = 0;
    }
}

// Motion callback function
void motion(int x, int y) {
    if (mouse_dragging_middle) {
        float dx = 2.0f * ((float)x / glutGet(GLUT_WINDOW_WIDTH) - 0.5f) - mouse_x;
        float dy = 2.0f * ((float)(glutGet(GLUT_WINDOW_HEIGHT) - y) / glutGet(GLUT_WINDOW_HEIGHT) - 0.5f) - mouse_y;
        mouse_x += dx;
        mouse_y += dy;
        glutPostRedisplay();
    }
    if (mouse_dragging_right) {
        if (prev_x == 0 && prev_y == 0) {
            prev_x = x;
            prev_y = y;
        }
        else {
            if (x > prev_x && y > prev_y) {  // drag toward lower right corner -> zoom in
                zoom_factor *= 1.1f;
            }
            else {  // otherwise -> zoom out
                zoom_factor /= 1.1f;
            }
            prev_x = x;
            prev_y = y;
            glutPostRedisplay();
        }
    }
}

// Main function
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutCreateWindow("21011591 서민정");
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouse);
    glutMotionFunc(motion);
    glEnable(GL_DEPTH_TEST);
    glutMainLoop();
    return 0;
}
