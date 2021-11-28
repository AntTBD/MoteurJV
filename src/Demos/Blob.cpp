#include "Blob.h"

#define USE_CABLE true

void Blob::GenerateScene()
{
    // copy objects
    std::vector<Object*>* objects = EngineManager::getInstance().getScene()->getObjects(); // copy of objects in the scene for simulation
    if (!objects->empty()) {



        // ------ add contacts -------
        // add contacts naive entre objets (=colision entre 2 objets)
        NaiveContactGenerator *naiveContactGenerator = new NaiveContactGenerator(objects, 10); // contacts entre particules de rayon 10
        EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(naiveContactGenerator, 2 * objects->size());
        // contact avec le sol
        GroundContactGenerator *groundContactGenerator = new GroundContactGenerator(objects, 0.0f); // contact avec le sol à une hauteur de 0
        EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(groundContactGenerator, objects->size());


        for (int i = 0; i < objects->size(); i++) {
            // ------ force -------
#if USE_CABLE == true
            // add ressort ancré sur l'objet actuel
            Spring *springGenerator = new Spring(*objects->at(i), 5, 50);
#endif
            // add tiges or cables between each objects + spring force anchored on actual object
            for (int k = i + 1; k < objects->size(); k++) {
                // ------ contacts -------
#if USE_CABLE == false
                // add contacts tiges
                auto tige = new Rod(objects->at(i), objects->at(k), (objects->at(k)->GetPosition() - objects->at(i)->GetPosition()).Magnitude()); // tige de longueur la distance initiale
                EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(tige, 1);
#else
                // add contacts cables
                auto cable = new Cable(objects->at(i), objects->at(k), 100); // cable de longueur 200
                EngineManager::getInstance().getPhysicEngine()->getContactRegistry()->Add(cable, 1);

                // ------ force -------
                // Add spring force
                EngineManager::getInstance().getPhysicEngine()->getForceRegistry()->Add(objects->at(k), springGenerator);
#endif
            }

            // ------ force -------
            // Add gravity force
            Gravity *gravityGenerator = new Gravity();
            EngineManager::getInstance().getPhysicEngine()->getForceRegistry()->Add(objects->at(i), gravityGenerator);
        }
    }


    EngineManager::getInstance().console.logSuccess("Blob demo has been generated\n");
}