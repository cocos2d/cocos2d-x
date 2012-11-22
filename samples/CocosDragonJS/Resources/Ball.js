/****************************************************************************
 Copyright (c) 2010-2012 cocos2d-x.org
 Copyright (c) 2008-2010 Ricardo Quesada
 Copyright (c) 2011      Zynga Inc.

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
var Ball = cc.Sprite.extend({
    _velocity:cc.p(0,0),
    _radius:0,
    ctor: function() {
        cc.associateWithNative( this, cc.Sprite );
        this.init();
    },
    init: function() {
        this._super();
    },
    radius:function () {
        return this._radius;
    },
    setRadius:function (rad) {
        this._radius = rad;
    },
    move:function (delta) {
        this.setPosition(cc.pAdd(this.getPosition(), cc.pMult(this._velocity, delta)));
        var winSize = cc.Director.getInstance().getWinSize();
        if (this.getPosition().x > winSize.width - this.radius()) {
            this.setPosition(cc.p(winSize.width - this.radius(), this.getPosition().y));
            this._velocity.x *= -1;
        } else if (this.getPosition().x < this.radius()) {
            this.setPosition(cc.p(this.radius(), this.getPosition().y));
            this._velocity.x *= -1;
        }
    },
    collideWithPaddle:function (paddle) {
        var paddleRect = paddle.rect();

        paddleRect.origin.x += paddle.getPosition().x;
        paddleRect.origin.y += paddle.getPosition().y;

        var lowY = cc.Rect.CCRectGetMinY(paddleRect);
        var midY = cc.Rect.CCRectGetMidY(paddleRect);
        var highY = cc.Rect.CCRectGetMaxY(paddleRect);

        var leftX = cc.Rect.CCRectGetMinX(paddleRect);
        var rightX = cc.Rect.CCRectGetMaxX(paddleRect);

        if ((this.getPosition().x > leftX) && (this.getPosition().x < rightX)) {
            var hit = false;
            var angleOffset = 0.0;
            if ((this.getPositionY() > midY) && (this.getPositionY() <= (highY + this.radius()))) {
                this.setPosition(cc.p(this.getPosition().x, highY + this.radius()));
                hit = true;
                angleOffset = Math.PI / 2;
            } else if (this.getPosition().y < midY && this.getPosition().y >= lowY - this.radius()) {
                this.setPosition(cc.p(this.getPosition().x, lowY - this.radius()));
                hit = true;
                angleOffset = -Math.PI / 2;
            }

            if (hit) {
                var hitAngle = cc.pToAngle(cc.pSub(paddle.getPosition(), this.getPosition())) + angleOffset;

                var scalarVelocity = cc.pLength(this._velocity) * 1.00000005;
                var velocityAngle = -cc.pToAngle(this._velocity) + 0.00000005 * hitAngle;
                //this._velocity = -this._velocity.y;
                this._velocity = cc.pMult(cc.pForAngle(velocityAngle), scalarVelocity);
            }
        }
    },
    setVelocity:function (velocity) {
        this._velocity = velocity;
    },
    getVelocity:function () {
        return this._velocity;
    }
});

Ball.ballWithTexture = function (texture) {
    log(Ball);
    var ball = new Ball();
    ball.initWithTexture(texture);
    if (texture instanceof cc.Texture2D)
        ball.setRadius(texture.getContentSize().width / 2);
    else if ((texture instanceof HTMLImageElement) || (texture instanceof HTMLCanvasElement))
        ball.setRadius(texture.width / 2);
    return ball;
};
