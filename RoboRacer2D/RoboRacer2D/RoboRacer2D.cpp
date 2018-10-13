// RoboRacer2D.cpp : Определяет точку входа для приложения.
//

#include "stdafx.h"
#include "RoboRacer2D.h"
#include "SOIL.h"
#include "Sprite.h"
#include "glut.h"
#include <gl\GL.h>
#include <gl\GLU.h>
#include "Input.h"

#define MAX_LOADSTRING 100

// Глобальные переменные:
HINSTANCE hInst;                                // текущий экземпляр
WCHAR szTitle[MAX_LOADSTRING];                  // Текст строки заголовка
WCHAR szWindowClass[MAX_LOADSTRING];            // имя класса главного окна
HDC hDC = NULL;
HGLRC hRC = NULL;
HWND hWnd = NULL;

bool fullscreen = false;
GLfloat screen_height;
GLfloat screen_width;

//Game variables
Sprite* robot_left;
Sprite* robot_right;
Sprite* robot_right_strip;
Sprite* robot_left_strip;
Sprite* background;
Sprite* player;
Input* inputManager;


// Отправить объявления функций, включенных в этот модуль кода:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

void ResizeGLScene(const GLsizei p_width, const GLsizei p_height)
{
	GLsizei h = p_height;
	GLsizei w = p_width;
	if (h == 0) h = 1;
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, w, h, 0, 0, 1);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

const bool InitGL()
{
	glEnable(GL_TEXTURE_2D);
	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f, 0.0f, 0.0f, 0.5f);
	glDisable(GL_DEPTH_TEST);
	return true;
}

const bool CreateGLWindow(const char* p_title, const int p_width, const int p_height, const int p_bits, const bool p_fullscreenflag)
{
	GLuint PixelFormat;
	WNDCLASS wc;
	DWORD dwExStyle;
	DWORD dwStyle;
	RECT WindowRect;
	WindowRect.left = (long)0;
	WindowRect.right = (long)p_width;
	WindowRect.top = (long)0;
	WindowRect.bottom = (long)p_height;
	fullscreen = p_fullscreenflag;
	screen_height = (GLfloat)p_height;
	screen_width = (GLfloat)p_width;
	hInst = GetModuleHandle(NULL);
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "OpenGL";
	if (!RegisterClass(&wc))
	{
		return false;
	}
	if (fullscreen)
	{
		DEVMODE dmScreenSettings;
		memset(&dmScreenSettings, 0, sizeof(dmScreenSettings));
		dmScreenSettings.dmSize = sizeof(dmScreenSettings);
		dmScreenSettings.dmPelsWidth = p_width;
		dmScreenSettings.dmPelsHeight = p_height;
		dmScreenSettings.dmBitsPerPel = p_bits;
		dmScreenSettings.dmFields = DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

		if (ChangeDisplaySettings(&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
		{
			fullscreen = false;
		}
	}
	if (fullscreen)
	{
		dwExStyle = WS_EX_APPWINDOW;
		dwStyle = WS_POPUP;
		ShowCursor(false);
	}
	else
	{
		dwExStyle = WS_EX_APPWINDOW | WS_EX_WINDOWEDGE;
		dwStyle = WS_OVERLAPPEDWINDOW;
	}
	AdjustWindowRectEx(&WindowRect, dwStyle, FALSE, dwExStyle);

	if (!(hWnd = CreateWindowEx(dwExStyle, 
								"OpenGL", 
								p_title, 
								dwStyle | 
								WS_CLIPSIBLINGS |
								WS_CLIPCHILDREN,
								0, 0,
								WindowRect.right - WindowRect.left,
								WindowRect.bottom - WindowRect.top,
								NULL,
								NULL,
								hInst,
								NULL)))
	{
		return false;
	}
	static	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW |
		PFD_SUPPORT_OPENGL |
		PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		p_bits,
		0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0,
		16, 0, 0,
		PFD_MAIN_PLANE,
		0, 0, 0, 0
	};
	if (!(hDC = GetDC(hWnd)))
	{
		return false;
	}
	if (!(PixelFormat = ChoosePixelFormat(hDC, &pfd)))
	{
		return false;
	}
	if (!SetPixelFormat(hDC, PixelFormat, &pfd))
	{
		return false;
	}
	if (!(hRC = wglCreateContext(hDC)))
	{
		return false;
	}
	if (!wglMakeCurrent(hDC, hRC))
	{
		return false;
	}
	ShowWindow(hWnd, SW_SHOW);
	SetForegroundWindow(hWnd);
	SetFocus(hWnd);
	ResizeGLScene(p_width, p_height);
	if (!InitGL())
	{
		return false;
	}
	return true;
}

const bool LoadTextures()
{
	background = new Sprite(1);
	background->SetFrameSize(1877.0f, 600.0f);
	background->SetNumberFrames(1);
	background->AddTexture("resources/background.png", false);

	robot_right = new Sprite(4);
	robot_right->SetFrameSize(100.0f, 125.0f);
	robot_right->SetNumberFrames(4);
	robot_right->SetPosition(0, screen_height - 130.0f);
	robot_right->AddTexture("resources/robot_right_00.png");
	robot_right->AddTexture("resources/robot_right_01.png");
	robot_right->AddTexture("resources/robot_right_02.png");
	robot_right->AddTexture("resources/robot_right_03.png");

	robot_left = new Sprite(4);
	robot_left->SetFrameSize(100.0f, 125.0f);
	robot_left->SetNumberFrames(4);
	robot_left->SetPosition(0, screen_height - 130.0f);
	robot_left->AddTexture("resources/robot_left_00.png");
	robot_left->AddTexture("resources/robot_left_01.png");
	robot_left->AddTexture("resources/robot_left_02.png");
	robot_left->AddTexture("resources/robot_left_03.png");

	robot_right_strip = new Sprite(4);
	robot_right_strip->SetFrameSize(125.0f, 100.0f);
	robot_right_strip->SetNumberFrames(4);
	robot_right_strip->SetPosition(0, screen_height - 130.0f);
	robot_right_strip->AddTexture("resources/robot_right_strip.png");

	robot_left_strip = new Sprite(4);
	robot_left_strip->SetFrameSize(125.0f, 100.0f);
	robot_left_strip->SetNumberFrames(4);
	robot_left_strip->SetPosition(0, screen_height - 130.0f);
	robot_left_strip->AddTexture("resources/robot_left_strip.png");

	background->IsVisible(true);
	background->IsActive(true);
	//background->SetVelocity(-25.0f);

	robot_right->IsVisible(true);
	robot_right->IsActive(true);
	robot_right->SetVelocity(50.0f);

	player = robot_right;
	player->IsVisible(true);
	player->IsActive(true);
	//player->SetVelocity(50.0f);

	return true;
}

void Render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();
	background->Render();
	robot_left->Render();
	robot_right->Render();
	robot_left_strip->Render();
	robot_right_strip->Render();
	SwapBuffers(hDC);
}

void StartGame()
{
	inputManager = new Input(hWnd);
	LoadTextures();
}

void ProcessInput(const float p_deltaTime)
{
	switch (inputManager->GetCommand())
	{
	case Input::Command::CM_STOP:
		player->SetVelocity(0.0f);
		background->SetVelocity(0.0f);
		break;
	case Input::Command::CM_LEFT:
		if (player == robot_right)
		{
			robot_right->IsActive(false);
			robot_right->IsVisible(false);
			robot_left->SetPosition(robot_right->GetPosition());
		}
		player = robot_left;
		player->IsActive(true);
		player->IsVisible(true);
		player->SetVelocity(-50.0f);
		background->SetVelocity(50.0f);
		break;
	case Input::Command::CM_RIGHT:
		if (player == robot_left)
		{
			robot_left->IsActive(false);
			robot_left->IsVisible(false);
			robot_right->SetPosition(robot_left->GetPosition());
		}
		player = robot_right;
		player->IsActive(true);
		player->IsVisible(true);
		player->SetVelocity(50.0f);
		background->SetVelocity(-50.0f);
		break;
	case Input::Command::CM_UP:
		player->Jump(Sprite::SpriteState::UP);
		break;
	case Input::Command::CM_DOWN:
		player->Jump(Sprite::SpriteState::DOWN);
		break;
	case Input::Command::CM_QUIT:
		PostQuitMessage(0);
		break;
	}
}

void Update(const float p_delta_time)
{
	inputManager->Update(p_delta_time);
	ProcessInput(p_delta_time);
	background->Update(p_delta_time);
	robot_left->Update(p_delta_time);
	robot_left_strip->Update(p_delta_time);
	robot_right->Update(p_delta_time);
	robot_right_strip->Update(p_delta_time);
}

void GameLoop(const float p_deltaTime )
{
	Update(p_deltaTime);
	Render();
}

void EndGame(){}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Разместите код здесь.

    // Инициализация глобальных строк
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_ROBORACER2D, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Выполнить инициализацию приложения:
	/*
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }
	*/
	//здесь своя инициализация окна
	if (!CreateGLWindow("RoboRacer 2D", 800, 600, 16, false))
	{
		return false;
	}

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ROBORACER2D));

    MSG msg;
	
	StartGame();
	int previousTime = glutGet(GLUT_ELAPSED_TIME);

	//Game Loop
	bool done = false;
	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
			{
				done = true;
			}
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			int currentTime = glutGet(GLUT_ELAPSED_TIME);
			float deltaTime = static_cast<float>(currentTime - previousTime) / 1000;
			previousTime = currentTime;
			GameLoop(deltaTime);
		}
	}
	EndGame();
	
    return (int) msg.wParam;
}



//
//  ФУНКЦИЯ: MyRegisterClass()
//
//  ЦЕЛЬ: Регистрирует класс окна.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ROBORACER2D));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_ROBORACER2D);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   ФУНКЦИЯ: InitInstance(HINSTANCE, int)
//
//   ЦЕЛЬ: Сохраняет маркер экземпляра и создает главное окно
//
//   КОММЕНТАРИИ:
//
//        В этой функции маркер экземпляра сохраняется в глобальной переменной, а также
//        создается и выводится главное окно программы.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Сохранить маркер экземпляра в глобальной переменной

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ФУНКЦИЯ: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  ЦЕЛЬ: Обрабатывает сообщения в главном окне.
//
//  WM_COMMAND  - обработать меню приложения
//  WM_PAINT    - Отрисовка главного окна
//  WM_DESTROY  - отправить сообщение о выходе и вернуться
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Разобрать выбор в меню:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Добавьте сюда любой код прорисовки, использующий HDC...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Обработчик сообщений для окна "О программе".
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
