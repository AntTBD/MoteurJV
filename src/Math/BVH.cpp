#include "BVH.h"

Node::Node()
{
	this->parentNode = nullptr;
    this->primitive = nullptr;
	this->sphere = BoundingSphere();
    this->childNodes = std::vector<Node*>();
}

Node::Node(Primitive* _primitive)
{
	this->parentNode = nullptr;
	this->primitive = _primitive;

    this->sphere = BoundingSphere(this->primitive->getCenter(), this->primitive->body->GetDimensions().GetMaxValue());
    this->childNodes = std::vector<Node*>();
}


Node::Node(Node* parent, const BoundingSphere &sphere, Primitive* _primitive){

    this->parentNode = parent;
    this->primitive = _primitive;
    this->sphere = sphere;
    this->childNodes = std::vector<Node*>();
}

float Node::getSphereVolume()
{
	return  (4.f / 3.f) * M_PI * powf(sphere.radius,2);
}

BoundingSphere Node::sphereBouding2Nodes(BoundingSphere sphereA, BoundingSphere sphereB)
{
	BoundingSphere newSphere;
    /*Vector3 centreOffset = sphereB.center - sphereA.center;
    float distanceAB = centreOffset.Magnitude();
    float radiusDiff = sphereB.radius - sphereA.radius;
    // Check if the larger sphere encloses the small one
    if (radiusDiff*radiusDiff >= distanceAB)
    {
        newSphere.center = sphereA.radius > sphereB.radius ? sphereA.center : sphereB.center;
        newSphere.radius = sphereA.radius > sphereB.radius ? sphereA.radius : sphereB.radius;
    }
    // Otherwise we need to work with partially
    // overlapping spheres
    else
    {
        distanceAB = sqrtf(distanceAB);
        newSphere.radius = (distanceAB + sphereA.radius + sphereB.radius) * (0.5f);

        // The new centre is based on one's centre, moved towards
        // two's centre by an ammount proportional to the spheres'
        // radii.
        newSphere.center = sphereA.center;
        if (distanceAB > 0)
        {
            newSphere.center += centreOffset * (float)((float)(newSphere.radius - sphereA.radius)/(float)distanceAB);
        }
    }*/

    float distanceAB = (sphereB.center - sphereA.center).Magnitude();
    if(distanceAB < sphereA.radius + sphereB.radius){
        newSphere.radius = sphereA.radius > sphereB.radius ? sphereA.radius : sphereB.radius;
        newSphere.center = sphereA.radius > sphereB.radius ? sphereA.center : sphereB.center;
    }else{
        if(distanceAB != 0) {
            Vector3 norm = (sphereB.center - sphereA.center).Normalize();

            Vector3 segmentCoteA = sphereA.center - norm * sphereA.radius;
            Vector3 segmentCoteB = sphereB.center + norm * sphereB.radius;
            newSphere.center = (segmentCoteA + segmentCoteB)/2.0f;
//            newSphere.center = Vector3(
//                    (segmentCoteA.GetX() + segmentCoteB.GetX()) / 2.f,
//                    (segmentCoteA.GetY() + segmentCoteB.GetY()) / 2.f,
//                    (segmentCoteA.GetZ() + segmentCoteB.GetZ()) / 2.f);
            newSphere.radius = (segmentCoteA - segmentCoteB).Magnitude() / 2.f;
        }else{
            // si les 2 nodes ont la meme position, on prend le plus grand rayon
            newSphere.radius = sphereA.radius > sphereB.radius ? sphereA.radius : sphereB.radius;
            newSphere.center = sphereA.radius > sphereB.radius ? sphereA.center : sphereB.center;

        }
    }
	return newSphere;
}

Node* Node::getBrotherNode()
{
	Node* brother = nullptr;
	if (hasParent())
	{
		int sizeParentChilds = this->parentNode->childNodes.size();
		int i = 0;
		while(i < sizeParentChilds && brother == nullptr)
		{
			if (this->parentNode->childNodes[i] != this && brother == nullptr) {
				brother = this->parentNode->childNodes[i];
			}
		}
	}

	return brother;
}

void Node::RemoveFromChild(Node* node)
{
	int index = 0;
	int indexNodeToRemove = -1;

	for (Node* child : this->childNodes)
	{
		if (child == node)
		{
			indexNodeToRemove = index;
		}
		index++;
	}

	if (indexNodeToRemove == -1)
	{
		std::cout << "Node not found" << std::endl;
		return;
	}

	this->childNodes.erase(this->childNodes.begin() + indexNodeToRemove);

}

void Node::insertNode(Primitive* newPrimitive, const BoundingSphere &newSphere)
{
    /*// si on a une primitive, on le donne à l'enfant
	if (this->primitive != nullptr)//isLeaf())
	{
        // ce node devient le parent des 2 nouveaux enfants
        // on cré un nouvel enfant
        Node *newChild = new Node();
        // on transfert la primitive au nouvel enfant et on l'enlève dans notre noeud
        if(this->primitive != nullptr){
            newChild->primitive = this->primitive;
            this->primitive = nullptr;
        }
        // on transfert notre sphere
        newChild->sphere = this->sphere;
        // on clear les enfants
        this->childNodes.clear();
        // on redéfinit le parent des 2 nouveaux enfants
        newChild->parentNode = this;
        this->childNodes.push_back(newChild);



        node->parentNode = this;
        this->childNodes.push_back(node);

            // on recalcule la sphere englobante avec maintenant les 2 enfants
            this->sphere = this->sphereBouding2Nodes(newChild->sphere, node->sphere);

            // on recalcule la sphere anglobante pour tous les parents
            Node *tempNode = this;
            while (tempNode->parentNode != nullptr) {
                if (tempNode->parentNode->childNodes.size() == 1) {
                   tempNode->parentNode->sphere = tempNode->parentNode->childNodes.at(0)->sphere;
                } else
                    tempNode->parentNode->sphere = tempNode->sphereBouding2Nodes(
                            tempNode->parentNode->childNodes.at(0)->sphere,
                            tempNode->parentNode->childNodes.at(1)->sphere);
                tempNode = tempNode->parentNode;
            }

        if(this->sphere.radius == 0)
            std::cout << "error" << std::endl;
	}
	else
	{*/
		/*float minSearch = std::numeric_limits<float>::max();
		Node* childToSave = nullptr;
        BoundingSphere sphere;
		for (Node* child : this->childNodes)
		{
            sphere = this->sphereBouding2Nodes(child->sphere, node->sphere);

            if (sphere.radius < minSearch) {
                minSearch = sphere.radius;
                childToSave = child;
            }
		}
        if(childToSave != nullptr){
            if(childToSave->sphere.radius == 0)
                std::cout << "error" << std::endl;
            childToSave->insertNode(node);
        }*/
        /*if(this->childNodes.size()>0) {
            BoundingSphere sphere1 = this->sphereBouding2Nodes(this->childNodes[0]->sphere, node->sphere);
            float growth1 =
                    sphere1.radius * sphere1.radius - this->childNodes[0]->sphere.radius * this->childNodes[0]->sphere.radius;

            if(this->childNodes.size()>1) {
                BoundingSphere sphere2 = this->sphereBouding2Nodes(this->childNodes[1]->sphere, node->sphere);
                float growth2 =
                        sphere2.radius * sphere2.radius - this->childNodes[1]->sphere.radius * this->childNodes[1]->sphere.radius;
                if (growth1 < growth2) {
                    this->childNodes[0]->insertNode(node);
                } else {
                    this->childNodes[1]->insertNode(node);
                }
                //this->sphere = this->sphereBouding2Nodes(this->childNodes[0]->sphere, this->childNodes[1]->sphere);
            }else{
                float growth2 =
                        sphere.radius * sphere.radius - this->childNodes[0]->sphere.radius * this->childNodes[0]->sphere.radius;
                if (growth1 < growth2) {
                    this->childNodes[0]->insertNode(node);
                    //this->sphere = this->sphereBouding2Nodes(this->childNodes[0]->sphere, node->sphere);
                }else{
                    this->childNodes.push_back(node);
                    //this->sphere = this->sphereBouding2Nodes(this->childNodes[0]->sphere, node->sphere);

                }
            }
        }else{
            this->childNodes.push_back(node);
            this->sphere = node->sphere;
        }
        Node *tempNode = this;
        while (tempNode->parentNode != nullptr) {
            if (tempNode->parentNode->childNodes.size() == 1) {
                tempNode->parentNode->sphere = tempNode->parentNode->childNodes.at(0)->sphere;
            } else
                tempNode->parentNode->sphere = tempNode->sphereBouding2Nodes(
                        tempNode->parentNode->childNodes.at(0)->sphere,
                        tempNode->parentNode->childNodes.at(1)->sphere);
            tempNode = tempNode->parentNode;
        }*/

	//}

    // If we are a leaf, then the only option is to spawn two
    // new children and place the new body in one.
    if (isLeaf())
    {
        // Child one is a copy of us.
        this->childNodes.push_back(new Node(
                this, this->sphere, this->primitive
        ));

        // Child two holds the new body
        this->childNodes.push_back(new Node(
                this, newSphere, newPrimitive
        ));

        // And we now loose the body (we're no longer a leaf)
        this->primitive = nullptr;

        // We need to recalculate our bounding volume
        this->recalculateBoundingVolume();
    }

        // Otherwise we need to work out which child gets to keep
        // the inserted body. We give it to whoever would grow the
        // least to incorporate it.
    else
    {
        if(this->childNodes.size() == 2) {
            if (this->childNodes[0]->sphere.getGrowth(newSphere) <
                this->childNodes[1]->sphere.getGrowth(newSphere)) {
                this->childNodes[0]->insertNode(newPrimitive, newSphere);
            } else {
                this->childNodes[1]->insertNode(newPrimitive, newSphere);
            }
        }else if(this->childNodes.size() == 1){
            if (this->childNodes[0]->sphere.getGrowth(newSphere) >
                this->sphere.getGrowth(newSphere)) {
                this->childNodes[0]->insertNode(newPrimitive, newSphere);
            } else {
                this->childNodes.push_back(new Node(this, newSphere, newPrimitive));
            }
            //this->childNodes[0]->insertNode(newPrimitive, newSphere);
            //this->childNodes.push_back(new Node(this, newSphere, newPrimitive));
        }else{
            this->childNodes.push_back(new Node(this, newSphere, newPrimitive));
        }
        // We need to recalculate our bounding volume
        this->recalculateBoundingVolume();

    }
}

void Node::deleteNode()
{
	if (hasParent() && this->parentNode->childNodes.size() == 2)
	{
		Node* grandParent = this->parentNode->parentNode;
		Node* parent = this->parentNode;
		Node* brother = getBrotherNode();

		grandParent->RemoveFromChild(parent);

		brother->parentNode = grandParent;
		grandParent->childNodes.push_back(brother);
	}

	delete this;
}

void Node::print(int degree)
{
	std::cout << "|";
	for (int i = 0; i < degree; i++) {
		std::cout << "----";
	}

	std::cout << "Node " << this->childNodes.size() << " center:" << this->sphere.center << " r:" << this->sphere.radius << " " ;
    if(this->primitive != nullptr)
        std::cout << "   >>>    "  << this->primitive->body->GetName() << " p.center:" << *this->primitive->center;
    std::cout << " \n";
if(this->sphere.radius ==0)
    std::cout << "Error "<< std::endl;

	for (Node* child : this->childNodes)
	{
		child->print(degree + 1);
	}
}

const Primitive& Node::getPrimitive() const {
    return *this->primitive;
}

BVH::BVH()
{
	root = new Node();
}

void BVH::broadPhaseCheck(Node* parent, CollisionData* cd) {
    if(parent->childNodes.size() == 2) {
        Node *child1 = parent->childNodes[0];
        Node *child2 = parent->childNodes[1];

        broadPhaseCheckChildPrimitive(child1, child2, cd);
    }
}


void BVH::broadPhaseCheckChildPrimitive(Node *child1, Node *child2, CollisionData* cd){
    // Early out if we don't overlap
    if(!child1->sphere.overlaps(child2->sphere)) return;

    // If we're both at leaf nodes, then we have a potential contact
    if (child1->isLeaf() && child2->isLeaf())
    {
        if (child1->primitive->body->GetShapeType() == RigidBody::ShapeType::Sphere &&
            child2->primitive->body->GetShapeType() == RigidBody::ShapeType::Plan) {
            CollisionDetector::sphereAndHalfSpace((const Sphere &) child1->getPrimitive(),
                                                  (const Plane &) child2->getPrimitive(),
                                                  cd);
        } else if (child1->primitive->body->GetShapeType() == RigidBody::ShapeType::Plan &&
                   child2->primitive->body->GetShapeType() == RigidBody::ShapeType::Sphere) {
            CollisionDetector::sphereAndHalfSpace((const Sphere &) child2->getPrimitive(),
                                                  (const Plane &) child1->getPrimitive(),
                                                  cd);
        } else if (child1->primitive->body->GetShapeType() == RigidBody::ShapeType::Cube &&
                   child2->primitive->body->GetShapeType() == RigidBody::ShapeType::Plan) {
            CollisionDetector::boxAndHalfSpace((const Box &) child1->getPrimitive(),
                                               (const Plane &) child2->getPrimitive(),
                                               cd);
        } else if (child1->primitive->body->GetShapeType() == RigidBody::ShapeType::Plan &&
                   child2->primitive->body->GetShapeType() == RigidBody::ShapeType::Cube) {
            CollisionDetector::boxAndHalfSpace((const Box &) child2->getPrimitive(),
                                               (const Plane &) child1->getPrimitive(),
                                               cd);
        }
    }
    if (!child1->isLeaf() && child2->isLeaf() ){
        if(child1->sphere.getVolume() >= child2->sphere.getVolume()){
            broadPhaseCheckChildPrimitive(child1->childNodes[0],
                                          child2, cd
            );
            broadPhaseCheckChildPrimitive(child1->childNodes[1],
                                            child2, cd
            );
        }
    }else if (child1->isLeaf() && !child2->isLeaf() ){
        if(child1->sphere.getVolume() >= child2->sphere.getVolume()){
            broadPhaseCheckChildPrimitive(child1,
                                          child2->childNodes[0], cd
            );
            broadPhaseCheckChildPrimitive(child1,
                                          child2->childNodes[1], cd
            );
        }
    }else if (!child1->isLeaf() && !child2->isLeaf()){
        for (Node* child_1:child1->childNodes) {
            for (Node *child_2: child2->childNodes) {
                broadPhaseCheckChildPrimitive(child_1, child_2, cd);
            }
        }
    }
    if(child1->childNodes.size()>0){
        broadPhaseCheckChildPrimitive(child1->childNodes[0], child1->childNodes[1], cd);
    }
    if(child2->childNodes.size()>0){
        broadPhaseCheckChildPrimitive(child2->childNodes[0], child2->childNodes[1], cd);
    }

    // Determine which node to descend into. If either is
    // a leaf, then we descend the other. If both are branches,
    // then we use the one with the largest size.
    /*if (child2->isLeaf() ||
        (!child1->isLeaf() && child1->sphere.getVolume() >= child2->sphere.getVolume()))
    {
        // Recurse into ourself
        //unsigned count =
        broadPhaseCheckChildPrimitive(child1->childNodes[0],
                child2, cd
        );

        // Check we have enough slots to do the other side too
        //if (limit > count) {
            //return count +
            broadPhaseCheckChildPrimitive(child1->childNodes[1],
                    child2, cd
            );
       // } else {
        //    return count;
        //}
    }
    else
    {
        // Recurse into the other node
        //unsigned count =
        broadPhaseCheckChildPrimitive(child1,
                child2->childNodes[0], cd
        );

        // Check we have enough slots to do the other side too
        //if (limit > count) {
            //return count +
        broadPhaseCheckChildPrimitive(child1,
                    child2->childNodes[1], cd
            );
        //} else {
        //    return count;
        //}
    }*/

   /* // check if distance AB > A.rayon + B.rayon
    //if ((child1->sphere.center - child2->sphere.center).Magnitude() < child1->sphere.radius + child2->sphere.radius) {

        // cas ou les 2 nodes sont des primitives
        if (child1->primitive != nullptr && child2->primitive != nullptr) {
            if (child1->primitive->body->GetShapeType() == RigidBody::ShapeType::Sphere &&
                child2->primitive->body->GetShapeType() == RigidBody::ShapeType::Plan) {
                CollisionDetector::sphereAndHalfSpace((const Sphere &) child1->getPrimitive(),
                                                      (const Plane &) child2->getPrimitive(),
                                                      cd);
            } else if (child1->primitive->body->GetShapeType() == RigidBody::ShapeType::Plan &&
                       child2->primitive->body->GetShapeType() == RigidBody::ShapeType::Sphere) {
                CollisionDetector::sphereAndHalfSpace((const Sphere &) child2->getPrimitive(),
                                                      (const Plane &) child1->getPrimitive(),
                                                      cd);
            } else if (child1->primitive->body->GetShapeType() == RigidBody::ShapeType::Cube &&
                child2->primitive->body->GetShapeType() == RigidBody::ShapeType::Plan) {
                CollisionDetector::boxAndHalfSpace((const Box &) child1->getPrimitive(),
                                                      (const Plane &) child2->getPrimitive(),
                                                      cd);
            } else if (child1->primitive->body->GetShapeType() == RigidBody::ShapeType::Plan &&
                       child2->primitive->body->GetShapeType() == RigidBody::ShapeType::Cube) {
                CollisionDetector::boxAndHalfSpace((const Box &) child2->getPrimitive(),
                                                      (const Plane &) child1->getPrimitive(),
                                                      cd);
            }
        }
//        else if (child1->primitive == nullptr && child2->primitive != nullptr){
//            for (Node* child:child1->childNodes) {
//                broadPhaseCheckChildPrimitive(child, child2, cd);
//            }
//        }else if (child1->primitive != nullptr && child2->primitive == nullptr){
//            for (Node* child:child2->childNodes) {
//                broadPhaseCheckChildPrimitive(child, child1, cd);
//            }
//        }else if (child1->primitive == nullptr && child2->primitive == nullptr){
//            for (Node* child_1:child1->childNodes) {
//                for (Node* child_2:child2->childNodes) {
//                    broadPhaseCheckChildPrimitive(child_1, child_2, cd);
//                }
//            }
//
//        }
        // Determine which node to descend into. If either is
        // a leaf, then we descend the other. If both are branches,
        // then we use the one with the largest size.
        else if (child2->primitive != nullptr ||
                (child1->primitive == nullptr && child1->sphere.getVolume() >= child2->sphere.getVolume())){
            for (Node* child:child1->childNodes) {
                broadPhaseCheckChildPrimitive(child, child2, cd);
            }
        }else{
            for (Node* child:child2->childNodes) {
                broadPhaseCheckChildPrimitive(child, child1, cd);
            }
        }
    //}*/
}




//	for (int i = 0; i < parent->childNodes.size(); i++)
//	{
//		for (int j = 0; j < parent->childNodes.size(); j++)
//		{
//			if (j != i)
//			{
//				if ((parent->childNodes[i]->sphere.center - parent->childNodes[j]->sphere.center).Magnitude() < parent->childNodes[i]->sphere.radius + parent->childNodes[j]->sphere.radius)
//				{
//					//cd->CheckerCollision
//					std::cout << "Potentielle collision a checker" << std::endl;
//                    if(parent->childNodes[i]->primitive != nullptr){
//
//                        Node* tempNode = parent->childNodes[j];
//                        while(tempNode->primitive != nullptr && tempNode->childNodes.size() > 0){
//                            tempNode = tempNode->childNodes[0];
//                        }
//                        if (parent->childNodes[i]->primitive->body->GetShapeType() == RigidBody::ShapeType::Sphere &&
//                                tempNode->primitive->body->GetShapeType() == RigidBody::ShapeType::Plan) {
//                            CollisionDetector::sphereAndHalfSpace((const Sphere &) parent->childNodes[i]->getPrimitive(),
//                                                                  (const Plane &) tempNode->getPrimitive(),
//                                                                  cd);
//                        } else if (parent->childNodes[i]->primitive->body->GetShapeType() == RigidBody::ShapeType::Sphere &&
//                                tempNode->primitive->body->GetShapeType() == RigidBody::ShapeType::Cube) {
//                            CollisionDetector::sphereAndHalfSpace((const Sphere &) tempNode->getPrimitive(),
//                                                                  (const Plane &) parent->childNodes[i]->getPrimitive(),
//                                                                  cd);
//                        }
//
//                    }
//
///*
//                    if(parent->childNodes[i]->primitive != nullptr && parent->childNodes[j]->primitive != nullptr) {
//                        std::cout << typeid(*parent->childNodes[i]->primitive).name() << " && " << typeid(*parent->childNodes[j]->primitive).name()<< std::endl;
//                        std::cout << parent->childNodes[i]->primitive->body->GetShapeType() << " && " << parent->childNodes[j]->primitive->body->GetShapeType()<< std::endl;
//                        std::cout << parent->childNodes[i]->primitive->body->GetName() << " && " << parent->childNodes[j]->primitive->body->GetName()<< std::endl;
//                        if (parent->childNodes[i]->primitive->body->GetShapeType() == RigidBody::ShapeType::Sphere &&
//                                parent->childNodes[j]->primitive->body->GetShapeType() == RigidBody::ShapeType::Plan) {
//                            CollisionDetector::sphereAndHalfSpace((const Sphere &) parent->childNodes[i]->getPrimitive(),
//                                                               (const Plane &) parent->childNodes[j]->getPrimitive(),
//                                                               cd);
//                        } else if (parent->childNodes[i]->primitive->body->GetShapeType() == RigidBody::ShapeType::Sphere &&
//                                   parent->childNodes[j]->primitive->body->GetShapeType() == RigidBody::ShapeType::Cube) {
//                            CollisionDetector::sphereAndHalfSpace((const Sphere &) parent->childNodes[j]->getPrimitive(),
//                                                               (const Plane &) parent->childNodes[i]->getPrimitive(),
//                                                               cd);
//                        }
//                    }*/
//				}
//			}
//		}
//
//		if (!parent->childNodes[i]->isLeaf())
//		{
//			broadPhaseCheck(parent->childNodes[i], cd);
//		}
//	}
//}

void BVH::broadPhaseCheck(CollisionData* cd)
{
	//CollisionData* cd = new CollisionData();
	broadPhaseCheck(this->root, cd);
}

void BVH::insertNode(Node* node)
{
	root->insertNode(node->primitive, node->sphere);
}

void BVH::print()
{
    std::cout << "==============" << std::endl;
    root->print(0);
    std::cout << "==============" << std::endl;
}

void Node::recalculateBoundingVolume() {
    if (isLeaf()) return;

    if(this->childNodes.size() == 2) {
        // Use the bounding volume combining constructor.
        this->sphere = BoundingSphere(
                this->childNodes[0]->sphere,
                this->childNodes[1]->sphere
        );
    }else if(this->childNodes.size() == 1){
        this->sphere = this->childNodes[0]->sphere;
    }

        // Recurse up the tree
    if (this->parentNode) this->parentNode->recalculateBoundingVolume();
}
