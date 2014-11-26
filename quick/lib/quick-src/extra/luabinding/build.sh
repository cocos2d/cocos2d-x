#!/usr/bin/env bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR"
OUTPUT_DIR="$DIR"
MAKE_LUABINDING="$QUICK_V3_ROOT"/quick/bin/compile_luabinding.sh
$MAKE_LUABINDING -E CCOBJECTS=CCHTTPRequest -pfx cc -d "$OUTPUT_DIR" cocos2dx_extra_luabinding.tolua
echo ""
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo ""
$MAKE_LUABINDING -pfx cc -d "$OUTPUT_DIR" cocos2dx_extra_ios_iap_luabinding.tolua
echo ""
echo "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~"
echo ""
$MAKE_LUABINDING -pfx cc -d "$OUTPUT_DIR" HelperFunc_luabinding.tolua
