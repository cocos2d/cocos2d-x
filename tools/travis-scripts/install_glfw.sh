#!/bin/bash

GLFW_VERSION="3.0.4"
GLFW_SOURCE="https://codeload.github.com/glfw/glfw/tar.gz/${GLFW_VERSION}"
GLFW_ZIP="glfw${GLFW_VERSION}.tar.gz"
GLFW_INSTALL="glfw_install"
GLFW_SRCDIR="glfw-${GLFW_VERSION}"
GLFW_DESTDIR="glfw_dest"

install_glfw_dep()
{
  sudo apt-get install xorg-dev
  sudo apt-get install libglu1-mesa-dev
  sudo apt-get install cmake
  sudo apt-get install curl
}

clean_tmp_file()
{
  rm -rf ${GLFW_INSTALL}
}

make_and_install()
{
  mkdir $GLFW_DESTDIR
  cd $GLFW_DESTDIR
  cmake "../${GLFW_SRCDIR}" -G "Unix Makefiles" -DBUILD_SHARED_LIBS=ON
  make
  sudo make install
  sudo ldconfig
  cd ..
}

install_glfw()
{
  echo glw_version ${GLFW_VERSION}
  echo glfw_download_size ${GLFW_SOURCE}
  echo glfw_zip_file ${GLFW_ZIP}
  install_glfw_dep
  mkdir $GLFW_INSTALL
  cd $GLFW_INSTALL
  curl -o $GLFW_ZIP $GLFW_SOURCE
  tar xzf ${GLFW_ZIP}
  make_and_install
  cd ..
  clean_tmp_file
}


install_glfw

