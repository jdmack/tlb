#ifndef TLB_GFX_PROJECTION_H_
#define TLB_GFX_PROJECTION_H_

// TODO(2016-05-14/JM): Decide what to do with this struct
// that is, keep it or get rid of it
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

