#include "PatrolState.h"

#include "CollisionManager.h"
#include "EnemyManager.h"

PatrolState::PatrolState(Enemy* enemy) : BehaviorState(enemy)
{

}

PatrolState::~PatrolState() = default;

void PatrolState::Enter()
{
	m_entity->SetStatus(PATROL);
}

void PatrolState::Update()
{
	// Failed to reach case:
	if (m_entity->GetPathManager()->goalCounter++ > 60 * 2.5)
	{
		m_entity->GetPathManager()->CleanNodes();
		m_entity->GetPathManager()->prevNode[PREVNODESSIZE - 1] = m_entity->GetGoal(); // Avoid unsuccessful point
		m_entity->SetGoal(nullptr);
		std::cout << "Failed to reach the goal\n";
	}

	// Deciding on the next goal:
	if (m_entity->GoalIsReached() or m_entity->GetGoal() == nullptr) // Find a new goal to seek:
	{
		m_entity->GetPathManager()->goalCounter = 0;
		m_entity->SetReachedGoal(false);

		float minDist = 999999;
		PathNode* goToNode = nullptr;

		// Seak for the node to seek:
		for (PathNode* patrolNode : *ENMA::GetScene()->GetLevel()->GetPatrolPath())
		{
			SDL_FPoint temp = { patrolNode->x, patrolNode->y };

			float dist = MAMA::SquareDistance(&temp, &m_entity->GetCenter());

			bool recorded = false;
			for (int i = 0; i < PREVNODESSIZE; i++)
			{
				if (patrolNode == m_entity->GetPathManager()->prevNode[i])
				{
					recorded = true;
					break;
				}
			}

			if (not recorded and dist < minDist and COMA::TunnelLOSCheck(&temp, &m_entity->GetCenter(), TUNNELENTITYWIDTH))
			{
				minDist = dist;
				goToNode = patrolNode;
			}
		}

		// Set the node as the goal:
		if (goToNode)
		{
			for (int i = 1; i < PREVNODESSIZE; i++)
			{
				m_entity->GetPathManager()->prevNode[i - 1] = m_entity->GetPathManager()->prevNode[i];
			}

			m_entity->GetPathManager()->prevNode[PREVNODESSIZE - 1] = goToNode;
			m_entity->GetPathManager()->prevCheck = MAXCHECK;

			m_entity->SetGoal(goToNode);
		}
	}
	else if (m_entity->GetGoal()) // We already have a goal to seek:
	{
		if (m_entity->GetPathManager()->prevCheck++ >= MAXCHECK)
		{
			m_entity->GetPathManager()->prevCheck = 0;

			SDL_FPoint goalPoint = { m_entity->GetGoal()->x, m_entity->GetGoal()->y };

			m_entity->Seek(goalPoint);

			float dist = MAMA::SquareDistance(&goalPoint, &m_entity->GetCenter());

			if (dist < pow(SWITHNODEDISTANCE, 2))
			{
				m_entity->SetGoal(nullptr);
				m_entity->SetReachedGoal(true);
			}
		}
	}
}

void PatrolState::Transition()
{

}

void PatrolState::Exit()
{

}