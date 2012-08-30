// this is to test the test bindings :)

var simple1 = new SimpleNativeClass();

// testing the getters and the constructor (that set some fields)
cc.log("someField: " + simple1.someField);
cc.log("someOtherField: " + simple1.someOtherField);
cc.log("anotherMoreComplexField: " + simple1.anotherMoreComplexField);

// testing the setters
simple1.someField = 1313;
simple1.someOtherField = 999;
simple1.anotherMoreComplexField = "this is a js string";

cc.log("someField: " + simple1.someField);
cc.log("someOtherField: " + simple1.someOtherField);
cc.log("anotherMoreComplexField: " + simple1.anotherMoreComplexField);

// testing std::string conversion

cc.log("someProcessing: " + simple1.doSomeProcessing("this is some js string", "this is another javascript string"));


var another = new AnotherClass();
// testing the getters and the constructor (that set some fields)
cc.log("justOneField: " + another.justOneField);
cc.log("aPublicField: " + another.aPublicField);

// testing setters, the setter for justOneField should not work (since it's not defined correctly in the native class)
another.justOneField = 8888;
another.aPublicField = 6667;
cc.log("justOneField: " + another.justOneField);
cc.log("aPublicField: " + another.aPublicField);

// should print something in stderr
another.doSomethingSimple();

//should print the enum
cc.log("enum: " + someThingEnumerated.kValue1);
cc.log("enum: " + someThingEnumerated.kValue2);
cc.log("enum: " + someThingEnumerated.kValue3);
cc.log("enum: " + someThingEnumerated.kValue4);
