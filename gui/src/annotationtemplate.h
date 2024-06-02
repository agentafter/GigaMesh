//
// Created by timo.homburg on 06.05.2024.
//

#ifndef GIGAMESH_ANNOTATIONTEMPLATE_H
#define GIGAMESH_ANNOTATIONTEMPLATE_H


#include <QString>
#include <QJsonArray>
#include <QFile>
#include <QJsonDocument>
#include <QFile>
#include <QJsonObject>

class AnnotationTemplate {

    QJsonArray templatejson;
    void importTemplateJSON(QString filepath);
    void exportTemplateJSON(QString filepath);
    bool validityCheck();
    void addTextField(QString name,QString type);

public:
    AnnotationTemplate(QByteArray data);
    AnnotationTemplate(QString filepath);
};


#endif //GIGAMESH_ANNOTATIONTEMPLATE_H
