#pragma once

class Uncopyable
{
private:
  Uncopyable(const Uncopyable&) = delete;
  void operator=(const Uncopyable&) = delete;
protected:
  Uncopyable() = default;
  ~Uncopyable() = default;
};