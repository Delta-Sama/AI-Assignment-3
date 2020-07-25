#include "UIManager.h"

#include <iostream>

std::vector<UIObject*> UIMA::s_UIObjects;

void UIManager::Update()
{
	for (std::vector<UIObject*>::iterator obj = s_UIObjects.begin(); obj != s_UIObjects.end();)
	{
		if (!(*obj)->GetActive())
		{
			delete (*obj);
			obj = s_UIObjects.erase(obj);
		}
		else
		{
			(*obj)->Update();
			obj++;
		}
	}
}

void UIManager::Render(Priority priority)
{
	for (UIObject* obj : s_UIObjects)
	{
		if (obj->GetPriority() == priority)
		{
			obj->Render();
		}
	}
}

void UIManager::AddObject(UIObject* obj)
{
	s_UIObjects.push_back(obj);
}
