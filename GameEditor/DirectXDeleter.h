#pragma once

template <class DirectXT>
struct DirectXDeleter
{
  void operator()(DirectXT* t)
  {
    if (t)
      t->Release();
  }
};