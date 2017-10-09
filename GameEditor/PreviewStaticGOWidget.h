#pragma once

#include <QDialog>
#include "ui_PreviewStaticGOWidget.h"
#include <QMessageBox>
#include <memory>
#include "Camera.h"
#include "D3DConfigurer.h"
#include "TextureShader.h"
#include "TextureFactory.h"
#include "ShaderConfiguration.h"
#include "ShaderFactory.h"
#include "MaterialFactory.h"
#include "Model.h"
#include "LightininigSystem.h"
#include "GraphicSystem.h"
#include "InputSystem.h"
#include "PreviewGameObject.h"
#include "HighPerformanceTimer.h"
#include "StaticGameObjectDbInfo.h"
#include "QtUtils.h"
#include "QtDirectXWidget.h"

class PreviewStaticGOWidget : public QtDirectXWidget, public Ui::PreviewStaticGOWidget
{
    Q_OBJECT
private:
  Model* m_model;
protected:
  /** Destroys the D3D environment */
  void Shutdown();

  /** paints the scene */
  virtual void paintEvent(QPaintEvent* pEvent);
public:
  PreviewStaticGOWidget(QString pathToModels, QString pathToMaterials, QWidget *parent = Q_NULLPTR);
  ~PreviewStaticGOWidget();
  /** Initialized the D3D environment */
  bool Initialize(int screenWidth, int screenHeight, HWND hwnd, std::string pathToMaterials);
  void SetStaticGameObject(StaticGameObjectDbInfo staticGameObject);
};
