#include "DDrawer.h"
#include "DTexture.h"
#include "DModel.h"
#include "DInterface.h"
#include "DLevel.h"
#include <math.h>

DDrawer::DDrawer(HWND hWnd, DInterface *pInterface, DLevel *pLevels)
{
	myhWnd = hWnd;
	hDC = GetDC(myhWnd);
	hRC = NULL;

	glTxtrEnable = false;
	

	m_pInterface = pInterface;
	m_pLevels = pLevels;

	pFontTxtr = 0;
	pBtnTxtr = 0;
	pMenuBackTxtr = 0;
	pAdMenuTxtr = 0;
	pBallTxtr = 0;
	pNewGameBtnTxtr = 0;
	pExitBtnTxtr = 0;
	pLockTxtr = 0;
	pChangeBtnTxtr = 0;
	pBallInfo1BtnTxtr = 0;
	pBallInfo2BtnTxtr = 0;
	pZoomInBtnTxtr = 0;
	pZoomOutBtnTxtr = 0;
}

DDrawer::~DDrawer(void)
{
	m_pInterface = 0;

	if(pFontTxtr)
		delete pFontTxtr;
	if(pBtnTxtr)
		delete pBtnTxtr;
	if(pMenuBackTxtr)
		delete pMenuBackTxtr;
	if(pAdMenuTxtr)
		delete pAdMenuTxtr;
	if(pBallTxtr)
		delete pBallTxtr;
	if(pNewGameBtnTxtr)
		delete pNewGameBtnTxtr;
	if(pExitBtnTxtr)
		delete pExitBtnTxtr;
	if(pLockTxtr)
		delete pLockTxtr;
	if(pChangeBtnTxtr)
		delete pChangeBtnTxtr;
	if(pBallInfo1BtnTxtr)
		delete pBallInfo1BtnTxtr;
	if(pBallInfo2BtnTxtr)
		delete pBallInfo2BtnTxtr;
	if (pZoomInBtnTxtr)
		delete pZoomInBtnTxtr;
	if (pZoomOutBtnTxtr)
		delete pZoomOutBtnTxtr;
}

void DDrawer::DrawColorQuadr(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4, float *color)
{
	glColor4f(color[0], color[1], color[2], color[3]);

	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);

	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();

	/*glBegin(GL_TRIANGLES);
	glVertex2f(x2, y2);
	glVertex2f(x3, y3);
	glVertex2f(x4, y4);
	glEnd();*/
}

void DDrawer::DrawColorRect(float x1, float x2, float y1, float y2, float z1, float z2, float *color)
{
	//настройка цвета
	glColor4f(color[0], color[1], color[2], color[3]);
	
	glBegin(GL_QUADS);

	//рисование вершин
	if(x1 == x2)
	{
		glVertex3f(x1, y1, z1);
		glVertex3f(x1, y2, z1);
		glVertex3f(x1, y2, z2);
		glVertex3f(x1, y1, z2);
	}
	if(y1 == y2)
	{
		glVertex3f(x1, y1, z1);
		glVertex3f(x1, y1, z2);
		glVertex3f(x2, y1, z2);
		glVertex3f(x2, y1, z1);
	}
	if(z1 == z2)
	{
		glVertex3f(x1, y1, z1);
		glVertex3f(x1, y2, z1);
		glVertex3f(x2, y2, z1);
		glVertex3f(x2, y1, z1);
	}

	glEnd();
}

void DDrawer::DrawColorRect(float x1, float x2, float y1, float y2, float *color)
{
	//DrawColorQuadr(x1, y1, x2, y1, x2, y2, x1, y2, color);
	glColor4f(color[0], color[1], color[2], color[3]);

	glBegin(GL_QUADS);
	glVertex2f(x1, y1);
	glVertex2f(x2, y1);
	glVertex2f(x2, y2);
	glVertex2f(x1, y2);
	glEnd();
}

void DDrawer::DrawTextureRect(float x1, float x2, float y1, float y2, float u1, float v1, float u2, float v2, DTexture *txtr, float bright)
{
	glEnable(GL_TEXTURE_2D);

	BindTexture(txtr);
	
	glColor4f(bright, bright, bright, 1.0f);

	//glColor4f(1.0f, 1.0f, 1.0f, alpha);

	glBegin(GL_QUADS);

	glTexCoord2f(u1, v1);
	glVertex2f(x1, y1);

	glTexCoord2f(u2, v1);
	glVertex2f(x2, y1);

	glTexCoord2f(u2, v2);
	glVertex2f(x2, y2);

	glTexCoord2f(u1, v2);
	glVertex2f(x1, y2);
	glEnd();
}

void DDrawer::InitGraphic()
{
	GLuint    iPixelFormat;			// Хранит результат после поиска
	// pfd сообщает Windows каким будет вывод на экран каждого пикселя
	static  PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),	// Размер дескриптора данного формата пикселей
		1,								// Номер версии
		PFD_DRAW_TO_WINDOW |			// Формат для Окна
		PFD_SUPPORT_OPENGL |			// Формат для OpenGL
		PFD_DOUBLEBUFFER,				// Формат для двойного буфера
		PFD_TYPE_RGBA,					// Требуется RGBA формат
		32,								// Выбирается бит глубины цвета
		0, 0, 0, 0, 0, 0,				// Игнорирование цветовых битов
		0,								// Нет буфера прозрачности
		0,								// Сдвиговый бит игнорируется
		0,								// Нет буфера накопления
		0, 0, 0, 0,						// Биты накопления игнорируются
		24,								// 24 битный Z-буфер (буфер глубины)
		8,								// 8bit буфера трафарета
		0,								// Нет вспомогательных буферов
		PFD_MAIN_PLANE,					// Главный слой рисования
		0,								// Зарезервировано
		0, 0, 0							// Маски слоя игнорируются
	};

	iPixelFormat = ChoosePixelFormat(hDC, &pfd);
	SetPixelFormat(hDC, iPixelFormat, &pfd);
	hRC = wglCreateContext(hDC);
	if(hRC)
		wglMakeCurrent(hDC, hRC);

	MakeTexture("data\\textures\\Button.tga", "BtnTxtr", pBtnTxtr, FILTER_NEAREST);
	MakeTexture("data\\textures\\Font.tga", "FontTxtr", pFontTxtr, FILTER_NEAREST);
	MakeTexture("data\\textures\\MenuBack.tga", "MenuBackTxtr", pMenuBackTxtr, FILTER_NEAREST);
	MakeTexture("data\\textures\\AdMenu.tga", "AdMenuTxtr", pAdMenuTxtr, FILTER_NEAREST);
	MakeTexture("data\\textures\\Ball.tga", "BallTxtr", pBallTxtr, FILTER_NEAREST);
	MakeTexture("data\\textures\\NewGameBtn.tga", "NewGameBtnTxtr", pNewGameBtnTxtr, FILTER_NEAREST);
	MakeTexture("data\\textures\\ExitBtn.tga", "ExitBtnTxtr", pExitBtnTxtr, FILTER_NEAREST);
	MakeTexture("data\\textures\\Lock.tga", "LockTxtr", pLockTxtr, FILTER_NEAREST);
	MakeTexture("data\\textures\\ChangeBtn.tga", "ChangeBtnTxtr", pChangeBtnTxtr, FILTER_NEAREST);
	MakeTexture("data\\textures\\Ball1Btn.tga", "BallInfo1BtnTxtr", pBallInfo1BtnTxtr, FILTER_NEAREST);
	MakeTexture("data\\textures\\Ball2Btn.tga", "BallInfo2BtnTxtr", pBallInfo2BtnTxtr, FILTER_NEAREST);
	MakeTexture("data\\textures\\ZoomInBtn.tga", "ZoomInBtnTxtr", pZoomInBtnTxtr, FILTER_NEAREST);
	MakeTexture("data\\textures\\ZoomOutBtn.tga", "ZoomOutBtnTxtr", pZoomOutBtnTxtr, FILTER_NEAREST);



	char fileName[256];
	char txtrName[256];
	DTexture *pTxtr = 0;
	int CreatedLevels = 2; //Количество уровней, которые готовы
	for(int i = 1; i <= CreatedLevels; i++)
	{
		sprintf(fileName, "data\\textures\\%dF.tga", i);
		sprintf(txtrName, "Lvl%dFTxtr", i-1);
		pTxtr = 0;
		MakeTexture( fileName, txtrName, pTxtr, FILTER_NEAREST);
		m_pLevels[i-1].SetFTextr(pTxtr);
	}

	for(int i = 0; i < BT_SIZE; i++)
	{
		//Настройка текстур для кнопок
		// а вот хрен вам. всё настраивается при рисовании каждой кнопки. однако почему - ?
	}

	glEnableClientState( GL_VERTEX_ARRAY );
	glEnableClientState( GL_TEXTURE_COORD_ARRAY );
	glEnableClientState( GL_NORMAL_ARRAY );
	glEnable(GL_BLEND);
	glEnable(GL_ALPHA_TEST);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	
}
void DDrawer::DrawScene()
{
	//glClear( GL_COLOR_BUFFER_BIT );
	//glClearColor( 1.0, 1.0, 1.0, 1.0 );

	RECT rc;
	GetClientRect(myhWnd, &rc);

	glMatrixMode( GL_PROJECTION );
		glLoadIdentity(); 
		glOrtho(rc.left, rc.right, rc.bottom, rc.top, -1, 1);

	//рисование карты

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glDisable( GL_DEPTH_TEST );
	glDepthMask( false );

	

	if( m_pInterface->GetSlcScreen() == SCR_MAINMENU)
		DrawMainMenu();
	if( m_pInterface->GetSlcScreen() == SCR_EX_SELECT )
		DrawExSelectMenu();
	if( m_pInterface->GetSlcScreen() == SCR_EX_DESCRIBE )
		DrawExDescribeMenu();
	

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glDisable( GL_DEPTH_TEST );
	glDepthMask( false );
	char text[256];
	//sprintf(text, "slcBtn: %d", m_pInterface->GetSlcBtn()->GetType());
	//DrawText( 500, 10, text);
	/*sprintf(text, "tg(a2): %f", tan( m_pLevels[0].GetPhysObject(1)->Get_alpha() ));
	DrawText( 500, 50, text);
	sprintf(text, "Время: %d", m_pLevels[m_pInterface->GetSlcLevel()].GetTime());
	DrawText( 500, 50, text);
*/
	SwapBuffers(hDC);
}

void DDrawer::DrawObject(DModel *pModel,float x,float y,float z)
{
	glPushMatrix();
	glTranslatef(x, y, z);
	static float angle = 0;
	//glRotatef( angle++, 0, 1, 0 );
	DrawModel(pModel);
	glPopMatrix();
}
void DDrawer::DrawModel( DModel * pModel )
{
	if(!pModel) return;

	glVertexPointer( 3, GL_FLOAT, sizeof(pModel->Vertex[0]), &(pModel->Vertex[0].x) );
	glNormalPointer( GL_FLOAT, sizeof(pModel->Vertex[0]), &(pModel->Vertex[0].nx) );
	glTexCoordPointer( 2, GL_FLOAT, sizeof(pModel->Vertex[0]), &(pModel->Vertex[0].tu) );

	glDrawArrays( GL_TRIANGLES, 0, pModel->VertexCount );
}

// Загружает модель формата *.smd
int	DDrawer::LoadModel( const char* filename, const char* name, DModel** newModel )
{
	if( (*newModel) )
	{
		delete (*newModel);
		*newModel = 0;
	}

	(*newModel) = new DModel();

	FILE *pfile = fopen( filename, "rt" );

	if( pfile )
	{
		// По началу будем игнорировать все блоки файла, кроме того, где хранится информация
		// о самой геометрии
		char buffer[1024];
		DVertex	read_vertex;
		int bone_id, bone_id2;
		std::vector< DVertex > list_vertex;

		while( fgets( buffer, 1024, pfile ) )
		{
			// Нашли блок 'triangles'
			if( strstr( buffer, "triangles" ) )
			{
				while( fgets(buffer, 1024, pfile) )
				{
					if( strstr( buffer, "end" ) )
					{
						(*newModel)->VertexCount = list_vertex.size();
						(*newModel)->Vertex = new DVertex[ list_vertex.size() ];
						for( int t = 0; t < (*newModel)->VertexCount; t++ )
						{
							(*newModel)->Vertex[t] = list_vertex[t];
							(*newModel)->Vertex[t].tv = 1 - (*newModel)->Vertex[t].tv;

							float rad_quad = (list_vertex[t].x*list_vertex[t].x + list_vertex[t].y*list_vertex[t].y);
							if( (*newModel)->Radius < rad_quad ) (*newModel)->Radius = rad_quad; 
	
						}
						(*newModel)->Radius = sqrt( (*newModel)->Radius );
						break;
					}
				// Формат вершины:
				// ? \ Х \ Y \ Z \ NX \ NY \ NZ \ U \ V \ bone?
				// Загрузить сразу 3 вершины 
				fscanf( pfile, "%d %f %f %f %f %f %f %f %f %d",
					&bone_id, 
					&read_vertex.x, &read_vertex.y, &read_vertex.z, 
					&read_vertex.nx, &read_vertex.ny, &read_vertex.nz, 
					&read_vertex.tu, &read_vertex.tv, &bone_id2 );
				list_vertex.push_back( read_vertex );

				fscanf( pfile, "%d %f %f %f %f %f %f %f %f %d",
					&bone_id, 
					&read_vertex.x, &read_vertex.y, &read_vertex.z, 
					&read_vertex.nx, &read_vertex.ny, &read_vertex.nz, 
					&read_vertex.tu, &read_vertex.tv, &bone_id2 );
				list_vertex.push_back( read_vertex );

				fscanf( pfile, "%d %f %f %f %f %f %f %f %f %d",
					&bone_id, 
					&read_vertex.x, &read_vertex.y, &read_vertex.z, 
					&read_vertex.nx, &read_vertex.ny, &read_vertex.nz, 
					&read_vertex.tu, &read_vertex.tv, &bone_id2 );
				list_vertex.push_back( read_vertex );
				}
			}
		}

		fclose( pfile );
	}

	return 1;
}

int	DDrawer::LoadModelAnimation( const char* filename, const char* anim_name, DModel ** )
{
	return 1;
}

int	DDrawer::DeleteModel( DModel** pModel )
{
	delete (*pModel);
	pModel = 0;
	return 1;
}
void DDrawer::DrawText( int x, int y, const char *strText, float size, float* color, int rect_width )
{
	glEnable(GL_TEXTURE_2D);
	//TextOut( hDC, x, y, str, strlen(str) );
    int iLength		= strlen( strText );
    float	cursorX	= x, 
		cursorY = y;
    float tx, ty;
	unsigned char out_char = 0;
	float	last_space_index = cursorX;
	int next_space_index = 0;


    if(!iLength)
		return;

	BindTexture( pFontTxtr );

	glBegin( GL_QUADS );
    for(int i=0; i<iLength; i++ )
    {
		//todo: добавить перенос по словам
		next_space_index = index_first_char_in_string( strText + i, ' ' );//strchr( strText + i, ' ' ) - strText - i + 1;
		if( next_space_index == -1 )
			next_space_index = index_first_char_in_string( strText + i, '\n' );

		if( rect_width>0 && next_space_index*size+cursorX > rect_width )
		{
			cursorY += size;
            cursorX = x;
		}
        if( strText[i] == '\n') //|| (rect_width>0 && cursorX > rect_width) )
        {
			cursorY += size;
            cursorX = x;
            continue;
        }else
        if( strText[i] == ' ' )
        {
			cursorX += size;
			last_space_index = cursorX;
            continue;
        }else
        if( strText[i] == '\t')
        {
			cursorX += size*6;
            continue;
        }

		if( strText[i] == '^' && i+1<iLength ) 
		{
			int ascii = (int)strText[i+1];
			glColor4f( (float)(ascii&4), (float)(ascii&2), (float)(ascii&1), 1.0f );
			i++;
			continue;
		}
		else
		{
			if(!color)
				glColor4f(0.0f, 0.0f, 0.0f, 1.0f);
			else glColor4f(color[0], color[1], color[2], color[3]);
			// Для выводы русских символолв
			out_char = strText[i];
			if( strText[i] < 0 ) out_char += 256;

			tx = float(out_char%16)/16.0f;
			ty = float(out_char/16)/16.0f;

			glTexCoord2f( tx, ty );
			glVertex2f( cursorX, cursorY);

			glTexCoord2f( tx+0.0625f, ty  );
			glVertex2f( cursorX+size, cursorY);

			glTexCoord2f( tx+0.0625f, ty+0.0625f  );
			glVertex2f( cursorX+size, cursorY+size);

			glTexCoord2f( tx, ty+0.0625f  );
			glVertex2f( cursorX, cursorY+size);
	
			cursorX += size;
		}
       }
       glEnd();
}

int DDrawer::index_first_char_in_string( const char* str, const char chr )
{
	int i = 0;
	while( str[i] )
	{
		if( str[i] == chr )
			return i;
		i++;
	}
	return -1;
}

void DDrawer::BindTexture( DTexture* ptex )
{
	if(ptex)
		glBindTexture( GL_TEXTURE_2D, ptex->glTexture );
	else
		glBindTexture( GL_TEXTURE_2D, 0 );
}

DTexture* DDrawer::CreateTexture( const char *name, unsigned int filter )
{
	DTexture *texture = new DTexture();
	texture->Filter = filter;
	strncpy( texture->Name, name, 32 );
	return texture;
}

int DDrawer::LoadTexture( const char *filename, DTexture** ptex )
{
	FILE			*pFile = NULL;
	unsigned char	*pData = 0;
	int				fWidth = 0,
					fHeight = 0;
	unsigned char	BitPerPixel = 0;
	unsigned char	iBPP = 0;
	//TGA file
	unsigned char	byteHeader[12];
	unsigned char	bheader[6];

	pFile = fopen( filename, "rb" );

	if(pFile == NULL)
	{
		char error[64];
		sprintf(error, "Файл %s не найден.", filename);
		MessageBox(NULL, LPCWSTR( error), LPCWSTR("Ошибка!"), MB_OK);
		return -1;
	}

	fread( byteHeader, 1, 12, pFile );
	fread( bheader, 1, 6, pFile );

	fWidth			= bheader[1] * 256 + bheader[0];
	fHeight			= bheader[3] * 256 + bheader[2];
	BitPerPixel		= bheader[4];
	iBPP			= BitPerPixel/8;

	if( byteHeader[2] == 2 )
	{

		pData = new unsigned char[fWidth*fHeight*iBPP];

		//TGA BGRA -> RGBA
		unsigned char dataTemp = 0;

		for(int i = fHeight-1; i > -1; i--)
		for(int t = 0; t< fWidth; t++)
		{
			int iIndex = (t+i*fWidth)*iBPP;

			dataTemp = fgetc(pFile);//B
			pData[ iIndex + 1] = fgetc(pFile);//G
			pData[ iIndex + 0] = fgetc(pFile);//R
			pData[ iIndex + 2] = dataTemp;

			if(BitPerPixel == 32)
				pData[ iIndex + 3] = fgetc(pFile);//A

		}

	}else
	if( byteHeader[2] == 10 )
	{
		pData = new unsigned char[fWidth*fHeight*iBPP];
		unsigned int pixelcount = fWidth*fHeight;
		unsigned int currentpixel = 0;
		unsigned int currentbyte = 0;
		unsigned char* colorbuffer =  new unsigned char[iBPP];

		do
		{
			unsigned char chunk=0;
			fread( &chunk, 1, 1, pFile );

			if(chunk < 128)
			{
				chunk++;

				for(int counter = 0; counter < chunk; counter++)
				{
					if(fread(colorbuffer, 1, iBPP, pFile) != iBPP)
					{
						MessageBox(NULL, LPCWSTR("Error in: load compressed TGA!(1)\nRAW chunk"), LPCWSTR("Error!"), MB_OK);
						return false;
					}

					pData[ currentbyte ] = colorbuffer[2];
					pData[ currentbyte + 1 ] = colorbuffer[1];
					pData[ currentbyte + 2 ] = colorbuffer[0];

					if(iBPP == 4)
						pData[ currentbyte + 3 ] = colorbuffer[3];

					currentbyte += iBPP;
					currentpixel++;

				}
			}else
			{
				chunk -= 127;

				if(fread( colorbuffer, 1, iBPP, pFile ) != iBPP)
				{
					MessageBox(NULL, LPCWSTR("Error in: load compressed TGA!(2)\nRLE chunk"), LPCWSTR("Error!"), MB_OK);
					return false;
				}

				for(int counter = 0; counter < chunk; counter++)
				{
					pData[ currentbyte ] = colorbuffer[2];
					pData[ currentbyte + 1 ] = colorbuffer[1];
					pData[ currentbyte + 2 ] = colorbuffer[0];
					if(iBPP == 4)
						pData[ currentbyte + 3 ] = colorbuffer[3];
					currentbyte += iBPP;
					currentpixel++;
				}
			}
		}while( currentpixel < pixelcount );

		unsigned char r,g,b,a;
		unsigned char* tempData = pData;
		pData = new unsigned char[ fWidth*fHeight*iBPP ];
		for( int y=0; y< fHeight; y++ )
		for( int x=0; x< fWidth; x++ )
		{
			r = tempData[ ( x + (fHeight-y-1)*fWidth)*iBPP ];
			g = tempData[ ( x + (fHeight-y-1)*fWidth)*iBPP+1 ];
			b = tempData[ ( x + (fHeight-y-1)*fWidth)*iBPP+2 ];

			if(iBPP==4)
			{
				a = tempData[ ( x + (fHeight-y-1)*fWidth)*iBPP+3 ];
				pData[ (x+y*fWidth)*iBPP + 3 ] = a;
			}
			pData[ (x+y*fWidth)*iBPP  ] = r;
			pData[ (x+y*fWidth)*iBPP+1 ] = g;
			pData[ (x+y*fWidth)*iBPP+2 ] = b;
		}
		delete[] tempData;

		free(colorbuffer);
	}else
	{
		MessageBox(NULL, LPCWSTR("Error in: not TGA data!"), LPCWSTR("Error!"), MB_OK);
		return -1;
	}

	fclose( pFile );

	//delete[] pData;

	(*ptex)->Width	= fWidth;
	(*ptex)->Height = fHeight;
	(*ptex)->bpp	= iBPP;
	(*ptex)->Data	= pData;
	strncpy( (*ptex)->FileName, filename, 32 );

	return true;
}

int DDrawer::GraphicsLoadTexture( DTexture** ptex )
{
	GLuint texture;

	glGenTextures( 1, &texture );

	glBindTexture( GL_TEXTURE_2D, texture );
	glTexEnvf( GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE );

	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexImage2D( GL_TEXTURE_2D, 0, (*ptex)->bpp, (*ptex)->Width, (*ptex)->Height, 0, ((*ptex)->bpp == 4)?GL_RGBA:GL_RGB, GL_UNSIGNED_BYTE, (*ptex)->Data );

	if( (*ptex)->Filter == FILTER_LINEAR )
	{
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
	}else
	if( (*ptex)->Filter == FILTER_NEAREST )
	{	
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
		glTexParameterf( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
	}

	(*ptex)->glTexture = texture;
	return texture;
}

void DDrawer::MakeTexture( const char *filename, const char* name, DTexture *&texture, unsigned int filter )
{
	texture = CreateTexture( name, filter );
	LoadTexture( filename, &texture );
	GraphicsLoadTexture( &texture ); 
}

void DDrawer::DrawButton(DButton *pBtn)
{
	if(!pBtn) return;
	if(!pBtn->GetVisibleStatus()) return;

	DTexture * pBtnTxtr;

	//DrawTextureRect(pBtn->GetX(), pBtn->GetX()+pBtn->GetWidth(), pBtn->GetY(), pBtn->GetY()+pBtn->GetHeight(), 0.0f, pBtn->GetActivateStatus()*0.5f, 1.0f, pBtn->GetActivateStatus()*0.5f + 0.5f, pBtnTxtr);
	if(pBtn->GetType() == BT_NEW)
		pBtnTxtr = pNewGameBtnTxtr;
	if(pBtn->GetType() == BT_EXIT)
		pBtnTxtr = pExitBtnTxtr;
	if(pBtn->GetType() >= BT_START_LVL1CHANGE_BTNS && pBtn->GetType() <= BT_END_LVL1CHANGE_BTNS)
		pBtnTxtr = pChangeBtnTxtr;
	if(pBtn->GetType() == BT_SHOWINFO_BALL1)
		pBtnTxtr = pBallInfo1BtnTxtr;
	if(pBtn->GetType() == BT_SHOWINFO_BALL2)
		pBtnTxtr = pBallInfo2BtnTxtr;
	if (pBtn->GetType() == BT_ZOOMIN)
		pBtnTxtr = pZoomInBtnTxtr;
	if (pBtn->GetType() == BT_ZOOMOUT)
		pBtnTxtr = pZoomOutBtnTxtr;

	
	if (pBtn->GetType() >= BT_START_LVL1CHANGE_BTNS && pBtn->GetType() <= BT_END_LVL1CHANGE_BTNS
		&& pBtn->GetEnableStatus() == false )
		DrawTextureRect(pBtn->GetX(), pBtn->GetX() + pBtn->GetWidth(), pBtn->GetY(), pBtn->GetY() + pBtn->GetHeight(), 0.0f, 0.0f, 1.0f, 1.0f, pBtnTxtr, 0.5f);
	else DrawTextureRect(pBtn->GetX(), pBtn->GetX()+pBtn->GetWidth(), pBtn->GetY(), pBtn->GetY()+pBtn->GetHeight(), 0.0f, 0.0f, 1.0f, 1.0f, pBtnTxtr);
	

	int size = 16;
	float color[4];
	if(pBtn->GetEnableStatus())
		memcpy(color, C_COLOR_BLACK, sizeof(color));
	else memcpy(color, C_COLOR_GRAY, sizeof(color));

	if(m_pInterface->GetSlcBtn() == pBtn)
		memcpy(color, C_COLOR_VIOLET, sizeof(color));

	//Следующие две строчки вызывают баги. Почему?
//	if (pBtn->GetText())
	//DrawText(pBtn->GetX()+(pBtn->GetWidth()-strlen(pBtn->GetText())*size)*0.5, pBtn->GetY()+(pBtn->GetHeight()-size)*0.5, pBtn->GetText(), size, color); 
	
}

void DDrawer::DrawButton(DButton *pBtn, DTexture * pTxtr, float bright)
{
	if (!pBtn) return;
	if (!pBtn->GetVisibleStatus()) return;

	DrawTextureRect(pBtn->GetX(), pBtn->GetX() + pBtn->GetWidth(), pBtn->GetY(), pBtn->GetY() + pBtn->GetHeight(), 0.0f, 0.0f, 1.0f, 1.0f, pTxtr, bright);
}

void DDrawer::DrawMainMenu()
{
	//Установка параметров
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glDisable( GL_DEPTH_TEST );
	glDepthMask( false );

	//Отрисовка фона
	float w = GetSystemMetrics(SM_CXSCREEN);
	float h = GetSystemMetrics(SM_CYSCREEN);
	DrawTextureRect(0, w, 0, h, 0.0f, 0.0f, 1.0f, 0.75f, pMenuBackTxtr);

	//Отрисовка различных изображений

	//Отрисовка кнопок
	for (int i = BT_START_MENU_BTNS; i <= BT_END_MENU_BTNS; i++)
		DrawButton(m_pInterface->GetButton(i));
}

void DDrawer::DrawExSelectMenu()
{
	//Установка параметров
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
	glDisable( GL_DEPTH_TEST );
	glDepthMask( false );

	//Отрисовка фона
	float w = GetSystemMetrics(SM_CXSCREEN);
	float h = GetSystemMetrics(SM_CYSCREEN);
	DrawTextureRect(0, w, 0, h, 0.0f, 0.0f, 1.0f, 0.75f, pMenuBackTxtr);


	int leftLevel = 0; //уровень, информация о котором рисуется левее всех остальных
	int numOfLevels = m_pLevels->GetNumOfLevels();
	int slcLevel = m_pInterface->GetSlcLevel();
	if(slcLevel == 0)
		leftLevel = 0;
	else if(slcLevel == numOfLevels-1)
		leftLevel = slcLevel - 2;
	else 
		leftLevel = slcLevel - 1;

	int scrWidth = GetSystemMetrics(SM_CXSCREEN);
	int scrHeight = GetSystemMetrics(SM_CYSCREEN);
	int horizSixteenth = scrWidth / 16;
	int vertSixth = scrHeight/6;
	int k = 0;
	int x = 0;
	DTexture *pTxtr = 0;

	float textColor[4];

	for(int i = leftLevel; i < leftLevel+3; i++)
	{
		if(i >= 0 && i < numOfLevels)
		{
			if (m_pLevels[i].GetFTextr())
			//if(i == 0)
				pTxtr = m_pLevels[i].GetFTextr();
			else pTxtr = pLockTxtr;
			x = horizSixteenth * (1 + 5*k);
			DrawTextureRect(x, x+horizSixteenth*4, vertSixth, vertSixth*3, 0.0f, 0.0f, 1.0f, 1.0f, pTxtr);
		
			memcpy( textColor, C_COLOR_ORANGE, sizeof(textColor));
			DrawText(x, vertSixth*3 + 10, m_pLevels[i].GetExSelectText(), 16, textColor, x+horizSixteenth*4);
			k++;
		}
	}



}

void DDrawer::DrawExDescribeMenu()
{
	switch (m_pInterface->GetSlcLevel())
	{
	case 0: //Уровень "Бильярдные шары"
		DrawMechLevel();
		break;
	case 1: //Уровень "Дифракционная решётка"
		DrawDifrLevel();
		break;
	default:
		break;
	}
}

void DDrawer::DrawMechLevel()
{
	//Отрисовка фона
	float w = GetSystemMetrics(SM_CXSCREEN);
	float h = GetSystemMetrics(SM_CYSCREEN);
	/*DrawTextureRect(w/3, w, 0, h, 0.0f, 0.0f, 1.0f, 1.0f, pAdMenuTxtr);*/
	glClear(GL_COLOR_BUFFER_BIT);
	//Фоновый цвет в зависимости от уровня
	glClearColor(0.75f, 0.75f, 0.75f, 1.0f);

	//Меню характеристик
	//Характеристики
	char text[256];
	sprintf(text, "Дано:");
	int textX = 30;
	int textY = 60;
	DrawText(20, textY, text, 36);

	textY += 100;


	DLevel * pSlcLevel = &m_pLevels[m_pInterface->GetSlcLevel()];
	DButton * pBtn = 0;
	int btnNumb;
	for (int i = 0; i < pSlcLevel->GetNumOfObjects(); i++)
	{
		/*sprintf(text, pSlcLevel->GetPhysObject(i)->GetName());
		DrawText( textX, textY, text, 24);*/

		if (i == 0)
			pBtn = m_pInterface->GetButton(BT_SHOWINFO_BALL1);
		if (i == 1)
			pBtn = m_pInterface->GetButton(BT_SHOWINFO_BALL2);

		pBtn->SetY(textY);
		DrawButton(pBtn);

		if (!pBtn->GetActivateStatus())
		{
			textY += 100;
			continue;
		}

		btnNumb = 0;

		textY += 50;
		char * izm = 0;
		for (int j = OBATT_ENUM_START; j < 3; j++)
		{
			/*if (pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName() == "v")
				sprintf(izm, "a");
			else if (pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName() == "m")
				sprintf(izm, "d");
			else if (pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName() == "angle")
				sprintf(izm, "e");

			sprintf(text, "%s:%4.0f %s", pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName(),
				pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetValue(), izm);
			*/

			if (pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName() == "v")
				sprintf(text, "%s:%4.0f м/с", pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName(),
				pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetValue());
			else if (pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName() == "m")
				sprintf(text, "%s:%4.0f кг", pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName(),
				pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetValue());
			else if (pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName() == "angle")
				sprintf(text, "%s:%4.0f ", pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName(),
				pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetValue());
			//sprintf(text, "%s:%4.0f", pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName(),
				//pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetValue());

			DrawText(textX, textY, text, 24);
			m_pInterface->GetButton(BT_START_LVL1CHANGE_BTNS + (i * 3) + btnNumb)->SetY(textY);
			DrawButton(m_pInterface->GetButton(BT_START_LVL1CHANGE_BTNS + (i * 3) + btnNumb));
			btnNumb++;
			textY += 50;
		}

		textY += 100;
	}
	pBtn = 0;

	//textY = 60;
	//textX = 250;

	sprintf(text, "Найти:");
	DrawText(textX, textY, text, 36);
	textY += 100;

	for (int i = 0; i < pSlcLevel->GetNumOfObjects(); i++)
	{
		if (!pSlcLevel->GetPhysObject(i))
			break;

		sprintf(text, pSlcLevel->GetPhysObject(i)->GetName());
		DrawText(textX, textY, text, 24);
		textY += 50;

		if (pSlcLevel->GetPhysObject(i)->Get_speed() == pSlcLevel->GetPhysObject(i)->Get_speed1())
			sprintf(text, "v`:? м/с");
		else
			sprintf(text, "v`:%3.2f м/с", pSlcLevel->GetPhysObject(i)->GetAttrib(OBATT_SPEED2)->GetValue());
		DrawText(textX, textY, text, 24);
		textY += 100;
	}

	//Рамка выплывающего меню
	DrawTextureRect(0, w / 3, 0, h, 0.0f, 0.0f, 1.0f, 1.0f, pAdMenuTxtr);

	//Траектории
	int t = 0;
	float x1, y1, x2, y2, w1, w2;
	w1 = pSlcLevel->GetPhysObject(0)->Get_width();
	w2 = pSlcLevel->GetPhysObject(1)->Get_width();
	while (true)
	{
		if (t == 0)
		{
			x1 = pSlcLevel->GetPhysObject(0)->Get_x0();
			x2 = pSlcLevel->GetPhysObject(1)->Get_x0();
			y1 = pSlcLevel->GetPhysObject(0)->Get_y0();
			y2 = pSlcLevel->GetPhysObject(1)->Get_y0();
		}
		else
		{
			x1 += pSlcLevel->GetPhysObject(0)->Get_speed1()->x;
			x2 += pSlcLevel->GetPhysObject(1)->Get_speed1()->x;
			y1 += pSlcLevel->GetPhysObject(0)->Get_speed1()->y;
			y2 += pSlcLevel->GetPhysObject(1)->Get_speed1()->y;
		}

		if ((x1 > w) || (x1 < -w)
			|| (x2 > w) || (x2 < -w)
			|| (y1 > h) || (y1 < -h)
			|| (y2 > h) || (y2 < -h))
			break;

		t++;
	}

	//sprintf(text, "%d     %d", &x1)
	
	//Обьекты
	int x = 0;
	int y = 0;
	int width = 0;
	int height = 0;
	int coordSysX = pSlcLevel->GetCoordSysX();
	int coordSysY = pSlcLevel->GetCoordSysY();

	for (int i = 0; i < pSlcLevel->GetNumOfObjects(); i++)
	{
		if (!pSlcLevel->GetPhysObject(i))
			break;

		x = pSlcLevel->GetPhysObject(i)->Get_x() * pSlcLevel->GetScale();
		y = pSlcLevel->GetPhysObject(i)->Get_y() * pSlcLevel->GetScale();
		width = pSlcLevel->GetPhysObject(i)->Get_width() * pSlcLevel->GetScale();
		height = pSlcLevel->GetPhysObject(i)->Get_height() * pSlcLevel->GetScale();

		DrawTextureRect(x + coordSysX, x + coordSysX + width, coordSysY - y, coordSysY - y + height,
			0.0f, 0.0f, 1.0f, 1.0f, pBallTxtr);
	}

	float color[4];
	memcpy(color, C_COLOR_RED, sizeof(color));
	if (pSlcLevel->GetPhysObject(0)->GetAttrib(OBATT_SPEED2)->GetValue() == -1)
	{
		sprintf(text, "Сумма углов направлений после столкновения не должна превышать 180");
		DrawText(w / 2, h / 3, text, 24, color, 5*w/6);
	}
	if (pSlcLevel->GetPhysObject(0)->GetAttrib(OBATT_SPEED2)->GetValue() == -2)
	{
		sprintf(text, "Сумма углов направлений после столкновения равная 180 возможна лишь когда m1*v1 = - m2*v2");
		DrawText(w / 2, h / 3, text, 24, color, 5 * w / 6);
	}

	//Рамка окна показа
	DrawTextureRect(w / 3, w, 0, h, 0.0f, 0.0f, 1.0f, 1.0f, pAdMenuTxtr);

	//Кнопки зума (приближение/отдаление)
	DrawButton(m_pInterface->GetButton(BT_ZOOMIN));
	DrawButton(m_pInterface->GetButton(BT_ZOOMOUT));
}

void DDrawer::DrawDifrLevel()
{
	//Отрисовка фона
	float w = GetSystemMetrics(SM_CXSCREEN);
	float h = GetSystemMetrics(SM_CYSCREEN);
	/*DrawTextureRect(w/3, w, 0, h, 0.0f, 0.0f, 1.0f, 1.0f, pAdMenuTxtr);*/
	glClear(GL_COLOR_BUFFER_BIT);
	//Фоновый цвет в зависимости от уровня
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	//Меню характеристик
	//Характеристики
	char text[256];
	sprintf(text, "Дано:");
	int textX = 30;
	int textY = 60;
	float clr[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
	DrawText(20, textY, text, 36, &clr[0]);
	textY += 100;

	DLevel * pSlcLevel = &m_pLevels[m_pInterface->GetSlcLevel()];
	DButton * pBtn = 0;
	int btnNumb;
	for (int i = 0; i < pSlcLevel->GetNumOfObjects(); i++)
	{
		DrawText(textX, textY, pSlcLevel->GetPhysObject(i)->GetName(), 24, &clr[0], w/3-textX*2);
		
		btnNumb = 0;
		
		textY += 50;

		for (int j = 0; j < 2; j++)
		{
			if (!pSlcLevel->GetPhysObject(i)->GetAttrib(j)) continue;

			DrawAttrib(pSlcLevel->GetPhysObject(i)->GetAttrib(j), textX, textY, w / 3 - textX*2, 24, &clr[0]);
			/*if (pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName() == "d")
				sprintf(text, "%s:%4.0f мкм", pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName(),
				pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetValue());
			if (pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName() == "lamb")
				sprintf(text, "%s:%4.0f нм", pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName(),
				pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetValue());
			if (pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName() == "k")
				sprintf(text, "%s:%4.0f", pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName(),
				pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetValue());
			if (pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName() == "angle")
				sprintf(text, "%s:%4.0f", pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName(),
				pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetValue());
			*/
			/*sprintf(text, "%s:%4.0f", pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetName(),
				pSlcLevel->GetPhysObject(i)->GetAttrib(j)->GetValue());*/

			//DrawText(textX, textY, text, 24, &clr[0]);
			/*m_pInterface->GetButton(BT_START_LVL1CHANGE_BTNS + (i * 3) + btnNumb)->SetY(textY);
			DrawButton(m_pInterface->GetButton(BT_START_LVL1CHANGE_BTNS + (i * 3) + btnNumb));
			btnNumb++;*/
			textY += 50;
		}
		
		textY += 75;
	}

	sprintf(text, "Найти:");
	DrawText(textX, textY, text, 36, &clr[0]);
	textY += 100;

	sprintf(text, "%s:%4.4f", pSlcLevel->GetPhysObject(1)->GetAttrib(2)->GetName(),
		pSlcLevel->GetPhysObject(1)->GetAttrib(2)->GetValue());

	DrawText(textX, textY, text, 24, &clr[0]);
	
	//Рамка выплывающего меню
	DrawTextureRect(0, w / 3, 0, h, 0.0f, 0.0f, 1.0f, 1.0f, pAdMenuTxtr);


	//Отрисовка всех элементов
	glDisable(GL_TEXTURE_2D);

	//Дифракционная решётка
	//float N = 50;// 1000 / pSlcLevel->GetPhysObject(0)->GetAttrib(0)->GetValue();
	float N = 1000 / pSlcLevel->GetPhysObject(0)->GetAttrib(0)->GetValue();
	float summH = 2 * h / 3;
	float H = summH / N;
	//float aH = H * 5 / 6;
	//float bH = H - aH; 
	float bH = summH / 50 / 6;
	float aH = H - bH;
	float clrBlack[4];

	float centrY = h / 2 - bH / 2;
	memcpy(clrBlack, C_COLOR_GRAY, sizeof(clrBlack));

	for (int i = 0; i < N / 2; i++)
	{
		DrawColorRect(w / 3 + w / 15, w / 3 + w / 10, centrY - (H*(i+1))+bH, centrY - (H*i), clrBlack);
		DrawColorRect(w / 3 + w / 15, w / 3 + w / 10, centrY + (H*i)+bH, centrY + (H*(i+1)) , clrBlack);
	}

	//"Экран"
	DrawColorRect(w - w / 12, w - w / 15, h / 6, h - h / 6, clrBlack);
	
	//Определение цвета света
	float clrLight[4];
	float constClrLight[4];

	int lamb = pSlcLevel->GetPhysObject(1)->GetAttrib(0)->GetValue();

	if (625 <= lamb && lamb <= 740)
		memcpy(constClrLight, C_COLOR_RED, sizeof(constClrLight));
	else if (590 <= lamb && lamb < 625)
		memcpy(constClrLight, C_COLOR_ORANGE, sizeof(constClrLight));
	else if (565 <= lamb && lamb < 590)
		memcpy(constClrLight, C_COLOR_YELLOW, sizeof(constClrLight));
	else if (500 <= lamb && lamb < 565)
		memcpy(constClrLight, C_COLOR_GREEN, sizeof(constClrLight));
	else if (485 <= lamb && lamb < 500)
		memcpy(constClrLight, C_COLOR_LIGHT_BLUE, sizeof(constClrLight));
	else if (440 <= lamb && lamb < 485)
		memcpy(constClrLight, C_COLOR_BLUE, sizeof(constClrLight));
	else if (380 <= lamb && lamb < 440)
		memcpy(constClrLight, C_COLOR_VIOLET, sizeof(constClrLight));
	else
		memcpy(constClrLight, C_COLOR_TRANSPARENT, sizeof(constClrLight));


	memcpy(clrLight, constClrLight, sizeof(clrLight));

	//Рисование лучей света
	DrawColorRect(w / 3 + w / 30, w - w / 12, centrY, centrY + bH, clrLight);
	
	//расстояние до экрана принято за 0,006 м == 6 мм
	int kmax = pSlcLevel->CalculateKmax();
	int klvl = pSlcLevel->GetPhysObject(1)->GetAttrib(1)->GetValue();
	float a; //расстояние между максимумами
	float b; //расстояние между экраном и решёткой
	b = h / 0.2475; //на момент написания здесь была своя логика
	float koef = pSlcLevel->GetPhysObject(1)->GetAttrib(0)->GetValue() / pSlcLevel->GetPhysObject(0)->GetAttrib(0)->GetValue() / 1000;
	float sin = 0;

	sin = koef * klvl;
	a = b*sin;

	/*if (centrY - a < h / 6)
	{
		float cat = 1/sin;
		float dx = (centrY - h/6)*b/a;
		DrawColorQuadr(w / 3 + w/10, centrY, w/3 + w/10 + dx, h/6, w / 3 + w/10 + dx, h / 6 + bH, w / 3 + w/10, centrY + bH, clrLight);
	}
	else*/
		DrawColorQuadr(w / 3 + w / 10, centrY, w - w / 12, centrY - a, w - w / 12, centrY - a + bH, w / 3 + w / 10, centrY + bH, clrLight);

	/*for (int k = 0; k <= kmax; k++)
	{
		sin = koef * k;
		a = b * sin;

		if (centrY - a < h / 6)
			break;

		//Рисовать линии
		DrawColorQuadr(w / 3 + w / 10, centrY, w - w / 12, centrY - a, w - w / 12, centrY - a + bH, w / 3 + w / 10, centrY + bH, clrLight);
		DrawColorQuadr(w / 3 + w / 10, centrY, w - w / 12, centrY + a, w - w / 12, centrY + a + bH, w / 3 + w / 10, centrY + bH, clrLight);
	}
	
	kmax = int(pSlcLevel->GetPhysObject(0)->GetAttrib(0)->GetValue() / pSlcLevel->GetPhysObject(1)->GetAttrib(0)->GetValue()*1000 - 0.5f);
	koef = pSlcLevel->GetPhysObject(1)->GetAttrib(0)->GetValue() / 2 / pSlcLevel->GetPhysObject(0)->GetAttrib(0)->GetValue()/1000;
	memcpy(clrLight, C_COLOR_BLACK, sizeof(clrLight));
	for (int k = 0; k <= kmax; k++)
	{
		sin = (2 * k + 1) * koef;
		a = b * sin;

		if (centrY - a < h / 6)
			break;

		DrawColorQuadr(w / 3 + w / 10, centrY, w - w / 12, centrY - a, w - w / 12, centrY - a + bH, w / 3 + w / 10, centrY + bH, clrLight);
		DrawColorQuadr(w / 3 + w / 10, centrY, w - w / 12, centrY + a, w - w / 12, centrY + a + bH, w / 3 + w / 10, centrY + bH, clrLight);
	}*/


	float dColor = 0.1f;
	a = 0;
	float dy = b * pSlcLevel->GetPhysObject(1)->GetAttrib(0)->GetValue() / pSlcLevel->GetPhysObject(0)->GetAttrib(0)->GetValue() /2/ 1000 / 10;
	memcpy(clrLight, constClrLight, sizeof(clrLight));
	bool tolight = false;
	while (true)
	{
		DrawColorRect(w - 11 * w / 120, w - w / 12, centrY-a, centrY -a + dy, clrLight);
		DrawColorRect(w - 11 * w / 120, w - w / 12, centrY + a, centrY + a + dy, clrLight);

		if (tolight)
			clrLight[3] += dColor;
		/*for (int i = 0; i < 4; i++)
			clrLight[i] += dColor;*/
		else
			clrLight[3] -= dColor;
			/*for (int i = 0; i < 4; i++)
				clrLight[i] -= dColor;*/

		if (clrLight[3] >= 1)
			tolight = false;
		if (clrLight[3] <= 0)
			tolight = true;

		a += dy;

		if (centrY - a < h / 6)
		{
			DrawColorRect(w - 11 * w / 120, w - w / 12, h / 6, centrY - a + dy, clrLight);
			DrawColorRect(w - 11 * w / 120, w - w / 12, centrY + a - dy, h - h / 6, clrLight);
			break;
		}

		
	}
	//Рамка окна показа
	glEnable(GL_TEXTURE_2D);
	DrawTextureRect(w / 3, w, 0, h, 0.0f, 0.0f, 1.0f, 1.0f, pAdMenuTxtr);
}

void DDrawer::FindLightWaveColor(double lamb, float ** color)
{
	if (625 <= lamb && lamb <= 740)
		memcpy(color, C_COLOR_RED, sizeof(color));
	else if (590 <= lamb && lamb < 625)
		memcpy(color, C_COLOR_ORANGE, sizeof(color));
	else if (565 <= lamb && lamb < 590)
		memcpy(color, C_COLOR_YELLOW, sizeof(color));
	else if (500 <= lamb && lamb < 565)
		memcpy(color, C_COLOR_GREEN, sizeof(color));
	else if (485 <= lamb && lamb < 500)
		memcpy(color, C_COLOR_LIGHT_BLUE, sizeof(color));
	else if (440 <= lamb && lamb < 485)
		memcpy(color, C_COLOR_BLUE, sizeof(color));
	else if (380 <= lamb && lamb < 440)
		memcpy(color, C_COLOR_VIOLET, sizeof(color));
	else
		memcpy(color, C_COLOR_TRANSPARENT, sizeof(color));
}

void DDrawer::DrawAttrib(DObjectAttrib * pAttrib, float x, float y, float w, float h, float * textClr)
{
	char text[256];

	if (pAttrib->GetName() == "d")
		sprintf(text, "%s:%4.0f мкм", pAttrib->GetName(), pAttrib->GetNewValue());
	if (pAttrib->GetName() == "lamb")
		sprintf(text, "%s:%4.0f нм", pAttrib->GetName(), pAttrib->GetNewValue());
	if (pAttrib->GetName() == "k")
		sprintf(text, "%s:%4.0f", pAttrib->GetName(), pAttrib->GetNewValue());
	if (pAttrib->GetName() == "angle")
		sprintf(text, "%s:%4.0f", pAttrib->GetName(), pAttrib->GetNewValue());

	DrawText(x, y, text, 24, textClr);

	if (pAttrib->GetButton())
	{
		DButton * pBtn = pAttrib->GetButton();
		pBtn->SetX(w - pBtn->GetWidth());
		pBtn->SetY(y);
		float bright;
		if (pBtn->GetEnableStatus()) bright = 1.0f;
		else bright = 0.5f;
		DrawButton(pBtn, pChangeBtnTxtr, bright);
	}
}