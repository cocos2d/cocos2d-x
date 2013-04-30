//
//  main.cpp
//  jsbcc
//
//  Created by sun zhuoshi on 4/28/13.
//  Copyright (c) 2013 sunzhuoshi. All rights reserved.
//

#include <iostream>
#include <sstream>

#include <sys/select.h>
#include <stdio.h>
#include <unistd.h>

#include "jsapi.h"

const char *USAGE = "Usage: jsbcc input_js_file [byte_code_file]\n"\
                    "       Pipe supported";
const char *BYTE_CODE_FILE_SUFFIX = ".bc";

enum ErrorCode {
    EC_OK = 0,
    EC_ERROR = 1
};

void Finalize(JSFreeOp *freeOp, JSObject *obj) {
}

void ReportError(JSContext *cx, const char *message, JSErrorReport *report) {
    std::cerr << "Error! " << message <<  std::endl;
}

JSClass GlobalClass = {
    "global", JSCLASS_GLOBAL_FLAGS,
    JS_PropertyStub, JS_PropertyStub, JS_PropertyStub, JS_StrictPropertyStub,
    JS_EnumerateStub, JS_ResolveStub, JS_ConvertStub, Finalize,
    JSCLASS_NO_OPTIONAL_MEMBERS
};

bool WriteFile(const std::string &filePath, void *data, uint32_t length) {
    FILE *file = fopen(filePath.c_str(), "wb");
    if (file) {
        size_t ret = fwrite(data, 1, length, file);
        fclose(file);
        if (ret == length) {
            return true;
        }
    }
    return false;
}

int main(int argc, const char * argv[])
{
    std::string inputFilePath;
    std::ostringstream outputFilePath;
    if (1 == argc) {
        fd_set fds;
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 500; // wait pipe data timeout
        FD_ZERO (&fds);
        FD_SET (STDIN_FILENO, &fds);
        int result = select (STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
        if (result) { // STDIN ready to read
            std::getline(std::cin, inputFilePath);
        }
        if (inputFilePath.empty()) {
            std::cerr << USAGE << std::endl;
            return EC_ERROR;
        }
    }
    else if (1 < argc) {
        inputFilePath = argv[1];
    }
    if (2 < argc) {
        outputFilePath << argv[2];
    }
    else {
        outputFilePath << inputFilePath << BYTE_CODE_FILE_SUFFIX;
    }
    std::cout << "Input file: " << inputFilePath << std::endl;
    JSRuntime * runtime = JS_NewRuntime(10 * 1024 * 1024, JS_NO_HELPER_THREADS);
    JSContext *context = JS_NewContext(runtime, 10240);
    JS_SetOptions(context, JSOPTION_TYPE_INFERENCE);
    JS_SetVersion(context, JSVERSION_LATEST);
    JS_SetOptions(context, JS_GetOptions(context) & ~JSOPTION_METHODJIT);
    JS_SetOptions(context, JS_GetOptions(context) & ~JSOPTION_METHODJIT_ALWAYS);
	JSObject* global = JS_NewGlobalObject(context, &GlobalClass, NULL);
    JS_SetErrorReporter(context, &ReportError);
	if (!JS_InitStandardClasses(context, global)) {
        return EC_ERROR;
    }
	JS::CompileOptions options(context);
    options.setSourcePolicy(JS::CompileOptions::NO_SOURCE);
    js::RootedObject rootedObject(context, global);
    std::cout << "Compiling ..." << std::endl;
    JSScript *script = JS::Compile(context, rootedObject, options, inputFilePath.c_str());
    if (!script) {
        return EC_ERROR;
    }
    void *data = NULL;
    uint32_t length = 0;
    std::cout << "Encoding ..." << std::endl;
    data = JS_EncodeScript(context, script, &length);
    if (!data) {
        return EC_ERROR;
    }
    if (WriteFile(outputFilePath.str(), data, length)) {
        std::cout << "Done! " << "Output file: " << outputFilePath.str() << std::endl;
        return EC_OK;
    }
    return EC_ERROR;
}

