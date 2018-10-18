#include "Object.h"

#include <iostream>

using namespace std;

Object::Object(Mesh* mesh, vec3 position, mat4 rotation)
{
	this->mesh = mesh;
	this->position = position;
	this->rotation = rotation;
}

Object::~Object()
{
	for (vector<Object*>::iterator it = children.begin(); it!=children.end(); ++it)
	{
		delete (*it);
	}
}

void Object::render(mat4 model)
{
	model = model * translate(position) * rotation;
	if(mesh)
		mesh->render(model);
	for (vector<Object*>::iterator it = children.begin(); it!=children.end(); ++it)
	{
		(*it)->render(model);
	}
}

void Object::setParent(Object* parent)
{
	if(parent == NULL) return;
	if(this->parent == parent) return;
	this->parent = parent;
	parent->addChild(this);
}

void Object::addChild(Object* child)
{
	vector<Object*>::iterator it;
	it = std::find(children.begin(), children.end(), child);
	if(it == children.end())
	{
		children.push_back(child);
		child->setParent(this);
	}
}

void Object::unsetParent()
{
	if(parent == NULL) return;
	Object* p = parent;
	parent = NULL;
	p->removeChild(this);
}

void Object::removeChild(Object* child)
{
	vector<Object*>::iterator it;
	it = find(children.begin(), children.end(), child);
	if(it != children.end())
	{
		Object* found = *it;
		children.erase(it);
		found->unsetParent();
	}
}

vector<Object*> Object::getChildren()
{
	//return vector<Object*>(children);
	return children;
}

vec3 Object::getPosition() { return position; }
mat4 Object::getRotation() { return rotation; }
void Object::setPosition(vec3 position) {this->position = position;}
void Object::setRotation(mat4 rotation) {this->rotation = rotation;}
Mesh* Object::getMesh() { return mesh; }