#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const double PI = 3.14159265359;

double theta = PI / 3;
double phi = PI / 4;
double R = 15.0;

void Camera_position(double R, double theta, double phi) {
    double x = R * sin(theta) * cos(phi);
    double y = R * sin(theta) * sin(phi);
    double z = R * cos(theta);
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

void Draw_coord_system() {
    glLineWidth(3.0);
    glColor3f(1.0, 0.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(-5.0, 0.0, 0.0);
    glVertex3f(5.0, 0.0, 0.0);
    glEnd();

    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, -5.0, 0.0);
    glVertex3f(0.0, 5.0, 0.0);
    glEnd();

    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_LINES);
    glVertex3f(0.0, 0.0, -5.0);
    glVertex3f(0.0, 0.0, 5.0);
    glEnd();
}

void Draw_wave() {
    const int gridX = 50;
    const int gridY = 50;
    const float size = 10.0f;
    const float step = size / gridX;
    const float waveFrequency = 2.0f;
    const float waveAmplitude = 1.0f;

    glColor3f(0.0, 0.5, 1.0);
    for (int i = 0; i < gridX; ++i) {
        for (int j = 0; j < gridY; ++j) {
            float x1 = -size / 2 + i * step;
            float x2 = x1 + step;
            float y1 = -size / 2 + j * step;
            float y2 = y1 + step;
            float z1 = waveAmplitude * sin(waveFrequency * x1) * cos(waveFrequency * y1);
            float z2 = waveAmplitude * sin(waveFrequency * x2) * cos(waveFrequency * y1);
            float z3 = waveAmplitude * sin(waveFrequency * x1) * cos(waveFrequency * y2);
            float z4 = waveAmplitude * sin(waveFrequency * x2) * cos(waveFrequency * y2);

            glBegin(GL_TRIANGLE_STRIP);
            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y1, z2);
            glVertex3f(x1, y2, z3);
            glVertex3f(x2, y2, z4);
            glEnd();
        }
    }
}

void Draw() {
    Draw_wave();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45, (float)SCR_WIDTH / SCR_HEIGHT, 1.0, 500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    Camera_position(10, theta, phi);
    Draw_coord_system();
    Draw();
    SDL_GL_SwapBuffers();
}

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(SCR_WIDTH, SCR_HEIGHT, 32, SDL_SWSURFACE | SDL_OPENGL);
    int running = 1;
    SDL_Event event;
    init();
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_LEFT) phi -= 0.1;
                if (event.key.keysym.sym == SDLK_RIGHT) phi += 0.1;
                if (event.key.keysym.sym == SDLK_UP) theta -= 0.1;
                if (event.key.keysym.sym == SDLK_DOWN) theta += 0.1;
            }
        }
        display();
    }
    SDL_Quit();
    return 0;
}
