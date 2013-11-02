set(UNZIP_SRC
  ioapi.cpp
  unzip.cpp
)

add_library(unzip STATIC
  ${UNZIP_SRC}
)
