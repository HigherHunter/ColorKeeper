#pragma once

#include "LinearMath/btIDebugDraw.h"
#include <GL/glew.h>
#include "Texture.h"

class DebugDrawer : public btIDebugDraw
{
public:

	// debug mode functions
	virtual void setDebugMode(int debugMode) override { this->debugMode = debugMode; }
	virtual int getDebugMode() const override { return debugMode; }

	// drawing functions
	virtual void  drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color) override;
	virtual void  drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;

	// unused
	virtual void  reportErrorWarning(const char* warningString) override {}
	virtual void  draw3dText(const btVector3& location, const char* textString) override {}

	void ToggleDebugFlag(int flag);

	GLuint passedUniformModel;
	Texture* drawTexture;

protected:
	
	int debugMode;
};