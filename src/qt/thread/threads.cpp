#include <QApplication>
#include <QtWidgets>

int main(int argc, char **argv)
{
  QApplication app(argc, argv);
  QLabel win1(QString::fromUtf8("GAME"));
  win1.show();
  app.exec();
  win1.hide();
  QLabel win2(QString::fromUtf8("Score"));
  win2.show();
  return app.exec();
}

