#include "Aoth.h"
//#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
int main()
{
	Aoth demo;
	if (demo.Construct(1024, 576, 1, 1))
		demo.Start();
	return 0;
}
