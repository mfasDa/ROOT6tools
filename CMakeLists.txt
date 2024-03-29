############################################################################
# Various helpers making life easier when working with ROOT6               #
# Copyright (C) 2015  Markus Fasel, Lawrence Berkeley National Laboratory  #
#                                                                          #
# This program is free software: you can redistribute it and/or modify     #
# it under the terms of the GNU General Public License as published by     #
# the Free Software Foundation, either version 3 of the License, or        #
# (at your option) any later version.                                      #
#                                                                          #
# This program is distributed in the hope that it will be useful,          #
# but WITHOUT ANY WARRANTY; without even the implied warranty of           #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            #
# GNU General Public License for more details.                             #
#                                                                          #
# You should have received a copy of the GNU General Public License        #
# along with this program.  If not, see <http://www.gnu.org/licenses/>.    #
############################################################################

project(ROOT6tools CXX)
cmake_minimum_required(VERSION 2.8.11)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake/modules" ${CMAKE_MODULE_PATH})

find_package(ROOT 6.04.02 REQUIRED)

include(CheckCXXCompilerFlag)

# ROOT dictionaries and maps
include(ROOTHelper)

#Determine ROOT c++ standard
execute_process(COMMAND root-config --has-cxx11 OUTPUT_VARIABLE ROOT_HAS_C++11)
string(REGEX REPLACE "\n$" "" ROOT_HAS_C++11 "${ROOT_HAS_C++11}")
execute_process(COMMAND root-config --has-cxx14 OUTPUT_VARIABLE ROOT_HAS_C++14)
string(REGEX REPLACE "\n$" "" ROOT_HAS_C++14 "${ROOT_HAS_C++14}")
execute_process(COMMAND root-config --has-cxx17 OUTPUT_VARIABLE ROOT_HAS_C++17)
string(REGEX REPLACE "\n$" "" ROOT_HAS_C++17 "${ROOT_HAS_C++17}")
execute_process(COMMAND root-config --has-cxx20 OUTPUT_VARIABLE ROOT_HAS_C++20)
string(REGEX REPLACE "\n$" "" ROOT_HAS_C++20 "${ROOT_HAS_C++20}")
MESSAGE(STATUS "C++11: ${ROOT_HAS_C++11}")
MESSAGE(STATUS "C++14: ${ROOT_HAS_C++14}")
MESSAGE(STATUS "C++17: ${ROOT_HAS_C++17}")
MESSAGE(STATUS "C++20: ${ROOT_HAS_C++20}")
if(ROOT_HAS_C++11 STREQUAL "yes")
	MESSAGE(STATUS "ROOT compiled with C++11 standard")
	CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
	CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)
	if(COMPILER_SUPPORTS_CXX11)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
	elseif(COMPILER_SUPPORTS_CXX0X)
    		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
	else()
    		message(FATAL_ERROR "C++11 support required.")
	endif()
elseif(ROOT_HAS_C++14 STREQUAL "yes")
	MESSAGE(STATUS "ROOT compiled with C++14 standard")
	CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)
	CHECK_CXX_COMPILER_FLAG("-std=c++1y" COMPILER_SUPPORTS_CXX1Y)
	if(COMPILER_SUPPORTS_CXX14)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
	elseif(COMPILER_SUPPORTS_CXX1Y)
    		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")
	else()
    		message(FATAL_ERROR "C++14 support required.")
	endif()
elseif(ROOT_HAS_C++17 STREQUAL "yes")
	MESSAGE(STATUS "ROOT compiled with C++17 standard")
	CHECK_CXX_COMPILER_FLAG("-std=c++17" COMPILER_SUPPORTS_CXX17)
	CHECK_CXX_COMPILER_FLAG("-std=c++1z" COMPILER_SUPPORTS_CXX1Z)
	if(COMPILER_SUPPORTS_CXX17)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
	elseif(COMPILER_SUPPORTS_CXX1Z)
    		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z")
	else()
    		message(FATAL_ERROR "C++17 support required.")
	endif()
elseif(ROOT_HAS_C++20 STREQUAL "yes")
	MESSAGE(STATUS "ROOT compiled with C++20 standard")
	CHECK_CXX_COMPILER_FLAG("-std=c++20" COMPILER_SUPPORTS_CXX20)
	CHECK_CXX_COMPILER_FLAG("-std=c++2a" COMPILER_SUPPORTS_CXX2A)
	if(COMPILER_SUPPORTS_CXX20)
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")
	elseif(COMPILER_SUPPORTS_CXX2A)
    		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++2a")
	else()
    		message(FATAL_ERROR "C++20 support required.")
	endif()
endif()

# Add libc++ in case of clang
message (STATUS "Compiler: ${CMAKE_CXX_COMPILER_ID}")
if(CMAKE_CXX_COMPILER_ID  STREQUAL Clang)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
endif()


add_subdirectory(src)
