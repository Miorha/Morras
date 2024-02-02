#include <windows.h>
#include <gl/gl.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "include/perlin-noise.hpp"

#define pix 0.01
#define WWIDTH 1024
#define WHEIGHT 256

FastNoiseLite noise;

float tex[][8][8][4]={//dirt with grass
{{{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}},
{{0,1,0,0},{0,1,0,0},{0.75,0.375,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0},{0,1,0,0}},
{{0,1,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0,1,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0,1,0,0}},
{{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0}},
{{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0}},
{{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0}},
{{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0}},
{{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0}}}
,//stone
{{{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0}},
{{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0}},
{{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0}},
{{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0}},
{{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0}},
{{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0}},
{{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0}},
{{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0},{0.5,0.5,0.5,0}}}
,//air
{{{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1}},
{{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1}},
{{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1}},
{{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1}},
{{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1}},
{{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1}},
{{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1}},
{{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1},{0,0,0,1}}}
,//dirt
{{{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0}},
{{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0}},
{{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0}},
{{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0}},
{{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0}},
{{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0}},
{{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0}},
{{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0}}}
};

float etex[][8][8][4]={//player upper
{{{1,0.875,0.875,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0}},
{{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{1,0.875,0.875,0}},
{{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0}},
{{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0}},
{{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{1,0.875,0.875,0}},
{{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{1,0.875,0.875,0}},
{{1,0.875,0.875,0},{1,0.875,0.875,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{1,0.875,0.875,0}},
{{1,0.875,0.875,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{0.75,0.375,0,0},{1,0.875,0.875,0},{1,0.875,0.875,0}}}
,//player lower
{{{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0}},
{{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0},{1,0.875,0.875,0}},
{{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}},
{{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}},
{{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}},
{{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}},
{{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}},
{{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0},{1,0,0,0}}}
};

class Block{
	private:
		int id,x,y;
	public:
		Block(int idb){
			id=idb;
		}Block(){
			id=2;
		}void draw(float stx,float sty){
			if(id!=2){
				glBegin(GL_POINTS);
				for(int i=0;i<8;++i){
					for(int j=0;j<8;++j){
						glColor4f(tex[id][i][j][0],tex[id][i][j][1],tex[id][i][j][2],tex[id][i][j][3]);
						glVertex2f(j*pix+stx,(7-i)*pix+sty); 
					}
				}glEnd();
			}
		}int getid(){
			return id;
		}
} world[WWIDTH][WHEIGHT];

class Player{
	public:
		int x=10,y=64;
		int xx=0,yy=0;
} player;

class Entity{
	private:
		int x,y,xx,yy;
		int type;
		//const char* name;
		float tex[8][8][4];
		Entity* next=NULL;
		//bool box[8][8];
		short nextplace;
	public:
		Entity(int xb,int yb,int xxb,int yyb,int typeb,Entity* nextb,/*bool boxb[8][8],*/short nextplaceb){
			x=xb;
			y=yb;
			xx=xxb;
			yy=yyb;
			type=typeb;
			for(int i=0;i<8;++i){
				for(int j=0;j<8;++j){
					for(int k=0;k<4;++k){
						tex[i][j][k]=etex[type][i][j][k];
					}
				}
			}
			/*for(int i=0;i<8;++i){
				for(int j=0;j<8;++j){
					box[i][j]=boxb[i][j];
				}
			} */
			nextplace=nextplaceb;
		}void draw(float stx,float sty){
			glBegin(GL_POINTS);
			for(int i=0;i<8;++i){
				for(int j=0;j<8;++j){
					glColor4f(etex[type][i][j][0],etex[type][i][j][1],etex[type][i][j][2],etex[type][i][j][3]);
					glVertex2f(j*pix+stx+xx*pix,(7-i)*pix+sty-yy*pix); 
				}
			}glEnd();
			/*if(next!=NULL){
				next->draw(stx+(nextplace%5-2)/pix,sty+(nextplace/5-2)/pix);
			}*/
		}int getx(){
			return x;
		}int gety(){
			return y;
		}void move(int dxx,int dyy){
			xx+=dxx;
			yy+=dyy;
			x+=xx/9;
			xx%=9;
			y+=yy/9;
			yy%=9;
		} 
};
std::vector<Entity> elist;

void worldgnr(int seed){
	noise.SetSeed(seed);
	srand(seed);
	noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
	for(int x=0;x<WWIDTH;++x){
		//basic ground generation
		int dirtheight=int(noise.GetNoise(float(x)*1.5f,0.4f)*10)+64;
		int stoneheight=dirtheight+rand()%3+3;
		for(int y=0;y<dirtheight;++y){
			world[x][y]=Block(2);
		}world[x][dirtheight]=Block(0);
		for(int y=dirtheight+1;y<stoneheight;++y){
			world[x][y]=Block(3);
		}for(int y=stoneheight;y<WHEIGHT;++y){
			world[x][y]=Block(1);
		}
	}
}

void setup(){
	srand(time(0));
	worldgnr(rand());
	Entity playerdown=Entity(10,74,0,0,1,NULL,short(0));
	Entity playerup=Entity(10,73,0,0,0,&playerdown,short(3));
	elist.push_back(playerup);
	elist.push_back(playerdown);
}

long long flick=0;

void GLmain(HWND hWnd,HDC hDC,HGLRC hRC){
	glClearColor(0.5f,1.0f,1.0f,0.0f);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
	
	glPointSize(5.0f);
	
	for(float i=-1;i<1;i+=pix*9){
		for(float j=-1;j<1;j+=pix*9){
			world[int((i+1)/pix/9)+player.x-6][int((j+1)/pix/9)+player.y-6].draw(i-player.xx*pix,0-j+player.yy*pix);
		}
	}
	
	for(std::vector<Entity>::iterator iter=elist.begin();iter<elist.end();iter++){
		iter->draw((iter->getx()-player.x)*pix*9-player.xx*pix,1-(iter->gety()-player.y)*pix*9+player.yy*pix);
	}
	
	for(float i=-1;i<1;i+=pix){
		for(float j=0;j<pix*9;j+=pix){
			glBegin(GL_POINTS);
			glColor3f(0,0,0);
			glVertex2f(i,j-1);
			glVertex2f(i,1-j);
			glVertex2f(j-1,i);
			glVertex2f(j-1+pix*9,i);
			glVertex2f(1-j,i);
			glEnd();
		}
	}
	
	if(GetKeyState('A') & 0x8000 && !(flick%30) && player.x>8){
		elist[0].move(-1,0);
		elist[1].move(-1,0);
		player.xx-=1;
	}if(GetKeyState('D') & 0x8000 && !(flick%30) && player.x<WWIDTH-8){
		elist[0].move(1,0);
		elist[1].move(1,0);
		player.xx+=1;
	}if(GetKeyState(VK_SPACE) & 0x8000 && !(flick%30) && player.y>8){
		elist[0].move(0,-1);
		elist[1].move(0,-1);
		player.yy-=1;
	}if(GetKeyState(VK_SHIFT) & 0x8000 && !(flick%30) && player.y<WHEIGHT-8){
		elist[0].move(0,1);
		elist[1].move(0,1);
		player.yy+=1;
	}player.x+=player.xx/9;
	player.xx%=9;
	player.y+=player.yy/9;
	player.yy%=9;
	
	++flick;
    SwapBuffers (hDC);
}

//dev-c++ works below
LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
WPARAM wParam, LPARAM lParam);
void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC);
void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC);


/**************************
 * WinMain
 *
 **************************/

int WINAPI WinMain (HINSTANCE hInstance,
                    HINSTANCE hPrevInstance,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASS wc;
    HWND hWnd;
    HDC hDC;
    HGLRC hRC;        
    MSG msg;
    BOOL bQuit = FALSE;
    float theta = 0.0f;

    /* register window class */
    wc.style = CS_OWNDC;
    wc.lpfnWndProc = WndProc;
    wc.cbClsExtra = 0;
    wc.cbWndExtra = 0;
    wc.hInstance = hInstance;
    wc.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wc.hCursor = LoadCursor (NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH) GetStockObject (BLACK_BRUSH);
    wc.lpszMenuName = NULL;
    wc.lpszClassName = "GLSample";
    RegisterClass (&wc);

    /* create main window */
    hWnd = CreateWindow (
      "GLSample", "Morras", 
      WS_CAPTION | WS_POPUPWINDOW | WS_VISIBLE,
      0, 0, 500, 500,
      NULL, NULL, hInstance, NULL);

    /* enable OpenGL for the window */
    EnableOpenGL (hWnd, &hDC, &hRC);
	
	setup();
	
    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage (&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage (&msg);
                DispatchMessage (&msg);
            }
        }
        else
        {
            GLmain(hWnd, hDC, hRC);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL (hWnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow (hWnd);

    return msg.wParam;
}


/********************
 * Window Procedure
 *
 ********************/

LRESULT CALLBACK WndProc (HWND hWnd, UINT message,
                          WPARAM wParam, LPARAM lParam)
{

    switch (message)
    {
    case WM_CREATE:
        return 0;
    case WM_CLOSE:
        PostQuitMessage (0);
        return 0;

    case WM_DESTROY:
        return 0;

    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
            return 0;
        }
        return 0;

    default:
        return DefWindowProc (hWnd, message, wParam, lParam);
    }
}


/*******************
 * Enable OpenGL
 *
 *******************/

void EnableOpenGL (HWND hWnd, HDC *hDC, HGLRC *hRC)
{
    PIXELFORMATDESCRIPTOR pfd;
    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC (hWnd);

    /* set the pixel format for the DC */
    ZeroMemory (&pfd, sizeof (pfd));
    pfd.nSize = sizeof (pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW | 
      PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;
    iFormat = ChoosePixelFormat (*hDC, &pfd);
    SetPixelFormat (*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext( *hDC );
    wglMakeCurrent( *hDC, *hRC );

}


/******************
 * Disable OpenGL
 *
 ******************/

void DisableOpenGL (HWND hWnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent (NULL, NULL);
    wglDeleteContext (hRC);
    ReleaseDC (hWnd, hDC);
}
