# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\multiThreadsApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\multiThreadsApp_autogen.dir\\ParseCache.txt"
  "multiThreadsApp_autogen"
  )
endif()
