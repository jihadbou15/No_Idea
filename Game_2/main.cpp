#include "stdafx.h"
#include "Core.h"
#include <ctime>
void StartHeapControl( );

int main( int argc, char *argv[] )
{
	srand(int(time(nullptr)));
	
	StartHeapControl( );

	Core core{ Window{ "WTF - Gaytard, Goatfucker- 1DAEXX", 640.0f, 360.0f} };
	core.Run( );

	return 0;
}

void StartHeapControl( )
{
#if defined(DEBUG) | defined(_DEBUG)
	// Notify user if heap is corrupt
	HeapSetInformation( NULL, HeapEnableTerminationOnCorruption, NULL, 0 );

	// Report detected leaks when the program exits
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

	// Set a breakpoint on the specified object allocation order number
	//_CrtSetBreakAlloc( 143 );
#endif
}


