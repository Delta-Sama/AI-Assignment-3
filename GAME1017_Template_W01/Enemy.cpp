#include "Enemy.h"
#include "CollisionManager.h"
#include "Config.h"
#include "EnemyManager.h"
#include "MathManager.h"
#include "SoundManager.h"
#include "TextureManager.h"

Enemy::Enemy(SDL_Texture* t, Vec2 pos, float maxHealth) : Entity({0,0,34,34},{pos.x * 48,pos.y * 48,60,60},t,maxHealth)
{
	this->m_body = { 0,0,35,35 };
	this->SetBodyPosition();

	this->SetType(ENEMY);
	
	this->m_healthBar = new HealthBar(this);

	this->m_active = true;

	std::cout << "Enemy created\n";
}

Enemy::~Enemy()
{
}

void Enemy::EnemyUpdate()
{
	SDL_FPoint PlayerCenter = ENMA::GetScene()->GetPlayer()->GetCenter();
	this->m_playerLOS = COMA::LOSCheck(&PlayerCenter, &this->GetCenter());
	this->m_playerDetectRad = MAMA::Distance(this->GetCenter().x, PlayerCenter.x, this->GetCenter().y, PlayerCenter.y) < DETECTRADIUS;

	this->MovementUpdate();

	if (m_moveEngine->GetVelX() == 0 and m_moveEngine->GetVelY() == 0)
		this->GetAnimator()->SetNextAnimation("idle");
	else
		this->GetAnimator()->SetNextAnimation("run");

	this->GetAnimator()->PlayAnimation();

	this->SetBodyPosition();

	if (m_health <= 0 and this->m_status != DIE)
	{
		SOMA::PlaySound("dead", 0, 5);
		this->m_healthBar->SetEnabled(false);
		this->m_status = DIE;
	}
}

void Enemy::Clean()
{
	this->m_active = false;
	this->m_healthBar->SetActive(false);
}

void Enemy::Seek(SDL_FPoint& goal)
{
	float angle = MAMA::AngleBetweenPoints((goal.y - this->GetCenter().y), (goal.x - this->GetCenter().x));
	angle = MAMA::Rad2Deg(angle) + 90;

	double dif = MAMA::Angle180(angle - (float)this->GetAngle());

	this->SetAngle(this->GetAngle() + std::max(std::min(dif, 5.0), -5.0));

	if (dif < 50.0)
	{
		float dx = goal.x - this->GetCenter().x;
		float dy = goal.y - this->GetCenter().y;
		float hyp = sqrt(dx * dx + dy * dy);
		dx = dx / hyp;
		dy = dy / hyp;

		m_moveEngine->SetAccelX(dx * SPEED);
		m_moveEngine->SetAccelY(dy * SPEED);
	}
}

void Enemy::CleanLocalPath()
{
	m_pathManager.CleanNodes();
	SetGoal(nullptr);
}
