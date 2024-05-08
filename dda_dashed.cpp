#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

int x1, x2, y1_coord, y2;

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glColor3f(0.0, 0.0, 0.0);
    gluOrtho2D(-250, 250, -250, 250);
}
void drawAxes() {
    glBegin(GL_LINES);
    // X-axis
    glVertex2i(-500, 0);
    glVertex2i(500, 0);
    // Y-axis
    glVertex2i(0, -500);
    glVertex2i(0, 500);
    glEnd();
}

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void ddaDashedLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps;

    if (abs(dx) > abs(dy)) {
        steps = abs(dx);
    }
    else {
        steps = abs(dy);
    }

    float xIncrement = (float)dx / steps;
    float yIncrement = (float)dy / steps;
    float x = x1;
    float y = y1;

    int dashLength = 10;
    int dashCount = 0;

    for (int i = 0; i < steps; i++) {
        if (dashCount < dashLength) {
            drawPixel((int)x, (int)y);
            dashCount++;
        } else {
            dashCount = 0;
        }

        x += xIncrement;
        y += yIncrement;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxes();
//    ddaDashedLine(x1, y1_coord, x2, y2);
    ddaDashedLine(-100, -100, 100, 100);
    glFlush();
}

int main(int argc, char** argv) {
/*
    cout << "Enter x1 and y1: ";
    cin >> x1 >> y1_coord;
    cout << "Enter x2 and y2: ";
    cin >> x2 >> y2;
*/

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA Dashed Line");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
