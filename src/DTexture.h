#ifndef DTEXTURE_H
#define DTEXTURE_H

// Фильтрация текстуры
	enum
	{
		FILTER_NEAREST,
		FILTER_LINEAR
	};
/*
Класс текстуры
*/
class DTexture
{
public:
	

	DTexture();
	~DTexture();

	// Индивидуальное имя текстуры
	char	Name[32];
	// Путь к файлу
	char	FileName[32];
	// Кол-во байт на пиксель ( не путать с "бит на пиксель" )
	char	bpp;
	// Ширина и высота изображения
	int		Width, 
			Height;

	// Данные о пикселях изображения
	unsigned char *Data;
	// Фильтр 
	unsigned int	Filter;

	// GAPI\OpenGL индификатор текстуры
	unsigned int	glTexture;
};

#endif DTEXTURE_H