#include <SDL.h>    // Apparently need to include this where main is
#include <iostream>
#include "../include/GameStates/StateFramework/GameStateManager.h"
#include "../include/GameStates/States/MainMenuState.h"
#include "../include/GameStates/States/GameRunningState.h"
#include "../include/SDL/SDLManager.h"
#include <windows.h>
#include <stdio.h>
#include <tchar.h>

// Use to convert bytes to KB
#define DIV 1024

// Specify the width of the field in which to print the numbers. 
// The asterisk in the format specifier "%*I64d" takes an integer 
// argument and uses it to pad and right justify the number.
#define WIDTH 7

// Messing with Awesomium integration
// Various included headers
int main(int argc, char *argv[])
{
	MEMORYSTATUSEX statex;

	statex.dwLength = sizeof(statex);

	GlobalMemoryStatusEx(&statex);

	_tprintf(TEXT("There is  %*ld percent of memory in use.\n"),
		WIDTH, statex.dwMemoryLoad);
	_tprintf(TEXT("There are %*I64d total KB of physical memory.\n"),
		WIDTH, statex.ullTotalPhys / DIV);
	_tprintf(TEXT("There are %*I64d free  KB of physical memory.\n"),
		WIDTH, statex.ullAvailPhys / DIV);
	_tprintf(TEXT("There are %*I64d total KB of paging file.\n"),
		WIDTH, statex.ullTotalPageFile / DIV);
	_tprintf(TEXT("There are %*I64d free  KB of paging file.\n"),
		WIDTH, statex.ullAvailPageFile / DIV);
	_tprintf(TEXT("There are %*I64d total KB of virtual memory.\n"),
		WIDTH, statex.ullTotalVirtual / DIV);
	_tprintf(TEXT("There are %*I64d free  KB of virtual memory.\n"),
		WIDTH, statex.ullAvailVirtual / DIV);

	// Show the amount of extended memory available.

	_tprintf(TEXT("There are %*I64d free  KB of extended memory.\n"),
		WIDTH, statex.ullAvailExtendedVirtual / DIV);
    // Set up the Game State Manager
    GameStateManager gamestatemanager;

    // Add states
    gamestatemanager.AddState(new MainMenuState());
    gamestatemanager.AddState(new GameRunningState());

    // Loop forever
    gamestatemanager.Run();

	statex.dwLength = sizeof(statex);

	GlobalMemoryStatusEx(&statex);

	_tprintf(TEXT("There is  %*ld percent of memory in use.\n"),
		WIDTH, statex.dwMemoryLoad);
	_tprintf(TEXT("There are %*I64d total KB of physical memory.\n"),
		WIDTH, statex.ullTotalPhys / DIV);
	_tprintf(TEXT("There are %*I64d free  KB of physical memory.\n"),
		WIDTH, statex.ullAvailPhys / DIV);
	_tprintf(TEXT("There are %*I64d total KB of paging file.\n"),
		WIDTH, statex.ullTotalPageFile / DIV);
	_tprintf(TEXT("There are %*I64d free  KB of paging file.\n"),
		WIDTH, statex.ullAvailPageFile / DIV);
	_tprintf(TEXT("There are %*I64d total KB of virtual memory.\n"),
		WIDTH, statex.ullTotalVirtual / DIV);
	_tprintf(TEXT("There are %*I64d free  KB of virtual memory.\n"),
		WIDTH, statex.ullAvailVirtual / DIV);

	// Show the amount of extended memory available.

	_tprintf(TEXT("There are %*I64d free  KB of extended memory.\n"),
		WIDTH, statex.ullAvailExtendedVirtual / DIV);

	getchar();
    return 0;
}
