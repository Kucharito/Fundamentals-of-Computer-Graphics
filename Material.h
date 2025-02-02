#pragma once

// Author: Adam Kuchár
// Login: KUC0396

#include <glm/glm.hpp>


class Material {
private:
	float ra;
	float rd;
	float rs;

public:
	Material(float ra, float rd, float rs);
	float getRa();
	float getRd();
	float getRs();
	void setRa(float ra);
	void setRd(float rd);
	void setRs(float rs);
};