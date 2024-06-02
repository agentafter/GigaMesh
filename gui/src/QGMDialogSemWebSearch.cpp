//
// Created by timo.homburg on 23.05.2024.
//

#include "QGMDialogSemWebSearch.h"

QGMDialogSemWebSearch::QGMDialogSemWebSearch(QWidget* w) {
    auto *gridLayout = new QGridLayout(this);
    auto *titlelabel = new QLabel(this);
    this->setWindowTitle("Search Semantic Web Concept");
    this->setWindowIcon(QIcon(_GIGAMESH_LOGO_));
    titlelabel->setText("Choose Annotation Template: ");
    this->tripleStoreCBox=new QComboBox();
    this->tripleStoreCBox->addItem("FactGrid");
    this->tripleStoreCBox->addItem("Wikidata");
    this->searchField=new QLineEdit();
    auto* propertyClassSearch=new QRadioButton();
    gridLayout->addWidget(titlelabel, 0, 0, 1, 2);
    gridLayout->addWidget(this->tripleStoreCBox, 0, 1, 1, 2);
    gridLayout->addWidget(propertyClassSearch, 1, 1, 1, 2);
    this->resultList=new QListView();

    //gridLayout->addWidget(this->chooseAnnotationTemplate, 0, 1, 1, 2);
}

/*
void QGMDialogSemWebSearch::searchFactGrid(bool propOrClass){
    this->fd=new FileDownloader("https://database.factgrid.de/query/?SELECT ?item ?itemLabel WHERE { ?item wdt:P2 ?class . ?item rdfs:label ?itemLabel . FILTER(CONTAINS(STR(?itemLabel),\""+this->searchField->text()+"\") }");
    //this->fd->connect()
}

void QGMDialogSemWebSearch::searchWikidata(bool propOrClass){

}

void QGMDialogSemWebSearch::handleQueryResult()
{
    QByteArray result=this->fd->downloadedData();
    QJsonDocument annoDoc;
    annoDoc=QJsonDocument::fromJson(result);
    

}
*/
