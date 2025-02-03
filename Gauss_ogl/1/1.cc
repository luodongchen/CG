#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
const double PI = 3.14159265359;

double Xmin = -10.0, Xmax = 10.0;
double Ymin = -10.0, Ymax = 10.0;

void Draw_coord_system() {
    glLineWidth(2.0);
    glColor3f(0.0, 0.0, 0.0);

    glBegin(GL_LINES);
    glVertex2f(Xmin, 0.0);
    glVertex2f(Xmax, 0.0);
    glVertex2f(0.0, Ymin);
    glVertex2f(0.0, Ymax);
    glEnd();
}

void Draw_equations() {
    glColor3f(1.0, 0.0, 0.0);
    glLineWidth(2.0);
    glBegin(GL_LINES);

    // Line for equation 1: 2x - 3y = 1 -> y = (2x - 1) / 3
    glVertex2f(Xmin, (2 * Xmin - 1) / 3);
    glVertex2f(Xmax, (2 * Xmax - 1) / 3);

    glColor3f(0.0, 0.0, 1.0);
    // Line for equation 2: 3x + 2y = 21 -> y = (21 - 3x) / 2
    glVertex2f(Xmin, (21 - 3 * Xmin) / 2);
    glVertex2f(Xmax, (21 - 3 * Xmax) / 2);

    glEnd();
}

void Draw_solution() {
    glPointSize(8.0);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2f(3, 5); // Solution of the system
    glEnd();
}

void Draw() {
    Draw_coord_system();
    Draw_equations();
    Draw_solution();
}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(Xmin, Xmax, Ymin, Ymax);
    glMatrixMode(GL_MODELVIEW);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
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
        }
        display();
    }
    SDL_Quit();
    return 0;
}
