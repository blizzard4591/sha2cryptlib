#include <QtWidgets>
#include <QDebug>

#include "shacrypt.h"
#include "ui_main.h"
#include "sodium.h"
#include "exceptions/InternalErrorException.h"

extern "C" char * sha256_crypt(const char *key, const char *salt);
extern "C" char * sha512_crypt(const char *key, const char *salt);

ShaCrypt::ShaCrypt(QWidget *parent) : QMainWindow(parent) {
	ui.setupUi(this);
	
	if (!connect(ui.btnHash, SIGNAL(clicked()), this, SLOT(btnHashOnClick()))) {
		throw InternalErrorException() << "Could not connect signal clicked() in the Client.";
	}

	if (!connect(ui.actionExit, SIGNAL(triggered(bool)), this, SLOT(btnExitOnClick(bool)))) {
		throw InternalErrorException() << "Could not connect signal triggered() in the Client.";
	}
}

void ShaCrypt::btnHashOnClick() {
	ui.btnHash->setEnabled(false);
	int const userHashType = ui.cboxHashType->currentIndex();
	int const userRoundCount = ui.spinBoxRounds->value();
	QString const& userPassword = ui.edtPassword->text();
	
	// Generate a 16 characters Salt
	static const char saltCharacters[65] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz./";
	char userSaltChars[17] = { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	for (int i = 0; i < 16; ++i) {
		uint32_t randValue = randombytes_uniform(64);
		userSaltChars[i] = saltCharacters[randValue];
	}
	// The Length of the Salt-String is at most $5$rounds=999999999$0123456789ABCDEF == 36
	// $5$rounds=5000$toolongsaltstring

	char* password = nullptr;
	if (userHashType == 0) {
		// SHA-256
		qDebug() << "Using hash-type: SHA-256 with " << userRoundCount << " rounds.";
		QString saltInputString = QString("$5$rounds=%1$%2").arg(userRoundCount).arg(userSaltChars);
		qDebug() << "Salt string: " << saltInputString;
		password = sha256_crypt(userPassword.toLocal8Bit().data(), saltInputString.toLocal8Bit().data());
	} else {
		// SHA-512
		qDebug() << "Using hash-type: SHA-512 with " << userRoundCount << " rounds.";
		QString saltInputString = QString("$6$rounds=%1$%2").arg(userRoundCount).arg(userSaltChars);
		qDebug() << "Salt string: " << saltInputString;
		password = sha512_crypt(userPassword.toLocal8Bit().data(), saltInputString.toLocal8Bit().data());
	}

	if (password != nullptr) {
		ui.edtResult->setText(QString(password));
		delete password;
		password = nullptr;
	}

	ui.btnHash->setEnabled(true);
}

void ShaCrypt::btnExitOnClick(bool checked) {
	qDebug() << "Exiting...";
	QApplication::quit();
}