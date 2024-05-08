#include <GL/glut.h>
#include <iostream>
#include <cmath>
using namespace std;

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    gluOrtho2D(0, 500, 0, 500);
}

void drawPixel(int x, int y) {
    glBegin(GL_POINTS);
    glVertex2i(x, y);
    glEnd();
}

void floodFill(int x, int y, float fillColor[3], float oldColor[3]) {
    float currentColor[3];
//    glReadPixels(x, y, 1, 1, GL_RGB, GL_FLOAT, currentColor);
    
    if (currentColor[0] == oldColor[0] && currentColor[1] == oldColor[1] && currentColor[2] == oldColor[2]) {
        glColor3fv(fillColor);
        drawPixel(x, y);
        floodFill(x + 1, y, fillColor, oldColor);
        floodFill(x - 1, y, fillColor, oldColor);
        floodFill(x, y + 1, fillColor, oldColor);
        floodFill(x, y - 1, fillColor, oldColor);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Draw a simple shape (e.g., a triangle)
    glColor3f(0.0, 0.0, 0.0);  // Triangle color (black)
    glBegin(GL_TRIANGLES);
    glVertex2i(100, 100);
    glVertex2i(200, 300);
    glVertex2i(300, 100);
    glEnd();
    
    // Seed point for flood fill algorithm
    int seedX = 200;
    int seedY = 200;
    
    // Fill color (e.g., red)
    float fillColor[3] = {1.0, 0.0, 0.0};
    
    // Old color (e.g., white)
    float oldColor[3] = {1.0, 1.0, 1.0};
    
    floodFill(seedX, seedY, fillColor, oldColor);
    
    glFlush();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(500, 500);
    glutCreateWindow("Flood Fill Algorithm");
    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}
