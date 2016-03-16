#ifndef DTEXTURE_H
#define DTEXTURE_H

// ���������� ��������
	enum
	{
		FILTER_NEAREST,
		FILTER_LINEAR
	};
/*
����� ��������
*/
class DTexture
{
public:
	

	DTexture();
	~DTexture();

	// �������������� ��� ��������
	char	Name[32];
	// ���� � �����
	char	FileName[32];
	// ���-�� ���� �� ������� ( �� ������ � "��� �� �������" )
	char	bpp;
	// ������ � ������ �����������
	int		Width, 
			Height;

	// ������ � �������� �����������
	unsigned char *Data;
	// ������ 
	unsigned int	Filter;

	// GAPI\OpenGL ����������� ��������
	unsigned int	glTexture;
};

#endif DTEXTURE_H