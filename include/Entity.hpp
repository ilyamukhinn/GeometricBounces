#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

#include <string>
#include <unordered_map>

enum class EntityType {
	UNDEFINED = 0,
	CIRCLE,
	RECTANGLE
};

static std::unordered_map<std::string, EntityType> const entityTypeMap = {
	{ "Circle",		EntityType::CIRCLE},
	{ "Rectangle",	EntityType::RECTANGLE}
};

class Entity {
	EntityType		m_entityType		{ EntityType::UNDEFINED };
	std::string		m_name				{ "" };
	std::uint8_t	m_id				{ 0 };
	bool			m_drawEntity		{ true };
	sf::Vector2f	m_position			{ 0.0f, 0.0f };
	sf::Vector2i	m_velocity			{ 0, 0 };
	float			m_color[3]			{ 255.0f, 255.0f, 255.0f };
	
	char			m_displayText[255]	{ "" };
	sf::Text		m_text;

public:
	Entity()	{};
	~Entity()	{};

	virtual void	setSizeData(std::ifstream& fin)		= 0;
	virtual			sf::FloatRect getLocalBounds()		= 0;
	virtual			sf::FloatRect getGlobalBounds()		= 0;
	virtual			sf::Shape& getEntity()				= 0;
	
	void	setEntityType(const EntityType& entityType);
	void	setName(const std::string& name);
	void	setId(std::uint8_t id);
	void	setDrawEntity(bool drawEntity);
	void	setPosition(const sf::Vector2f& position);
	void	setVelocity(const sf::Vector2i& velocity);
	void	setColor(const float* color);

	void	setText(const sf::Text& text);
	void	setTextString(const std::string& str);
	void	setTextCharacterSize(unsigned int size);
	void	setTextPosition(const sf::Vector2f& position);
	void	setDisplayText(const char* displayText);


	EntityType		getEntityType()		const;
	std::string		getName()			const;
	std::uint8_t	getId()				const;
	bool			getDrawEntity()		const;
	sf::Vector2f	getPosition()		const;
	sf::Vector2i	getVelocity()		const;
	const float*	getColor()			const;

	sf::Text		getText()			const;
	char*			getDisplayText();
};

#endif // ENTITY_H