#include "RedSniper.h"
#include "CollisionManager.h"
#include "EnemyManager.h"
#include "MathManager.h"
#include "TextureManager.h"

RedSniper::RedSniper(Vec2 pos) : Enemy(TEMA::GetTexture("enemy"), pos, SNIPERMAXHEALTH)
{
	this->AddAnimator(new Animator(this));

	this->GetAnimator()->AddAnimation("idle", 3, 1, 34, 0, 0, 0, 16);
	this->GetAnimator()->AddAnimation("run", 8, 2, 34, 0, 0, 34);
	this->GetAnimator()->AddAnimation("die", 4, 4, 34, 0, 0, 68);
	this->GetAnimator()->AddAnimation("damaged", 3, 3, 34, 0, 0, 102,4);
	
	m_status = IDLE;
}

RedSniper::~RedSniper()
{
	
}

void RedSniper::MakeDecision()
{
	switch (m_status)
	{
	case IDLE:
		m_pathManager.CleanNodes();
		m_goal = nullptr;
		this->Stop();
		break;
	case PATROL:
		{
			if (m_pathManager.goalCounter++ > 60 * 2.5)
			{
				m_pathManager.CleanNodes();
				std::cout << "Failed to reach the goal\n";
				m_pathManager.prevNode[PREVNODESSIZE-1] = m_goal;
				m_goal = nullptr;
			}
			if (m_reachedGoal or m_goal == nullptr)
			{
				m_pathManager.goalCounter = 0;
				m_reachedGoal = false;
				float minDist = 999999;
				PathNode* goToNode = nullptr;
				for (PathNode* patrolNode : *ENMA::GetScene()->GetLevel()->GetPatrolPath())
				{
					SDL_FPoint temp = { patrolNode->x, patrolNode->y };
					float dist = MAMA::SquareDistance(&temp, &this->GetCenter());
					bool notRecorded = true;

					for (int i = 0; i < PREVNODESSIZE; i++)
					{
						if (patrolNode == m_pathManager.prevNode[i])
						{
							notRecorded = false;
							break;
						}
					}
					
					if (notRecorded and dist < minDist)
					{
						minDist = dist;
						goToNode = patrolNode;
					}
				}

				if (goToNode)
				{
					for (int i = 1; i < PREVNODESSIZE; i++)
					{
						m_pathManager.prevNode[i-1] = m_pathManager.prevNode[i];
					}
					
					m_pathManager.prevNode[PREVNODESSIZE-1] = goToNode;
					m_goal = goToNode;
					m_pathManager.prevCheck = MAXCHECK;
				}
			}
			else if (m_goal)
			{
				if (m_pathManager.prevCheck++ >= MAXCHECK)
				{
					m_pathManager.prevCheck = 0;

					SDL_FPoint goalPoint = { m_goal->x, m_goal->y };
					this->Seek(goalPoint);

					SDL_FPoint temp = { m_goal->x, m_goal->y };
					float dist = MAMA::SquareDistance(&temp, &this->GetCenter());
					
					if (dist < 24 * 24)
					{
						m_goal = nullptr;
						m_reachedGoal = true;
					}
				}
			}
		}
		break;
	case DIE:
		if (this->m_dying++ < 4 * 8)
		{
			this->Stop();
			this->GetAnimator()->SetNextAnimation("die");
		}
		else
		{
			this->clean();
		}
		break;
	default:
		break;
	}
}

void RedSniper::update()
{
	MakeDecision();

	if (m_damaged-- > 0)
	{
		this->GetAnimator()->SetNextAnimation("damaged");
	}
	
	EnemyUpdate();
}
