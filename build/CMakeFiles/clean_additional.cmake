# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Release")
  file(REMOVE_RECURSE
  "CMakeFiles\\CalculadoraAguaEspumas_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CalculadoraAguaEspumas_autogen.dir\\ParseCache.txt"
  "CalculadoraAguaEspumas_autogen"
  )
endif()
