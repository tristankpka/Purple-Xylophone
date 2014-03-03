#include "Actor.h"
#include "ResourceHolder.h"
#include "Utility.h"
#include "TextNode.h"

#include <string>

const float SCALE = 30.f; // Box2D works in a scale of 30 pixels = 1 meter

Textures::ID toTextureID(Actor::Type type)
{
    switch (type)
    {

    }

}

Actor::Actor(Type type, const TextureHolder& textures, const FontHolder& fonts, b2World& world):
    Entity(createBody(world)),
    m_type(type),
    m_lookingOrientation(LookingOrientation::Down)
{
    // Player
    // TODO rendre adaptable taille anim (frame)
    sf::Rect<float> spriteBounds(0,0,32,32);// = m_sprite.getGlobalBounds();
    Transformable::setOrigin(sf::Vector2f(spriteBounds.width/2,spriteBounds.height/2));

    b2FixtureDef ActorFixtureDef;
    b2PolygonShape ActorShape;
    ActorShape.SetAsBox((spriteBounds.width/2.0f)/SCALE, (spriteBounds.height/2.0f)/SCALE);
    ActorFixtureDef.shape = &ActorShape;
    ActorFixtureDef.density = 1.0f;
    ActorFixtureDef.friction = 0.3f;
    ActorFixtureDef.userData = this;
    m_body->CreateFixture(&ActorFixtureDef);
}


void Actor::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{

}

void Actor::updateCurrent(sf::Time dt, CommandQueue& commands)
{
    // TODO
    Entity::updateCurrent(dt, commands);
}

bool Actor::isDestroyed() const
{
    return false;
}

unsigned int Actor::getCategory() const
{
    switch(m_type)
    {
        case Hero:
            return Category::PlayerActor;
    }
}

b2Body* Actor::createBody(b2World& world)
{
    b2BodyDef ActorBodyDef;
    ActorBodyDef.type = b2_dynamicBody;
    ActorBodyDef.fixedRotation = true;
    ActorBodyDef.linearDamping = 0.2f;
    b2Body* body = world.CreateBody(&ActorBodyDef);

    return body;
}

