#include "Enemy.h"
#include "CollisionManager.h"
#include "Config.h"
#include "EnemyManager.h"
#include "MathManager.h"
#include "PathManager.h"
#include "SoundManager.h"
#include "TextureManager.h"
#include "Util.h"

Enemy::Enemy(SDL_Texture* t, Vec2 pos, float maxHealth, EnemyType enemyType)
: Entity({0,0,34,34},{pos.x * 48,pos.y * 48,60,60},t,maxHealth), m_enemyType(enemyType)
{
	this->m_body = { 0,0,35,35 };
	this->SetBodyPosition();

	this->SetType(ENEMY);
	
	this->m_healthBar = new HealthBar(this);

	this->m_AIState = new AIState(this);
	
	this->m_active = true;

	this->m_fleeCounter = 0;
	this->m_coveringTime = 0;
	this->m_hideTime = 0;
}

Enemy::~Enemy()
{
	if (this->m_AIState)
		delete this->m_AIState;
}

void Enemy::EnemyUpdate()
{
	SDL_FPoint PlayerCenter = ENMA::GetScene()->GetPlayer()->GetCenter();
	SDL_FPoint this_center = GetCenter();
	this->m_playerLOS = COMA::LOSCheck(&PlayerCenter, &this->GetCenter());
	this->m_playerDetectRad = MAMA::Distance(PlayerCenter, this_center) < DETECT_RADIUS;

	this->MovementUpdate();

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

	if (this->IsMoving())
		this->GetAnimator()->SetNextAnimation("run");
	else
		this->GetAnimator()->SetNextAnimation("idle");

	this->GetAnimator()->Update();

	m_shortestNode = COMA::GetClosestTunnelNode(GetCenter());
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

	if (dif < MIN_MOVE_ANGLE_DISTANCE)
	{
		float dx = goal.x - this->GetCenter().x;
		float dy = goal.y - this->GetCenter().y;
		float hyp = sqrt(dx * dx + dy * dy);
		dx = dx / hyp;
		dy = dy / hyp;

		m_moveEngine->SetAccelX(dx * SPEED);
		m_moveEngine->SetAccelY(dy * SPEED);

		m_moveEngine->SetMove(true);
	}

	if (MAMA::SquareDistance(&GetCenter(),&goal) < pow(MIN_SEEK_DISTANCE,2))
	{
		return true;
	}
	return false;
}

void Enemy::Flee()
{
	float dif = 30.0;
	
	if (m_fleeCounter++ > 0)
	{
		m_fleeCounter = 0;
		
		PathNode* LOS_node = nullptr;
		long max_dist = 0;
		
		SDL_FPoint player_center = ENMA::GetPlayer()->GetCenter();
		
		float start_angle = MAMA::Rad2Deg(MAMA::AngleBetweenPoints(GetCenter().y - player_center.y, GetCenter().x - player_center.x));
		long plr_ent_dist = (long int)MAMA::SquareDistance(&GetCenter(), &player_center);
		
		//Util::QueueLine(GetCenter(), player_center, { 1,1,0,1 });
		
		if (plr_ent_dist < pow(AVOID_DISTANCE, 2))
			dif = 360.0;

		start_angle = MAMA::Angle180(start_angle);

		for (int i = 0; i < 2; i++)
		{
			for (PathNode* node : *PAMA::GetNodes())
			{
				SDL_FPoint temp_pos = { node->x, node->y };
				if (not COMA::TunnelLOSCheck(&temp_pos,&player_center,TUNNEL_ENTITY_WIDTH))
				{
					long plr_node_dist = (long int)MAMA::SquareDistance(&player_center, &temp_pos);
					long ent_node_dist = (long int)MAMA::SquareDistance(&GetCenter(), &temp_pos);
					long plr_node_angle = MAMA::Rad2Deg(MAMA::AngleBetweenPoints(temp_pos.y - player_center.y, temp_pos.x - player_center.x));
					bool node_in_view = abs(start_angle - MAMA::Angle180(plr_node_angle)) < dif;
			
					if (node_in_view)
					{
						//Util::QueueLine(temp_pos,player_center,{0,0,1,1});
						if (plr_node_dist > max_dist)
						{
							max_dist = plr_node_dist;
							LOS_node = node;
						}
					}
				}
			}
			if (LOS_node)
			{
				break;
			}
			else
			{
				dif = 360.0;
			}
		}
		
		if (LOS_node and GetShortestLOSNode())
		{
			std::cout << "New path flee\n";
			//Util::QueueCircle(*LOS_node,10,{0,1,0,1});
			m_fleePath = PAMA::GetShortestPath(GetShortestLOSNode(), LOS_node, true);
		}
	}
	if (not m_fleePath.empty())
	{
		FollowThePath(m_fleePath);
		for (int i = 0; i < m_fleePath.size(); i++)
		{
			PathNode* from = m_fleePath[i]->GetFromNode();
			PathNode* to = m_fleePath[i]->GetToNode();
			//Util::QueueLine({ from->x, from->y }, { to->x, to->y }, { 1,0,0,1 });
		}
	}
}

void Enemy::FollowThePath(std::vector<PathConnection*>& path)
{
	if (not path.empty())
	{
		SDL_FPoint from_point = { path.back()->GetFromNode()->x, path.back()->GetFromNode()->y };
		SDL_FPoint to_point = { path.back()->GetToNode()->x, path.back()->GetToNode()->y };

		// If can go directly to the "ToNode"
		if (COMA::TunnelLOSCheck(&to_point, &GetCenter(), TUNNEL_ENTITY_WIDTH))
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
