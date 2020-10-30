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
project(MBL_example)

add_executable(example example.cxx)

if( CMAKE_SOURCE_DIR STREQUAL CMAKE_CURRENT_SOURCE_DIR )
  # stand-alone build
  find_package(MBL REQUIRED)
  target_link_libraries(example MBL::MBL_Static)
else()
  include_directories(../MBL/include)
  target_link_libraries(example MBL_Static)
endif()
