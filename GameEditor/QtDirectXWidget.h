#pragma once

#include <QWidget>
#include <QDialog>
#include "ui_QtDirectXWidget.h"
#include <QMessageBox>
#include <string>
#include <memory>
#include "InputSystem.h"
#include "Camera.h"
#include "ShaderConfiguration.h"
#include "LightininigSystem.h"
#include "GraphicSystem.h"

class QtDirectXWidget : public QWidget, public Ui::QtDirectXWidget
{
    Q_OBJECT
protected:
  const bool FULL_SCREEN = false;
  const bool VSYNC_ENABLED = false;
  const float SCREEN_DEPTH = 65536.0f;
  const float SCREEN_NEAR = 0.1f;

  std::string m_pathToMaterials;
  std::string m_pathToModels;

  int m_minWidth = 800;
  int m_minHeight = 600;

  std::unique_ptr<InputSystem> m_inputSystem;
  std::unique_ptr<Camera> m_Camera;

  std::unique_ptr<ShaderConfiguration> m_shaderConfiguration;
  std::unique_ptr<LightininigSystem> m_lightininigSystem;
  std::unique_ptr<GraphicSystem> m_graphicSystem;

protected:
  /** Destroys the D3D environment */
  void Shutdown();

  /** paints the scene */
  virtual void paintEvent(QPaintEvent* pEvent);
  Model* GetModel(const std::string& modelName);
public:
  QtDirectXWidget(QString pathToModels, QString pathToMaterials, QWidget *parent = Q_NULLPTR);
  ~QtDirectXWidget();

  /** Initialized the D3D environment */
  bool Initialize(int screenWidth, int screenHeight, HWND hwnd);

  void SetPathToModels(QString pathToModels) { m_pathToModels = pathToModels.toStdString(); }
  void SetPathToMaterials(QString pathToMaterials) { m_pathToMaterials = pathToMaterials.toStdString(); }

  ModelFactory* GetModelFactory() { m_graphicSystem->GetModelFactory(); }

  /** a hint to Qt to give the widget as much space as possible */
  QSizePolicy sizePolicy() const { return QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); }

  /** a hint to Qt that we take care of the drawing for ourselves, thankyouverymuch */
  QPaintEngine *paintEngine() const { return NULL; }

  virtual void resizeEvent(QResizeEvent* evt);
};
