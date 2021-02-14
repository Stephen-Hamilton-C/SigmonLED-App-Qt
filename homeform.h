#ifndef HOMEFORM_H
#define HOMEFORM_H

#include <QObject>
#include <QColor>
#include <QAbstractItemModel>

class HomeForm : public QObject
{
	Q_OBJECT

	//I did the wrong property thing but the syntax is all right. I'll leave it here so I can ref it later
	//Q_PROPERTY(QString connButtonText READ connButtonText WRITE setConnButtonText NOTIFY connButtonTextChanged)

	Q_PROPERTY(QStringList devices MEMBER devices NOTIFY devicesChanged);
	Q_PROPERTY(QString highlightedDelegate MEMBER highlightedDelegate NOTIFY highlightedDelegateChanged);
	Q_PROPERTY(bool showAll READ showAll WRITE setShowAll NOTIFY showAllChanged);

	//Basically exposes read and write of a var to Qml. NOTIFY is already setup in the background
	//Q_PROPERTY(type qmlVarName MEMBER varName)



public:
	explicit HomeForm(QObject *parent = nullptr);

private slots:
	void devicesUpdated(QStringList deviceNames);

public slots:
	void connectPressed();
	void connectToTestDevice();

private:

	QStringList devices;
	QString highlightedDelegate;
	const QString shownBrand = "64:69:4E";
	bool m_showAll = false;
	bool showAll();
	void setShowAll(bool showAll);

	//QString m_connButtonText = "Not Connected";
	//QString connButtonText();
	//void setConnButtonText(QString value);

signals:
	//void connButtonTextChanged();
	void devicesChanged(QStringList devices);
	void highlightedDelegateChanged();
	void showAllChanged(bool showAll);

};

#endif // HOMEFORM_H
