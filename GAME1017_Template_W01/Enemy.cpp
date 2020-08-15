#include "Enemy.h"
#include "CollisionManager.h"
#include "Config.h"
#include "EnemyManager.h"
#include "MathManager.h"
#include "PathManager.h"
#include "SoundManager.h"
#include "TextureManager.h"

Enemy::Enemy(SDL_Texture* t, Vec2 pos, float maxHealth) : Entity({0,0,34,34},{pos.x * 48,pos.y * 48,60,60},t,maxHealth)
{
	this->m_body = { 0,0,35,35 };
	this->SetBodyPosition();

	this->SetType(ENEMY);
	
	this->m_healthBar = new HealthBar(this);

	this->m_AIState = new AIState(this);
	
	this->m_active = true;
}

Enemy::~Enemy()
{
	if (this->m_AIState)
		delete this->m_AIState;
}

void Enemy::EnemyUpdate()
{
	SDL_FPoint PlayerCenter = ENMA::GetScene()->GetPlayer()->GetCenter();
	this->m_playerLOS = COMA::LOSCheck(&PlayerCenter, &this->GetCenter());
	this->m_playerDetectRad = MAMA::Distance(this->GetCenter().x, PlayerCenter.x, this->GetCenter().y, PlayerCenter.y) < DETECTRADIUS;

	this->MovementUpdate();

	if (this->m_moveEngine->GetVelX() != 0 or this->m_moveEngine->GetVelY() != 0)
		this->GetAnimator()->SetNextAnimation("run");
	
	this->GetAnimator()->Update();

	this->SetBodyPosition();

	if (this->m_damaged > 0)
	{
		this->m_damaged--;
		this->GetAnimator()->SetNextAnimation("damaged");
	}
	
	if (this->m_health <= 0 and this->m_status != DIE)
	{

		this->m_AIState->ChangeState(DIE);
	}

	m_shortestNode = nullptr;
	long min_dist = 99999;
	
	for (PathNode* node : *PAMA::GetNodes())
	{
		SDL_FPoint temp_pos = { node->x, node->y };
		if (COMA::TunnelLOSCheck(&temp_pos,&GetCenter(),TUNNELENTITYWIDTH))
		{
			long dist = (long)MAMA::SquareDistance(&GetCenter(), &temp_pos);
			
			if (dist < min_dist)
			{
				min_dist = dist;
				m_shortestNode = node;
			}
		}
	}
}

void Enemy::Clean()
{
	this->m_active = false;
	this->m_healthBar->SetActive(false);
}

bool Enemy::Seek(SDL_FPoint& goal)
{
	float angle = MAMA::AngleBetweenPoints((goal.y - this->GetCenter().y), (goal.x - this->GetCenter().x));
	double dif = SetSmoothAngle(angle);

	if (dif < MINMOVEANGLEDISTANCE)
	{
		float dx = goal.x - this->GetCenter().x;
		float dy = goal.y - this->GetCenter().y;
		float hyp = sqrt(dx * dx + dy * dy);
		dx = dx / hyp;
		dy = dy / hyp;

		m_moveEngine->SetAccelX(dx * SPEED);
		m_moveEngine->SetAccelY(dy * SPEED);
	}

	if (MAMA::SquareDistance(&GetCenter(),&goal) < pow(MINSEEKDISTANCE,2))
	{
		return true;
	}
	return false;
}

void Enemy::FollowThePath(std::vector<PathConnection*>& path)
{
	if (not path.empty())
	{
		SDL_FPoint from_point = { path.back()->GetFromNode()->x, path.back()->GetFromNode()->y };
		SDL_FPoint to_point = { path.back()->GetToNode()->x, path.back()->GetToNode()->y };

		// If can go directly to the "ToNode"
		if (COMA::TunnelLOSCheck(&to_point, &GetCenter(), TUNNELENTITYWIDTH))
		{
			//Util::QueueCircle({ to_point.x, to_point.y }, 10, { 1,0,0,1 });
			if (Seek(to_point))
			{
				path.pop_back(); // Pop if reached
			}
		}
		else // Else go to the "FromNode"
		{
			//Util::QueueCircle({ from_point.x, from_point.y }, 10, { 1,0,0,1 });
			Seek(from_point);
		}

	}
}

void Enemy::CleanLocalPath()
{
	m_pathManager.CleanNodes();
	SetGoal(nullptr);
}
