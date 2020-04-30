//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////																						  ////////////
////////////////					Universidad Nacional Autónoma de México.	                          ////////////
////////////////							Facultad de Ingeniería.										  ////////////
////////////////																						  ////////////
////////////////																						  ////////////
////////////////					       Materia:Computación Gráfica.									  ////////////
////////////////																						  ////////////
////////////////																						  ////////////
////////////////					 Profesor: Ing. Arturo Perez de la Cruz.							  ////////////
////////////////																						  ////////////
////////////////																						  ////////////
////////////////									Grupo: 03.											  ////////////
////////////////																						  ////////////
////////////////																						  ////////////
////////////////								  Proyecto Final.										  ////////////
////////////////																						  ////////////
////////////////																						  ////////////
////////////////							 Integrantes del equipo.									  ////////////
////////////////							 - González Rojo Irvin.										  ////////////
////////////////							 - González Joel.           								  ////////////
////////////////																						  ////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


#include "texture.h"
#include "figuras.h"
#include "Camera.h"
#include "cmodel/CModel.h"
#include <Windows.h>
#include <mmsystem.h>

static GLuint ciudad_display_list;	

									//Variables de dibujo y manipulacion
float posX = 0, posY = 2.5, posZ = -3.5, rotRodIzq = 0, rotBrIzq = 0, rotBrDer = 0, rotRodDer = 0;
float giroMonito = 0;

#define MAX_FRAMES 5
int i_max_steps = 90;
int i_curr_steps = 0;
DWORD dwFrames = 0;
DWORD dwCurrentTime = 0;
DWORD dwLastUpdateTime = 0;
DWORD dwElapsedTime = 0;
int juego;
int juego1=0;
int mundo; 
float arriba = 0.0;

float  arribaInc = 0.0;
float horizontal = 0;
float vertical = 1.24;
float profundidad = -25;
float giro = 0;

typedef struct _frame
{
	//Variables para GUARDAR Key Frames
	float posX;		//Variable para PosicionX
	float posY;		//Variable para PosicionY
	float posZ;		//Variable para PosicionZ
	float incX;		//Variable para IncrementoX
	float incY;		//Variable para IncrementoY
	float incZ;		//Variable para IncrementoZ
	float rotRodIzq;
	float rotInc;
	float rotBrIzq;
	float rotInc2;
	float rotBrDer;
	float rotRodDer;
	float rotInc4;
	float rotInc3;

	float giroMonito;
	float giroMonitoInc;
	float  arriba=0.0;
	float arribaInc = 0.0;

	float horizontal = 0;
	float vertical = 1.24;
	float profundidad = -25;
	float giro = 0;

	float horizontalInc = 0;
	float verticalInc = 0;
	float profundidadInc = 0;
	float giroInc = 0;


}FRAME;

FRAME KeyFrame[MAX_FRAMES];
int FrameIndex = 20;			//introducir datos
bool play = false;
int playIndex = 0;

int w = 500, h = 500;
int frame = 0, time, timebase = 0;
char s[30];

CCamera objCamera;	//Create objet Camera

GLfloat g_lookupdown = 0.0f;    // Look Position In The Z-Axis (NEW) 

int font = (int)GLUT_BITMAP_HELVETICA_18;


GLfloat Diffuse[] = { 0.5f, 0.5f, 0.5f, 1.0f };				// Diffuse Light Values
GLfloat Specular[] = { 1.0, 1.0, 1.0, 1.0 };				// Specular Light Values
GLfloat Position[] = { 0.0f, 7.0f, -5.0f, 0.0f };			// Light Position
GLfloat Position2[] = { 0.0f, 0.0f, -5.0f, 1.0f };			// Light Position

GLfloat m_dif1[] = { 0.0f, 0.2f, 1.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec1[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb1[] = { 1, 1, 1, 1.0 };				// Ambiental Light Values
GLfloat m_s1[] = { 18 };

GLfloat m_dif2[] = { 0.8f, 0.2f, 0.0f, 1.0f };				// Diffuse Light Values
GLfloat m_spec2[] = { 0.0, 0.0, 0.0, 1.0 };				// Specular Light Values
GLfloat m_amb2[] = { 0.0, 0.0, 0.0, 1.0 };				// Ambiental Light Values
GLfloat m_s2[] = { 22 };

CTexture text1; //Paisaje de fondo
CTexture text2; //Ventana
CTexture text5;	//Pasto
CTexture text8; //Cielo
CTexture text9; //Puerta
CTexture piso; //pavimento



//END NEW//////////////////////////////////////////

CFiguras fig2;
CFiguras fig3;
CFiguras fig4;	//Pasto01
CFiguras fig5;	//Casa01
CFiguras fig6;
CFiguras fig7;	//Para crear Monito
CFiguras fig8;//torre roja
CFiguras fig9;//torre blanca
CFiguras fig10;//torre azul
CFiguras fig11;//estrellas
CFiguras fig12;//cadenas
CFiguras fig13;//silla amarilla

CFiguras fig14;
CFiguras fig15;
CFiguras fig16;
CFiguras fig17;//MCDon
CFiguras fig18;
CFiguras fig19;
CFiguras fig20;
CFiguras fig21;
CFiguras fig22;
CFiguras fig23;
CFiguras fig24;
CFiguras fig25;
CFiguras fig26;

CModel sol;
float movsol = 100.0;

CModel soll;
float movsoll = 100.0;

CModel solll;
float movsolll = 100.0;


CModel soolll;
float movsoolll = 100.0;

CModel sooll;
float movsooll = 100.0;

CModel pue;
float movpue = 100.0;

CModel ado;
float movado = 100.0;

CModel ca;
float movca = 100.0;

CModel cer;
float movcer = 100.0;


CModel me;
float movme = 100.0;

CModel si;
float movsi = 100.0;

void Audio() {
	PlaySound(TEXT("Audio/fondo.wav"), NULL, SND_LOOP || SND_ASYNC);
}

void saveFrame(void)
{

	printf("frameindex %d\n", FrameIndex);

	KeyFrame[FrameIndex].posX = posX;
	KeyFrame[FrameIndex].posY = posY;
	KeyFrame[FrameIndex].posZ = posZ;

	KeyFrame[FrameIndex].rotRodIzq = rotRodIzq;
	KeyFrame[FrameIndex].rotBrIzq = rotBrIzq;
	KeyFrame[FrameIndex].rotBrDer = rotBrDer;
	KeyFrame[FrameIndex].rotRodDer = rotBrDer;
	KeyFrame[FrameIndex].giroMonito = giroMonito;

	FrameIndex++;
}

void resetElements(void)
{
	posX = KeyFrame[0].posX;
	posY = KeyFrame[0].posY;
	posZ = KeyFrame[0].posZ;

	rotRodIzq = KeyFrame[0].rotRodIzq;
	rotBrIzq = KeyFrame[0].rotBrIzq;
	rotBrDer = KeyFrame[0].rotBrDer;
	rotRodDer = KeyFrame[0].rotRodDer;
	giroMonito = KeyFrame[0].giroMonito;

}

void interpolation(void)
{
	KeyFrame[playIndex].incX = (KeyFrame[playIndex + 1].posX - KeyFrame[playIndex].posX) / i_max_steps;
	KeyFrame[playIndex].incY = (KeyFrame[playIndex + 1].posY - KeyFrame[playIndex].posY) / i_max_steps;
	KeyFrame[playIndex].incZ = (KeyFrame[playIndex + 1].posZ - KeyFrame[playIndex].posZ) / i_max_steps;

	KeyFrame[playIndex].rotInc = (KeyFrame[playIndex + 1].rotRodIzq - KeyFrame[playIndex].rotRodIzq) / i_max_steps;
	KeyFrame[playIndex].rotInc2 = (KeyFrame[playIndex + 1].rotBrIzq - KeyFrame[playIndex].rotBrIzq) / i_max_steps;
	KeyFrame[playIndex].rotInc3 = (KeyFrame[playIndex + 1].rotBrDer - KeyFrame[playIndex].rotBrDer) / i_max_steps;
	KeyFrame[playIndex].rotInc4 = (KeyFrame[playIndex + 1].rotRodDer - KeyFrame[playIndex].rotRodDer) / i_max_steps;
	KeyFrame[playIndex].giroMonitoInc = (KeyFrame[playIndex + 1].giroMonito - KeyFrame[playIndex].giroMonito) / i_max_steps;

}

void casa() {
	glPushMatrix(); 

		glTranslatef(0.0, 4.0, 0.0);
		glScalef(10,8,8);
		glPushMatrix();
			glColor3f(0.05,0.29,0.93);
			glDisable(GL_LIGHTING);
			fig3.prisma2(0,0);//fIGURA A
			glEnable(GL_LIGHTING);
		glPopMatrix();

		glScalef(.1, .125, .125);
		
		glPushMatrix();			
			glTranslatef(0,4.25,0);
			glScalef(12,.5,10);
			glPushMatrix();
				glColor3f(0.89,0.168,0.313);
				glDisable(GL_LIGHTING);
				fig3.prisma2(0, 0);   //FIGURA B 
				glEnable(GL_LIGHTING);
			glPopMatrix();
			glScalef(0.0833,2,0.1);
			glTranslatef(0,.5,0);
			glScalef(10, .5, 8);
			glPushMatrix();
				glColor3f(1, 0.1411, 0);
				glDisable(GL_LIGHTING);
				fig3.prisma2(0, 0);   //FIGURA C
				glEnable(GL_LIGHTING);
			glPopMatrix();
			glScalef(.1,2,0.125);
			glTranslatef(0,.5,0);
			glScalef(8,.5,6);
			glPushMatrix();
				glColor3f(0.89, 0.168, 0.313);
				glDisable(GL_LIGHTING);
				fig3.prisma2(0, 0);   //FIGURA D
				glEnable(GL_LIGHTING);
			glPopMatrix();
			glScalef(.125, 2, 0.166);
			glTranslatef(0, .5, 0);
			glScalef(6, .5, 4);
			glPushMatrix();
				glColor3f(1, 0.1411, 0);
				glDisable(GL_LIGHTING);
				fig3.prisma2(0, 0);   //FIGURA E
				glEnable(GL_LIGHTING);
			glPopMatrix();
			glScalef(.166, 2, 0.25);
			glTranslatef(0, .5, 0);
			glScalef(4, .5, 2);
			glPushMatrix();
				glColor3f(0.89, 0.168, 0.313);
				glDisable(GL_LIGHTING);
				fig3.prisma2(0, 0);   //FIGURA F
				glEnable(GL_LIGHTING);
			glPopMatrix();
			glScalef(.25, 2, 0.5);
			glTranslatef(4, -.25, 0);
			glScalef(2, 2, 2);
			glPushMatrix();
				glColor3f(1, 0.1411, 0);
				glDisable(GL_LIGHTING);
				fig3.prisma2(0, 0);   //FIGURA G
				glEnable(GL_LIGHTING);
			glPopMatrix();
			glScalef(.5, .5, 0.5);
			glTranslatef(0, 1.5, 0);
			glScalef(1, 1, 1);
			glPushMatrix();
				glColor3f(0.1098, 0.05, 0.007);
				glDisable(GL_LIGHTING);
				fig3.prisma2(0, 0);   //FIGURA H
				glEnable(GL_LIGHTING);
			glPopMatrix();
			glTranslatef(.5, 1, 0);
			glScalef(1, 1, 1);
			glPushMatrix();
				glColor3f(0.1098, 0.05, 0.007);
				glDisable(GL_LIGHTING);
				fig3.prisma2(0, 0);   //FIGURA I
				glEnable(GL_LIGHTING);
			glPopMatrix();
			glTranslatef(.5, 1, 0);
			glScalef(1, 1, 1);
			glPushMatrix();
				glColor3f(0.1098, 0.05, 0.007);
				glDisable(GL_LIGHTING);
				fig3.prisma2(0, 0);   //FIGURA J
				glEnable(GL_LIGHTING);
			glPopMatrix();
		glPopMatrix();
		
		glPushMatrix();
			glTranslatef(0,-1,4.05);
			glScalef(3,6,.1);
			glPushMatrix();
				glColor3f(1,1,1);
				glDisable(GL_LIGHTING);
				fig3.prisma2(NULL,text9.GLindex); //FIGURA K
				glEnable(GL_LIGHTING);
			glPopMatrix();
			glScalef(0.333,0.1666,10);
			glTranslatef(-3.25,1.75,0);
			glScalef(2.5,2.5,.1);
			glPushMatrix();
				glDisable(GL_LIGHTING);
				fig3.prisma2(NULL, text2.GLindex); //FIGURA L
				glEnable(GL_LIGHTING);
			glPopMatrix();
			glScalef(0.4,0.4,10);
			glTranslatef(6.5,0,0);
			glScalef(2.5, 2.5, .1);
			glPushMatrix();
				glDisable(GL_LIGHTING);
				fig3.prisma2(NULL, text2.GLindex); //FIGURA M
				glEnable(GL_LIGHTING);
			glPopMatrix();
		glPopMatrix();
		glPopMatrix();
}



void parque()
{
	//Comienzan los caminos

	glPushMatrix(); //pasto 1
		glTranslatef(-95, 0.0, -95.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1,0,0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 2
		glTranslatef(-95, 0.0, -85.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 3
		glTranslatef(-95, 0.0, -75.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 4
		glTranslatef(-95, 0.0, -65.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 5
		glTranslatef(-95, 0.0, -55.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 6
		glTranslatef(-95, 0.0, -45.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 7
		glTranslatef(-95, 0.0, -35.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 8
		glTranslatef(-95, 0.0, -25.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 9
		glTranslatef(-95, 0.0, -15.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 10
		glTranslatef(-95, 0.0, -5.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 11
		glTranslatef(-95, 0.0, 5.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 12
		glTranslatef(-95, 0.0, 15.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 13
		glTranslatef(-95, 0.0, 25.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 14
		glTranslatef(-95, 0.0, 35.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 15
		glTranslatef(-95, 0.0, 45.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 16
		glTranslatef(-95, 0.0, 55.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 17
		glTranslatef(-95, 0.0, 65.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 18
		glTranslatef(-95, 0.0, 75.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 19
		glTranslatef(-95, 0.0, 85.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix(); //pasto 20
		glTranslatef(-95, 0.0, 95.0);
		glScalef(10, 0.1, 10);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
		glTranslatef(1, 0, 0);
		glDisable(GL_LIGHTING);
		fig3.prisma2(text5.GLindex, 0);
		glEnable(GL_LIGHTING);
	glPopMatrix();



	//cielo
	glPushMatrix(); //cielo 1
	glRotatef(180,1,0,0);
		glPushMatrix();
			glTranslatef(-95, -125,95);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1,0,0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 2
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, 85);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 3
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, 75);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 4
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, 65);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 5
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, 55);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 6
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, 45);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 7
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, 35);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 8
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, 25);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 9
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, 15);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 10
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, 5);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 11
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, -5);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 12
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, -15);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 13
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, -25);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 14
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, -35);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 15
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, -45);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 16
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, -55);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 17
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, -65);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 18
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, -75);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 19
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, -85);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	glPushMatrix(); //cielo 20
		glRotatef(180, 1, 0, 0);
		glPushMatrix();
			glTranslatef(-95, -125, -95);
			glScalef(10, 0.1, 10);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
			glTranslatef(1, 0, 0);
			glDisable(GL_LIGHTING);
			fig3.prisma2(text8.GLindex, 0);
			glEnable(GL_LIGHTING);
		glPopMatrix();
	glPopMatrix();

	/*
	glPushMatrix(); //Camino1
	glTranslatef(0, 0.0, -30);
	glDisable(GL_LIGHTING);
	fig20.prisma(.5, 10, 10, piso.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();
	*/
	
}

/*
void Alumbrado(void) {
	glPushMatrix();
	glTranslatef(-28, 0, -43);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-19, 0, -43);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-28, 0, -55);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-19, 0, -55);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-28, 0, -67);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-19, 0, -67);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-28, 0, -77);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-19, 0, -77);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-28, 0, -90);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-19, 0, -90);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-28, 0, -102);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-19, 0, -102);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, 0, -67);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-5, 0, -77);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 0, -77);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 0, -67);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(25, 0, -77);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(25, 0, -67);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(41, 0, -77);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(41, 0, -67);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(52, 0, -77);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(52, 0, -67);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(52, 0, -52);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(41, 0, -52);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(52, 0, -35);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(41, 0, -35);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(52, 0, -20);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(41, 0, -20);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(52, 0, -5);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(41, 0, -5);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(52, 0, 10);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(41, 0, 10);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(52, 0, 25);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(41, 0, 25);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(52, 0, 42);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(41, 0, 42);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(52, 0, 52.5);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(41, 0, 52.5);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25, 0, 52.5);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(25, 0, 43);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(10, 0, 52.5);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, 0, 43);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-5, 0, 52.5);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-5, 0, 43);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20, 0, 52.5);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-20, 0, 43);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-35, 0, 52.5);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-35, 0, 43);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-50, 0, 52.5);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-50, 0, 43);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-65, 0, 52.5);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-65, 0, 43);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-88, 0, 52.5);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-88, 0,43);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();
	
	glPushMatrix();
	glTranslatef(-98, 0, 52.5);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-98, 0, 43);
	glScalef(.08, .08, .08);
	glEnable(GL_LIGHTING);
	solll.GLrender(NULL, _SHADED, 1.0);
	glDisable(GL_LIGHTING);
	glPopMatrix();
}

*/



/*
void carpa(void) {

	//Aquí empieza la barda del circo
	glPushMatrix();
		glTranslatef(15, 0, 0);
		glDisable(GL_LIGHTING);
		fig11.prisma(4,.5,15,text9.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-15, 0, 0);
		glDisable(GL_LIGHTING);
		fig11.prisma(4, .5, 15, text9.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(0, 0, 15);
		glDisable(GL_LIGHTING);
		fig11.prisma(4, 15, .5, text9.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.25, 0, 11.25);
		glRotatef(45,0,1,0);
		glDisable(GL_LIGHTING);
		fig11.prisma(4, 11, .5, text9.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.25, 0, 11.25);
		glRotatef(135, 0, 1, 0);
		glDisable(GL_LIGHTING);
		fig11.prisma(4, 11, .5, text9.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(11.25, 0, -11.25);
		glRotatef(135, 0, 1, 0);
		glDisable(GL_LIGHTING);
		fig11.prisma(4, 11, .5, text9.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-11.25, 0, -11.25);
		glRotatef(45, 0, 1, 0);
		glDisable(GL_LIGHTING);
		fig11.prisma(4, 11, .5, text9.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();
	

	//Aqui empiezan las gradas

	glPushMatrix();
		glTranslatef(20, 0,0 );
		glDisable(GL_LIGHTING);
		fig26.prisma(4,2,15,text8.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(22, 0, 0);
		glDisable(GL_LIGHTING);
		fig26.prisma(8, 2, 15, text8.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(24, 0, 0);
		glDisable(GL_LIGHTING);
		fig26.prisma(12, 2, 15, text8.GLindex);
		glEnable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(-20, 0, 0);
	glDisable(GL_LIGHTING);
	fig26.prisma(4, 2, 15, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-22, 0, 0);
	glDisable(GL_LIGHTING);
	fig26.prisma(8, 2, 15, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-24, 0, 0);
	glDisable(GL_LIGHTING);
	fig26.prisma(12, 2, 15, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0, 0, 20);
	glDisable(GL_LIGHTING);
	fig26.prisma(4, 15, 2, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 22);
	glDisable(GL_LIGHTING);
	fig26.prisma(8, 15, 2, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0,24);
	glDisable(GL_LIGHTING);
	fig26.prisma(12, 15,2, text8.GLindex);
	glEnable(GL_LIGHTING);
	glPopMatrix();

	glPushMatrix();
		glTranslatef(-30, -1, 30);
		glRotatef(180, 0, 1, 0);
		glScalef(.004, .004, .004);
		glPushMatrix();
		glColor3f(1,0,0);
		soll.GLrender(NULL, _SHADED, 1.0);
		glPopMatrix();
	glPopMatrix();
}
*/
/*
void carrusel(void)
{
	glTranslatef(0, 0, 23);
	glPushMatrix();
		glTranslatef(8, 0.1, 20);
		
	
	
	glPopMatrix();

	//techo
	
	
	glPushMatrix();
		glColor3f(0.1, 0.0, 0.0);
		glTranslatef(10, 6, 22);
		glRotatef(mundo, 0, 1, 0);
		fig24.cono(2,7,1000,10);
	glPopMatrix();
	//piso
	glPushMatrix();
		glTranslatef(10, 0.2, 22);
		glRotatef(mundo, 0, 1, 0);
		fig24.cono(0.01, 7, 1000, 10);
	glPopMatrix();

	//postes 
	glPushMatrix();
		glTranslatef(10, 0.1, 22);	
		glColor3f(1, 0, 0);
		fig25.cilindro(0.3, 6, 100, 10);
		glRotatef(mundo, 0, 1, 0);
		glScalef(0.0285, 0.0285, 0.0285);
		glTranslatef(230, 80, 50);
		glRotatef(210, 0, 1, 0);
		glEnable(GL_LIGHTING);
		sol.GLrender(NULL, _SHADED, 1.0);
		fig25.cilindro(3.1, 125, 1000, 2);
		fig25.cilindro(3.1, -75, 1000, 2);
	
	
		glTranslatef(250, 0, -50);
		glRotatef(-50, 0, 1, 0);
		sol.GLrender(NULL, _SHADED, 1.0);
		fig25.cilindro(3.1, 125, 1000, 2);
		fig25.cilindro(3.1, -75, 1000, 2);


		glTranslatef(250, 0, 0);
		glRotatef(-75, 0, 1, 0);
		sol.GLrender(NULL, _SHADED, 1.0);
		fig25.cilindro(3.1, 125, 1000, 2);
		fig25.cilindro(3.1, -75, 1000, 2);


		glTranslatef(250, 0, -30);
		glRotatef(-75, 0, 1, 0);
		sol.GLrender(NULL, _SHADED, 1.0);
		fig25.cilindro(3.1, 125, 1000, 2);
		fig25.cilindro(3.1, -75, 1000, 2);
	
		glTranslatef(250, 0, -80);
		glRotatef(-75, 0, 1, 0);
		sol.GLrender(NULL, _SHADED, 1.0);
	
		fig25.cilindro(3.1, 125, 1000, 2);
		fig25.cilindro(3.1, -75, 1000, 2);
	
		glDisable(GL_LIGHTING);
	
	glPopMatrix();
	
	
}
*/



GLuint createDL()
{
	GLuint ciudadDL;

	// Create the id for the list
	ciudadDL = glGenLists(1);
	// start list
	glNewList(ciudadDL, GL_COMPILE);

	parque();
	casa();
	glEndList();

	return(ciudadDL);
}

void InitGL(GLvoid)     // Inicializamos parametros
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);				// Negro de fondo	

	glEnable(GL_TEXTURE_2D);

	glShadeModel(GL_SMOOTH);

	glLightfv(GL_LIGHT1, GL_POSITION, Position);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, Diffuse);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glClearDepth(1.0f);									// Configuramos Depth Buffer
	glEnable(GL_DEPTH_TEST);							// Habilitamos Depth Testing
	glDepthFunc(GL_LEQUAL);								// Tipo de Depth Testing a realizar
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_AUTO_NORMAL);
	glEnable(GL_NORMALIZE);


    text1.LoadTGA("texturas/fondo.tga"); //paisaje fondo
	text1.BuildGLTexture();
	text1.ReleaseImage();

	text2.LoadTGA("texturas/ventana.tga"); //Ventana
	text2.BuildGLTexture();
	text2.ReleaseImage();

	piso.LoadTGA("texturas/pavimento.tga"); //pavimento
	piso.BuildGLTexture();
	piso.ReleaseImage();

	text5.LoadTGA("texturas/pasto.tga"); //pasto
	text5.BuildGLTexture();
	text5.ReleaseImage();

	text8.LoadTGA("texturas/cielo.tga"); //cielo
	text8.BuildGLTexture();
	text8.ReleaseImage();

	text9.LoadTGA("texturas/door.tga");//Puerta
	text9.BuildGLTexture();
	text9.ReleaseImage();

	sol._3dsLoad("Modelos/Caballo.3ds");
	sol.VertexNormals();

	soll._3dsLoad("Modelos/carpa.3ds");
	soll.VertexNormals();

	solll._3dsLoad("Modelos/lampara.3ds");
	solll.VertexNormals();

	//NEW////////////////////////////////////////////
	KeyFrame[0].arriba = 0;
	KeyFrame[0].horizontal = 0;
	KeyFrame[0].vertical = 1.4;
	KeyFrame[0].profundidad = -25;
	KeyFrame[0].giro = 0;



	KeyFrame[1].arriba = -8;
	KeyFrame[1].horizontal = 26.2;
	KeyFrame[1].vertical = 1.4;
	KeyFrame[1].profundidad = -25;
	KeyFrame[1].giro = 0;

	KeyFrame[2].arriba = 0;
	KeyFrame[2].horizontal = 26.2;
	KeyFrame[2].vertical = 1.4;
	KeyFrame[2].profundidad = -42;
	KeyFrame[2].giro = 0;

	KeyFrame[3].horizontal = 20;
	KeyFrame[3].vertical = 1.4;
	KeyFrame[3].profundidad = -42;
	KeyFrame[3].giro = 0;
	


	//END NEW//////////////////////////////

	objCamera.Position_Camera(0, 2.5f, 3, 0, 2.5f, 0, 0, 1, 0);

	//NEW Crear una lista de dibujo
	ciudad_display_list = createDL();

	//NEW Iniciar variables de KeyFrames
	for (int i = 0; i<MAX_FRAMES; i++)
	{
		KeyFrame[i].posX = 0;
		KeyFrame[i].posY = 0;
		KeyFrame[i].posZ = 0;
		KeyFrame[i].incX = 0;
		KeyFrame[i].incY = 0;
		KeyFrame[i].incZ = 0;
		KeyFrame[i].rotRodIzq = 0;
		KeyFrame[i].rotBrIzq = 0;
		KeyFrame[i].rotInc2 = 0;
		KeyFrame[i].rotInc = 0;
		KeyFrame[i].rotBrDer = 0;
		KeyFrame[i].rotInc3 = 0;
		KeyFrame[i].giroMonito = 0;
		KeyFrame[i].giroMonitoInc = 0;
	}
	//NEW//////////////////NEW//////////////////NEW///////////

}

void pintaTexto(float x, float y, float z, void *font, char *string)
{

	char *c;     //Almacena los caracteres a escribir
	glRasterPos3f(x, y, z);	//Posicion apartir del centro de la ventana
							//glWindowPos2i(150,100);
	for (c = string; *c != '\0'; c++) //Condicion de fin de cadena
	{
		glutBitmapCharacter(font, *c); //imprime
	}
}

void display(void)   // Creamos la funcion donde se dibuja
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	glPushMatrix();
		glRotatef(g_lookupdown, 1.0f, 0, 0);
		gluLookAt(objCamera.mPos.x, objCamera.mPos.y, objCamera.mPos.z,
			objCamera.mView.x, objCamera.mView.y, objCamera.mView.z,
			objCamera.mUp.x, objCamera.mUp.y, objCamera.mUp.z);

		glPushMatrix();
			glPushMatrix(); //Creamos cielo
				glDisable(GL_LIGHTING);
				glTranslatef(0, 60, 0);
				fig3.skybox(200.0, 130.0, 200.0, text1.GLindex);
				glEnable(GL_LIGHTING);
			glPopMatrix();

			glPushMatrix();
				glEnable(GL_COLOR_MATERIAL);
				glColor3f(1, 1, 1);
				glCallList(ciudad_display_list);
				glTranslatef(posX, posY, posZ);
				glRotatef(giroMonito, 0, 1, 0);
				glDisable(GL_COLOR_MATERIAL);
			glPopMatrix();
			glEnable(GL_LIGHTING);
		glPopMatrix();
		glColor3f(1.0, 1.0, 1.0);
	glPopMatrix();

	glDisable(GL_TEXTURE_2D);
	glDisable(GL_LIGHTING);
	glColor3f(1.0, 0.0, 0.0);
	pintaTexto(-11, 12.0, -14.0, (void *)font, "Proyecto Lego.");
	glColor3f(1.0, 1.0, 1.0);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glutSwapBuffers();

}


void reshape(int width, int height)   // Creamos funcion Reshape
{
	if (height == 0)										// Prevenir division entre cero
	{
		height = 1;
	}

	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);						// Seleccionamos Projection Matrix
	glLoadIdentity();

	// Tipo de Vista

	glFrustum(-0.1, 0.1, -0.1, 0.1, 0.1, 170000.0);

	glMatrixMode(GL_MODELVIEW);							// Seleccionamos Modelview Matrix
	glLoadIdentity();
}

int test = 0;

void keyboard(unsigned char key, int x, int y)  // Create Keyboard Function
{
	switch (key) {
	case 'w':   //Movimientos de camara
	case 'W': //Adelante
		objCamera.Move_Camera(CAMERASPEED + 0.2);
		break;

	case 's'://Atrás
	case 'S':
		objCamera.Move_Camera(-(CAMERASPEED + 0.2));
		break;

	case 'a'://Izquierda
	case 'A':
		objCamera.Strafe_Camera(-(CAMERASPEED + 0.4));
		break;

	case 'd'://Derecha
	case 'D':
		objCamera.Strafe_Camera(CAMERASPEED + 0.4);
		break;
	case 'x'://Arriba
	case 'X':
		objCamera.UpDown_Camera(CAMERASPEED + 0.1);
		break;
	case 'c'://Abajo
	case 'C':
		objCamera.UpDown_Camera(-(CAMERASPEED + 0.1));
		break;

	case 27:        // Cuando Esc es presionado...
		exit(0);   // Salimos del programa
		break;

	default:        // Cualquier otra
		break;
	}

	glutPostRedisplay();
}

void arrow_keys(int a_keys, int x, int y)  // Funcion para manejo de teclas especiales (arrow keys)
{
	switch (a_keys) {
	case GLUT_KEY_PAGE_UP:
		objCamera.UpDown_Camera(CAMERASPEED);
		break;

	case GLUT_KEY_PAGE_DOWN:
		objCamera.UpDown_Camera(-CAMERASPEED);
		break;

	case GLUT_KEY_UP:     // Presionamos tecla ARRIBA...
		g_lookupdown -= 1.0f;
		break;

	case GLUT_KEY_DOWN:               // Presionamos tecla ABAJO...
		g_lookupdown += 1.0f;
		break;

	case GLUT_KEY_LEFT:
		objCamera.Rotate_View(-CAMERASPEED);
		break;

	case GLUT_KEY_RIGHT:
		objCamera.Rotate_View(CAMERASPEED);
		break;

	default:
		break;
	}
	glutPostRedisplay();
}



int main(int argc, char** argv)   // Main Function
{
	int submenu;
	glutInit(&argc, argv); // Inicializamos OpenGL
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH); // Display Mode (Clores RGB y alpha | Buffer Doble )
	glutInitWindowSize(500, 500);	// Tamaño de la Ventana
	glutInitWindowPosition(0,0);	//Posicion de la Ventana
	glutCreateWindow("Proyecto Final Lego"); // Nombre de la Ventana
	//glutFullScreen     ( );         // Full Screen
	InitGL();						// Parametros iniciales de la aplicacion
	glutDisplayFunc(display);  //Indicamos a Glut función de dibujo
	glutReshapeFunc(reshape);	//Indicamos a Glut función en caso de cambio de tamano
	glutKeyboardFunc(keyboard);	//Indicamos a Glut función de manejo de teclado
	glutSpecialFunc(arrow_keys);	//Otras
	

	
	Audio();

	glutMainLoop();  

	return 0;
}