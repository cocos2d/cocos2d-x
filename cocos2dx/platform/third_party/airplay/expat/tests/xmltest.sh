#! /bin/sh

#   EXPAT TEST SCRIPT FOR W3C XML TEST SUITE

# This script can be used to exercise Expat against the
# w3c.org xml test suite, available from
# http://www.w3.org/XML/Test/xmlts20020606.zip.

# To run this script, first set XMLWF so that xmlwf can be
# found, then set the output directory with OUTPUT.

# The script lists all test cases where Expat shows a discrepancy
# from the expected result. Test cases where only the canonical
# output differs are prefixed with "Output differs:", and a diff file
# is generated in the appropriate subdirectory under $OUTPUT.

# If there are output files provided, the script will use
# output from xmlwf and compare the desired output against it.
# However, one has to take into account that the canonical output
# produced by xmlwf conforms to an older definition of canonical XML
# and does not generate notation declarations.

MYDIR="`dirname \"$0\"`"
cd "$MYDIR"
MYDIR="`pwd`"
XMLWF="`dirname \"$MYDIR\"`/xmlwf/xmlwf"
# XMLWF=/usr/local/bin/xmlwf
TS="$MYDIR/XML-Test-Suite"
# OUTPUT must terminate with the directory separator.
OUTPUT="$TS/out/"
# OUTPUT=/home/tmp/xml-testsuite-out/


RunXmlwfNotWF() {
  $XMLWF $1 $2 > outfile || return $?
  read outdata < outfile
  if test "$outdata" = "" ; then
      echo "Well formed: $3$2"
      return 1
  else
      return 0
  fi 
}

RunXmlwfWF() {
  $XMLWF $1 -d "$OUTPUT$3" $2 > outfile || return $?
  read outdata < outfile 
  if test "$outdata" = "" ; then 
      if [ -f out/$2 ] ; then 
          diff "$OUTPUT$3$2" out/$2 > outfile 
          if [ -s outfile ] ; then 
              cp outfile $OUTPUT$3${2}.diff 
              echo "Output differs: $3$2"
              return 1
          fi 
      fi 
      return 0
  else 
      echo "In $3: $outdata"
      return 1
  fi 
}

SUCCESS=0
ERROR=0

##########################
# well-formed test cases #
##########################

cd "$TS/xmlconf"
for xmldir in ibm/valid/P*/ \
              ibm/invalid/P*/ \
              xmltest/valid/ext-sa/ \
              xmltest/valid/not-sa/ \
              xmltest/invalid/ \
              xmltest/invalid/not-sa/ \
              xmltest/valid/sa/ \
              sun/valid/ \
              sun/invalid/ ; do
  cd "$TS/xmlconf/$xmldir"
  mkdir -p "$OUTPUT$xmldir"
  for xmlfile in *.xml ; do
      if RunXmlwfWF -p "$xmlfile" "$xmldir" ; then
          SUCCESS=`expr $SUCCESS + 1`
      else
          ERROR=`expr $ERROR + 1`
      fi
  done
  rm outfile
done

cd "$TS/xmlconf/oasis"
mkdir -p "$OUTPUT"oasis/
for xmlfile in *pass*.xml ; do
    if RunXmlwfWF -p "$xmlfile" "oasis/" ; then
        SUCCESS=`expr $SUCCESS + 1`
    else
        ERROR=`expr $ERROR + 1`
    fi
done
rm outfile

##############################
# not well-formed test cases #
##############################

cd "$TS/xmlconf"
for xmldir in ibm/not-wf/P*/ \
              ibm/not-wf/misc/ \
              xmltest/not-wf/ext-sa/ \
              xmltest/not-wf/not-sa/ \
              xmltest/not-wf/sa/ \
              sun/not-wf/ ; do
  cd "$TS/xmlconf/$xmldir"
  for xmlfile in *.xml ; do
      if RunXmlwfNotWF -p "$xmlfile" "$xmldir" ; then
          SUCCESS=`expr $SUCCESS + 1`
      else
          ERROR=`expr $ERROR + 1`
      fi
  done
  rm outfile
done

cd "$TS/xmlconf/oasis"
for xmlfile in *fail*.xml ; do
    if RunXmlwfNotWF -p "$xmlfile" "oasis/" ; then
        SUCCESS=`expr $SUCCESS + 1`
    else
        ERROR=`expr $ERROR + 1`
    fi
done
rm outfile

echo "Passed: $SUCCESS"
echo "Failed: $ERROR"
