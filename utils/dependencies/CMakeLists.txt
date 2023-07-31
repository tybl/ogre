# License: The Unlicense (https://unlicense.org)
cmake_minimum_required(VERSION 3.18)

project(ogre_dependencies)

include(ExternalProject)

ExternalProject_Add(doctest
	CMAKE_ARGS	-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
			-DDOCTEST_WITH_TESTS=OFF
	GIT_REPOSITORY	https://github.com/onqtam/doctest.git
	GIT_SHALLOW	TRUE
	GIT_TAG		ae7a13539fb71f270b87eb2e874fbac80bc8dda2 #v2.4.11
	INSTALL_DIR	${CMAKE_BINARY_DIR})

ExternalProject_Add(fmt
	CMAKE_ARGS	-DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
			-DFMT_DOC=OFF
			-DFMT_TEST=OFF
	GIT_REPOSITORY	https://github.com/fmtlib/fmt.git
	GIT_SHALLOW	TRUE
	GIT_TAG		a33701196adfad74917046096bf5a2aa0ab0bb50 #v9.1.0
	INSTALL_DIR	${CMAKE_BINARY_DIR})
