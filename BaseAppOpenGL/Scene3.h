#pragma once
#include "SceneBaseClass.h"
#include "CTexture.h"
#include "CTimer.h"
#include "CTexto.h"
#include "CCamera.h"
#include "VertexData.h"
#include <glm/glm.hpp>
#include <vector>

class CScene3 : public CSceneBaseClass
{
public:
	CScene3();
	~CScene3(void);


	virtual void MouseMove(void);					// Tratamento de movimento do mouse
	virtual void KeyPressed(void);					// Tratamento de teclas pressionadas
	virtual void KeyDownPressed(WPARAM	wParam);	// Tratamento de teclas pressionadas
	virtual int DrawGLScene(void);					// Função que desenha a cena

	void Draw3DSGrid(float width, float length);
	void DrawAxis();

	void DrawCube();
	void DrawPyramid();

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

	float fPosX;
	float fPosY;
	float fPosZ;

	unsigned char R;
	unsigned char G;
	unsigned char B;


	CColor3 faceColor[38];

	// CASA
	CVector3 vCasaVertices[41] = {
	{7.34, 11.26, -2.34},
	{7.34, 11.26, -2.34},
	{-7.34, 11.26, -2.34},
	{-7.34, 11.26, 2.34},
	{7.34, 11.26, 2.34},
	 {10.48, 7.46, -5.48},
	 {10.48, 7.46, 5.48},
	 {10.48, 0.00, 5.48},
	 {10.48, 0.00, -5.48},
	{-10.48, 0.00, -5.48},
	{-10.48, 7.46, -5.48},
	{-10.48, 7.46, 5.48},
	{-10.48, 0.00, 5.48},
	{-0.41, 1.43, 4.89},
	{-0.41, 1.43, 5.48},
	 {2.37, 1.43, 5.48},
	 {2.37, 1.43, 4.89},
	 {2.37, 4.66, 5.48},
	 {2.37, 4.66, 4.89},
	{-0.41, 4.66, 5.48},
	{-0.41, 4.66, 4.89},
	 {4.45, 4.66, 4.89},
	 {7.24, 4.66, 4.89},
	 {7.24, 4.66, 5.48},
	 {4.45, 4.66, 5.48},
	 {4.45, 1.43, 5.48},
	 {4.45, 1.43, 4.89},
	 {7.24, 1.43, 5.48},
	 {7.24, 1.43, 4.89},
	{-3.30, 0.18, 5.48},
	{-3.30, 0.18, 4.67},
	{-8.35, 0.18, 4.67},
	{-8.35, 0.18, 5.48},
	{-3.30, 6.03, 5.48},
	{-3.30, 6.03, 4.67},
	{-8.35, 6.03, 5.48},
	{-8.35, 6.03, 4.67},
	{11.70, 7.02, 6.12},
	{-11.70, 7.02, 6.12},
	{11.70, 7.02, -6.12},
	{-11.70, 7.02, -6.12}
	};

	CIndex3 vCasaIndexes[68] = {
		{1,2,3},
		{3,4,1},
		{5,6,7},
		{7,8,5},
		{5,8,9},
		{9,10,5},
		{11,10,9},
		{9,12,11},
		{13,14,15},
		{15,16,13},
		{17,18,16},
		{16,15,17},
		{19,20,18},
		{18,17,19},
		{19,14,13},
		{13,20,19},
		{21,22,23},
		{23,24,21},
		{24,25,26},
		{26,21,24},
		{25,27,28},
		{28,26,25},
		{28,27,23},
		{23,22,28},
		{29,30,31},
		{31,32,29},
		{33,34,30},
		{30,29,33},
		{35,36,34},
		{34,33,35},
		{31,36,35},
		{35,32,31},
		{11,33,24},
		{11,24,23},
		{6,11,23},
		{6,23,27},
		{7,6,27},
		{7,27,25},
		{25,24,17},
		{25,17,15},
		{7,25,15},
		{7,15,14},
		{17,24,33},
		{19,17,33},
		{14,19,33},
		{14,33,29},
		{7,14,29},
		{7,29,32},
		{35,33,11},
		{32,35,11},
		{32,11,12},
		{7,32,12},
		{11,6,37},
		{37,38,11},
		{6,5,39},
		{39,37,6},
		{5,10,40},
		{40,39,5},
		{10,11,38},
		{38,40,10},
		{38,37,4},
		{4,3,38},
		{37,39,1},
		{1,4,37},
		{39,40,2},
		{2,1,39},
		{40,38,3},
		{3,2,40}
	};





	vector<CVector3> vCasaVerticesVA = {
		{7.34, 11.26, -2.34 },
	{7.34, 11.26, -2.34 },
	{-7.34, 11.26, -2.34},
	{-7.34, 11.26, 2.34 },
	{7.34, 11.26, 2.34},
	 {10.48, 7.46, -5.48},
	 {10.48, 7.46, 5.48},
	 {10.48, 0.00, 5.48},
	 {10.48, 0.00, -5.48},
	{-10.48, 0.00, -5.48},
	{-10.48, 7.46, -5.48},
	{-10.48, 7.46, 5.48},
	{-10.48, 0.00, 5.48},
	{-0.41, 1.43, 4.89},
	{-0.41, 1.43, 5.48},
	 {2.37, 1.43, 5.48},
	 {2.37, 1.43, 4.89},
	 {2.37, 4.66, 5.48},
	 {2.37, 4.66, 4.89},
	{-0.41, 4.66, 5.48},
	{-0.41, 4.66, 4.89},
	 {4.45, 4.66, 4.89},
	 {7.24, 4.66, 4.89},
	 {7.24, 4.66, 5.48},
	 {4.45, 4.66, 5.48},
	 {4.45, 1.43, 5.48},
	 {4.45, 1.43, 4.89},
	 {7.24, 1.43, 5.48},
	 {7.24, 1.43, 4.89},
	{-3.30, 0.18, 5.48},
	{-3.30, 0.18, 4.67},
	{-8.35, 0.18, 4.67},
	{-8.35, 0.18, 5.48},
	{-3.30, 6.03, 5.48},
	{-3.30, 6.03, 4.67},
	{-8.35, 6.03, 5.48},
	{-8.35, 6.03, 4.67},
	{11.70, 7.02, 6.12},
	{-11.70, 7.02, 6.12},
	{11.70, 7.02, -6.12},
	{-11.70, 7.02, -6.12}
	};

	vector<unsigned int> vCasaIndexesVA = {
		1,2,3,
		3,4,1,
		5,6,7,
		7,8,5,
		5,8,9,
		9,10,5,
		11,10,9,
		9,12,11,
		13,14,15,
		15,16,13,
		17,18,16,
		16,15,17,
		19,20,18,
		18,17,19,
		19,14,13,
		13,20,19,
		21,22,23,
		23,24,21,
		24,25,26,
		26,21,24,
		25,27,28,
		28,26,25,
		28,27,23,
		23,22,28,
		29,30,31,
		31,32,29,
		33,34,30,
		30,29,33,
		35,36,34,
		34,33,35,
		31,36,35,
		35,32,31,
		11,33,24,
		11,24,23,
		6,11,23,
		6,23,27,
		7,6,27,
		7,27,25,
		25,24,17,
		25,17,15,
		7,25,15,
		7,15,14,
		17,24,33,
		19,17,33,
		14,19,33,
		14,33,29,
		7,14,29,
		7,29,32,
		35,33,11,
		32,35,11,
		32,11,12,
		7,32,12,
		11,6,37,
		37,38,11,
		6,5,39,
		39,37,6,
		5,10,40,
		40,39,5,
		10,11,38,
		38,40,10,
		38,37,4,
		4,3,38,
		37,39,1,
		1,4,37,
		39,40,2,
		2,1,39,
		40,38,3,
		3,2,40
	};

};

