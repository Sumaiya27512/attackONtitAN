#include <GL/glut.h>
#include <cmath>
int currentScene = 0;

float mimiX = 375.0f;
float mimiY = 180.0f;
bool walking = false;
int walkTimer = 0;
float walkOffset = 0.0f;

bool night = false;

float butterflyX = 600.0f;
float butterflyY = 430.0f;
float butterflyAngle = 0.0f;
bool butterflyMove = false;

float leafY = 340.0f;
float leafY2 = 360.0f;
float leafY3 = 330.0f;

float waterMove = 0.0f;

bool starVisible = true;
float starFallY = 550.0f;
bool starCaught = false;

float treeSway = 0.0f;
bool treeGlow = false;

float rabbitX = 220.0f;
float rabbitY = 200.0f;
bool rabbitHelped = false;

bool crossingRiver = false;
bool riverCrossed = false;

float boatX = 100.0f;

bool mimiGone = false;

void drawText(float x, float y, const char* text){
    glColor3f(0.0f, 0.0f, 0.0f);
    glRasterPos2f(x,y);
    for (int i=0; text[i]!='\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, text[i]);
    }
}

void drawCircle(float cx, float cy, float r){
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);
    for (int i=0; i<=100; i++){
        float angle = 2.0f*3.1416f*i/100;
        glVertex2f(cx+r*cos(angle),cy+r*sin(angle));
    }
    glEnd();
}

void drawHeart(float x, float y)
{
    glBegin(GL_TRIANGLES);
        glVertex2f(x - 3, y + 1);
        glVertex2f(x + 3, y + 1);
        glVertex2f(x, y - 4);
    glEnd();

    drawCircle(x - 2, y + 2, 2);
    drawCircle(x + 2, y + 2, 2);
}

void drawMimi(){
   glColor3f(1.0f, 0.75f, 0.55f);
   drawCircle(mimiX, mimiY+70, 25);

    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(mimiX-8, mimiY+76, 3);
    drawCircle(mimiX+8, mimiY+76, 3);

    glBegin(GL_LINE_STRIP);
        glVertex2f(mimiX-7, mimiY+65);
        glVertex2f(mimiX-3, mimiY+62);
        glVertex2f(mimiX, mimiY+61);
        glVertex2f(mimiX+3, mimiY+ 62);
        glVertex2f(mimiX+7, mimiY+65);
    glEnd();

    glColor3f(0.95f, 0.25f, 0.45f);
    glBegin(GL_QUADS);
        glVertex2f(mimiX-20, mimiY+20);
        glVertex2f(mimiX+20, mimiY+20);
        glVertex2f(mimiX+20, mimiY+55);
        glVertex2f(mimiX-20, mimiY+55);
    glEnd();

    glColor3f(1.0f, 0.75f, 0.55f);
    glBegin(GL_QUADS);
        glVertex2f(mimiX-20, mimiY+45);
        glVertex2f(mimiX-10, mimiY+45);
        glVertex2f(mimiX-35, mimiY+25);
        glVertex2f(mimiX-42, mimiY+30);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(mimiX+10, mimiY+45);
        glVertex2f(mimiX+20, mimiY+45);
        glVertex2f(mimiX+42, mimiY+30);
        glVertex2f(mimiX+35, mimiY+25);
    glEnd();

    glColor3f(0.15f, 0.20f, 0.60f);
    glBegin(GL_QUADS);
        glVertex2f(mimiX- 15, mimiY+20);
        glVertex2f(mimiX-4, mimiY+20);
        glVertex2f(mimiX-4, mimiY + walkOffset);
        glVertex2f(mimiX-15, mimiY+walkOffset);
    glEnd();

    glBegin(GL_QUADS);
        glVertex2f(mimiX + 4, mimiY + 20);
        glVertex2f(mimiX + 15, mimiY + 20);
        glVertex2f(mimiX + 15, mimiY - walkOffset);
        glVertex2f(mimiX + 4, mimiY - walkOffset);
    glEnd();
}

void drawRabbit(float x, float y){
    glColor3f(0.9f, 0.9f, 0.9f);
    drawCircle(x, y + 25, 25);
    drawCircle(x, y + 60, 20);
    glBegin(GL_QUADS);
        glVertex2f(x - 15, y + 75);
        glVertex2f(x - 5,  y + 75);
        glVertex2f(x - 8,  y + 115);
        glVertex2f(x - 18, y + 115);
        glVertex2f(x + 5,  y + 75);
        glVertex2f(x + 15, y + 75);
        glVertex2f(x + 18, y + 115);
        glVertex2f(x + 8,  y + 115);
    glEnd();

    glColor3f(0.0f, 0.0f, 0.0f);
    drawCircle(x - 7, y + 65, 3);
    drawCircle(x + 7, y + 65, 3);
    drawCircle(x, y + 57, 3);
}

void drawBird(float x, float y){
    glColor3f(0.1f, 0.1f, 0.1f);
    glBegin(GL_LINES);
        glVertex2f(x - 10, y);
        glVertex2f(x, y + 6);
        glVertex2f(x, y + 6);
        glVertex2f(x + 10, y);
    glEnd();
}

void drawButterfly(){
    glColor3f(0.75f, 0.25f, 1.0f);
    drawCircle(butterflyX - 15, butterflyY, 15);
    glColor3f(0.95f, 0.45f, 1.0f);
    drawCircle(butterflyX + 15, butterflyY, 15);

    glColor3f(0.15f, 0.08f, 0.20f);
    glBegin(GL_QUADS);
        glVertex2f(butterflyX - 4, butterflyY - 15);
        glVertex2f(butterflyX + 4, butterflyY - 15);
        glVertex2f(butterflyX + 4, butterflyY + 15);
        glVertex2f(butterflyX - 4, butterflyY + 15);
    glEnd();

    glBegin(GL_LINES);
        glVertex2f(butterflyX - 2, butterflyY + 12);
        glVertex2f(butterflyX - 12, butterflyY + 25);
        glVertex2f(butterflyX + 2, butterflyY + 12);
        glVertex2f(butterflyX + 12, butterflyY + 25);
    glEnd();
}

void drawHouse(){
    glColor3f(0.85f, 0.65f, 0.40f);
    glBegin(GL_QUADS);
        glVertex2f(250, 180);
        glVertex2f(500, 180);
        glVertex2f(500, 350);
        glVertex2f(250, 350);
    glEnd();

    glColor3f(0.55f, 0.20f, 0.12f);
    glBegin(GL_TRIANGLES);
        glVertex2f(220, 350);
        glVertex2f(530, 350);
        glVertex2f(375, 480);
    glEnd();

    glColor3f(0.30f, 0.15f, 0.08f);
    glBegin(GL_QUADS);
        glVertex2f(350, 180);
        glVertex2f(420, 180);
        glVertex2f(420, 290);
        glVertex2f(350, 290);
    glEnd();

    glColor3f(1.0f, 0.85f, 0.1f);
    drawCircle(405, 235, 6);

    glColor3f(0.4f, 0.8f, 1.0f);
    glBegin(GL_QUADS);
        glVertex2f(275, 255);
        glVertex2f(325, 255);
        glVertex2f(325, 310);
        glVertex2f(275, 310);
    glEnd();
    glBegin(GL_QUADS);
        glVertex2f(425, 255);
        glVertex2f(475, 255);
        glVertex2f(475, 310);
        glVertex2f(425, 310);
    glEnd();
}

void drawSun(){
    glColor3f(1.0f, 0.85f, 0.1f);
    drawCircle(680, 500, 45);
}

void drawMoon(){
    glColor3f(1.0f, 1.0f, 0.85f);
    drawCircle(680, 500, 35);
    glColor3f(0.03f, 0.05f, 0.15f);
    drawCircle(695, 510, 35);
}

void drawCloud(float x, float y){
    glColor3f(1.0f, 1.0f, 1.0f);
    drawCircle(x, y, 25);
    drawCircle(x + 30, y + 10, 30);
    drawCircle(x + 60, y, 25);

    glBegin(GL_QUADS);
        glVertex2f(x, y - 20);
        glVertex2f(x + 60, y - 20);
        glVertex2f(x + 60, y + 5);
        glVertex2f(x, y + 5);
    glEnd();
}

void drawStar(){
    if (!starVisible)
        return;

    float cx;
    float cy;

    if (starCaught){
        cx = mimiX + 25.0f;
        cy = mimiY + 75.0f;
    }
    else{
        cx = 680.0f;
        cy = starFallY;
    }

    glColor3f(1.0f, 0.85f, 0.2f);
    glBegin(GL_QUADS);
        glVertex2f(cx, cy + 10);
        glVertex2f(cx + 10, cy);
        glVertex2f(cx, cy - 10);
        glVertex2f(cx - 10, cy);
    glEnd();
}

void drawNightStars(){
    glColor3f(1.0f, 0.9f, 0.2f);
    drawCircle(80, 520, 3);
    drawCircle(130, 470, 2);
    drawCircle(180, 550, 3);
    drawCircle(230, 500, 2);
    drawCircle(280, 550, 3);
    drawCircle(330, 480, 2);
    drawCircle(380, 540, 3);
    drawCircle(430, 500, 2);
    drawCircle(480, 555, 3);
    drawCircle(530, 480, 2);
    drawCircle(580, 530, 3);
    drawCircle(630, 490, 2);
    drawCircle(700, 550, 3);
    drawCircle(750, 500, 2);

    drawCircle(110, 430, 2);
    drawCircle(210, 450, 3);
    drawCircle(300, 430, 2);
    drawCircle(500, 440, 3);
    drawCircle(600, 450, 2);
    drawCircle(720, 430, 3);
}


void drawTree(float x, float y){
    glColor3f(0.40f, 0.20f, 0.08f);
    glBegin(GL_QUADS);
        glVertex2f(x - 18, y);
        glVertex2f(x + 18, y);
        glVertex2f(x + 18, y + 120);
        glVertex2f(x - 18, y + 120);
    glEnd();

    float sway = sin(treeSway) * 8.0f;
    glColor3f(0.10f, 0.55f, 0.18f);
    drawCircle(x + sway, y + 145, 55);
    drawCircle(x - 40 + sway, y + 125, 40);
    drawCircle(x + 40 + sway, y + 125, 40);
}

void drawLeaves(){
    glColor3f(0.8f, 0.6f, 0.1f);
    drawCircle(100, leafY, 4);
    drawCircle(120, leafY + 20, 3);
    drawCircle(140, leafY - 10, 4);
    drawCircle(80, leafY + 30, 3);
    drawCircle(110, leafY + 45, 3);
    drawCircle(150, leafY + 15, 4);
    drawCircle(350, leafY2, 3);
    drawCircle(380, leafY2 + 30, 4);
    drawCircle(400, leafY2 - 15, 3);
    drawCircle(330, leafY2 + 40, 4);
    drawCircle(370, leafY2 + 55, 3);
    drawCircle(420, leafY2 + 20, 4);
    drawCircle(600, leafY3, 4);
    drawCircle(630, leafY3 + 25, 3);
    drawCircle(660, leafY3 - 10, 4);
    drawCircle(580, leafY3 + 35, 3);
    drawCircle(620, leafY3 + 50, 4);
    drawCircle(680, leafY3 + 20, 3);
}

void drawMagicalTree(float x, float y){
    glColor3f(0.40f, 0.20f, 0.08f);
    glBegin(GL_QUADS);
        glVertex2f(x - 20, y);
        glVertex2f(x + 20, y);
        glVertex2f(x + 20, y + 140);
        glVertex2f(x - 20, y + 140);
    glEnd();

    float sway = sin(treeSway) * 8.0f;
    glColor3f(0.10f, 0.55f, 0.18f);
    drawCircle(x + sway, y + 165, 65);
    drawCircle(x - 45 + sway, y + 145, 45);
    drawCircle(x + 45 + sway, y + 145, 45);
}

void drawBoat(){
    glColor3f(0.55f, 0.25f, 0.08f);
    glBegin(GL_QUADS);
        glVertex2f(boatX, 120);
        glVertex2f(boatX + 80, 120);
        glVertex2f(boatX + 65, 145);
        glVertex2f(boatX + 15, 145);
    glEnd();

    glColor3f(0.80f, 0.50f, 0.15f);
    glBegin(GL_QUADS);
        glVertex2f(boatX + 30, 145);
        glVertex2f(boatX + 50, 145);
        glVertex2f(boatX + 50, 175);
        glVertex2f(boatX + 30, 175);
    glEnd();

    glColor3f(0.90f, 0.20f, 0.20f);
    glBegin(GL_TRIANGLES);
        glVertex2f(boatX + 50, 170);
        glVertex2f(boatX + 75, 160);
        glVertex2f(boatX + 50, 155);

    glEnd();
}

void drawBridge(){
    glColor3f(0.55f, 0.30f, 0.12f);
    glBegin(GL_QUADS);
        glVertex2f(150, 235);
        glVertex2f(650, 235);
        glVertex2f(650, 270);
        glVertex2f(150, 270);
    glEnd();

    glColor3f(0.35f, 0.18f, 0.07f);
    glBegin(GL_LINES);
        glVertex2f(220, 235);
        glVertex2f(220, 270);
        glVertex2f(290, 235);
        glVertex2f(290, 270);
        glVertex2f(360, 235);
        glVertex2f(360, 270);
        glVertex2f(430, 235);
        glVertex2f(430, 270);
        glVertex2f(500, 235);
        glVertex2f(500, 270);
        glVertex2f(570, 235);
        glVertex2f(570, 270);
    glEnd();

    glColor3f(0.40f, 0.20f, 0.08f);
    glBegin(GL_QUADS);
        glVertex2f(180, 200);
        glVertex2f(205, 200);
        glVertex2f(205, 235);
        glVertex2f(180, 235);
        glVertex2f(595, 200);
        glVertex2f(620, 200);
        glVertex2f(620, 235);
        glVertex2f(595, 235);
    glEnd();
}

void drawRiver(){
    if (night){
        glColor3f(0.05f, 0.25f, 0.45f);
    }
    else{
        glColor3f(0.20f, 0.60f, 0.90f);
        }

    glBegin(GL_QUADS);
        glVertex2f(150, 0);
        glVertex2f(650, 0);
        glVertex2f(650, 200);
        glVertex2f(150, 200);
    glEnd();

    glColor3f(0.80f, 0.95f, 1.0f); // Water lines
    glBegin(GL_LINES);
        glVertex2f(170 + waterMove, 170);
        glVertex2f(240 + waterMove, 170);
        glVertex2f(300 + waterMove, 145);
        glVertex2f(370 + waterMove, 145);
        glVertex2f(430 + waterMove, 120);
        glVertex2f(500 + waterMove, 120);
        glVertex2f(200 + waterMove, 90);
        glVertex2f(270 + waterMove, 90);
        glVertex2f(350 + waterMove, 65);
        glVertex2f(420 + waterMove, 65);
        glVertex2f(480 + waterMove, 35);
        glVertex2f(550 + waterMove, 35);
    glEnd();
}

void drawTreeGlow(float x, float y){
      glColor3f(1.0f, 0.9f, 0.1f);

    drawHeart(x - 25, y + 195);
    drawHeart(x - 5,  y + 205);
    drawHeart(x + 15, y + 198);
    drawHeart(x + 32, y + 190);
    drawHeart(x - 40, y + 175);
    drawHeart(x - 20, y + 180);
    drawHeart(x + 20, y + 178);
    drawHeart(x + 42, y + 170);
    drawHeart(x - 55, y + 155);
    drawHeart(x - 35, y + 150);
    drawHeart(x - 10, y + 160);
    drawHeart(x + 12, y + 150);
    drawHeart(x + 35, y + 158);
    drawHeart(x + 55, y + 145);
    drawHeart(x - 50, y + 135);
    drawHeart(x - 25, y + 125);
    drawHeart(x + 25, y + 130);
    drawHeart(x + 48, y + 125);
}

void drawForestGlow(){
    glColor3f(1.0f, 0.9f, 0.2f);

    for (int y = 15; y <= 285; y += 35){
        for (int x = 20; x <= 140; x += 40){
            drawHeart(x, y);
        }
    }
    for (int y = 240; y <= 290; y += 30){
        for (int x = 20; x <= 780; x += 40){
            drawHeart(x, y);
        }
    }
    for (int y = 15; y <= 265; y += 35)
    {
        for (int x = 665; x <= 795; x += 40)
        {
            drawHeart(x, y);
        }
    }
}

void drawStartScreen(){
    glColor3f(1.0f, 1.0f, 1.0f);
    glRasterPos2f(365, 300);
    const char* text = "Start";
    for (int i = 0; text[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text[i]);
    }
}

void drawHomeScene(){
    glColor3f(0.20f, 0.60f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(800, 0);
        glVertex2f(800, 180);
        glVertex2f(0, 180);
    glEnd();

    drawSun();
    drawCloud(100, 500);
    drawCloud(500, 530);
    drawTree(100, 180);
    drawTree(650, 180);
    drawHouse();
    drawMimi();
    drawText(mimiX - 45,mimiY + 120,"Hello, I am Mimi!!");
}

void drawForestEntrance(){
    drawSun();
    drawCloud(100, 500);
    drawCloud(500, 530);

    glColor3f(0.20f, 0.60f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(800, 0);
        glVertex2f(800, 300);
        glVertex2f(0, 300);
    glEnd();

    drawTree(120, 180);
    drawTree(375, 200);
    drawTree(650, 180);
    drawLeaves();
    drawButterfly();

    if (!butterflyMove){
        drawText(butterflyX - 45,butterflyY + 35,"Hey, play with me!");
    }
    drawMimi();
}

void drawDeepForest(){
    drawSun();
    drawCloud(100, 500);
    drawCloud(500, 530);

    glColor3f(0.20f, 0.60f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(800, 0);
        glVertex2f(800, 300);
        glVertex2f(0, 300);
    glEnd();

    drawTree(100, 180);
    drawTree(375, 200);
    drawTree(650, 180);
    drawLeaves();
    drawButterfly();
    drawRiver();
    drawBoat();
    drawBridge();

    drawBird(180, 420);
    drawBird(300, 470);
    drawBird(420, 400);
    drawBird(550, 450);
    drawBird(680, 390);

    drawRabbit(rabbitX, rabbitY);
    drawMimi();

    if (!rabbitHelped){
        drawText(mimiX - 55,mimiY + 145,"Help me to cross the river.");
    }else if (!crossingRiver && !riverCrossed){
        drawText(rabbitX - 65,rabbitY + 145,"OK mimi!");
    }
}

void drawMagicalTreeScene(){
    drawNightStars();
    drawMoon();

    glColor3f(0.20f, 0.60f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(800, 0);
        glVertex2f(800, 300);
        glVertex2f(0, 300);
    glEnd();

    drawMagicalTree(120, 180);
    drawMagicalTree(400, 180);
    drawMagicalTree(680, 180);

    if (treeGlow){
        drawTreeGlow(120, 180);
        drawTreeGlow(400, 180);
        drawTreeGlow(680, 180);
        drawForestGlow();
    }

    drawRiver();
    drawBridge();
    drawRabbit(rabbitX, rabbitY);
    drawStar();
    drawMimi();
}

void drawEnding(){
    glColor3f(0.20f, 0.60f, 0.25f);
    glBegin(GL_QUADS);
        glVertex2f(0, 0);
        glVertex2f(800, 0);
        glVertex2f(800, 180);
        glVertex2f(0, 180);
    glEnd();

    drawNightStars();
    drawMoon();
    drawTree(100, 180);
    drawTree(650, 180);
    drawHouse();

    if (!mimiGone){
        drawMimi();
    }

    glColor3f(1.0f, 1.0f, 0.85f);
    glRasterPos2f(230, 520);
    const char* text = "Every little adventure can create a little magic.";
    for (int i = 0; text[i] != '\0'; i++){
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,text[i]);
    }
}

void timer(int value){
     if (walking && currentScene != 3){
        walkTimer--;
        if (walkTimer <= 0){
            walking = false;
            walkOffset = 0.0f;
        }
      }
     if (walking){
        walkOffset += 2.0f;
        if (walkOffset > 8.0f){
            walkOffset = -8.0f;
        }
    }else{
        walkOffset = 0.0f;
    }

    treeSway += 0.08f;

    leafY -= 2.0f;
    if (leafY < 180.0f){
        leafY = 340.0f;
    }
    leafY2 -= 1.5f;
    if (leafY2 < 180.0f){
        leafY2 = 360.0f;
    }
    leafY3 -= 1.8f;
    if (leafY3 < 180.0f){
        leafY3 = 330.0f;
    }

    waterMove += 5.0f;
    if (waterMove > 80.0f){
        waterMove = 0.0f;
    }

    boatX += 3.0f;
    if (boatX >= 570.0f){
        boatX = 150.0f;
    }

    if (currentScene == 2){
        if (butterflyMove){
            butterflyAngle += 0.09f;

            butterflyX = mimiX+cos(butterflyAngle) * 130.0f;
            butterflyY = mimiY+100.0f+sin(butterflyAngle) * 70.0f;
        }
    }

    if (currentScene == 3){
        if (crossingRiver){
            rabbitX += 6.0f;
            mimiX = rabbitX - 100.0f;
            walking = true;

            if (rabbitX >= 760.0f){
                rabbitX = 760.0f;
                mimiX = 660.0f;
                walking = false;
                walkOffset = 0.0f;
                crossingRiver = false;
                riverCrossed = true;
            }
         }

        butterflyAngle += 0.08f;
        butterflyX = 400.0f + cos(butterflyAngle) * 260.0f + sin(butterflyAngle * 2.0f) * 70.0f;
        butterflyY = 400.0f + sin(butterflyAngle * 1.3f) * 100.0f + cos(butterflyAngle * 2.0f) * 45.0f;
        if (butterflyX < 30.0f)
            butterflyX = 30.0f;
        if (butterflyX > 770.0f)
            butterflyX = 770.0f;
        if (butterflyY < 300.0f)
            butterflyY = 300.0f;
        if (butterflyY > 570.0f)
            butterflyY = 570.0f;
    }

    if (currentScene == 4 &&starVisible && !starCaught){
        if (starFallY > 330.0f){
            starFallY -= 5.0f;
        }
        if (mimiX >= 620.0f && mimiX <= 720.0f && starFallY <= 350.0f){
            starCaught = true;
            treeGlow = true;
            starVisible=true;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(100, timer, 0);
}

void display(){

    if (night){
        glClearColor(0.03f,0.05f,0.15f,1.0f);
    }else{
        glClearColor(0.45f,0.75f,1.0f,1.0f);
    }
    glClear(GL_COLOR_BUFFER_BIT);

    if (currentScene == 0){
        glClearColor(0.0f,0.0f,0.0f,1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        drawStartScreen();
        glutSwapBuffers();
        return;
    }

    if (currentScene == 1){
        drawHomeScene();
    }
    else if (currentScene == 2){
        drawForestEntrance();
    }
    else if (currentScene == 3){
        drawDeepForest();
    }
    else if (currentScene == 4){
        drawMagicalTreeScene();
    }
    else if (currentScene == 5){
        drawEnding();
    }
    glutSwapBuffers();
}

void keyboard(unsigned char key, int x, int y){
    if (key == 's'){
        if (currentScene == 0){
            currentScene = 1;
            night = false;
            mimiX = 375.0f;
            mimiY = 180.0f;
            glutPostRedisplay();
        }
    }
    if (key == 'd'){
        if (currentScene == 5){
            if (mimiX >= 350.0f && mimiX <= 420.0f){
                mimiGone = true;
            }
        }
    }

    if (key ==  ' ' ){
        if (currentScene == 1){
            currentScene = 2;
            night = false;
            butterflyX = 500.0f;
            butterflyY = 350.0f;
            butterflyMove = false;
            butterflyAngle = 0.0f;
            glutPostRedisplay();
        }else if (currentScene == 2){
           if (!butterflyMove){
                butterflyMove = true;
                butterflyAngle = 0.0f;
            }else{
                currentScene = 3;
                mimiX = 80.0f;
                mimiY = 200.0f;
                rabbitX = 220.0f;
                rabbitY = 200.0f;
                walking = false;
                walkOffset = 0.0f;
                butterflyMove = false;
                rabbitHelped = false;
                crossingRiver = false;
                night = false;
            }
            glutPostRedisplay();
        }else if (currentScene == 3){
            if (!rabbitHelped){
                rabbitHelped = true;
                glutPostRedisplay();
            }else if (!crossingRiver &&!riverCrossed){
                crossingRiver = true;
                walking = true;
                walkOffset = 0.0f;
                glutPostRedisplay();
            }else if (riverCrossed){
                currentScene = 4;
                mimiY = 200.0f;
                rabbitX = 140.0f;
                rabbitY = 200.0f;
                walking = false;
                walkOffset = 0.0f;
                night = true;
                starVisible = true;
                starCaught = false;
                treeGlow = false;
                starFallY = 550.0f;
                glutPostRedisplay();
            }
        }else if (currentScene == 4){
            if (starCaught && treeGlow){
                currentScene = 5;
                night = true;
                mimiX = 680.0f;
                mimiY = 180.0f;
                mimiGone = false;
                walking = false;
                walkOffset = 0.0f;
                glutPostRedisplay();
            }
        }
    }
    if (key == 'r'){
        currentScene = 0;
        mimiX = 375.0f;
        mimiY = 180.0f;
        mimiGone = false;
        starVisible = true;
        treeGlow = false;
        starFallY = 550.0f;
        starCaught = false;
        walking = false;
        walkOffset = 0.0f;
        butterflyX = 600.0f;
        butterflyY = 430.0f;
        butterflyAngle = 0.0f;
        butterflyMove = false;
        rabbitHelped = false;
        crossingRiver = false;
        rabbitX = 220.0f;
        rabbitY = 200.0f;
        riverCrossed = false;
        leafY = 340.0f;
        leafY2 = 360.0f;
        leafY3 = 330.0f;
        waterMove = 0.0f;
        night = false;

        glutPostRedisplay();
    }
}

void specialKeys(int key, int x, int y){

    if (key == GLUT_KEY_RIGHT){
        mimiX += 10;
        walking = true;
        walkTimer = 2;
    }else if (key == GLUT_KEY_LEFT){
        mimiX -= 10;
        walking = true;
        walkTimer = 2;
    }
    if (mimiX < 30)
        mimiX = 30;
    if (mimiX > 750)
        mimiX = 750;

    if (currentScene == 3){
        return;
    }

    glutPostRedisplay();
}

void init(){
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0,800,0,600);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(100,50);
    glutCreateWindow("A Little Journey to the Enchanted Forest");
    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutTimerFunc(100,timer,0);

    glutMainLoop();
    return 0;
}
