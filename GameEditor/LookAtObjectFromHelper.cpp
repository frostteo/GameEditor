#include "LookAtObjectFromHelper.h"


LookAtObjectFromHelper::LookAtObjectFromHelper()
{
}


LookAtObjectFromHelper::~LookAtObjectFromHelper()
{
}

void LookAtObjectFromHelper::LookToObjectFromHelper(StaticGameObject* gameObject, float& newWidth, float& newHeight, float& newDepth, XMVECTOR& newObjectCenter)
{
  XMMATRIX objectWorldMatrix;
  const int TEST_POINTS_COUNT = 4;
  XMVECTOR testPoints[TEST_POINTS_COUNT];
  float minX, maxX, minY, maxY, minZ, maxZ;
  XMFLOAT3 boundingBoxMinPoint, boundingBoxMaxPoint;
  XMVECTOR minPoint, maxPoint, secondDiagonalFirstPoint, secondDiagonalSecondPoint;

  gameObject->GetWorldMatrix(objectWorldMatrix);
  boundingBoxMinPoint = gameObject->GetModel()->GetBoundingBox()->GetMinPoint();
  boundingBoxMaxPoint = gameObject->GetModel()->GetBoundingBox()->GetMaxPoint();
  minPoint = XMLoadFloat3(&boundingBoxMinPoint);
  maxPoint = XMLoadFloat3(&boundingBoxMaxPoint);
  secondDiagonalFirstPoint = XMVectorSet(boundingBoxMinPoint.x, boundingBoxMaxPoint.y, boundingBoxMinPoint.z, 0.0f);
  secondDiagonalSecondPoint = XMVectorSet(boundingBoxMaxPoint.x, boundingBoxMinPoint.y, boundingBoxMaxPoint.z, 0.0f);

  testPoints[0] = XMVector3Transform(minPoint, objectWorldMatrix);
  testPoints[1] = XMVector3Transform(maxPoint, objectWorldMatrix);
  testPoints[2] = XMVector3Transform(secondDiagonalFirstPoint, objectWorldMatrix);
  testPoints[3] = XMVector3Transform(secondDiagonalSecondPoint, objectWorldMatrix);
  newObjectCenter = XMVector3Transform(XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f), objectWorldMatrix);

  minX = XMVectorGetX(testPoints[0]);
  maxX = minX;
  minY = XMVectorGetY(testPoints[0]);
  maxY = minY;
  minZ = XMVectorGetZ(testPoints[0]);
  maxZ = minZ;

  for (int i = 1; i < TEST_POINTS_COUNT; ++i)
  {
    float pointX = XMVectorGetX(testPoints[i]);
    float pointY = XMVectorGetY(testPoints[i]);
    float pointZ = XMVectorGetZ(testPoints[i]);

    if (pointX < minX)
      minX = pointX;
    else if (pointX > maxX)
      maxX = pointX;

    if (pointY < minY)
      minY = pointY;
    else if (pointY > maxY)
      maxY = pointY;

    if (pointZ < minZ)
      minZ = pointZ;
    else if (pointZ > maxZ)
      maxZ = pointZ;
  }

  newWidth = maxX - minX;
  newHeight = maxY - minY;
  newDepth = maxZ - minZ;
}

void LookAtObjectFromHelper::LookToObjectFromWorldFront(Camera* camera, StaticGameObject* gameObject)
{
  float newWidth, newHeight, newDepth, greatestDimension, FOV, cameraDistanceFromObjectCenter;
  XMVECTOR newObjectCenter, newCameraPosition, helper;
  XMMATRIX newCameraMatrix;

  LookToObjectFromHelper(gameObject, newWidth, newHeight, newDepth, newObjectCenter);

  greatestDimension = newWidth > newHeight ? newWidth : newHeight;
  FOV = camera->GetFieldOfView();
  cameraDistanceFromObjectCenter = (greatestDimension * 0.75) / tan(FOV * 0.5) + abs(newDepth * 0.5);
  newCameraPosition = newObjectCenter;

  newCameraPosition = XMVectorSetZ(newCameraPosition, XMVectorGetZ(newCameraPosition) - cameraDistanceFromObjectCenter);

  newCameraMatrix = XMMatrixLookAtLH(newCameraPosition, newObjectCenter, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
  camera->SetWorldMatrix(XMMatrixInverse(&helper, newCameraMatrix));
}

void LookAtObjectFromHelper::LookToObjectFromWorldUp(Camera* camera, StaticGameObject* gameObject)
{
  float newWidth, newHeight, newDepth, greatestDimension, FOV, cameraDistanceFromObjectCenter;
  XMVECTOR newObjectCenter, newCameraPosition, helper;
  XMMATRIX newCameraMatrix;

  LookToObjectFromHelper(gameObject, newWidth, newHeight, newDepth, newObjectCenter);

  greatestDimension = newWidth > newDepth ? newWidth : newDepth;
  FOV = camera->GetFieldOfView();
  cameraDistanceFromObjectCenter = (greatestDimension * 0.75) / tan(FOV * 0.5) + abs(newHeight * 0.5);
  newCameraPosition = newObjectCenter;

  newCameraPosition = XMVectorSetY(newCameraPosition, XMVectorGetY(newCameraPosition) + cameraDistanceFromObjectCenter);
  newCameraPosition = XMVectorSetZ(newCameraPosition, XMVectorGetZ(newCameraPosition) - 2);

  newCameraMatrix = XMMatrixLookAtLH(newCameraPosition, newObjectCenter, XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f));
  camera->SetWorldMatrix(XMMatrixInverse(&helper, newCameraMatrix));
}