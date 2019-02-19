/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/


#include "ConfigurationTest.h"
#include "../testResource.h"
#include "cocos2d.h"

USING_NS_CC;

ConfigurationTests::ConfigurationTests()
{
    ADD_TEST_CASE(ConfigurationLoadConfig);
    ADD_TEST_CASE(ConfigurationQuery);
    ADD_TEST_CASE(ConfigurationInvalid);
    ADD_TEST_CASE(ConfigurationDefault);
    ADD_TEST_CASE(ConfigurationSet);
}

std::string ConfigurationBase::title() const
{
    return "Configuration Test";
}

//------------------------------------------------------------------
//
// ConfigurationLoadConfig
//
//------------------------------------------------------------------
void ConfigurationLoadConfig::onEnter()
{
    ConfigurationBase::onEnter();

	Configuration::getInstance()->loadConfigFile("configs/config-test-ok.plist");
    std::string config = Configuration::getInstance()->getInfo();
    log("%s\n", config.c_str());
}

std::string ConfigurationLoadConfig::subtitle() const
{
    return "Loading config file manually. See console";
}

//------------------------------------------------------------------
//
// ConfigurationQuery
//
//------------------------------------------------------------------
void ConfigurationQuery::onEnter()
{
    ConfigurationBase::onEnter();

	log("cocos2d version: %s", Configuration::getInstance()->getValue("cocos2d.x.version").asString().c_str() );
	log("OpenGL version: %s", Configuration::getInstance()->getValue("gl.version").asString().c_str() );
}

std::string ConfigurationQuery::subtitle() const
{
    return "Check the console";
}

//------------------------------------------------------------------
//
// ConfigurationInvalid
//
//------------------------------------------------------------------
void ConfigurationInvalid::onEnter()
{
    ConfigurationBase::onEnter();

	Configuration::getInstance()->loadConfigFile("configs/config-test-invalid.plist");
}

std::string ConfigurationInvalid::subtitle() const
{
    return "Loading an invalid config file";
}

//------------------------------------------------------------------
//
// ConfigurationDefault
//
//------------------------------------------------------------------
void ConfigurationDefault::onEnter()
{
    ConfigurationBase::onEnter();

    std::string c_value = Configuration::getInstance()->getValue("invalid.key", Value("no key")).asString();
	if( c_value != "no key" )
		log("1. Test failed!");
	else
		log("1. Test OK!");

	bool b_value = Configuration::getInstance()->getValue("invalid.key", Value(true)).asBool();
	if( ! b_value )
		log("2. Test failed!");
	else
		log("2. Test OK!");

	double d_value = Configuration::getInstance()->getValue("invalid.key", Value(42.42)).asDouble();
	if( d_value != 42.42 )
		log("3. Test failed!");
	else
		log("3. Test OK!");

}

std::string ConfigurationDefault::subtitle() const
{
    return "Tests defaults values";
}

//------------------------------------------------------------------
//
// ConfigurationSet
//
//------------------------------------------------------------------
void ConfigurationSet::onEnter()
{
    ConfigurationBase::onEnter();

	Configuration *conf = Configuration::getInstance();

	conf->setValue("this.is.an.int.value", Value(10) );
	conf->setValue("this.is.a.bool.value", Value(true) );
	conf->setValue("this.is.a.string.value", Value("hello world") );

	auto str = conf->getInfo();
    log("%s\n", str.c_str());
}

std::string ConfigurationSet::subtitle() const
{
    return "Tests setting values manually";
}

