#define nu 3

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QDebug>
#include <QMessageBox>
#include <QDateTime>
#include <QTabWidget>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
	ui->splitter->hide();
	ui->splitter_2->hide();
	ui->msgbox->hide();
	ui->send->hide();
	ui->chat1->hide();
	ui->chat2->hide();	// chatbackup, is shown with /chatbu
	ui->pwInput->setEchoMode(QLineEdit::Password);
}

// public vars
QString clearCmd = "/clear";
QString exitCmd = "/exit";
QString chatBkUp = "/chatbu";
QString noParse = "!! ";
QString validID;
QString validPW;
bool idF = false;
bool pwF = false;
int index;
QString users[nu][2] = {{"Admin","admin"},
						{"Guille","23751818"},
						{"Melba","7779050"}};

bool MainWindow::statusLoginPage() {
	bool check = false;
	if(
		ui->cover->isHidden() ||
		ui->idLabel->isHidden() ||
		ui->pwLabel->isHidden() ||
		ui->idInput->isHidden() ||
		ui->pwInput->isHidden() ||
		ui->loginButton->isHidden() ||
		ui->cancelLoginButton->isHidden()
	) { // if body
		check = false;	// false is hidden
	} else {
		check = true;	// true is shown
	}
	return check;
}
void MainWindow::hideLoginPage() {
	bool check = MainWindow::statusLoginPage();
	if(check) {
		ui->splitter->show();
		ui->splitter_2->show();
		ui->msgbox->show();
		ui->send->show();
		ui->chat1->show();
		ui->cover->hide();
		ui->idLabel->hide();
		ui->pwLabel->hide();
		ui->idInput->hide();
		ui->pwInput->hide();
		ui->loginButton->hide();
		ui->cancelLoginButton->hide();
	}
}

void MainWindow::showLoginPage() {
	bool check = MainWindow::statusLoginPage();
	if(!check) {
		ui->splitter->hide();
		ui->splitter_2->hide();
		ui->msgbox->hide();
		ui->send->hide();
		ui->chat1->hide();
		ui->cover->show();
		ui->idLabel->show();
		ui->pwLabel->show();
		ui->idInput->show();
		ui->pwInput->show();
		ui->loginButton->show();
		ui->cancelLoginButton->show();
	}
}

QString date() {
    QDateTime dateTime = QDateTime::currentDateTime();
//    QString dateStr = dateTime.toString("d/M/yy h:mm ap");	// 13/12/16 8:15 pm
	QString dateStr = dateTime.toString("h:mm:ss");				// 20:15:34
    return dateStr;
}

void MainWindow::on_send_clicked() {
    QString message = ui->msgbox->text().trimmed();
    if(!message.isEmpty()) {
        if(message==clearCmd) {
                ui->chat1->clear();
		} else if(message==exitCmd) {
			this->close();
		} else if(message==chatBkUp) {
			if(ui->chat2->isHidden()) {
				ui->chat2->show();
			} else {
				ui->chat2->hide();
			}
		} else {
			QString messageShortForNoParse = message.at(0);
			messageShortForNoParse += message.at(1);
			messageShortForNoParse += message.at(2);
			if(messageShortForNoParse==noParse) {
				message = message.remove(0,3);
				ui->chat1->appendHtml(QString("[" + date() + "] <b>" + validID + "</b>: ").toUtf8());
				ui->chat2->appendHtml(QString("[" + date() + "] <b>" + validID + "</b>: ").toUtf8());
				ui->chat1->font().Courier;
				ui->chat1->insertPlainText(QString(message).toUtf8());
				ui->chat2->insertPlainText(QString(message).toUtf8());
			} else {
				ui->chat1->appendHtml(QString("[" + date() + "] <b>" + validID + "</b>: " + message).toUtf8());
				ui->chat2->appendHtml(QString("[" + date() + "] <b>" + validID + "</b>: " + message).toUtf8());
			}
		}
    }
    ui->msgbox->clear();
}

void MainWindow::on_loginButton_clicked() {
	if((ui->idInput->text().isEmpty()) || (ui->pwInput->text().isEmpty())) {
		QMessageBox::warning(this,"Error","Please input both ID and Password");
	} else {
		for(int i=0; i<nu; i++) {
			if((ui->idInput->text().toLower()==users[i][0].toLower()) && (ui->pwInput->text()==users[i][1])) {
				idF = true;
				pwF = true;
				index=i;
				i=nu;
			} else {
				idF = false;
				pwF = false;
			}
		}
		if(idF && pwF) {
			validID = users[index][0];
			ui->idInput->clear();
			ui->pwInput->clear();
			hideLoginPage();
			QMessageBox::information(this,"Success","You've been logged in as " + validID);
			ui->chat1->appendHtml(QString("Welcome to Convives Communication Room, " + validID).toUtf8());
			ui->chat2->appendHtml(QString("Welcome to Convives Communication Room, " + validID).toUtf8());
		} else {
			QMessageBox::warning(this,"Fail","ID or Password wrong");
		}
	}
}

void MainWindow::on_cancelLoginButton_clicked() {
	this->close();
}

void MainWindow::on_actionE_xit_triggered() {
	this->close();
}

void MainWindow::on_actionClear_chat_triggered() {
	ui->chat1->clear();
}

MainWindow::~MainWindow() {
	delete ui;
}