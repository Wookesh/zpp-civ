#ifndef GRAPHICINTERFACE_H
#define GRAPHICINTERFACE_H

#include <QWidget>
#include "GameView.hpp"
#include <QResizeEvent>
#include "NextTurnButton.hpp"
#include "SNScene.hpp"
#include "ObjectInfoBox.hpp"

class GraphicInterface : public QWidget {
Q_OBJECT
public:
	GraphicInterface(QWidget *parent = nullptr);
	~GraphicInterface();
protected:
	void resizeEvent(QResizeEvent *event);
private:
	NextTurnButton *nextTurn_;
	GameView *gameView_;
	SNScene *scene_;
	ObjectInfoBox *infobox_;
	
	void createInterface();
	void createConnections();
};

#endif
