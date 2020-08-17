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
		m_entity->GetPathManager()->prevNode[PREV_NODES_SIZE - 1] = m_entity->GetGoal(); // Avoid unsuccessful point
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
			for (int i = 0; i < PREV_NODES_SIZE; i++)
			{
				if (patrolNode == m_entity->GetPathManager()->prevNode[i])
				{
					recorded = true;
					break;
				}
			}

			if (not recorded and dist < minDist and COMA::TunnelLOSCheck(&temp, &m_entity->GetCenter(), TUNNEL_ENTITY_WIDTH))
			{
				minDist = dist;
				goToNode = patrolNode;
			}
		}

		// Set the node as the goal:
		if (goToNode)
		{
			for (int i = 1; i < PREV_NODES_SIZE; i++)
			{
				m_entity->GetPathManager()->prevNode[i - 1] = m_entity->GetPathManager()->prevNode[i];
			}

			m_entity->GetPathManager()->prevNode[PREV_NODES_SIZE - 1] = goToNode;
			m_entity->GetPathManager()->prevCheck = MAX_CHECK;

			m_entity->SetGoal(goToNode);
		}
	}
	else if (m_entity->GetGoal()) // We already have a goal to seek:
	{
		if (m_entity->GetPathManager()->prevCheck++ >= MAX_CHECK)
		{
			m_entity->GetPathManager()->prevCheck = 0;

			SDL_FPoint goalPoint = { m_entity->GetGoal()->x, m_entity->GetGoal()->y };

			m_entity->Seek(goalPoint);

			float dist = MAMA::SquareDistance(&goalPoint, &m_entity->GetCenter());

			if (dist < pow(SWITCH_NODE_DISTANCE, 2))
			{
				m_entity->SetGoal(nullptr);
				m_entity->SetReachedGoal(true);
			}
		}
	}
}

void PatrolState::Transition()
{
	if (m_entity->GetPlayerDetectRad() and not m_entity->GetPlayerLOS())
	{
		m_entity->GetAIState()->ChangeState(MOVETOLOS);
		return;
	}
	if (m_entity->GetPlayerLOS())
	{
		if (m_entity->GetEnemyType() == MELEETYPE)
			m_entity->GetAIState()->ChangeState(MOVETOLOS);
		else if (m_entity->GetEnemyType() == RANGETYPE)
			m_entity->GetAIState()->ChangeState(MOVETORANGE);
		
		return;
	}
}

void PatrolState::Exit()
{

}