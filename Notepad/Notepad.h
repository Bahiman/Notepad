#pragma once

#include <QtWidgets/QMainWindow>
#include <QPlainTextEdit>
#include <QVBoxLayout>
#include <QVBoxLayout>
#include "ui_Notepad.h"
#include <QPushButton>

class Notepad : public QMainWindow
{
    Q_OBJECT

private:
    std::string m_current_path = "./log.txt";
    Ui::NotepadClass ui;
    QPlainTextEdit* m_field;
    QVBoxLayout* m_field_layout;
    QWidget* m_central_widget;
    QPushButton* m_save_btn;
    QHBoxLayout* m_button_layout;
    QAction* save;
    QAction* open;
    QAction* zoom_in;
    QAction* zoom_out;
    void on_save_bar_clicked();
    void on_open_bar_Clicked();
    void on_zoom_in_bar_clicked();
	void on_zoom_out_bar_clicked();
    void setButtons();
    void setNavbar();
    void setFields();
    void setUi();
    void setConnects();
    void on_submit_btn_clicked();
    void update();
    bool saved = true;
public:
    Notepad(QWidget* parent = nullptr);
    ~Notepad();
};
