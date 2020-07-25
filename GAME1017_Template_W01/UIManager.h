#pragma once
#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_

#include "UIObject.h"

#include <vector>



class UIManager
{
public:
	static void Update();
	static void Render(Priority priority);

	static void AddObject(UIObject* obj);
	
private:
	static std::vector<UIObject*> s_UIObjects;
	
};

typedef UIManager UIMA;

#endif