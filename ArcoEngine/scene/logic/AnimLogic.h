#pragma once
#include <vector>
#include <string>
#include <utility>

struct sAnimSeq 
{
	float startPr;
	float endPr;
	float animTime;
};


class AnimLogic
{
public:
	AnimLogic(void);
	~AnimLogic(void)		{ }

	void addFrame(sAnimSeq &aseq);

	void startAnim(float cutNowTime);
	std::pair<int, float> propAnimStep(float runTime);

private:
	std::vector<sAnimSeq> mAnimSequences;
	float mStarAnimTime = 0.f;

	float mStartFrameTime = 0.f;
	int mFrameIdx = 0;
};
