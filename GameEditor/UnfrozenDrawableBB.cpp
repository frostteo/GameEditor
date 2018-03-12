#include "UnfrozenDrawableBB.h"

const XMFLOAT3 UnfrozenDrawableBB::UNFROZEN_COLOR_FIRST = XMFLOAT3(1.0f, 0.0f, 0.0f);
const XMFLOAT3 UnfrozenDrawableBB::UNFROZEN_COLOR_SECOND = XMFLOAT3(0.0f, 1.0f, 0.0f);

UnfrozenDrawableBB::UnfrozenDrawableBB(ID3D11Device* device, const BoundingBox& boundingBox)
  : TwoColoredDrawableBB(device, boundingBox, UNFROZEN_COLOR_FIRST, UNFROZEN_COLOR_SECOND)
{
}

