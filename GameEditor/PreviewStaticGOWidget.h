#pragma once

#include <QDialog>
#include "ui_PreviewStaticGOWidget.h"

#include <QMessageBox>
#include <memory>
#include "Camera.h"
#include "D3DConfigurer.h"
#include "TextureShader.h"
#include "MeshFactory.h"
#include "TextureFactory.h"
#include "ShaderConfiguration.h"
#include "ShaderFactory.h"
#include "MaterialFactory.h"
#include "Static.h"
#include "LightininigSystem.h"
#include "GraphicSystem.h"
#include "InputSystem.h"
#include "PreviewGameObject.h"
#include "HighPerformanceTimer.h"
#include "StaticGameObject.h"
#include "QtUtils.h"

class PreviewStaticGOWidget : public QDialog, public Ui::PreviewStaticGOWidget
{
    Q_OBJECT
private:
  const char m_filePathSeparator = '/';
  std::string m_pathToMaterials;
  std::string m_pathToModels;

  const bool FULL_SCREEN = false;
  const bool VSYNC_ENABLED = true;
  const float SCREEN_DEPTH = 1000.0f;
  const float SCREEN_NEAR = 0.1f;

  int m_minWidth = 800;
  int m_minHeight = 600;

  std::unique_ptr<InputSystem> m_inputSystem;
  std::unique_ptr<Camera> m_Camera;
  
  std::unique_ptr<ShaderConfiguration> m_shaderConfiguration;
  std::unique_ptr<LightininigSystem> m_lightininigSystem;
  std::unique_ptr<GraphicSystem> m_graphicSystem;

  Static m_static;
protected:
  /** Initialized the D3D environment */
  bool Initialize(int screenWidth, int screenHeight, HWND hwnd);

  /** Destroys the D3D environment */
  void Shutdown();

  /** paints the scene */
  void paintEvent(QPaintEvent* pEvent);
public:
  PreviewStaticGOWidget(QString pathToModels, QString pathToMaterials, QWidget *parent = Q_NULLPTR);
  ~PreviewStaticGOWidget();

  /** a hint to Qt to give the widget as much space as possible */
  QSizePolicy sizePolicy() const { return QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); }

  /** a hint to Qt that we take care of the drawing for ourselves, thankyouverymuch */
  QPaintEngine *paintEngine() const { return NULL; }

  void SetPathToModels(QString pathToModels) { m_pathToModels = QtUtils::QStringToStdStr(pathToModels); }
  void SetPathToMaterials(QString pathToMaterials) { m_pathToMaterials = QtUtils::QStringToStdStr(pathToMaterials); }

  void SetStaticGameObject(StaticGameObject staticGameObject);
};
