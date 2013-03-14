import QtQuick 1.0

Rectangle {
    id: order_window
    signal itemClick(string item_id)

    Image {
        id: itemImage
        source: "qrc:/images/backgrounds/bg1.png"
        anchors.fill: parent
        smooth: true;
        //fillMode: Image.PreserveAspectCrop
    }

    ListView {
        id: orderView
        anchors.fill: parent
        anchors.margins: 10
        spacing: 5
        model: ordersModel
        delegate: orderDelegate
        clip: true
    }

    Component {
        id: orderDelegate

        Rectangle {

            id: orderRect
            width: 290
            height: 50

            BorderImage {
                id: itemImage
                width: 285; height: parent.height
                source: mouseArea.containsMouse ? "qrc:/images/pressed_button.png" : "qrc:/images/normal_button.png" ;
                border.left: 4; border.top: 4
                border.right: 4; border.bottom: 4
            }

            MouseArea {
                id: mouseArea
                anchors.fill: parent

                onClicked: {
                    console.debug("item: " + model.modelData.orderId + " is clicked");
                    order_window.itemClick(orderIndexId);
                }
            }

            Item {
                anchors.fill: parent
                anchors.top: parent.top
                anchors.topMargin: 1

                Image {
                    id: iconImage
                    width: 32; height: 32
                    anchors.left: parent.left
                    anchors.top: parent.top
                    anchors.topMargin: 5
                    source: "qrc:/images/juices/category_" + model.modelData.orderCategory + ".png"
                    smooth: true
                }

                Item {
                    height: parent.height
                    width: 240
                    anchors.left: iconImage.right
                    anchors.leftMargin: 10

                    Text {
                        id: orderLabel
                        text: orderName;
                        font.bold: true;
                        font.pointSize: 14;
                        font.family: "Hacen Liner Screen Bd";

                        Text {
                            text: model.modelData.orderName + " -- " + model.modelData.orderDescription
                            anchors.top: parent.baseline
                            anchors.topMargin: 4
                        }
                    }

                    Text {
                        text: orderCost + " SR"
                        font.pointSize: 16;
                        font.family: "ChunkFive";
                        anchors.right: parent.right
                        anchors.top: parent.top
                        anchors.rightMargin: 5
                        anchors.topMargin: 12
                        color: "black"
                    }
                }
            }
        }

    }

}
