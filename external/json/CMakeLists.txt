set(JSONCPP_SRC
  json_reader.cpp
  json_value.cpp 
  json_writer.cpp
)

include_directories(

)

add_library(jsoncpp STATIC
  ${JSONCPP_SRC}
)

