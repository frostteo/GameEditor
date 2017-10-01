#pragma once

struct VertexObj
{
  float x, y, z;
  bool operator== (const VertexObj& another) const { return this->x == another.x && this->y == another.y && this->z == another.z; }
};


struct VertexTxt
{
  VertexObj coord;
  VertexObj normal;
  VertexObj tangent;
  VertexObj binormal;
  float tv, tu;
  bool operator== (const VertexTxt& other) const {
    return this->coord == other.coord && this->tangent == other.tangent && this->binormal == other.binormal && this->tv == other.tv &&
      this->tu == other.tu;
  }
};