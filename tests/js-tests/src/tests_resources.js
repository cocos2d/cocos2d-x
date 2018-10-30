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

// Resources prefix
var s_resprefix = "";

var ccbjs = "";
// js-test use cpptest resource in debug mode , and in the release mode, console will copy the resource into the res dir
// so the respath will modify to res,
if (!cc.sys.isNative)
{
    if (cc.game.config && cc.game.config[cc.game.CONFIG_KEY.engineDir] !== "frameworks/cocos2d-html5") {
        ccbjs = "../../js-tests/resjs/";
    }
    else
    {
        ccbjs = "";
    }

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

// Issue CustomIssueAnimationsWithOnlyOneFrame
var s_testIssueAnimationsWithOnlyOneFrame_json = "ccs-res/cocosui/CustomIssueAnimationsWithOnlyOneFrame/AnimationsWithOnlyOneFrame.json";
var s_testIssueAnimationsWithOnlyOneFrame_png = "ccs-res/cocosui/CustomIssueAnimationsWithOnlyOneFrame/TheDigitalSpell.png";

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
    s_back2,
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
    s_back1
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
    s_pathClose,
    "ccs-res/cocosui/CloseSelected.png",
    "ccs-res/cocosui/green_edit.png",
    s_grossini_aliases,
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
    "spine/spineboy-ess.json",
    "spine/spineboy.png",
    "spine/sprite.png",
    "spine/goblins.png",
    "spine/goblins.atlas",
    "spine/goblins-pro.json"
];

if (!cc.sys.isNative) {
    var res = res || {};
    res.CCControlColourPickerSpriteSheet_plist = "extensions/CCControlColourPickerSpriteSheet.plist";
    res.CCControlColourPickerSpriteSheet_png = "extensions/CCControlColourPickerSpriteSheet.png";
}
