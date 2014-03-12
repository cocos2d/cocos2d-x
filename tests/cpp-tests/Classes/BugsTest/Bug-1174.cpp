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
    
    auto p4_p3 = p4 - p3;
    auto p4_p3_t = p4_p3 * t;
    auto hitPoint1 = p3 + p4_p3_t;
    
    auto p2_p1 = p2 - p1;
    auto p2_p1_s = p2_p1 * s;
    auto hitPoint2 = p1 + p2_p1_s;
    
    // Since float has rounding errors, only check if diff is < 0.05
    if( (fabs( hitPoint1.x - hitPoint2.x) > 0.1f) || ( fabs(hitPoint1.y - hitPoint2.y) > 0.1f) )
    {
        log("ERROR: (%f,%f) != (%f,%f)", hitPoint1.x, hitPoint1.y, hitPoint2.x, hitPoint2.y);
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
        log("Test1 - Start");
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
            
            A = Point(ax,ay);
            B = Point(bx,by);
            C = Point(cx,cy);
            D = Point(dx,dy);
            if( Point::isLineIntersect( A, D, B, C, &s, &t) ) {
                if( check_for_error(A, D, B, C, s, t) )
                    err++;
                else
                    ok++;
            }
        }
        log("Test1 - End. OK=%i, Err=%i", ok, err);

        //
        // Test 2.
        //
        log("Test2 - Start");
        
        p1 = Point(220,480);
        p2 = Point(304,325);
        p3 = Point(264,416);
        p4 = Point(186,416);
        s = 0.0f;
        t = 0.0f;
        if( Point::isLineIntersect(p1, p2, p3, p4, &s, &t) )
            check_for_error(p1, p2, p3, p4, s,t );

        log("Test2 - End");

        
        //
        // Test 3
        //
        log("Test3 - Start");
        
        ok=0;
        err=0;
        for( int i=0;i<10000;i++)
        {
            // A | b
            // -----
            // c | d
            float ax = CCRANDOM_0_1() * -500;
            float ay = CCRANDOM_0_1() * 500;
            p1 = Point(ax,ay);
            
            // a | b
            // -----
            // c | D
            float dx = CCRANDOM_0_1() * 500;
            float dy = CCRANDOM_0_1() * -500;
            p2 = Point(dx,dy);
            
            
            //////
            
            float y = ay - ((ay - dy) /2.0f);

            // a | b
            // -----
            // C | d
            float cx = CCRANDOM_0_1() * -500;
            p3 = Point(cx,y);
            
            // a | B
            // -----
            // c | d
            float bx = CCRANDOM_0_1() * 500;
            p4 = Point(bx,y);

            s = 0.0f;
            t = 0.0f;
            if( Point::isLineIntersect(p1, p2, p3, p4, &s, &t) ) {
                if( check_for_error(p1, p2, p3, p4, s,t ) )
                    err++;
                else
                    ok++;
            }
        }
        
        log("Test3 - End. OK=%i, err=%i", ok, err);
        return true;
    }

    return false;
}
