//
// Created by timo.homburg on 20.05.2024.
//

#include "QGMDialogChooseAnnotationTemplate.h"
#include "annotationtemplate.h"

QGMDialogChooseAnnotationTemplate::QGMDialogChooseAnnotationTemplate(MeshWidget* themwidget){
    this->templatelist=themwidget->annotationtemplates;
    auto * gridLayout = new QGridLayout(this);
    auto * titlelabel=new QLabel(this);
    this->setWindowTitle("Choose Annotation Template");
    this->setWindowIcon( QIcon( _GIGAMESH_LOGO_ ) );
    this->chooseAnnotationTemplate=new QComboBox(this);
    this->themwidget=themwidget;
    titlelabel->setText("Choose Annotation Template: ");
    gridLayout->addWidget(titlelabel,0,0,1,2);
    this->chooseAnnotationTemplate->addItem("Default Template");
    this->chooseAnnotationTemplate->addItems(templatelist.keys());
    gridLayout->addWidget(this->chooseAnnotationTemplate,0,1,1,2);
    this->annotationtemplateFromURLLabel=new QLabel("Annotation Template from URL:",this);
    this->annotationtemplateFromURL=new QLineEdit(this);
    auto* checkTemplateURL=new QPushButton();
    gridLayout->addWidget(annotationtemplateFromURLLabel,1,0);
    gridLayout->addWidget(annotationtemplateFromURL,1,1);
    gridLayout->addWidget(checkTemplateURL,1,2);
    auto * okbutton=new QPushButton(this);
    okbutton->setText("Ok");
    gridLayout->addWidget(okbutton,2,1);
    auto * cancelbutton=new QPushButton(this);
    cancelbutton->setText("Cancel");
    gridLayout->addWidget(cancelbutton,2,0);
    connect(checkTemplateURL,SIGNAL(clicked()),
            this,SLOT(checkTemplateURL()));
    connect(okbutton,SIGNAL(clicked()),
            this,SLOT(applyChanges()));
    connect(cancelbutton,SIGNAL(clicked()),
            this,SLOT(close()));
    this->setLayout(gridLayout);
    this->loadAnnotationTemplateIndex();
}

void QGMDialogChooseAnnotationTemplate::loadAnnotationTemplateIndex(){
    this->fd=new FileDownloader(QUrl(this->annotemplateindex),this);
    std::cout << "Loading Index from " << this->annotemplateindex.toStdString() << "\n";
    connect(fd, SIGNAL (downloaded()), this, SLOT (handleDownloadResultIndex()));
}

void QGMDialogChooseAnnotationTemplate::checkTemplateURL(){
    this->fd=new FileDownloader(QUrl(this->annotationtemplateFromURL->text()),this);
    connect(fd, SIGNAL (downloaded()), this, SLOT (handleDownloadResult()));
}

void QGMDialogChooseAnnotationTemplate::handleDownloadResultIndex()
{
    QByteArray result=this->fd->downloadedData();
    QJsonDocument annoDoc;
    annoDoc=QJsonDocument::fromJson(result);
    std::cout << "Processing Index Result \n";
    QJsonArray templatejson=annoDoc.array();
    for(int i=0;i<templatejson.count();i++){
        std::cout << "Working through template index " << i << "\n";
        QJsonObject curobj=templatejson.at(i).toObject();
        this->chooseAnnotationTemplate->addItem(curobj.find("title")->toString());
    }
}

void QGMDialogChooseAnnotationTemplate::handleDownloadResult()
{
    QByteArray result=this->fd->downloadedData();

    const AnnotationTemplate &temp = AnnotationTemplate(result);


}

void QGMDialogChooseAnnotationTemplate::applyTemplate(){

}

void QGMDialogChooseAnnotationTemplate::applyChanges(){

}

void QGMDialogChooseAnnotationTemplate::deselectTemplate(){

}