#include "Scene4.h"

CScene4::CScene4()
{
	pCamera = NULL;
	pTexto = NULL;
	pTextures = NULL;

	bIsWireframe = false;
	bIsCameraFPS = true;

	iFPS = 0;
	iFrames = 0;
	ulLastFPS = 0;
	szTitle[256] = 0;

	// Cria gerenciador de impressão de texto na tela
	pTexto = new CTexto();

	// Cria camera
	pCamera = new CCamera(0.0f, 1.0f, 20.0f, 0.1f);

	// Cria o Timer
	pTimer = new CTimer();
	pTimer->Init();

	fTimerPosY = 0.0f;
	fRenderPosY = 0.0f;

	// Carrega todas as texturas
	// pTextures = new CTexture();


	fRotY = 0.0f;

	fPosX = 0.0f;
	fPosY = 0.0f;
	fPosZ = 0.0f;
}


CScene4::~CScene4(void)
{
	if (pTexto)
	{
		delete pTexto;
		pTexto = NULL;
	}

	if (pTextures)
	{
		delete pTextures;
		pTextures = NULL;
	}

	if (pCamera)
	{
		delete pCamera;
		pCamera = NULL;
	}

	if (pTimer)
	{
		delete pTimer;
		pTimer = NULL;
	}
}




int CScene4::DrawGLScene(void)	// Função que desenha a cena
{
	// Get FPS
	if (GetTickCount() - ulLastFPS >= 1000)	// When A Second Has Passed...
	{
		ulLastFPS = GetTickCount();				// Update Our Time Variable
		iFPS = iFrames;							// Save The FPS
		iFrames = 0;							// Reset The FPS Counter
	}
	iFrames++;									// FPS counter

	pTimer->Update();							// Atualiza o timer

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Limpa a tela e o Depth Buffer
	glLoadIdentity();									// Inicializa a Modelview Matrix Atual


	// Seta as posições da câmera
	pCamera->setView();

	// Desenha grid 
	Draw3DSGrid(20.0f, 20.0f);

	// Desenha os eixos do sistema cartesiano
	DrawAxis();

	// Modo FILL ou WIREFRAME (pressione barra de espaço)	
	if (bIsWireframe)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	else
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (INÍCIO)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//Arveres
	DrawTree(1.0f, 3.0f, 0.75f);
	DrawTree(0.0f, 3.0f, 1.0f);
	DrawTree(-1.0f, 3.0f, 1.3f);

	DrawTree(-2.0f, 2.0f, 1.0f);
	DrawTree(-2.0f, 1.0f, 1.0f);
	DrawTree(-2.0f, 0.0f, 1.0f);
	DrawTree(-2.0f, -1.0f, 1.0f);
	DrawTree(-2.0f, -2.0f, 1.0f);
	DrawTree(-2.0f, -3.0f, 1.0f);

	DrawTree(1.0f, -3.0f, 0.75f);
	DrawTree(0.0f, -3.0f, 1.0f);
	DrawTree(-1.0f, -3.0f, 1.3f);


	//Walter White
	glColor3ub(220, 220, 220);
	glPushMatrix();
		glRotatef(fRotY, 1.0f, 0.0f, 0.0f);

		//Corpo
		glPushMatrix();

			glTranslatef(0.0f, 0.25f, 0.0f);
			auxSolidSphere(0.35f);

			glTranslatef(0.0f, 0.35f, 0.0f);
			auxSolidSphere(0.25f);

		glPopMatrix();

		glPushMatrix();

			//Cabeça
			glTranslatef(0.0f, 0.95f, 0.0f);
			auxSolidSphere(0.15f);

			//Naso
			glColor3ub(255, 165, 0);
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			glTranslatef(0.0f, 0.0f, 0.07f);
			auxSolidCone(0.02f, 0.2f);

			//Olhos
			glColor3ub(0, 0, 0);

			glTranslatef(0.07f, 0.02f, 0.07f);
			auxSolidSphere(0.02f);

			glTranslatef(-0.14f, 0.0f, 0.00f);
			auxSolidSphere(0.02f);

		glPopMatrix();

		glPushMatrix();
			glTranslatef(0.0f, 0.1f, 0.0f);
			auxSolidCylinder(0.2f, 0.05f);
			glTranslatef(0.0f, 0.1f, 0.0f);
			auxSolidCylinder(0.1f, 0.1f);
		glPopMatrix();
	glPopMatrix();

	if (bEsq) {
		fRotY += 1.0f;

		if (fRotY == 360) {
			fRotY = 0.0f;
		}
		else if (fRotY == 45.0f) bEsq = false;
	}
	else {
		fRotY -= 1.0f;

		if (fRotY == 0) {
			fRotY = 360.0f;
		}
		else if (fRotY == 325.0f) bEsq = true;
	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//                               DESENHA OS OBJETOS DA CENA (FIM)
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	fTimerPosY = pTimer->GetTime() / 1000.0f;
	fRenderPosY += 0.2f;

	// Impressão de texto na tela...
	// Muda para modo de projeção ortogonal 2D
	// OBS: Desabilite Texturas e Iluminação antes de entrar nesse modo de projeção
	OrthoMode(0, 0, WIDTH, HEIGHT);


	glPushMatrix();
	glTranslatef(0.0f, HEIGHT - 150, 0.0f);	// Move 1 unidade para dentro da tela (eixo Z)

	// Cor da fonte
	glColor3f(1.0f, 1.0f, 0.0f);


	glRasterPos2f(10.0f, 0.0f);	// Posicionando o texto na tela
	if (!bIsWireframe) {
		pTexto->glPrint("[TAB]  Modo LINE"); // Imprime texto na tela
	}
	else {
		pTexto->glPrint("[TAB]  Modo FILL");
	}


	//// Camera LookAt
	glRasterPos2f(10.0f, 40.0f);
	pTexto->glPrint("Player LookAt  : %f, %f, %f", pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);

	//// Posição do Player
	glRasterPos2f(10.0f, 60.0f);
	pTexto->glPrint("Player Position: %f, %f, %f", pCamera->Position[0], pCamera->Position[1], pCamera->Position[2]);

	//// Imprime o FPS da aplicação e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime() / 1000));

	glRasterPos2f(10.0f, 100.0f);
	pTexto->glPrint("fRot: %.1f ", fRotY);




	glPopMatrix();

	// Muda para modo de projeção perspectiva 3D
	PerspectiveMode();

	return true;
}




void CScene4::MouseMove(void) // Tratamento de movimento do mouse
{
	// Realiza os cálculos de rotação da visão do Player (através das coordenadas
	// X do mouse.
	POINT mousePos;
	int middleX = WIDTH >> 1;
	int middleY = HEIGHT >> 1;

	GetCursorPos(&mousePos);

	if ((mousePos.x == middleX) && (mousePos.y == middleY)) return;

	SetCursorPos(middleX, middleY);

	fDeltaX = (float)((middleX - mousePos.x)) / 10;
	fDeltaY = (float)((middleY - mousePos.y)) / 10;

	// Rotaciona apenas a câmera
	pCamera->rotateGlob(-fDeltaX, 0.0f, 1.0f, 0.0f);
	pCamera->rotateLoc(-fDeltaY, 1.0f, 0.0f, 0.0f);
}

void CScene4::KeyPressed(void) // Tratamento de teclas pressionadas
{

	// Verifica se a tecla 'W' foi pressionada e move o Player para frente
	if (GetKeyState('W') & 0x80)
	{
		pCamera->moveGlob(pCamera->Forward[0], pCamera->Forward[1], pCamera->Forward[2]);
	}
	// Verifica se a tecla 'S' foi pressionada e move o Player para tras
	else if (GetKeyState('S') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Forward[0], -pCamera->Forward[1], -pCamera->Forward[2]);
	}
	// Verifica se a tecla 'A' foi pressionada e move o Player para esquerda
	else if (GetKeyState('A') & 0x80)
	{
		pCamera->moveGlob(-pCamera->Right[0], -pCamera->Right[1], -pCamera->Right[2]);
	}
	// Verifica se a tecla 'D' foi pressionada e move o Player para direira
	else if (GetKeyState('D') & 0x80)
	{
		pCamera->moveGlob(pCamera->Right[0], pCamera->Right[1], pCamera->Right[2]);
	}
	else if (GetKeyState('Q') & 0x80)
	{
		pCamera->moveGlob(0.0f, -pCamera->Up[1], 0.0f);
	}
	else if (GetKeyState('E') & 0x80)
	{
		pCamera->moveGlob(0.0f, pCamera->Up[1], 0.0f);
	}
	// Senão, interrompe movimento do Player
	else
	{
	}


	if (GetKeyState(VK_LEFT) & 0x80)
		fPosX -= 0.1f;
	if (GetKeyState(VK_RIGHT) & 0x80)
		fPosX += 0.1f;
	if (GetKeyState(VK_UP) & 0x80)
		fPosZ -= 0.1f;
	if (GetKeyState(VK_DOWN) & 0x80)
		fPosZ += 0.1f;
	if (GetKeyState(VK_PRIOR) & 0x80)
		fPosY += 0.1f;
	if (GetKeyState(VK_NEXT) & 0x80)
		fPosY -= 0.1f;


}

void CScene4::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
{
	switch (wParam)
	{
	case VK_TAB:
		bIsWireframe = !bIsWireframe;
		break;

	case VK_SPACE:
		pTimer->Init();
		break;

	case VK_RETURN:
		break;

	}

}

//	Cria um grid horizontal ao longo dos eixos X e Z
void CScene4::Draw3DSGrid(float width, float length)
{
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  // Mude para o modo de preenchimento sólido
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glBegin(GL_QUADS);
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(-width, 0.0f, -length);  // Canto inferior esquerdo
	glVertex3f(width, 0.0f, -length);   // Canto inferior direito
	glVertex3f(width, 0.0f, length);    // Canto superior direito
	glVertex3f(-width, 0.0f, length);   // Canto superior esquerdo
	glEnd();
	glPopMatrix();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}



void CScene4::DrawAxis()
{
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	// Eixo X
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-1000.0f, 0.0f, 0.0f);
	glVertex3f(1000.0f, 0.0f, 0.0f);

	// Eixo Y
	glColor3f(0.0f, 1.0f, 0.0f);
	glVertex3f(0.0f, 1000.0f, 0.0f);
	glVertex3f(0.0f, -1000.0f, 0.0f);

	// Eixo Z
	glColor3f(0.0f, 0.0f, 1.0f);
	glVertex3f(0.0f, 0.0f, 1000.0f);
	glVertex3f(0.0f, 0.0f, -1000.0f);
	glEnd();
	glPopMatrix();
}


void CScene4::DrawCube()
{
	glBegin(GL_QUADS);
	// face frente
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);

	// face trás
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, -0.5f);

	// face direita
	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.5f, 0.5f, 0.5f);

	// face esquerda
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

	// face baixo
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 0.5f);

	// face cima
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, 0.5f, 0.5f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.5f, 0.5f, 0.5f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.5f, 0.5f, -0.5f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, 0.5f, -0.5f);

	glEnd();
}


void CScene4::DrawPyramid()
{
	glBegin(GL_TRIANGLES);

	// Face frente
	glTexCoord2f(0.02f, 0.1f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.435f, 0.1f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.23f, 0.45f); glVertex3f(0.0f, 0.5f, 0.0f);

	// Face direita
	glTexCoord2f(0.52f, 0.1f); glVertex3f(0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.94f, 0.1f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.73f, 0.45f); glVertex3f(0.0f, 0.5f, 0.0f);

	// Face esquerda
	glTexCoord2f(0.02f, 0.56f); glVertex3f(0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.435f, 0.56f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.23f, 0.9f); glVertex3f(0.0f, 0.5f, 0.0f);

	// Face trás
	glTexCoord2f(0.53f, 0.56f); glVertex3f(-0.5f, -0.5f, -0.5f);
	glTexCoord2f(0.93f, 0.56f); glVertex3f(-0.5f, -0.5f, 0.5f);
	glTexCoord2f(0.73f, 0.9f); glVertex3f(0.0f, 0.5f, 0.0f);
	glEnd();
}

void CScene4::DrawTree(float x, float z, float scale) {
	glPushMatrix();

	glTranslatef(x, 0.0f, z);
	glScalef(scale, scale, scale);

	// Tronco
	glColor3f(0.4f, 0.2f, 0.0f);
	auxSolidCylinder(0.1f, 1.0f);

	// Copa 1
	glColor3f(0.0f, 0.8f, 0.0f);
	glTranslatef(0.0f, 1.0f, 0.0f);
	glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
	auxSolidCone(0.5f, 1.0f);

	// Copa2
	glColor3f(0.0f, 0.8f, 0.0f);
	glTranslatef(0.0f, 0.0f, 0.5f);
	glRotatef(0.0f, 1.0f, 0.0f, 0.0f);
	auxSolidCone(0.5f, 1.0f);

	glPopMatrix();
}