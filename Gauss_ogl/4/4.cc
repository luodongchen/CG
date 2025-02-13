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

void Draw_equation(double a, double b, double c, float r, float g, float b_col) {
    glColor3f(r, g, b_col);
    glLineWidth(2.0);
    glBegin(GL_LINES);
    glVertex2f(Xmin, (c - a * Xmin) / b);
    glVertex2f(Xmax, (c - a * Xmax) / b);
    glEnd();
}

void Draw_solution(double x, double y) {
    glPointSize(8.0);
    glColor3f(0.0, 1.0, 0.0);
    glBegin(GL_POINTS);
    glVertex2f(x, y);
    glEnd();
}

void Draw_step(int step) {
    Draw_coord_system();


        Draw_solution(3, 5);

}

void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(Xmin, Xmax, Ymin, Ymax);
    glMatrixMode(GL_MODELVIEW);
}

void display(int step) {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    Draw_step(step);
    SDL_GL_SwapBuffers();
}

int main(int argc, char* args[]) {
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_SetVideoMode(SCR_WIDTH, SCR_HEIGHT, 32, SDL_SWSURFACE | SDL_OPENGL);
    int running = 1, step = 0;
    SDL_Event event;
    init();
    while (running) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) running = 0;
            if (event.type == SDL_KEYDOWN) {
                if (event.key.keysym.sym == SDLK_RIGHT) step = (step + 1) % 5;
            }
        }
        display(step);
    }
    SDL_Quit();
    return 0;
}
