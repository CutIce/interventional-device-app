# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\omega7_com_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\omega7_com_autogen.dir\\ParseCache.txt"
  "omega7_com_autogen"
  )
endif()
