#include "Scene6.h"

CScene6::CScene6()
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
	pTextures = new CTexture();
	pTextures->CreateTextureMipMap(0, "../Scene1/parede.BMP");
	pTextures->CreateTextureMipMap(1, "../Scene1/paredejanela.BMP");
	pTextures->CreateTextureMipMap(2, "../Scene1/R1.jpg");
	pTextures->CreateTextureMipMap(3, "../Scene1/CRATE.BMP");
	pTextures->CreateTextureMipMap(4, "../Scene1/grama.BMP");
	pTextures->CreateTextureMipMap(5, "../Scene1/paredeporta.BMP");


	fRotY = 0.0f;

	fPosX = 0.0f;
	fPosY = 0.0f;
	fPosZ = 0.0f;
}


CScene6::~CScene6(void)
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




int CScene6::DrawGLScene(void)	// Função que desenha a cena
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
	glColor4ub(255, 255, 255, 255);

	// Habilita texturização
	glEnable(GL_TEXTURE_2D);

	// Desenha Casa
	DrawCasa();

	//Caixas Menores
	DrawCaixa(
		5.0f, 0.5f, 7.0f, 0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f
	);
	DrawCaixa(
		-1.5f, 1.5f, 8.5f, 0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 45.0f
	);

	//Caixa Grande
	DrawCaixa(
		4.0f, 0.5f, 3.5f, 1.0f, 2.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f
	);


	glDisable(GL_TEXTURE_2D);

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

	//// Imprime o FPS da aplicação e o Timer
	glRasterPos2f(10.0f, 80.0f);
	pTexto->glPrint("Frames-per-Second: %d ---- Timer: %.1f segundos", iFPS, (pTimer->GetTime() / 1000));

	glRasterPos2f(10.0f, 100.0f);

	glPopMatrix();

	// Muda para modo de projeção perspectiva 3D
	PerspectiveMode();

	return true;
}




void CScene6::MouseMove(void) // Tratamento de movimento do mouse
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

void CScene6::KeyPressed(void) // Tratamento de teclas pressionadas
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

void CScene6::KeyDownPressed(WPARAM	wParam) // Tratamento de teclas pressionadas
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
void CScene6::Draw3DSGrid(float width, float length)
{
	glColor4ub(255, 255, 255, 255);

	// Habilita texturização
	glEnable(GL_TEXTURE_2D);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	pTextures->ApplyTexture(4);
	glPushMatrix();
		glBegin(GL_QUADS);
			glTexCoord2d(0.0f, 0.0f); glVertex3f(-width, 0.0f, -length); // Canto inferior esquerdo
			glTexCoord2d(width, 0.0f); glVertex3f(width, 0.0f, -length);   // Canto inferior direito
			glTexCoord2d(width, length); glVertex3f(width, 0.0f, length);   // Canto superior direito
			glTexCoord2d(0.0f, length); glVertex3f(-width, 0.0f, length);	// Canto superior esquerdo
		glEnd();
	glPopMatrix();
	glDisable(GL_TEXTURE_2D);
}



void CScene6::DrawAxis()
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


void CScene6::DrawCasa()
{
	// face frente (Janela)
	pTextures->ApplyTexture(1);
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);

	glTexCoord2d(0.0f, 0.0f); glVertex3f(-2.5f, 0.0f, 1.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.9f, 0.0f, 1.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.9f, 1.7f, 1.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-2.5f, 1.7f, 1.0f);

	glEnd();
	glPopMatrix();

	//face frente (Porta)
	pTextures->ApplyTexture(5);
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);

	glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.9f, 0.0f, 1.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(0.7f, 0.0f, 1.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(0.7f, 1.7f, 1.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.9f, 1.7f, 1.0f);

	glEnd();
	glPopMatrix();

	//face frente (Resto)
	pTextures->ApplyTexture(0);
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);

	glTexCoord2d(0.0f, 0.0f); glVertex3f(0.7f, 0.0f, 1.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.5f, 0.0f, 1.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.5f, 1.7f, 1.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(0.7f, 1.7f, 1.0f);

	glEnd();
	glPopMatrix();

	// face esquerda (Janela)
	pTextures->ApplyTexture(1);
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);

	glTexCoord2d(0.0f, 0.0f); glVertex3f(-2.5f, 0.0f, -1.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-2.5f, 0.0f, 1.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-2.5f, 1.7f, 1.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(-2.5f, 1.7f, -1.0f);

	glEnd();
	glPopMatrix();

	//Resto
	pTextures->ApplyTexture(0);
	glPushMatrix();
		glTranslatef(0.0f, 0.0f, 0.0f);
	glBegin(GL_QUADS);

	//face direita
	glTexCoord2d(0.0f, 0.0f); glVertex3f(2.5f, 0.0f, -1.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(2.5f, 0.0f, 1.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.5f, 1.7f, 1.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(2.5f, 1.7f, -1.0f);

	// face baixo
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-2.5f, 0.0f, -1.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(2.5f, 0.0f, -1.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.5f, 0.0f, 1.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-2.5f, 0.0f, 1.0f);

	// face cima
	glTexCoord2d(0.0f, 0.0f); glVertex3f(-2.5f, 1.7f, 1.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(2.5f, 1.7f, 1.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(2.5f, 1.7f, -1.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-2.5f, 1.7f, -1.0f);

	// face trás
	glTexCoord2d(0.0f, 0.0f); glVertex3f(2.5f, -0.0f, -1.0f);
	glTexCoord2d(1.0f, 0.0f); glVertex3f(-2.5f, -0.0f, -1.0f);
	glTexCoord2d(1.0f, 1.0f); glVertex3f(-2.5f, 1.7f, -1.0f);
	glTexCoord2d(0.0f, 1.0f); glVertex3f(2.5f, 1.7f, -1.0f);

	glEnd();
	glPopMatrix();


	//Telhado
	// Seta a textura atual
	pTextures->ApplyTexture(2);
	glPushMatrix();
		//glScalef(5.0f, 2.0f, 2.5f);
		glTranslatef(0.0f, 2.0f, 0.0f);
		glRotatef(180.0f, 1.0f, 0.0f, 0.0f);
		glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
		glRotatef(45.0f, 0.0f, 0.0f, 1.0f);
	glBegin(GL_QUADS);

		// face esquerda
		glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -3.0f);
		glTexCoord2d(0.0f, 1.0f); glVertex3f(-0.5f, -0.5f, 3.0f);
		glTexCoord2d(1.0f, 1.0f); glVertex3f(-0.5f, 1.5f, 3.0f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, 1.5f, -3.0f);

		// face baixo
		glTexCoord2d(0.0f, 0.0f); glVertex3f(-0.5f, -0.5f, -3.0f);
		glTexCoord2d(0.0f, 1.0f); glVertex3f(1.5f, -0.5f, -3.0f);
		glTexCoord2d(1.0f, 1.0f); glVertex3f(1.5f, -0.5f, 3.0f);
		glTexCoord2d(1.0f, 0.0f); glVertex3f(-0.5f, -0.5f, 3.0f);

	glEnd();
	glPopMatrix();

}

void CScene6::DrawCaixa(float x, float y, float z, float Sx, float Sy, float Sz, float Rx, float Ry, float Rz, float rotation)
{
	// Seta a textura atual
	pTextures->ApplyTexture(3);
	glPushMatrix();
	glScalef(Sx, Sy, Sz);
	glRotatef(rotation, Rx, Ry, Rz);
	glTranslatef(x, y, z);
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
	glPopMatrix();
}