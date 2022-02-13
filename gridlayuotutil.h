#ifndef GRIDLAYUOTUTIL_H
#define GRIDLAYUOTUTIL_H

#include <QGridLayout>
#include <QWidget>

class GridLayoutUtil {

public:
  static void rimuoviRiga(QGridLayout *layout, int row, bool deleteWidgets = true);

private:
  // Removes all layout items which span the given row and column.
  static void remove(QGridLayout *layout, int row, int column, bool deleteWidgets);

  // Deletes all child widgets of the given layout item.
  static void deleteChildWidgets(QLayoutItem *item);
};

#endif // GRIDLAYUOTUTIL_H
