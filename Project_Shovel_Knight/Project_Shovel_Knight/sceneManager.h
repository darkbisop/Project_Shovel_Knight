#pragma once
#include "singletonBase.h"

class scene;

class sceneManager :public singletonBase<sceneManager>
{
private:
	map<string, scene*>	m_mapScenes;
	map<string, scene*>::iterator	m_iter;

	map<string, scene*>	m_mapLoadingScenes;
	map<string, scene*>::iterator	m_iterLoading;

	static scene*	m_pCurrScene;	// ���� ��
	static scene*	m_pNextScene;	// ��ȯ ��� ���� ��
	static scene*	m_pLoadingScene;// �ε� ��	

public:
	HRESULT init();
	void release();
	void update();
	void render(HDC hdc);

	// �Ϲ� ��
	scene* addScene(string sceneName, scene* pScene);
	HRESULT changeScene(string sceneName);

	// Loading ���� ����
	scene* addLoadingScene(string loadingSceneName,
		scene* pScene);
	HRESULT changeScene(string nextSceneName,
		string loadingSceneName);

	// loading Thread���� ȣ���� �Լ�
	friend DWORD CALLBACK loadingThread(LPVOID prc);

	sceneManager();
	~sceneManager();
};
