#include "Body.h"

#include "World.h"

// initialize body global world
World Body::gWorld(b2Vec2(0.f, 9.8f));

// simple constructor
Body::Body(const b2Vec2& position, const std::initializer_list<b2Vec2>& vertices,
           const float density, const b2BodyType bodyType):
    mSprite(vertices.size())
{
    // init body definition
    b2BodyDef bodyDef;
    bodyDef.position = position;
    bodyDef.type     = bodyType;

    // create body
    mPhysicsBody = gWorld.getPhysicsWorld().CreateBody(&bodyDef);

    // init body shape
    b2PolygonShape shape;
    shape.Set(vertices.begin(), vertices.size());
    
    // init body fixture
    b2FixtureDef fixtureDef;
    fixtureDef.density = density;
    fixtureDef.shape   = &shape;

    // attach fixture to body
    mPhysicsBody->CreateFixture(&fixtureDef);

    // init sprite
    {
        size_t idx = 0;
        for(const auto& vertex : vertices) {
            mSprite.setPoint(idx, {vertex.x, vertex.y});
            ++idx;
        }
    }
    
    // init graphics transform
    setPosition(position.x, position.y); 
}

// draw function
void Body::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    // assertions
    assert(mPhysicsBody && "drawing body with no physics body...");

    // set up transform
    states.transform.translate(getPosition() * 30.f);
    states.transform.scale(getScale() * 30.f);
    states.transform.rotate(getRotation());

    // DB: fill sprite with red
    const_cast<sf::ConvexShape*>(&mSprite)->setFillColor(sf::Color::Red);

    // draw sprite
    target.draw(mSprite, states);
}
