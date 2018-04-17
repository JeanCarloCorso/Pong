#include <stdlib.h>
#include<stdio.h>
#include <GL/glut.h>
#include <math.h>

#define MAX_THREADS 2
#define BUF_SIZE 255

#define PI 3.14159265358979323846  
#define janela_altura 600
#define janela_largura 1000

float xbola = 0.0;
float ybola = 0.0;
float tyA = 0.0;
float tyB = 0.0;
float YbolaStep = 6;
float XbolaStep = 10;
float yStep = 5;

BOOLEAN fim = false;
BOOLEAN derroraA = false;
BOOLEAN derroraB = false;
BOOLEAN ROBO = false;
int pontosA = 0;
int pontosB = 0;
BOOLEAN inicio = false;
GLfloat corR = 0.2;
GLfloat corG = 0.4;
GLfloat corB = 1;
void reiniciar(int i){
	if (i == 1)
	{
		inicio = false;
		xbola = 0;
		ybola = 0;
	}
	else if (i == 2)
	{
		derroraA = false;
		derroraB = false;
	}
	else if (i == 3){
		inicio = false;
		xbola = 0;
		ybola = 0;
		derroraA = false;
		derroraB = false;
		pontosA = 0;
		pontosB = 0;
		fim = false;
	}
	
	
}
void display(void);
void tela(GLsizei w, GLsizei h);
void keyboard(unsigned char key, int x, int y);
void anima(int valor);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);  // controla se o sistema operacional tem suporte a janelas.

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);  // quantidade de buffer de cores e que o padrao de cores é RGB ou RGBA

	glutInitWindowSize(janela_largura, janela_altura);  // tamanho da janela

	glutInitWindowPosition(60, 60); // posicao inicial da janela

	glutCreateWindow("Animação Casa");   /// cria a janela

	glutReshapeFunc(tela);
	glutDisplayFunc(display);
	glutKeyboardFunc(&keyboard);
	glutTimerFunc(150, anima, 1);
	glutMainLoop(); //redesenhar
	return(0);
}

void anima(int valor){
	//inicio
	if ((inicio == true) && (fim == false))
	{
		xbola += XbolaStep;
		ybola += YbolaStep;
	}
	//Laterais
	if ((ybola >= 260) || (ybola < -260))
	{
		YbolaStep *= -1;
	}
	//raquete direita B
	if (((xbola >= 410) && (xbola <= 420)) && ((ybola <= 30 + tyB) && (ybola >= -30 + tyB)))
	{
		XbolaStep *= -1;
	}
	if (((xbola >= 410) && (xbola <= 420)) && ((ybola <= 30 + tyB) && (ybola >= 10 + tyB)))
	{
		YbolaStep = 6;
	}
	if (((xbola >= 410) && (xbola <= 420)) && ((ybola >= -30 + tyB) && (ybola <= -10 + tyB)))
	{
		YbolaStep = -6;
	}
	if (((xbola >= 410) && (xbola <= 420)) && ((ybola >= -10 + tyB) && (ybola <= 10 + tyB)))
	{
		YbolaStep = 0;
	}
	//raquete esquerda A
	if (((xbola <= -410) && (xbola >= -420)) && ((ybola <= 30 + tyA) && (ybola >= -30 + tyA)))
	{
		XbolaStep *= -1;
	}
	if (((xbola <= -410) && (xbola >= -420)) && ((ybola <= 30 + tyA) && (ybola >= 10 + tyA)))
	{
		YbolaStep = 6;
	}
	if (((xbola <= -410) && (xbola >= -420)) && ((ybola >= -30 + tyA) && (ybola <= -10 + tyA)))
	{
		YbolaStep = -6;
	}
	if (((xbola <= -410) && (xbola >= -420)) && ((ybola >= -10 + tyA) && (ybola <= 10 + tyA)))
	{
		YbolaStep = 0;
	}
	//Derrota A
	if (xbola <= -420)
	{
		pontosB += 1;
		reiniciar(1);
		derroraA = true;
		printf("\a");
	}
	//Derrota B
	if (xbola >= 420)
	{
		pontosA += 1;
		reiniciar(1);
		derroraB = true;
		printf("\a");
	}

	glutPostRedisplay();
	glutTimerFunc(150, anima, 1);
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'x':
		if (inicio == false)
		{
			exit(EXIT_SUCCESS);
		}	
		break;
	case 'w':
		tyA += yStep;
		if (tyA>=230)
		{
			tyA = 230;
		}
		printf("%f\n", tyA);
		break;
	case 's':
		tyA -= yStep;
		if (tyA<=-230)
		{
			tyA = -230;
		}
		printf("%f\n", tyA);
		break;
	case 'o':
		tyB += yStep;
		if (tyB >= 230)
		{
			tyB = 230;
		}
		printf("B: %f\n", tyB);
		break;
	case 'l':
		tyB -= yStep;
		if (tyB <= -230)
		{
			tyB = -230;
		}
		printf("B: %f\n", tyB);
		break;
	case '1':
		inicio = true;
		reiniciar(2);
		break;
	case '2':
		inicio = false;
		break;
	case 'r':
		reiniciar(3);
		break;
	case 'j':
		if (ROBO == false)
		{
			ROBO = true;
			printf("O modo roubo foi ativado\n");
		}
		else if (ROBO == true)
		{
			ROBO = false;
			printf("O modo roubo foi desativado\n %d", xbola);
		}
	}
}

void desenhar()
{
	glClearColor(0.51, 0.27, 0.07, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef((janela_largura) / 2, (janela_altura) / 2, 0);

	for (int i = 0; i < 30; i++)
	{
		glPushMatrix();
	}

	//mesa
	glColor3f(0.0f, 0.0f, 0.56f);
	glBegin(GL_POLYGON);
	glVertex2d(-430, 260);
	glVertex2d(430, 260);
	glVertex2d(430, -260);
	glVertex2d(-430, -260);
	glEnd();

	//caso A perca a partida
	if (derroraA == true)
	{
		glColor3f(1.0f, 0.0f, 0.56f);
		glBegin(GL_POLYGON);
		glVertex2d(0, 260);
		glVertex2d(-430, 260);
		glVertex2d(-430, -260);
		glVertex2d(0, -260);
		glEnd();
	}

	//caso B perca a partida
	if (derroraB == true)
	{
		glColor3f(1.0f, 0.0f, 0.56f);
		glBegin(GL_POLYGON);
		glVertex2d(430, 260);
		glVertex2d(0, 260);
		glVertex2d(0, -260);
		glVertex2d(430, -260);
		glEnd();
	}

	//quando A vence o jogo
	if (pontosA == 3)
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex2d(0, 260);
		glVertex2d(-430, 260);
		glVertex2d(-430, -260);
		glVertex2d(0, -260);
		glEnd();

		glColor3f(1.0f, 0.0f, 0.56f);
		glBegin(GL_POLYGON);
		glVertex2d(0, 260);
		glVertex2d(430, 260);
		glVertex2d(430, -260);
		glVertex2d(0, -260);
		glEnd();
		fim = true;
	}

	//quando B vence o jogo
	if (pontosB == 3)
	{
		glColor3f(1.0f, 0.0f, 0.56f);
		glBegin(GL_POLYGON);
		glVertex2d(0, 260);
		glVertex2d(-430, 260);
		glVertex2d(-430, -260);
		glVertex2d(0, -260);
		glEnd();

		glColor3f(0.0f, 1.0f, 0.0f);
		glBegin(GL_POLYGON);
		glVertex2d(0, 260);
		glVertex2d(430, 260);
		glVertex2d(430, -260);
		glVertex2d(0, -260);
		glEnd();
		fim = true;
	}
	//centro da mesa
	GLfloat circ_pnt = 100;
	GLfloat ang, raioX = 15.0f, raioY = 15.0f;
	glColor3f(1, 0, 0);
	glBegin(GL_POLYGON);
	for (int i = 0; i < circ_pnt; i++){
		ang = (2 * PI * i) / circ_pnt;
		glVertex2f(cos(ang)* raioX, sin(ang)*raioY);
	}
	glEnd();

	//linha central
	glLineWidth(7);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0);
	glVertex2d(0,260);
	glVertex2d(0, -260);
	glEnd();

	//linha secundaria esquerda
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0);
	glVertex2d(-60, 0);
	glVertex2d(-370, 0);
	glEnd();

	//linha secundaria direita
	glLineWidth(3);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0);
	glVertex2d(60, 0);
	glVertex2d(370, 0);
	glEnd();

	//raquete esquerda A
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 1.0f, 0.56f);
	glVertex2d(-410, 30 + tyA);
	glVertex2d(-420, 30 + tyA);
	glVertex2d(-420, -30 + tyA);
	glVertex2d(-410, -30 + tyA);
	glEnd();
	glPopMatrix();

	//Linha raquete direita A
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2d(-410, 30 + tyA);
	glVertex2d(-420, 30 + tyA);
	glVertex2d(-420, -30 + tyA);
	glVertex2d(-410, -30 + tyA);
	glEnd();
	glPopMatrix();

	//lista 1 raquete A
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0);
	glVertex2d(-410, 10 + tyA);
	glVertex2d(-420, 10 + tyA);
	glEnd();

	//lista 2 raquete A
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0);
	glVertex2d(-410, -10+tyA);
	glVertex2d(-420, -10 + tyA);
	glEnd();

	//raquete direita B
	glBegin(GL_POLYGON);
	glColor3f(0.0f, 1.0f, 0.56f);
	glVertex2d(410, 30 + tyB);
	glVertex2d(420, 30 + tyB);
	glVertex2d(420, -30 + tyB);
	glVertex2d(410, -30 + tyB);
	glEnd();
	glPopMatrix();

	//Linha raquete direita B
	glLineWidth(2);
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex2d(410, 30 + tyB);
	glVertex2d(420, 30 + tyB);
	glVertex2d(420, -30 + tyB);
	glVertex2d(410, -30 + tyB);
	glEnd();
	glPopMatrix();

	//lista 1 raquete B
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0);
	glVertex2d(410, 10 + tyB);
	glVertex2d(420, 10 + tyB);
	glEnd();

	//lista 2 raquete B
	glLineWidth(2);
	glBegin(GL_LINES);
	glColor3f(0.0f, 0.0f, 0.0);
	glVertex2d(410, -10 + tyB);
	glVertex2d(420, -10 + tyB);
	glEnd();

	if (ROBO == false)
	{
		glColor3f(1, 1, 1);
		//printf("A cor da bola e branco");
	}
	else if ((ROBO == true) && (xbola < 0))
	{
		glColor3f(1, 1, 1);
		//printf("A cor da bola e branco");
	}
	else if ((ROBO == true) && (xbola >= 0))
	{
		glColor3f(0.0f, 0.0f, 0.56f);
	}
	

	
	//bola
	glEnable(GL_POINT_SMOOTH);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glPointSize(10.0);
	glBegin(GL_POINTS);
	glVertex2i(0 + xbola, 0 + ybola);
	glEnd();

	//pontos A
	int distanciaA = 0;
	for (int i = 0; i < pontosA; i++)
	{
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPointSize(10.0);
		glBegin(GL_POINTS);
		glColor3f(0, 1, 0);
		glVertex2i(-430 + distanciaA, 280);
		glEnd();
		distanciaA += 15;
	}

	//pontos B
	int distanciaB = 0;
	for (int i = 0; i < pontosB; i++)
	{
		glEnable(GL_POINT_SMOOTH);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glPointSize(10.0);
		glBegin(GL_POINTS);
		glColor3f(0, 1, 0);
		glVertex2i(430 + distanciaB, 280);
		glEnd();
		distanciaB += -15;
	}

	glFlush(); // executa o desenho
}

void display(){
	glMatrixMode(GL_MODELVIEW); //COORDENADAS DO DESENHO
	glLoadIdentity();
	glViewport(0, 0, janela_largura, janela_altura);
	desenhar();
	glFlush();
}

void tela(GLsizei w, GLsizei h){
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluOrtho2D(0, janela_largura, 0, janela_altura);

	glMatrixMode(GL_MODELVIEW);
}