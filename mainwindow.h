#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
//		Ui::MainWindow *ui;

private slots:
//	void startUp();

	bool statusLoginPage();
	void showLoginPage();
	void hideLoginPage();

    void on_send_clicked();

//    void on_action_Login_triggered();

	void on_actionE_xit_triggered();

	void on_actionClear_chat_triggered();

	void on_loginButton_clicked();

	void on_cancelLoginButton_clicked();

	private:
	Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
