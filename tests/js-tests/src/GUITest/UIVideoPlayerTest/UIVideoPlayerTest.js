var UIVideoPlayerTest = UIScene.extend({

    onEnter: function(){
        UIScene.prototype.onEnter.call(this);

        var video = new ccui.VideoPlayer("cocosvideo.mp4");
        video.setContentSize(320, 240);
        video.setPosition(800/2, 450/2);
        video.setScale(0.5);
        window.video = video;
        this.addChild(video);

        video.setEventListener(ccui.VideoPlayer.EventType.PLAYING, function(sender){
            cc.log("VideoPlayer PLAYING");
        });
        video.setEventListener(ccui.VideoPlayer.EventType.PAUSED, function(sender){
            cc.log("VideoPlayer PAUSED");
        });
        video.setEventListener(ccui.VideoPlayer.EventType.STOPPED, function(sender){
            cc.log("VideoPlayer STOPPED");
        });
        video.setEventListener(ccui.VideoPlayer.EventType.COMPLETED, function(sender){
            cc.log("VideoPlayer COMPLETED");
        });

        var playState = new cc.LabelTTF("PLAY State", "Thonburi", 28);
        playState.setPosition(400, 350);
        this.addChild(playState);

        ccui.VideoPlayer.EventType = {
            PLAYING: "play",
            PAUSED: "pause",
            STOPPED: "stop",
            COMPLETED: "complete"
        };
        var list = [
            { name: "PLAYURL", func: function(){
                cc.log("play!");
                playState.setString("play");
                video.setURL("http://benchmark.cocos2d-x.org/cocosvideo.mp4");
                video.play();
            }},
            { name: "PLAYLOCAL", func: function(){
                cc.log("play!");
                playState.setString("play");
                video.setURL("cocosvideo.mp4");
                video.play();
            }},
            { name: "STOP", func: function(){
                cc.log("stop!");
                playState.setString("stop");
                video.stop();
            }},
            { name: "PAUSE", func: function(){
                cc.log("pause!");
                playState.setString("pause");
                video.pause();
            }},
            { name: "RESUME", func: function(){
                cc.log("resume!");
                playState.setString("resume");
                video.resume();
            }},
            { name: "SEEKTO", func: function(){
                var sec = ((Math.random() * 59) * 100 | 0) / 100;
                cc.log("seekTo %f sec!", sec);
                video.seekTo(sec);
            }},
            { name: "ISPLAYING", func: function(){
                cc.log("isPlaying!");
                playState.setString("isPlaying");
                cc.log(video.isPlaying());
            }},
            { name: "Full Screen", func: function(){
                cc.log("setFullScreenEnabled!");
                playState.setString("setFullScreenEnabled");
                video.setFullScreenEnabled(true);
            }},
            { name: "Scale", func: function(){
                var scale = ((Math.random() * 0.5 + 0.2) * 100 | 0) / 100;
                cc.log("setScale(%f)!", scale);
                video.setScale(scale);
            }},
            { name: "AnchorPoint 0 / 1", func: function(){
                var anp = video.getAnchorPoint();
                if(anp.x === 1)
                    video.setAnchorPoint(0, 0);
                else
                    video.setAnchorPoint(1, 1);
            }},
            { name: "AnchorPoint 0.5", func: function(){
                video.setAnchorPoint(0.5, 0.5);
            }}
        ];

        var layer = this;
        list.forEach(function(item, i){
            var but = new ccui.Button();
            but.setPosition( 140 + (i / 6 | 0) * 500, 300 - (i % 6) * 35);
            but.setTitleText(item.name);
            but.setZoomScale(0.3);
            but.setPressedActionEnabled(true);
            but.addClickEventListener(item.func);
            layer.addChild(but);
        });

    }

});