cocos.log("welcome to cocos2d-x-javascript");

var Test = function () {
};
Test.prototype.assertNum = 0;
Test.prototype.assertEqual = function (expr, target, str) {
	this.assertNum++;
	str = str || "";
	if (expr != target) {
		throw "assert failed: " + str + " (" + expr + ")";
	}
};
Test.prototype.assertFloatEqual = function (num1, target, str) {
	this.assertNum++;
	str = str || "";
	if (Math.abs(num1 - target) > 0.000001) {
		throw "assert failed: " + str + " (" + expr + ")";
	}
};
Test.prototype.setup = function () {};
Test.prototype.run = function () {
	cocos.log("Test started");
	var ok = 0, fail = 0, failed = [];
	for (var key in this) {
		if (key.match(/^test/)) {
			try {
				this[key]();
				ok++;
			} catch (e) {
				failed.push(this.assertNum + ": " + e);
				fail++;
			}
		}
	}
	cocos.log("total asserts: " + this.assertNum);
	cocos.log("tests [ok]: " + ok);
	cocos.log("tests [fail]: " + fail);
	cocos.log(failed.join("\n"));
};

var GeometryTest = function () {
};
GeometryTest.prototype = Object.create(Test.prototype);

GeometryTest.prototype.test_point1 = function () {
	var pt = new cocos.Point();
	this.assertEqual(pt.x, 0, "pt.x == 0");
	this.assertEqual(pt.y, 0, "pt.y == 0");

	pt.x = 0.5;
	pt.y = 13.37;
	this.assertFloatEqual(pt.x, 0.5, "pt.x == 0.5");
	this.assertFloatEqual(pt.y, 13.37, "pt.y == 13.37");
};

GeometryTest.prototype.test_point2 = function () {
	var pt1 = new cocos.Point();
	var pt2 = new cocos.Point();
	pt1.x = 100.50;
	pt2.y = 99;
	pt1.y = pt1.x + pt2.y;
	this.assertFloatEqual(pt1.y, 100.50 + 99, "pt1.y == 100.50 + 99");
};

GeometryTest.prototype.test_size1 = function () {
	var sz1 = new cocos.Size();
	this.assertEqual(sz1.width, 0, "sz1.width == 0");
	this.assertEqual(sz1.height, 0, "sz1.height == 0");

	sz1.width = 99.2323;
	sz1.height = 13.3700;
	this.assertFloatEqual(sz1.width, 99.2323, "sz1.width == 99.2323");
	this.assertFloatEqual(sz1.height, 13.3700, "sz1.height == 13.3700");
};

GeometryTest.prototype.test_rect1 = function () {
	var rect = new cocos.Rect();
	var orig = rect.origin;
	this.assertEqual(orig.x, 0, "orig.x == 0");
	this.assertEqual(orig.y, 0, "orig.y == 0");
	orig.x = 51343.034;

	var orig2 = rect.origin;
	this.assertFloatEqual(orig2.x, orig.x, "orig2.x == orig.x");
};

GeometryTest.prototype.test_rect2 = function () {
	var rect1 = new cocos.Rect();
	var rect2 = new cocos.Rect();
	var pt1 = new cocos.Point();
	var pt2 = rect1.origin;

	pt2.x = 500; pt2.y = 900;
	this.assertEqual(pt2.x, 500, "pt2.x == 500");
	this.assertEqual(pt2.y, 900, "pt2.y == 900");

	pt1.x = 13.37; pt1.y = 13.13;
	rect2.origin = pt1;
	pt2 = rect2.origin;

	this.assertFloatEqual(pt2.x, 13.37, "pt2.x == 13.37");
	this.assertFloatEqual(pt2.y, 13.13, "pt2.y == 13.13");
};

test = new GeometryTest();
test.run();

// small performance test

var totalIter = 10000;
var rect = new cocos.Rect();
var pt = new cocos.Point();
var sum;

sum = 0;
for (var i=0; i < totalIter; i++) {
	pt.x = i;
	var startTime = Date.now();
	rect.origin = pt;
	var endTime = Date.now();
	sum += (endTime - startTime) / 1000.0;
}
cocos.log(totalIter + "\t" + sum);

cocos.log("END OF TEST");
