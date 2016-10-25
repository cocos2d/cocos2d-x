#include "creator_utils.h"

USING_NS_CC;

static void setSpriteQuad(V3F_C4B_T2F_Quad* quad, const Size& origSize, const int x, const int y, float x_factor, float y_factor)
{
    float offset_x = origSize.width * x;
    float offset_y = origSize.height * y;

    quad->bl.vertices.set(Vec3(offset_x, offset_y, 0));
    quad->br.vertices.set(Vec3(offset_x + (origSize.width * x_factor), offset_y, 0));
    quad->tl.vertices.set(Vec3(offset_x, offset_y + (origSize.height * y_factor), 0));
    quad->tr.vertices.set(Vec3(offset_x + (origSize.width * x_factor), offset_y + (origSize.height * y_factor), 0));

    if (x_factor != 1.0f || y_factor != 1.0f) {
        float x_size = (quad->br.texCoords.u - quad->bl.texCoords.u) * x_factor;
        float y_size = (quad->tl.texCoords.v - quad->bl.texCoords.v) * y_factor;

        quad->br.texCoords = Tex2F(quad->bl.texCoords.u + x_size, quad->bl.texCoords.v);
        quad->tl.texCoords = Tex2F(quad->tl.texCoords.u, quad->bl.texCoords.v + y_size);
        quad->tr.texCoords = Tex2F(quad->bl.texCoords.u + x_size, quad->bl.texCoords.v + y_size);
    }
}

void creator_tile_sprite(Sprite* sprite)
{
    const auto new_s = sprite->getContentSize();
    const auto frame = sprite->getSpriteFrame();
    const auto orig_s_pixel = frame->getOriginalSizeInPixels();
    const auto orig_rect = frame->getRectInPixels();

    // cheat: let the sprite calculate the original Quad for us.
    sprite->setContentSize(orig_s_pixel);
    V3F_C4B_T2F_Quad origQuad = sprite->getQuad();

    // restore the size
    sprite->setContentSize(new_s);

    const float f_x = new_s.width / orig_rect.size.width;
    const float f_y = new_s.height / orig_rect.size.height;
    const int n_x = std::ceil(f_x);
    const int n_y = std::ceil(f_y);

    PolygonInfo poly;
    const int totalQuads = n_x * n_y;

    V3F_C4B_T2F_Quad* ptr = (V3F_C4B_T2F_Quad*) malloc(sizeof(V3F_C4B_T2F_Quad) * totalQuads);

    for (int y=0; y<n_y; ++y) {
        for (int x=0; x<n_x; ++x) {
            ptr[y * n_x + x] = origQuad;
            float x_factor = (orig_rect.size.width * (x+1) <= new_s.width) ? 1 : f_x - (long)f_x;
            float y_factor = (orig_rect.size.height * (y+1) <= new_s.height) ? 1 : f_y - (long)f_y;
            CCLOG("x=%g, y=%g", x_factor, y_factor);
            setSpriteQuad(&ptr[y * n_x + x], orig_rect.size, x, y, x_factor, y_factor);
        }
    }

    poly.setQuads(ptr, totalQuads);
    sprite->setPolygonInfo(poly);
}
