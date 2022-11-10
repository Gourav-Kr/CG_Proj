// #include<windows.h>
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include<math.h>

//Game Speed
int FPS = 20;
int high_score=0;
//Game Track
int start=0;
int gv=0;
int level = 1;
//Track Score
int score = 0;
//Form move track
int roadDivTopMost = 0;
int roadDivTop = 0;
int roadDivMdl = 0;
int roadDivBtm = 0;
//For Card Left / RIGHT
int lrIndex = 0 ;
//Car Coming
int car1 = 0;
int lrIndex1=0;
int car2 = +35;
int lrIndex2=0;
int car3 = +70;
int lrIndex3=0;

char s[30];
void renderBitmapString(float x, float y, void *font,const char *string){
    const char *c;
    glRasterPos2f(x, y);
    for (c=string; *c != '\0'; c++) {
        glutBitmapCharacter(font, *c);
    }
}

void draw_game_road(){
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
        score++;
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
        score++;
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
        score++;
    }
}

void draw_main_car(){
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

void draw_opp(){
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 4);
    glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 6);
    glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 6);
    glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 26 - 2, car1 + 100);
    glVertex2f(lrIndex1 + 26 - 2, car1 + 100 - 2);
    glVertex2f(lrIndex1 + 30 + 2, car1 + 100 - 2);
    glVertex2f(lrIndex1 + 30 + 2, car1 + 100);
    glEnd();
    glColor3f(1.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex1 + 26, car1 + 100);
    glVertex2f(lrIndex1 + 26, car1 + 100 - 7);
    glVertex2f(lrIndex1 + 28, car1 + 100 - 9);
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
    if ((abs(lrIndex - lrIndex1) < 8) && (car1 + 100 < 10))
    {
        start = 0;
        gv = 1;
    }
    // Opposite car 2
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 4);
    glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 6);
    glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 6);
    glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 26 - 2, car2 + 100);
    glVertex2f(lrIndex2 + 26 - 2, car2 + 100 - 2);
    glVertex2f(lrIndex2 + 30 + 2, car2 + 100 - 2);
    glVertex2f(lrIndex2 + 30 + 2, car2 + 100);
    glEnd();
    glColor3f(0.294, 0.000, 0.510);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex2 + 26, car2 + 100);
    glVertex2f(lrIndex2 + 26, car2 + 100 - 7);
    glVertex2f(lrIndex2 + 28, car2 + 100 - 9);
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
    if ((abs(lrIndex - lrIndex2) < 8) && (car2 + 100 < 10))
    {
        start = 0;
        gv = 1;
    }
    // Opposite car 3
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 4);
    glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 6);
    glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 6);
    glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 4);
    glEnd();
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 26 - 2, car3 + 100);
    glVertex2f(lrIndex3 + 26 - 2, car3 + 100 - 2);
    glVertex2f(lrIndex3 + 30 + 2, car3 + 100 - 2);
    glVertex2f(lrIndex3 + 30 + 2, car3 + 100);
    glEnd();
    glColor3f(1.000, 0.271, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(lrIndex3 + 26, car3 + 100);
    glVertex2f(lrIndex3 + 26, car3 + 100 - 7);
    glVertex2f(lrIndex3 + 28, car3 + 100 - 9);
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
    if ((abs(lrIndex - lrIndex3) < 8) && (car3 + 100 < 10))
    {
        start = 0;
        gv = 1;
    }
}

void startGame(){
    
    //Road
    draw_game_road();

    //Score Board
    glColor3f(0.000, 0.000, 0.000);
    glBegin(GL_POLYGON);
    glVertex2f(0,20);
    glVertex2f(17,20);
    glVertex2f(17,0);
    glVertex2f(0,0);
    glEnd();
    //Print Score
    char buffer [50];
    sprintf (buffer, "SCORE: %d", score);
    glColor3f(1.000, 1.000, 0.000);
    // glColor3f(1.000, 0.692, 0.000);
    renderBitmapString(0, 16, (void *)GLUT_BITMAP_HELVETICA_18, buffer);
    //Speed Print
    char buffer1 [50];
    sprintf (buffer1, "SPEED:%dKm/h", FPS);
    glColor3f(1.000, 1.000, 0.000);
    // glColor3f(0.000, 0.692, 0.000);
    renderBitmapString(0, 17-5, (void *)GLUT_BITMAP_HELVETICA_18, buffer1);
    //level Print
    // level=1;
    if(score % 10 == 0){
        int last = score /10 +1;
        if(last!=level){
            level = score/10 +1;
            FPS=FPS+2;
        }
    }
    char level_buffer [50];
    sprintf (level_buffer, "LEVEL: %d", level);
    glColor3f(1.000, 1.000, 0.000);

    renderBitmapString(0, 17 - 9, (void *)GLUT_BITMAP_HELVETICA_18, level_buffer);
    //Increse Speed With level

    //MAIN car
    draw_main_car();
    
    //Opposite car
    draw_opp();

}

void fristDesign(){
    // Road Backgound
    glColor3f(0.000, 0.692, 0.000);
    // glColor3f(0.25, 0.88, 0.3);
    glBegin(GL_POLYGON);
    glVertex2f(0, 55);
    glVertex2f(100, 55);
    glVertex2f(100, 50 - 50);
    glVertex2f(0, 50 - 50);
    glEnd();
    // Road Design In Front Page
    glColor3f(00, 0, 0);
    glBegin(GL_TRIANGLES);
    glVertex2f(32 - 2 + 21, 55);
    glVertex2f(32 + 58, 50 - 50);
    glVertex2f(32 - 22, 50 - 50);
    glEnd();
    // Road Midle
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLES);
    glVertex2f(32 - 2 + 21, 55);
    glVertex2f(50 + 2, 50 - 50);
    glVertex2f(50 - 2, 50 - 50);
    glEnd();
    // Road Sky
    glColor3f(0.000, 0.749, 1.000);
    glBegin(GL_POLYGON);
    glVertex2f(100, 100);
    glVertex2f(0, 100);
    // glColor3f(0.686, 0.933, 0.933);
    glVertex2f(0, 55);
    glVertex2f(100, 55);
    glEnd();
    // //Hill 1
    glColor3f(0.235, 0.702, 0.443);
    glBegin(GL_TRIANGLES);
    glVertex2f(20, 55 + 10);
    glVertex2f(20 + 7, 55);
    glVertex2f(0, 55);
    glEnd();
    // Hill 2
    glColor3f(0.000, 0.502, 0.000);
    glBegin(GL_TRIANGLES);
    glVertex2f(20 + 15, 55 + 12);
    glVertex2f(20 + 20 + 10, 55);
    glVertex2f(0 + 10, 55);
    glEnd();
    // //Hill 4
    glColor3f(0.235, 0.702, 0.443);
    glBegin(GL_TRIANGLES);
    glVertex2f(87, 55 + 10);
    glVertex2f(100, 55);
    glVertex2f(60, 55);
    glEnd();
    //  //Hill 3
    // glColor3f(0.000, 0.502, 0.000);
    // glBegin(GL_TRIANGLES);
    // glVertex2f(70,70);
    // glVertex2f(90,55);
    // glVertex2f(50,55);
    // glEnd();

    //     //Menu Place Holder
        glColor3f(0.098, 0.098, 0.439);
        glBegin(GL_POLYGON);
        glVertex2f(0,5+5+10);
        glVertex2f(50,5+5+10);
        glVertex2f(50,5-15+10);
        glVertex2f(0,5-15+10);
        glEnd();
        glColor3f(1, 1, 1.000);
        glBegin(GL_POLYGON);
        glVertex2f(0,5+5+10);
        glVertex2f(50,5+5+10);
        glVertex2f(50,5+4+10);
        glVertex2f(0,5+4+10);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(49,5+5+10);
        glVertex2f(51,5+5+10);
        glVertex2f(49,5-15+10);
        glVertex2f(51,5-15+10);
        glEnd();
        glBegin(GL_POLYGON);
        glVertex2f(0,5-14+10);
        glVertex2f(50,5-14+10);
        glVertex2f(50,5-15+10);
        glVertex2f(0,5-15+10);
        glEnd();


        // Sun out
        glColor3ub(252.0f, 210.0f, 5.0f);
        glBegin(GL_POLYGON);
        float angle10;
        for (int i = 0; i < 360; i++)
        {
            angle10 = i * 3.1416 / 180;
            glVertex2f(80.0 + 6 * cos(angle10), 80 + 6 * sin(angle10));
        }
        glEnd();

        // Sun in
        glColor3ub(252.0f, 236.0f, 3.0f);
        glBegin(GL_POLYGON);
        float angle11;
        for (int i = 0; i < 360; i++)
        {
            angle11 = i * 3.1416 / 180;
            glVertex2f(80.0 + 5 * cos(angle11), 80 + 5 * sin(angle11));
        }
        glEnd();
        //Text Information in Frist Page
        if(gv==1){
            glColor3f(1.000, 0.000, 0.000);
            renderBitmapString(45,60+15,(void *)GLUT_BITMAP_TIMES_ROMAN_24,"GAME OVER");
            glColor3f(1.000, 0.000, 0.000);
            char buffer2 [50];
            sprintf (buffer2, "Your Score is : %d", score);
            if(score>high_score) high_score=score;
            renderBitmapString(38-5,60-4+15,(void *)GLUT_BITMAP_HELVETICA_18,buffer2);
            char buffer3[50];
            sprintf(buffer3, "High Score : %d", high_score);
            renderBitmapString(38+20, 60 - 4 + 15, (void *)GLUT_BITMAP_HELVETICA_18, buffer3);
        }
        // glColor3f(0.000, 0.000, 0.000);
        // renderBitmapString(30,80,(void *)GLUT_BITMAP_TIMES_ROMAN_24,"2D Car Racing Game ");
        glColor3f(0.000, 1.000, 0.000);
        renderBitmapString(2,5+1.5+10,(void *)GLUT_BITMAP_HELVETICA_12,"Help:");
        renderBitmapString(2,5+1.49+10,(void *)GLUT_BITMAP_HELVETICA_18,"____");
        glColor3f(0.200, 1.000, 0.900);
        renderBitmapString(2,3+10,(void *)GLUT_BITMAP_HELVETICA_18,"Press SPACE to START New Game");
        glColor3f(1.000, 1.000, 1.000);
        renderBitmapString(2,4-3+10,(void *)GLUT_BITMAP_8_BY_13,"Press UP Arrow Button to increase Speed");
        renderBitmapString(2,4-5+10,(void *)GLUT_BITMAP_8_BY_13,"Press DWON Arrow Button to decrease Speed");
        renderBitmapString(2,4-7+10,(void *)GLUT_BITMAP_8_BY_13,"Press RIGHT Arrow Button to turn Right");
        renderBitmapString(2,4-9+10,(void *)GLUT_BITMAP_8_BY_13,"Press LEFT Arrow Button to turn Left");
        glColor3f(1.000, 0.000, 0.000);
        renderBitmapString(2, 3 - 11 + 10, (void *)GLUT_BITMAP_HELVETICA_18, "Press ESC to Exit");
        glColor3f(1.000, 1.000, 1.000);
        renderBitmapString(60-5,50-40,(void *)GLUT_BITMAP_HELVETICA_18,"Made  By :-");
        glColor3f(1.000, 1.000, 0.000);
        renderBitmapString(60-5,50-43,(void *)GLUT_BITMAP_HELVETICA_18,"Gourav Kumar : 20074014");
        glColor3f(1.000, 1.000, 0.000);
        renderBitmapString(60 - 5, 50 - 46, (void *)GLUT_BITMAP_HELVETICA_18, "Sadula Vishwa : 20074028");
        glColor3f(1.000, 1.000, 0.000);
        renderBitmapString(60 - 5, 50 - 49, (void *)GLUT_BITMAP_HELVETICA_18, "Shalini : 20074029");
}
void display(){
    glClear(GL_COLOR_BUFFER_BIT);
    if(start==1){
        // glClearColor(0.627, 0.322, 0.176,1);
        glClearColor(0.000, 0.392, 0.000,1);
        startGame();
    }
    else{
        fristDesign();
        //glClearColor(0.184, 0.310, 0.310,1);
    }
    glFlush();
    glutSwapBuffers();
}
void spe_key(int key, int x, int y){
        switch (key) {
        case GLUT_KEY_DOWN:
            if(FPS>(50+(level*2)))
            FPS=FPS-2;
            break;
        case GLUT_KEY_UP:
            FPS=FPS+2;
            break;
        case GLUT_KEY_LEFT:
            if(lrIndex>=0){
                lrIndex = lrIndex - (FPS/10);
                if(lrIndex<0){
                    lrIndex=-1;
                }
            }
            break;
        case GLUT_KEY_RIGHT:
            if(lrIndex<=44){
                lrIndex = lrIndex + (FPS/10);
                if(lrIndex>44){
                    lrIndex = 45;
                }
            }
            break;
        default:
                break;
        }
}
void processKeys(unsigned char key, int x, int y) {
      switch (key)
            {
                case ' ':
            if(start==0){
                start = 1;
                gv = 0;
                FPS = 50;
                roadDivTopMost = 0;
                roadDivTop = 0;
                roadDivMdl = 0;
                roadDivBtm = 0;
                lrIndex = 0 ;
                car1 = 0;
                lrIndex1=0;
                car2 = +35;
                lrIndex2=0;
                car3 = +70;
                lrIndex3=0;
                score=0;
                level=0;
            }
             break;
             case 27:
                 exit(0);
             break;
             default:
                break;
        }
}
void timer(int){
    glutPostRedisplay();
    glutTimerFunc(1000/FPS,timer,0);
}
int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowSize(800,600);
    glutInitWindowPosition(200,20);
    glutCreateWindow("Car Racing Game");
    glutDisplayFunc(display);
    glutSpecialFunc(spe_key);
    glutKeyboardFunc(processKeys );
    glOrtho(0,100,0,100,-1,1);
    glClearColor(0.184, 0.310, 0.310,1);
    glutTimerFunc(1000,timer,0);
    glutMainLoop();
    return 0;
}
