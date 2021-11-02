#include "ParticleContactResolver.h"
#include <limits>

ParticleContactResolver::ParticleContactResolver()
{
}

/// <summary>
/// Résoudre les contacts les plus important d’abord !<para />
/// ---<para />
/// 1. Calculer les vélocités relatives de tout les contacts et conserver la plus petite valeur<para />
/// ==> Si la plus petite valeur est plus grand que 0, alors tout les contacts sont résolue<para />
/// 2. Gérer la collision du contacts(Impulsion + interpénétration)<para />
/// 3. Recommencer à l’étape 1<para />
/// ---<para />
/// *Afin de limiter le temps nécessaire au calcul, on limitera le nombre d’itération(ex : 2 fois le nombre de contacts)
/// </summary>
/// <param name="contactArray">list des contacts</param>
/// <param name="duration"></param>
void ParticleContactResolver::resolveContacts(std::vector<ParticleContact*> contactArray, float duration)
{
	if (contactArray.size() > 0) {
		//  on limite le nombre d’itération (ex : 2 fois le nombre de contacts)
		this->maxIteration = 2 * contactArray.size();

		float minSeparatingVelocity = std::numeric_limits<float>::infinity();
		int minContactIndex;
		float tempSeparatingVelocity;

		int iteration = 0;
		while (iteration < this->maxIteration) // tant qu'on a pas atteint le nombre max d'iterations
		{
			// Calculer les vélocités relatives de tout les contacts et conserver la plus petite valeur
			minSeparatingVelocity = std::numeric_limits<float>::infinity(); // on initialise le min à l'infini
			minContactIndex = 0;

			for (int i = 0; i < contactArray.size(); i++)
			{
				if (contactArray[i] != nullptr) {
					tempSeparatingVelocity = contactArray[i]->calculateSeparatingVelocity();
					if (tempSeparatingVelocity < minSeparatingVelocity) // on conserve la plus petite valeur
					{
						minSeparatingVelocity = tempSeparatingVelocity;
						minContactIndex = i;
					}
				}
			}

			// Si la plus petite valeur est plus grand que 0, alors tout les contacts sont résolues
			if (minSeparatingVelocity >= 0)
			{
				break;
			}

			// resolution du contact (Impulsion + interpénétration)
			contactArray[minContactIndex]->resolve(duration);

			iteration++;
		}
	}
}
