var UIVideoPlayerTest = UIScene.extend({

    onEnter: function(){
        UIScene.prototype.onEnter.call(this);

        var video = new ccui.VideoPlayer("res/cocosui/UITest/movie.mp4");
        video.setContentSize(320, 240);
        video.setPosition(800/2, 450/2);
        video.setScale(0.5);
        window.video = video;
        this.addChild(video);

        var list = [
            { name: "PLAY", func: function(){
                    cc.log("play!");
                    video.play();
             }},
            { name: "STOP", func: function(){
                    cc.log("stop!");
                    video.stop();
            }},
            { name: "PAUSE", func: function(){
                    cc.log("pause!");
                    video.pause();
            }},
            { name: "RESUME", func: function(){
                    cc.log("resume!");
                    video.resume();
            }},
            { name: "SEEKTO", func: function(){
                var sec = ((Math.random() * 3) * 100 | 0) / 100;
                    cc.log("seekTo %f sec!", sec);
                    video.seekTo(sec);
            }},
            { name: "ISPLAYING", func: function(){
                    cc.log("isPlaying!");
                    cc.log(video.isPlaying());
            }},
            { name: "Full Screen", func: function(){
                    cc.log("setFullScreenEnabled!");
                    video.setFullScreenEnabled();
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
            but.setPosition( 140 + (i / 5 | 0) * 500, 300 - (i % 5) * 35);
            but.setTitleText(item.name);
            but.setZoomScale(0.3);
            but.setPressedActionEnabled(true);
            but.addClickEventListener(item.func);
            layer.addChild(but);
        });

    }

});