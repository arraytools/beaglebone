#include <QWidget>
#include <QSlider>
#include <QLabel>
class Slider : public QWidget
{
  Q_OBJECT
  public:
    Slider(QWidget *parent =0);
    ~Slider();
  private:
    QSlider *slider;
    QLabel *label;
  public slots:
    void value(int);
};

