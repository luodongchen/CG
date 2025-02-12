#include <SDL/SDL.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;
float angle = 0.0f;

void init() {
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);

    GLfloat light_position[] = {1.0, 1.0, 1.0, 0.0};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)SCR_WIDTH / SCR_HEIGHT, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void Draw_cube() {
    GLfloat cube_normals[][3] = {
        {0.0, 0.0, 1.0}, {0.0, 0.0, -1.0},
        {0.0, 1.0, 0.0}, {0.0, -1.0, 0.0},
        {1.0, 0.0, 0.0}, {-1.0, 0.0, 0.0}
    };
    GLfloat cube_colors[][3] = {
        {1.0, 0.0, 0.0}, {0.0, 1.0, 0.0},
        {0.0, 0.0, 1.0}, {1.0, 1.0, 0.0},
        {1.0, 0.0, 1.0}, {0.0, 1.0, 1.0}
    };
    GLfloat cube_vertices[][3] = {
        {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0},
        {-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0}
    };
    GLint cube_faces[][4] = {
        {0, 1, 2, 3}, {5, 4, 7, 6},
        {3, 2, 6, 7}, {4, 5, 1, 0},
        {1, 5, 6, 2}, {4, 0, 3, 7}
    };

    for (int i = 0; i < 6; ++i) {
        glColor3fv(cube_colors[i]);
        glBegin(GL_QUADS);
        glNormal3fv(cube_normals[i]);
        for (int j = 0; j < 4; ++j) {
            glVertex3fv(cube_vertices[cube_faces[i][j]]);
        }
        glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(4.0, 4.0, 4.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glRotatef(angle, -1.0, 1.0, 1.0);
    Draw_cube();
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
        angle += 0.5f;
        display();
    }
    SDL_Quit();
    return 0;
}
