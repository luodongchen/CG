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

void Draw_cube() {
    glColor3f(0.2, 0.6, 0.8);
    glBegin(GL_QUADS);
    // Front Face
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);

    // Back Face
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);

    // Top Face
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);

    // Bottom Face
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);

    // Right face
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);

    // Left Face
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();
}

void Draw() {
    Draw_cube();
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
