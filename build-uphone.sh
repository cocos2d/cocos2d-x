pushd ./box2d/proj.uphone
make -f Makefile.ARM clean
make -f Makefile.ARM all
popd

pushd ./chipmunk/proj.uphone
make -f Makefile.ARM clean
make -f Makefile.ARM all
popd

pushd ./cocos2dx/proj.uphone
make -f Makefile.ARM clean
make -f Makefile.ARM all
popd

pushd ./CocosDenshion/proj.uphone
make -f Makefile.ARM clean
make -f Makefile.ARM all
popd

pushd ./tests/test.uphone
make -f Makefile.ARM clean
make -f Makefile.ARM all
popd

