#include "AIState.h"

#include "CollisionManager.h"
#include "EnemyManager.h"
#include "MathManager.h"
#include "PathManager.h"
#include "SoundManager.h"
#include "Util.h"

BehaviorState::BehaviorState(Enemy* player) : m_entity(player)
{

}

BehaviorState::~BehaviorState() = default;

AIState::AIState(Enemy* player) : m_entity(player)
{
	ChangeState(new IdleState(m_entity));
}

AIState::~AIState() = default;

void AIState::Update()
{
	if (m_state)
	{
		m_state->Update();
		m_state->Test();
	}
}

void AIState::ChangeState(BehaviorState* newState)
{
	if (m_state)
	{
		m_state->Exit();
		delete m_state;
	}
	m_state = newState;
	m_state->Enter();
}

void AIState::ChangeState(Status status)
{
	switch (status)
	{
	case IDLE:
		ChangeState(new IdleState(m_entity));
		break;
	case PATROL:
		ChangeState(new PatrolState(m_entity));
		break;
	case DIE:
		ChangeState(new DieState(m_entity));
		break;
	case GOTOLOS:
		ChangeState(new MoveToLOSState(m_entity));
		break;
	case GOTOCOVER:
		ChangeState(new MoveBehindCoverState(m_entity));
		break;
	}
}

// States:

// IDLE:

IdleState::IdleState(Enemy* enemy) : BehaviorState(enemy)
{

}

IdleState::~IdleState() = default;

void IdleState::Enter()
{
	m_entity->GetPathManager()->CleanNodes();
	m_entity->SetGoal(nullptr);
	m_entity->GetMoveEngine()->Stop();
	m_entity->SetStatus(IDLE);
}

void IdleState::Update()
{
	m_entity->GetAnimator()->SetNextAnimation("idle");
}

void IdleState::Exit()
{
	
}

void IdleState::Test()
{
	
}

// PATROLLING:

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
		m_entity->SetReachedGoal(false) ;
		
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

			if (not recorded and dist < minDist and COMA::LOSCheck(&temp, &m_entity->GetCenter()))
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

			if (dist < pow(SWITHNODEDISTANCE,2))
			{
				m_entity->SetGoal(nullptr);
				m_entity->SetReachedGoal(true);
			}
		}
	}
}

void PatrolState::Test()
{

}

void PatrolState::Exit()
{
	
}

// MOVING TO LOS:

MoveToLOSState::MoveToLOSState(Enemy* enemy) : BehaviorState(enemy), update_frame(0)
{
}

MoveToLOSState::~MoveToLOSState() = default;

void MoveToLOSState::Enter()
{
	
}

void MoveToLOSState::Update()
{
	// Find nearest LOS node:
	PathNode* LOS_node = nullptr;
	long min_dist = 99999;

	for (PathNode* node : *PAMA::GetNodes())
	{
		if (node->GetPlayerLOS())
		{
			SDL_FPoint temp_pos = { node->x, node->y };
			long dist = (long int)MAMA::SquareDistance(&ENMA::GetPlayer()->GetCenter(), &temp_pos);
			
			if (dist < min_dist)
			{
				
				min_dist = dist;
				LOS_node = node;
			}
		}
	}
	// Draw path:
	if (LOS_node and m_entity->GetShortestLOSNode())
	{
		Util::QueueCircle({ m_entity->GetShortestLOSNode()->x, m_entity->GetShortestLOSNode()->y }, 15, {255,0,0,255});
		Util::QueueCircle({ LOS_node->x, LOS_node->y }, 10);
		std::vector<PathConnection*> path = PAMA::GetShortestPath(m_entity->GetShortestLOSNode(), LOS_node);
		//std::cout << "Path size: " << path.size() << "\n";
		for (int i = 0; i < path.size(); i++)
		{
			PathNode* from = path[i]->GetFromNode();
			PathNode* to = path[i]->GetToNode();
			Util::QueueLine({ from->x, from->y }, { to->x, to->y }, { 255,0,0,255 });
		}
	}
}

void MoveToLOSState::Test()
{
	
}

void MoveToLOSState::Exit()
{
	
}

// MOVE BEHIND COVER:

MoveBehindCoverState::MoveBehindCoverState(Enemy* enemy) : BehaviorState(enemy)
{
}

MoveBehindCoverState::~MoveBehindCoverState() = default;

void MoveBehindCoverState::Enter()
{
	
}

void MoveBehindCoverState::Update()
{
	// Find nearest LOS node:
	PathNode* LOS_node = nullptr;
	long min_dist = 99999;

	for (PathNode* node : *PAMA::GetNodes())
	{
		if (not node->GetPlayerLOS())
		{
			SDL_FPoint temp_pos = { node->x, node->y };
			long dist = (long int)MAMA::SquareDistance(&m_entity->GetCenter(), &temp_pos);

			if (dist < min_dist)
			{

				min_dist = dist;
				LOS_node = node;
			}
		}
	}
	// Draw path:
	if (LOS_node and m_entity->GetShortestLOSNode())
	{
		Util::QueueCircle({ m_entity->GetShortestLOSNode()->x, m_entity->GetShortestLOSNode()->y }, 15, { 255,0,0,255 });
		Util::QueueCircle({ LOS_node->x, LOS_node->y }, 10);
		std::vector<PathConnection*> path = PAMA::GetShortestPath(m_entity->GetShortestLOSNode(), LOS_node);
		//std::cout << "Path size: " << path.size() << "\n";
		for (int i = 0; i < path.size(); i++)
		{
			PathNode* from = path[i]->GetFromNode();
			PathNode* to = path[i]->GetToNode();
			Util::QueueLine({ from->x, from->y }, { to->x, to->y }, { 255,0,0,255 });
		}
	}
}

void MoveBehindCoverState::Test()
{
	
}

void MoveBehindCoverState::Exit()
{
	
}

// DYING:

DieState::DieState(Enemy* enemy) : BehaviorState(enemy)
{
	
}

DieState::~DieState() = default;

void DieState::Enter()
{
	SOMA::PlaySound("dead", 0, 5);
	m_entity->GetAnimator()->PlayFullAnimation("die");
	
	m_entity->GetHealthBar()->SetEnabled(false);
	
	m_entity->SetStatus(DIE);
}

void DieState::Update()
{
	if (m_entity->GetAnimator()->AnimationIsPlaying("die"))
	{
		m_entity->GetMoveEngine()->Stop();
	}
	else
	{
		m_entity->Clean();
	}
}

void DieState::Test()
{
	
}

void DieState::Exit()
{
	
}

