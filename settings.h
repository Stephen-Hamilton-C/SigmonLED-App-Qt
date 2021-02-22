#ifndef SETTINGS_H
#define SETTINGS_H

#include <QObject>
#include <QSettings>

class Settings : public QObject
{
	Q_OBJECT

	Q_PROPERTY(bool darkMode READ darkMode WRITE setDarkMode NOTIFY darkModeChanged)
	Q_PROPERTY(bool autoConnect READ autoConnect WRITE setAutoConnect NOTIFY autoConnectChanged)

public:
	explicit Settings(QObject *parent = nullptr);

private slots:
	void emitInit();

private:
	QSettings settings;

	bool darkMode();
	void setDarkMode(bool darkMode);
	bool autoConnect();
	void setAutoConnect(bool autoConnect);

signals:
	void darkModeChanged(bool darkMode);
	void autoConnectChanged(bool autoConnect);

};

#endif // SETTINGS_H
