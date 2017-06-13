/*
Custom SFML Loader.

Loads appropriate SFML libs and dependencies
*/

#ifndef SFMLFULL_INCLUDED
#define SFMLFULL_INCLUDED

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>

#if defined(_DEBUG) || defined(DEBUG)
	#ifdef SFML_STATIC
		#pragma comment(lib,"sfml-graphics-s-d.lib")
		#pragma comment(lib,"sfml-audio-s-d.lib")
		#pragma comment(lib,"sfml-window-s-d.lib")
		#pragma comment(lib,"sfml-system-s-d.lib")

		// Dependancies https://www.sfml-dev.org/tutorials/2.3/start-vc.php
		#pragma comment(lib,"opengl32.lib")
		#pragma comment(lib,"freetype.lib")
		#pragma comment(lib,"jpeg.lib")
		#pragma comment(lib,"winmm.lib")
		#pragma comment(lib,"gdi32.lib")
		#pragma comment(lib,"openal32.lib")
		#pragma comment(lib,"flac.lib")
		#pragma comment(lib,"vorbisenc.lib")
		#pragma comment(lib,"vorbisfile.lib")
		#pragma comment(lib,"vorbis.lib")
		#pragma comment(lib,"ogg.lib")
	#else
		#pragma comment(lib,"sfml-graphics-d.lib")
		#pragma comment(lib,"sfml-audio-d.lib")
		#pragma comment(lib,"sfml-window-d.lib")
		#pragma comment(lib,"sfml-system-d.lib")

		#pragma comment(lib,"opengl32.lib")
		#pragma comment(lib,"freetype.lib")
		#pragma comment(lib,"jpeg.lib")
		#pragma comment(lib,"winmm.lib")
		#pragma comment(lib,"gdi32.lib")
		#pragma comment(lib,"openal32.lib")
		#pragma comment(lib,"flac.lib")
		#pragma comment(lib,"vorbisenc.lib")
		#pragma comment(lib,"vorbisfile.lib")
		#pragma comment(lib,"vorbis.lib")
		#pragma comment(lib,"ogg.lib")
	#endif
	#pragma comment(lib,"sfml-main-d.lib")
#else
	#ifdef SFML_STATIC
		#pragma comment(lib,"sfml-graphics-s.lib")
		#pragma comment(lib,"sfml-audio-s.lib")
		#pragma comment(lib,"sfml-window-s.lib")
		#pragma comment(lib,"sfml-system-s.lib")

		#pragma comment(lib,"opengl32.lib")
		#pragma comment(lib,"freetype.lib")
		#pragma comment(lib,"jpeg.lib")
		#pragma comment(lib,"winmm.lib")
		#pragma comment(lib,"gdi32.lib")
		#pragma comment(lib,"openal32.lib")
		#pragma comment(lib,"flac.lib")
		#pragma comment(lib,"vorbisenc.lib")
		#pragma comment(lib,"vorbisfile.lib")
		#pragma comment(lib,"vorbis.lib")
		#pragma comment(lib,"ogg.lib")
	#else
		#pragma comment(lib,"sfml-graphics.lib")
		#pragma comment(lib,"sfml-audio.lib")
		#pragma comment(lib,"sfml-window.lib")
		#pragma comment(lib,"sfml-system.lib")

		#pragma comment(lib,"opengl32.lib")
		#pragma comment(lib,"freetype.lib")
		#pragma comment(lib,"jpeg.lib")
		#pragma comment(lib,"winmm.lib")
		#pragma comment(lib,"gdi32.lib")
		#pragma comment(lib,"openal32.lib")
		#pragma comment(lib,"flac.lib")
		#pragma comment(lib,"vorbisenc.lib")
		#pragma comment(lib,"vorbisfile.lib")
		#pragma comment(lib,"vorbis.lib")
		#pragma comment(lib,"ogg.lib")
	#endif
	#pragma comment(lib,"sfml-main.lib")
#endif


#endif // SFMLFULL_INCLUDED 