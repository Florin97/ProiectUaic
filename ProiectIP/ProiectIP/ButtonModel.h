#pragma once
class ButtonModel
{
private:
	char *label;
	int tag;
public:
	char *getLabel();
	int getTag();
	ButtonModel(char *label, int tag);
	~ButtonModel();
};

