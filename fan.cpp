// fan in openGL
// Made by: SHASHANK AGRAWAL
// 2020A7PS0073P
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>
#include <stdlib.h>

static GLfloat spin = 0.0;
static GLfloat rotate_angle = 0.0;

GLUquadricObj* qobj;
float leng; float wid; float dep;
int i;
void box(float leng, float wid, float dep);
void wall(float leng, float wid, float dep);
void Fan_Physics();
void Fan_Render();

//************************* variables************************//
static int running = 0;
static int rotate_running = 0;
static bool going_pos=0;
static float translate_speed = .02;
static float X_max = 7.0;
static float X_min = -7.0;
static float Y_max = 7.0;
static float Y_min = -7.0;
static float x_cord = 0.0;
static float y_cord = 0.0;
static int move_up = 0;
static int move_left = 0;
static int lookat_x = 0;
static int lookat_y = 2;
static int lookat_z = 5;

void init(void)
{
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 5.0, 1.0, 5.0, 0.0 };
    GLfloat ambience_color_red[] = { 1.0, 0.5, 0.0, 0.5 };
    GLfloat ambience_color_green[] = { 0.0, 1.0, 0.0, 0.5 };
    GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_ambient[] = { 0.15, 0.15, 0.15, 0.15 };
    GLfloat light_specular[] = { 1.0, 1.0, 1.0, 1.0 };


    glClearColor(0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);

    //glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    //glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambience_color_red);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

}

void display(void)
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();             /* clear the matrix */
    glTranslatef(0.0, 0.0, -4.0);

    gluLookAt(lookat_x, lookat_y, lookat_z, 0, 0, 0, 0, 1, 0);
    //Fan_Physics(); calls moved to keyboard Function
    Fan_Render();
    glutSwapBuffers();
    glutPostRedisplay();

}

void Fan_Physics(void)
{
    // if (running == 1)
        // speed = speed + 0.9;
        // speed = speed - 1.8;
    // if (speed < 0)
        // speed = 0;
    // spin = spin + speed / 10000;
    //glutPostRedisplay(); 

    //if (running == 1)
    //if (rotate_angle < 0)
        //spin = 0;
    if (rotate_running == 1)
    {
        if (rotate_angle < 30 && going_pos == 0)
            rotate_angle += 0.01;
        else
            going_pos = 1;
        if (rotate_angle >= -30 && going_pos == 1)
            rotate_angle -= 0.01;
        else
            going_pos = 0;
    }
	
    if (rotate_running == 0)
	rotate_angle = rotate_angle + 0;

    if (running == 1)
    spin = spin + 0.5;
	
    if (move_up == 1)
    {
		y_cord += translate_speed;
        move_up = 0;
        //printf("%f , %f\n",x_cord, y_cord);
    }
    if (move_up == -1)
    {
        y_cord -= translate_speed;
        move_up = 0;
        //printf("%f , %f\n", x_cord, y_cord);
    }
	if (move_left == 1)
	{
        x_cord -= translate_speed;
        move_left = 0;
        printf("%d, %f\n", move_left, translate_speed);
        //printf("%f , %f\n", x_cord, y_cord);
	}
    if (move_left == -1)
    {
		x_cord += translate_speed;
        move_left = 0;
        // printf("%d, %f\n", move_left, translate_speed);
        //printf("%f , %f\n", x_cord, y_cord);
    }
    //glutPostRedisplay(); 
}


void Fan_Render(void)
{
    glPushMatrix();
    glScalef(.5, .5, .5);
    glTranslatef(x_cord, y_cord, 0);
    /* Fan*/
    glPushMatrix();

    // ************** MATERIAL COLORS ***************** //
    GLfloat ambience_color_red[] = { 1.0, 0.5, 0.0, 0.5 };
    GLfloat ambience_color_green[] = { 0.0, 1.0, 0.0, 0.5 };
    GLfloat ambience_color_other[] = { 0.2, 1, 1, 0.2 };
    GLfloat ambience_color_black[] = { 0.0, 0.0, 0.0, 0.5 };
    GLfloat ambience_color_white[] = { 1,1,1,0.5 };
	GLfloat ambience_color_ground[] = { 0.4, 0.7, 0.3, 0.5 };
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambience_color_red);

    // Fan Base:
    qobj = gluNewQuadric();
    gluQuadricDrawStyle(qobj, GLU_FILL);
    gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
    gluQuadricNormals(qobj, GLU_SMOOTH);
    glScalef(3, 3, 0.5);
    glEnable(GL_NORMALIZE);
    //Sphere with radius 0.25 then scaled
    // gluSphere(qobj, 0.25, 20, 20);

    //square at back
    glPushMatrix();
    glScalef(.3, .3, .3);
    glTranslatef(0, 3, -5);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambience_color_white);
    box(3, 3, 0.1);
    glPopMatrix();
    glPopMatrix();
    glPushMatrix();
	
    gluQuadricDrawStyle(qobj, GLU_FILL); /* smooth shaded */
    gluQuadricNormals(qobj, GLU_SMOOTH);
    glRotatef(rotate_angle, 0.0, 1.0, 0.0);
    glTranslatef(0.0, 3.0, 0.8);
    glScalef(0.3, 0.3, 1);
    glEnable(GL_NORMALIZE);
    gluSphere(qobj, 1, 20, 20);
	
	//wire
    glPushMatrix();
    glColor3f(1.0f, 1.0f, 0.0f);
    glScalef(1, 1.5, .25);
    glutWireSphere(4, 20, 5);
    glPopMatrix();
	
    // glPopMatrix();-->change1

    //**********************************************
    // Fan Blades:
    glTranslatef(0.0, 0.0, 0.5);//-->change2
    glRotatef(spin, 0.0, 0.0, 1.0);
    for (i = 1; i <= 360; i = i + 60)

    {
        glPushMatrix();
        glRotatef(i, 0.0, 0.0, 1.0);
        glTranslatef(1.5, 0.0, 0.0);
        glRotatef(-45, 1.0, 0.0, 0.0);
        glShadeModel(GL_FLAT);
        glEnable(GL_DEPTH_TEST);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        //glMaterialfv_p(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambience_color);
        glPushMatrix();
        /*calling Box ie: drawing the Blade of the fan*/
        glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambience_color_black);
        box(2, 0.2, 0.01);
        //glEnable(GL_LIGHTING);
        glPopMatrix();
        glPopMatrix();

    }
    // glPopMatrix();
    glPopMatrix();
    //box(5.0, 0.3, 0.3);
    glPopMatrix();
    glPushMatrix();
    glTranslatef(0.0, 0.0, -5.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambience_color_other);
    wall(7.0, 7.0, 0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(-7.0, 0.0, -5.0);
    glRotatef(90, 0, 1, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambience_color_other);
    wall(7.0, 7.0, 0.2);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(7.0, 0.0, -5.0);
    glRotatef(90, 0, 1, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambience_color_other);
    wall(7.0, 7.0, 0.2);
    glPopMatrix();

	// ground
    glPushMatrix();
    glTranslatef(0.0, -7.0, -5.0);
    glRotatef(90, 1, 0, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambience_color_ground);
    wall(7.0, 7.0, 0.2);
    glPopMatrix();

    // *******************Table
    glPushMatrix();
    glScalef(.5, .5, .5);
    glTranslatef(7, -7, -2);
    box(3, 3, 2);
    glTranslatef(0, 4, 0);
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, ambience_color_red);
    box(4, 1, 2);
    glPopMatrix();

}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-1, 1, -1.0, 1.0, 1.5, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 'q':
        exit(0);
        break;

    case 's':
    {
        running = 1; glutIdleFunc(Fan_Physics);
        break;
    }

    case 't':
    {
        running = 0;
        glutIdleFunc(Fan_Physics);
        break;
    }

    case 'h':
    {
        if (rotate_running == 0) {
            rotate_running = 1;
            glutIdleFunc(Fan_Physics);
        }
        else
        {
            rotate_running = 0;
            glutIdleFunc(Fan_Physics);
        }

        break;
    }

    case 'u':
    {
        move_up = 1;
        move_left = 0;
        glutIdleFunc(Fan_Physics);
        break;
    }

    case 'd':
    {
        move_up = -1;
        move_left = 0;
        glutIdleFunc(Fan_Physics);
        break;
    }

    case 'l':
    {
        move_left = 1;
        move_up = 0;
        glutIdleFunc(Fan_Physics);
        break;
    }

    case 'r':
    {
        move_left = -1;
        move_up = 0;
        glutIdleFunc(Fan_Physics);
        break;
    }
    case '1':
    {
        lookat_x = -4;
        break;
    }
    case '2':
    {
        lookat_x = 0;
        break;
    }
    case '3':
    {
        lookat_x = 4;
        break;
    }
    }
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(640, 480);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("             Press 1/2/3 to Switch Angles");
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    //glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}

void box(float leng, float wid, float dep)
{
    float a = leng; float b = wid; float c = dep;

    glBegin(GL_QUADS);

    /* Top face of box*/
    // top of box
    glVertex3f(a, b, -c);     // Top right
    glVertex3f(-a, b, -c);    //Top left
    glVertex3f(-a, b, c);     // Bottom left
    glVertex3f(a, b, c);      // Bottom right

    // Bottom face of box
    // bottom of box
    glVertex3f(a, -b, -c);     // Top right
    glVertex3f(-a, -b, -c);    // Top left
    glVertex3f(-a, -b, c);   // Bottom left
    glVertex3f(a, -b, c);   // Bottom right
    glColor3f(1.0, 0.0, 0.0);

    // Front of box
    glVertex3f(a, b, c);      // Top right
    glVertex3f(-a, b, c);     // Top left
    glVertex3f(-a, -b, c);    // Bottom left
    glVertex3f(a, -b, c);     // Bottom right
    glColor3f(1.0, 0.0, 0.0);

    // Back of box
    glVertex3f(a, -b, -c);    // Bottom right
    glVertex3f(-a, -b, -c);   // Bottom left
    glVertex3f(-a, b, -c);    // top left
    glVertex3f(a, b, -c);     // Top right
    glColor3f(1.0, 0.0, 0.0);

    // Left of box
    glVertex3f(-a, b, c);     // Top right
    glVertex3f(-a, b, -c);    // Top left 
    glVertex3f(-a, -b, -c);   // Bottom left
    glVertex3f(-a, -b, c);    // Bottom
    glColor3f(1.0, 0.0, 0.0);

    // Right of box
    glVertex3f(a, b, -c);     // Top right vertex (Right)
    glVertex3f(a, b, c);      // Top left vertex (Right)
    glVertex3f(a, -b, c);     // Bottom left vertex (Right)
    glVertex3f(a, -b, -c);    // Bottom right vertex (Right)
    glColor3f(1.0, 0.0, 0.0);
    glEnd();
}

void wall(float leng, float wid, float dep)
{
    float a = leng; float b = wid; float c = dep;

    glPushMatrix();
    glBegin(GL_QUADS);

    /* Top face of box*/
    glColor3f(1.0,1.0,0.0);
    glVertex3f(a, b, -c);     // Top right
    glVertex3f(-a, b, -c);    //Top left
    glVertex3f(-a, b, c);     // Bottom left
    glVertex3f(a, b, c);      // Bottom right

    // Bottom face of box
    glColor3f(1.0,1.0,0.0);
    glVertex3f(a, -b, -c);     // Top right
    glVertex3f(-a, -b, -c);    // Top left
    glVertex3f(-a, -b, c); 
    glColor3f(1.0, 0.0, 1.0);// Bottom left
    glVertex3f(a, -b, c);   // Bottom right
    glColor3f(1.0, 0.5, 0.0);

    // Front of box
    glColor3f(1.0,1.0,0.0);
    glVertex3f(a, b, c);      // Top right
    glVertex3f(-a, b, c);     // Top left
    glVertex3f(-a, -b, c);
                                // Bottom left
    glVertex3f(a, -b, c);     // Bottom right
    glColor3f(1.0, 0.0, 0.0);
    // Back of box
    glColor3f(1.0,1.0,0.0);
    glVertex3f(a, -b, -c);    // Bottom right
    glVertex3f(-a, -b, -c);   // Bottom left
    glVertex3f(-a, b, -c);    // top left
    glVertex3f(a, b, -c);     // Top right
    glColor3f(1.0, 1.0, 0.0);
    // Left of box
    glColor3f(1.0,1.0,0.0);
    glVertex3f(-a, b, c);     // Top right vertex (Left)
    glVertex3f(-a, b, -c);    // Top left vertex (Left)
    glVertex3f(-a, -b, -c);   // Bottom left vertex (Left)
    glVertex3f(-a, -b, c);    // Bottom vertex (Left)
    glColor3f(1.0, 1.0, 0.0);
    // Right of box
    glColor3f(1.0,1.0,0.0);
    glVertex3f(a, b, -c);     // Top right vertex (Right)
    glVertex3f(a, b, c);      // Top left vertex (Right)
    glVertex3f(a, -b, c);     // Bottom left vertex (Right)
    glVertex3f(a, -b, -c);    // Bottom right vertex (Right)
    // End drawing the box
    glEnd();
    glPopMatrix();

}
