#!/usr/bin/python
#-*- coding: UTF-8 -*-
# ----------------------------------------------------------------------------
# Convert the performance test result from json files to excel.
#
# Author: Bill Zhang
#
# License: MIT
# ----------------------------------------------------------------------------
'''
Convert the performance test result from json files to excel.
'''

import xlwt
import os
import json

from argparse import ArgumentParser

DEFAULT_STYLE = 'borders: left thin, right thin, top thin, bottom thin;'
CONDITION_STYLE = 'pattern: pattern solid, fore_color light_green;'
RESULT_STYLE = 'pattern: pattern solid, fore_color light_yellow;'

BASE_KEYS = [
    'osVersion',
    'fileVersion',
    'timeStamp',
    'engineVersion',
    'device'
]

KEY_CONDITION_HEADERS = "conditionHeaders"
KEY_RESULT_HEADERS    = "resultHeaders"
KEY_RESULTS           = "results"

START_COL_INDEX = 0
START_ROW_INDEX = 0

class KnownException(Exception):
    pass

class Convertor:

    def __init__(self, src_path, output_path=None):
        self.src_path = self.change_to_abspath(src_path)
        if not os.path.exists(self.src_path):
            raise KnownException('%s is not existed!' % self.src_path)

        if output_path is None:
            # not specified output path, default use source path
            if os.path.isfile(self.src_path):
                self.output_path = os.path.dirname(self.src_path)
            else:
                self.output_path = self.src_path
        else:
            self.output_path = self.change_to_abspath(output_path)

    def change_to_abspath(self, path):
        ret = os.path.expanduser(path)
        if not os.path.isabs(ret):
            ret = os.path.abspath(ret)

        ret = os.path.normpath(ret)
        return ret

    def get_col_width(self, col_str):
        return 256 * (len(col_str) + 1)

    def convert_file(self, file_path):
        f = open(file_path)
        testData = json.load(f)
        f.close()

        basename, ext = os.path.splitext(os.path.basename(file_path))
        dst_file_path = os.path.join(self.output_path, "%s.xls" % basename)
        if os.path.isfile(dst_file_path):
            os.remove(dst_file_path)

        workbook = xlwt.Workbook(encoding = 'ascii')

        default_style = xlwt.Style.easyxf(DEFAULT_STYLE)
        con_style = xlwt.Style.easyxf("%s%s" % (DEFAULT_STYLE, CONDITION_STYLE))
        ret_style = xlwt.Style.easyxf("%s%s" % (DEFAULT_STYLE, RESULT_STYLE))

        for key in testData.keys():
            if key in BASE_KEYS:
                continue

            # create a sheet for the test case
            sheetObj = workbook.add_sheet(key)

            # get test case data
            caseInfo = testData[key]

            # Add headers for the test case
            condHeaders = caseInfo[KEY_CONDITION_HEADERS]
            retHeaders = caseInfo[KEY_RESULT_HEADERS]
            curRow = START_ROW_INDEX
            curCol = START_COL_INDEX

            col_widths = {}
            for header in (condHeaders + retHeaders):
                sheetObj.write(curRow, curCol, header, default_style)
                col_width = self.get_col_width(header)
                col_widths[curCol] = col_width
                sheetObj.col(curCol).width = col_width
                curCol += 1

            rets = caseInfo[KEY_RESULTS]
            for retInfo in rets:
                curRow += 1
                curCol = START_COL_INDEX
                for ret in retInfo:
                    if (curCol - START_COL_INDEX) < len(condHeaders):
                        use_style = con_style
                    else:
                        use_style = ret_style
                    sheetObj.write(curRow, curCol, ret, use_style)
                    new_width = self.get_col_width(ret)
                    old_width = col_widths[curCol]
                    if new_width > old_width:
                        sheetObj.col(curCol).width = new_width
                        col_widths[curCol] = new_width
                    curCol += 1

        workbook.save(dst_file_path)
        print("%s is generated." % dst_file_path)

    def do_convert(self):
        if not os.path.exists(self.output_path):
            os.makedirs(self.output_path)

        if os.path.isfile(self.src_path):
            self.convert_file(self.src_path)
        else:
            for f in os.listdir(self.src_path):
                full_path = os.path.join(self.src_path, f)
                ignore, ext = os.path.splitext(f)
                if os.path.isfile(full_path) and ext == '.json':
                    self.convert_file(full_path)

if __name__ == '__main__':
    parser = ArgumentParser(description="Performance test data convertor.")
    parser.add_argument('-s', dest='src_path', required=True, help='Specify the json file path or the folder path of json files.')
    parser.add_argument('-o', dest='output_path', help='Specify the output path of excel files.')
    (args, unknown) = parser.parse_known_args()

    try:
        convertor = Convertor(args.src_path, args.output_path)
        convertor.do_convert()
    except Exception as e:
        if e.__class__.__name__ == "KnownException":
            print(' '.join(e.args))
        else:
            raise
