
#include "Instance.h"
#include "ext/matrix_transform.hpp"
#include <iostream>
#include <gtx/string_cast.hpp>

Instance::Instance(Model* object_model, glm::vec3 position)
	: objModel(object_model), mMatrix(glm::mat4(1.0f))
{
	trans.vDisplacement.vector = position;
	trans.vRotation.vector = glm::vec3(0.0f);
	trans.vScale.vector = glm::vec3(1.0f);

	trans.vDisplacement.isUpdated = true;
	trans.vRotation.isUpdated = false;
	trans.vScale.isUpdated = false;

	updateModelMatrix();
}

Instance::Instance(const Instance& inst)
{
	this->mMatrix = inst.mMatrix;
	this->trans = inst.trans;
	this->objModel = inst.objModel;
}

Instance& Instance::operator=(const Instance&)
{

	return *this;
}

Instance::~Instance() = default;

glm::mat4 Instance::getModelMatrix()
{
	updateModelMatrix();
	return mMatrix;
}

void Instance::updateModelMatrix()
{
	if(trans.vDisplacement.isUpdated)
	{
		mMatrix = glm::translate(mMatrix, trans.vDisplacement.vector);
		trans.vDisplacement.isUpdated = false;
		trans.vDisplacement.vector = glm::vec3(0.0f);
	}

	if (trans.vRotation.isUpdated)
	{
		mMatrix = glm::rotate(mMatrix, glm::radians(trans.vRotation.vector.x), glm::vec3(1.0f, 0.0f, 0.0f));
		mMatrix = glm::rotate(mMatrix, glm::radians(trans.vRotation.vector.y), glm::vec3(0.0f, 1.0f, 0.0f));
		mMatrix = glm::rotate(mMatrix, glm::radians(trans.vRotation.vector.z), glm::vec3(0.0f, 0.0f, 1.0f));

		trans.vRotation.isUpdated = false;
		trans.vRotation.vector = glm::vec3(0.0f);
	}


	if (trans.vScale.isUpdated)
	{
		mMatrix = glm::scale(mMatrix, trans.vScale.vector);
		trans.vScale.isUpdated = false;
		trans.vScale.vector = glm::vec3(1.0f);
	}

}



void Instance::Move(const glm::vec3 dVec)
{
	trans.vDisplacement.vector = dVec;
	trans.vDisplacement.isUpdated = true;
}

void Instance::Rotate(const glm::vec3 rVec)
{
	trans.vRotation.vector = rVec;
	trans.vRotation.isUpdated = true;
}

void Instance::Scale(const glm::vec3 sVec)
{
	trans.vScale.vector = sVec;
	trans.vScale.isUpdated = true;
}

