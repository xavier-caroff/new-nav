cmake_minimum_required(VERSION 3.0.0)
project(new-nav VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 11)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

include(CTest)
enable_testing()

if (MSVC)
    add_definitions(
        -W4
    )
else()
    add_definitions(
        -Wall
    )
endif(MSVC)

add_subdirectory(framework)
add_subdirectory(app)
add_subdirectory(module)

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

# Doxygen documentation

find_package(Doxygen 1.8.10)
if(DOXYGEN_FOUND)
    
	configure_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/doc/Doxyfile.in
        ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        @ONLY)

	add_custom_target(doxygen
		${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating documentation with Doxygen" VERBATIM)
else(DOXYGEN_FOUND)

	message (WARNING "Documentation generation is disabled.")
endif(DOXYGEN_FOUND)
