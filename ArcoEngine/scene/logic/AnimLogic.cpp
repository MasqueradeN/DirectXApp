#include <d3d11.h>
#include <cmath>
#include "AnimLogic.h"
//#include "../../tools/pugixml.hpp"

AnimLogic::AnimLogic()
{

}

void AnimLogic::addFrame(sAnimSeq &aseq)
{
	mAnimSequences.push_back(aseq);
}

void AnimLogic::startAnim(float cutNowTime)
{
	mStarAnimTime = cutNowTime;
	mStartFrameTime = 0.f;
	mFrameIdx = 0;
}

std::pair<int, float> AnimLogic::propAnimStep(float runTime)
{
	if (mFrameIdx >= mAnimSequences.size()) { 
		return std::make_pair(0, 0.f);
	}

	float deltaTime = runTime - mStartFrameTime;
	if (deltaTime >= mAnimSequences[mFrameIdx].animTime) {
		size_t seqSz = mAnimSequences.size();
		if (++mFrameIdx >= seqSz) {
			return std::make_pair(2, mAnimSequences[seqSz - 1].endPr);
		}
		mStartFrameTime = runTime;
		deltaTime = 0.f;
	}
	sAnimSeq &sq = mAnimSequences[mFrameIdx];
	float retProp = sq.startPr + ((deltaTime / sq.animTime) * (sq.endPr - sq.startPr));

	return std::make_pair(1, retProp);
}


