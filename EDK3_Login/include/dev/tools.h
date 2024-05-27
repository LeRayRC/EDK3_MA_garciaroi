#ifndef _CUSTOM_TOOLS_
#define _CUSTOM_TOOLS_ 1

#include "EDK3/scoped_array.h"

void ReadFile(const char* filename, EDK3::scoped_array<char>& output);

struct HeightmapConf {
	float scale;
	float coeff;
	float exp;
};

#endif // !_CUSTOM_TOOLS_
