#include "ContactResolver.h"
#include <limits>
#include "../../EngineManager.h"

ContactResolver::ContactResolver()
{
}

/// <summary>
/// R�soudre les contacts les plus important d�abord !<para />
/// ---<para />
/// 1. Calculer les v�locit�s relatives de tout les contacts et conserver la plus petite valeur<para />
/// ==> Si la plus petite valeur est plus grand que 0, alors tout les contacts sont r�solue<para />
/// 2. G�rer la collision du contacts(Impulsion + interp�n�tration)<para />
/// 3. Recommencer � l��tape 1<para />
/// ---<para />
/// *Afin de limiter le temps n�cessaire au calcul, on limitera le nombre d�it�ration(ex : 2 fois le nombre de contacts)
/// </summary>
/// <param name="contactArray">list des contacts</param>
/// <param name="duration"></param>
void ContactResolver::resolveContacts(std::vector<Contact*> contactArray, float duration)
{
	if (contactArray.size() > 0) {
		//  on limite le nombre d�it�ration (ex : 2 fois le nombre de contacts)
		this->maxIteration = 2 * contactArray.size();

		float minSeparatingVelocity = std::numeric_limits<float>::infinity();
		int minContactIndex;
		float tempSeparatingVelocity;

		int iteration = 0;
		while (iteration < this->maxIteration) // tant qu'on a pas atteint le nombre max d'iterations
		{
			// Calculer les v�locit�s relatives de tout les contacts et conserver la plus petite valeur
			minSeparatingVelocity = std::numeric_limits<float>::infinity(); // on initialise le min � l'infini
			minContactIndex = contactArray.size();

			for (int i = 0; i < contactArray.size(); i++)
			{
				if (contactArray[i] != nullptr) {
					tempSeparatingVelocity = contactArray[i]->calculateSeparatingVelocity();
					if (tempSeparatingVelocity < minSeparatingVelocity && (tempSeparatingVelocity < 0 || contactArray[i]->m_penetration > 0)) // on conserve la plus petite valeur
					{
						minSeparatingVelocity = tempSeparatingVelocity;
						minContactIndex = i;
					}
				}
			}

			// Si la plus petite valeur est plus grand que 0, alors tout les contacts sont r�solues
			if (minContactIndex >= contactArray.size())
			{
				break;
			}
            if (contactArray[minContactIndex]->m_penetration > 0) {
                EngineManager::getInstance().getPhysicEngine()->pause();
                std::cout << "stop" << contactArray.size() << std::endl;
            }
			// resolution du contact (Impulsion + interp�n�tration)
			//contactArray[minContactIndex]->resolve(duration);

			iteration++;
		}
	}
}
