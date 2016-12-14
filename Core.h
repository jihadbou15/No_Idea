#pragma once

class Core
{
public:
	explicit Core( const Window& window );
	Core( const Core& other ) = delete;
	Core& operator=( const Core& other ) = delete;
	~Core( );

	void Run( );

private:
	// DATA MEMBERS
	// The window properties
	Window m_Window;
	// The window we render to
	SDL_Window* m_pWindow{ };
	// OpenGL context
	SDL_GLContext m_pContext{ };
	// The time keeper
	Uint32 m_MilliSeconds{};
	// Init info
	bool m_Initialized;

	// FUNCTIONS
	void Initialize( );
	void Cleanup( );
};
