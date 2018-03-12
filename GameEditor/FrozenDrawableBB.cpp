#include "FrozenDrawableBB.h"

const XMFLOAT3 FrozenDrawableBB::FROZEN_COLOR_FIRST = XMFLOAT3(0.043f, 0.05f, 0.5f);
const XMFLOAT3 FrozenDrawableBB::FROZEN_COLOR_SECOND = XMFLOAT3(0.013f, 0.5f, 0.1568f);

FrozenDrawableBB::FrozenDrawableBB(ID3D11Device* device, const BoundingBox& boundingBox)
  : TwoColoredDrawableBB(device, boundingBox, FROZEN_COLOR_FIRST, FROZEN_COLOR_SECOND)
{
}
