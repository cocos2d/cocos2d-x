--[[

Copyright (c) 2011-2014 chukong-inc.com

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

]]

--[[--

将 cocos2d-x 对象放入名字空间

]]

local c = cc

-- actions
c.Follow                       = CCFollow
c.Speed                        = CCSpeed

c.OrbitCamera                  = CCOrbitCamera

c.CardinalSplineTo             = CCCardinalSplineTo
c.CardinalSplineBy             = CCCardinalSplineBy
c.CatmullRomTo                 = CCCatmullRomTo
c.CatmullRomBy                 = CCCatmullRomBy

c.EaseRateAction               = CCEaseRateAction
c.EaseIn                       = CCEaseIn
c.EaseOut                      = CCEaseOut
c.EaseInOut                    = CCEaseInOut
c.EaseExponentialIn            = CCEaseExponentialIn
c.EaseExponentialOut           = CCEaseExponentialOut
c.EaseExponentialInOut         = CCEaseExponentialInOut
c.EaseSineIn                   = CCEaseSineIn
c.EaseSineOut                  = CCEaseSineOut
c.EaseSineInOut                = CCEaseSineInOut
c.EaseElastic                  = CCEaseElastic
c.EaseElasticIn                = CCEaseElasticIn
c.EaseElasticOut               = CCEaseElasticOut
c.EaseElasticInOut             = CCEaseElasticInOut
c.EaseBounce                   = CCEaseBounce
c.EaseBounceIn                 = CCEaseBounceIn
c.EaseBounceOut                = CCEaseBounceOut
c.EaseBounceInOut              = CCEaseBounceInOut
c.EaseBackIn                   = CCEaseBackIn
c.EaseBackOut                  = CCEaseBackOut
c.EaseBackInOut                = CCEaseBackInOut

c.TiledGrid3DAction            = CCTiledGrid3DAction
c.AccelDeccelAmplitude         = CCAccelDeccelAmplitude
c.AccelAmplitude               = CCAccelAmplitude
c.DeccelAmplitude              = CCDeccelAmplitude

c.StopGrid                     = CCStopGrid
c.ReuseGrid                    = CCReuseGrid

c.Waves3D                      = CCWaves3D
c.FlipX3D                      = CCFlipX3D
c.FlipY3D                      = CCFlipY3D
c.Lens3D                       = CCLens3D
c.Ripple3D                     = CCRipple3D
c.Shaky3D                      = CCShaky3D
c.Liquid                       = CCLiquid
c.Waves                        = CCWaves
c.Twirl                        = CCTwirl

c.Show                         = CCShow
c.Hide                         = CCHide
c.ToggleVisibility             = CCToggleVisibility
c.RemoveSelf                   = CCRemoveSelf
c.FlipX                        = CCFlipX
c.FlipY                        = CCFlipY
c.Place                        = CCPlace
c.CallFunc                     = CCCallFunc
c.CallFuncN                    = CCCallFuncN

c.Sequence                     = CCSequence
c.Repeat                       = CCRepeat
c.RepeatForever                = CCRepeatForever
c.Spawn                        = CCSpawn
c.RotateTo                     = CCRotateTo
c.RotateBy                     = CCRotateBy
c.MoveBy                       = CCMoveBy
c.MoveTo                       = CCMoveTo
c.SkewTo                       = CCSkewTo
c.SkewBy                       = CCSkewBy
c.JumpBy                       = CCJumpBy
c.JumpTo                       = CCJumpTo
c.BezierBy                     = CCBezierBy
c.BezierTo                     = CCBezierTo
c.ScaleTo                      = CCScaleTo
c.ScaleBy                      = CCScaleBy
c.Blink                        = CCBlink
c.FadeIn                       = CCFadeIn
c.FadeOut                      = CCFadeOut
c.FadeTo                       = CCFadeTo
c.TintTo                       = CCTintTo
c.TintBy                       = CCTintBy
c.DelayTime                    = CCDelayTime
c.ReverseTime                  = CCReverseTime
c.Animate                      = CCAnimate
c.TargetedAction               = CCTargetedAction

c.PageTurn3D                   = CCPageTurn3D

c.ProgressTo                   = CCProgressTo
c.ProgressFromTo               = CCProgressFromTo

c.ShakyTiles3D                 = CCShakyTiles3D
c.ShatteredTiles3D             = CCShatteredTiles3D
c.ShuffleTiles                 = CCShuffleTiles
c.FadeOutTRTiles               = CCFadeOutTRTiles
c.FadeOutBLTiles               = CCFadeOutBLTiles
c.FadeOutUpTiles               = CCFadeOutUpTiles
c.FadeOutDownTiles             = CCFadeOutDownTiles
c.TurnOffTiles                 = CCTurnOffTiles
c.WavesTiles3D                 = CCWavesTiles3D
c.JumpTiles3D                  = CCJumpTiles3D
c.SplitRows                    = CCSplitRows
c.SplitCols                    = CCSplitCols

c.ActionManager                = CCActionManager


-- base nodes
c.AtlasNode                    = CCAtlasNode
c.Node                         = CCNode

-- cocoa
c.Array                        = CCArray
c.Dictionary                   = CCDictionary
c.Set                          = CCSet
c.Point                        = CCPoint
c.Size                         = CCSize
c.Rect                         = CCRect
c.PointArray                   = CCPointArray

c.Bool                         = CCBool
c.Double                       = CCDouble
c.Float                        = CCFloat
c.Integer                      = CCInteger
c.String                       = CCString

-- draw nodes
c.DrawNode                     = CCDrawNode

c.CircleShape                  = CCCircleShape
c.RectShape                    = CCRectShape
c.PointShape                   = CCPointShape
c.PolygonShape                 = CCPolygonShape

-- label nodes
c.LabelAtlas                   = CCLabelAtlas
c.LabelBMFont                  = CCLabelBMFont
c.LabelTTF                     = CCLabelTTF

-- layers scenes transitions nodes
c.Layer                        = CCLayer
c.LayerColor                   = CCLayerColor
c.LayerGradient                = CCLayerGradient
c.LayerMultiplex               = CCLayerMultiplex
c.Scene                        = CCScene

c.TransitionSceneOriented      = CCTransitionSceneOriented
c.TransitionRotoZoom           = CCTransitionRotoZoom
c.TransitionJumpZoom           = CCTransitionJumpZoom
c.TransitionMoveInL            = CCTransitionMoveInL
c.TransitionMoveInR            = CCTransitionMoveInR
c.TransitionMoveInT            = CCTransitionMoveInT
c.TransitionMoveInB            = CCTransitionMoveInB
c.TransitionSlideInL           = CCTransitionSlideInL
c.TransitionSlideInR           = CCTransitionSlideInR
c.TransitionSlideInB           = CCTransitionSlideInB
c.TransitionSlideInT           = CCTransitionSlideInT
c.TransitionShrinkGrow         = CCTransitionShrinkGrow
c.TransitionFlipX              = CCTransitionFlipX
c.TransitionFlipY              = CCTransitionFlipY
c.TransitionFlipAngular        = CCTransitionFlipAngular
c.TransitionZoomFlipX          = CCTransitionZoomFlipX
c.TransitionZoomFlipY          = CCTransitionZoomFlipY
c.TransitionZoomFlipAngular    = CCTransitionZoomFlipAngular
c.TransitionFade               = CCTransitionFade
c.TransitionCrossFade          = CCTransitionCrossFade
c.TransitionTurnOffTiles       = CCTransitionTurnOffTiles
c.TransitionSplitCols          = CCTransitionSplitCols
c.TransitionSplitRows          = CCTransitionSplitRows
c.TransitionFadeTR             = CCTransitionFadeTR
c.TransitionFadeBL             = CCTransitionFadeBL
c.TransitionFadeUp             = CCTransitionFadeUp
c.TransitionFadeDown           = CCTransitionFadeDown
c.TransitionPageTurn           = CCTransitionPageTurn
c.TransitionProgressRadialCCW  = CCTransitionProgressRadialCCW
c.TransitionProgressRadialCW   = CCTransitionProgressRadialCW
c.TransitionProgressHorizontal = CCTransitionProgressHorizontal
c.TransitionProgressVertical   = CCTransitionProgressVertical
c.TransitionProgressInOut      = CCTransitionProgressInOut
c.TransitionProgressOutIn      = CCTransitionProgressOutIn

-- menu nodes
c.Menu                         = CCMenu
c.MenuItem                     = CCMenuItem
c.MenuItemLabel                = CCMenuItemLabel
c.MenuItemAtlasFont            = CCMenuItemAtlasFont
c.MenuItemFont                 = CCMenuItemFont
c.MenuItemSprite               = CCMenuItemSprite
c.MenuItemImage                = CCMenuItemImage
c.MenuItemToggle               = CCMenuItemToggle

-- misc nodes
c.ClippingNode                 = CCClippingNode
c.ClippingRegionNode           = CCClippingRegionNode
c.MotionStreak                 = CCMotionStreak
c.ProgressTimer                = CCProgressTimer
c.RenderTexture                = CCRenderTexture

-- particle nodes
c.ParticleBatchNode            = CCParticleBatchNode
c.ParticleSystemQuad           = CCParticleSystemQuad

-- platform
c.Application                  = CCApplication
c.Device                       = CCDevice
c.EGLView                      = CCEGLView
c.FileUtils                    = CCFileUtils
c.Image                        = CCImage
c.Time                         = CCTime

-- sprite nodes
c.AnimationFrame               = CCAnimationFrame
c.Animation                    = CCAnimation
c.AnimationCache               = CCAnimationCache
c.GraySprite                   = CCGraySprite
c.Sprite                       = CCSprite
c.SpriteBatchNode              = CCSpriteBatchNode
c.SpriteFrame                  = CCSpriteFrame
c.SpriteFrameCache             = CCSpriteFrameCache

-- support
c.UserDefault                  = CCUserDefault
c.NotificationCenter           = CCNotificationCenter

-- text input node
c.TextFieldTTF                 = CCTextFieldTTF

-- textures
c.Texture2D                    = CCTexture2D
c.TextureCache                 = CCTextureCache

-- tilemap parallax nodes
c.ParallaxNode                 = CCParallaxNode
c.TileMapAtlas                 = CCTileMapAtlas
c.TMXLayer                     = CCTMXLayer
c.TMXObjectGroup               = CCTMXObjectGroup
c.TMXTiledMap                  = CCTMXTiledMap
c.TMXLayerInfo                 = CCTMXLayerInfo
c.TMXTilesetInfo               = CCTMXTilesetInfo
c.TMXMapInfo                   = CCTMXMapInfo

-- cocos2dx
c.Configuration                = CCConfiguration
c.Director                     = CCDirector
c.Scheduler                    = CCScheduler

