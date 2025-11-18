cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

message(VERBOSE "Executing patch step for sheenbidi")

block(SCOPE_FOR VARIABLES)

execute_process(
  WORKING_DIRECTORY "C:/Users/Andrzej/Desktop/Snake/build/_deps/sheenbidi-src"
  COMMAND_ERROR_IS_FATAL LAST
  COMMAND  [====[C:/mingw64/bin/cmake.exe]====] [====[-DSHEENBIDI_DIR=C:/Users/Andrzej/Desktop/Snake/build/_deps/sheenbidi-src]====] [====[-P]====] [====[C:/Users/Andrzej/Desktop/Snake/thirdparty/SFML/tools/sheenbidi/PatchSheenBidi.cmake]====]
)

endblock()
