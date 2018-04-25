cmake_minimum_required (VERSION 2.6)
project (Sheet)
# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)
 

include_directories (
  "./Cell.h"
  "./CellAddress.h"
  "./Range.h"
  "./Sheet.h"
  "./SheetView.h"
  )
 

set(SOURCES main.cpp SheetView.cpp Range.cpp Sheet.cpp CellAdress.cpp Cell.cpp)
 
file(GLOB SOURCES "*.cpp")

# add the executable
add_executable(sheet ${SOURCES})