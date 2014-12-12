
------------ MAP A0001 ------------

local map = {}

map.size = {width = 1600, height = 1000}
map.imageName = "MapA0001Bg.png"

local objects = {}

local object = {
    points = {
        {1115,  817}, {1058,  854}, { 992,  878}, { 902,  890}, { 863,  892}, { 811,  885},
        { 773,  871}, { 748,  849}, { 733,  828}, { 720,  810}, { 713,  790}, { 711,  771},
        { 717,  741}, { 727,  709}, { 748,  662}, { 778,  610}, { 811,  569}, { 846,  535},
        { 876,  501}, { 910,  454}, { 944,  405}, { 972,  352}, { 986,  330}, { 998,  322},
        {1020,  318}, {1047,  317}, {1090,  330}, {1142,  344}, {1181,  352}, {1230,  356},
        {1269,  352}, {1329,  331}, {1375,  304}, {1395,  281}, {1407,  254}, {1407,  231},
        {1404,  214}, {1395,  174}, {1385,  145}, {1373,  123},
     }
}
objects["path:1"] = object

----

local object = {
    points = {
        { 230,  559}, { 209,  521}, { 198,  493}, { 190,  472}, { 182,  438}, { 182,  404},
        { 187,  371}, { 196,  343}, { 210,  319}, { 229,  295}, { 255,  269}, { 283,  249},
        { 319,  235}, { 365,  227}, { 422,  221}, { 476,  225}, { 518,  233}, { 556,  245},
        { 581,  254}, { 598,  257}, { 626,  256}, { 649,  247}, { 692,  240}, { 742,  233},
        { 802,  233}, { 853,  238}, { 893,  252}, { 933,  267}, { 977,  288}, {1017,  301},
        {1053,  311}, {1090,  324}, {1123,  333}, {1162,  344}, {1206,  350}, {1250,  349},
        {1291,  340}, {1344,  317}, {1383,  289}, {1399,  262}, {1402,  243}, {1397,  193},
        {1388,  159}, {1370,  127},
     }
}
objects["path:2"] = object

----

local object = {
    radius = 51,
    tag = 0,
    x = 1375,
    y = 101,
}
objects["range:21"] = object

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
    x = 154,
    y = 241,
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
    defineId = "PlayerTower02",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower02L01",
    x = 588,
    y = 177,
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
    defineId = "PlayerTower01",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower01L01",
    x = 92,
    y = 330,
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
    defineId = "PlayerTower01",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower01L01",
    x = 79,
    y = 443,
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
    x = 698,
    y = 350,
}
objects["static:14"] = object

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
    y = 359,
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
    defineId = "PlayerTower01",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower01L01",
    x = 684,
    y = 946,
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
    x = 1008,
    y = 774,
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
    x = 853,
    y = 787,
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
    defineId = "PlayerTower01",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower01L01",
    x = 616,
    y = 799,
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
    x = 628,
    y = 662,
}
objects["static:20"] = object

----

local object = {
    defineId = "Building01",
    flipSprite = false,
    tag = 0,
    x = 1367,
    y = 91,
}
objects["static:3"] = object

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
    x = 872,
    y = 352,
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
    defineId = "PlayerTower02",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower02L01",
    x = 1009,
    y = 548,
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
    defineId = "PlayerTower02",
    flipSprite = false,
    tag = 0,
    towerId = "PlayerTower02L01",
    x = 310,
    y = 429,
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
    x = 424,
    y = 355,
}
objects["static:9"] = object

----

map.objects = objects

return map
