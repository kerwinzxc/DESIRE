project "DESIRE"
	AddCommonLibConfig()
	warnings "Extra"
	uuid "74923478-6D8D-4892-A013-C2B759A870EC"

	pchheader "Engine/stdafx.h"
	pchsource "../src/Engine/stdafx.cpp"

	includedirs
	{
		"../3rdparty",
	}

	files
	{
		"../3rdparty/**.h",
	}

	filter "system:not android"
		removefiles
		{
			"../src/**/ANDROID/**",
		}

	filter "system:not ios"
		removefiles
		{
			"../src/**/IOS/**",
		}

	filter "system:not linux"
		removefiles
		{
			"../src/**/LINUX/**",
		}

	filter "system:not macosx"
		removefiles
		{
			"../src/**/OSX/**",
		}

	filter "system:not windows"
		removefiles
		{
			"../src/**/WINDOWS/**",
		}
