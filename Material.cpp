#include "Material.h"

Material::Material(float ra, float rd, float rs)
{
	this->ra = ra;
	this->rd = rd;
	this->rs = rs;
}

float Material::getRa() 
{
	return ra;
}

float Material::getRd() 
{
	return rd;
}

float Material::getRs() 
{
	return rs;
}

void Material::setRa(float ra)
{
	this->ra = ra;
}

void Material::setRd(float rd)
{
	this->rd = rd;
}

void Material::setRs(float rs)
{
	this->rs = rs;
}
