#include <GL/glut.h>
#include <iostream>
using namespace std;

int x1, x2, y1, y2;

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);  //white background
    glColor3f(0.0, 0.0, 0.0);  // Set drawing color to black
    gluOrtho2D(0, 500, 0, 500);  // Set the coordinate system range
}

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void ddaSolidLine(int x1, int y1, int x2, int y2) {
    int dx = x2 - x1;
    int dy = y2 - y1;
    //int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
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

    for (int i = 0; i < steps; i++) {
        drawPixel((int)x, (int)y);
        x += xIncrement;
        y += yIncrement;
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    //ddaSolidLine(x1, y1, x2, y2);
    ddaSolidLine(258, 269, 358, 369);
    glFlush();
}

int main(int argc, char** argv) {
 /* cout << "Enter x1 and y1: ";
    cin >> x1 >> y1;
    cout << "Enter x2 and y2: ";
    cin >> x2 >> y2;
*/
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("DDA Solid Line");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
