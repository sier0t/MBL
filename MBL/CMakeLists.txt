# ----------------------------------------------------------------------
# Copyright (C) 2020 Karol Sierocinski
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.                           
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.
# ----------------------------------------------------------------------

cmake_minimum_required(VERSION 3.5)

project(MBL LANGUAGES CXX)
project(MBL VERSION 0.0.1 DESCRIPTION "MBL - Macro Benchmarking Library")

include(GNUInstallDirs)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(MBL_SRC
        src/MBL.cxx
        src/measure.cxx
        src/measurement.cxx
)

add_library(MBL_Shared SHARED ${MBL_SRC})
add_library(MBL_Static STATIC ${MBL_SRC})

set(MBL_targets MBL_Shared MBL_Static)
set_property(TARGET ${MBL_targets} PROPERTY OUTPUT_NAME MBL)
set_property(TARGET ${MBL_targets} PROPERTY POSITION_INDEPENDENT_CODE true)

target_include_directories(MBL_Shared PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)
target_include_directories(MBL_Static PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
    $<INSTALL_INTERFACE:include>
)
set_property(TARGET ${MBL_targets} PROPERTY VERSION ${PROJECT_VERSION})
set_property(TARGET ${MBL_targets} PROPERTY PUBLIC_HEADER "include/MBL.h")


install(TARGETS ${MBL_targets}
    EXPORT MBLConfig
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(DIRECTORY "include/MBL"
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

export(TARGETS
    ${MBL_targets}
    NAMESPACE MBL::
    FILE "${CMAKE_CURRENT_BINARY_DIR}/MBLConfig.cmake"
)

install(EXPORT
    MBLConfig
    DESTINATION "${CMAKE_INSTALL_DATADIR}/MBL/cmake"
    NAMESPACE MBL::
)
