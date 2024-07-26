#pragma once
#include "Component.h"
#include "AABB.h"
#include <vector>
class Camera : public Component
{
	//static std::vector<Camera*> allCamera;
public:
	Camera() {
		//allCamera.push_back(this);
	};
	virtual ~Camera() {
		/*auto it = std::find(allCamera.begin(), allCamera.end(), this);
		if (it != allCamera.end()) {
			allCamera.erase(it);
		}*/
	};

	AABB cameraRect;
};

