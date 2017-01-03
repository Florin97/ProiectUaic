#include "ButtonModel.h"



ButtonModel::ButtonModel(char *label, int tag)
{
	this->label = label;
	this->tag = tag;
}

char *ButtonModel::getLabel() {
	return this->label;
}
int ButtonModel::getTag() {
	return this->tag;
}
ButtonModel::~ButtonModel()
{
}
