#include <iostream>

#include <SFML/Graphics.hpp>

#include <Box2D/Box2D.h>
#include <imgui/imgui.h>

#include "World.h"
#include "Body.h"

// static body
class StaticBody: public Body {
    private:

    public:
        // constructor
        StaticBody(const b2Vec2& position, const std::initializer_list<b2Vec2>& vertices,
                   const float density):
            Body(position, vertices, density, b2_staticBody) {}

        // to be called every frame
        void update(const sf::Time& time) override {
            ;
        }
};

// dynamic body 
class DynamicBody: public Body {
    private:

    public: 
        // constructor
        DynamicBody(const b2Vec2& position, const std::initializer_list<b2Vec2>& vertices,
                    const float density):
            Body(position, vertices, density, b2_dynamicBody) {}

        // to be called every frame
        void update(const sf::Time& time) override {
            // assertions
            assert(mPhysicsBody && "updating body with no physics body...");

            // update body position
            auto [x, y] = mPhysicsBody->GetPosition();
            setPosition(x, y);

            // update body rotation
            setRotation(mPhysicsBody->GetAngle() / b2_pi * 180.f);
        }
        
};

// MAIN
int main() {
    // global window
    sf::RenderWindow window(sf::VideoMode(750, 750), "Lander");
    window.setFramerateLimit(60);

    // initialize test bodies
    Body::gWorld.spawn<StaticBody>(b2Vec2(2, 2), std::initializer_list<b2Vec2>{
        b2Vec2(0, 10),
        b2Vec2(10, 10),
        b2Vec2(10, 12),
        b2Vec2(0, 12)
    }, 1.f);
    Body::gWorld.spawn<DynamicBody>(b2Vec2(2, 2), std::initializer_list<b2Vec2>{
        b2Vec2(0, 0),
        b2Vec2(2, 2),
        b2Vec2(2, 4),
        b2Vec2(1, 5),
        b2Vec2(0, 4)
    }, 1.f);

    // main loop
    sf::Event e;
    while(window.isOpen()) {
        // handle events
        while(window.pollEvent(e)) {
            // default window close event
            if(e.type == sf::Event::Closed)
                window.close();

            // close if key is pressed
            else if(e.type == sf::Event::KeyPressed)
                window.close();
        }

        // update physics
        Body::gWorld.update(sf::seconds(1.f/60.f));

        // draw things
        window.clear();
        window.draw(Body::gWorld);
        window.display();
    }

    // end
    return 0;
}
