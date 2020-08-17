#include "LeavingState.h"

#include "EnemyManager.h"

const float LEAVESPEED = 4.0;

LeavingState::LeavingState(Enemy* enemy) : BehaviorState(enemy)
{
}

LeavingState::~LeavingState() = default;

void LeavingState::Enter()
{
	dx = m_entity->GetCenter().x - WIDTH / 2.0;
	dy = m_entity->GetCenter().y - HIGH / 2.0;
	float len = sqrt(pow(dx, 2) + pow(dy, 2));
	dx /= len;
	dy /= len;

	float angle = MAMA::AngleBetweenPoints(dy, dx);
	m_entity->SetAngle(MAMA::Rad2Deg(angle) + 90);
	
	m_frame = 120;
	
	m_entity->SetCollidable(false);
}

void LeavingState::Update()
{
	m_frame--;
	m_entity->GetDstP()->x += dx * LEAVESPEED;
	m_entity->GetDstP()->y += dy * LEAVESPEED;
	m_entity->GetMoveEngine()->SetMove(true);
}

void LeavingState::Transition()
{
	if (m_frame <= 0)
	{
		Exit();
		return;
	}
}

void LeavingState::Exit()
{
	m_entity->Clean();

	EnemyType type = rand() % 2 == 0 ? RANGETYPE: MELEETYPE;
	PathNode* point = (*ENMA::GetScene()->GetLevel()->GetPatrolPath())[rand() % ENMA::GetScene()->GetLevel()->GetPatrolPath()->size()];
	ENMA::LateAddEnemy(type, { point->x / 48.0f,point->y / 48.0f }, (rand() % 12) * 30);
}
