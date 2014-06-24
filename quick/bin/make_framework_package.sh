#!/bin/bash
DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
cd "$DIR/../"
"$DIR/compile_scripts.sh" -i framework -o lib/framework_precompiled/framework_precompiled.zip -p framework -m zip

echo ""
echo "### UPDATING ###"
echo ""
echo "updating all framework_precompiled.zip"
echo ""
echo template/PROJECT_TEMPLATE_01/res/framework_precompiled.zip
cp lib/framework_precompiled/framework_precompiled.zip template/PROJECT_TEMPLATE_01/res/

for dest in `find samples -type f | grep "/res/framework_precompiled.zip"`
do
    echo $dest
    cp lib/framework_precompiled/framework_precompiled.zip $dest
done

echo ""
echo "DONE"
echo ""

