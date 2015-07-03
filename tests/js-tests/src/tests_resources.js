// Resources prefix
var s_resprefix = "";

var ccbjs = "";
if (!cc.sys.isNative)
{
    ccbjs = "../../js-tests/resjs/";
}

var s_pathGrossini = "Images/grossini.png";
var s_pathSister1 = "Images/grossinis_sister1.png";
var s_pathSister2 = "Images/grossinis_sister2.png";
var s_pathB1 = "Images/b1.png";
var s_pathB2 = "Images/b2.png";
var s_pathR1 = "Images/r1.png";
var s_pathR2 = "Images/r2.png";
var s_pathF1 = "Images/f1.png";
var s_pathF2 = "Images/f2.png";
var s_pathBlock = "Images/blocks.png";
var s_back = "Images/background.png";
var s_back1 = "Images/background1.png";
var s_back2 = "Images/background2.png";
var s_back3 = "Images/background3.png";
var s_stars1 = "Images/stars.png";
var s_stars2 = "Images/stars2.png";
var s_fire = "Images/fire.png";
var s_snow = "Images/snow.png";
var s_streak = "Images/streak.png";
var s_playNormal = "Images/btn-play-normal.png";
var s_playSelect = "Images/btn-play-selected.png";
var s_aboutNormal = "Images/btn-about-normal.png";
var s_aboutSelect = "Images/btn-about-selected.png";
var s_highNormal = "Images/btn-highscores-normal.png";
var s_highSelect = "Images/btn-highscores-selected.png";
var s_ball = "Images/ball.png";
var s_paddle = "Images/paddle.png";
var s_pathClose = "Images/close.png";
var s_menuItem = "Images/menuitemsprite.png";
var s_shapeModeMenuItem = "Images/shapemode.png";
var s_textureModeMenuItem = "Images/texturemode.png";
var s_MovementMenuItem = "Images/movement.png";
var s_sendScore = "Images/SendScoreButton.png";
var s_pressSendScore = "Images/SendScoreButtonPressed.png";
var s_power = "Images/powered.png";
var s_atlasTest = "Images/atlastest.png";
var s_stars2Grayscale = "Images/stars2-grayscale.png";
var s_starsGrayscale = "Images/stars-grayscale.png";
var s_grossini_dance_atlas = "Images/grossini_dance_atlas.png";
var s_piece = "Images/piece.png";
var s_grossini_dance_atlas_mono = "Images/grossini_dance_atlas-mono.png";
var s_lookup_desktop_plist = "Images/lookup-desktop.plist";
var s_lookup_mobile_plist = "Images/lookup-mobile.plist";
var s_lookup_html5_plist = "Images/lookup-html5.plist";

var s_grossini = "animations/grossini.png";
var s_grossini_gray = "animations/grossini_gray.png";
var s_grossini_blue = "animations/grossini_blue.png";
var s_grossini_aliases = "animations/grossini-aliases.png";
var s_dragon_animation = "animations/dragon_animation.png";
var s_ghosts = "animations/ghosts.png";
var s_grossini_family = "animations/grossini_family.png";

var s_tcc_issue_1 = "animations/tcc_issue_1.png";
var s_tcc_issue_2 = "animations/tcc_issue_2.png";
var s_tcc_issue_1_plist = "animations/tcc_issue_1.plist";
var s_tcc_issue_2_plist = "animations/tcc_issue_2.plist";

var s_Cowboy_json = "ccs-res/armature/Cowboy.ExportJson";
var s_Cowboy_plist = "ccs-res/armature/Cowboy0.plist";
var s_Cowboy_png = "ccs-res/armature/Cowboy0.png";
var s_hero_json = "ccs-res/armature/hero.ExportJson";
var s_hero0_plist = "ccs-res/armature/hero0.plist";
var s_hero0_png = "ccs-res/armature/hero0.png";
var s_horse_json = "ccs-res/armature/horse.ExportJson";
var s_horse0_plist = "ccs-res/armature/horse0.plist";
var s_horse0_png = "ccs-res/armature/horse0.png";
var s_bear_json = "ccs-res/armature/bear.ExportJson";
var s_bear0_plist = "ccs-res/armature/bear0.plist";
var s_bear0_png = "ccs-res/armature/bear0.png";
var s_blood_plist = "ccs-res/armature/blood.plist";
var s_HeroAnimation_json = "ccs-res/armature/HeroAnimation.ExportJson";
var s_HeroAnimation0_plist = "ccs-res/armature/HeroAnimation0.plist";
var s_HeroAnimation0_png = "ccs-res/armature/HeroAnimation0.png";
var s_cyborg_plist = "ccs-res/armature/cyborg.plist";
var s_cyborg_png = "ccs-res/armature/cyborg.png";
var s_cyborg_xml = "ccs-res/armature/cyborg.xml";
var s_Dragon_plist = "ccs-res/armature/Dragon.plist";
var s_Dragon_png = "ccs-res/armature/Dragon.png";
var s_Dragon_xml = "ccs-res/armature/Dragon.xml";
var s_knight_plist = "ccs-res/armature/knight.plist";
var s_knight_png = "ccs-res/armature/knight.png";
var s_knight_xml = "ccs-res/armature/knight.xml";
var s_robot_plist = "ccs-res/armature/robot.plist";
var s_robot_png = "ccs-res/armature/robot.png";
var s_robot_xml = "ccs-res/armature/robot.xml";
var s_weapon_plist = "ccs-res/armature/weapon.plist";
var s_weapon_png = "ccs-res/armature/weapon.png";
var s_weapon_xml = "ccs-res/armature/weapon.xml";
var s_testEasing_json = "ccs-res/armature/testEasing.ExportJson";
var s_testEasing0_plist = "ccs-res/armature/testEasing0.plist";
var s_testEasing0_png = "ccs-res/armature/testEasing0.png";

var s_s9s_blocks9 = "Images/blocks9ss.png";
var s_s9s_blocks9_plist = "Images/blocks9ss.plist";
var s_blocks9 = "Images/blocks9.png";

var s_s9s_ui = "Images/ui.png";
var s_s9s_ui_plist = "Images/ui.plist";

var s_boilingFoamPlist = "Images/BoilingFoam.plist";
var s_grossiniPlist = "animations/grossini.plist";
var s_grossini_grayPlist = "animations/grossini_gray.plist";
var s_grossini_bluePlist = "animations/grossini_blue.plist";
var s_grossini_aliasesPlist = "animations/grossini-aliases.plist";
var s_ghostsPlist = "animations/ghosts.plist";
var s_grossini_familyPlist = "animations/grossini_family.plist";
var s_animations2Plist = "animations/animations-2.plist";
var s_animationsPlist = "animations/animations.plist";

var s_helloWorld = "Images/HelloWorld.png";
var s_grossiniDance01 = "Images/grossini_dance_01.png";
var s_grossiniDance02 = "Images/grossini_dance_02.png";
var s_grossiniDance03 = "Images/grossini_dance_03.png";
var s_grossiniDance04 = "Images/grossini_dance_04.png";
var s_grossiniDance05 = "Images/grossini_dance_05.png";
var s_grossiniDance06 = "Images/grossini_dance_06.png";
var s_grossiniDance07 = "Images/grossini_dance_07.png";
var s_grossiniDance08 = "Images/grossini_dance_08.png";
var s_grossiniDance09 = "Images/grossini_dance_09.png";
var s_grossiniDance10 = "Images/grossini_dance_10.png";
var s_grossiniDance11 = "Images/grossini_dance_11.png";
var s_grossiniDance12 = "Images/grossini_dance_12.png";
var s_grossiniDance13 = "Images/grossini_dance_13.png";
var s_grossiniDance14 = "Images/grossini_dance_14.png";

var s_arrows = "Images/arrows.png";
var s_arrowsBar = "Images/arrowsBar.png";
var s_arrows_hd = "Images/arrows-hd.png";
var s_arrowsBar_hd = "Images/arrowsBar-hd.png";

// tilemaps resource
var s_tilesPng = "TileMaps/tiles.png";
var s_levelMapTga = "TileMaps/levelmap.tga";
var s_fixedOrthoTest2Png = "TileMaps/fixed-ortho-test2.png";
var s_hexaTilesPng = "TileMaps/hexa-tiles.png";
var s_isoTestPng = "TileMaps/iso-test.png";
var s_isoTest2Png = "TileMaps/iso-test2.png";
var s_isoPng = "TileMaps/iso.png";
var s_orthoTest1BwPng = "TileMaps/ortho-test1_bw.png";
var s_orthoTest1Png = "TileMaps/ortho-test1.png";
var s_tilesHdPng = "TileMaps/tiles-hd.png";
var s_tmwDesertSpacingHdPng = "TileMaps/tmw_desert_spacing-hd.png";
var s_tmwDesertSpacingPng = "TileMaps/tmw_desert_spacing.png";
var s_tileISOOffsetPng = "TileMaps/tile_iso_offset.png";
var s_tileISOOffsetTmx = "TileMaps/tile_iso_offset.tmx";

var s_fnTuffyBoldItalicCharmapPng = "fonts/tuffy_bold_italic-charmap.png";
var s_fpsImages = "fps_images.png";
var s_bitmapFontTest = "fonts/bitmapFontTest.png";
var s_bitmapFontTest2 = "fonts/bitmapFontTest2.png";
var s_bitmapFontTest3 = "fonts/bitmapFontTest3.png";
var s_bitmapFontTest4 = "fonts/bitmapFontTest4.png";
var s_bitmapFontTest5 = "fonts/bitmapFontTest5.png";
var s_konqa32 = "fonts/konqa32.png";
var s_konqa32_hd = "fonts/konqa32-hd.png";
var s_bitmapFontChinese = "fonts/bitmapFontChinese.png";
var s_arial16 = "fonts/arial16.png";
var s_larabie_16 = "fonts/larabie-16.png";
var s_larabie_16_hd = "fonts/larabie-16-hd.png";
var s_futura48 = "fonts/futura-48.png";
var s_arial_unicode_26 = "fonts/arial-unicode-26.png";

var s_bitmapFontTest_fnt = "fonts/bitmapFontTest.fnt";
var s_bitmapFontTest2_fnt = "fonts/bitmapFontTest2.fnt";
var s_bitmapFontTest3_fnt = "fonts/bitmapFontTest3.fnt";
var s_bitmapFontTest4_fnt = "fonts/bitmapFontTest4.fnt";
var s_bitmapFontTest5_fnt = "fonts/bitmapFontTest5.fnt";
var s_konqa32_fnt = "fonts/konqa32.fnt";
var s_konqa32_hd_fnt = "fonts/konqa32-hd.fnt";
var s_bitmapFontChinese_fnt = "fonts/bitmapFontChinese.fnt";
var s_arial16_fnt = "fonts/arial16.fnt";
var s_futura48_fnt = "fonts/futura-48.fnt";
var s_helvetica32_fnt = "fonts/helvetica-32.fnt";
var s_geneva32_fnt = "fonts/geneva-32.fnt";
var s_helvetica_helvetica_32_png = "fonts/helvetica-geneva-32.png";
var s_arial_unicode_26_fnt = "fonts/arial-unicode-26.fnt";
var s_markerFelt_fnt = "fonts/markerFelt.fnt";
var s_markerFelt_png = "fonts/markerFelt.png";
var s_markerFelt_hd_fnt = "fonts/markerFelt-hd.fnt";
var s_markerFelt_hd_png = "fonts/markerFelt-hd.png";

var s_larabie_16_plist = "fonts/larabie-16.plist";
var s_larabie_16_hd_plist = "fonts/larabie-16-hd.plist";
var s_tuffy_bold_italic_charmap = "fonts/tuffy_bold_italic-charmap.plist";
var s_tuffy_bold_italic_charmap_hd = "fonts/tuffy_bold_italic-charmap-hd.plist";

var s_particles = "Images/particles.png";
var s_particles_hd = "Images/particles-hd.png";
var s_texture512 = "Images/texture512x512.png";
var s_hole_effect_png = "Images/hole_effect.png";
var s_hole_stencil_png = "Images/hole_stencil.png";
var s_pathFog = "Images/Fog.png";
var s_circle_plist  = "Images/bugs/circle.plist";
var s_circle_png  = "Images/bugs/circle.png";

var s_extensions_background = "extensions/background.png";
var s_extensions_buttonBackground = "extensions/buttonBackground.png";
var s_extensions_button = "extensions/button.png";
var s_extensions_buttonHighlighted = "extensions/buttonHighlighted.png";
var s_extensions_ribbon = "extensions/ribbon.png";
var s_image_icon = "Images/Icon.png";
var s_html5_logo = "Images/cocos-html5.png";

var g_resources = [
    //global
    s_grossini_dance_atlas,
    s_pathFog,
    s_circle_plist,
    s_circle_png,
    s_texture512,
    s_hole_effect_png,
    s_hole_stencil_png,
    s_pathB1,
    s_pathB2,
    s_pathR1,
    s_pathR2,
    s_pathF1,
    s_pathF2,
    s_pathBlock,
    s_back3,
    s_fire,
    s_pathClose,
    s_pathGrossini,
    s_pathSister1,
    s_pathSister2,
    s_grossiniDance01,
    s_grossiniDance02,
    s_grossiniDance03,
    s_grossiniDance04,
    s_grossiniDance05,
    s_grossiniDance06,
    s_grossiniDance07,
    s_grossiniDance08,
    s_grossiniDance09,
    s_grossiniDance10,
    s_grossiniDance11,
    s_grossiniDance12,
    s_grossiniDance13,
    s_grossiniDance14,

    s_grossini,
    s_grossiniPlist,

    s_animations2Plist,
    s_grossini_blue,
    s_grossini_bluePlist,
    s_grossini_family,
    s_grossini_familyPlist,
    s_helloWorld,
    s_bitmapFontTest5,
    s_playNormal,
    s_playSelect,
    s_bitmapFontTest5_fnt,
    s_extensions_background,
    s_extensions_ribbon
];

var g_sprites = [
    s_piece,
    s_grossini_gray,
    s_grossini_blue,
    s_grossini_aliases,
    s_dragon_animation,
    s_ghosts,
    s_grossini_family,

    s_grossini_dance_atlas_mono,
    s_animationsPlist,
    s_grossini_grayPlist,
    s_grossini_bluePlist,
    s_grossini_aliasesPlist,
    s_ghostsPlist,
    s_grossini_familyPlist,

    s_tcc_issue_1_plist,
    s_tcc_issue_2_plist,
    s_tcc_issue_1,
    s_tcc_issue_2,

    s_s9s_blocks9_plist,
    s_s9s_blocks9,
    "Images/dot.png",
    "Images/wood.jpg"
];

var g_menu = [
    s_bitmapFontTest3_fnt,
    s_bitmapFontTest3,
    s_aboutNormal,
    s_aboutSelect,
    s_highNormal,
    s_highSelect,
    s_menuItem,
    s_sendScore,
    s_pressSendScore,
    s_fpsImages
];

var g_touches = [
    s_ball,
    s_paddle
];

var g_s9s_blocks = [
    s_s9s_blocks9_plist,
    s_s9s_blocks9,
    s_blocks9,
    s_s9s_ui,
    s_s9s_ui_plist
];

var g_opengl_resources = [
    //preload shader source
    ccbjs + "Shaders/example_Outline.fsh",
    ccbjs + "Shaders/example_Outline.vsh",
    ccbjs + "Shaders/example_Blur.fsh",
    ccbjs + "Shaders/example_ColorBars.fsh",
    ccbjs + "Shaders/example_ColorBars.vsh",
    ccbjs + "Shaders/example_Flower.fsh",
    ccbjs + "Shaders/example_Flower.vsh",
    ccbjs + "Shaders/example_Heart.fsh",
    ccbjs + "Shaders/example_Heart.vsh",
    ccbjs + "Shaders/example_Julia.fsh",
    ccbjs + "Shaders/example_Julia.vsh",
    ccbjs + "Shaders/example_Mandelbrot.fsh",
    ccbjs + "Shaders/example_Mandelbrot.vsh",
    ccbjs + "Shaders/example_Monjori.fsh",
    ccbjs + "Shaders/example_Monjori.vsh",
    ccbjs + "Shaders/example_Plasma.fsh",
    ccbjs + "Shaders/example_Plasma.vsh",
    ccbjs + "Shaders/example_Twist.fsh",
    ccbjs + "Shaders/example_Twist.vsh",

    "fonts/west_england-64.fnt",
    "fonts/west_england-64.png"
];

var g_label = [
    //s_atlasTest,
    s_bitmapFontTest,
    s_bitmapFontTest2,
    s_bitmapFontTest3,
    s_bitmapFontTest4,
    s_konqa32,
    s_konqa32_hd,
    s_bitmapFontChinese,
    s_arial16,
    s_larabie_16,
    s_larabie_16_hd,
    s_futura48,
    s_arial_unicode_26,
    s_fnTuffyBoldItalicCharmapPng,

    s_arrows,
    s_arrowsBar,
    s_arrows_hd,
    s_arrowsBar_hd,
    s_larabie_16_plist,
    s_larabie_16_hd_plist,
    s_tuffy_bold_italic_charmap,
    s_tuffy_bold_italic_charmap_hd,
    s_bitmapFontTest_fnt,
    s_bitmapFontTest2_fnt,
    s_bitmapFontTest3_fnt,
    s_bitmapFontTest4_fnt,
    s_konqa32_fnt,
    s_konqa32_hd_fnt,
    s_bitmapFontChinese_fnt,
    s_arial16_fnt,
    s_futura48_fnt,
    s_helvetica32_fnt,
    s_geneva32_fnt,
    s_helvetica_helvetica_32_png,
    s_arial_unicode_26_fnt,
    s_markerFelt_fnt,
    s_markerFelt_png,
    s_markerFelt_hd_fnt,
    s_markerFelt_hd_png,
    "fonts/strings.xml"
];

var g_transitions = [
    s_back1,
    s_back2
];

var g_box2d = [
    s_pathBlock
];

var g_cocosdeshion = [
    "background.mp3",
    "effect2.mp3"
    //"background.ogg",                        //one sound only, cc.audio can auto select other format to load if the sound format isn't supported on some browser.
    //"effect2.ogg"
];

var g_parallax = [
    "TileMaps/orthogonal-test2.tmx",
    s_fixedOrthoTest2Png,
    s_power,
    s_back
];

var g_eventDispatcher = [
    "Images/CyanSquare.png",
    "Images/MagentaSquare.png",
    "Images/YellowSquare.png",
    "Images/ball.png",
    s_extensions_button,
    s_extensions_buttonHighlighted,
    s_extensions_buttonBackground
];

var g_particle = [
    s_fpsImages,
    s_starsGrayscale,
    s_stars2Grayscale,
    s_textureModeMenuItem,
    s_shapeModeMenuItem,
    s_MovementMenuItem,
    s_stars1,
    s_stars2,
    s_snow,
    s_particles,
    s_particles_hd,
    "Particles/BoilingFoam.plist",
    "Particles/BurstPipe.plist",
    "Particles/Comet.plist",
    "Particles/debian.plist",
    "Particles/ExplodingRing.plist",
    "Particles/Flower.plist",
    "Particles/Galaxy.plist",
    "Particles/LavaFlow.plist",
    "Particles/Phoenix.plist",
    "Particles/SmallSun.plist",
    "Particles/SpinningPeas.plist",
    "Particles/Spiral.plist",
    "Particles/SpookyPeas.plist",
    "Particles/TestPremultipliedAlpha.plist",
    "Particles/Upsidedown.plist"
];

var g_fonts = [
    //@face-font for WebFonts
    {
        type:"font",
        name:"Thonburi",
        srcs:["../cpp-tests/Resources/fonts/Thonburi.eot", "../cpp-tests/Resources/fonts/Thonburi.ttf"]
    },
    {
        type:"font",
        name:"Schwarzwald Regular",
        srcs:["../cpp-tests/Resources/fonts/Schwarzwald_Regular.eot", "../cpp-tests/Resources/fonts/Schwarzwald Regular.ttf"]
    },
    {
        type:"font",
        name:"ThonburiBold",
        srcs:["../cpp-tests/Resources/fonts/ThonburiBold.eot", "../cpp-tests/Resources/fonts/ThonburiBold.ttf"]
    },
    {
        type:"font",
        name:"Courier New",
        srcs:["../cpp-tests/Resources/fonts/Courier New.eot", "../cpp-tests/Resources/fonts/Courier New.ttf"]
    }
];

var g_extensions = [
    s_image_icon,
    s_extensions_background,
    s_extensions_buttonBackground,
    s_extensions_button,
    s_extensions_buttonHighlighted,
    s_extensions_ribbon,

    //ccbi resource
    ccbjs + "ccb/HelloCocosBuilder.ccbi",
    ccbjs + "ccb/ccb/TestAnimations.ccbi",
    ccbjs + "ccb/ccb/TestAnimationsSub.ccbi",
    ccbjs + "ccb/ccb/TestButtons.ccbi",
    ccbjs + "ccb/ccb/TestHeader.ccbi",
    ccbjs + "ccb/ccb/TestLabels.ccbi",
    ccbjs + "ccb/ccb/TestMenus.ccbi",
    ccbjs + "ccb/ccb/TestParticleSystems.ccbi",
    ccbjs + "ccb/ccb/TestScrollViews.ccbi",
    ccbjs + "ccb/ccb/TestScrollViewsContentA.ccbi",
    ccbjs + "ccb/ccb/TestSprites.ccbi",

    ccbjs + "ccb/ccbParticleStars.png",
    ccbjs + "ccb/btn-test-0.png",
    ccbjs + "ccb/animated-grossini.png",
    ccbjs + "ccb/btn-a-0.png",
    ccbjs + "ccb/btn-a-1.png",
    ccbjs + "ccb/btn-a-2.png",
    ccbjs + "ccb/btn-b-0.png",
    ccbjs + "ccb/btn-b-1.png",
    ccbjs + "ccb/btn-b-2.png",
    ccbjs + "ccb/btn-back-0.png",
    ccbjs + "ccb/btn-back-1.png",
    ccbjs + "ccb/btn-test-0.png",
    ccbjs + "ccb/btn-test-1.png",
    ccbjs + "ccb/btn-test-2.png",
    ccbjs + "ccb/burst.png",
    ccbjs + "ccb/flower.jpg",
    ccbjs + "ccb/grossini-generic.png",
    ccbjs + "ccb/jungle.png",
    ccbjs + "ccb/jungle-left.png",
    ccbjs + "ccb/jungle-right.png",
    ccbjs + "ccb/logo.png",
    ccbjs + "ccb/logo-icon.png",
    ccbjs + "ccb/markerfelt24shadow.png",
    ccbjs + "ccb/particle-fire.png",
    ccbjs + "ccb/particle-smoke.png",
    ccbjs + "ccb/particle-snow.png",
    ccbjs + "ccb/particle-stars.png",
    ccbjs + "ccb/scale-9-demo.png",
    "extensions/green_edit.png",
    "extensions/orange_edit.png",
    "extensions/yellow_edit.png",
    "extensions/switch-mask.png",
    "extensions/switch-on.png",
    "extensions/switch-off.png",
    "extensions/switch-thumb.png",
    "extensions/sliderProgress.png",
    "extensions/sliderProgress2.png",
    "extensions/sliderThumb.png",
    "extensions/sliderTrack.png",
    "extensions/sliderTrack2.png",
    "extensions/stepper-minus.png",
    "extensions/stepper-plus.png",
    "extensions/potentiometerButton.png",
    "extensions/potentiometerProgress.png",
    "extensions/potentiometerTrack.png",
    "extensions/CCControlColourPickerSpriteSheet.plist",
    "extensions/CCControlColourPickerSpriteSheet.png",

    ccbjs + "ccb/markerfelt24shadow.fnt",

    ccbjs + "ccb/grossini-generic.plist",
    ccbjs + "ccb/animated-grossini.plist"
];

var g_cocoStudio = [
    //Armature
    s_Cowboy_json ,
    s_Cowboy_plist,
    s_Cowboy_png,
    s_hero_json,
    s_hero0_plist,
    s_hero0_png,
    s_horse_json,
    s_horse0_plist,
    s_horse0_png,
    s_bear_json,
    s_bear0_plist,
    s_bear0_png,
    s_blood_plist,
    s_HeroAnimation_json,
    s_HeroAnimation0_plist,
    s_HeroAnimation0_png,
    s_cyborg_plist ,
    s_cyborg_png ,
    s_cyborg_xml ,
    s_Dragon_plist ,
    s_Dragon_png ,
    s_Dragon_xml ,
    s_knight_plist ,
    s_knight_png ,
    s_knight_xml ,
    s_robot_plist ,
    s_robot_png ,
    s_robot_xml ,
    s_weapon_plist ,
    s_weapon_png ,
    s_weapon_xml ,
    s_testEasing_json ,
    s_testEasing0_plist ,
    s_testEasing0_png ,

//GUI
    "Particles/SmallSun.plist",
    "Images/b1.png",
    "Images/b2.png",
    "Images/f1.png",
    "Images/f2.png",
    "ccs-res/cocosui/UIEditorTest/UIButton/background.png",
    "ccs-res/cocosui/UIEditorTest/UIButton/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UIButton/buttonHighlighted.png",
    "ccs-res/cocosui/UIEditorTest/UIButton/button_n.png",
    "ccs-res/cocosui/UIEditorTest/UIButton/button_p.png",
    "ccs-res/cocosui/UIEditorTest/UIButton/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UIButton/Button_1.json",
    "ccs-res/cocosui/UIEditorTest/UICheckBox/background.png",
    "ccs-res/cocosui/UIEditorTest/UICheckBox/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UICheckBox/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UICheckBox/selected01.png",
    "ccs-res/cocosui/UIEditorTest/UICheckBox/selected02.png",
    "ccs-res/cocosui/UIEditorTest/UICheckBox/checkbox_1.json",
    "ccs-res/cocosui/UIEditorTest/UICheckBox/MainScene.json",
    "ccs-res/cocosui/UIEditorTest/UICheckBox/Default/CheckBox_Disable.png",
    "ccs-res/cocosui/UIEditorTest/UICheckBox/img/btn_music.png",
    "ccs-res/cocosui/UIEditorTest/UICheckBox/img/btn_sound_off.png",
    "ccs-res/cocosui/UIEditorTest/UIImageView/background.png",
    "ccs-res/cocosui/UIEditorTest/UIImageView/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UIImageView/buttonHighlighted.png",
    "ccs-res/cocosui/UIEditorTest/UIImageView/GUI/image.png",
    "ccs-res/cocosui/UIEditorTest/UIImageView/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UIImageView/ImageView_1.json",
    "ccs-res/cocosui/UIEditorTest/UILabelAtlas/background.png",
    "ccs-res/cocosui/UIEditorTest/UILabelAtlas/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UILabelAtlas/GUI/labelatlasimg.png",
    "ccs-res/cocosui/UIEditorTest/UILabelAtlas/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UILabelAtlas/labelatlas_1.json",
    "ccs-res/cocosui/UIEditorTest/UILabelBMFont/background.png",
    "ccs-res/cocosui/UIEditorTest/UILabelBMFont/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UILabelBMFont/GUI/missing-font.fnt",
    "ccs-res/cocosui/UIEditorTest/UILabelBMFont/GUI/missing-font.png",
    "ccs-res/cocosui/UIEditorTest/UILabelBMFont/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UILabelBMFont/labelbmfont_1.json",
    "ccs-res/cocosui/UIEditorTest/UILabel/background.png",
    "ccs-res/cocosui/UIEditorTest/UILabel/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UILabel/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UILabel/label_1.json",
    "ccs-res/cocosui/UIEditorTest/UILayout/BackgroundImage/background.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/BackgroundImage/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/BackgroundImage/button_n.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/BackgroundImage/button_p.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/BackgroundImage/GUI/image.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/BackgroundImage/Hello.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/BackgroundImage/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/BackgroundImage/selected01.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/BackgroundImage/selected02.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/BackgroundImage/backgroundimage_1.json",
    "ccs-res/cocosui/UIEditorTest/UILayout/Color/background.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Color/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Color/button_n.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Color/button_p.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Color/GUI/image.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Color/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Color/selected01.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Color/selected02.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Color/color_1.json",
    "ccs-res/cocosui/UIEditorTest/UILayout/Layout/background.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Layout/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Layout/button_n.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Layout/button_p.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Layout/GUI/image.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Layout/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Layout/selected01.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Layout/selected02.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Layout/layout_1.json",
    "ccs-res/cocosui/UIEditorTest/UILayout/Gradient_Color/background.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Gradient_Color/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Gradient_Color/button_n.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Gradient_Color/button_p.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Gradient_Color/GUI/image.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Gradient_Color/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Gradient_Color/selected01.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Gradient_Color/selected02.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Gradient_Color/gradient_color_1.json",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Horizontal_Layout/background.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Horizontal_Layout/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Horizontal_Layout/button_n.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Horizontal_Layout/button_p.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Horizontal_Layout/GUI/image.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Horizontal_Layout/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Horizontal_Layout/selected01.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Horizontal_Layout/selected02.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Horizontal_Layout/linear_horizontal.json",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Vertical_Layout/background.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Vertical_Layout/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Vertical_Layout/button_n.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Vertical_Layout/button_p.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Vertical_Layout/GUI/image.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Vertical_Layout/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Vertical_Layout/selected01.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Vertical_Layout/selected02.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Linear_Vertical_Layout/linear_vertical.json",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Location/background.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Location/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Location/button_n.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Location/button_p.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Location/GUI/image.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Location/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Location/selected01.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Location/selected02.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Location/relative_align_location.json",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Parent/background.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Parent/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Parent/button_n.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Parent/button_p.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Parent/GUI/image.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Parent/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Parent/selected01.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Parent/selected02.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Relative_Align_Parent/relative_align_parent.json",
    "ccs-res/cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage/background.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage/button_n.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage/button_p.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage/GUI/image.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage/selected01.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage/selected02.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage/slider_bar.png",
    "ccs-res/cocosui/UIEditorTest/UILayout/Scale9_BackgroundImage/scale9.json",
    "ccs-res/cocosui/UIEditorTest/UIListView/Horizontal/background.png",
    "ccs-res/cocosui/UIEditorTest/UIListView/Horizontal/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UIListView/Horizontal/button_p.png",
    "ccs-res/cocosui/UIEditorTest/UIListView/Horizontal/GUI/button.png",
    "ccs-res/cocosui/UIEditorTest/UIListView/Horizontal/GUI/image.png",
    "ccs-res/cocosui/UIEditorTest/UIListView/Horizontal/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UIListView/Horizontal/horizontal_1.json",
    "ccs-res/cocosui/UIEditorTest/UIListView/Vertical/background.png",
    "ccs-res/cocosui/UIEditorTest/UIListView/Vertical/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UIListView/Vertical/button_p.png",
    "ccs-res/cocosui/UIEditorTest/UIListView/Vertical/GUI/button.png",
    "ccs-res/cocosui/UIEditorTest/UIListView/Vertical/GUI/image.png",
    "ccs-res/cocosui/UIEditorTest/UIListView/Vertical/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UIListView/Vertical/vertical_1.json",
    "ccs-res/cocosui/UIEditorTest/UILoadingBar/background.png",
    "ccs-res/cocosui/UIEditorTest/UILoadingBar/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UILoadingBar/GUI/loadingbar.png",
    "ccs-res/cocosui/UIEditorTest/UILoadingBar/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UILoadingBar/loadingbar_1.json",
    "ccs-res/cocosui/UIEditorTest/UIPageView/background.png",
    "ccs-res/cocosui/UIEditorTest/UIPageView/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UIPageView/button_n.png",
    "ccs-res/cocosui/UIEditorTest/UIPageView/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UIPageView/pageview_1.json",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Both/background.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Both/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Both/button_n.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Both/button_p.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Both/GUI/image.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Both/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Both/selected01.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Both/selected02.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Both/both_1.json",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Horizontal/background.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Horizontal/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Horizontal/button_n.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Horizontal/button_p.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Horizontal/GUI/image.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Horizontal/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Horizontal/selected01.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Horizontal/selected02.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Horizontal/horizontal_1.json",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Vertical/background.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Vertical/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Vertical/button_n.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Vertical/button_p.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Vertical/GUI/image.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Vertical/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Vertical/selected01.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Vertical/selected02.png",
    "ccs-res/cocosui/UIEditorTest/UIScrollView/Vertical/vertical_1.json",
    "ccs-res/cocosui/UIEditorTest/UISlider/2014-1-26 11-42-09.png",
    "ccs-res/cocosui/UIEditorTest/UISlider/2014-1-26 11-43-52.png",
    "ccs-res/cocosui/UIEditorTest/UISlider/background.png",
    "ccs-res/cocosui/UIEditorTest/UISlider/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UISlider/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UISlider/silder_progressBar.png",
    "ccs-res/cocosui/UIEditorTest/UISlider/slider_bar.png",
    "ccs-res/cocosui/UIEditorTest/UISlider/slider_bar_button.png",
    "ccs-res/cocosui/UIEditorTest/UISlider/slider_1.json",
    "ccs-res/cocosui/UIEditorTest/UITextField/background.png",
    "ccs-res/cocosui/UIEditorTest/UITextField/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UITextField/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UITextField/textfield_1.json",
    "ccs-res/cocosui/UIEditorTest/UIWidgetAddNode/background.png",
    "ccs-res/cocosui/UIEditorTest/UIWidgetAddNode/buttonBackground.png",
    "ccs-res/cocosui/UIEditorTest/UIWidgetAddNode/ribbon.png",
    "ccs-res/cocosui/UIEditorTest/UIWidgetAddNode/widget_add_node.json",
    "background-music-aac.wav",
    "pew-pew-lei.wav",
    //Components
    "components/Player.png",
    "components/Projectile.png",
    "components/Target.png",
    //Scene
    "ccs-res/scenetest/ArmatureComponentTest/ArmatureComponentTest.json",
    "ccs-res/scenetest/ArmatureComponentTest/fishes/blowFish/Blowfish.ExportJson",
    "ccs-res/scenetest/ArmatureComponentTest/fishes/blowFish/Blowfish0.plist",
    "ccs-res/scenetest/ArmatureComponentTest/fishes/blowFish/Blowfish0.png",
    "ccs-res/scenetest/ArmatureComponentTest/fishes/Butterflyfish/Butterflyfish.ExportJson",
    "ccs-res/scenetest/ArmatureComponentTest/fishes/Butterflyfish/Butterflyfish0.plist",
    "ccs-res/scenetest/ArmatureComponentTest/fishes/Butterflyfish/Butterflyfish0.png",
    "ccs-res/scenetest/ArmatureComponentTest/Images/startMenuBG.png",
    "ccs-res/scenetest/AttributeComponentTest/AttributeComponentTest.json",
    "ccs-res/scenetest/AttributeComponentTest/grossinis_sister1.png",
    "ccs-res/scenetest/AttributeComponentTest/grossinis_sister2.png",
    "ccs-res/scenetest/AttributeComponentTest/PlayerAttribute.json",
    "ccs-res/scenetest/BackgroundComponentTest/BackgroundComponentTest.json",
    "ccs-res/scenetest/BackgroundComponentTest/Images/startMenuBG.png",
    "ccs-res/scenetest/BackgroundComponentTest/Misc/music_logo.mp3",
    "ccs-res/scenetest/BackgroundComponentTest/Misc/music_logo.wav",
    "ccs-res/scenetest/BackgroundComponentTest/Particles/qipao01.plist",
    "ccs-res/scenetest/BackgroundComponentTest/Particles/qipao01.png",
    "ccs-res/scenetest/BackgroundComponentTest/startMenu/Fish_UI/starMenuButton01.png",
    "ccs-res/scenetest/BackgroundComponentTest/startMenu/Fish_UI/starMenuButton02.png",
    "ccs-res/scenetest/BackgroundComponentTest/startMenu/Fish_UI/ui_logo_001-hd.png",
    "ccs-res/scenetest/BackgroundComponentTest/startMenu/startMenu_1.json",
    "ccs-res/scenetest/EffectComponentTest/CowBoy/Cowboy.ExportJson",
    "ccs-res/scenetest/EffectComponentTest/CowBoy/Cowboy0.plist",
    "ccs-res/scenetest/EffectComponentTest/CowBoy/Cowboy0.png",
    "ccs-res/scenetest/EffectComponentTest/EffectComponentTest.json",
    "ccs-res/scenetest/EffectComponentTest/pew-pew-lei.wav",
    "ccs-res/scenetest/LoadSceneEdtiorFileTest/fishes/blowFish/Blowfish.ExportJson",
    "ccs-res/scenetest/LoadSceneEdtiorFileTest/fishes/blowFish/Blowfish0.plist",
    "ccs-res/scenetest/LoadSceneEdtiorFileTest/fishes/blowFish/Blowfish0.png",
    "ccs-res/scenetest/LoadSceneEdtiorFileTest/fishes/Butterflyfish/Butterflyfish.ExportJson",
    "ccs-res/scenetest/LoadSceneEdtiorFileTest/fishes/Butterflyfish/Butterflyfish0.plist",
    "ccs-res/scenetest/LoadSceneEdtiorFileTest/fishes/Butterflyfish/Butterflyfish0.png",
    "ccs-res/scenetest/LoadSceneEdtiorFileTest/FishJoy2.json",
    "ccs-res/scenetest/LoadSceneEdtiorFileTest/Images/startMenuBG.png",
    "ccs-res/scenetest/LoadSceneEdtiorFileTest/Misc/music_logo.mp3",
    "ccs-res/scenetest/LoadSceneEdtiorFileTest/Misc/music_logo.wav",
    "ccs-res/scenetest/LoadSceneEdtiorFileTest/Particles/qipao01.plist",
    "ccs-res/scenetest/LoadSceneEdtiorFileTest/Particles/qipao01.png",
    "ccs-res/scenetest/LoadSceneEdtiorFileTest/startMenu/Fish_UI/starMenuButton01.png",
    "ccs-res/scenetest/LoadSceneEdtiorFileTest/startMenu/Fish_UI/starMenuButton02.png",
    "ccs-res/scenetest/LoadSceneEdtiorFileTest/startMenu/Fish_UI/ui_logo_001-hd.png",
    "ccs-res/scenetest/LoadSceneEdtiorFileTest/startMenu/startMenu_1.json",
    "ccs-res/scenetest/ParticleComponentTest/ParticleComponentTest.json",
    "ccs-res/scenetest/ParticleComponentTest/SmallSun.plist",
    "ccs-res/scenetest/ParticleComponentTest/Upsidedown.plist",
    "ccs-res/scenetest/SpriteComponentTest/grossinis_sister1.png",
    "ccs-res/scenetest/SpriteComponentTest/grossinis_sister2.png",
    "ccs-res/scenetest/SpriteComponentTest/SpriteComponentTest.json",
    "ccs-res/scenetest/TmxMapComponentTest/iso-test.png",
    "ccs-res/scenetest/TmxMapComponentTest/iso-test.tmx",
    "ccs-res/scenetest/TmxMapComponentTest/TmxMapComponentTest.json",
    "ccs-res/scenetest/TriggerTest/fishes/blowFish/Blowfish.ExportJson",
    "ccs-res/scenetest/TriggerTest/fishes/blowFish/Blowfish0.plist",
    "ccs-res/scenetest/TriggerTest/fishes/blowFish/Blowfish0.png",
    "ccs-res/scenetest/TriggerTest/fishes/Butterflyfish/Butterflyfish.ExportJson",
    "ccs-res/scenetest/TriggerTest/fishes/Butterflyfish/Butterflyfish0.plist",
    "ccs-res/scenetest/TriggerTest/fishes/Butterflyfish/Butterflyfish0.png",
    "ccs-res/scenetest/TriggerTest/Images/startMenuBG.png",
    "ccs-res/scenetest/TriggerTest/TriggerTest.json",
    "ccs-res/scenetest/UIComponentTest/fishes/blowFish/Blowfish.ExportJson",
    "ccs-res/scenetest/UIComponentTest/fishes/blowFish/Blowfish0.plist",
    "ccs-res/scenetest/UIComponentTest/fishes/blowFish/Blowfish0.png",
    "ccs-res/scenetest/UIComponentTest/fishes/Butterflyfish/Butterflyfish.ExportJson",
    "ccs-res/scenetest/UIComponentTest/fishes/Butterflyfish/Butterflyfish0.plist",
    "ccs-res/scenetest/UIComponentTest/fishes/Butterflyfish/Butterflyfish0.png",
    "ccs-res/scenetest/UIComponentTest/Images/startMenuBG.png",
    "ccs-res/scenetest/UIComponentTest/starMenuButton/starMenuButton.ExportJson",
    "ccs-res/scenetest/UIComponentTest/starMenuButton/starMenuButton0.plist",
    "ccs-res/scenetest/UIComponentTest/starMenuButton/starMenuButton0.png",
    "ccs-res/scenetest/UIComponentTest/UIComponentTest.json",

    //parser
    "ccs-res/cocosui/UIEditorTest/cocostudio1_3/CocostudioV1_3_1.ExportJson",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_3/CocostudioV1_30.plist",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_3/CocostudioV1_30.png",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_3/SmallSun.plist",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_3/GUI/labelatlasimg.png",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_3/GUI/missing-font.fnt",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_3/GUI/missing-font.png",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_4/Cocostudio1_4_1.ExportJson",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_4/Cocostudio1_40.plist",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_4/Cocostudio1_40.png",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_4/SmallSun.plist",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_4/GUI/labelatlasimg.png",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_4/GUI/missing-font.fnt",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_4/GUI/missing-font.png",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_5/Cocostudio1_5_1.ExportJson",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_5/Cocostudio1_50.plist",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_5/Cocostudio1_50.png",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_5/SmallSun.plist",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_5/GUI/labelatlasimg.png",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_5/GUI/missing-font.fnt",
    "ccs-res/cocosui/UIEditorTest/cocostudio1_5/GUI/missing-font.png",

    "ccs-res/cocosui/UIEditorTest/2.1/MainScene.json",
    "ccs-res/cocosui/UIEditorTest/2.1/plist1/Plist.plist",
    "ccs-res/cocosui/UIEditorTest/2.1/Plist/ui.plist",
    "ccs-res/cocosui/UIEditorTest/2.1/LoadingBar/pipe2.png",
    "ccs-res/cocosui/UIEditorTest/2.1/Slider/2013-8-13 15-44-11.png",
    "ccs-res/cocosui/UIEditorTest/2.1/Slider/teehanlax - iOS 6 - iPhone_slider01.png",
    "ccs-res/cocosui/UIEditorTest/2.1/particle/blue.plist",
    "ccs-res/cocosui/UIEditorTest/2.1/Default/Slider_Back.png",
    "ccs-res/cocosui/UIEditorTest/2.1/Default/SliderNode_Normal.png",
    "ccs-res/cocosui/UIEditorTest/2.1/Default/SliderNode_Press.png",
    "ccs-res/cocosui/UIEditorTest/2.1/Default/SliderNode_Disable.png",
    "ccs-res/cocosui/UIEditorTest/2.1/Default/Slider_PressBar.png",
    "ccs-res/cocosui/UIEditorTest/2.1/Default/defaultParticle.plist",
    "ccs-res/cocosui/UIEditorTest/2.1/Default/TextAtlas.png",
    "ccs-res/cocosui/UIEditorTest/2.1/fonts_weapon_001-hd.png",
    "ccs-res/cocosui/UIEditorTest/2.1/FNT/futura.fnt",
    "ccs-res/cocosui/UIEditorTest/2.1/Default/defaultBMFont.fnt",
    "ccs-res/cocosui/UIEditorTest/2.1/FNT/Heiti18.fnt",

    "Particles/BoilingFoam.plist",
    "ccs-res/cocosui/CustomImageViewTest/NewProject_2_1.ExportJson",
    "ccs-res/cocosui/CustomImageViewTest/NewProject_20.plist",
    "ccs-res/cocosui/CustomImageViewTest/NewProject_20.png"
];

var g_ui = [
    "ccs-res/cocosui/switch-mask.png",
    "ccs-res/cocosui/animationbuttonnormal.png",
    "ccs-res/cocosui/animationbuttonpressed.png",
    "ccs-res/cocosui/arrow.png",
    "ccs-res/cocosui/b11.png",
    "ccs-res/cocosui/backtotopnormal.png",
    "ccs-res/cocosui/backtotoppressed.png",
    "ccs-res/cocosui/bitmapFontTest2.fnt",
    "ccs-res/cocosui/bitmapFontTest2.png",
    "ccs-res/cocosui/button.png",
    "ccs-res/cocosui/buttonHighlighted.png",
    "ccs-res/cocosui/ccicon.png",
    "ccs-res/cocosui/check_box_active.png",
    "ccs-res/cocosui/check_box_active_disable.png",
    "ccs-res/cocosui/check_box_active_press.png",
    "ccs-res/cocosui/check_box_normal.png",
    "ccs-res/cocosui/check_box_normal_disable.png",
    "ccs-res/cocosui/check_box_normal_press.png",
    "ccs-res/cocosui/CloseNormal.png",
    "ccs-res/cocosui/CloseSelected.png",
    "ccs-res/cocosui/green_edit.png",
    "ccs-res/cocosui/grossini-aliases.png",
    "ccs-res/cocosui/Hello.png",
    "ccs-res/cocosui/labelatlas.png",
    "ccs-res/cocosui/loadingbar.png",
    {type:"font", name:"Marker Felt", srcs:["../cpp-tests/Resources/fonts/Marker Felt.ttf"]},
    "ccs-res/cocosui/scrollviewbg.png",
    "ccs-res/cocosui/slidbar.png",
    "ccs-res/cocosui/sliderballnormal.png",
    "ccs-res/cocosui/sliderballpressed.png",
    "ccs-res/cocosui/sliderProgress.png",
    "ccs-res/cocosui/sliderProgress2.png",
    "ccs-res/cocosui/sliderThumb.png",
    "ccs-res/cocosui/sliderTrack.png",
    "ccs-res/cocosui/sliderTrack2.png",
    "ccs-res/cocosui/slider_bar_active_9patch.png",
    "ccs-res/cocosui/UITest/b1.png",
    "ccs-res/cocosui/UITest/b2.png",
    "ccs-res/cocosui/UITest/background.png",
    "ccs-res/cocosui/UITest/buttonBackground.png",
    "ccs-res/cocosui/UITest/f1.png",
    "ccs-res/cocosui/UITest/f2.png",
    "ccs-res/cocosui/UITest/r1.png",
    "ccs-res/cocosui/UITest/r2.png",
    "ccs-res/cocosui/UITest/ribbon.png",
    "ccs-res/cocosui/UITest/UITest.json",
    "ccs-res/cocosui/100/100.ExportJson",
    "ccs-res/cocosui/100/1000.plist",
    "ccs-res/cocosui/100/1000.png",
    s_s9s_blocks9_plist,
    "ccs-res/cocosui/CloseSelected.png"
];

var g_performace = [
    "animations/crystals.plist",
    "animations/crystals.png",
    "fps_images.png",
    "Images/spritesheet1.png",
    "Images/sprites_test/sprite-0-0.png",
    "Images/sprites_test/sprite-0-1.png",
    "Images/sprites_test/sprite-0-2.png",
    "Images/sprites_test/sprite-0-3.png",
    "Images/sprites_test/sprite-0-4.png",
    "Images/sprites_test/sprite-0-5.png",
    "Images/sprites_test/sprite-0-6.png",
    "Images/sprites_test/sprite-0-7.png",
    "Images/sprites_test/sprite-1-0.png",
    "Images/sprites_test/sprite-1-1.png",
    "Images/sprites_test/sprite-1-2.png",
    "Images/sprites_test/sprite-1-3.png",
    "Images/sprites_test/sprite-1-4.png",
    "Images/sprites_test/sprite-1-5.png",
    "Images/sprites_test/sprite-1-6.png",
    "Images/sprites_test/sprite-1-7.png",
    "Images/sprites_test/sprite-2-0.png",
    "Images/sprites_test/sprite-2-1.png",
    "Images/sprites_test/sprite-2-2.png",
    "Images/sprites_test/sprite-2-3.png",
    "Images/sprites_test/sprite-2-4.png",
    "Images/sprites_test/sprite-2-5.png",
    "Images/sprites_test/sprite-2-6.png",
    "Images/sprites_test/sprite-2-7.png",
    "Images/sprites_test/sprite-3-0.png",
    "Images/sprites_test/sprite-3-1.png",
    "Images/sprites_test/sprite-3-2.png",
    "Images/sprites_test/sprite-3-3.png",
    "Images/sprites_test/sprite-3-4.png",
    "Images/sprites_test/sprite-3-5.png",
    "Images/sprites_test/sprite-3-6.png",
    "Images/sprites_test/sprite-3-7.png",
    "Images/sprites_test/sprite-4-0.png",
    "Images/sprites_test/sprite-4-1.png",
    "Images/sprites_test/sprite-4-2.png",
    "Images/sprites_test/sprite-4-3.png",
    "Images/sprites_test/sprite-4-4.png",
    "Images/sprites_test/sprite-4-5.png",
    "Images/sprites_test/sprite-4-6.png",
    "Images/sprites_test/sprite-4-7.png",
    "Images/sprites_test/sprite-5-0.png",
    "Images/sprites_test/sprite-5-1.png",
    "Images/sprites_test/sprite-5-2.png",
    "Images/sprites_test/sprite-5-3.png",
    "Images/sprites_test/sprite-5-4.png",
    "Images/sprites_test/sprite-5-5.png",
    "Images/sprites_test/sprite-5-6.png",
    "Images/sprites_test/sprite-5-7.png",
    "Images/sprites_test/sprite-6-0.png",
    "Images/sprites_test/sprite-6-1.png",
    "Images/sprites_test/sprite-6-2.png",
    "Images/sprites_test/sprite-6-3.png",
    "Images/sprites_test/sprite-6-4.png",
    "Images/sprites_test/sprite-6-5.png",
    "Images/sprites_test/sprite-6-6.png",
    "Images/sprites_test/sprite-6-7.png",
    "Images/sprites_test/sprite-7-0.png",
    "Images/sprites_test/sprite-7-1.png",
    "Images/sprites_test/sprite-7-2.png",
    "Images/sprites_test/sprite-7-3.png",
    "Images/sprites_test/sprite-7-4.png",
    "Images/sprites_test/sprite-7-5.png",
    "Images/sprites_test/sprite-7-6.png",
    "Images/sprites_test/sprite-7-7.png"
];

var g_tilemaps = [
    //image
    s_fixedOrthoTest2Png,
    s_hexaTilesPng,
    s_isoTestPng,
    s_isoTest2Png,
    s_isoPng,
    s_orthoTest1BwPng,
    s_orthoTest1Png,
    s_tilesHdPng,
    s_tmwDesertSpacingHdPng,
    s_tmwDesertSpacingPng,
    s_tilesPng,
    s_tileISOOffsetPng,
    s_tileISOOffsetTmx,
    "TileMaps/ortho-test2.png",

    //tmx
    "TileMaps/orthogonal-test1.tmx",
    "TileMaps/orthogonal-test1.tsx",
    "TileMaps/orthogonal-test2.tmx",
    "TileMaps/orthogonal-test3.tmx",
    "TileMaps/orthogonal-test4.tmx",
    "TileMaps/orthogonal-test4-hd.tmx",
    "TileMaps/orthogonal-test5.tmx",
    "TileMaps/orthogonal-test6.tmx",
    "TileMaps/orthogonal-test6-hd.tmx",
    "TileMaps/hexa-test.tmx",
    "TileMaps/iso-test.tmx",
    "TileMaps/iso-test1.tmx",
    "TileMaps/iso-test2.tmx",
    "TileMaps/iso-test2-uncompressed.tmx",
    "TileMaps/ortho-objects.tmx",
    "TileMaps/iso-test-objectgroup.tmx",
    "TileMaps/iso-test-zorder.tmx",
    "TileMaps/orthogonal-test-zorder.tmx",
    "TileMaps/iso-test-vertexz.tmx",
    "TileMaps/orthogonal-test-vertexz.tmx",
    "TileMaps/iso-test-movelayer.tmx",
    "TileMaps/orthogonal-test-movelayer.tmx",
    "TileMaps/iso-test-bug787.tmx",
    "TileMaps/test-object-layer.tmx",
    "TileMaps/ortho-tile-property.tmx",
    "TileMaps/ortho-rotation-test.tmx"
];

var g_spine = [
    "spine/spineboy.atlas",
    "spine/spineboy.json",
    "spine/spineboy.png",
    "spine/sprite.png",
    "spine/goblins-ffd.png",
    "spine/goblins-ffd.atlas",
    "spine/goblins-ffd.json"
];

var g_ccs2 = [
    "ActionTimeline/boy_1.csb",
    "ActionTimeline/armature/Cowboy0.plist",
    "ccs-res/cocosui/UIEditorTest/UILabelBMFont_Editor/GUI/missing-font.fnt",
    "ccs-res/cocosui/UIEditorTest/UILabelBMFont_Editor/GUI/missing-font.png"
];

if (!cc.sys.isNative) {
    var res = res || {};
    res.CCControlColourPickerSpriteSheet_plist = "extensions/CCControlColourPickerSpriteSheet.plist";
    res.CCControlColourPickerSpriteSheet_png = "extensions/CCControlColourPickerSpriteSheet.png";
}