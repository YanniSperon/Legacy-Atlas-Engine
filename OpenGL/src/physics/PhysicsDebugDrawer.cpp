#include "PhysicsDebugDrawer.h"
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "System.h"

void PhysicsDebugDrawer::drawLine(const btVector3 &from,const btVector3 &to, const btVector3 &color)
{
	glBegin(GL_LINES);
	glColor3f(color.getX(), color.getY(), color.getZ());
	glVertex3f(from.getX(), from.getY(), from.getZ());
	glVertex3f(to.getX(), to.getY(), to.getZ());
	glEnd();
}

void PhysicsDebugDrawer::drawContactPoint(const btVector3 &pointOnB, const btVector3 &normalOnB, btScalar distance, int lifeTime, const btVector3 &color)
{
	btVector3 const startPoint = pointOnB;
	btVector3 const endPoint = pointOnB + normalOnB * distance;
	drawLine( startPoint, endPoint, color );
}

void PhysicsDebugDrawer::ToggleDebugFlag(int flag) {
	if (m_debugMode & flag) {
		Atlas::System::Log("Disabled");
		m_debugMode = m_debugMode & (~flag);
	}
	else {
		Atlas::System::Log("Enabled");
		m_debugMode |= flag;
	}
}