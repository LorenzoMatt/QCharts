#include "gridlayuotutil.h"

void GridLayoutUtil::rimuoviRiga(QGridLayout *layout, int row, bool deleteWidgets)
{
    remove(layout, row, -1, deleteWidgets);
    layout->setRowMinimumHeight(row, 0);
    layout->setRowStretch(row, 0);
}

void GridLayoutUtil::remove(QGridLayout *layout, int row, int column, bool deleteWidgets)
{
    // We avoid usage of QGridLayout::itemAtPosition() here to improve performance.
    for (int i = layout->count() - 1; i >= 0; i--) {
      int r, c, rs, cs;
      layout->getItemPosition(i, &r, &c, &rs, &cs);
      if (
          (row == -1 || (r <= row && r + rs > row)) &&
          (column == -1 || (c <= column && c + cs > column))) {
        // This layout item is subject to deletion.
        QLayoutItem *item = layout->takeAt(i);
        if (deleteWidgets) {
          deleteChildWidgets(item);
        }
        delete item;
      }
    }
}

void GridLayoutUtil::deleteChildWidgets(QLayoutItem *item)
{
    QLayout *layout = item->layout();
    if (layout) {
      // Process all child items recursively.
      int itemCount = layout->count();
      for (int i = 0; i < itemCount; i++) {
        deleteChildWidgets(layout->itemAt(i));
      }
    }
    delete item->widget();
}
