#include <iostream>
#include <vector>

#include "CGL/vector2D.h"

#include "mass.h"
#include "rope.h"
#include "spring.h"

namespace CGL {

    Rope::Rope(Vector2D start, Vector2D end, int num_nodes, float node_mass, float k, vector<int> pinned_nodes)
    {
        // TODO (Part 1): Create a rope starting at `start`, ending at `end`, and containing `num_nodes` nodes.

//        Comment-in this part when you implement the constructor
//        for (auto &i : pinned_nodes) {
//            masses[i]->pinned = true;
//        }

        Vector2D coords = start;
        for (int i = 0;i < num_nodes;i++)
        {
            coords = (i * end + (num_nodes - i - 1) * start) / (num_nodes - 1);
            Mass* new_mass = new Mass(coords, node_mass, false);
            masses.push_back(new_mass);
            if (i > 0)
            {
                Spring* new_spring = new Spring(masses[masses.size() - 2], masses[masses.size() - 1], k);
                springs.push_back(new_spring);
            }
        }
        for (auto& i : pinned_nodes)
        {
            masses[i]->pinned = true;
        }
    }

    void Rope::simulateEuler(float delta_t, Vector2D gravity)
    {

        double damping_factor = 0.1;

        for (auto& m : masses)
        {
            m->forces = Vector2D(0.0, 0.0);
        }
        for (auto& s : springs)
        {
            // TODO (Part 2): Use Hooke's law to calculate the force on a node
            double new_length = (s->m1->position - s->m2->position).norm();
            double f = -(s->k) * (new_length - s->rest_length);
            s->m2->forces += f * (s->m2->position - s->m1->position) / new_length;
            s->m1->forces += f * (s->m1->position - s->m2->position) / new_length;
            //std::cout << new_length << std::endl;
        }

        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                // TODO (Part 2): Add the force due to gravity, then compute the new velocity and position

                m->forces += m->mass * gravity;
                //std::cout << m->forces << std::endl;
                Vector2D a = m->forces / m->mass;
                m->velocity = m->velocity + (1-damping_factor)*a * delta_t;
                m->position = m->position + (1-damping_factor)*m->velocity * delta_t;

                // TODO (Part 2): Add global damping
            }

            // Reset all forces on each mass
            m->forces = Vector2D(0, 0);
        }
    }

    void Rope::simulateVerlet(float delta_t, Vector2D gravity)
    {

        double damping_factor = 0.00005;

        for (auto& s : springs)
        {
            // TODO (Part 3): Simulate one timestep of the rope using explicit Verlet （solving constraints)
            double new_length = (s->m1->position - s->m2->position).norm();
            double f = -(s->k) * (new_length - s->rest_length);
            s->m2->forces += f * (s->m2->position - s->m1->position) / new_length;
            s->m1->forces += f * (s->m1->position - s->m2->position) / new_length;
        }

        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                Vector2D temp_position = m->position;
                // TODO (Part 3.1): Set the new position of the rope mass
                
                // TODO (Part 4): Add global Verlet damping

                m->forces += m->mass * gravity;
                //std::cout << m->forces << std::endl;
                Vector2D a = m->forces / m->mass;
                Vector2D X_n = m->position + (1 - damping_factor) * (m->position - m->last_position) + a * delta_t * delta_t;
                m->last_position = m->position;
                m->position = X_n;
            }
            m->forces = Vector2D(0.0, 0.0);
        }
    }
}
