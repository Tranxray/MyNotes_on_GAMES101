//
// Created by Göksu Güvendiren on 2019-05-14.
//

#include "Scene.hpp"


void Scene::buildBVH() {
    printf(" - Generating BVH...\n\n");
    this->bvh = new BVHAccel(objects, 1, BVHAccel::SplitMethod::NAIVE);
}

Intersection Scene::intersect(const Ray &ray) const
{
    return this->bvh->Intersect(ray);
}

void Scene::sampleLight(Intersection &pos, float &pdf) const
{
    float emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
        }
    }
    float p = get_random_float() * emit_area_sum;
    emit_area_sum = 0;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        if (objects[k]->hasEmit()){
            emit_area_sum += objects[k]->getArea();
            if (p <= emit_area_sum){
                objects[k]->Sample(pos, pdf);
                break;
            }
        }
    }
}

bool Scene::trace(
        const Ray &ray,
        const std::vector<Object*> &objects,
        float &tNear, uint32_t &index, Object **hitObject) const
{
    *hitObject = nullptr;
    for (uint32_t k = 0; k < objects.size(); ++k) {
        float tNearK = kInfinity;
        uint32_t indexK;
        Vector2f uvK;
        if (objects[k]->intersect(ray, tNearK, indexK) && tNearK < tNear) {
            *hitObject = objects[k];
            tNear = tNearK;
            index = indexK;
        }
    }


    return (*hitObject != nullptr);
}

float vec_dis_2(const Vector3f& vec)
{
    return vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
}

// Implementation of Path Tracing
Vector3f Scene::castRay(const Ray &ray, int depth) const
{
    // TO DO Implement Path Tracing Algorithm here

    Intersection p = intersect(ray);
    Vector3f wo = normalize(ray.direction);

    Vector3f L_dir;
    if (!p.happened)return L_dir;
    if (p.m->hasEmission())return p.m->getEmission();

    Intersection inter;
    float pdf_light;
    sampleLight(inter, pdf_light);

    Vector3f inter_coords = inter.coords;
    Vector3f emit = inter.emit;
    Vector3f ws = normalize(inter_coords - p.coords);
    Vector3f N = p.normal.normalized();
    Vector3f NN = inter.normal.normalized();

    Ray ref_ray(p.coords, ws);
    Intersection test_inter = intersect(ref_ray);
    float d1 = (inter_coords - p.coords).norm();
    float d2 = (test_inter.coords - p.coords).norm();
    if (d2 - d1 > -0.001)
    {
        L_dir = emit * p.m->eval(wo, ws, N) * dotProduct(N, ws) * dotProduct(NN, -ws) / (d1*d1) / pdf_light;
       // std::cout << L_dir << std::endl;
    }

    Vector3f L_indir;

    float prr = get_random_float();
    if (prr < RussianRoulette)
    {
        Vector3f wi = p.m->sample(wo, N).normalized();
        //std::cout << wi << std::endl;
        Ray out_ray(p.coords, wi);
        Intersection out_inter = intersect(out_ray);
        if (out_inter.happened && !out_inter.obj->hasEmit())
        {
            L_indir = castRay(out_ray, depth + 1) * p.m->eval(wo, wi, N) * dotProduct(wi, N) / p.m->pdf(wo, wi, N) / RussianRoulette;
            //std::cout << L_dir << "          " << L_indir << std::endl;
        }
    }

    return L_dir + L_indir;

}