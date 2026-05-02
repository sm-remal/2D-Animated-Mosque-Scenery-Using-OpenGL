#include <GL/glut.h>
#include <cmath>

float birdX=-1.0;
bool fountain=false;
bool lampOn=false;
float waterHeight=0;

// Car variables
float car1X = -1.2;
float car2X = 1.2;

//---------------- Smooth Circle ----------------
void circle(float x,float y,float rx,float ry){
glBegin(GL_POLYGON);
for(float i=0;i<360;i+=0.5){
float a=i*3.1416/180;
glVertex2f(x+rx*cos(a),y+ry*sin(a));
}
glEnd();
}

//---------------- Gradient Sky ----------------
void sky(){
glBegin(GL_QUADS);

glColor3f(0.1,0.4,0.8);
glVertex2f(-1,1);
glVertex2f(1,1);

glColor3f(0.65,0.85,1);
glVertex2f(1,-0.2);
glVertex2f(-1,-0.2);

glEnd();
}

//---------------- Sun ----------------
void sun(){

glColor3f(1,1,0);
circle(.78,.8,.07,.07);

// Rays
glColor3f(1,.9,.2);

for(float a=0;a<360;a+=30){
float r=a*3.1416/180;

glBegin(GL_LINES);
glVertex2f(.78,.8);
glVertex2f(.78+.12*cos(r),.8+.12*sin(r));
glEnd();
}
}

//--------------- Cloud ---------------
void cloud(float x,float y){
glColor4f(1,1,1,.85);

circle(x,y,.05,.03);
circle(x+.05,y+.015,.06,.035);
circle(x+.11,y,.05,.03);
}

//--------------- Tree ----------------
void tree(float x,float y){

//trunk
glColor3f(.45,.25,.1);

glBegin(GL_QUADS);
glVertex2f(x,y);
glVertex2f(x+.03,y);
glVertex2f(x+.03,y+.12);
glVertex2f(x,y+.12);
glEnd();

//leaf layers
for(int i=0;i<3;i++){

glColor3f(0,.45+(i*.12),0);

glBegin(GL_TRIANGLES);

glVertex2f(x-.06,y+.08+(i*.04));
glVertex2f(x+.015,y+.22+(i*.04));
glVertex2f(x+.09,y+.08+(i*.04));

glEnd();

}
}

//--------------- Flower ----------------
void flower(float x,float y){

glColor3f(1,0,0);
circle(x,y,.01,.01);

glColor3f(1,1,0);
circle(x,y,.004,.004);

}

//-------------- Road ------------------
void road(){

glColor3f(.15,.15,.15);

glBegin(GL_QUADS);
glVertex2f(-1,-.18);
glVertex2f(1,-.18);
glVertex2f(1,-.35);
glVertex2f(-1,-.35);
glEnd();

//divider
glColor3f(1,1,1);

for(float i=-1;i<1;i+=.28){

glBegin(GL_QUADS);

glVertex2f(i,-.255);
glVertex2f(i+.12,-.255);
glVertex2f(i+.12,-.27);
glVertex2f(i,-.27);

glEnd();

}

}

//----------- Walking Path -------------
void pathway(){

glColor3f(.85,.75,.55);

glBegin(GL_QUADS);
glVertex2f(-.65,-.35);
glVertex2f(.65,-.35);
glVertex2f(.45,-.55);
glVertex2f(-.45,-.55);
glEnd();

}

//------------ Bench ----------------
void bench(float x,float y){

glColor3f(.55,.2,.1);

glBegin(GL_QUADS);

//seat
glVertex2f(x,y);
glVertex2f(x+.12,y);
glVertex2f(x+.12,y+.03);
glVertex2f(x,y+.03);

//back
glVertex2f(x,y+.03);
glVertex2f(x+.12,y+.03);
glVertex2f(x+.12,y+.08);
glVertex2f(x,y+.08);

glEnd();

glColor3f(0,0,0);

glBegin(GL_LINES);

glVertex2f(x+.02,y);
glVertex2f(x+.02,y-.05);

glVertex2f(x+.1,y);
glVertex2f(x+.1,y-.05);

glEnd();
}

//------------- Fountain --------------
void drawFountain(){

glColor3f(.75,.75,.75);
circle(.5,-.45,.12,.06);

glColor3f(.55,.55,.55);
circle(.5,-.45,.07,.03);

if(fountain){

glColor3f(.35,.6,1);

glLineWidth(2);

glBegin(GL_LINES);

for(float i=-.04;i<=.04;i+=.015){

glVertex2f(.5+i,-.43);
glVertex2f(.5+i,-.32+waterHeight);

}

glEnd();

glLineWidth(1);

}
}

//-------------- Lamps ----------------
void lamp(float x){

glColor3f(0,0,0);

glBegin(GL_LINES);
glVertex2f(x,-.25);
glVertex2f(x,.08);
glEnd();

if(lampOn){
glColor3f(1,1,.5);
circle(x,.1,.03,.03);

glColor4f(1,1,.6,.2);
circle(x,.1,.07,.07);

}
else{
glColor3f(.4,.4,.4);
circle(x,.1,.02,.02);
}

}



//------------- Bird -----------------
void bird(){

glColor3f(0,0,0);

glBegin(GL_LINE_STRIP);

glVertex2f(birdX,.65);
glVertex2f(birdX+.03,.68);
glVertex2f(birdX+.06,.65);

glEnd();

}

//------------- Car -----------------
void car(float x, float y, float r, float g, float b){

// Car body
glColor3f(r, g, b);
glBegin(GL_QUADS);
glVertex2f(x, y);
glVertex2f(x+.15, y);
glVertex2f(x+.15, y+.05);
glVertex2f(x, y+.05);
glEnd();

// Car top
glBegin(GL_QUADS);
glVertex2f(x+.03, y+.05);
glVertex2f(x+.12, y+.05);
glVertex2f(x+.11, y+.08);
glVertex2f(x+.04, y+.08);
glEnd();

// Windows
glColor3f(0.6, 0.8, 1);
glBegin(GL_QUADS);
glVertex2f(x+.04, y+.055);
glVertex2f(x+.07, y+.055);
glVertex2f(x+.065, y+.075);
glVertex2f(x+.045, y+.075);
glEnd();

glBegin(GL_QUADS);
glVertex2f(x+.08, y+.055);
glVertex2f(x+.11, y+.055);
glVertex2f(x+.105, y+.075);
glVertex2f(x+.085, y+.075);
glEnd();

// Wheels
glColor3f(0.1, 0.1, 0.1);
circle(x+.03, y, .015, .015);
circle(x+.12, y, .015, .015);

}

//------------- Person walking -----------------
void person(float x, float y, float r, float g, float b){

// Head
glColor3f(1, 0.8, 0.6);
circle(x, y+.06, .012, .012);

// Body
glColor3f(r, g, b);
glBegin(GL_QUADS);
glVertex2f(x-.01, y+.048);
glVertex2f(x+.01, y+.048);
glVertex2f(x+.01, y+.01);
glVertex2f(x-.01, y+.01);
glEnd();

// Legs
glColor3f(0.2, 0.2, 0.5);
glLineWidth(3);
glBegin(GL_LINES);
glVertex2f(x-.005, y+.01);
glVertex2f(x-.008, y-.02);
glVertex2f(x+.005, y+.01);
glVertex2f(x+.008, y-.02);
glEnd();
glLineWidth(1);

// Arms
glColor3f(r, g, b);
glLineWidth(2);
glBegin(GL_LINES);
glVertex2f(x, y+.04);
glVertex2f(x-.015, y+.025);
glVertex2f(x, y+.04);
glVertex2f(x+.015, y+.025);
glEnd();
glLineWidth(1);

}

//----------- Display ----------------
void display(){

glClear(GL_COLOR_BUFFER_BIT);

sky();

sun();

cloud(-.7,.75);
cloud(-.2,.82);
cloud(.2,.72);

//grass
glColor3f(.25,.75,.25);

glBegin(GL_QUADS);
glVertex2f(-1,-1);
glVertex2f(1,-1);
glVertex2f(1,-.35);
glVertex2f(-1,-.35);
glEnd();

// Draw trees first (behind road)
tree(-.85,-.15);
tree(-.55,-.2);
tree(.1,-.18);
tree(.35,-.2);

road();

// Draw cars on road (on top of road)
car(car1X, -.28, 0.8, 0.1, 0.1);  // Red car going right
car(car2X, -.23, 0.1, 0.3, 0.8);  // Blue car going left

pathway();

//flowers
for(float i=-.6;i<.6;i+=.08)
flower(i,-.58);

bench(-.45,-.62);
bench(-.18,-.62);

// Draw standing people on pathway
person(-0.3, -.55, 0.9, 0.3, 0.3);  // Person in red
person(0.15, -.52, 0.3, 0.6, 0.9);  // Person in blue
person(-0.55, -.48, 0.2, 0.7, 0.3);  // Person in green

drawFountain();

lamp(-.72);
lamp(.72);


bird();

//Title
glColor3f(1,1,1);

glRasterPos2f(-.95,.92);

char title[]="2D CITY PARK";
for(int i=0;title[i];i++)
glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,title[i]);

glutSwapBuffers();

}

//---------- Animation Timer --------
void timer(int){

// Bird animation
birdX+=0.004;
if(birdX>1)
birdX=-1;

// Fountain animation
if(fountain){
waterHeight+=.008;
if(waterHeight>.08)
waterHeight=0;
}

// Car 1 animation (going right)
car1X += 0.008;
if(car1X > 1.2)
car1X = -1.2;

// Car 2 animation (going left)
car2X -= 0.01;
if(car2X < -1.2)
car2X = 1.2;

glutPostRedisplay();

glutTimerFunc(30,timer,0);

}

//----------- Keyboard --------------
void keyboard(unsigned char key,int x,int y){

if(key=='L'||key=='l')
lampOn=!lampOn;

if(key=='F'||key=='f')
fountain=!fountain;

}

//----------- Init ----------------
void init(){

glClearColor(1,1,1,1);

glMatrixMode(GL_PROJECTION);

glLoadIdentity();

gluOrtho2D(-1,1,-1,1);

glEnable(GL_BLEND);

glBlendFunc(GL_SRC_ALPHA,
GL_ONE_MINUS_SRC_ALPHA);

}

//----------- Main ----------------
int main(int argc,char** argv){

glutInit(&argc,argv);

glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);

glutInitWindowSize(1100,750);

glutCreateWindow("2D City Park - Animated");

init();

glutDisplayFunc(display);

glutKeyboardFunc(keyboard);

glutTimerFunc(30,timer,0);

glutMainLoop();

return 0;
}