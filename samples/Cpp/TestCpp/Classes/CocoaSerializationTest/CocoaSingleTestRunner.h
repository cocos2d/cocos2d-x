#ifndef SINGLETESTRUNNER_H
#define SINGLETESTRUNNER_H

#include "cocos2d.h"

/**
 * For one test case, add dictionary to resources and pass resource name.
 *
 * This function will read dictionary, write it to "<test name.out", read again
 * and compare with original. Comparison failure gives nice trace.
 *
 * @return false if failed, failure message printed with CCLOG.
 */
bool runCocoaSerializationTestCase(const std::string &resourcePath);

#endif // SINGLETESTRUNNER_H
