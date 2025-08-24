#include <Game/Player.h>

Player::Player(glm::vec3 position, glm::vec3 scale, glm::vec4 color, std::string texturePath, std::string name, bool isStatic)
{
    mesh = AssetManager::GetMesh("quadMesh");
    shaderName = "textureShader";
    transform.position = position;
    transform.scale = scale;
    rigidBody.isStatic = isStatic;
    hp = 3;
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
    if(input.IsKeyDown("L"))
    {
        usingSword = true;
        items["sword"]->transform.position.x = transform.position.x + items["sword"]->transform.scale.x;
        items["sword"]->transform.position.y = transform.position.y;
    }
    else
    {
        usingSword = false;
        items["sword"]->transform.position.x = transform.position.x;
        items["sword"]->transform.position.y = transform.position.y;
    }
}

void Player::Update(const Input& input, float dt)
{
    if(hit)
    {
        if(timeSinceHit >= 0.5f){
            hit = false;
        }
        else{
            timeSinceHit += dt;
        }
    }
    else if(!(input.IsKeyDown("D") || input.IsKeyDown("A") || input.IsKeyDown("W") || input.IsKeyDown("S")))
    {
        rigidBody.velocity.x = 0;
        rigidBody.velocity.y = 0;
    }
    else
    {
        if(input.IsKeyDown("D") && !hit)
        {
            rigidBody.velocity.x = 300.0f;
            positionFacing = "Right";
        }
        else if(input.IsKeyDown("A") && !hit)
        {
            rigidBody.velocity.x = -300.0f;
            positionFacing = "Left";
        }
        else{
            rigidBody.velocity.x = 0.0f;
        }
        if(input.IsKeyDown("W") && !hit)
        {
            rigidBody.velocity.y = 300.0f;
            positionFacing = "Up";
        }
        else if(input.IsKeyDown("S") && !hit)
        {
            rigidBody.velocity.y = -300.0f;
            positionFacing = "Down";
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
        alive = false;
    }
    if(usingSword)
    {
        if(input.IsKeyDown("L"))
        {
            usingSword = true;
            if(positionFacing == "Right")
            {
                items["sword"]->transform.position.x = transform.position.x + items["sword"]->transform.scale.x;
                items["sword"]->transform.position.y = transform.position.y;
                items["sword"]->transform.rotation.z = 0.0f;
            }
            else if(positionFacing == "Left")
            {
                items["sword"]->transform.position.x = transform.position.x - items["sword"]->transform.scale.x;
                items["sword"]->transform.position.y = transform.position.y;
                items["sword"]->transform.rotation.z = 0.0f;
            }
            else if(positionFacing == "Up")
            {
                items["sword"]->transform.position.x = transform.position.x;
                items["sword"]->transform.position.y = transform.position.y + items["sword"]->transform.scale.x;
                items["sword"]->transform.rotation.z = 90.0f;

            }
            else if(positionFacing == "Down")
            {
                items["sword"]->transform.position.x = transform.position.x;
                items["sword"]->transform.position.y = transform.position.y - items["sword"]->transform.scale.x;
                items["sword"]->transform.rotation.z = 90.0f;
            }
        }
        else
        {
            usingSword = false;
            items["sword"]->transform.position.x = transform.position.x;
            items["sword"]->transform.position.y = transform.position.y;
        }
    }
}

void Player::OnCollision(std::shared_ptr<GameObject> collidedObj, glm::vec2 collisionNormal, float dt)
{
    if (collidedObj->name.find("enemy") != std::string::npos && !hit)
    {
        Hit(collisionNormal, dt);
    }
}

void Player::Render(Renderer& renderer, const Camera& camera)
{
    renderer.DrawTexturedQuad(*mesh, transform, camera, AssetManager::GetShader(shaderName), texture, color);
    texture.Unbind();
}

void Player::Hit(glm::vec2 collisionNormal, float dt)
{
    //Collided from Left
    if(collisionNormal.x == 1 || collisionNormal.x == -1)
    {
        rigidBody.velocity.x *= -1;
    }
    else
    {
        rigidBody.velocity.y *= -1;
    }
    hit = true;
    timeSinceHit = 0.0f;
    hp--;
}

void Player::AddItem(std::string name, std::shared_ptr<GameObject> item)
{
    items[name] = item;
}
