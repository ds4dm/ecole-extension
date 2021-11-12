cmake_minimum_required(VERSION 3.15.0)

project(
	{{cookiecutter.cmake_project_name}}_extension
	LANGUAGES CXX
	DESCRIPTION "{{cookiecutter.project_short_description}}"
	VERSION {{cookiecutter.version}}
)


option(CMAKE_POSITION_INDEPENDENT_CODE "Position Independent Code for building shared libraries." ON)
option(CMAKE_VISIBILITY_INLINES_HIDDEN "Hidden symbol visibility for inline functions in shared libraries" ON)
set(CMAKE_CXX_VISIBILITY_PRESET hidden CACHE STRING "Hidden visibility of symbols in shared libraries.")

find_package(Python COMPONENTS Interpreter Development NumPy REQUIRED)
find_package(Ecole REQUIRED)
find_package(EcoleExtensionHelper REQUIRED)
find_package(pybind11 REQUIRED)
find_package(xtensor REQUIRED)
find_package(xtensor-python REQUIRED)

pybind11_add_module(
	{{cookiecutter.python_module_name}}
	src/bindings.cpp
	src/some-observation.cpp
)

target_include_directories(
	{{cookiecutter.python_module_name}}
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include
	SYSTEM PRIVATE "${Python_NumPy_INCLUDE_DIRS}"
)

target_link_libraries(
	{{cookiecutter.python_module_name}}
	PRIVATE
		Ecole::ecole-lib
		xtensor
		xtensor-python
)

if(SKBUILD)
	install(
		TARGETS {{cookiecutter.python_module_name}}
		DESTINATION src/{{cookiecutter.python_package_name}}
	)
endif()
