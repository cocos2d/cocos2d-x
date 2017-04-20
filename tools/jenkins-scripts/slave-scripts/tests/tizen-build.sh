DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
COCOS2DX_ROOT="$DIR"/../../../..
cd ${COCOS2DX_ROOT}
cocos compile -p tizen --tizen-arch arm -s tests/cpp-tests
if [ ! $? = 0 ]; then
    echo "compile cpp-tests error"
    exit 1
fi

cocos compile -p tizen --tizen-arch arm -s tests/cpp-empty-test
if [ ! $? = 0 ]; then
    echo "compile cpp-empty-test error"
    exit 1
fi

cocos compile -p tizen --tizen-arch arm -s tests/lua-tests
if [ ! $? = 0 ]; then
    echo "compile lua-tests error"
    exit 1
fi

cocos compile -p tizen --tizen-arch arm -s tests/lua-empty-test
if [ ! $? = 0 ]; then
    echo "compile lua empty test error"
    exit 1
fi
