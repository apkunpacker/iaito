#ifndef HEXDUMPWIDGET_H
#define HEXDUMPWIDGET_H

#include <QAction>
#include <QDebug>
#include <QMouseEvent>
#include <QTextEdit>

#include <array>
#include <memory>

#include "HexWidget.h"
#include "MemoryDockWidget.h"
#include "common/Highlighter.h"
#include "common/IaitoSeekable.h"
#include "common/SvgIconEngine.h"
#include "core/Iaito.h"

#include "Dashboard.h"

namespace Ui {
class HexdumpWidget;
}

class RefreshDeferrer;
class QSyntaxHighlighter;

class HexdumpWidget : public MemoryDockWidget
{
    Q_OBJECT
public:
    explicit HexdumpWidget(MainWindow *main);
    ~HexdumpWidget() override;
    Highlighter *highlighter;

    static QString getWidgetType();

public slots:
    void initParsing();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    QWidget *widgetToFocusOnRaise() override;

private:
    std::unique_ptr<Ui::HexdumpWidget> ui;

    bool sent_seek = false;

    RefreshDeferrer *refreshDeferrer;
    QSyntaxHighlighter *syntaxHighLighter;

    void refresh();
    void refresh(RVA addr);
    void selectHexPreview();

    void setupFonts();

    void refreshSelectionInfo();
    void updateParseWindow(RVA start_address, RVA end_address);
    void clearParseWindow();
    void showSidePanel(bool show);

    QString getWindowTitle() const override;

private slots:
    void onSeekChanged(RVA addr);

    void selectionChanged(HexWidget::Selection selection);

    void on_parseArchComboBox_currentTextChanged(const QString &arg1);
    void on_parseBitsComboBox_currentTextChanged(const QString &arg1);
    void on_parseTypeComboBox_currentTextChanged(const QString &arg1);
    void on_parseEndianComboBox_currentTextChanged(const QString &arg1);

    void fontsUpdated();

    void on_hexSideTab_2_currentChanged(int index);
    void on_copyMD5_clicked();
    void on_copySHA1_clicked();
    void on_copySHA256_clicked();
    void on_copyCRC32_clicked();
};

#endif // HEXDUMPWIDGET_H
