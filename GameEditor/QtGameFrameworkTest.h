#pragma once

#include <QWidget>
#include <QMessageBox>
#include "ui_QtGameFrameworkTest.h"
#include "Camera.h"
#include "D3DConfigurer.h"
#include "TextureShader.h"
#include "MeshFactory.h"
#include "TextureFactory.h"
#include "ShaderConfiguration.h"
#include "ShaderFactory.h"
#include "MaterialFactory.h"
#include "Static.h"

const bool FULL_SCREEN = false;
const bool VSYNC_ENABLED = true;
const float SCREEN_DEPTH = 1000.0f;
const float SCREEN_NEAR = 0.1f;

class QtGameFrameworkTest : public QWidget, public Ui::QtGameFrameworkTest
{
    Q_OBJECT

public:
    QtGameFrameworkTest(QWidget *parent = Q_NULLPTR);
    ~QtGameFrameworkTest();

    /** a hint to Qt to give the widget as much space as possible */
    QSizePolicy sizePolicy() const { return QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); }

    /** a hint to Qt that we take care of the drawing for ourselves, thankyouverymuch */
    QPaintEngine *paintEngine() const { return NULL; }
protected:
  /** Initialized the D3D environment */
  bool Initialize(int screenWidth, int screenHeight, HWND hwnd);

  /** Destroys the D3D environment */
  void Shutdown();

  /** paints the scene */
  void paintEvent(QPaintEvent* pEvent);
private:
  D3DConfigurer* m_Direct3D;
  Camera* m_Camera;
  Static m_static;
  ShaderConfiguration* m_shaderConfiguration;
};
