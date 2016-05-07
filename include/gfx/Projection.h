#ifndef TLB_GFX_PROJECTION_H_
#define TLB_GFX_PROJECTION_H_

struct PersProjInfo
{
    float fov_;
    float width_;
    float height_;
    float zNear_;
    float zFar_;
};

struct OrthoProjInfo
{
    float r_;        // right
    float l_;        // left
    float b_;        // bottom
    float t_;        // top
    float n_;        // z near
    float f_;        // z far
};

#endif

