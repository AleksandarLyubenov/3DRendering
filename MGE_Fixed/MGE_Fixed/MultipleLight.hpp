#ifndef MULTIPLELIGHT_HPP
#define MULTIPLELIGHT_HPP

#include "glm.hpp"
#include "mge/core/GameObject.hpp"

/**
 * Exercise for the student: implement the Light class...
 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
 */
class MultipleLight : public GameObject
{
public:
	MultipleLight(const std::string& aName = nullptr, const glm::vec3& aPosition = glm::vec3(2.0f, 10.0f, 5.0f));
	virtual ~MultipleLight();

	//override set parent to register/deregister light...
	virtual void _setWorldRecursively(World* pWorld) override;

	float getConstantAttenuation() const;
	void setConstantAttenuation(float value);

	float getLinearAttenuation() const;
	void setLinearAttenuation(float value);

	float getQuadraticAttenuation() const;
	void setQuadraticAttenuation(float value);
private:
	float _constantAttenuation = 1.0f;
	float _linearAttenuation = 0.09f;
	float _quadraticAttenuation = 0.032f;

};

#endif // MULTIPLELIGHT_HPP
