workspace "GameProject"
  configurations { "Debug", "Release" }
  location "./"

project "Game"
	kind "ConsoleApp"
	language "C++"
	location "bin/Game"
	targetdir "bin/%{cfg.buildcfg}"

	files { "src/**.hpp", "src/**.h", "src/**.cpp" }

	includedirs {
		"dep/include/",
	}

	libdirs { "./dep/lib/sdl2/",  "./dep/lib/glew/", "./dep/lib/soil/" }
	links {"sdl2", "sdl2main", "glew32", "gdi32", "OpenGL32", "soil"}