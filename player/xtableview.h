#ifndef XTABLEVIEW_H
#define XTABLEVIEW_H

#include "qtableview.h"
#include "QStringListModel"
#include "QStandardItemModel"
class XTableView:public QTableView
{
    Q_OBJECT
public:
    XTableView(QWidget*p=NULL);
    ~XTableView(){}
    QStandardItemModel *model = new QStandardItemModel();
    model->setColumnCount(2);

};

#endif // XTABLEVIEW_H
