#pragma once
class DButton;

class DObjectAttrib
{
public:
	DObjectAttrib();
	~DObjectAttrib();

	void SetValue(double val) { Value = val; }
	double GetValue() { return Value; }
	void SetNewValue(double val) { newValue = val; }
	double GetNewValue() { return newValue; }
	void AsignValue() { if (newValue != 0) Value = newValue; else newValue = Value; }
	//void SetValue(float val) { Value = val; }
	//float GetValue() { return Value; }

	void SetName(char * name) { Name = name; }
	char * GetName(){ return Name; }
	void * ClickButton();
	DButton * GetButton() { return pChangeBtn; }
	void deleteButton(){ if (pChangeBtn) delete pChangeBtn; pChangeBtn = 0; }
private:
	double Value;
	double newValue;
	//float Value;
	char * Name;
	DButton * pChangeBtn;
};

