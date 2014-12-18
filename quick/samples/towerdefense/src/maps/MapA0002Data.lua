
------------ MAP A0002 ------------

local map = {}

map.size = {width = 1600, height = 1000}
map.imageName = "MapA0002Bg.png"

local objects = {}

local object = {
    points = {
        { 121, 1005}, { 131,  969}, { 139,  943}, { 150,  914}, { 167,  846}, { 198,  775},
        { 230,  710}, { 269,  664}, { 311,  627}, { 358,  604}, { 429,  597}, { 490,  594},
        { 561,  589}, { 624,  587}, { 682,  585}, { 736,  577}, { 767,  566}, { 781,  554},
        { 788,  540}, { 792,  510}, { 787,  474}, { 783,  440}, { 783,  409}, { 796,  375},
        { 810,  360}, { 827,  345}, { 848,  336}, { 876,  333}, { 960,  333}, {1080,  342},
        {1177,  348}, {1247,  356}, {1284,  368}, {1294,  377}, {1303,  392}, {1305,  413},
        {1301,  442}, {1296,  469}, {1285,  501}, {1267,  540}, {1242,  576}, {1238,  590},
        {1244,  612}, {1255,  630}, {1273,  652}, {1293,  678}, {1310,  697}, {1330,  722},
        {1355,  750}, {1378,  789}, {1402,  842}, {1431,  895}, {1445,  926}, {1476, 1007},
     }
}
objects["path:1"] = object

----

local object = {
    points = {
        {1006,  924}, {1003,  878}, {1004,  845}, {1004,  807}, {1003,  758}, { 997,  697},
        { 988,  639}, { 960,  610}, { 927,  587}, { 871,  575}, { 829,  575}, { 786,  573},
        { 774,  575}, { 412,  590}, { 384,  582}, { 370,  567}, { 362,  551}, { 354,  531},
        { 344,  504}, { 335,  480}, { 332,  453}, { 331,  432}, { 333,  401}, { 342,  379},
        { 353,  359}, { 378,  347}, { 419,  341}, { 743,  345}, { 765,  340}, { 774,  333},
        { 779,  319}, { 781,  300}, { 784,  273}, { 786,  248}, { 788,  219}, { 791,  193},
        { 796,  166}, { 805,  143}, { 824,  126}, { 855,  119}, { 894,  118}, { 938,  124},
        { 984,  140}, {1274,  253}, {1291,  265}, {1300,  280}, {1305,  299}, {1305,  316},
        {1301,  341}, {1296,  350}, {1288,  355}, {1273,  355}, {1253,  355}, { 848,  339},
        { 823,  345}, { 806,  361}, { 799,  380}, { 794,  400}, { 791,  421}, { 790,  443},
        { 790,  468}, { 793,  489}, { 794,  508}, { 795,  525}, { 795,  544}, { 790,  560},
        { 779,  570}, { 758,  581}, { 716,  591}, { 663,  598}, { 604,  606}, { 587,  614},
        { 578,  623}, { 566,  645}, { 562,  669}, { 559,  694}, { 554,  728}, { 554,  785},
        { 550,  863}, { 550,  886}, { 549,  940}, { 546, 1000},
     }
}
objects["path:2"] = object

----

local object = {
    radius = 32,
    tag = 0,
    x = 1490,
    y = 1100,
}
objects["range:28"] = object

----

local object = {
    radius = 38,
    tag = 0,
    x = 542,
    y = 1111,
}
objects["range:30"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower01",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower01L01",
    x = 454,
    y = 465,
}
objects["static:1"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower02",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower02L01",
    x = 693,
    y = 246,
}
objects["static:10"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower01",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower01L01",
    x = 901,
    y = 250,
}
objects["static:11"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower02",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower02L01",
    x = 982,
    y = 265,
}
objects["static:12"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower02",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower02L01",
    x = 1069,
    y = 275,
}
objects["static:13"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower01",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower01L01",
    x = 674,
    y = 708,
}
objects["static:15"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower02",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower02L01",
    x = 782,
    y = 686,
}
objects["static:16"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower01",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower01L01",
    x = 886,
    y = 703,
}
objects["static:17"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower01",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower01L01",
    x = 1121,
    y = 718,
}
objects["static:18"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower02",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower02L01",
    x = 1369,
    y = 597,
}
objects["static:19"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower02",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower02L01",
    x = 559,
    y = 473,
}
objects["static:2"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower02",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower02L01",
    x = 436,
    y = 722,
}
objects["static:20"] = object

----

local object = {
    defineId = "IncreaseHp",
    flipSprite = false,
    tag = 0,
    x = 132,
    y = 960,
}
objects["static:21"] = object

----

local object = {
    defineId = "Building01",
    flipSprite = false,
    tag = 0,
    x = 93,
    y = 364,
}
objects["static:25"] = object

----

local object = {
    defineId = "Building01",
    flipSprite = false,
    tag = 0,
    x = 1487,
    y = 290,
}
objects["static:26"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower01",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower01L01",
    x = 660,
    y = 466,
}
objects["static:3"] = object

----

local object = {
    defineId = "IncreaseHp",
    flipSprite = false,
    tag = 0,
    x = 1004,
    y = 988,
}
objects["static:31"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower02",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower02L01",
    x = 916,
    y = 475,
}
objects["static:4"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower01",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower01L01",
    x = 999,
    y = 472,
}
objects["static:5"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower01",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower01L01",
    x = 1086,
    y = 475,
}
objects["static:6"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower02",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower02L01",
    x = 1166,
    y = 479,
}
objects["static:7"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower01",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower01L01",
    x = 541,
    y = 267,
}
objects["static:8"] = object

----

local object = {
    behaviors = {
        "CampBehavior",
        "CollisionBehavior",
        "DecorateBehavior",
        "DestroyedBehavior",
        "FireBehavior",
        "TowerBehavior",
    },
    campId = 1,
    collisionEnabled = true,
    decorationsMore = {
    },
    defineId = "PlayerTower01",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower01L01",
    x = 619,
    y = 250,
}
objects["static:9"] = object

----

map.objects = objects

return map
