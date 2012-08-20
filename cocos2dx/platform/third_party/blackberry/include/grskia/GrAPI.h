

class GrAPI {
public:

    void setRenderTarget(GrRenderTarget* target);

    void setMatrix(const GrMatrix&);

    void setClip(rect, bool aa);
    void setClip(rect[], bool aa);
    void setClip(path, bool aa);
    void setClip(rect, texture/key, state, matrix);
    void setClip(path, texture/key, state, matrix);
    
    void setColor(color);
    void setTexture(texture/key, sampler, const GrMatrix* = NULL);
    void setBlend(src, dst);
    
    void drawRect(const GrRect&, stroke, join);
    void drawOval(const GrRect&, stroke);
    void drawRoundRect(const GrRect&, GrScalar ovalW, GrScalar ovalH, stroke);
    void drawPath(const GrPathIter&, GrPathFill);
    void drawVertices(...);
    void drawGlyphs(const uint16_t[], int count, const GrPoint[], GrFontScaler*);

///

    void save();
    void restore();
    void concatMatrix(const GrMatrix&);
    void concatClipRect(const GrRect&);
    void concatClipPath(const GrPathIter&, bool aa);

};


