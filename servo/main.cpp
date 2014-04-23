#include <QApplication>
#include "servo.h"
int main(int argc, char*argv[])
{
  QApplication app(argc, argv);
  Slider window;
  window.move(0,0);
  window.setWindowTitle("My Servo");
  window.show();
  return app.exec();
}
