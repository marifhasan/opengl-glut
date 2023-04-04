#include<windows.h>
#ifdef __APPLE__
#else
#include <glut.h>
#endif
#include <stdlib.h>
#include <iostream>
using namespace std;

static GLfloat spin = 0;
float posX = 0, posY = 0, posZ = 0;
int y1=-10,y2=-6,x1=-20;
int pro_tr = -150,onboat=0,t_onboat=0,cought=0,sound=0,take=0;
float t_boat=0.0,f_boat=0.0,walk=0.0,run=0.0,t_pos=0.0,tt_pos=0.0,f_pos=0.0,h_move=-1,hv_move=0,s=0;
void delay(){
    for(int i=0;i<40000000;i++);
}

void circle(int X,int Y, float R){
    float x=0,y=20,r=R,d=0;
    glBegin(GL_POLYGON);
    for(int c=-1;c<2;c+=2){
        for(int e=-1;e<2;e=e+2){
            int co = 0;
            while(co<2){
                x = 0;
                y = r;
                d=3-2*r;
                while(x<=y){
                    if(co==0)
                        glVertex2f((c*x)+X,(e*y)+Y);
                    if(co==1)
                        glVertex2f((e*y)+X,(c*x)+Y);
                    if(d<0){
                        d = d + 4*x + 6;
                    }
                    else{
                        d = d + 4*(x-y) + 10;
                        y=y-0.5;
                    }
                    x=x+0.5;
                }
                co++;
            }
        }
    }
    glEnd();
}
void man(float x,float y,float inc){
//MAN
    glColor3f(0.15,0.35,0.55);
    circle(x-inc,y,1);
    glRectf(x-0.8-inc, y-1, x+0.8-inc, y-6);
    glRectf(x-0.5-inc, y-11.0, x+0.5-inc, y-6);
}
void runman(float x,float y,float inc){
//MAN
    glColor3f(0.15,0.35,0.55);
    circle(x-1-inc,y,1);
    glRectf(x-0.8-inc, y-1, x+0.8-inc, y-6);
    glRectf(x-0.5-inc, y-11.0, x+0.5-inc, y-6);
}
void tr_man(float x,float y,float inc){
//MAN
    glColor3f(0.15,0.35,0.55);
    circle(x-inc,y,1);
    glRectf(x-0.8-inc, y-1, x+0.8-inc, y-2);
}
void sitting_woman(float x,float y){
//WOMAN
    glColor3f(0.15,0.35,0.55);
    circle(x,y,1);
    glRectf(x-0.8, y-1, x+0.8, y-5);
    glRectf(x-1.0, y-8.5, x+0.2, y-6);
}
void standing_woman(float x,float y){
//WOMAN
    glColor3f(0.15,0.35,0.55);
    circle(x,y,1);
    glRectf(x-0.8, y-1, x+0.8, y-6);
    glRectf(x-0.5, y-10, x+0.5, y-6.5);
}
void sitting_man(float x,float y){
//WOMAN
    glColor3f(0.15,0.35,0.55);
    circle(x,y,1);
    glRectf(x-0.8, y-1, x+0.8, y-5.5);
    glRectf(x-1.0, y-9, x+0.2, y-6.5);
}
void h_man(float x,float y,float inc){
//MAN
    glColor3f(0.15,0.35,0.55);
    circle(x-inc,y,1);
    glRectf(x-0.8-inc, y-1, x+0.8-inc, y-3);
}
void walkman(float x,float y,float inc){
//MAN
    glColor3f(0.15,0.35,0.55);
    circle(x+inc,y,1);
    glRectf(x-0.8+inc, y-1, x+0.8+inc, y-6);
    glRectf(x-0.5+inc, y-11.0, x+0.5+inc, y-6);
}

void train(void){

    int tr=-90,w;
    glPushMatrix();
    glTranslatef(-pro_tr,0,0);

    glColor3f(0.0, 0.0, 1.0);
    glRectf(tr-pro_tr, 1.0, tr+64-pro_tr, 11.0);
    glRectf(tr+1-pro_tr, 10.0, tr+5-pro_tr, 13.0);
    tr+=6;
    for( w=0;w<3;w++){
        glColor3f(0.0, 0.75, 0.98);
        glRectf(tr+10-pro_tr, 1.0, tr+12-pro_tr, 11.0);
        glRectf(tr+14-pro_tr, 4.0, tr+18-pro_tr, 8.0);
        glRectf(tr+20-pro_tr, 4.0, tr+24-pro_tr, 8.0);
        tr_man(tr+16,6,pro_tr);
        tr_man(tr+22,6,pro_tr);

        glColor3f(0.0, 0.0, 1.0);
        glRectf(tr+10-pro_tr, 2.0, tr+12-pro_tr, 4.0);
        tr+=16;
    }

    glPopMatrix();
}
void bridge(void){
//BRIDGE
    if(pro_tr < -90){
        walkman(-55,11,walk);
        sitting_woman(67,9);
    }
    else if(pro_tr < -6){
        runman(-13,11,run);
        standing_woman(67,10);
        if(sound==0){
            PlaySound("train.wav", NULL, SND_ASYNC);
            sound++;
        }
    }
    else if(pro_tr< 40){
        walkman(-81,11,0);
        sitting_woman(67,9);
        if(sound<=3){
            PlaySound("train.wav", NULL, SND_ASYNC);
            sound++;
        }
    }
    else if(walk>182){
        sitting_man(65,9.5);
        sitting_woman(67,9);
    }
    else{
        walkman(-118,11,walk);
        sitting_woman(67,9);
    }
    glColor3f(0.0, 1.0, 0.0);
    glRectf(-80.0, 2.0, 40.0, 0.0);
    glRectf(-75.0, 14.0, 34.0, 15.0);
    int ver=75,w;
    for( w=0;w<10;w++){
        glRectf(-ver, 0.0, -ver+1, 15.0);
        ver-=12;
    }
}
void river(void){
    glClear(GL_COLOR_BUFFER_BIT);
// SKY
    glColor3f(0.0, 0.75, 0.98);
    glRectf(-250,-10,250,100);
//SUN
    glColor3f(1.0, 0.2, 0.0);
    circle(10,75,10);
//RIVER
    glColor3f(0.0, 1.0, 1.0);
    glRectf(-250.0, -100.0, 250.0, -10.0);

//MUD
    //LEFT
    glColor3f(0.5,0.5,0.5);
    glRectf(-250.0, -30.0, -75.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex3f(-75.0,0,0);
        glVertex3f(-75,-20,0);
        glVertex3f(-65,0,0);
    glEnd();
    //MIDD
    glBegin(GL_POLYGON);
        glVertex3f(-30,0,0);
        glVertex3f(-10,0,0);
        glVertex3f(-20,-20,0);
    glEnd();
    glRectf(-25,-30,-15,-10);
    //RIGHT
    glRectf(35.0, -30.0, 250.0, 0.0);
    glRectf(100.0, -80.0, 250.0, 0.0);
    glBegin(GL_POLYGON);
        glVertex3f(35.0,0,0);
        glVertex3f(35,-20,0);
        glVertex3f(25,0,0);
    glEnd();
    glBegin(GL_POLYGON);
        glVertex3f(100.0,-30,0);
        glVertex3f(50,-30,0);
        glVertex3f(100,-80,0);
    glEnd();
//BENCH
    glRectf(60.0, 3.0, 72.0, 4.0);
    glRectf(62.0, 3.0, 63.0, 0.0);
    glRectf(69.0, 3.0, 70.0, 0.0);

}

void thiefspeedboat(void){
    glPushMatrix();
    glTranslatef(-t_boat,0,0);

    if(cought==0){
            if(t_onboat==0 && take==0){
                man(92,-49,run);
            }else if(take==0){
                man(72,-49,t_boat);
            }
//        man(72,-49,t_boat);
        glColor3f(1.0,0.0,0.0);
        glRectf(66-t_boat, -60.0, 68-t_boat, -55);
        glBegin(GL_POLYGON);
            glVertex3f(60.0-t_boat,-60,0);
            glVertex3f(90-t_boat,-60,0);
            glVertex3f(90-t_boat,-66,0);
            glVertex3f(70-t_boat,-66,0);
        glEnd();
    }
    else if(cought==1){
        glColor3f(1.0,0.0,0.0);
        glRectf(66-t_boat, -60.0, 68-t_boat, -55);
        glBegin(GL_POLYGON);
            glVertex3f(60.0-t_boat,-60,0);
            glVertex3f(90-t_boat,-60,0);
            glVertex3f(90-t_boat,-66,0);
            glVertex3f(70-t_boat,-66,0);
        glEnd();
        if(take==0){
            man(93+f_pos,-53,posX);
        }
    }

    glPopMatrix();
}
void fbispeedboat(void){

  //  glTranslatef(posX,posY,posZ);
    if(take==0){
        man(92,-53,posX);
    }

    glColor3f(1.0,1.0,0.0);
    glRectf(66-f_boat, -64.0, 68-f_boat, -59);
    glBegin(GL_POLYGON);
        glVertex3f(60.0-f_boat,-64,0);
        glVertex3f(90-f_boat,-64,0);
        glVertex3f(90-f_boat,-70,0);
        glVertex3f(70-f_boat,-70,0);
    glEnd();
}
void hellicopter(void){
        glPushMatrix();
        glTranslatef(-h_move,-hv_move,0);

        glColor3f(1.0,0.0,0.0);

        glRectf(150-h_move, 59.0-hv_move, 170-h_move , 58-hv_move);
        glRectf(159-h_move, 58.0-hv_move, 161-h_move , 56-hv_move);
        glBegin(GL_POLYGON);
            glVertex3f(150.0-h_move,56-hv_move,0);
            glVertex3f(170.0-h_move,56-hv_move,0);
            glVertex3f(170.0-h_move,48-hv_move,0);
            glVertex3f(145.0-h_move,48-hv_move,0);
            glVertex3f(145.0-h_move,54-hv_move,0);
        glEnd();
        glRectf(170-h_move, 52.0-hv_move, 190-h_move , 50-hv_move);
        glRectf(189-h_move, 54.0-hv_move, 190-h_move , 48-hv_move);
        glRectf(156-h_move, 48.0-hv_move, 158-h_move , 46-hv_move);
        glRectf(145-h_move, 46.0-hv_move, 170-h_move , 45-hv_move);

        glColor3f(0.0, 0.75, 0.98);

        glRectf(150-h_move, 50.0-hv_move, 157-h_move , 54-hv_move);
        glRectf(160-h_move, 50.0-hv_move, 167-h_move , 54-hv_move);
        h_man(154-h_move,53-hv_move,1);
        if(take==1){
            h_man(163-h_move,53-hv_move,1);
            h_man(166-h_move,53-hv_move,1);
        }
        if(s!=h_move){
            cout << "h_move" <<h_move << " ";
        }
        s=h_move;
        glPopMatrix();
}
void fixed2d(void){
    river();
    train();
    bridge();
    thiefspeedboat();
    fbispeedboat();
    hellicopter();
}
void display(void)
{
    delay();
    pro_tr++;
    walk+=.2;
    run+=0.47;
    if (f_pos <= t_pos && cought==0){
            if(tt_pos < 12){
                tt_pos+=0.3;
            }
            else{
                t_onboat=1;
                t_boat+=0.3;
                t_pos+=0.3;
            }
        }
    if(h_move >=0){
            if(h_move < f_pos){
                h_move+=1;
                cout << "f_pos: " <<f_pos << " ";
            }
            else if(hv_move < 55 && take == 0){
                hv_move+=1;
                h_move+=.7;
            }
            else if(hv_move >= 0 && take==1){
                hv_move-=1;
                h_move+=.7;
            }
            else if(take==1){
                h_move+=1;
            }
    }
    fixed2d();
    glutPostRedisplay();
	glFlush();
}
float move_unit = 0.8f;
void keyboardown(int key, int x, int y)
{
    switch (key){
        case GLUT_KEY_LEFT:
                if(posX < 18 && t_boat >0 ){
                    posX+=move_unit;
                }
                else if(posX >= 18 ){
                    f_boat+=1;
                    posX+=1;
                    onboat++;
                    f_pos+=0.5;
                    cout << "fposX: " <<posX << " ";
                }
            break;

        case GLUT_KEY_RIGHT:
                if(onboat>0){
                    posX-=1;
                    f_boat-=1;
                    onboat--;
                    if(cought==0){
                        f_pos-=0.5;
                    }
                }
                else {
                    posX-=move_unit;
                }
            break;
        case GLUT_KEY_F1:
                if(onboat > 0 && (f_pos-t_pos)<=5){
                    cought=1;
                }
            break;
        case GLUT_KEY_F2:
                if(cought==1 && h_move <=0){
                    h_move=0;
                }
            break;

        case GLUT_KEY_F3:
                if(cought==1){
                    take=1;
                    cout << "h_move" <<h_move << " ";
                }

            break;
        default:
         break;
    }
    glutPostRedisplay();
}

void init (void)
{
   glClearColor (1.0, 1.0, 1.0, 0.0);
   glOrtho(-170, 145, -100, 100, -100, 100);
}

int main()
{
   glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
   glutInitWindowSize (1000, 600);
   glutInitWindowPosition (100, 100);
   glutCreateWindow("Catch ME IF U Can");
   init();
   glutDisplayFunc(display);
   glutSpecialFunc(keyboardown);
   glutMainLoop();
   return 0;
}
