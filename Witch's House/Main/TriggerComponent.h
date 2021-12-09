//#pragma once
//
//#include "Component.h"
//
//class Collider : public Component
//{
//public:
//	virtual void Update()
//	{
//		if (PhysicsManager::GetInstance()->CheckCollide())
//		{
//			_owner->GetComponent<TriggerComponent>()->OnCollision();
//		}
//	}
//private:
//};
//
//class TriggerComponent : public Component
//{
//public:
//	virtual void OnCollision()
//	{
//		// Á×´Â´Ù ~
//	}
//	
//};
//
//class DieComponent : public Component
//{
//public:
//	virtual void Update()
//	{
//		if (Player::GetPos() == _owner->GetPos())
//		{
//			
//		}
//	}
//};