#ifndef DMODEL_H
#define DMODEL_H

struct DVertex
{
	float x, y, z;
	float nx, ny, nz;
	float tu, tv;
};

class DModel
{
public:
	DModel();
	~DModel();

	unsigned int VertexCount;
	DVertex *Vertex;

	DVertex bbMax, bbMin;
	float Radius;

	unsigned int IndexCount;
	unsigned short *Index;
private:
	
};

#endif