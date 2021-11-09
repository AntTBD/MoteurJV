#include "ImGuiWindowConfig.h"

void ImGuiWindowConfig::show()
{
	if (this->show)
	{
		if (this->begin("Config"))
		{
			/// TODO complete config window interface
		}
		this->end();
	}
}