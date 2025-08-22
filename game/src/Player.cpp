#include <Game/Player.h>

Player::Player(glm::vec3 position, glm::vec3 scale, glm::vec4 color, std::string texturePath, std::string name, bool isStatic)
{
    mesh = AssetManager::GetMesh("quadMesh");
    shaderName = "textureShader";
    transform.position = position;
    transform.scale = scale;
    rigidBody.isStatic = isStatic;
    hp = 2;
    texture.Create("/Users/cameronprzybylski/Documents/C++/C++ Projects/MyAdventureGame/textures/8bitLink.png");
    this->color = color;
    this->name = name;
}

Player::~Player()
{

}

void Player::OnEvent(const Input& input)
{
    if(input.IsKeyDown("D") && !hit)
    {
        rigidBody.velocity.x = 300.0f;
    }
    else if(input.IsKeyDown("A") && !hit)
    {
        rigidBody.velocity.x = -300.0f;
    }
    if(input.IsKeyDown("W") && !hit)
    {
        rigidBody.velocity.y = 300.0f;
    }
    else if(input.IsKeyDown("S") && !hit)
    {
        rigidBody.velocity.y = -300.0f;
    }
}

void Player::Update(const Input& input, float dt)
{
    if(!(input.IsKeyDown("D") || input.IsKeyDown("A") || input.IsKeyDown("W") || input.IsKeyDown("S")))
    {
        rigidBody.velocity.x = 0;
        rigidBody.velocity.y = 0;
    }
    else
    {
        if(input.IsKeyDown("D") && !hit)
        {
            rigidBody.velocity.x = 300.0f;
        }
        else if(input.IsKeyDown("A") && !hit)
        {
            rigidBody.velocity.x = -300.0f;
        }
        else{
            rigidBody.velocity.x = 0.0f;
        }
        if(input.IsKeyDown("W") && !hit)
        {
            rigidBody.velocity.y = 300.0f;
        }
        else if(input.IsKeyDown("S") && !hit)
        {
            rigidBody.velocity.y = -300.0f;
        }
        else
        {
            rigidBody.velocity.y = 0.0f;
        }
    }
    if(transform.position.y >= 800)
    {
        //transform.position.y = 800.0f;
    }if(transform.position.y < 0.0f || hp <= 0){
        //alive = false;
    }
}

void Player::OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt)
{
    if(collisionNormal.x == 0 && collisionNormal.y == 1)
    {
        if(collidedObj->name.find("obstacle") != std::string::npos)
        {
        }
    }
    else if (collidedObj->name.find("enemy") != std::string::npos && !hit)
    {
        Hit(dt);
    }
}

void Player::Render(Renderer& renderer, const Camera& camera)
{
    renderer.DrawTexturedQuad(*mesh, transform, camera, AssetManager::GetShader(shaderName), texture, color);
    texture.Unbind();
}

void Player::Jump()
{
    rigidBody.velocity = {rigidBody.velocity.x, 1000.0f, 0.0f};
}

void Player::Hit(float dt)
{
    rigidBody.velocity.x *= -1;
    hit = true;
    hp--;
    Jump();
}
