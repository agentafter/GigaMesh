//
// Created by timo.homburg on 20.05.2024.
//

#ifndef GIGAMESH_QGMDIALOGCHOOSEANNOTATIONTEMPLATE_H
#define GIGAMESH_QGMDIALOGCHOOSEANNOTATIONTEMPLATE_H

#include <QtGui>
#include <QDialog>
#include <QGridLayout>
#include <QListWidget>

#include "QGMMacros.h"
#include "meshwidget.h"
#include "FileDownloader.h"

class QGMDialogChooseAnnotationTemplate : public QDialog {
    Q_OBJECT
    FileDownloader* fd;
    QJsonObject curtemplate;
    QComboBox* chooseAnnotationTemplate;
    QLineEdit* annotationtemplateFromURL;
    QLabel* annotationtemplateFromURLLabel;
    QMap<QString,QJsonObject> templatelist;
    MeshWidget* themwidget;
    QString annotemplateindex="https://www.gigamesh.eu/annotemplatesindex.json";
    QString annotemplaterepository="https://www.gigamesh.eu/annotemplatesall.json";
    public:
    QGMDialogChooseAnnotationTemplate(MeshWidget* themwidget);
    public slots:
    void applyTemplate();
    void checkTemplateURL();
    void handleDownloadResult();
    void handleDownloadResultIndex();
    void loadAnnotationTemplateIndex();
    void deselectTemplate();

};


#endif //GIGAMESH_QGMDIALOGCHOOSEANNOTATIONTEMPLATE_H
