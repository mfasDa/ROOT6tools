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

set(MODULE ROOT6tools)

include_directories(
    ${ROOT_INCLUDE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}
)
link_directories(
    ${ROOT_LIBDIR}
)

set(SRCS
    TNamedStl.cxx
    TGraphicsStyle.cxx
    TPlotMaker.cxx
)

# Headers from sources
string(REPLACE ".cxx" ".h" HDRS "${SRCS}")

set(ROOT_DEPENDENCIES Core EG Geom Gpad Graf Hist MathCore Matrix Physics RIO Tree VMC)

get_directory_property(incdirs INCLUDE_DIRECTORIES)
generate_dictionary("${MODULE}" "${MODULE}LinkDef.h" "${HDRS}" "${incdirs}")

# Create an object to be reused in case of static libraries 
# Otherwise the sources will be compiled twice
add_library(${MODULE} SHARED ${SRCS} ${HDRS} ${MODULE}LinkDef.h G__${MODULE}.cxx)

target_link_libraries(${MODULE} ${ROOT_DEPENDENCIES})

install(TARGETS ${MODULE}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib)
install(FILES ${HDRS} DESTINATION include)
