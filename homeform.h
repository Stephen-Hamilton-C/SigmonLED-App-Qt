#ifndef HOMEFORM_H
#define HOMEFORM_H

#include <QObject>
#include <QColor>

class HomeForm : public QObject
{
	Q_OBJECT

	//I did the wrong property thing but the syntax is all right. I'll leave it here so I can ref it later
	//Q_PROPERTY(QString connButtonText READ connButtonText WRITE setConnButtonText NOTIFY connButtonTextChanged)



	//Basically exposes read and write of a var to Qml. NOTIFY is already setup in the background
	//Q_PROPERTY(type qmlVarName MEMBER varName)

public:
	explicit HomeForm(QObject *parent = nullptr);

private:

	//QString m_connButtonText = "Not Connected";
	//QString connButtonText();
	//void setConnButtonText(QString value);


signals:
	//void connButtonTextChanged();

};

#endif // HOMEFORM_H
