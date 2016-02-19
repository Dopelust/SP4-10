#ifndef G_BUFFER_H
#define G_BUFFER_H

class FBO;
class Texture;

class GBuffer
{
public:
	static GBuffer& Instance();

	enum attachmentType
	{
		POSITION_MAP,
		NORMAL_MAP,
		DIFFUSE_MAP,
		SPECULAR_MAP,
		FORWARD_TEXTURE,
		DEPTH_TEXTURE,
		NUM_ATTACHMENTS,
	};

	void Init(int width, int height);
	void Resize(int width, int height);

	void BindForWriting(bool clearColor = false);
	void Bind(attachmentType attachment, int textureUnit = 0);

	Texture* GetOutput();

	void StartGPass();
	void StartDirLightPass();
	void StartForwardPass();

private:
	GBuffer();
	~GBuffer();

	FBO* fbo;
};

#endif
