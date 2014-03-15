#include <assert.h>
#include <stdio.h>
#include "ray2.h"

void kmRay2Fill(kmRay2* ray, kmScalar px, kmScalar py, kmScalar vx, kmScalar vy) {
    ray->start.x = px;
    ray->start.y = py;    
    ray->dir.x = vx;
    ray->dir.y = vy;
}

kmBool kmRay2IntersectLineSegment(const kmRay2* ray, const kmVec2* p1, const kmVec2* p2, kmVec2* intersection) {
    
    kmScalar x1 = ray->start.x;
    kmScalar y1 = ray->start.y;
    kmScalar x2 = ray->start.x + ray->dir.x;
    kmScalar y2 = ray->start.y + ray->dir.y;
    kmScalar x3 = p1->x;
    kmScalar y3 = p1->y;
    kmScalar x4 = p2->x;
    kmScalar y4 = p2->y;

    kmScalar denom = (y4 -y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
    
    //If denom is zero, the lines are parallel
    if(denom > -kmEpsilon && denom < kmEpsilon) {
        return KM_FALSE;
    }
    
    kmScalar ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / denom;
    kmScalar ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / denom;
    
    kmScalar x = x1 + ua * (x2 - x1);
    kmScalar y = y1 + ua * (y2 - y1);
    
    if((0.0 <= ua) && (ua <= 1.0) && (0.0 <= ub) && (ub <= 1.0)) {
        intersection->x = x;
        intersection->y = y;
        
        return KM_TRUE;    
    }

    return KM_FALSE;        
}

void calculate_line_normal(kmVec2 p1, kmVec2 p2, kmVec2 other_point, kmVec2* normal_out) {
    /*
        A = (3,4)
        B = (2,1)
        C = (1,3)

        AB = (2,1) - (3,4) = (-1,-3)
        AC = (1,3) - (3,4) = (-2,-1)
        N = n(AB) = (-3,1)
        D = dot(N,AC) = 6 + -1 = 5

        since D > 0:
          N = -N = (3,-1)
    */
    
    kmVec2 edge, other_edge;
    kmVec2Subtract(&edge, &p2, &p1);
    kmVec2Subtract(&other_edge, &other_point, &p1);
    kmVec2Normalize(&edge, &edge);
    kmVec2Normalize(&other_edge, &other_edge);
    
    kmVec2 n;
    n.x = edge.y;
    n.y = -edge.x;
    
    kmScalar d = kmVec2Dot(&n, &other_edge);
    if(d > 0.0f) {
        n.x = -n.x;
        n.y = -n.y;
    }

    normal_out->x = n.x;
    normal_out->y = n.y;
    kmVec2Normalize(normal_out, normal_out);
}

kmBool kmRay2IntersectTriangle(const kmRay2* ray, const kmVec2* p1, const kmVec2* p2, const kmVec2* p3, kmVec2* intersection, kmVec2* normal_out, kmScalar* distance_out) {
    kmVec2 intersect;
    kmVec2 final_intersect;
    kmVec2 normal;
    kmScalar distance = 10000.0f;
    kmBool intersected = KM_FALSE;
 
    if(kmRay2IntersectLineSegment(ray, p1, p2, &intersect)) {
        kmVec2 tmp;
        kmScalar this_distance = kmVec2Length(kmVec2Subtract(&tmp, &intersect, &ray->start));
        kmVec2 this_normal;
        calculate_line_normal(*p1, *p2, *p3, &this_normal);                                   
        if(this_distance < distance && kmVec2Dot(&this_normal, &ray->dir) < 0.0f) {
            final_intersect.x = intersect.x;
            final_intersect.y = intersect.y;
            distance = this_distance;
            kmVec2Assign(&normal, &this_normal);
            intersected = KM_TRUE;                        
        }
    }
    
    if(kmRay2IntersectLineSegment(ray, p2, p3, &intersect)) {
        kmVec2 tmp;
        kmScalar this_distance = kmVec2Length(kmVec2Subtract(&tmp, &intersect, &ray->start));
        
        kmVec2 this_normal;
        calculate_line_normal(*p2, *p3, *p1, &this_normal);
        
        if(this_distance < distance && kmVec2Dot(&this_normal, &ray->dir) < 0.0f) {
            final_intersect.x = intersect.x;
            final_intersect.y = intersect.y;
            distance = this_distance;
            kmVec2Assign(&normal, &this_normal);
            intersected = KM_TRUE;                                
        }   
    }
    
    if(kmRay2IntersectLineSegment(ray, p3, p1, &intersect)) {

        kmVec2 tmp;
        kmScalar this_distance = kmVec2Length(kmVec2Subtract(&tmp, &intersect, &ray->start));
        
        kmVec2 this_normal;
        calculate_line_normal(*p3, *p1, *p2, &this_normal);                           
        if(this_distance < distance && kmVec2Dot(&this_normal, &ray->dir) < 0.0f) {
            final_intersect.x = intersect.x;
            final_intersect.y = intersect.y;
            distance = this_distance;
            kmVec2Assign(&normal, &this_normal);
            intersected = KM_TRUE;                                
        }          
    }
    
    if(intersected) {
        intersection->x = final_intersect.x;
        intersection->y = final_intersect.y;
        if(normal_out) {
            normal_out->x = normal.x;
            normal_out->y = normal.y;
        }
        if(distance) {
            *distance_out = distance;
        }
    }
    
    return intersected;
}

kmBool kmRay2IntersectBox(const kmRay2* ray, const kmVec2* p1, const kmVec2* p2, const kmVec2* p3, const kmVec2* p4,
kmVec2* intersection, kmVec2* normal_out) {
    kmBool intersected = KM_FALSE;
    kmVec2 intersect, final_intersect, normal;
    kmScalar distance = 10000.0f;
    
    const kmVec2* points[4];
    points[0] = p1;
    points[1] = p2;
    points[2] = p3; 
    points[3] = p4;

    unsigned int i = 0;
    for(; i < 4; ++i) {
        const kmVec2* this_point = points[i];
        const kmVec2* next_point = (i == 3) ? points[0] : points[i+1];
        const kmVec2* other_point = (i == 3 || i == 0) ? points[1] : points[0];
        
        if(kmRay2IntersectLineSegment(ray, this_point, next_point, &intersect)) {
            
            kmVec2 tmp;
            kmScalar this_distance = kmVec2Length(kmVec2Subtract(&tmp, &intersect, &ray->start));
            
            kmVec2 this_normal;
            
            calculate_line_normal(*this_point, *next_point, *other_point, &this_normal);
            if(this_distance < distance && kmVec2Dot(&this_normal, &ray->dir) < 0.0f) {
                kmVec2Assign(&final_intersect, &intersect);
                distance = this_distance;
                intersected = KM_TRUE;        
                kmVec2Assign(&normal, &this_normal);
            }
        }
    }
    
    if(intersected) {
        intersection->x = final_intersect.x;
        intersection->y = final_intersect.y;
        if(normal_out) {
            normal_out->x = normal.x;
            normal_out->y = normal.y;
        }
    }
    
    return intersected;    
}

kmBool kmRay2IntersectCircle(const kmRay2* ray, const kmVec2 centre, const kmScalar radius, kmVec2* intersection) {
    assert(0 && "Not implemented");
    return KM_TRUE;
}
