#include "AchievementScript.h"

AchievementScript::AchievementScript()
{
}

AchievementScript::~AchievementScript()
{
}

#include "../../../../Scene.h"
#include "../../../Entity.h"
#include "../../../EntityFactory.h"
#include "../../Transform.h"

#include "../../GUI/Button.h"
#include "../../GUI/Slider.h"

#include "Vector2.h"

#include "LUAEngine.h"
#include "../../../../../SoundEngine.h"
#include "Utility.h"
#include "../../TextRenderer2D.h"

void AchievementScript::Init(Entity * ent)
{
	StateObject::Init(ent);	

	achievement = Achievement();
	LoadAchievements("Data//Save//achievementStats.txt");

	Entity* entity = ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 100), "BACK", 400, Vector3(0.7f, 0.7f, 0)));
	back = entity->GetComponent<Button>();

	entity = ent->AttachChild(EntityFactory::CreateTextButton(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.8f, 100), "RESET", 400, Vector3(0.7f, 0.7f, 0)));
	reset = entity->GetComponent<Button>();

	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5f, 650), "Lifetime Stats", 400, true));
	entity->GetComponent<TextRenderer2D>()->color.Set(0.75f, 0.75f, 0);

	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.2f, 550), "Games Played", 200, false));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.8f, 550), ToString(achievement.gamesPlayed).c_str(), 200, false));
	texts.push_back(entity->GetComponent<TextRenderer2D>());

	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.2f, 500), "Games Won", 200, false));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.8f, 500), ToString(achievement.gamesWon).c_str(), 200, false));
	texts.push_back(entity->GetComponent<TextRenderer2D>());

	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.2f, 450), "Towers Placed", 200, false));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.8f, 450), ToString(achievement.towersPlaced).c_str(), 200, false));
	texts.push_back(entity->GetComponent<TextRenderer2D>());

	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.2f, 400), "Towers Upgraded", 200, false));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.8f, 400), ToString(achievement.towersUpgraded).c_str(), 200, false));
	texts.push_back(entity->GetComponent<TextRenderer2D>());

	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.2f, 350), "Towers Max Upgraded", 200, false));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.8f, 350), ToString(achievement.towersMaxUpgraded).c_str(), 200, false));
	texts.push_back(entity->GetComponent<TextRenderer2D>());

	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.2f, 300), "Jellies Popped", 200, false));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.8f, 300), ToString(achievement.enemiesPopped).c_str(), 200, false));
	texts.push_back(entity->GetComponent<TextRenderer2D>());

	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.2f, 250), "Enemies Leaked", 200, false));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.8f, 250), ToString(achievement.enemiesLeaked).c_str(), 200, false));
	texts.push_back(entity->GetComponent<TextRenderer2D>());

	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.2f, 200), "Waves Completed", 200, false));
	entity = ent->AttachChild(EntityFactory::CreateTextGUI(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.8f, 200), ToString(achievement.wavesCompleted).c_str(), 200, false));
	texts.push_back(entity->GetComponent<TextRenderer2D>());

	/*Entity* SmoothSlide = ent->AttachChild(EntityFactory::CreateSlider(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5, Scene::scene->GetResolutionY(Scene::scene->canvas)*0.45f), Vector2(400, 12), "SFX", 0, LUA.GetGlobalNumber("SFX_VOLUME"), 100, true));
	sfx = SmoothSlide->GetChild("Slider")->GetComponent<Slider>();

	SmoothSlide->AttachChild(EntityFactory::CreateCheckbox(Vector2(-180, -24), 16, 2, "Mute"));

	SmoothSlide = ent->AttachChild(EntityFactory::CreateSlider(Vector2(Scene::scene->GetResolutionX(Scene::scene->canvas) * 0.5, Scene::scene->GetResolutionY(Scene::scene->canvas)*0.6f), Vector2(400, 12), "BGM", 0, LUA.GetGlobalNumber("BGM_VOLUME"), 100, true));
	bgm = SmoothSlide->GetChild("Slider")->GetComponent<Slider>();

	SmoothSlide->AttachChild(EntityFactory::CreateCheckbox(Vector2(-180, -24), 16, 2, "Mute"));*/

	target.Set(Scene::scene->GetResolutionX(Scene::scene->canvas), 0);
	transform->Position() = target.GetVector3();

	rate = 16;
}

#include "MenuHandler.h"
#include "MenuScript.h"


void AchievementScript::Update(double dt)
{
	StateObject::Update(dt);

	if (back->IsState())
		menu->Pop();
	else if (reset->IsState())
		ResetAchievements();
}

#include "FileSystem.h"

void AchievementScript::ResetAchievements()
{
	ofstream& output = *File.BeginWriting("Data//Save//achievementStats.txt");

	output << 0 << ", ";
	output << 0 << ", ";
	output << 0 << ", ";
	output << 0 << ", ";
	output << 0 << ", ";
	output << 0 << ", ";
	output << 0 << ", ";
	output << 0 << ", ";

	File.EndWriting();

	LoadAchievements("Data//Save//achievementStats.txt");
	UpdateAchievements();
}

void AchievementScript::UpdateAchievements()
{
	texts[0]->SetText(ToString(achievement.gamesWon).c_str());
	texts[1]->SetText(ToString(achievement.gamesPlayed).c_str());
	texts[2]->SetText(ToString(achievement.towersPlaced).c_str());
	texts[3]->SetText(ToString(achievement.towersUpgraded).c_str());
	texts[4]->SetText(ToString(achievement.towersMaxUpgraded).c_str());
	texts[5]->SetText(ToString(achievement.enemiesPopped).c_str());
	texts[6]->SetText(ToString(achievement.enemiesLeaked).c_str());
	texts[7]->SetText(ToString(achievement.wavesCompleted).c_str());
}

void AchievementScript::LoadAchievements(const char *filepath)
{
	if (File.Exists(filepath))
	{
		vector<string>& lines = File.GetLines(filepath);

		for (auto& line : lines)
		{
			vector<string>& tokens = ParseLine(line, " ,");
			achievement.gamesPlayed = stoi(tokens[0]);
			achievement.gamesWon = stoi(tokens[1]);
			achievement.towersPlaced = stoi(tokens[2]);
			achievement.towersUpgraded = stoi(tokens[3]);
			achievement.towersMaxUpgraded = stoi(tokens[4]);
			achievement.enemiesPopped = stoi(tokens[5]);
			achievement.enemiesLeaked = stoi(tokens[6]);
			achievement.wavesCompleted = stoi(tokens[7]);
		}
	}
}
