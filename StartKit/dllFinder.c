#include <windows.h>
#include <stdio.h>

int main(void)
{
	HINSTANCE hDLL;
	// Load a Dll
	hDLL = LoadLibrary(TEXT("artilleryRed.dll"));

	if (hDLL != NULL) {
		printf("DLL Found\n");
	}
	else {
		printf("DLL Not Found\n");
	}

	return 0;
}