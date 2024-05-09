#pragma once

#include "DataStruct.h"
namespace Engine {
	class GameObject;
	class Scene
	{
		//하이어라키에 들어갈 gameObject를 어떤 구조로 넣을지

		// 1. 메인 하이어라키
		//	 => gameObject1					-> gameObject2 ->			  ->... gameObjectN;
		//    V (componenet1<GameObject1>)   V(componenet1<GameObject2>)   V
		//    V (componenet2<GameObject1>)   V(componenet1<GameObject2>)   V
		// 이번에 배운 연결리스트로 메인 하이어라키에 게임 오브젝트를 넣고
		// 넣은 게임 오브젝트는 다음 게임 오브젝트를 가리키는 포인터 주소와
		// 본인에게 붙는 컴포넌트를 가리킬 포인터 주소, (이 때 각 컴포넌트는 다음 컴포넌트를 가리키는 주소를 가지고 있음)
		// (추가로 컴포넌트의 마지막을 첫번째 주소와 연결해 원형처럼 만들고 검색을 한다면 자기 자신 컴포넌트부터 자기 자신 컴포넌트까지 검색해서 찾기도 가능할 지도?)
		// (또는 해당 게임오브젝트의 컴포넌트를 찾을 때 게임오브젝트부터 시작해서 컴포넌트 끝까지 검색하는 방식으로?)
		// 본인의 자식 게임오브젝트를 가리킬 포인터 주소 3가지를 가지게 됨.

		// 나중에 컴포넌트를 검색 할 일이 있다면 stack미로처럼 주소를 저장하고 돌아오는 방식으로 찾아서 리턴.

		// 정리하면 
		// 메인 하이어라키부터 시작해서 게임 오브젝트를 단일연결리스트로 연결.
		// 각 게임오브젝트 마다 컴포넌트와 자식 오브젝트를 가리킬 주소를 가짐.
		// 어떤 컴포넌트가 게임오브젝트 안의 다른 컴포넌트를 찾을 때 해당 게임오브젝트부터 시작하여 마지막 컴포넌트까지 검색하여 리턴.
		// (unity의 tryGetComponent도 구현가능 할 듯?)
		// 이를 위한 class이름이 맞는지 체크할 수 있는 기능?
		// 유니티로치면 class A가 있을 때 A temp;를 선언하면
		// if(temp is A)로 구분 가능한데 이게 c++에 있는가? dynamic_cast라는 기능이 있음
		// 만약 비용이 많이드는 작업이라면 compoenetName같은 string으로 저장하여 비교하는 식으로 찾아야할 듯. 
		// (class이름을 가져오는 기능이 있다면 처음 초기화 하는 방식을 써도 좋고?)

		// Scene -> hierarchy -> GameObject -> childGameObejct
		// GameObject -> Components
	public:
		DoubleLinkedList<GameObject*> hierarchy;
	};
}

// 상속받는 객체는 부모객체의 정보를 include로 저장하고 맴버 변수로 받을 객체의 정보는 class classname; 형식으로 저장.
