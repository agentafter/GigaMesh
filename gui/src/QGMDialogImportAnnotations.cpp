//
// Created by timo.homburg on 01.05.2024.
//


#include <QWidget>
#include <QColorDialog>
#include <QFileDialog>
#include <QJsonParseError>
#include <QMap>
#include <QMessageBox>
#include <iostream>
#include "QGMDialogImportAnnotations.h"
#include "ColorSelectorButton.h"
#include "GigaMesh/mesh/primitive.h"

QGMDialogImportAnnotations::QGMDialogImportAnnotations(MeshWidget* mMeshWidget,QWidget *parent){
    this->meshwidget=mMeshWidget;
    int linecounter=0;
    this->setWindowTitle("Import Annotations");
    this->setWindowIcon( QIcon( _GIGAMESH_LOGO_ ) );
    auto * gridLayout = new QGridLayout(this);
    auto* annoctemplatecboxLabel=new QLabel();
    annoctemplatecboxLabel->setText("Color Template:");
    gridLayout->addWidget(annoctemplatecboxLabel,linecounter,0);
    this->annostyletemplatecbox=new QComboBox();
    gridLayout->addWidget(annostyletemplatecbox,linecounter,1);
    linecounter+=1;
    auto* annostylecboxLabel=new QLabel();
    annostylecboxLabel->setText("Annotation Style:");
    gridLayout->addWidget(annostylecboxLabel,linecounter,0);
    this->annostylecbox=new QComboBox();
    annostylecbox->addItem("Border + Filling");
    annostylecbox->addItem("Border Only");
    annostylecbox->addItem("Filling Only");
    gridLayout->addWidget(annostylecbox,linecounter,1);
    linecounter+=1;
    auto* annocolorLabel=new QLabel();
    annocolorLabel->setText("Annotation Color:");
    gridLayout->addWidget(annocolorLabel,linecounter,0);
    annocolorButton=new ColorSelectorButton(this);
    annocolorButton->setColor(QColor().blue());
    gridLayout->addWidget(annocolorButton,linecounter,1);
    linecounter+=1;
    auto* annobordercolorLabel=new QLabel();
    annobordercolorLabel->setText("Annotation Border Color:");
    gridLayout->addWidget(annobordercolorLabel,linecounter,0);
    annobordercolorButton=new ColorSelectorButton(this);
    annobordercolorButton->setColor(QColor().black());
    gridLayout->addWidget(annobordercolorButton,linecounter,1);
    linecounter+=1;
    auto* borderThicknessLabel=new QLabel();
    borderThicknessLabel->setText("Annotation Border Thickness:");
    gridLayout->addWidget(borderThicknessLabel,linecounter,0);
    thicknessEdit=new QDoubleSpinBox();
    thicknessEdit->setSingleStep(0.1);
    thicknessEdit->setMinimum(0.0);
    thicknessEdit->setValue(0.5);
    gridLayout->addWidget(thicknessEdit,linecounter,1);
    linecounter+=1;
    auto* selectFileLabel=new QLabel();
    selectFileLabel->setText("Select Annotation File:");
    gridLayout->addWidget(selectFileLabel,linecounter,0);
    filepath=new QLineEdit();
    gridLayout->addWidget(filepath,linecounter,1);
    auto* searchFile=new QPushButton("...");
    connect(searchFile,SIGNAL(clicked()),
            this,SLOT(chooseFile()));
    gridLayout->addWidget(searchFile,linecounter,2);
    linecounter+=1;
    auto* sideLabel=new QLabel();
    sideLabel->setText("Annotation File Contained Side:");
    gridLayout->addWidget(sideLabel,linecounter,0);
    this->sideEdit=new QComboBox();
    sideEdit->addItem("n/a");
    sideEdit->addItem("front");
    sideEdit->addItem("back");
    sideEdit->addItem("left");
    sideEdit->addItem("right");
    sideEdit->addItem("top");
    sideEdit->addItem("bottom");
    gridLayout->addWidget(sideEdit,linecounter,1);
    linecounter+=1;
    auto * okbutton=new QPushButton(this);
    okbutton->setText("Ok");
    gridLayout->addWidget(okbutton,linecounter,1);
    auto * cancelbutton=new QPushButton(this);
    cancelbutton->setText("Cancel");
    gridLayout->addWidget(cancelbutton,linecounter,0);
    connect(okbutton,SIGNAL(clicked()),
            this,SLOT(importAnnotations()));
    connect(cancelbutton,SIGNAL(clicked()),
            this,SLOT(close()));
    this->setLayout(gridLayout);
    setWindowIcon( QIcon( _GIGAMESH_LOGO_ ) );
    this->show();
}

//! Fetches target.selector.type of an annotation, without dereferencing keys which may be absent.
static QString selectorTypeOf( const QJsonObject& rAnnotation ) {
	return rAnnotation.value( "target" ).toObject().value( "selector" ).toObject().value( "type" ).toString();
}

//! True for selector types whose import writes per-vertex labels. Box3DSelector is drawn as a pure
//! overlay instead and therefore leaves the labeling of the mesh untouched.
static bool selectorLabelsVertices( const QString& rSelectorType ) {
	return rSelectorType == "WKTSelector" || rSelectorType == "WktSelector" ||
	       rSelectorType == "SvgSelector" || rSelectorType == "SVGSelector";
}

//! Maps an annotation tag - e.g. "Wedge" or "Character" - to a color of the standard GigaMesh
//! label palette. Tags are numbered in order of appearance, so the n-th distinct tag of an
//! annotation file gets the n-th palette color. Untagged annotations share the index of the empty tag.
static QColor colorForTagLabel( const QString& rTagLabel, QMap<QString,int>& rTagLabelToIndex ) {
	auto foundIdx = rTagLabelToIndex.find( rTagLabel );
	if( foundIdx == rTagLabelToIndex.end() ) {
		foundIdx = rTagLabelToIndex.insert( rTagLabel, static_cast<int>( rTagLabelToIndex.size() ) );
	}
	unsigned char colRGB[3];
	if( !Primitive::getColor( colRGB, foundIdx.value() % 11, Primitive::COLMAP_BREWER_PAIRED ) ) {
		return QColor( 255, 191, 0 );
	}
	return QColor( colRGB[0], colRGB[1], colRGB[2] );
}

void QGMDialogImportAnnotations::importAnnotations(){
    QString filename = this->filepath->text();
    this->close();
    int side=0;
    QString sideval=this->sideEdit->currentText();
    QString sidestr="noside";
    if(sideval!="n/a"){
        sidestr=sideval;
    }
    std::cout << filename.toStdString() << std::endl;
    if (!filename.isNull()) {
        if (filename.contains("front")) {
            side = 3;
            sidestr="front";
        } else if (filename.contains("back")) {
            side = 6;
            sidestr="back";
        } else if (filename.contains("bottom")) {
            side = 5;
            sidestr="bottom";
        } else if (filename.contains("top")) {
            side = 1;
            sidestr="top";
        } else if (filename.contains("left")) {
            side = 2;
            sidestr="left";
        } else if (filename.contains("right")) {
            side = 4;
            sidestr="right";
        }
        QFile jsonfile;
        jsonfile.setFileName(filename);
        qDebug() << filename;
        if(!jsonfile.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this,tr("Import Annotations"),
                                  tr("Could not open '%1':\n%2").arg(filename,jsonfile.errorString()));
            return;
        }
        QByteArray data = jsonfile.readAll();
        //qDebug()<<QJsonDocument::fromJson(data);
        QJsonParseError parseError{};
        QJsonDocument annoDoc = QJsonDocument::fromJson(data,&parseError);
        if(parseError.error!=QJsonParseError::NoError){
            jsonfile.close();
            QMessageBox::critical(this,tr("Import Annotations"),
                                  tr("'%1' is no valid JSON:\n%2 (offset %3)")
                                          .arg(filename,parseError.errorString()).arg(parseError.offset));
            return;
        }
        QJsonObject mainObject = annoDoc.object();
        if(mainObject.isEmpty()){
            jsonfile.close();
            QMessageBox::warning(this,tr("Import Annotations"),
                                 tr("'%1' contains no annotations. Expected a JSON object mapping "
                                    "annotation ids to annotations.").arg(filename));
            return;
        }
        QStringList thekeys = mainObject.keys();
        std::list<Annotation*> annotationlist;
        std::cout << "Getting border parameters" << std::endl;
        bool borderOnly=false;
        bool border=true;
        if(this->annostylecbox->currentText().contains("Border Only")){
            borderOnly=true;
        }else if(this->annostylecbox->currentText().contains("Filling Only")){
            borderOnly=false;
        }else if(this->annostylecbox->currentText().contains("Border + Filling")){
            border=true;
            borderOnly=false;
        }
        //std::cout << "Accessing meshwidget" << std::endl;
        //! Only an import which actually writes per-vertex labels needs a clean labeling to start from.
        //! A file holding nothing but Box3DSelectors is a pure overlay, so any labels already present -
        //! e.g. the labelid read from the mesh file itself - are kept.
        bool writesVertexLabels=false;
        for(const QString& key:thekeys){
            if(selectorLabelsVertices(selectorTypeOf(mainObject.value(key).toObject()))){
                writesVertexLabels=true;
                break;
            }
        }
        if (writesVertexLabels && !meshwidget->getMesh()->annotationsLoaded) {
            meshwidget->getMesh()->labelVerticesNone();
            meshwidget->getMesh()->labelVerticesBackground();
        }
        QColor annocolor=annocolorButton->getColor();
        QColor annobordercolor=annobordercolorButton->getColor();
        //! Each distinct annotation tag (e.g. "Wedge", "Character") gets the next color of the
        //! standard GigaMesh label palette, so annotations of different type are told apart by color.
        QMap<QString,int> tagLabelToIndex;
        std::cout << "Creating annos" << std::endl;
        for (int i = 0; i < mainObject.size(); ++i) {//mainObject.size();
            QJsonObject curannojson = mainObject.find(thekeys.at(i))->toObject();
            QString annotype = selectorTypeOf(curannojson);
            std::cout << "Creating first anno" << std::endl;
            Annotation* curanno = new Annotation(curannojson, thekeys.at(i), meshwidget->getMesh(), sidestr);
            std::cout << "CurAnno created " << std::endl;
            if (annotype == "WKTSelector" || annotype == "WktSelector") {
                meshwidget->getMesh()->labelVerticesInBBOX(curanno->minX, curanno->maxX, curanno->minY, curanno->maxY,
                                                            curanno->minZ, curanno->maxZ, 2.0, border,borderOnly,annocolor,annobordercolor,thicknessEdit->value());
            } else if (annotype == "SvgSelector" || annotype == "SVGSelector") {
                meshwidget->getMesh()->labelVerticesInBBOX(curanno->minX, curanno->maxX, curanno->minY, curanno->maxY,
                                                            side, 2.0, border, borderOnly,annocolor,annobordercolor,thicknessEdit->value());
            } else if (annotype == "Box3DSelector") {
                // Boxes are already in mesh coordinates and are shown as a wireframe overlay, so no
                // vertex labeling takes place. The style/thickness/color fields of this dialog have no
                // effect on such annotations - their color is derived from the annotation's tag instead.
                curanno->bboxColor = colorForTagLabel( curanno->tagLabel, tagLabelToIndex );
            }
            annotationlist.push_back(curanno);
            meshwidget->addAnnotation(curanno);
        }
        meshwidget->calculateRelativeAnnotationPositions();
        meshwidget->getMesh()->annotationsLoaded = true;
        std::cout << annotationlist.size() << std::endl;
        jsonfile.close();
    }

}


void QGMDialogImportAnnotations::chooseFile()
{
    QString directory = QFileDialog::getOpenFileName(this,
                                                          tr("Find Files"), QDir::currentPath(),
                                                          QString(), nullptr, QFileDialog::DontUseNativeDialog);

    if (!directory.isEmpty()) {
        this->filepath->setText(directory);
    }
}