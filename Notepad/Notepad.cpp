#include "Notepad.h"
#include"ThreadPool.h"
#include <QPlainTextEdit>
#include <iostream>
#include<qtoolbutton.h>
#include<thread>
#include<mutex>
#include<qtoolbar.h>
#include<qthread.h>
#include<execution>
#include"Logger.h"
#include<algorithm>
#include <QFileDialog>
#include "FileReader.h"
#include  "FileWriter.h"


class MyClass
{
public:
    MyClass();
    ~MyClass();

private:

};

MyClass::MyClass()
{
}

MyClass::~MyClass()
{
}

    class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> m_StartTimePoint;

public:

    void Stop()
    {
        auto endTimePoint = std::chrono::high_resolution_clock::now();

        auto start = std::chrono::time_point_cast<std::chrono::microseconds>(m_StartTimePoint).time_since_epoch().count();

        auto end = std::chrono::time_point_cast<std::chrono::microseconds>(endTimePoint).time_since_epoch().count();

        auto duration = end - start;

        double ms = duration * 0.001;

        Logger::LOG(std::to_string(ms));

        std::cout << duration << "us (" << ms << "ms)\n";
    }

    Timer()
    {
        m_StartTimePoint = std::chrono::high_resolution_clock::now();

    }
    ~Timer()
    {
        Stop();
    }
};


Notepad::Notepad(QWidget *parent):
QMainWindow(parent)
{
    ui.setupUi(this);
    setUi();
    setConnects();
    update();
    this->setWindowTitle(QString::fromStdString(m_current_path));
}           

Notepad::~Notepad()
{
    
}



void Notepad::on_save_bar_clicked() 
{
    try
    {
        auto text = m_field->toPlainText();
#ifdef _DEBUG
        Logger::LOG(text.toStdString());
#endif // _DEBUG

        FileWriter::updatePath(m_current_path);
        FileWriter::write(text.toStdString());
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << " :(";
#ifdef _DEBUG
        Logger::LOG("Error: " + std::string(e.what()));
#endif // _DEBUG

    }
}

void Notepad::on_open_bar_Clicked()
{
    try
    {
        auto fileName = QFileDialog::getOpenFileName(this, tr("Choose file: "));

        m_current_path = (fileName != "" && fileName != " ") ? fileName.toStdString() : "./log.txt"; 

    #ifdef _DEBUG
        Logger::LOG(m_current_path);
    #endif // _DEBUG


        update();
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << " :(";
#ifdef _DEBUG
        Logger::LOG("Error: " + std::string(e.what()));
#endif // _DEBUG

    }
}   

void Notepad::on_zoom_in_bar_clicked()
{
    try
    {
        QFont font = m_field->font();
        font.setPointSize(font.pointSize() + 3);
        m_field->setFont(font);
#ifdef _DEBUG
        Logger::LOG("Zoom in button clicked!");
#endif // _DEBUG

    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << " :(";
    }
}

void Notepad::on_zoom_out_bar_clicked()
{
    try
    {
#ifdef _DEBUG
        Logger::LOG("Zoom out button clicked");
#endif // _DEBUG

        QFont font = m_field->font();
        font.setPointSize(font.pointSize() - 3);
        m_field->setFont(font);
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << " :(";
        #ifdef _DEBUG
        Logger::LOG("Error: " + std::string(e.what()));
        #endif
    }
}

void Notepad::setButtons()
{
    m_button_layout = new QHBoxLayout;
    m_button_layout->addStretch();
    m_word_count_label = new QLabel();
    m_word_count_label->setText("Word count: 0");
    int button_width = this->width() * 0.2;
    m_button_layout->addWidget(m_word_count_label);
    m_button_layout->setContentsMargins(0, 15, 20, 0);
    m_field_layout->addLayout(m_button_layout);
}

void Notepad::setFields()
{
    m_field = new QPlainTextEdit(this);
    m_field->setReadOnly(false);
    m_field_layout->addWidget(m_field);
}

void Notepad::setNavbar()
{
    QToolBar* nav_bar = new QToolBar;
    nav_bar->setMovable(false);
    nav_bar->setFloatable(false);
    save = new QAction("Save", this);
    open = new QAction("Open", this);
    zoom_in = new QAction("+", this);
    zoom_out = new QAction("-", this);
    count_words = new QAction("Count", this);
    QToolButton* save_btn = new QToolButton;
    save_btn->setDefaultAction(save);
    QToolButton* zoom_in_btn = new QToolButton;
    zoom_in_btn->setDefaultAction(zoom_in);
    QToolButton* zoom_out_btn = new QToolButton;
    zoom_out_btn->setDefaultAction(zoom_out);
    QToolButton* open_btn = new QToolButton;
    open_btn->setDefaultAction(open);
    QToolButton* count_btn = new QToolButton;
    count_btn->setDefaultAction(count_words);
    nav_bar->addWidget(open_btn);
    nav_bar->addWidget(save_btn);
    nav_bar->addWidget(zoom_in_btn);
    nav_bar->addWidget(zoom_out_btn);
    nav_bar->addWidget(count_btn);
    this->addToolBar(nav_bar);
}

void Notepad::setUi()
{
    m_field_layout = new QVBoxLayout;
    m_field_layout->setContentsMargins(0, 10, 0, 10);
    setFields();
    setButtons();
    m_central_widget = new QWidget(this);
    m_central_widget->setLayout(m_field_layout);
    setNavbar();
    this->setCentralWidget(m_central_widget);
}

#define OUT 0
#define IN 1

int Notepad::updateWordCount(std::string_view s)
{
        Timer timer;
        int n = s.size(), cnt = 0, i = 0;

        while (i < n && s[i] == ' ')i++;

        for (; i < n; i++)
        {
            if ((s[i] <= 'z' && 'a' <= s[i]) || ('A' <= s[i] && s[i] <= 'Z') || ((int)s[i] == 39))
            {
                while (i < n && ((s[i] <= 'z' && 'a' <= s[i]) || ('A' <= s[i] && s[i] <= 'Z') || ((int)s[i] == 39)))i++;
                i--;
                cnt++;
            }
        }

        return cnt;
        // what does the fox say and also set the fuck down t series I am here to spi;l;l
}

void Notepad::changeWordCount()
{
    auto s = m_field->toPlainText().toStdString();
    reflectCount(updateWordCount(s));
}

void Notepad::reflectCount(int var)
{
    m_word_count_label->setText("Word Count: " + QString::fromStdString(std::to_string(var)));
}

void Notepad::setConnects()
{
    //connect(m_save_btn, &QPushButton::clicked,this,&Notepad::on_submit_btn_clicked);
    connect(save, &QAction::triggered, this, &Notepad::on_save_bar_clicked);
    connect(open, &QAction::triggered, this, &Notepad::on_open_bar_Clicked);
    connect(zoom_in, &QAction::triggered, this, &Notepad::on_zoom_in_bar_clicked);
    connect(zoom_out, &QAction::triggered, this, &Notepad::on_zoom_out_bar_clicked);    
    connect(count_words, &QAction::triggered, this, &Notepad::changeWordCount);
    connect(m_field, &QPlainTextEdit::textChanged, this, &Notepad::changeWordCount);
}

void Notepad::on_submit_btn_clicked()
{
    try
    {
#ifdef _DEBUG
        Logger::LOG("Mess");
#endif // _DEBUG

    } 
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << " :(";
#ifdef _DEBUG
        Logger::LOG("Error: " + std::string(e.what()));
#endif // _DEBUG

    }
}

void Notepad::update()
{
    try
    {
        FileReader::updatePath(m_current_path);

        FileReader::updateContents();

        auto& file_contents = FileReader::getContents();
#ifdef _DEBUG
        Logger::LOG(file_contents);
#endif // _DEBUG


        m_field->clear();

        m_field->setPlainText(QString::fromStdString(file_contents));
    }
    catch (const std::runtime_error& e)
    {
        std::cerr << e.what() << " :(";
#ifdef _DEBUG
        Logger::LOG("Error: " + std::string(e.what()));
#endif // _DEBUG

    }
}

