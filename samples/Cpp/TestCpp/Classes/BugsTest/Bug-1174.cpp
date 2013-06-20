//
// Bug-1174
// http://code.google.com/p/cocos2d-iphone/issues/detail?id=1174
//

#include "Bug-1174.h"

int check_for_error( Point p1, Point p2, Point p3, Point p4, float s, float t );

int check_for_error( Point p1, Point p2, Point p3, Point p4, float s, float t )
{
    //    the hit point is        p3 + t * (p4 - p3);
    //    the hit point also is    p1 + s * (p2 - p1);
    
    Point p4_p3 = ccpSub( p4, p3);
    Point p4_p3_t = ccpMult(p4_p3, t);
    Point hitPoint1 = ccpAdd( p3, p4_p3_t);
    
    Point p2_p1 = ccpSub( p2, p1);
    Point p2_p1_s = ccpMult(p2_p1, s);
    Point hitPoint2 = ccpAdd( p1, p2_p1_s);
    
    // Since float has rounding errors, only check if diff is < 0.05
    if( (fabs( hitPoint1.x - hitPoint2.x) > 0.1f) || ( fabs(hitPoint1.y - hitPoint2.y) > 0.1f) )
    {
        CCLog("ERROR: (%f,%f) != (%f,%f)", hitPoint1.x, hitPoint1.y, hitPoint2.x, hitPoint2.y);
        return 1;
    }

    return 0;
}

bool Bug1174Layer::init()
{
    if (BugsTestBaseLayer::init())
    {
//         // seed
//         srand(0);

        Point A,B,C,D,p1,p2,p3,p4;
        float s,t;
        
        int err=0;
        int ok=0;
        
        //
        // Test 1.
        //
        CCLog("Test1 - Start");
        for( int i=0; i < 10000; i++)
        {
            // A | b
            // -----
            // c | d
            float ax = CCRANDOM_0_1() * -5000;
            float ay = CCRANDOM_0_1() * 5000;

            // a | b
            // -----
            // c | D
            float dx = CCRANDOM_0_1() * 5000;
            float dy = CCRANDOM_0_1() * -5000;

            // a | B
            // -----
            // c | d
            float bx = CCRANDOM_0_1() * 5000;
            float by = CCRANDOM_0_1() * 5000;
            
            // a | b
            // -----
            // C | d
            float cx = CCRANDOM_0_1() * -5000;
            float cy = CCRANDOM_0_1() * -5000;
            
            A = ccp(ax,ay);
            B = ccp(bx,by);
            C = ccp(cx,cy);
            D = ccp(dx,dy);
            if( ccpLineIntersect( A, D, B, C, &s, &t) ) {
                if( check_for_error(A, D, B, C, s, t) )
                    err++;
                else
                    ok++;
            }
        }
        CCLog("Test1 - End. OK=%i, Err=%i", ok, err);

        //
        // Test 2.
        //
        CCLog("Test2 - Start");
        
        p1 = ccp(220,480);
        p2 = ccp(304,325);
        p3 = ccp(264,416);
        p4 = ccp(186,416);
        s = 0.0f;
        t = 0.0f;
        if( ccpLineIntersect(p1, p2, p3, p4, &s, &t) )
            check_for_error(p1, p2, p3, p4, s,t );

        CCLog("Test2 - End");

        
        //
        // Test 3
        //
        CCLog("Test3 - Start");
        
        ok=0;
        err=0;
        for( int i=0;i<10000;i++)
        {
            // A | b
            // -----
            // c | d
            float ax = CCRANDOM_0_1() * -500;
            float ay = CCRANDOM_0_1() * 500;
            p1 = ccp(ax,ay);
            
            // a | b
            // -----
            // c | D
            float dx = CCRANDOM_0_1() * 500;
            float dy = CCRANDOM_0_1() * -500;
            p2 = ccp(dx,dy);
            
            
            //////
            
            float y = ay - ((ay - dy) /2.0f);

            // a | b
            // -----
            // C | d
            float cx = CCRANDOM_0_1() * -500;
            p3 = ccp(cx,y);
            
            // a | B
            // -----
            // c | d
            float bx = CCRANDOM_0_1() * 500;
            p4 = ccp(bx,y);

            s = 0.0f;
            t = 0.0f;
            if( ccpLineIntersect(p1, p2, p3, p4, &s, &t) ) {
                if( check_for_error(p1, p2, p3, p4, s,t ) )
                    err++;
                else
                    ok++;
            }
        }
        
        CCLog("Test3 - End. OK=%i, err=%i", ok, err);
        return true;
    }

    return false;
}
