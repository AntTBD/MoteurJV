# Moteur Physique de Jeu Vidéo

Projet de création d'un moteur physique de jeu vidéo, réalisé en cours de Mathématiques et Physique pour le Jeu Vidéo.
## But
Créer un moteur physique dont les objets sont des corps rigides et dont la résolution de collisions se fait de manière itérative à l’aide d’impulsions. Ce but sera atteint graduellement au fil du trimestre. La conception se fera en quatre (4) phases itératives.

### Phase 1 : construction d’un moteur élémentaire de gestion de particules
#### [Phase 1](https://github.com/AntTBD/MoteurJV/tree/Phase/1)

Le but de cette phase est de créer un moteur physique simple de gestion de particules à partir des notions vues en classes. En particulier, vous devez :
* Implémenter une classe Vecteur3D avec toutes les méthodes nécessaires.
* Implémenter une classe Particule comprenant des accesseurs pour l’attribut InverseMasse.
* Implémenter un intégrateur afin de mettre à jour la position et la vélocité de chaque particule à chaque frame. Celui-ci peut être implémenté en tant que méthode de la classe Particule.
* Réaliser un petit jeu de tir balistique où on peut choisir entre différents projectiles (e.g. balles, boulets, laser, boule de feu) et effectuer un tir. Chaque projectile doit avoir sa propre vélocité initiale et sa propre masse. Le frottement doit être négligeable (près de 1).

| Demo Phase 1 |
|---|
| ![Demo Phase 1](Physic%20Engine%201.0%20-%20Phase%201.gif) |

### Phase 2 : gestion d’objets formés de plusieurs masses par l’ajout de différentes forces et contraintes
#### [Phase 2](https://github.com/AntTBD/MoteurJV/tree/Phase/2)

Le but de cette phase est de poursuivre le développement du moteur physique réalisé lors de la phase 1 en lui ajoutant les notions de forces et contraintes vues en classe. Ainsi, le moteur permettra la gestion d’amas de particules. En particulier, vous devez :
* Implémenter, à l’aide d’une interface, des générateurs pour les forces suivantes : gravité, friction et ressorts. Notez que tous les types de ressorts vus en classe doivent être implémentés.
* Implémenter un système de détection de collisions. Ce système devra détecter les types de collisions suivants : interpénétrations, contacts au repos, tiges et câbles.
* Implémenter un système de résolution de collisions basé sur les impulsions.
* Réaliser un petit jeu où l’on déplace un amas de particule, i.e. blob. Chaque particule est représentée par un cercle. Les particules sont reliées entre elles en utilisant des ressorts classiques. Cependant, ces liens ont une limite d’élasticité au-delà de laquelle ils se comportent comme des câbles.
* Vous aurez des points bonis si votre blob peut se séparer en plusieurs morceaux et se fusionner.

| Demo Phase 2 |
|---|
| ![Demo Phase 2](Physic%20Engine%201.0%20-%20Phase%202.gif) |

## Bonus : refonte graphique
#### [Refonte](https://github.com/AntTBD/MoteurJV/tree/UI/2.0)

Amélioration de l'interface et de la structure des fichiers. Utilisation approfondie de la libraire ImGUI via OpenGL qui s'occupe également du rendu dans la nouvelle fenêtre Render. Cela a également permis d'améliorer le temps de rendu entre chaque frame.

* Ajout d'une fenêtre dédiée au rendu 3d de la scene via un FrameBuffer.
* Ajout d'une console avec différentes couleurs en fonction de l'importance.
* Ajout d'un inspecteur simple avec possibilité de changer les valeurs.

|  Avant |  Après |
| ------ | ------ |
| ![Physic Engine 1.0](Physic%20Engine%201.0%20-%20Phase%202.png) | ![Physic Engine 2.0](Physic%20Engine%202.0%20-%20Phase%202.png) |


### Phase 3 : gestion des corps rigides par l’ajout de la physique rotationnelle
#### [Phase 3](https://github.com/AntTBD/MoteurJV/tree/Phase/3)

Le but de cette phase est de spécialiser le moteur physique des phases 1 et 2 par l’ajout de la physique rotationnelle, implémentant ainsi les notions vues en classe. Ce faisant, le moteur permettra la gestion des corps rigides. Notez toutefois que la gestion des collisions n’est pas à implémenter dans cette phase. En particulier, vous devez :
* Implémenter une classe CorpsRigide avec les attributs et méthodes pertinentes.
* Implémenter les classes Matrix3, Matrix4 et Quaternion avec les attributs et méthodes pertinentes.
* Implémenter un intégrateur physique complet permettant la mise à jour des objets de type CorpsRigide.
* Réaliser deux courtes démos :
  * Une première où un objet de forme irrégulière est lancer en l’air avec des vélocités linéaires et angulaires non nulles. Le centre de masse ainsi que le mouvement de rotation doivent être clairement visibles.
  * Une deuxième où deux boîtes représentant deux voitures entrent en collision. Cette collision doit obligatoirement entraîner une rotation pour au moins une des deux voitures. Vous pouvez « hardcoder » le moment de la collision et le point d’impact.

| Demo Phase 3 - Random rigidbody | Demo Phase 3 - Cars collision |
|---|---|
| ![Demo Phase 3 Part 1](Physic%20Engine%202.0%20-%20Phase%203%20a.gif) | ![Demo Phase 3 Part 2](Physic%20Engine%202.0%20-%20Phase%203%20b.gif) |



### Phase 4 : ajout d’un système élémentaire de résolution de collisions
#### [Phase 4](https://github.com/AntTBD/MoteurJV/tree/Phase/4)

Le but de cette phase est d’ajouter au moteur physique de la phase 3 un système simple de détection de collisions. Ce faisant, le moteur permettra la détection de collisions entre une boîte et un plan. Notez toutefois que vous n’avez pas à implémenter un système de gestion de collisions.
Pour cette phase, vous devez produire une démo où une boîte rectangulaire est lancée dans une pièce rectangulaire fermée. La pièce doit être assez grande pour bien voir le déplacement de la boîte. Les vélocités linéaire et angulaire initiales doivent être non nulles. Lorsque la boîte entre en collision avec un des murs, la démo s’arrête. Vous devez alors générer la collision, c’est-à-dire produire le CollisionData approprié et en afficher le contenu (i.e. point d’impact, normale et interpénétration).
Pour ce faire, vous devez, en particulier:
* Implémenter un système de détection de collisions (broad phase) à l’aide d’une des structures vues en classe (e.g. octree, BSP, BVH, etc.). Il est conseillé d’utiliser une sphère comme volume englobant.
* Implémenter un système de génération de collisions (narrow phase) boîte-plan tel que vu en classe.
* Implémenter toutes les classes pertinentes à la réalisation de ce projet : ocTree, Contact, CollisionData, Primitive, Plane, Sphere, Box, etc.



| Demo Phase 4 |
|---|
| ![Demo Phase 4](Physic%20Engine%202.0%20-%20Phase%204.gif) |



## Created by:
* [@AntTBD](https://github.com/AntTBD)
* [@TheoLoubet](https://github.com/TheoLoubet)
* [@xNaRKoZz](https://github.com/xNaRKoZz)

<a href = "../../graphs/contributors">
  <img src = "https://contrib.rocks/image?repo=AntTBD/MoteurJV"/>
</a>

*3<sup>ème</sup> trimestre 2021, UQAC, CA*


> Made with *Visual Studio and CLion (with CMake)* \
> Plateforms supported : Windows 32-64bits

> <b style="color:red;">
> Avant de compiler le programme il faut
> ajouter le chemin de ..\MoteurJV\include\SDL2-2.0.16\lib\x64 dans la variable d'environnement système PATH
> </b>

> Pour **CMake dans CLion** : \
> Se rendre dans les *CMake Option* et recopier la ligne ci-dessous en fonction du besoin :
> * `-G "Visual Studio 16 2019" -A "x64"`
> * `-G "Visual Studio 16 2019" -A "Win32"`
 
