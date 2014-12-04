import QtQuick 2.3
import QtQuick.Controls 1.2
import "../gameBoard.js" as Logic

Rectangle {
	id: gameBoard
	width: parent.width
	height: parent.height
	antialiasing: true

	function update() {
		Logic.update();
	}

	Component.onCompleted: {

		Logic.createBoard()
	}
	MouseArea {
		anchors.fill: parent
		drag.target: scene;
		drag.minimumX: parent.width - scene.width
		drag.maximumX: 0
		drag.minimumY: parent.height - scene.height
		drag.maximumY: 0
		drag.filterChildren: true
		acceptedButtons: Qt.AllButtons
		onWheel: {
			if (wheel.angleDelta.y > 0) {
				if (scene.scale < 1)
					scene.scale += 0.05
			} else {
				if (scene.scale > 0.1)
					scene.scale -= 0.05
			}
		}

		onClicked: {
			console.log(mouseX + " " + mouseY + " " + scene.childAt(mouseX, mouseY).width + "\n")
		}

		onPositionChanged: {
			console.log("SceneX = " + scene.childAt(mouseX, mouseY).x / 100)
			console.log("SceneY = " + scene.childAt(mouseX, mouseY).y / 100 + "\n")
		}
		Rectangle {
			height: 5000
			width: 5000
			x: 0
			y: 0
			id:scene

		 }


 }

	signal exit()

	Button {
		z: 1
		text: "Quit"
		onClicked:
			gameBoard.exit()
	}
}
