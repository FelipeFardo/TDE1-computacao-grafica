#pragma once
#pragma once
#include "SceneBaseClass.h"
#include "CTexture.h"
#include "CTimer.h"
#include "CTexto.h"
#include "CCamera.h"
#include "VertexData.h"
#include <glm/glm.hpp>
#include <vector>
#include <cstdlib>
#include <ctime>

class CScene5 : public CSceneBaseClass
{
public:
	CScene5();
	~CScene5(void);


	virtual void MouseMove(void);					// Tratamento de movimento do mouse
	virtual void KeyPressed(void);					// Tratamento de teclas pressionadas
	virtual void KeyDownPressed(WPARAM	wParam);	// Tratamento de teclas pressionadas
	virtual int DrawGLScene(void);					// Função que desenha a cena

	void Draw3DSGrid(float width, float length);
	void DrawAxis();

	void DrawCube(float x, float y, float r, float g, float b);
	void StackCubes(float x, float r, float g, float b);
	void checkClearPositions();

private:

	bool	keys[256];		// Array usado para rotinas do teclado
	bool	active;			// Window Active Flag Set To TRUE By Default
	bool	fullscreen;		// Exibir janela em modo fullscreem (TRUE) ou em janela (FALSE)


	CCamera* pCamera;	// Gerencia câmera OpenGL
	float fDeltaY;				// Rotação da câmera OpenGL no eixo Y
	float fDeltaX;				// Rotação da câmera OpenGL no eixo X

	CTexto* pTexto;	// Objeto que gerencia texto
	CTexture* pTextures;	// Objeto que gerencia texturas
	CTimer* pTimer;	// Objeto que gerencia o timer


	int		iFPS;			// FPS and FPS Counter
	int		iFrames;		// FPS and FPS Counter
	DWORD	ulLastFPS;		// FPS and FPS Counter
	char	szTitle[256];	// FPS and FPS Counter


	bool bIsWireframe;	// Modos Wireframe/Solid
	bool bIsCameraFPS;	// Ativa modo de camera First Person Shooter (true) ou Third Person Shooter (false)

	float fRenderPosY;
	float fTimerPosY;

	float fRotY;
	bool bEsq = true;

	float fPosX;
	float fPosY;
	float fPosZ;

	int r;
	int g;
	int b;

	float randX;
	float randY;
	float randZ;

	int counter;

	int occPositions[5][10] = {
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
		{0,0,0,0,0,0,0,0,0,0},
	};

	float cubos[5][10][5];
};