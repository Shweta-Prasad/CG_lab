#include <GL/glut.h>
#include <cmath>

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 600

struct Planet {
    float distance; // Distance from the sun
    float angle;    // Current angle of rotation
    float speed;    // Angular speed of rotation
    float radius;   // Radius of the planet
    float color[3]; // RGB color of the planet
};

Planet sun = { 0.0f, 0.0f, 0.0f, 20.0f, {1.0f, 1.0f, 0.0f} }; // Sun
Planet planets[4] = { // Planets in the solar system
    {150.0f, 0.0f, 1.0f, 10.0f, {0.0f, 0.5f, 1.0f}},    // Earth
    {200.0f, 0.0f, 0.7f, 8.0f, {1.0f, 0.0f, 0.0f}},    // Mars
    {250.0f, 0.0f, 0.5f, 15.0f, {0.61f, 0.29f, 0.0f}}, // Jupiter (Brown)
    {300.0f, 0.0f, 0.3f, 12.0f, {0.8f, 0.6f, 0.0f}}    // Saturn (Dark Yellow)
};

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Draw sun at the center
    glColor3fv(sun.color);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; ++i) {
        float angle = i * M_PI / 180;
        glVertex2f(sun.radius * cos(angle), sun.radius * sin(angle));
    }
    glEnd();

    // Draw planets
    for (int i = 0; i < 4; ++i) {
        glColor3fv(planets[i].color);
        glPushMatrix();
        glRotatef(planets[i].angle, 0.0f, 0.0f, 1.0f);
        glTranslatef(planets[i].distance, 0.0f, 0.0f);
        glBegin(GL_POLYGON);
        for (int j = 0; j < 360; ++j) {
            float angle = j * M_PI / 180;
            glVertex2f(planets[i].radius * cos(angle), planets[i].radius * sin(angle));
        }
        glEnd();
        glPopMatrix();
        planets[i].angle += planets[i].speed;
    }

    // Draw orbit lines
    glColor3f(1.0f, 1.0f, 1.0f); // White
    for (int i = 0; i < 4; ++i) {
        glBegin(GL_LINE_LOOP);
        for (int j = 0; j < 360; ++j) {
            float angle = j * M_PI / 180;
            glVertex2f(planets[i].distance * cos(angle), planets[i].distance * sin(angle));
        }
        glEnd();
    }

    glutSwapBuffers();
}

void update(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, update, 0); // Update at ~60 FPS
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-WINDOW_WIDTH / 2, WINDOW_WIDTH / 2, -WINDOW_HEIGHT / 2, WINDOW_HEIGHT / 2);
    glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("Solar System Simulation");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}
