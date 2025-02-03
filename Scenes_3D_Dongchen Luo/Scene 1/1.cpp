#include<SDL/SDL.h>
#include<GL/gl.h>
#include<GL/glu.h>

#include <math.h>
//============================
//=====================================================
double pi=3.14159265359;

double theta=pi/3; // camera angle
double phi = pi/4; // camera angle
double R=15;  // Camera radius

//---------------------------
// Camera position:
void Camera_position(double R, double theta, double phi)
{
    double x = R * sin(theta) * cos(phi);
    double y = R * sin(theta) * sin(phi);
    double z = R * cos(theta);
    gluLookAt(x, y, z, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0);
}

//---------------------------

//-------------------------------------
// Drawing:


//-------------------------------
void Draw_segment(float V1 [3],float V2 [3])
{

glBegin(GL_LINES);
    glVertex3f(V1[0], V1[1], V1[2]);
    glVertex3f(V2[0], V2[1], V2[2]);
glEnd();
}
//-------------------------------


//--------------------------------------
// Coordinate system
void Draw_coord_system()
{
//------------------------
// X axis
glLineWidth(5.0);
glColor3f( 1.0, 0.0, 0.0);
float V1 [3] = {-5.0, 0.0f,0.0f};
float V2 [3] = {5.0, 0.0f,0.0f};
Draw_segment(V1,V2);

//-----------------
// Tip of axis
glPointSize(15);
glEnable(GL_POINT_SMOOTH);
glColor4f( 1.0, 0.0, 0.0, 1);
glBegin(GL_POINTS);
    glVertex3f(5,0,0);
glEnd();
//-----------------
//------------------------


//------------------------
// Y axis
glColor3f( 0.0, 1.0, 0.0);
V1[0] = 0.0;
V1[1] = -5.0;
V2[0] = 0.0;
V2[1] = 5.0;
Draw_segment(V1,V2);

//-----------------
// Tip of axis
glPointSize(15);
glEnable(GL_POINT_SMOOTH);
glColor4f( 0.0, 1.0, 0.0, 1);
glBegin(GL_POINTS);
    glVertex3f(0,5,0);
glEnd();
//-----------------

//------------------------

//------------------------
// Z axis
glColor3f( 0.0, 0.0, 1.0);
V1[1] = 0.0;
V1[2] = -5.0;
V2[1] = 0.0;
V2[2] = 5.0;
Draw_segment(V1,V2);

//-----------------
// Tip of axis
glPointSize(15);
glEnable(GL_POINT_SMOOTH);
glColor4f( 0.0, 0.0, 1.0, .4);
glBegin(GL_POINTS);
    glVertex3f(0,0,5);
glEnd();
//-----------------
// end: Z axis
//------------------------

}
//End: coord system
//--------------------------------------



void Draw_Surface()
{
    const int u_steps = 100;
    const int v_steps = 50;
    const double u_min = 0.0, u_max = 2 * pi;
    const double v_min = 0.0, v_max = 3.0;

    glColor4f(0.5, 0.5, 0.5, 0.8);
    for (int i = 0; i < v_steps; ++i)
    {
        double v1 = v_min + (v_max - v_min) * i / v_steps;
        double v2 = v_min + (v_max - v_min) * (i + 1) / v_steps;

        glBegin(GL_TRIANGLE_STRIP);
        for (int j = 0; j <= u_steps; ++j)
        {
            double u = u_min + (u_max - u_min) * j / u_steps;


            float x1 = cos(u) * v1;
            float y1 = sin(u) * v1;
            float z1 = v1;


            float x2 = cos(u) * v2;
            float y2 = sin(u) * v2;
            float z2 = v2;

            glVertex3f(x1, y1, z1);
            glVertex3f(x2, y2, z2);
        }
        glEnd();
    }
}


void Draw_point()
{
    float P[3] = {sqrt(2.0), sqrt(2.0), 2.0};
    glPointSize(10.0);
    glEnable(GL_POINT_SMOOTH);
    glColor3f(0.0, 0.0, 1.0);
    glBegin(GL_POINTS);
        glVertex3f(P[0], P[1], P[2]);
    glEnd();
}


void Draw(){
    Draw_Surface();
;
}




void init()
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45,640.0/480.0,1.0,500.0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
}


void display()
{
//------
glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

glLoadIdentity();

Camera_position(10, theta, phi);
Draw_coord_system();
Draw();

//phi+=0.01;
// theta-=0.001;
}



int main(int argc, char* args[])
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_SetVideoMode(640,480,32,SDL_SWSURFACE|SDL_OPENGL);

    int petla=1;

    SDL_Event myevent;
    init();
    while (petla==1)
    {

        while (SDL_PollEvent(&myevent))
        {
            switch(myevent.type)
            {
                case SDL_QUIT:
                petla=0;
                break;


                case SDL_KEYDOWN:

                if (myevent.key.keysym.sym==SDLK_LEFT) phi-=0.1;// rotate camera
                if (myevent.key.keysym.sym==SDLK_RIGHT) phi+=0.1;// rotate camera
                if (myevent.key.keysym.sym==SDLK_UP) theta-=0.1;// rotate camera
                if (myevent.key.keysym.sym==SDLK_DOWN) theta+=0.1;// rotate camera

                break;
            }
        }
       display();

        SDL_GL_SwapBuffers();

    }
    SDL_Quit();
    return 0;
}
