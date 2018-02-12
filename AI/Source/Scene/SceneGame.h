#ifndef SCENE_GAME_H
#define SCENE_GAME_H

//#define DEBUG_COUT
//#define DEBUG_MINIONNORMAL
//#define DEBUG_MINIONGUARDIAN
//#define DEBUG_SAFETYCHECKS

#include "SceneBase.h"
#include "../GameObject.h"

#include <vector>
#include <queue>

class SceneGame : public SceneBase, public ObjectBase
{
public:
	SceneGame();
	~SceneGame();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();

	bool Handle(Message *message);

	GameObject* FetchGO(GameObject::TYPE type);
	void RenderGO(GameObject *go);

	void RenderMap();
	
protected:

	std::vector<GameObject *> m_goList;
	float m_speed;
	float m_worldWidth;
	float m_worldHeight;
	int m_objectCount;

	// Functions //

	// Player Variable //

	// Game //
};

#endif