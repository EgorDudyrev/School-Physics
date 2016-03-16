#include "DObjectAttrib.h"
#include "DButton.h"

DObjectAttrib::DObjectAttrib()
{
	Value = 0; 
	newValue = 0;
	Name = 0;
	
	pChangeBtn = new DButton();
	pChangeBtn->SetWidth(32);
	pChangeBtn->SetHeight(32);
	pChangeBtn->SetVisibleStatus(true);
}


DObjectAttrib::~DObjectAttrib()
{
	if (Name)
		delete Name;
	if (pChangeBtn)
		delete pChangeBtn;
}
