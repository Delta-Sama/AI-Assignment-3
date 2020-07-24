#include "Debug.h"
#include "CollisionManager.h"
#include "Util.h"

DebugMode::DebugMode(GameState* scene)
{
	m_playScene = scene;
}

void DebugMode::Draw()
{
	if (m_mode)
	{
		/*if (CollisionManager::LOSCheck(m_playScene->GetPlayer(), m_playScene->GetPlane()))
			Util::DrawLine(m_playScene->GetPlayer()->getTransform()->position, m_playScene->GetPlane()->getTransform()->position);
		else
			Util::DrawLine(m_playScene->GetPlayer()->getTransform()->position, m_playScene->GetPlane()->getTransform()->position, glm::vec4(1, 0, 0, 1));

		glm::vec2 plrHalfPos = { m_playScene->GetPlayer()->getTransform()->position.x - m_playScene->GetPlayer()->getWidth() / 2,
			m_playScene->GetPlayer()->getTransform()->position.y - m_playScene->GetPlayer()->getHeight() / 2 };
		glm::vec4 color = (CollisionManager::AABBCheck(m_playScene->GetPlayer(), m_playScene->GetPlane())
			? glm::vec4{ 1, 0, 0, 1 } : glm::vec4{ 0, 1, 0, 1 });
		Util::DrawRect(plrHalfPos, m_playScene->GetPlayer()->getWidth(), m_playScene->GetPlayer()->getHeight(), color);

		glm::vec2 plnHalfPos = { m_playScene->GetPlane()->getTransform()->position.x - m_playScene->GetPlane()->getWidth() / 2,
			m_playScene->GetPlane()->getTransform()->position.y - m_playScene->GetPlane()->getHeight() / 2 };

		Util::DrawRect(plnHalfPos, m_playScene->GetPlane()->getWidth(), m_playScene->GetPlane()->getHeight(), color);*/
	}
}