#ifndef BOB_ROSS_H
#define BOB_ROSS_H

#include "Mtx44.h"
#include "ShaderManager.h"
#include "FontManager.h"

class Texture;
class FBO;
class FontManager;
class GBuffer;
class PostProcessor;

#define Graphics GraphicsEngine::Instance()

class GraphicsEngine
{
public:
	static GraphicsEngine& Instance();

	void Start();

	void ForwardPass(bool pass);
	void Finish();

	void FinalPass(Texture* texture);

	void InitFBO();
	void Init(int width, int height);
	void Exit();

	Shader* GetShader(const char* key);

	FontManager* font;
	void UpdateV(Shader* shader, bool identity = false);
	void UpdateP(Shader* shader, bool ortho = false);

	void Render2D(const char* shader = "2D", int x = 1280, int y = 720, bool identity = true);

	GBuffer* gBuffer;
	PostProcessor* pp;

	enum fboType
	{
		BLUR,
		HALF,
		NUM_FBO,
	};

	FBO* GetFBO(fboType f);

	Texture* GaussianBlur(Texture* input, float radius, bool halfRes);
	Texture* Combine(Texture* input1, Texture* input2);

	void Resize(int width, int height);

	const Mtx44& GetView();
	const Mtx44& GetProjection();
	const Mtx44& GetProjection2D();

private:
	GraphicsEngine();
	~GraphicsEngine();

	FBO* frameBuffer[NUM_FBO];

	Mtx44 view;
	Mtx44 screen_projection, projection;
};

#endif
