-- premake5.lua
workspace "Solar System Simulation"
   architecture "x64"
   configurations { "Debug", "Release", "Dist" }
   startproject "Solar System Simulation"

   -- Workspace-wide build options for MSVC
   filter "system:windows"
      buildoptions { "/EHsc", "/Zc:preprocessor", "/Zc:__cplusplus" }

OutputDir = "Build/%{cfg.system}-%{cfg.architecture}/%{cfg.buildcfg}"

group "Core"
	include "Engine/Build-Core.lua"
group ""

include "Solar System Simulation/Build-App.lua"