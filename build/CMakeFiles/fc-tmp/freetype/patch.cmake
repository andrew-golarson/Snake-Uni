cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for freetype")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "C:/Users/Andrzej/Desktop/Snake/build/_deps/freetype-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[C:/mingw64/bin/cmake.exe]====] [====[-DFREETYPE_DIR=C:/Users/Andrzej/Desktop/Snake/build/_deps/freetype-src]====] [====[-P]====] [====[C:/Users/Andrzej/Desktop/Snake/thirdparty/SFML/tools/freetype/PatchFreetype.cmake]====]
)

endblock()
