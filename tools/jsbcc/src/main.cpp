//
//  main.cpp
//  jsbcc
//
//  Created by sun zhuoshi on 4/28/13.
//  Copyright (c) 2013 sunzhuoshi. All rights reserved.
//

#include <iostream>
#include <sstream>

#include <stdio.h>

#ifdef WIN32
#include <Winsock2.h>
#define STDIN_FILENO 0
#else
#include <unistd.h>
#include <sys/select.h>
#endif

#include "jsapi.h"

#ifdef WIN32
const char *USAGE = "Usage: jsbcc input_js_file [byte_code_file]";
#else
const char *USAGE = "Usage: jsbcc input_js_file [byte_code_file]\n"\
                    "       Or\n"\
                    "       ls *.js | jsbcc -p";
#endif
const char *BYTE_CODE_FILE_EXT = ".jsc";

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

std::string RemoveFileExt(const std::string &filePath) {
    size_t pos = filePath.rfind('.');
    if (0 < pos) {
        return filePath.substr(0, pos);
    }
    else {
        return filePath;
    }
}

bool CompileFile(const std::string &inputFilePath, const std::string &outputFilePath) {
    bool result = false;
    std::string ofp;
    if (!outputFilePath.empty()) {
        ofp = outputFilePath;
    }
    else {
        ofp = RemoveFileExt(inputFilePath) + BYTE_CODE_FILE_EXT;
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
	if (JS_InitStandardClasses(context, global)) {

        JS::CompileOptions options(context);
        options.setUTF8(true);
        options.setSourcePolicy(JS::CompileOptions::NO_SOURCE);
        js::RootedObject rootedObject(context, global);
        std::cout << "Compiling ..." << std::endl;
        JSScript *script = JS::Compile(context, rootedObject, options, inputFilePath.c_str());
        if (script) {
            void *data = NULL;
            uint32_t length = 0;
            std::cout << "Encoding ..." << std::endl;
            data = JS_EncodeScript(context, script, &length);
            if (data) {
                if (WriteFile(ofp, data, length)) {
                    std::cout << "Done! " << "Output file: " << ofp << std::endl;
                    result = true;
                }
            }
        }
        
    }
    if (context) {
        JS_DestroyContext(context);
        context = NULL;
    }
    if (runtime) {
        JS_DestroyRuntime(runtime);
        runtime = NULL;
    }
    return result;
}

int main(int argc, const char * argv[])
{
    std::string inputFilePath, outputFilePath;
    if (1 == argc) {
        std::cerr << USAGE << std::endl;
        return EC_ERROR;
    }
    else {
        if (1 < argc) {            
            if (std::string(argv[1]) == "-p") { // pipe mode
                fd_set fds;
                FD_ZERO (&fds);
                FD_SET (STDIN_FILENO, &fds);
                int result = select (STDIN_FILENO + 1, &fds, NULL, NULL, NULL); // infinite wait
                if (result) { // STDIN ready to read
                    std::string line;
                    while (std::getline(std::cin, line)) {
                        if (!line.empty()) {
                            CompileFile(line, "");
                        }
                    }
                    return EC_OK;
                }
                else {
                    std::cerr << "Failed to read from pipe" << std::endl;
                    return EC_ERROR;
                }
            }
            else {
                inputFilePath = argv[1];
            }
        }
        if (2 < argc) {
            outputFilePath = argv[2];
        }
        if (CompileFile(inputFilePath, outputFilePath)) {
            return EC_OK;
        }
        return EC_ERROR;
    }
}
