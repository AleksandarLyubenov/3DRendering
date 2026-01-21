#ifndef LIGHT_HPP
#define LIGHT_HPP

#include "../../glm.hpp"
#include "GameObject.hpp"

/**
 * Exercise for the student: implement the Light class...
 * Imagine things like setLightType, setLightIntensity, setFalloffAngle etc, see the corresponding lectures
 */
class Light : public GameObject
{
	public:
		Light(const std::string& aName = nullptr, const glm::vec3& aPosition = glm::vec3( 2.0f, 10.0f, 5.0f ) );
		virtual ~Light();

        //override set parent to register/deregister light...
        virtual void _setWorldRecursively (World* pWorld) override;

		float getConstantAttenuation() const;
		void setConstantAttenuation(float value);

		float getLinearAttenuation() const;
		void setLinearAttenuation(float value);

		float getQuadraticAttenuation() const;
		void setQuadraticAttenuation(float value);

		glm::vec3 getLightColor() const;
		void setLightColor(const glm::vec3& color);
	private:
		float _constantAttenuation = 1.0f;
		float _linearAttenuation = 0.09f;
		float _quadraticAttenuation = 0.032f;
		glm::vec3 _lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

};

#endif // LIGHT_HPP
