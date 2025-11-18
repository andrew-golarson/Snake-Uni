cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for flac")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "C:/Users/Andrzej/Desktop/Snake/build/_deps/flac-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[C:/mingw64/bin/cmake.exe]====] [====[-DFLAC_DIR=C:/Users/Andrzej/Desktop/Snake/build/_deps/flac-src]====] [====[-P]====] [====[C:/Users/Andrzej/Desktop/Snake/thirdparty/SFML/tools/flac/PatchFLAC.cmake]====]
)

endblock()
