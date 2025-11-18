cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for ogg")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "C:/Users/Andrzej/Desktop/Snake/build/_deps/ogg-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[C:/mingw64/bin/cmake.exe]====] [====[-DOGG_DIR=C:/Users/Andrzej/Desktop/Snake/build/_deps/ogg-src]====] [====[-P]====] [====[C:/Users/Andrzej/Desktop/Snake/thirdparty/SFML/tools/ogg/PatchOgg.cmake]====]
)

endblock()
