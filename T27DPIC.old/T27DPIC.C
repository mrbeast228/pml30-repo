#include "pic.h"
#include "glut.h"

unsigned char Frame[FRAME_H][FRAME_W][3];

void PutPixel( int x, int y, int r, int g, int b )
{
  if (x < 0 || x >= FRAME_W || y < 0 || y >= FRAME_H)
    return;
  Frame[y][x][0] = b;
  Frame[y][x][1] = g;
  Frame[y][x][2] = r;
}

void Display( void )
{
  glClear(GL_COLOR_BUFFER_BIT);

  glRasterPos2d(-1, 1);
  glPixelZoom(1, -1);
  glDrawPixels(FRAME_W, FRAME_H, GL_BGR_EXT, GL_UNSIGNED_BYTE, Frame);

  glFinish();
  glutSwapBuffers();
  glutPostRedisplay();
}

void Keyboard( unsigned char Key, int X, int Y )
{
  if (Key == 27)
    exit(0);
}

void Mouse( int Button, int State, int MouseX, int MouseY )
{
  int TSK_MButtons = 0;
  
  if (Button == GLUT_LEFT_BUTTON)
  {
    if (State == GLUT_DOWN)
      TSK_MButtons = 1;
    else
      TSK_MButtons = 0;
  }

  if (TSK_MButtons)
    exit(12); /* do something */
}

void main( int argc, char *argv[] )
{
  PIC p1, p2;
  byte L1[256];
  int i;
  
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);

  glutInitWindowPosition(0, 0);
  glutInitWindowSize(FRAME_W, FRAME_H);
  glutCreateWindow("����� �������� ������");
  
  glutDisplayFunc(Display);
  glutKeyboardFunc(Keyboard);
  glutMouseFunc(Mouse);

  glClearColor(0, 0, 0, 1);

  /* � ����� ���� �������� � ������
  �� ���� P**.G24, ��� ** - �����
  ��������� ��� � ������ � Z:\T27DPIC
  �������� ������ � ��������� ������ */
  if (PicLoad(&p1, "P33.G24"))
  {
    if (PicCreate(&p2, p1.W, p1.H))
    {
      /* ��� lut ������ ���
      
      LUTSetContrast(L1, 50, 205);
      LUTApply(&p2, &p1, L1);
      AutoDraw(&p2);
      PicSave(&p2, "res1.g24");
      
      ��� �������� ������ ���
      �������� � linfil.c ����� �����
      ���� ������� ������� ����
      � ��������� ��� � i
      
      i = 15;
      PicFilter(&p2, &p1, &Filters[i]);
      AutoDraw(&p2);
      PicSave(&p2, "res1.g24");
      
      ��� ���������� ��� ���
      
      PicFilterRoberts(&p2, &p1, 3);
      AutoDraw(&p2);
      PicSave(&p2, "res1.g24");
      
      � ����� ������ ����� ����������
      ��������� � ������ �� ��� �����
      ������ ��������� � Z:\T27DPIC\res1.g24
      ������ ����������� �� ���� 
    
      ���������: ������� embossing ���������
      ����� ���� ������ big NE ��� ���� ������ big SW
      � ����� big E - big S */
      PicFree(&p2);
    }
    PicFree(&p1);
  }

  glutMainLoop();
}