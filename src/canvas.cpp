﻿#include "canvas.h"
#include "ui_canvas.h"

#include <QMouseEvent>
#include <QPainter>

Canvas::Canvas(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Canvas)
{
    ui->setupUi(this);
    clear();
}

Canvas::~Canvas()
{
    delete ui;
}

void Canvas::open()
{
    // TODO
}

void Canvas::save()
{
    // TODO
}

void Canvas::clear()
{
    count = 0;
    selected = false;

    // 请求重绘
    update();
}

void Canvas::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) // 单击左键选中
    {
        int selectedIndex = -1;
        for (int i = count - 1; i >= 0; --i)
        {
            // 逆序遍历，存在多个时选择最顶层的
            if (squares[i].contains(event->pos()))
            {
                selectedIndex = i;
                break;
            }
        }

        // 未点击正方形
        if (selectedIndex < 0)
            return;

        selected = true; // 更新选中状态

        // 将选中正方形移至顶部
        for (int i = selectedIndex; i < count; ++i)
        {
            if (i < (count - 1))
            {
                std::swap(squares[i], squares[i + 1]);
            }
        }
    }
    else if (event->button() == Qt::RightButton) // 单击右键取消选中
    {
        selected = false; // 更新选中状态
    }
    // 请求重绘
    update();
}

void Canvas::mouseReleaseEvent(QMouseEvent *event)
{
    // TODO
}

void Canvas::mouseMoveEvent(QMouseEvent *event)
{
    // TODO
}

void Canvas::mouseDoubleClickEvent(QMouseEvent *event)
{
    // 双击生成正方形
    if (count < 6)
    {
        // 事件位置为 Canvas 坐标，需要转换为 canvas 坐标
        QRect squareRect(0, 0, 60, 60);
        squareRect.moveCenter(event->pos());
        squares[count] = squareRect;
        ++count;
    }

    // 请求重绘
    update();
}

void Canvas::keyPressEvent(QKeyEvent *event)
{
    // TODO
}

void Canvas::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);

    // 背景为白色
    painter.fillRect(QRect(0, 0, 600, 600), Qt::white);

    // 按照序号绘制正方形，及先后覆盖关系
    for (int i = 0; i < count; ++i)
    {
        if ((i == (count - 1)) && selected)
        {
            /* 选中正方形，填充绿色，边框红色
             * 只绘制被移动到顶层的选中正方形，即之前被选中的自动取消选中 */
            painter.fillRect(squares[i], Qt::green);
            painter.setPen(Qt::red);
            painter.drawRect(squares[i]);
        }
        else
        {
            // 未选中正方形，填充蓝色，边框黑色
            painter.fillRect(squares[i], Qt::blue);
            painter.setPen(Qt::black);
            painter.drawRect(squares[i]);
        }
    }
}
