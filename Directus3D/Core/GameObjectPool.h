/*
Copyright(c) 2016 Panos Karabelas

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is furnished
to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR
COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#pragma once

//= INCLUDES ============================
#include "../Multithreading/ThreadPool.h"
//=======================================

class GameObject;

class GameObjectPool
{
public:
	GameObjectPool();
	~GameObjectPool();

	static GameObjectPool& GetInstance()
	{
		static GameObjectPool instance;
		return instance;
	}

	void Initialize(Context* context);
	void Start();
	void Update();
	void Release();
	void Clear();

	/*------------------------------------------------------------------------------
									[I/O]
	------------------------------------------------------------------------------*/
	void Serialize();
	void Deserialize();

	/*------------------------------------------------------------------------------
									[MISC]
	------------------------------------------------------------------------------*/
	std::vector<GameObject*> GetAllGameObjects();
	std::vector<GameObject*> GetRootGameObjects();
	GameObject* GetGameObjectRoot(GameObject* gameObject);
	int GetGameObjectCount();
	int GetGameObjectIndex(GameObject* gameObject);
	GameObject* GetGameObjectByName(const std::string& name);
	GameObject* GetGameObjectByIndex(int index);
	GameObject* GetGameObjectByID(const std::string& ID);
	const std::vector<GameObject*>& GetGameObjectsByParentID(const std::string& ID);
	bool GameObjectExists(GameObject* gameObject);
	bool GameObjectExistsByName(const std::string& name);
	void RemoveGameObject(GameObject* gameObject);
	void RemoveSingleGameObject(GameObject* gameObject);

	/*------------------------------------------------------------------------------
								[CALLED BY GAMEOBJECTS]
	------------------------------------------------------------------------------*/
	void AddGameObjectToPool(GameObject* gameObject);

private:
	std::vector<GameObject*> m_gameObjectPool;
	Context* m_context;
};