#include "SceneGame.h"
#include "GL\glew.h"
#include "../Application.h"

#include "../Message/PostOffice.h"
#include "../Message/ConcreteMessages.h"

//Include States Here


//Include Others Here
#include "../SpriteAnimation/SpriteAnimation.h"

#include <sstream>

/****************************************************************
// TODO //

*****************************************************************/

SceneGame::SceneGame()
{
}

SceneGame::~SceneGame()
{
}

/*********************************
* INIT *
*********************************/
void SceneGame::Init()
{
	SceneBase::Init();

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//Physics code here
	m_speed = 1.f;

	Math::InitRNG();

	PostOffice::GetInstance()->Register("GAME", this); //Register into Message System

	//SpriteAnimation* sa = dynamic_cast<SpriteAnimation*>(meshList[GEO_SPRITE1]);
	//if (sa)
	//{
	//	sa->m_anim = new Animation();
	//	sa->m_anim->Set(0, 4, 0, 1.0f, true);
	//}
}


/*********************************
* CREATION AND HANDLES *
*********************************/
// Create New GameObjects (GameObjects) and put in GOList //
GameObject* SceneGame::FetchGO(GameObject::TYPE type)
{
	for (std::vector<GameObject *>::iterator it = m_goList.begin(); it != m_goList.end(); ++it)
	{
		GameObject *go = (GameObject *)*it;
		if (!go->active && go->type == type)
		{
			go->active = true;
			++m_objectCount;
			go->id = m_objectCount;
			return go;
		}
	}

	for (unsigned i = 0; i < 5; ++i)
	{
		GameObject *go = new GameObject(type);
		m_goList.push_back(go);
	}
	return FetchGO(type);
}

// Messages for states //
bool SceneGame::Handle(Message * message)
{
	MessageWRU *messageWRU = dynamic_cast<MessageWRU*>(message);

	if (messageWRU)
	{
		switch (messageWRU->type)
		{
		// REFERENCE
		//case MessageWRU::MESSAGE_GETNEXTNODE_NORMAL:
		//	GetNextNode_NormalMinion(messageWRU->go_dota);
		//	break;

		}
		delete message;
		return true;
	}
	delete message;
	return false;
}

/*********************************
* UPDATE *
*********************************/
void SceneGame::Update(double dt)
{
	SceneBase::Update(dt);

	//Calculating aspect ratio
	m_worldHeight = 100.f;
	m_worldWidth = m_worldHeight * (float)Application::GetWindowWidth() / Application::GetWindowHeight();

	//============ Input Section ============//
	if (Application::IsKeyPressed(VK_OEM_MINUS))
	{
		m_speed = Math::Max(0.f, m_speed - 0.1f);
	}
	if (Application::IsKeyPressed(VK_OEM_PLUS))
	{
		m_speed += 0.1f;
	}
	if (Application::IsKeyPressed('N'))
	{
	}
	if (Application::IsKeyPressed('M'))
	{
	}
	if (Application::IsKeyPressed(VK_RETURN))
	{
	}
	if (Application::IsKeyPressed('R'))
	{
	}

	static bool bLButtonState = false;
	if (!bLButtonState && Application::IsMousePressed(0))
	{
		bLButtonState = true;
		std::cout << "LBUTTON DOWN" << std::endl;
		double x, y;
		Application::GetCursorPos(&x, &y);
		int w = Application::GetWindowWidth();
		int h = Application::GetWindowHeight();
		float posX = static_cast<float>(x) / w * m_worldWidth;
		float posY = (h - static_cast<float>(y)) / h * m_worldHeight;
		if (posX < m_worldHeight && posY < m_worldHeight)
		{
		}
	}
	else if (bLButtonState && !Application::IsMousePressed(0))
	{
		bLButtonState = false;
		std::cout << "LBUTTON UP" << std::endl;
	}
	static bool bRButtonState = false;
	if (!bRButtonState && Application::IsMousePressed(1))
	{
		bRButtonState = true;
		std::cout << "RBUTTON DOWN" << std::endl;
	}
	else if (bRButtonState && !Application::IsMousePressed(1))
	{
		bRButtonState = false;
		std::cout << "RBUTTON UP" << std::endl;
	}
	static bool bSpaceState = false;
	if (!bSpaceState && Application::IsKeyPressed(VK_SPACE))
	{
		bSpaceState = true;
	}
	else if (bSpaceState && !Application::IsKeyPressed(VK_SPACE))
	{
		bSpaceState = false;
	}

	//============ Gameplay ============//


	//============ Sprite ==============//
	//SPRITE
	//SpriteAnimation *sa = dynamic_cast<SpriteAnimation
	//	*>(meshList[GEO_SPRITE1]);
	//if (sa)
	//{
	//	sa->Update(dt);
	//	sa->m_anim->animActive = true;
	//}
}

/*********************************
* RENDER *
*********************************/
void SceneGame::RenderGO(GameObject *go)
{
	switch (go->type)
	{
		// REFERENCE
	//case GameObject::DO_KNIGHT:
	//	modelStack.PushMatrix(); //<< START MODELSTACK PUSH
	//	modelStack.Translate(go->pos.x, go->pos.y, go->id * 0.001f);

	//	modelStack.PushMatrix();//<< OBJECT SPRITE
	//	modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
	//	RenderMesh(meshList[GEO_BLUEKNIGHT], false);
	//	modelStack.PopMatrix();	//>> OBJECT SPRITE

	//	modelStack.PushMatrix();//<< HP BAR
	//	modelStack.Translate(-(1 - go->hp / go->maxhp), go->scale.x, 0);
	//	modelStack.Scale(go->hp / go->maxhp * go->scale.x, 0.5f, 0);
	//	RenderMesh(meshList[GEO_BLUEQUAD], false); 
	//	modelStack.PopMatrix(); //<< HP BAR

	//	modelStack.PopMatrix(); //<< END MODELSTACK POP
	//	break;

	//case GameObject::DO_EXPLOSION:
	//	modelStack.PushMatrix();
	//	modelStack.Translate(go->pos.x, go->pos.y, 2.f);
	//	modelStack.Scale(go->scale.x, go->scale.y, go->scale.z);
	//	RenderMesh(meshList[GEO_EXPLOSION], false);
	//	modelStack.PopMatrix();
	//	break;
	}
}

void SceneGame::RenderMap()
{
}

void SceneGame::Render()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Projection matrix : Orthographic Projection
	Mtx44 projection;
	projection.SetToOrtho(0, m_worldWidth, 0, m_worldHeight, -10, 10);
	projectionStack.LoadMatrix(projection);

	// Camera matrix
	viewStack.LoadIdentity();
	viewStack.LookAt(
		camera.position.x, camera.position.y, camera.position.z,
		camera.target.x, camera.target.y, camera.target.z,
		camera.up.x, camera.up.y, camera.up.z
	);
	// Model matrix : an identity matrix (model will be at the origin)
	modelStack.LoadIdentity();

	//RenderMesh(meshList[GEO_AXES], false);

	// Render Map and OBJ //
	RenderMap();

	for (auto go : m_goList)
	{
		if (go->active)
			RenderGO(go);
	}

	// Render Onscreen Text //
	//std::ostringstream ss;
	//ss.precision(3);
	//ss << "Speed:" << m_speed;
	//RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 6);

	//ss.str("");
	//ss.precision(5);
	//ss << "FPS:" << fps;
	//RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(0, 1, 0), 3, 50, 3);
}

// Exit //
void SceneGame::Exit()
{
	SceneBase::Exit();
	//Cleanup GameObjects
	while (m_goList.size() > 0)
	{
		GameObject *go = m_goList.back();
		delete go;
		m_goList.pop_back();
	}
}