#include <GL/freeglut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <iostream>
using namespace std;

GLsizei winWidth = 600, winHeight = 400;
GLfloat ANGLE = 0;
GLfloat SPEED = 0.01;
GLfloat DIRECTION = 1;

void init(void) {
  /* selecionar cor de fundo (preto) */
  glClearColor(0.0, 0.0, 0.0, 0.0);

  glMatrixMode(GL_PROJECTION);
  gluOrtho2D(0, winWidth, 0, winHeight);
}

// desenha as transformacoes / Opengl= máquina de estado (cima -> baixo)
//  Composicao de Matriz: Baixo -> Cima
void displayRet(void) {

  // limpa o display
  glClear(GL_COLOR_BUFFER_BIT);

  // Desenha Triangulo
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glColor3f(1.0, 0.0, 0.0);
  glPointSize(10.0);

  glColor3f(1.0, 1.0, .0);
  glBegin(GL_POLYGON);
  glVertex3f(249.0f, 250.0f, -1.0f);
  glVertex3f(251.0f, 250.0f, -1.0f);
  glVertex3f(249.0f, 100.0f, -1.0f);
  glVertex3f(251.0f, 100.0f, -1.0f);
  glEnd();

  glPushMatrix();
  glTranslatef(250, 250, 0);
  glRotatef(ANGLE, 0.0, 0.0, 1.0);
  glTranslatef(-250, -250, 0);

  /* Desenhar um polígono branco  */
  glColor3f(1.0, 1.0, 1.0);
  glBegin(GL_TRIANGLES);
  glVertex2f(250.0f, 250.0f);
  glVertex2f(230.0f, 200.0f);
  glVertex2f(270.0f, 200.0f);
  glEnd();

  /* Desenhar um polígono vermelho */
  glColor3f(1.0, 0.0, 0.0);
  glBegin(GL_TRIANGLES);
  glVertex2f(250.0f, 250.0f);
  glVertex2f(300.0f, 230.0f);
  glVertex2f(300.0f, 270.0f);
  glEnd();

  /* Desenhar um polígono verde */
  glColor3f(0.0, 1.0, 0.0);
  glBegin(GL_TRIANGLES);
  glVertex2f(250.0f, 250.0f);
  glVertex2f(230.0f, 300.0f);
  glVertex2f(270.0f, 300.0f);
  glEnd();

  /* Desenhar um polígono vermelho */
  glColor3f(0.0, 0.0, 1.0);
  glBegin(GL_TRIANGLES);
  glVertex2f(250.0f, 250.0f);
  glVertex2f(200.0f, 270.0f);
  glVertex2f(200.0f, 230.0f);
  glEnd();

  // executa os comandos
  glFlush();
}

void rotateTriangle() {
  ANGLE += SPEED * DIRECTION;
  glutPostRedisplay();
}

void catchKey(unsigned char key, int x, int y) {

  switch (key) {
  case 'q':
    exit(0);
    break;
  case '=':
    SPEED += 0.005;
    break;
  case '-':
    SPEED -= SPEED > 0 ? 0.005 : 0;
    break;
  }
}

void catchSpecialKey(int key, int x, int y) {
  if (key == GLUT_KEY_LEFT) {
    DIRECTION = 1;
  }
  if (key == GLUT_KEY_RIGHT) {
    DIRECTION = -1;
  }
}

void reshape(int width, int height) {
  // Força a janela a manter o tamanho original
  glutReshapeWindow(600, 400);
}

int main(int argc, char *argv[]) {

  cout << "==== CATAVENTO ====\n" << endl;
  cout << "Change direction with LEFT and RIGHT" << endl;
  cout << "Change Speed with + and -" << endl;

  /* inicializa o sitema GLUT */
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
  glutInitWindowSize(600, 400);
  glutInitWindowPosition(100, 100);
  glutCreateWindow("Catavento");

  // chama a funcao init e inicia as propriedades View Port
  init();
  /* Callback para mostrar objetos na tela */
  glutDisplayFunc(displayRet);
  glutReshapeFunc(reshape);
  /* Callback para para interagir com teclado */
  glutKeyboardFunc(catchKey);
  glutSpecialFunc(catchSpecialKey);
  glutIdleFunc(rotateTriangle);
  /* inicia o processamento dos eventos... */
  glutMainLoop();

  return 0;
}
