#include "TileGraphics.hpp"

#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>
#include "../SNScene.hpp"
#include "../SNHelpers.hpp"
#include <QMap>

const QPolygonF &TileGraphics::hexagon()
{
		static const QPolygonF hexagon_ = []{
		QPolygonF result;
		for (int i = 0; i < 6; ++i)
			result << QPointF(RADIUS * cos(2 * 3.14 / 6 * i), RADIUS * sin(2 * 3.14 / 6 * i));
		return result;
		}();
	return hexagon_;
}

QColor TileGraphics::highlightColor(ActionType type)
{
	static const QHash<ActionType, QColor> map({
		{ActionType::Attack, Qt::red},
		{ActionType::Capture, Qt::magenta},
		{ActionType::Move, Qt::cyan},
		{ActionType::None, Qt::white},
		{ActionType::Settle, Qt::yellow},
		{ActionType::CreateUnit, Qt::darkYellow}
	});
	return map[type];
}

TileGraphics::TileGraphics(const Tile *tile, QGraphicsItem *parent) : QGraphicsPolygonItem(hexagon(), parent),
tile_(tile), actionType_(ActionType::None)
{
	setPos(coordToPos(tile->position()));
}

TileGraphics::~TileGraphics()
{
	
}

void TileGraphics::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	dynamic_cast<SNScene *>(scene())->select(tile_);
	QGraphicsItem::mousePressEvent(event);
}

void TileGraphics::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	QGraphicsItem::mouseReleaseEvent(event);
}

void TileGraphics::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	QPen pen = painter->pen();
	pen.setWidth(5);
	pen.setColor(Qt::green);
	painter->setPen(pen);
	painter->drawPolygon(polygon(), Qt::OddEvenFill);
	if (actionType_ != ActionType::None) {
		QPainterPath path;
		path.addPolygon(polygon());
		painter->setOpacity(OPACITY);
		painter->fillPath(path, highlightColor(actionType_));
	}
}

void TileGraphics::highlight(ActionType actionType)
{
	actionType_ = actionType;
	update();
}

