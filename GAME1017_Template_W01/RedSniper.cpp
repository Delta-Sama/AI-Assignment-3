#include "RedSniper.h"
#include "CollisionManager.h"
#include "EnemyManager.h"
#include "MathManager.h"
#include "TextureManager.h"

RedSniper::RedSniper(Vec2 pos) : Enemy(TEMA::GetTexture("enemy"), pos)
{
	this->addAnimator(new Animator(this));

	this->getAnimator()->addAnimation("idle", 3, 1, 34, 0, 0, 0, 16);
	this->getAnimator()->addAnimation("run", 8, 2, 34, 0, 0, 34);

	m_status = PATROL;
}

RedSniper::~RedSniper()
{
	
}

void RedSniper::MakeDecision()
{
	switch (m_status)
	{
	case IDLE:
		
		break;
	case PATROL:
		{
			if (m_pathManager.goalCounter++ > 60 * 2.5)
			{
				for (int i = 0; i < PREVNODESSIZE; i++)
				{
					m_pathManager.prevNode[i] = nullptr;
				}
				std::cout << "Failed to reach\n";
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
					
					float angle = MAMA::AngleBetweenPoints((m_goal->y - this->GetCenter().y), (m_goal->x - this->GetCenter().x));
					angle = MAMA::Rad2Deg(angle) + 90;

					double dif = MAMA::Angle180(angle - (float)this->GetAngle());
					
					this->SetAngle(this->GetAngle() + std::max(std::min(dif, 5.0), -5.0));

					if (dif < 50.0)
					{
						float dx = m_goal->x - this->GetCenter().x;
						float dy = m_goal->y - this->GetCenter().y;
						float hyp = sqrt(dx * dx + dy * dy);
						dx = dx / hyp;
						dy = dy / hyp;

						this->SetAccelX(dx * SPEED);
						this->SetAccelY(dy * SPEED);
					}

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
	default:
		break;
	}
}

void RedSniper::update()
{
	m_playerLOS = COMA::LOSCheck(&ENMA::GetScene()->GetPlayer()->GetCenter(), &this->GetCenter());

	MakeDecision();
	
	movementUpdate();

	if (this->GetVelX() == 0 and this->GetVelY() == 0)
		this->getAnimator()->setNextAnimation("idle");
	else
		this->getAnimator()->setNextAnimation("run");

	this->getAnimator()->playAnimation();
	
	this->SetBodyPosition();
}
