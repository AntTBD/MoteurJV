# Moteur Physique de Jeu Vid�o

Projet de cr�ation d'un moteur physique de jeu vid�o, r�alis� en cours de Math�matiques et Physique pour le Jeu Vid�o.
## But
Cr�er un moteur physique dont les objets sont des corps rigides et dont la r�solution de collisions se fait de mani�re it�rative � l�aide d�impulsions. Ce but sera atteint graduellement au fil du trimestre. La conception se fera en quatre (4) phases it�ratives.

### Phase 1 : construction d�un moteur �l�mentaire de gestion de particules
#### [Phase 1](../../tree/Phase/1)

Le but de cette phase est de cr�er un moteur physique simple de gestion de particules � partir des notions vues en classes. En particulier, vous devez :
* Impl�menter une classe Vecteur3D avec toutes les m�thodes n�cessaires.
* Impl�menter une classe Particule comprenant des accesseurs pour l�attribut InverseMasse. 
* Impl�menter un int�grateur afin de mettre � jour la position et la v�locit� de chaque particule � chaque frame. Celui-ci peut �tre impl�ment� en tant que m�thode de la classe Particule.
* R�aliser un petit jeu de tir balistique o� on peut choisir entre diff�rents projectiles (e.g. balles, boulets, laser, boule de feu) et effectuer un tir. Chaque projectile doit avoir sa propre v�locit� initiale et sa propre masse. Le frottement doit �tre n�gligeable (pr�s de 1).

| Demo Phase 1 |
|---|
| ![Demo Phase 1](doc/Physic%20Engine%201.0%20-%20Phase%201.gif) |

### Phase 2 : gestion d�objets form�s de plusieurs masses par l�ajout de diff�rentes forces et contraintes
#### [Phase 2](../../tree/Phase/2)

Le but de cette phase est de poursuivre le d�veloppement du moteur physique r�alis� lors de la phase 1 en lui ajoutant les notions de forces et contraintes vues en classe. Ainsi, le moteur permettra la gestion d�amas de particules. En particulier, vous devez :
* Impl�menter, � l�aide d�une interface, des g�n�rateurs pour les forces suivantes : gravit�, friction et ressorts. Notez que tous les types de ressorts vus en classe doivent �tre impl�ment�s.
* Impl�menter un syst�me de d�tection de collisions. Ce syst�me devra d�tecter les types de collisions suivants : interp�n�trations, contacts au repos, tiges et c�bles.
* Impl�menter un syst�me de r�solution de collisions bas� sur les impulsions.
* R�aliser un petit jeu o� l�on d�place un amas de particule, i.e. blob. Chaque particule est repr�sent�e par un cercle. Les particules sont reli�es entre elles en utilisant des ressorts classiques. Cependant, ces liens ont une limite d��lasticit� au-del� de laquelle ils se comportent comme des c�bles.
* Vous aurez des points bonis si votre blob peut se s�parer en plusieurs morceaux et se fusionner.

| Demo Phase 2 |
|---|
| ![Demo Phase 2](doc/Physic%20Engine%201.0%20-%20Phase%202.gif) |

## Bonus : refonte graphique
#### [Refonte](../../tree/UI/2.0)

Am�lioration de l'interface et de la structure des fichiers. Utilisation approfondie de la libraire ImGUI via OpenGL qui s'occupe �galement du rendu dans la nouvelle fen�tre Render. Cela a �galement permis d'am�liorer le temps de rendu entre chaque frame.

* Ajout d'une fen�tre d�di�e au rendu 3d de la scene via un FrameBuffer.
* Ajout d'une console avec diff�rentes couleurs en fonction de l'importance.
* Ajout d'un inspecteur simple avec possibilit� de changer les valeurs.

|  Avant |  Apr�s |
| ------ | ------ |
| <img alt="Physic Engine 1.0" src="doc/Physic%20Engine%201.0%20-%20Phase%202.png" height="200"> | <img alt="Physic Engine 2.0" src="doc/Physic%20Engine%202.0%20-%20Phase%202.png" height="200"> |


### Phase 3 : gestion des corps rigides par l�ajout de la physique rotationnelle
#### [Phase 3](../../tree/Phase/3)

Le but de cette phase est de sp�cialiser le moteur physique des phases 1 et 2 par l�ajout de la physique rotationnelle, impl�mentant ainsi les notions vues en classe. Ce faisant, le moteur permettra la gestion des corps rigides. Notez toutefois que la gestion des collisions n�est pas � impl�menter dans cette phase. En particulier, vous devez :
* Impl�menter une classe CorpsRigide avec les attributs et m�thodes pertinentes.
* Impl�menter les classes Matrix3, Matrix4 et Quaternion avec les attributs et m�thodes pertinentes.
* Impl�menter un int�grateur physique complet permettant la mise � jour des objets de type CorpsRigide.
* R�aliser deux courtes d�mos :
  * Une premi�re o� un objet de forme irr�guli�re est lancer en l�air avec des v�locit�s lin�aires et angulaires non nulles. Le centre de masse ainsi que le mouvement de rotation doivent �tre clairement visibles.
  * Une deuxi�me o� deux bo�tes repr�sentant deux voitures entrent en collision. Cette collision doit obligatoirement entra�ner une rotation pour au moins une des deux voitures. Vous pouvez � hardcoder � le moment de la collision et le point d�impact.

| Demo Phase 3 - Random rigidbody | Demo Phase 3 - Cars collision |
|---|---|
| ![Demo Phase 3 Part 1](doc/Physic%20Engine%202.0%20-%20Phase%203%20a.gif) | ![Demo Phase 3 Part 2](doc/Physic%20Engine%202.0%20-%20Phase%203%20b.gif) |



### Phase 4 : ajout d�un syst�me �l�mentaire de r�solution de collisions
#### [Phase 4](../../tree/Phase/4)

Le but de cette phase est d�ajouter au moteur physique de la phase 3 un syst�me simple de d�tection de collisions. Ce faisant, le moteur permettra la d�tection de collisions entre une bo�te et un plan. Notez toutefois que vous n�avez pas � impl�menter un syst�me de gestion de collisions.
Pour cette phase, vous devez produire une d�mo o� une bo�te rectangulaire est lanc�e dans une pi�ce rectangulaire ferm�e. La pi�ce doit �tre assez grande pour bien voir le d�placement de la bo�te. Les v�locit�s lin�aire et angulaire initiales doivent �tre non nulles. Lorsque la bo�te entre en collision avec un des murs, la d�mo s�arr�te. Vous devez alors g�n�rer la collision, c�est-�-dire produire le CollisionData appropri� et en afficher le contenu (i.e. point d�impact, normale et interp�n�tration).
Pour ce faire, vous devez, en particulier:
* Impl�menter un syst�me de d�tection de collisions (broad phase) � l�aide d�une des structures vues en classe (e.g. octree, BSP, BVH, etc.). Il est conseill� d�utiliser une sph�re comme volume englobant.
* Impl�menter un syst�me de g�n�ration de collisions (narrow phase) bo�te-plan tel que vu en classe.
* Impl�menter toutes les classes pertinentes � la r�alisation de ce projet : ocTree, Contact, CollisionData, Primitive, Plane, Sphere, Box, etc.



| Demo Phase 4 |
|---|
| ![Demo Phase 4](doc/Physic%20Engine%202.0%20-%20Phase%204.gif) |



## Created by:
* [@AntTBD](https://github.com/AntTBD)
* [@TheoLoubet](https://github.com/TheoLoubet)
* [@xNaRKoZz](https://github.com/xNaRKoZz)

<a href = "../../graphs/contributors">
  <img src = "https://contrib.rocks/image?repo=AntTBD/MoteurJV"/>
</a>

*3<sup>�me</sup> trimestre 2021, UQAC, CA*


> Made with *Visual Studio and CLion (with CMake)* \
> Plateforms supported : Windows 32-64bits

> <b style="color:red;">
> Avant de compiler le programme il faut
> ajouter le chemin de ..\MoteurJV\include\SDL2-2.0.16\lib\x64 dans la variable d'environnement syst�me PATH
> </b>

> Pour **CMake dans CLion** : \
> Se rendre dans les *CMake Option* et recopier la ligne ci-dessous en fonction du besoin :
> * `-G "Visual Studio 16 2019" -A "x64"`
> * `-G "Visual Studio 16 2019" -A "Win32"`
 