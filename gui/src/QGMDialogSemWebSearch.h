//
// Created by timo.homburg on 23.05.2024.
//

#ifndef GIGAMESH_QGMDIALOGSEMWEBSEARCH_H
#define GIGAMESH_QGMDIALOGSEMWEBSEARCH_H

#include <QDialog>
#include <QGridLayout>
#include <QListWidget>
#include <QListView>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QIcon>
#include <QRadioButton>

#include "QGMMacros.h"
#include "meshwidget.h"
#include "FileDownloader.h"

class QGMDialogSemWebSearch : public QDialog {

    Q_OBJECT
    FileDownloader* fd;
    QGridLayout* gridLayout;
    QLineEdit* searchField;
    QComboBox* tripleStoreCBox;
    QListView* resultList;
public:
    QGMDialogSemWebSearch(QWidget* w);



};


#endif //GIGAMESH_QGMDIALOGSEMWEBSEARCH_H
