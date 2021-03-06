#pragma once

#include <QtWidgets>

class algorithm_scene_base : public QGraphicsScene
{
    Q_OBJECT
public:
    algorithm_scene_base(QObject* parent = nullptr);
protected:
    virtual void drawBackground(QPainter* painter, const QRectF& rect) override;
};

class algorithm_input_scene : public algorithm_scene_base
{
    Q_OBJECT
public:
    algorithm_input_scene(QObject* parent = nullptr);
};

struct points_collection
{
    QList<QPointF> points;
    QColor color;
    float radius = 5.0f;
    bool indexed = false;
};

struct lines_collection
{
    QList<QLineF> lines;
    QColor color;
    float width = 0.0f;
    bool indexed = false;
};

struct polygons_collection
{
    QList<QPolygonF> polygons;
    QColor color;
};

class algorithm_scene
{
private:
    QList<points_collection> _ptcolls;
    QList<lines_collection> _lcolls;
    QList<polygons_collection> _plcolls;
public:
    algorithm_scene(const QList<points_collection>& ptcolls, const QList<lines_collection>& lcolls, const QList<polygons_collection>& plcolls, QObject* parent = nullptr);
public:
    void set_scene(QGraphicsView* view);
};