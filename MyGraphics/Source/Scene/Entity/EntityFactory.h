#pragma once

#include <map>
#include <vector>
using namespace::std;

struct Vector4;
struct Vector3;
struct Vector2;
class Entity;
class Assets;
class Texture;
class Model;
class Sprite;

class EntityFactory
{
public:
	static void GenerateEntities();
	static void DestroyEntities();

	static Entity* GeneratePlayer();

	static Entity* GenerateButton(const Vector2& position, const Vector2& size, Texture* texture, const Vector3& color);
	static Entity* GenerateSlider(const Vector2& position, const Vector2& size, const char* tag, Texture* texture, float min, float value, float max,bool integer);
	static Entity* GenerateInputField(const Vector2& position, const Vector3& color, int limit, float textSize);
	static Entity* GenerateTextGUI(const Vector2& position, const char* text, float size);

	static Entity* CreateSlider(const Vector2& position, const Vector2& size, const char* tag, float min, float value, float max, bool integer);
	static Entity* CreateCheckbox(const Vector2& position, float size, float stroke, const char* text, bool* toggle);

	static Entity* CreateSprite(const Vector2& position, const Vector2& size, Sprite* sprite, const Vector4& color, int layer = 0);
	static Entity* CreateGraphic(const Vector2& position, const Vector2& size, Texture* texture, const Vector4& color, int layer = 0);
	static Entity* CreateButton(const Vector2& position, const Vector2& size, Texture* texture, const Vector3& color);

	static Entity* CreateTextGUI(const Vector2& position, const char* text, float size, bool alignCenter = true);

	static Entity* GenerateGraphic(const Vector2& position, const Vector2& size, Texture* texture, const Vector4& color, int layer = 0);
	static Entity* GenerateTower(const Vector2& position, string type);
	static Entity* GenerateProjectile(const Vector2& position, string type);
	static Entity* GeneratePathFinder();
	static Entity* GenerateEnemy(const Vector2& position, int enemyTier, const char * animator, const char * animation);

	static Entity* CreateParticle(const Vector2& position, const Vector2& size, const char* animator, const char* animation, float alpha = 1);
	static Entity* GenerateParticle(const Vector2& position, const Vector2& size, const char* animator, const char* animation, float alpha = 1);

	static Entity* Generate(Entity* root, Entity* entity);
	static void Destroy(Entity* entity);

private:
	friend Entity;

	static Assets& assets;

	static map<Entity*, vector<Entity*>> toGenerate;
	static map<Entity*, vector<Entity*>> toDestroy;
};