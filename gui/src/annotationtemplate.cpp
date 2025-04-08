//
// Created by timo.homburg on 06.05.2024.
//


#include "annotationtemplate.h"

AnnotationTemplate::AnnotationTemplate(QByteArray data){
    QJsonDocument annoDoc;
    annoDoc=QJsonDocument::fromJson(data);
    templatejson=annoDoc.object();
}

AnnotationTemplate::AnnotationTemplate(QString filepath){
    QFile jsonfile;
    jsonfile.setFileName(filepath);
    jsonfile.open(QIODevice::ReadOnly);
    QByteArray data = jsonfile.readAll();
    QJsonDocument annoDoc;
    annoDoc=QJsonDocument::fromJson(data);
    templatejson=annoDoc.object();
}

void AnnotationTemplate::importTemplateJSON(QString filepath){
    /*QFile jsonfile;
    jsonfile.setFileName(filepath);
    jsonfile.open(QIODevice::ReadOnly);
    QByteArray data = jsonfile.readAll();
    qDebug()<<QJsonDocument::fromJson(data);
    QJsonDocument annoDoc;
    annoDoc=QJsonDocument::fromJson(data);
    annotemplate=annoDoc.array().at(0).toObject();*/
}

bool AnnotationTemplate::validityCheck(){
    if(!this->templatejson.contains("fields")){
        return false;
    }
    return true;
}

QJsonObject AnnotationTemplate::getTemplateJSON(){
    return this->templatejson;
}

QString AnnotationTemplate::toHTML(){
    QString result="Annotation Template ";
    if(this->templatejson.contains("name")){
        result+=this->templatejson.find("name")->toString();
    }
    result+="<br/>";
    if(this->templatejson.contains("fields")){
        result+="<table><caption>Fields</caption><thead><th>Field Name</th><th>Field Type</th></thead><tbody>";
        QJsonObject fieldsobj=this->templatejson.find("fields")->toObject();
        for(const QString& key:fieldsobj.keys()){
            result+="<tr><td>"+key+"</td>";
            if(fieldsobj.find(key)->toObject().contains("inputtype")) {
                result+="<td>"+fieldsobj.find(key)->toObject().find("inputtype")->toString()+"</td>";
            }
            result+="</tr>";
        }
        result+="</tbody></table>";
    }
    if(this->templatejson.contains("tags")){
        QJsonArray tagarray=this->templatejson.find("tags")->toArray();
        result+="<table><caption>Tags</caption><thead><th>Tag Name</th><th>TagURI</th></thead><tbody>";
        for(int i=0;i<tagarray.count();i++){
            QJsonObject curtag=tagarray.at(i).toObject();
            if(curtag.contains("label") && curtag.contains("uri")){
                result+="<tr><td>"+curtag.find("label")->toString()+"</td><td>"+curtag.find("uri")->toString()+"</td></tr>";
            }
        }
        result+="</tbody></table>";
    }
    return result;
}

void AnnotationTemplate::exportTemplateJSON(QString filepath){
    /*for (int i = 0; i < templatejson.count(); i++) {
        QJsonObject curobj = templatejson.at(i).toObject();
        if (curobj.contains("name") && curobj.value("name").toString() == templatename) {
            curobj.remove("tags");
            curobj.insert("tags",QJsonArray());
            const QJsonArray &thetags = curobj.value("tags").toArray();
            for (int j = 0; j < this->annotagWidget->rowCount(); j++) {
                thetags.operator+(QJsonObject());
                thetags.at(j).toObject()["tag"]=this->annotagWidget->item(j, 0)->text();
                thetags.at(j).toObject()["uri"]=this->annotagWidget->item(j, 1)->text();
            }
            const QJsonObject &thefields = curobj.value("fields").toObject();
            for (int j = 0; j < this->annotemplateWidget->rowCount(); j++) {
                thefields[this->annotemplateWidget->item(j,0)->text()]=QJsonObject();
                QJsonObject curobject=thefields.value(this->annotemplateWidget->item(j,0)->text()).toObject();
                curobject.insert(QString("inputtype"),this->annotemplateWidget->item(j,1)->text());
                curobject.insert(QString("uri"),this->annotemplateWidget->item(j,2)->text());
                curobject.insert(QString("category"),this->annotemplateWidget->item(j,3)->text());
                curobject.insert(QString("datalist"),this->annotemplateWidget->item(j,4)->text());
            }
        }
    }
    QJsonDocument(templatejson)
     */
}