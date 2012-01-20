pushd ./box2d/proj.wophone
make -f Makefile.ARM clean
make -f Makefile.ARM all
popd

pushd ./chipmunk/proj.wophone
make -f Makefile.ARM clean
make -f Makefile.ARM all
popd

pushd ./cocos2dx/proj.wophone
make -f Makefile.ARM clean
make -f Makefile.ARM all
popd

pushd ./CocosDenshion/proj.wophone
make -f Makefile.ARM clean
make -f Makefile.ARM all
popd

pushd ./HelloWorld/wophone
make -f Makefile.ARM clean
make -f Makefile.ARM all
popd

pushd ./tests/test.wophone
make -f Makefile.ARM clean
make -f Makefile.ARM all
popd

