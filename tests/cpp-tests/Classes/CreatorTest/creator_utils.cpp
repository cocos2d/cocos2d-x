#include "creator_utils.h"

USING_NS_CC;

static void setSpriteQuad(const V3F_C4B_T2F_Quad& origQuad, const Size& origSize, V3F_C4B_T2F_Quad* quad, const int x, const int y)
{
    float offset_x = origSize.width * x;
    float offset_y = origSize.height * y;

    *quad = origQuad;
    quad->bl.vertices.set(Vec3(offset_x, offset_y, 0));
    quad->br.vertices.set(Vec3(offset_x + origSize.width, offset_y, 0));
    quad->tl.vertices.set(Vec3(offset_x, offset_y + origSize.height, 0));
    quad->tr.vertices.set(Vec3(offset_x + origSize.width, offset_y + origSize.height, 0));
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

    // restore it.
    sprite->setContentSize(new_s);

    // restore the size
    sprite->setContentSize(new_s);

    const int n_x = std::ceil(new_s.width / orig_s_pixel.width);
    const int n_y = std::ceil(new_s.height / orig_s_pixel.height);

    PolygonInfo poly;
    const int totalQuads = n_x * n_y;

    V3F_C4B_T2F_Quad* ptr = (V3F_C4B_T2F_Quad*) malloc(sizeof(V3F_C4B_T2F_Quad) * totalQuads);

    for (int y=0; y<n_y; ++y) {
        for (int x=0; x<n_x; ++x) {
            setSpriteQuad(origQuad, orig_rect.size, &ptr[y * n_y + x], x, y);
        }
    }

    poly.setQuads(ptr, totalQuads);
    sprite->setPolygonInfo(poly);
}
