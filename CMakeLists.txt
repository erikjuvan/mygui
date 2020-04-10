cmake_minimum_required(VERSION 3.11.3)
project(mygui VERSION 1.0 DESCRIPTION "my own private little GUI for SFML")

set(CMAKE_CONFIGURATION_TYPES "Debug;Release;RelWithDebInfo") 

set(CMAKE_DEBUG_POSTFIX "-d")

# Find SFML
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Tell CMake to create the executable
add_library(${PROJECT_NAME} SHARED)

set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(${PROJECT_NAME} PROPERTIES DEFINE_SYMBOL MYGUI_EXPORTS)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

target_sources(${PROJECT_NAME} PRIVATE
	src/Button.cpp
	src/Label.cpp
	src/Textbox.cpp	
	src/Checkbox.cpp
	src/Chart.cpp
	src/Action.cpp
	)
	
target_sources(${PROJECT_NAME} PRIVATE
	include/mygui/Config.hpp
	include/mygui/ResourceManager.hpp
	include/mygui/Object.hpp
	include/mygui/Button.hpp
	include/mygui/Label.hpp
	include/mygui/Textbox.hpp
	include/mygui/Checkbox.hpp
	include/mygui/Chart.hpp
	include/mygui/Action.hpp
	)
	
target_include_directories(${PROJECT_NAME} PRIVATE include/mygui)
target_link_libraries(${PROJECT_NAME} PRIVATE sfml-graphics sfml-window sfml-system)