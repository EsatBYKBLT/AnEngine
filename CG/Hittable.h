#pragma once
#include "Ray.h"
namespace ERay {

class HitRecord {
public:
    Vec3 p;
    Vec3 normal;
    double t;
};

class Hittable{
public:
    virtual ~Hittable() = default;

    virtual bool Hit(const Ray& r, double ray_tmin, double ray_tmax, HitRecord& rec) const = 0;
};

}
