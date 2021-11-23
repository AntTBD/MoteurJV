#include "Blob.h"


void Blob::GenerateScene()
{
    // copy objects
    std::vector<Object*>* objects = EngineManager::getInstance().getScene()->getObjects(); // copy of objects in the scene for simulation
    if (!objects->empty()) {



        // ------ add contacts -------
        // add contacts naive entre particules (=colision entre 2 particules)
        NaiveContactGenerator *naiveContactGenerator = new NaiveContactGenerator(objects,
                                                                                                         10);// contacts entre particules de rayon 10
        EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(naiveContactGenerator,
                                                                                  2 * objects->size());
        // contact avec le sol
        GroundContactGenerator *groundContactGenerator = new GroundContactGenerator(objects,
                                                                                    0.0f);// contact avec le sol à une hauteur de 0
        EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(groundContactGenerator,
                                                                                  objects->size());


        for (int i = 0; i < objects->size(); i++) {
            // ------ force -------
            // add ressort ancré sur la particule actuelle
            ParticleSpring *particleSpringGenerator = new ParticleSpring(*objects->at(i), 5, 50);

            // add tiges or cables between each particles + spring force anchored on actual particle
            for (int k = i + 1; k < objects->size(); k++) {
                // ------ contacts -------
                // add contacts cables
                //auto tige = new ParticleRod(objects->at(i), objects->at(k), 100);// tige de longueur 200
                //EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(tige, 1);

                // add contacts tiges
                auto cable = new ParticleCable(objects->at(i), objects->at(k), 100);// cable de longueur 200
                EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(cable, 1);

                // ------ force -------
                // Add spring force
                EngineManager::getInstance().getPhysicEngine()->getForceRegistry()->Add(objects->at(k),
                                                                                        particleSpringGenerator);
            }

            // ------ force -------
            // Add gravity force
            ParticleGravity *particleGravityGenerator = new ParticleGravity();
            EngineManager::getInstance().getPhysicEngine()->getForceRegistry()->Add(objects->at(i),
                                                                                    particleGravityGenerator);
        }
    }
}