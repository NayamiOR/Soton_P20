//
// Created by Administrator on 2024/4/25.
//

#ifndef P20_CODE_CANVAS_H
#define P20_CODE_CANVAS_H

#define INIT_WIDTH 5000
#define INIT_HEIGHT 5000

#include <QWidget>
#include <QPainter>
#include <QMouseEvent>

class Canvas : public QWidget {
Q_OBJECT

public:
    Canvas(QWidget *parent = nullptr);

    QColor penColor;

protected:
    void mousePressEvent(QMouseEvent *event) override;

    void paintEvent(QPaintEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

    void resizeEvent(QResizeEvent *event) override;

private:
    QPoint lastPoint;
    QImage img;

signals:
    void imgChanged();

public slots:

    void clear();

};


#endif //P20_CODE_CANVAS_H
