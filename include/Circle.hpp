#ifndef CIRCLE_H
#define CIRCLE_H

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

class Circle : public Entity, sf::CircleShape {
private:
	sf::CircleShape m_circle;
	float			m_radius	{ 1.0f };

public:
	Circle()	{};
	~Circle()	{};

	void			setRadius(float radius);
	float			getRadius()						const;

	void			setSizeData(std::ifstream& fin) override;
	sf::FloatRect	getLocalBounds()				override;
	sf::FloatRect	getGlobalBounds()				override;
	std::size_t		getPointCount()					const override;
	sf::Vector2f	getPoint(std::size_t index)		const override;
	sf::Shape&		getEntity()						override;
};

#endif // CIRCLE_H