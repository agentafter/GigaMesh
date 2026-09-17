//
// Created by timo.homburg on 29.04.2024.
//

#ifndef GIGAMESH_ANNOTATION_H
#define GIGAMESH_ANNOTATION_H

#include <QJsonObject>
#include <QJsonDocument>
#include <QColor>
#include "GigaMesh/mesh/mesh.h"
#include "meshQt.h"

class Annotation {
    public:
        enum exportFormats{WKTSelector,WKTPolygonSelector, SVGSelector, PLYSelector,PLYFiles, MeshIDSelector,MeshLabelSelector,MeshVertexSelector};
        enum annotationType{Character, Word, Line, Surface};
        Annotation();
        Annotation(QJsonObject annojson,QString annoid, MeshQt* mesh,QString side="noside");
        double minX = 0.0;
        double maxX = 0.0;
        double minY = 0.0;
        double maxY = 0.0;
        double minZ = 0.0;
        double maxZ = 0.0;
        QColor bboxColor = QColor( 255, 191, 0 ); //!< Color used to render 3D BoundingBox
        QString tagLabel;                         //!< Label of the body's "tagging" SpecificResource, e.g. "Wedge" or "Character". Empty when the annotation carries no tag.
        QJsonObject annojson;
        std::set<Vertex*> vertices;
        std::set<Vertex*> bboxVertices;
        Mesh* getAnnotationMesh(Mesh* themesh);
        std::string annotationid;
        MeshQt* themesh = nullptr;
        bool isempty = true;

        bool determineZBBOXFromVertices(std::string side);

        bool pointInAnnotationBBOX3D(double x, double y, double z);

        bool pointInAnnotationBBOX2D(double x, double y);

        bool bboxToVertexIds(MeshQt* meshToTest, bool twodimensional,std::string side);

        QJsonArray getAnnotationBody();

        void setAnnotationBody(QJsonArray newbody);

        void getRelativePositions(std::list<Annotation*> otherannotations);

        void setLabelIDs(uint64_t labelid);

        bool getBBOXFromVertices();

        bool convexHull();

        bool getBBOXVertices(double borderThickness);

        QJsonObject getAnnotation(std::string exportFormats,Mesh* themesh,QString outpath,QString formatstr,bool borderOnly);

        std::string toHTML();

        QString formatFileNameFromFormatString(QString formatstr);

        std::string toString();

        QJsonArray annotationbody;

        std::set<std::string> fieldnames;

        Annotation* leftOf  = nullptr;
        Annotation* rightOf = nullptr;
        Annotation* above   = nullptr;
        Annotation* below   = nullptr;

    private:



        std::string annotationtarget;

};


#endif //GIGAMESH_ANNOTATION_H
