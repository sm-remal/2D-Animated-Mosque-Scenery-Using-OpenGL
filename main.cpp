#include <GL/glut.h>
#include <cmath>
#include <cstring>
#include <cstdio>

const int WIN_W = 900;
const int WIN_H = 600;

float car1X = -200.0f, car2X = -500.0f, car3X = 900.0f, car4X = 700.0f;
float cloud1X = -100.0f, cloud2X = 350.0f, cloud3X = 700.0f;

struct Person {
    float x, y;
    float speed;
    bool goingToMosque;
    float colorR, colorG, colorB;
};

Person people[6] = {
    {150, 210, 0.5f, true, 0.95f, 0.85f, 0.70f},
    {300, 210, 0.4f, true, 0.90f, 0.95f, 0.90f},
    {500, 210, 0.45f, true, 0.85f, 0.90f, 0.85f},
    {600, 210, 0.35f, false, 0.88f, 0.88f, 0.95f},
    {200, 210, 0.55f, false, 0.95f, 0.90f, 0.75f},
    {700, 210, 0.38f, false, 0.92f, 0.92f, 0.92f}
};

const float CAR_SPEED = 1.8f, CAR3_SPEED = 2.2f, CAR4_SPEED = 2.0f;
const float CLOUD_SPEED = 0.25f;

static const float PI = 3.14159265f;
inline float deg(float d) { return d * PI / 180.0f; }

void drawCircle(float cx, float cy, float r, int segs = 60) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segs; i++) {
        float a = deg(360.0f * i / segs);
        glVertex2f(cx + r * cosf(a), cy + r * sinf(a));
    }
    glEnd();
}

void drawSemiCircle(float cx, float cy, float r, int segs = 60) {
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i = 0; i <= segs; i++) {
        float a = deg(180.0f * i / segs);
        glVertex2f(cx + r * cosf(a), cy + r * sinf(a));
    }
    glEnd();
}

void drawRect(float x, float y, float w, float h) {
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + w, y);
    glVertex2f(x + w, y + h);
    glVertex2f(x, y + h);
    glEnd();
}

void drawRectOutline(float x, float y, float w, float h, float lw = 1.5f) {
    glLineWidth(lw);
    glBegin(GL_LINE_LOOP);
    glVertex2f(x, y); glVertex2f(x + w, y);
    glVertex2f(x + w, y + h); glVertex2f(x, y + h);
    glEnd();
}

void drawArch(float cx, float baseY, float w, float h, int segs = 40) {
    float r = w * 0.5f;
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, baseY + h * 0.5f);
    glVertex2f(cx - r, baseY);
    for (int i = 0; i <= segs; i++) {
        float a = deg(180.0f * i / segs);
        glVertex2f(cx + r * cosf(a), baseY + r * sinf(a) + (h - r));
    }
    glVertex2f(cx + r, baseY);
    glEnd();
}

void drawSky() {
    glBegin(GL_QUADS);
    glColor3f(0.10f, 0.18f, 0.45f); glVertex2f(0, WIN_H); glVertex2f(WIN_W, WIN_H);
    glColor3f(0.45f, 0.72f, 0.95f); glVertex2f(WIN_W, 220); glVertex2f(0, 220);
    glEnd();
    glBegin(GL_QUADS);
    glColor3f(0.45f, 0.72f, 0.95f); glVertex2f(0, 220); glVertex2f(WIN_W, 220);
    glColor3f(0.85f, 0.92f, 1.0f); glVertex2f(WIN_W, 200); glVertex2f(0, 200);
    glEnd();
}

void drawStars() {
    static const float stars[][2] = {
        {50,560},{120,520},{200,580},{310,540},{430,570},{510,510},{620,555},{700,580},{800,530},{860,560},
        {80,490},{160,505},{270,530},{390,480},{470,550},{580,500},{660,520},{750,490},{840,510},{30,545}
    };
    glColor3f(1.0f, 1.0f, 0.9f);
    glPointSize(2.5f);
    glBegin(GL_POINTS);
    for (int i = 0; i < 20; i++) glVertex2f(stars[i][0], stars[i][1]);
    glEnd();
}

void drawMoon() {
    glColor3f(1.0f, 0.98f, 0.82f); drawCircle(800, 520, 28);
    glColor3f(0.15f, 0.22f, 0.50f); drawCircle(810, 524, 24);
}

void drawCloud(float cx, float cy) {
    glColor3f(0.88f, 0.92f, 1.0f);
    drawCircle(cx, cy, 22); drawCircle(cx + 26, cy + 8, 18);
    drawCircle(cx - 26, cy + 5, 17); drawCircle(cx + 10, cy + 18, 16);
    drawCircle(cx - 10, cy + 16, 14);
}

void drawGround() {
    glColor3f(0.18f, 0.52f, 0.18f);
    drawRect(0, 190, WIN_W, 40);
    drawRect(0, 140, WIN_W, 20);

    glColor3f(0.13f, 0.42f, 0.13f);
    glLineWidth(1.0f);
    for (int x = 0; x < WIN_W; x += 12) {
        glBegin(GL_LINES);
        glVertex2f(x, 190); glVertex2f(x + 6, 230);
        glEnd();
    }
}

void drawRoad() {
    glColor3f(0.18f, 0.18f, 0.18f); drawRect(0, 145, WIN_W, 50);
    glColor3f(0.9f, 0.9f, 0.1f); glLineWidth(2.5f);
    glBegin(GL_LINES);
    glVertex2f(0, 192); glVertex2f(WIN_W, 192);
    glVertex2f(0, 148); glVertex2f(WIN_W, 148);
    glEnd();

    glColor3f(1.0f, 1.0f, 1.0f); glLineWidth(2.0f);
    for (int x = 0; x < WIN_W; x += 40) {
        glBegin(GL_LINES);
        glVertex2f(x, 170); glVertex2f(x + 22, 170);
        glEnd();
    }
}

void drawWalkway() {

    glColor3f(0.75f, 0.70f, 0.65f);
    glBegin(GL_QUADS);
    glVertex2f(400, 195);
    glVertex2f(500, 195);
    glVertex2f(460, 242);
    glVertex2f(440, 242);
    glEnd();


    glColor3f(0.55f, 0.50f, 0.45f);
    glLineWidth(2.0f);
    glBegin(GL_LINE_LOOP);
    glVertex2f(400, 195);
    glVertex2f(500, 195);
    glVertex2f(460, 242);
    glVertex2f(440, 242);
    glEnd();


    glColor3f(0.65f, 0.60f, 0.55f);
    glLineWidth(1.0f);
    for (int i = 0; i < 8; i++) {
        float y = 195 + i * 6;
        float xLeft = 400 + (440 - 400) * (y - 195) / (242 - 195);
        float xRight = 500 - (500 - 460) * (y - 195) / (242 - 195);
        glBegin(GL_LINES);
        glVertex2f(xLeft, y);
        glVertex2f(xRight, y);
        glEnd();
    }
}

// Shahedul
void drawPerson(float x, float y, float r, float g, float b, bool facingRight) {
    glColor3f(0.85f, 0.65f, 0.50f);
    drawCircle(x, y + 28, 6);

    glColor3f(r, g, b);
    drawRect(x - 7, y + 8, 14, 20);

    glColor3f(r * 0.9f, g * 0.9f, b * 0.9f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y + 28);
    glVertex2f(x - 3, y + 24);
    glVertex2f(x + 3, y + 24);
    glEnd();

    glColor3f(r, g, b);
    if (facingRight) {
        drawRect(x + 7, y + 18, 8, 8);
        drawRect(x - 15, y + 16, 8, 8);
    }
    else {
        drawRect(x - 15, y + 18, 8, 8);
        drawRect(x + 7, y + 16, 8, 8);
    }

    glColor3f(0.95f, 0.95f, 0.95f);
    drawRect(x - 6, y, 5, 9);
    drawRect(x + 1, y, 5, 9);

    glColor3f(0.40f, 0.30f, 0.20f);
    drawRect(x - 6, y - 2, 5, 2);
    drawRect(x + 1, y - 2, 5, 2);

    glColor3f(0.95f, 0.95f, 0.95f);
    drawCircle(x, y + 34, 5, 20);
    glColor3f(r * 0.8f, g * 0.8f, b * 0.8f);
    drawCircle(x, y + 34, 3, 20);
}

void drawTree(float bx, float by, float scale = 1.0f) {
    float th = 55 * scale, tw = 10 * scale, lr = 32 * scale;
    glColor3f(0.45f, 0.28f, 0.10f); drawRect(bx - tw * 0.5f, by, tw, th);
    glColor3f(0.05f, 0.28f, 0.05f); drawCircle(bx, by + th + lr * 0.7f, lr * 0.92f);
    glColor3f(0.10f, 0.45f, 0.10f); drawCircle(bx, by + th + lr * 0.5f, lr);
    glColor3f(0.15f, 0.58f, 0.15f);
    drawCircle(bx - lr * 0.4f, by + th + lr * 0.8f, lr * 0.75f);
    drawCircle(bx + lr * 0.4f, by + th + lr * 0.8f, lr * 0.75f);
    glColor3f(0.22f, 0.68f, 0.22f); drawCircle(bx, by + th + lr * 1.4f, lr * 0.60f);
}

void drawMosque() {
    glColor3f(0.80f, 0.80f, 0.85f); drawRect(200, 230, 500, 12);

    glColor3f(0.22f, 0.38f, 0.70f); drawRect(240, 242, 420, 140);

    glColor3f(0.18f, 0.30f, 0.60f); glLineWidth(1.0f);
    for (int x = 260; x < 660; x += 35) {
        glBegin(GL_LINES); glVertex2f(x, 242); glVertex2f(x, 382); glEnd();
    }

    glColor3f(0.78f, 0.86f, 1.0f); drawRect(240, 372, 420, 10);
    glColor3f(0.22f, 0.38f, 0.70f);
    for (int x = 245; x < 660; x += 18) drawRect(x, 382, 10, 12);

    glColor3f(0.22f, 0.38f, 0.70f); drawRect(380, 382, 140, 28);
    glColor3f(0.78f, 0.86f, 1.0f); drawRect(380, 408, 140, 6);
    glColor3f(1.0f, 1.0f, 1.0f); drawSemiCircle(450, 414, 72);
    glColor3f(0.88f, 0.93f, 1.0f); drawSemiCircle(432, 414, 24);
    glColor3f(0.90f, 0.80f, 0.20f); drawRect(447, 486, 6, 20); drawCircle(450, 508, 5);
    glColor3f(0.95f, 0.85f, 0.10f); drawCircle(450, 520, 7);
    glColor3f(0.22f, 0.38f, 0.70f); drawCircle(453, 522, 6);

    glColor3f(0.22f, 0.38f, 0.70f); drawRect(248, 230, 34, 185);
    glColor3f(0.78f, 0.86f, 1.0f);
    for (int y = 260; y < 415; y += 30) drawRect(248, y, 34, 5);
    glColor3f(0.80f, 0.88f, 1.0f); drawRect(242, 390, 46, 8);
    glColor3f(0.22f, 0.38f, 0.70f); drawRect(254, 398, 22, 22);
    glColor3f(1.0f, 1.0f, 1.0f); drawSemiCircle(265, 420, 16);
    glColor3f(0.90f, 0.80f, 0.20f); drawRect(263, 436, 4, 14); drawCircle(265, 452, 3.5f);

    glColor3f(0.22f, 0.38f, 0.70f); drawRect(618, 230, 34, 185);
    glColor3f(0.78f, 0.86f, 1.0f);
    for (int y = 260; y < 415; y += 30) drawRect(618, y, 34, 5);
    glColor3f(0.80f, 0.88f, 1.0f); drawRect(612, 390, 46, 8);
    glColor3f(0.22f, 0.38f, 0.70f); drawRect(624, 398, 22, 22);
    glColor3f(1.0f, 1.0f, 1.0f); drawSemiCircle(635, 420, 16);
    glColor3f(0.90f, 0.80f, 0.20f); drawRect(633, 436, 4, 14); drawCircle(635, 452, 3.5f);

    glColor3f(0.22f, 0.38f, 0.70f); drawRect(308, 368, 80, 24);
    glColor3f(1.0f, 1.0f, 1.0f); drawSemiCircle(348, 392, 42);
    glColor3f(0.90f, 0.80f, 0.20f); drawRect(346, 434, 4, 12); drawCircle(348, 448, 3.0f);
    glColor3f(0.22f, 0.38f, 0.70f); drawRect(512, 368, 80, 24);
    glColor3f(1.0f, 1.0f, 1.0f); drawSemiCircle(552, 392, 42);
    glColor3f(0.90f, 0.80f, 0.20f); drawRect(550, 434, 4, 12); drawCircle(552, 448, 3.0f);

    glColor3f(0.90f, 0.92f, 1.0f); drawArch(450, 242, 56, 80);
    glColor3f(0.50f, 0.50f, 0.50f); drawArch(450, 242, 48, 74);
    glColor3f(0.40f, 0.40f, 0.40f);
    drawRect(427, 242, 22, 55); drawRect(451, 242, 22, 55);
    glColor3f(0.90f, 0.80f, 0.20f); drawCircle(448, 277, 3); drawCircle(452, 277, 3);

    glColor3f(0.90f, 0.92f, 1.0f); drawArch(340, 242, 40, 58);
    glColor3f(0.50f, 0.50f, 0.50f); drawArch(340, 242, 34, 53);
    glColor3f(0.40f, 0.40f, 0.40f); drawRect(324, 242, 16, 40); drawRect(340, 242, 16, 40);
    glColor3f(0.90f, 0.92f, 1.0f); drawArch(560, 242, 40, 58);
    glColor3f(0.50f, 0.50f, 0.50f); drawArch(560, 242, 34, 53);
    glColor3f(0.40f, 0.40f, 0.40f); drawRect(544, 242, 16, 40); drawRect(560, 242, 16, 40);

    float wXs[] = { 268, 310, 590, 632 };
    for (int i = 0; i < 4; i++) {
        float wx = wXs[i];
        glColor3f(0.85f, 0.90f, 1.0f); drawArch(wx + 14, 315, 28, 38);
        glColor3f(0.20f, 0.55f, 0.85f); drawArch(wx + 14, 315, 22, 32);
    }
}

void drawCar(float x, float y, float r, float g, float b) {
    glColor3f(r, g, b); drawRect(x, y + 8, 100, 24);
    glColor3f(r * 0.85f, g * 0.85f, b * 0.85f); drawRect(x + 18, y + 32, 64, 20);
    glColor3f(0.65f, 0.85f, 0.95f);
    glBegin(GL_POLYGON);
    glVertex2f(x + 80, y + 32); glVertex2f(x + 82, y + 52);
    glVertex2f(x + 96, y + 52); glVertex2f(x + 100, y + 40);
    glEnd();
    glColor3f(0.70f, 0.88f, 0.98f); drawRect(x + 22, y + 34, 55, 16);
    glColor3f(0.15f, 0.15f, 0.15f); drawCircle(x + 20, y + 10, 12); drawCircle(x + 80, y + 10, 12);
    glColor3f(0.75f, 0.75f, 0.78f); drawCircle(x + 20, y + 10, 5.5f); drawCircle(x + 80, y + 10, 5.5f);
    glColor3f(1.0f, 1.0f, 0.70f); drawRect(x + 95, y + 18, 5, 8);
    glColor3f(0.95f, 0.15f, 0.10f); drawRect(x, y + 18, 4, 8);
}


// Remal
void drawLampPost(float x, float y) {
    glColor3f(0.55f, 0.55f, 0.60f); drawRect(x, y, 5, 70); drawRect(x, y + 68, 20, 4);
    glColor3f(0.90f, 0.85f, 0.30f); drawRect(x + 14, y + 64, 14, 10);
    glColor3f(1.0f, 0.98f, 0.70f); drawCircle(x + 21, y + 69, 6);
}

void drawFence(float startX, float endX, float y) {
    glColor3f(0.88f, 0.88f, 0.88f); glLineWidth(1.5f);
    glBegin(GL_LINES);
    glVertex2f(startX, y + 12); glVertex2f(endX, y + 12);
    glVertex2f(startX, y + 4); glVertex2f(endX, y + 4);
    glEnd();
    for (float x = startX; x < endX; x += 12) {
        glBegin(GL_LINES); glVertex2f(x, y); glVertex2f(x, y + 16); glEnd();
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    drawSky();
    drawStars();
    drawMoon();
    drawCloud(cloud1X, 490);
    drawCloud(cloud2X, 520);
    drawCloud(cloud3X, 475);
    drawGround();
    drawRoad();
    drawWalkway();
    drawFence(0, WIN_W, 225);

    drawLampPost(150, 200);
    drawLampPost(730, 200);
    drawLampPost(440, 200);

    drawTree(100, 228, 0.85f);
    drawTree(160, 228, 0.90f);
    drawTree(55, 228, 0.80f);
    drawTree(740, 228, 0.88f);
    drawTree(800, 228, 0.92f);
    drawTree(850, 228, 0.78f);

    drawMosque();

    for (int i = 0; i < 6; i++) {
        drawPerson(people[i].x, people[i].y, people[i].colorR,
            people[i].colorG, people[i].colorB, people[i].goingToMosque);
    }

    drawCar(car1X, 152, 0.85f, 0.10f, 0.10f);
    drawCar(car2X, 152, 0.95f, 0.80f, 0.10f);
    drawCar(car3X, 190, 0.2f, 0.8f, 0.9f);
    drawCar(car4X, 170, 0.1f, 0.6f, 0.7f);

    glutSwapBuffers();
}

void update(int value) {
    car1X += CAR_SPEED; if (car1X > WIN_W + 10) car1X = -110.0f;
    car2X += CAR_SPEED * 0.70f; if (car2X > WIN_W + 10) car2X = -110.0f;
    car3X -= CAR3_SPEED; if (car3X < -120) car3X = WIN_W + 10;
    car4X -= CAR4_SPEED; if (car4X < -110) car4X = WIN_W + 5;

    cloud1X += CLOUD_SPEED; if (cloud1X > WIN_W + 80) cloud1X = -80.0f;
    cloud2X += CLOUD_SPEED * 0.75f; if (cloud2X > WIN_W + 80) cloud2X = -80.0f;
    cloud3X += CLOUD_SPEED * 0.55f; if (cloud3X > WIN_W + 80) cloud3X = -80.0f;

    for (int i = 0; i < 6; i++) {
        if (people[i].goingToMosque) {
            people[i].x += people[i].speed;
            if (people[i].x > 450) {
                people[i].x = 100;
            }
        }
        else {
            people[i].x -= people[i].speed;
            if (people[i].x < 100) {
                people[i].x = 450;
            }
        }
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void reshape(int w, int h) {
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, WIN_W, 0, WIN_H);
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char key, int, int) {
    if (key == 27) exit(0);
}

void init() {
    glClearColor(0.10f, 0.18f, 0.45f, 1.0f);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(WIN_W, WIN_H);
    glutInitWindowPosition(100, 80);
    glutCreateWindow("Beautiful Mosque Scenery - Optimized with People");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(16, update, 0);
    glutMainLoop();

    return 0;
}