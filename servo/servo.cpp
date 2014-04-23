#include "servo.h"
#include <stdio.h>
#include <iostream>
Slider::Slider(QWidget *parent)
  : QWidget(parent)
{
  slider = new QSlider(Qt::Horizontal, this);
  slider->setGeometry(50,50,130,30);
  slider->setRange(510000, 2400000);
  label = new QLabel("0", this);
  label->setGeometry(230,50,60,30);

  system("if [ `grep -q am33xx_pwm /sys/devices/bone_capemgr.9/slots` ]; then :; else echo am33xx_pwm > /sys/devices/bone_capemgr.9/slots; fi");
  system("if [ `grep -q bone_pwm_P8_13 /sys/devices/bone_capemgr.9/slots` ]; then :; else echo bone_pwm_P8_13 > /sys/devices/bone_capemgr.9/slots; fi");
  //  The directory </sys/devices/ocp.3/pwm_test_P8_13.15> should be created now.
  system("if [ -e /sys/devices/ocp.3/pwm_test_P8_13.15 ]; then :; else mkdir /sys/devices/ocp.3/pwm_test_P8_13.15; fi");
  system("echo 20000000 > /sys/devices/ocp.3/pwm_test_P8_13.15/period");
  system("echo 0 > /sys/devices/ocp.3/pwm_test_P8_13.15/polarity");
  system("echo 1 > /sys/devices/ocp.3/pwm_test_P8_13.15/run");
  system("if [ -e /sys/devices/ocp.3/pwm_test_P8_13.15/duty ]; then :; else echo  510000 > /sys/devices/ocp.3/pwm_test_P8_13.15/duty; fi");

  connect(slider, SIGNAL(valueChanged(int)), label, SLOT(setNum(int)));
  connect(slider, SIGNAL(valueChanged(int)), this, SLOT(value(int)));
}

Slider::~Slider() {
  /*
  *  We need to wait the servo turning before turning it off
  *  so we don't hear the noise coming from the servo.
  */
  system("sleep 1");
  system("echo 0 > /sys/devices/ocp.3/pwm_test_P8_13.15/run");
}

void Slider::value(int k) {
  char buffer[70];
  sprintf(buffer, "echo %d > /sys/devices/ocp.3/pwm_test_P8_13.15/duty\n", k);
  system(buffer);
  std::cout << k << std::endl;
  /*
  duty=`cat /sys/devices/ocp.3/pwm_test_P8_13.15/duty`
  if [ $duty -gt 1000000  ]; then
    echo  510000 > /sys/devices/ocp.3/pwm_test_P8_13.15/duty
    echo "clockwise"
  else
    echo 2400000 > /sys/devices/ocp.3/pwm_test_P8_13.15/duty
  echo "counter-clockwise"
  fi
  */
}
