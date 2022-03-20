#include "pch.h"
#include <iostream>
#include "LevelEditor.h"

int main(int argc, char** argv)
{
	try
	{
		LevelEditor levelEditor;
		levelEditor.initApp();
		levelEditor.getRoot()->startRendering();
		levelEditor.closeApp();
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error occurred during execution: " << e.what() << '\n';
		return 1;
	}

	return 0;
}
