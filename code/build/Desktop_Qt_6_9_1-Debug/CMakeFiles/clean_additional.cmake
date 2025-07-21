# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/rpg_v2_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/rpg_v2_autogen.dir/ParseCache.txt"
  "rpg_v2_autogen"
  )
endif()
