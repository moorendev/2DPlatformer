#include "Gamescene.h"
#include "Utilities.h"

Gamescene::Gamescene(std::string name)
	:Scene(name)
{
	//No gravity this is top down scene
	m_gravity = b2Vec2(0.f, -200.f);
	m_physicsWorld->SetGravity(m_gravity);
}

void Gamescene::InitScene(float windowWidth, float windowHeight)
{
	//Dynamically allocated the register
	m_sceneReg = new entt::registry;
	//Attatch the register
	ECS::AttachRegister(m_sceneReg);

	//Sets up aspect ratio for the camera
	float aspectRatio = windowWidth / windowHeight;

	//Setup MainCamera Entity
	{
		//Scene::CreateCamera(m_sceneReg,vec4(-75.f,75.f,-75.f,75.f)-100.f,100.f,windowWidth,widowHeight,true,true);
		//Creates camera entity
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainCamera(entity, true);

		//Creates new orthographic camera
		ECS::AttachComponent<Camera>(entity);
		ECS::AttachComponent<HorizontalScroll>(entity);
		ECS::AttachComponent<VerticalScroll>(entity);

		vec4 temp = vec4(-75.f, 75.f, -75.f, 75.f);
		ECS::GetComponent<Camera>(entity).SetOrthoSize(temp);
		ECS::GetComponent<Camera>(entity).SetWindowSize(vec2(float(windowWidth), float(windowHeight)));
		ECS::GetComponent<Camera>(entity).Orthographic(aspectRatio, temp.x, temp.y, temp.z, temp.w, -100.f, 100.f);

		//Attatches the Camera
		ECS::GetComponent<HorizontalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));
		ECS::GetComponent<VerticalScroll>(entity).SetCam(&ECS::GetComponent<Camera>(entity));


	}
	//Setup new Entity
	{
		//Scene::CreatSprite(m_sceneReg,"HelloWorld.png",100,60,0.5f,vec3(0.f,0.f,0.f));
		//creates entity
		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);

		//Set up the components
		std::string fileName = "super.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 100, 60);
		ECS::GetComponent<Sprite>(entity).SetTransparency(0.5f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 50.f, 0.f));

	}
	//Link entity
	{
		//Scene::CreatePhysicsSprite(m_sceneRed,"LinkStandby:,80,60,1.f,vec3(0.f,30.f,2.f)b2_dynamicBody,0.f,0.f,true,true);
		auto entity = ECS::CreateEntity();
		ECS::SetIsMainPlayer(entity, true);

		//Add components
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//sets up the components
		std::string fileName = "mario.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 25, 25);
		ECS::GetComponent<Sprite>(entity).SetTransparency(1.f);
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(0.f, 30.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;


		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_dynamicBody;
		tempDef.position.Set(float32(0.f), float32(30.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false);

		ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer()).GetBody()->SetFixedRotation(true);


	}
	//Setup Box
	//{
	//	//Creates entity
	//	auto entity = ECS::CreateEntity();

	//	//Add components
	//	ECS::AttachComponent<Sprite>(entity);
	//	ECS::AttachComponent<Transform>(entity);
	//	ECS::AttachComponent<PhysicsBody>(entity);

	//	//sets up components
	//	std::string fileName = "qsmark.png";
	//	ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 20, 20);
	//	ECS::GetComponent<Transform>(entity).SetPosition(vec3(-30.f, -30.f, 2.f));

	//	auto& tempSpr = ECS::GetComponent<Sprite>(entity);
	//	auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

	//	float shrinkX = 0.f;
	//	float shrinkY = 0.f;

	//	b2Body* tempBody;
	//	b2BodyDef tempDef;

	//	tempDef.type = b2_dynamicBody;
	//	tempDef.position.Set(float32(-30.f), float32(-20.f));

	//	tempBody = m_physicsWorld->CreateBody(&tempDef);

	//	tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false);

	//}

	{

	}

	//setup static box
	{
		//creates entity
		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up componets
		std::string fileName = "brick.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 23440, 40);;
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(20.f), float32(-20.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false);


	}
	{
		//creates entity
		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up componets
		std::string fileName = "brick.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 40, 5);;
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(200.f), float32(30.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false);


	}

	{
		//creates entity
		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up componets
		std::string fileName = "brick.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 70, 20);;
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(100.f), float32(10.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false);


	}

	{
		//creates entity
		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up componets
		std::string fileName = "brick.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 50, 20);;
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(100.f), float32(30.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false);


	}
	{
		//creates entity
		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up componets
		std::string fileName = "brick.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 30, 20);;
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(100.f), float32(50.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false);


	}
	{
		//creates entity
		auto entity = ECS::CreateEntity();
		ECS::AttachComponent<Sprite>(entity);
		ECS::AttachComponent<Transform>(entity);
		ECS::AttachComponent<PhysicsBody>(entity);

		//Sets up componets
		std::string fileName = "brick.png";
		ECS::GetComponent<Sprite>(entity).LoadSprite(fileName, 10, 20);;
		ECS::GetComponent<Transform>(entity).SetPosition(vec3(30.f, -20.f, 2.f));

		auto& tempSpr = ECS::GetComponent<Sprite>(entity);
		auto& tempPhsBody = ECS::GetComponent<PhysicsBody>(entity);

		float shrinkX = 0.f;
		float shrinkY = 0.f;
		b2Body* tempBody;
		b2BodyDef tempDef;
		tempDef.type = b2_staticBody;
		tempDef.position.Set(float32(100.f), float32(70.f));

		tempBody = m_physicsWorld->CreateBody(&tempDef);

		tempPhsBody = PhysicsBody(tempBody, float(tempSpr.GetWidth() - shrinkX), float(tempSpr.GetHeight() - shrinkY), vec2(0.f, 0.f), false);


	}
	ECS::GetComponent<HorizontalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	ECS::GetComponent<VerticalScroll>(MainEntities::MainCamera()).SetFocus(&ECS::GetComponent<Transform>(MainEntities::MainPlayer()));
	
}

void Gamescene::Update()
{
	Scene::AdjustScrollOffset();
}


void Gamescene::KeyboardHold()
{
	auto& player = ECS::GetComponent<PhysicsBody>(MainEntities::MainPlayer());
	float speed = 10.f;
	b2Vec2 vel = b2Vec2(0.f, 0.f);

	if (Input::GetKey(Key::Shift))
	{
		speed *= 3.f;
	}

	if (Input::GetKey(Key::W))
	{
		vel += b2Vec2(0.f, 1.f);

	}
	/*if (Input::GetKey(Key::S))
	{
		vel += b2Vec2(0.f, -1.f);

	}*/
	if (Input::GetKey(Key::A))
	{
		vel += b2Vec2(-1.f, 0.f);

	}
	if (Input::GetKey(Key::D))
	{
		vel += b2Vec2(1.f, 0.f);

	}
	player.GetBody()->SetLinearVelocity(speed * vel);
}

void Gamescene::KeyboardDown()
{
}

void Gamescene::KeyboardUp()
{
}

