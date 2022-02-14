#ifndef GRIDLAYUOTUTIL_H
#define GRIDLAYUOTUTIL_H

#include <QGridLayout>
#include <QWidget>

class GridLayoutUtil {

public:
  static void rimuoviRiga(QGridLayout *layout, int row, bool deleteWidgets = true);

private:
  static void remove(QGridLayout *layout, int row, int column, bool deleteWidgets);
  static void deleteChildWidgets(QLayoutItem *item);
};

#endif // GRIDLAYUOTUTIL_H
