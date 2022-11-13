
#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <math.h>

using namespace std;

// Speed
int speed_of_car = 50;

// Score
int player_score = 0;

// Track
int start = 0;
int game_over = 0;
int cur_level = 1;

// high player_score
int high_score = 0;

// Form move track
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;

// For Car Left / RIGHT
int lrIndex = 0;

// Car Coming
int car1 = 0;
int lrIndex1 = 0;
int car2 = +35;
int lrIndex2 = 0;
int car3 = +70;
int lrIndex3 = 0;

char s[30];
void renderBitmapString(float x, float y, void *font, const char *string)
{
    const char *c;
    glRasterPos2f(x, y);
    for (c = string; *c != '\0'; c++)
    {
        glutBitmapCharacter(font, *c);
    }
}
void draw_game_road();
void draw_main_car();
void draw_opp();
void sun(int r);
void hill(int x);
void startGame();
void fristDesign();
void spe_key(int key, int x, int y);
void processKeys(unsigned char key, int x, int y);
void timer(int);
void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    if (start == 1)
    {
        glClearColor(0.000, 0.692, 0.000, 1);
        startGame();
    }
    else
    {
        fristDesign(); 
    }
    glFlush();
    glutSwapBuffers();
}

int main(int argc, char *argv[])
{

    fstream fin("hs.txt");

    string hs="";

    while (!fin.eof())
    {
        string text;
        fin>>text;
        hs+=text;
    }
    fin.close();
    high_score=stoi(hs);
    
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(560, 240);
    glutCreateWindow("Car Racing Game");
    glutDisplayFunc(display);
    glutSpecialFunc(spe_key);
    glutKeyboardFunc(processKeys);
    glOrtho(0, 100, 0, 100, -1, 1);
    glClearColor(0.184, 0.310, 0.310, 1);
    glutTimerFunc(1000, timer, 0);
    glutMainLoop();
    return 0;
}

// Main Functions

void draw_game_road()
{
    // Road
    glColor3f(0.312, 0.312, 0.312);
    glBegin(GL_POLYGON);
    glVertex2f(20, 0);
    glVertex2f(20, 100);
    glVertex2f(80, 100);
    glVertex2f(80, 0);
    glEnd();

    // Road Middel Border
    // TOP
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivTop + 80);
    glVertex2f(48, roadDivTop + 100);
    glVertex2f(52, roadDivTop + 100);
    glVertex2f(52, roadDivTop + 80);
    glEnd();
    roadDivTop--;
    if (roadDivTop < -100)
    {
        roadDivTop = 20;
        player_score++;
    }
    // Midle
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivMdl + 40);
    glVertex2f(48, roadDivMdl + 60);
    glVertex2f(52, roadDivMdl + 60);
    glVertex2f(52, roadDivMdl + 40);
    glEnd();
    roadDivMdl--;
    if (roadDivMdl < -60)
    {
        roadDivMdl = 60;
        player_score++;
    }
    // Bottom
    glColor3f(1.000, 1.000, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(48, roadDivBtm + 0);
    glVertex2f(48, roadDivBtm + 20);
    glVertex2f(52, roadDivBtm + 20);
    glVertex2f(52, roadDivBtm + 0);
    glEnd();
    roadDivBtm--;
    if (roadDivBtm < -20)
    {
        roadDivBtm = 100;
        player_score++;
    }
}

void draw_main_car()
{
    // Front Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 28 - 2, 7);
    glVertex2f(lrIndex + 28 - 2, 9);
    glVertex2f(lrIndex + 28 + 2, 9);
    glVertex2f(lrIndex + 28 + 2, 7);
    glEnd();
    // Back Tire
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex + 26.5 - 2.5, 1);
    glVertex2f(lrIndex + 26.5 - 2.5, 3);
    glVertex2f(lrIndex + 29.5 + 2.5, 3);
    glVertex2f(lrIndex + 29.5 + 2.5, 1);
    glEnd();
    // Car Body
    glBegin(GL_POLYGON);
    glColor3ub(3.0f, 140.0f, 252.0f);
    glVertex2f(lrIndex + 25, 1);
    glVertex2f(lrIndex + 28, 12);
    glVertex2f(lrIndex + 31, 1);
    glEnd();
}

void draw_opp()
{
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 27 - 2, car1 + 100 - 4);
    glVertex2f(lrIndex1 + 27 - 2, car1 + 100 - 6);
    glVertex2f(lrIndex1 + 29 + 2, car1 + 100 - 6);
    glVertex2f(lrIndex1 + 29 + 2, car1 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 27 - 2, car1 + 100);
    glVertex2f(lrIndex1 + 27 - 2, car1 + 100 - 2);
    glVertex2f(lrIndex1 + 29 + 2, car1 + 100 - 2);
    glVertex2f(lrIndex1 + 29 + 2, car1 + 100);
    glEnd();
    glColor3f(1.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 26, car1 + 100);
    glVertex2f(lrIndex1 + 26, car1 + 100 - 7);
    glVertex2f(lrIndex1 + 27, car1 + 100 - 9);
    glVertex2f(lrIndex1 + 29, car1 + 100 - 9);
    glVertex2f(lrIndex1 + 30, car1 + 100 - 7);
    glVertex2f(lrIndex1 + 30, car1 + 100);
    glEnd();
    car1--;
    if (car1 < -100)
    {
        car1 = 0;
        lrIndex1 = lrIndex;
    }
    // KIll check car1
    if ((abs(lrIndex - lrIndex1) < 6) && (car1 + 100 < 10))
    {
        start = 0;
        game_over = 1;
    }
    // Opposite car 2
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 27 - 2, car2 + 100 - 4);
    glVertex2f(lrIndex2 + 27 - 2, car2 + 100 - 6);
    glVertex2f(lrIndex2 + 29 + 2, car2 + 100 - 6);
    glVertex2f(lrIndex2 + 29 + 2, car2 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 27 - 2, car2 + 100);
    glVertex2f(lrIndex2 + 27 - 2, car2 + 100 - 2);
    glVertex2f(lrIndex2 + 29 + 2, car2 + 100 - 2);
    glVertex2f(lrIndex2 + 29 + 2, car2 + 100);
    glEnd();
    glColor3f(0.294, 0.000, 0.510);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 26, car2 + 100);
    glVertex2f(lrIndex2 + 26, car2 + 100 - 7);
    glVertex2f(lrIndex2 + 27, car2 + 100 - 9);
    glVertex2f(lrIndex2 + 29, car2 + 100 - 9);
    glVertex2f(lrIndex2 + 30, car2 + 100 - 7);
    glVertex2f(lrIndex2 + 30, car2 + 100);
    glEnd();
    car2--;
    if (car2 < -100)
    {
        car2 = 0;
        lrIndex2 = lrIndex;
    }
    // KIll check car2
    if ((abs(lrIndex - lrIndex2) < 6) && (car2 + 100 < 10))
    {
        start = 0;
        game_over = 1;
    }
    // Opposite car 3
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 27 - 2, car3 + 100 - 4);
    glVertex2f(lrIndex3 + 27 - 2, car3 + 100 - 6);
    glVertex2f(lrIndex3 + 29 + 2, car3 + 100 - 6);
    glVertex2f(lrIndex3 + 29 + 2, car3 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 27 - 2, car3 + 100);
    glVertex2f(lrIndex3 + 27 - 2, car3 + 100 - 2);
    glVertex2f(lrIndex3 + 29 + 2, car3 + 100 - 2);
    glVertex2f(lrIndex3 + 29 + 2, car3 + 100);
    glEnd();
    glColor3f(1.000, 0.271, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 26, car3 + 100);
    glVertex2f(lrIndex3 + 26, car3 + 100 - 7);
    glVertex2f(lrIndex3 + 27, car3 + 100 - 9);
    glVertex2f(lrIndex3 + 29, car3 + 100 - 9);
    glVertex2f(lrIndex3 + 30, car3 + 100 - 7);
    glVertex2f(lrIndex3 + 30, car3 + 100);
    glEnd();
    car3--;
    if (car3 < -100)
    {
        car3 = 0;
        lrIndex3 = lrIndex;
    }
    // KIll check car3
    if ((abs(lrIndex - lrIndex3) < 6) && (car3 + 100 < 10))
    {
        start = 0;
        game_over = 1;
    }
}

void sun(int r)
{
    glBegin(GL_POLYGON);
    float angle;
    for (int i = 0; i < 360; i++)
    {
        angle = i * 3.1416 / 180;
        glVertex2f(80.0 + r * cos(angle), 80 + r * sin(angle));
    }
    glEnd();
}
void hill(int x)
{
    glBegin(GL_TRIANGLES);
    glVertex2f(x, 55 + 10);
    glVertex2f(x + 13, 55);
    glVertex2f(x - 27, 55);
    glEnd();
}

void startGame()
{

    // Road
    draw_game_road();

    // Score Board
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(0, 20);
    glVertex2f(17, 20);
    glVertex2f(17, 0);
    glVertex2f(0, 0);
    glEnd();

    // Print Score
    char buffer[50];
    sprintf(buffer, "SCORE: %d", player_score);
    glColor3f(1.000, 1.000, 0.000);
    renderBitmapString(0, 16, (void *)GLUT_BITMAP_HELVETICA_18, buffer);

    // Speed Print
    char buffer1[50];
    sprintf(buffer1, "SPEED:%dKm/h", speed_of_car);
    glColor3f(1.000, 1.000, 0.000);
    renderBitmapString(0, 17 - 5, (void *)GLUT_BITMAP_HELVETICA_18, buffer1);

    // cur_level Print
    if (player_score % 10 == 0)
    {
        int last = player_score / 10 + 1;
        if (last != cur_level)
        {
            cur_level = player_score / 10 + 1;
            speed_of_car = speed_of_car + 5;
        }
    }

    char level_buffer[50];
    sprintf(level_buffer, "LEVEL: %d", cur_level);
    glColor3f(1.000, 1.000, 0.000);
    renderBitmapString(0, 17 - 9, (void *)GLUT_BITMAP_HELVETICA_18, level_buffer);

    // MAIN car
    draw_main_car();

    // Opposite car
    draw_opp();
}

void fristDesign()
{
    // Road Backgound
    glColor3f(0.000, 0.692, 0.000);
    // glColor3f(0.25, 0.88, 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(0, 55);
    glVertex2f(100, 55);
    glVertex2f(100, 50 - 50);
    glVertex2f(0, 50 - 50);
    glEnd();

    glColor3f(00, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(0, 55);
    glVertex2f(100, 55);
    glVertex2f(100, 40);
    glVertex2f(0, 40);
    glEnd();

    // road mid tmp_h

    glColor3f(1, 1, 1);
    glBegin(GL_POLYGON);
    glVertex2f(0, 48.5);
    glVertex2f(100, 48.5);
    glVertex2f(100, 46.5);
    glVertex2f(0, 46.5);

    glEnd();

    // carrrrrrrrr

    glColor3f(1, 0, 0);
    glBegin(GL_POLYGON);
    glVertex2f(68, 43 + 1);
    glVertex2f(68, 48 + 1);
    glVertex2f(72, 48 + 1);
    glVertex2f(76, 52 + 1);
    glVertex2f(86, 52 + 1);
    glVertex2f(90, 48 + 1);
    glVertex2f(90, 43 + 1);
    glEnd();

    // tireee
    glColor3ub(41.0f, 41.0f, 41.0f);
    glBegin(GL_POLYGON);
    float angle;
    for (int i = 0; i < 360; i++)
    {
        angle = i * 3.1416 / 180;
        glVertex2f(76.0 + 2 * cos(angle), 44 + 2 * sin(angle));
    }
    glEnd();
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++)
    {
        angle = i * 3.1416 / 180;
        glVertex2f(86.0 + 2 * cos(angle), 44 + 2 * sin(angle));
    }
    glEnd();

    // Road Sky
    glColor3f(0.000, 0.749, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(100, 100);
    glVertex2f(0, 100);
    glVertex2f(0, 55);
    glVertex2f(100, 55);
    glEnd();

    // //Hills
    glColor3f(0.235, 0.702, 0.443);
    hill(20);
    glColor3f(0.000, 0.502, 0.000);
    hill(38);
    glColor3f(0.235, 0.702, 0.443);
    hill(78);
    glColor3f(0.000, 0.502, 0.000);
    hill(97);

    // menu border
    glColor3ub(77.0f, 0.0f, 77.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 5 + 5 + 1 + 10);
    glVertex2f(50 + 1, 5 + 5 + 1 + 10);
    glVertex2f(50 + 1, 5 - 15 + 10);
    glVertex2f(0, 5 - 15 + 10);
    glEnd();

    //     //Menu Place Holder
    glColor3ub(129.0f, 0.0f, 129.0f);
    glBegin(GL_POLYGON);
    glVertex2f(0, 5 + 5 + 10);
    glVertex2f(50, 5 + 5 + 10);
    glVertex2f(50, 5 - 15 + 10);
    glVertex2f(0, 5 - 15 + 10);
    glEnd();

    // Sun out
    glColor3ub(252.0f, 210.0f, 5.0f);
    sun(6);

    // Sun in
    glColor3ub(252.0f, 236.0f, 3.0f);
    sun(5);

    // Text Information in Frist Page
    if (game_over == 1)
    {
        glColor3f(1.000, 0.000, 0.000);
        renderBitmapString(45, 60 + 15, (void *)GLUT_BITMAP_TIMES_ROMAN_24, "GAME OVER");
        glColor3ub(191.0f, 66.0f, 37.0f);
        char buffer2[50];
        sprintf(buffer2, "Your Score is : %d", player_score);
        if (player_score > high_score){
            high_score = player_score;
            fstream fin("hs.txt", ios::trunc | ios::out);
            string sc=to_string(high_score);
            fin<<sc;
        }
        renderBitmapString(38 - 5, 60 - 4 + 15, (void *)GLUT_BITMAP_HELVETICA_18, buffer2);
        char buffer3[50];
        sprintf(buffer3, "High Score : %d", high_score);
        renderBitmapString(38 + 20, 60 - 4 + 15, (void *)GLUT_BITMAP_HELVETICA_18, buffer3);
    }

    glColor3f(0.200, 1.000, 0.900);
    renderBitmapString(2, 3 + 2.5 + 10, (void *)GLUT_BITMAP_HELVETICA_18, "Press ANY KEY to START New Game");
    glColor3f(1.000, 1.000, 1.000);
    renderBitmapString(2, 4 - 1 + 10, (void *)GLUT_BITMAP_8_BY_13, "KEY    FUNCTION");
    renderBitmapString(2, 4 - 3 + 10, (void *)GLUT_BITMAP_8_BY_13, "UP   : Increase Speed");
    renderBitmapString(2, 4 - 5 + 10, (void *)GLUT_BITMAP_8_BY_13, "DOWN : Decrease Speed");
    renderBitmapString(2, 4 - 7 + 10, (void *)GLUT_BITMAP_8_BY_13, "RIGHT: Turn Right");
    renderBitmapString(2, 4 - 9 + 10, (void *)GLUT_BITMAP_8_BY_13, "LEFT : Turn Left");

    glColor3f(1.000, 0.000, 0.000);
    renderBitmapString(2, 3 - 11 + 10, (void *)GLUT_BITMAP_HELVETICA_18, "Press ESC to Exit");
    glColor3f(1.000, 1.000, 1.000);
    renderBitmapString(60 - 5, 50 - 40, (void *)GLUT_BITMAP_HELVETICA_18, "Made  By :-");
    glColor3f(1.000, 1.000, 0.000);
    renderBitmapString(60 - 5, 50 - 43, (void *)GLUT_BITMAP_HELVETICA_18, "Gourav Kumar : 20074014");
    glColor3f(1.000, 1.000, 0.000);
    renderBitmapString(60 - 5, 50 - 46, (void *)GLUT_BITMAP_HELVETICA_18, "Sadula Vishwa : 20074028");
    glColor3f(1.000, 1.000, 0.000);
    renderBitmapString(60 - 5, 50 - 49, (void *)GLUT_BITMAP_HELVETICA_18, "Shalini : 20074029");

    ///////////////////

    glBegin(GL_POLYGON);           // start drawing a polygon
    glColor3f(1.0f, 0.0f, 0.0f);   // Set The Color To Red
    glVertex3f(-1.0f, 1.0f, 0.0f); // Top left
    glVertex3f(0.4f, 1.0f, 0.0f);

    glVertex3f(1.0f, 0.4f, 0.0f);

    glColor3f(0.0f, 1.0f, 0.0f);   // Set The Color To Green
    glVertex3f(1.0f, 0.0f, 0.0f);  // Bottom Right
    glColor3f(0.0f, 0.0f, 1.0f);   // Set The Color To Blue
    glVertex3f(-1.0f, 0.0f, 0.0f); // Bottom Left
    glEnd();
}

void spe_key(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_DOWN:
        if (speed_of_car > (50 + (cur_level * 2)))
            speed_of_car = speed_of_car - 2;
        break;
    case GLUT_KEY_UP:
        speed_of_car = speed_of_car + 2;
        break;
    case GLUT_KEY_LEFT:
        if (lrIndex >= 0)
        {
            lrIndex = lrIndex - (speed_of_car / 10);
            if (lrIndex < 0)
            {
                lrIndex = -1;
            }
        }
        break;
    case GLUT_KEY_RIGHT:
        if (lrIndex <= 44)
        {
            lrIndex = lrIndex + (speed_of_car / 10);
            if (lrIndex > 44)
            {
                lrIndex = 45;
            }
        }
        break;
    default:
        break;
    }
}

void processKeys(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 27:
        exit(0);
        break;
    // case ' ':
    default:
        if (start == 0)
        {
            start = 1;
            game_over = 0;
            speed_of_car = 50;
            roadDivTopMost = 0;
            roadDivTop = 0;
            roadDivMdl = 0;
            roadDivBtm = 0;
            lrIndex = 0;
            car1 = 0;
            lrIndex1 = 0;
            car2 = +35;
            lrIndex2 = 0;
            car3 = +70;
            lrIndex3 = 0;
            player_score = 0;
            cur_level = 0;
        }
        break;

        //  default:
        //     break;
    }
}

void timer(int)
{
    glutPostRedisplay();
    glutTimerFunc(1000 / speed_of_car, timer, 0);
}
