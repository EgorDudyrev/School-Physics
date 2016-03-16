#include "DModel.h"

DModel::DModel()
{
	
}

DModel::~DModel(void)
{
	if( Vertex )
		delete [] Vertex;
	if( Index )
		delete [] Index;
}