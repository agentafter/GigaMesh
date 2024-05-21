//
// Created by timo.homburg on 20.05.2024.
//

#include "QGMDialogChooseAnnotationTemplate.h"


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
    auto * okbutton=new QPushButton(this);
    okbutton->setText("Ok");
    gridLayout->addWidget(okbutton,1,1);
    auto * cancelbutton=new QPushButton(this);
    cancelbutton->setText("Cancel");
    gridLayout->addWidget(cancelbutton,1,0);
    connect(okbutton,SIGNAL(clicked()),
            this,SLOT(applyChanges()));
    connect(cancelbutton,SIGNAL(clicked()),
            this,SLOT(close()));
    this->setLayout(gridLayout);
}

void QGMDialogChooseAnnotationTemplate::applyTemplate(){

}

void QGMDialogChooseAnnotationTemplate::deselectTemplate(){

}