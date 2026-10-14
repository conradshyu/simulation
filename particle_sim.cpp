#include <vector>
#include <cmath>
#include <cstdlib>
#include <emscripten/bind.h>

struct Particle
{
    float x, y, vx, vy;
};

class ParticleSystem
{
    std::vector<Particle> particles;
    float width, height;

public:
    ParticleSystem(int count, float w, float h) : width(w), height(h)
    {
        particles.reserve(count);

        for (int i = 0; i < count; ++i)
        {
            Particle p;
            p.x = (float)rand() / static_cast<float>(RAND_MAX) * width;
            p.y = (float)rand() / static_cast<float>(RAND_MAX) * height;
            p.vx = ((float)rand() / static_cast<float>(RAND_MAX) - 0.5f) * 100.0f;
            p.vy = ((float)rand() / static_cast<float>(RAND_MAX) - 0.5f) * 100.0f;
            particles.push_back(p);
        }
    }

    void step(float dt)
    {
        for (auto &p : particles)
        {
            p.x += p.vx * dt;
            p.y += p.vy * dt;

            if (p.x < 0 || p.x > width)
                p.vx *= -1;
            if (p.y < 0 || p.y > height)
                p.vy *= -1;

            if (p.x < 0)
                p.x = 0;
            if (p.x > width)
                p.x = width;
            if (p.y < 0)
                p.y = 0;
            if (p.y > height)
                p.y = height;
        }
    }

    emscripten::val positions() const
    {
        emscripten::val arr = emscripten::val::array();

        for (size_t i = 0; i < particles.size(); ++i)
        {
            arr.call<void>("push", particles[i].x);
            arr.call<void>("push", particles[i].y);
        }

        return arr;
    }
};

EMSCRIPTEN_BINDINGS(particle_module)
{
    emscripten::class_<ParticleSystem>("ParticleSystem")
        .constructor<int, float, float>()
        .function("step", &ParticleSystem::step)
        .function("positions", &ParticleSystem::positions);
}
