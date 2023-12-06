#include "OpenGLRender.h"

using namespace std;

int main()
{
	Window win{ 1400, 1400, "e" };

	while (win.IsRunning())
	{
		win.Update();
		win.SwapBuffers();
	}

	cout << "Hello CMake." << endl;
	return 0;
}
