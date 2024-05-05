#include <GL/glut.h>
#include <iostream>
using namespace std;

int x1, x2, y1, y2;
int ch;

void init() {
    glClearColor(1, 1, 1, 1);
    glColor3f(0, 0, 0);
    gluOrtho2D(-500, 500, -500, 500);
}

void drawPoint(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

// DDA line drawing algorithm for simple and dashed lines
void ddaLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float xIncrement = (float)dx / steps;
    float yIncrement = (float)dy / steps;
    float x = x1;
    float y = y1;
    bool draw = true; // flag to control dashed line drawing

    for (int i = 0; i < steps; i++) {
        if (draw) {
            drawPoint(x, y);
        }
        x += xIncrement;
        y += yIncrement;
        draw = !draw; // toggle draw flag to create dashed line effect
    }
}

// Bresenham line drawing algorithm for simple and dashed lines
void bresenhamLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;
    int error = dx - dy;
    bool draw = true; // flag to control dashed line drawing

    while (x1 != x2 || y1 != y2) {
        if (draw) {
            drawPoint(x1, y1);
        }
        int error2 = error * 2;

        if (error2 > -dy) {
            error -= dy;
            x1 += sx;
        }

        if (error2 < dx) {
            error += dx;
            y1 += sy;
        }

        draw = !draw; // toggle draw flag to create dashed line effect
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(3);
    glLineWidth(3);

    switch (ch) {
        case 1:
            ddaLine(x1, y1, x2, y2);
            break;
        case 2:
            bresenhamLine(x1, y1, x2, y2);
            break;
    }

    glBegin(GL_LINES);
    glVertex2i(-500, 0);
    glVertex2i(500, 0);
    glVertex2i(0, -500);
    glVertex2i(0, 500);
    glEnd();

    glFlush();
}

int main(int argc, char** argv) {
    cout << "Enter x1 and y1" << endl;
    cin >> x1 >> y1;
    cout << "Enter x2 and y2" << endl;
    cin >> x2 >> y2;
    cout << "1. DDA Line\n2. Bresenham Line" << endl;
    cout << "Enter your choice: ";
    cin >> ch;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Line Drawing");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
